#!/bin/bash
# =============================================================================
#  push_swap — test suite
#
#  Usage:
#     ./test_push_swap.sh              run everything except leaks
#     ./test_push_swap.sh basic        build, errors, output discipline, flags
#     ./test_push_swap.sh correct      checker validation across strategies
#     ./test_push_swap.sh bench        --bench format and counter consistency
#     ./test_push_swap.sh leaks        valgrind on success and error paths
#     ./test_push_swap.sh perf         subject performance thresholds
#     ./test_push_swap.sh complexity   empirical proof of the O() classes
#     ./test_push_swap.sh all          everything, leaks included
# =============================================================================

PROG=./push_swap
if [ "$(uname)" = "Darwin" ]; then CHECKER=./checker_Mac; else CHECKER=./checker_linux; fi
OPS_RE='^(sa|sb|ss|pa|pb|ra|rb|rr|rra|rrb|rrr)$'

RED='\033[0;31m'; GRN='\033[0;32m'; YEL='\033[0;33m'; BLU='\033[0;34m'; NC='\033[0m'
PASS=0; FAIL=0

hdr()  { echo -e "\n${BLU}=== $1 ===${NC}"; }
ok()   { echo -e "  ${GRN}OK${NC}   $1"; PASS=$((PASS+1)); }
ko()   { echo -e "  ${RED}KO${NC}   $1"; [ -n "$2" ] && echo -e "       ${YEL}$2${NC}"; FAIL=$((FAIL+1)); }
skip() { echo -e "  ${YEL}--${NC}   $1"; }

rnd() { shuf -i 0-99999 -n "$1" | tr '\n' ' '; }

# -----------------------------------------------------------------------------
# 1. BUILD
# -----------------------------------------------------------------------------
test_build()
{
	hdr "BUILD"

	if make re > /tmp/ps_build.log 2>&1; then
		ok "make re compiles"
	else
		ko "make re failed" "$(tail -5 /tmp/ps_build.log)"
		echo -e "${RED}Cannot continue without a binary.${NC}"; exit 1
	fi

	out=$(make 2>&1)
	if echo "$out" | grep -qiE 'cc |gcc |clang '; then
		ko "Makefile relinks" "second 'make' rebuilt something"
	else
		ok "no relink on second make"
	fi

	for rule in all clean fclean re; do
		grep -qE "^$rule:" Makefile && ok "rule '$rule' present" \
			|| ko "rule '$rule' missing"
	done

	grep -q -- "-Wall" Makefile && grep -q -- "-Wextra" Makefile \
		&& grep -q -- "-Werror" Makefile \
		&& ok "flags -Wall -Wextra -Werror" || ko "missing required flags"

	grep -rn --include=*.c --include=*.h -E '^[a-zA-Z_].*[a-zA-Z_]+[ \t]*=' srcs includes 2>/dev/null \
		| grep -vE '\(|\)' | grep -q . \
		&& ko "possible global variable — inspect manually" \
		|| ok "no obvious global variables"

	if command -v norminette > /dev/null 2>&1; then
		if norminette srcs includes 2>&1 | grep -q "Error"; then
			ko "norminette errors" "$(norminette srcs includes 2>&1 | grep -B1 Error | head -10)"
		else
			ok "norminette clean"
		fi
	else
		skip "norminette not installed"
	fi
}

# -----------------------------------------------------------------------------
# 2. ERROR HANDLING  (subject p.15 / p.20)
# -----------------------------------------------------------------------------
# expect_error <description> <args...>
expect_error()
{
	local desc="$1"; shift
	local so se rc
	so=$("$PROG" "$@" 2>/tmp/ps_err); rc=$?; se=$(cat /tmp/ps_err)

	if [ "$se" != "Error" ]; then
		ko "$desc" "stderr is '$se', expected exactly 'Error'"
	elif [ -n "$so" ]; then
		ko "$desc" "stdout must stay empty, got: $(echo "$so" | head -1)"
	elif [ "$rc" -eq 0 ]; then
		ko "$desc" "exit code 0 on an error"
	else
		ok "$desc"
	fi
}

# expect_silent <description> <args...>
expect_silent()
{
	local desc="$1"; shift
	local so se rc
	so=$("$PROG" "$@" 2>/tmp/ps_err); rc=$?; se=$(cat /tmp/ps_err)

	if [ -n "$so" ]; then
		ko "$desc" "expected no output, got: $(echo "$so" | head -1)"
	elif [ -n "$se" ]; then
		ko "$desc" "expected empty stderr, got: $se"
	elif [ "$rc" -ne 0 ]; then
		ko "$desc" "exit code $rc, expected 0"
	else
		ok "$desc"
	fi
}

test_errors()
{
	hdr "ERROR HANDLING"

	expect_error "non-numeric argument"        0 one 2 3
	expect_error "duplicate values"            3 2 3
	expect_error "duplicate via sign"          3 2 +2
	expect_error "INT_MAX + 1"                 2147483648
	expect_error "INT_MIN - 1"                 -2147483649
	expect_error "far out of range"            99999999999999
	expect_error "empty string argument"       "" 1
	expect_error "lone plus sign"              + 1
	expect_error "lone minus sign"             - 1
	expect_error "double sign"                 --5 1
	expect_error "trailing garbage"            12a 3
	expect_error "unknown flag"                --turbo 3 2 1
	expect_error "two strategy flags"          --simple --complex 3 2 1
	expect_error "duplicate across strings"    "3 2" "2 1"

	hdr "SILENT CASES"

	expect_silent "no arguments"
	expect_silent "single value"               42
	expect_silent "already sorted"             1 2 3 4 5
	expect_silent "sorted, forced simple"      --simple 1 2 3 4 5
	expect_silent "sorted, forced complex"     --complex 1 2 3 4 5

	hdr "ACCEPTED EDGE VALUES"

	for t in "2147483647 1" "-2147483648 1" "+5 -3 0" "3 1 2" ; do
		if "$PROG" $t > /dev/null 2>/tmp/ps_err && [ ! -s /tmp/ps_err ]; then
			ok "accepts: $t"
		else
			ko "accepts: $t" "$(cat /tmp/ps_err)"
		fi
	done

	# space-separated string form — the subject's own examples rely on it
	for t in "3 1 2" "5 4 3 2 1"; do
		if "$PROG" "$t" > /dev/null 2>/tmp/ps_err && [ ! -s /tmp/ps_err ]; then
			ok "accepts quoted string: \"$t\""
		else
			ko "accepts quoted string: \"$t\"" "$(cat /tmp/ps_err)"
		fi
	done

	if "$PROG" "3 1" 2 > /dev/null 2>&1; then
		ok "accepts mixed string + separate args"
	else
		ko "accepts mixed string + separate args"
	fi
}

# -----------------------------------------------------------------------------
# 3. OUTPUT DISCIPLINE  (subject p.14: operations separated by \n and nothing else)
# -----------------------------------------------------------------------------
test_output()
{
	hdr "OUTPUT DISCIPLINE"

	local args bad
	args=$(rnd 50)

	for s in simple medium complex adaptive; do
		bad=$("$PROG" --$s $args 2>/dev/null | grep -vcE "$OPS_RE")
		if [ "$bad" -eq 0 ]; then
			ok "--$s: stdout holds only valid operations"
		else
			ko "--$s: stdout polluted" \
			   "$("$PROG" --$s $args 2>/dev/null | grep -vE "$OPS_RE" | head -3)"
		fi
	done

	if [ -z "$("$PROG" --simple $args 2>&1 >/dev/null)" ]; then
		ok "stderr silent without --bench"
	else
		ko "stderr should be empty without --bench"
	fi

	if [ -n "$("$PROG" --simple --bench $args 2>&1 >/dev/null)" ]; then
		ok "--bench writes to stderr"
	else
		ko "--bench produced nothing on stderr"
	fi

	bad=$("$PROG" --bench $args 2>/dev/null | grep -vcE "$OPS_RE")
	if [ "$bad" -eq 0 ]; then
		ok "--bench keeps stdout clean (pipeable to checker)"
	else
		ko "--bench leaks metrics onto stdout"
	fi
}

# -----------------------------------------------------------------------------
# 4. CORRECTNESS  (checker)
# -----------------------------------------------------------------------------
test_correct()
{
	hdr "CORRECTNESS (checker)"

	if [ ! -x "$CHECKER" ]; then
		skip "$CHECKER not found or not executable — run: chmod +x $CHECKER"
		return
	fi
	if ! echo "" | "$CHECKER" 1 2 > /dev/null 2>&1; then
		skip "$CHECKER will not run here — check architecture: $(file "$CHECKER" 2>/dev/null | cut -d: -f2-)"
		return
	fi

	# every permutation of 3, plus both of 2 — classic off-by-one territory
	local small=("2 1" "1 2" "1 2 3" "1 3 2" "2 1 3" "2 3 1" "3 1 2" "3 2 1")
	local allok=1
	for p in "${small[@]}"; do
		[ "$("$PROG" $p 2>/dev/null | "$CHECKER" $p)" = "OK" ] || { allok=0; ko "small case: $p"; }
	done
	[ $allok -eq 1 ] && ok "all permutations of n=2 and n=3"

	for s in simple medium complex adaptive; do
		for n in 5 10 33 100 500; do
			local args res
			args=$(rnd $n)
			res=$("$PROG" --$s $args 2>/dev/null | "$CHECKER" $args)
			if [ "$res" = "OK" ]; then
				ok "--$s  n=$n"
			else
				ko "--$s  n=$n" "checker said: ${res:-<empty>}"
			fi
		done
	done

	# structured inputs — where adaptive should shine
	local rev asc nearly
	rev=$(seq 100 -1 1 | tr '\n' ' ')
	nearly="2 1 $(seq 3 100 | tr '\n' ' ')"
	for name in rev nearly; do
		local args="${!name}"
		[ "$("$PROG" $args 2>/dev/null | "$CHECKER" $args)" = "OK" ] \
			&& ok "structured input: $name" || ko "structured input: $name"
	done
}

# -----------------------------------------------------------------------------
# 5. BENCH FORMAT  (subject p.15)
# -----------------------------------------------------------------------------
test_bench()
{
	hdr "BENCH MODE"

	local args out
	args=$(rnd 100)
	out=$("$PROG" --bench $args 2>&1 >/dev/null)

	echo "$out" | grep -qE '^\[bench\] disorder:' \
		&& ok "reports disorder" || ko "missing disorder line"
	echo "$out" | grep -qE '[0-9]+\.[0-9]{2}%' \
		&& ok "disorder as percentage with 2 decimals" || ko "disorder format wrong"
	echo "$out" | grep -qE '^\[bench\] strategy:' \
		&& ok "reports strategy name" || ko "missing strategy line"
	echo "$out" | grep -qE 'O\(' \
		&& ok "reports complexity class" || ko "missing complexity class"
	echo "$out" | grep -qE '^\[bench\] total_ops:' \
		&& ok "reports total_ops" || ko "missing total_ops line"

	local missing=""
	for op in sa sb ss pa pb ra rb rr rra rrb rrr; do
		echo "$out" | grep -qE "\b$op:" || missing="$missing $op"
	done
	[ -z "$missing" ] && ok "all 11 operation counters present" \
		|| ko "missing counters:$missing"

	# the counters must agree with what actually went to stdout
	local emitted reported
	emitted=$("$PROG" --bench $args 2>/dev/null | wc -l | tr -d ' ')
	reported=$("$PROG" --bench $args 2>&1 >/dev/null | grep total_ops | grep -oE '[0-9]+$')
	if [ "$emitted" = "$reported" ]; then
		ok "total_ops ($reported) matches emitted lines"
	else
		ko "counter drift" "stdout lines: $emitted, total_ops: $reported"
	fi

	# forced strategies must be named correctly
	for s in simple medium complex; do
		"$PROG" --$s --bench $args 2>&1 >/dev/null | grep -qiE "strategy:.*$s" \
			&& ok "--$s reported as $s" || ko "--$s reported under a different name"
	done

	# disorder is measured before any move: sorted input must read 0.00%
	"$PROG" --bench 1 2 3 4 5 2>&1 >/dev/null | grep -q '0.00%' \
		&& ok "sorted input reports 0.00% disorder" || ko "disorder wrong on sorted input"
	# fully reversed must read 100.00%
	"$PROG" --bench 5 4 3 2 1 2>&1 >/dev/null | grep -q '100.00%' \
		&& ok "reversed input reports 100.00% disorder" || ko "disorder wrong on reversed input"
}

# -----------------------------------------------------------------------------
# 6. LEAKS
# -----------------------------------------------------------------------------
test_leaks()
{
	hdr "MEMORY (valgrind)"

	if ! command -v valgrind > /dev/null 2>&1; then
		skip "valgrind not installed"
		return
	fi

	# vg_case <description> <args...>
	vg_case()
	{
		local desc="$1"; shift
		valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=42 \
			"$PROG" "$@" > /dev/null 2> /tmp/ps_vg
		if [ $? -eq 42 ] || grep -qE 'definitely lost: [1-9]|indirectly lost: [1-9]|Invalid (read|write)' /tmp/ps_vg; then
			ko "$desc" "$(grep -E 'lost:|Invalid' /tmp/ps_vg | head -3)"
		else
			ok "$desc"
		fi
	}

	vg_case "sorting path"            --simple $(rnd 100)
	vg_case "sorting path (radix)"    --complex $(rnd 100)
	vg_case "sorting path (chunks)"   --medium $(rnd 100)
	vg_case "already sorted"          1 2 3 4 5
	vg_case "no arguments"
	vg_case "error mid-parse"         3 2 one 5
	vg_case "error: duplicate"        3 2 1 2
	vg_case "error: overflow"         1 2 2147483648
	vg_case "error: bad flag"         --turbo 3 2 1
	vg_case "error inside a string"   "3 2 one 5"
	vg_case "bench path"              --bench $(rnd 50)
}

# -----------------------------------------------------------------------------
# 7. PERFORMANCE  (subject p.17)
# -----------------------------------------------------------------------------
grade()
{
	local ops=$1 pass=$2 good=$3 exc=$4
	if   [ "$ops" -lt "$exc"  ]; then echo -e "${GRN}EXCELLENT${NC}";
	elif [ "$ops" -lt "$good" ]; then echo -e "${GRN}good${NC}";
	elif [ "$ops" -lt "$pass" ]; then echo -e "${YEL}pass${NC}";
	else                              echo -e "${RED}FAIL${NC}"; fi
}

test_perf()
{
	hdr "PERFORMANCE (default --adaptive)"

	local reps=5

	perf_at()
	{
		local n=$1 pass=$2 good=$3 exc=$4
		local worst=0 total=0 ops args i
		for ((i=0; i<reps; i++)); do
			args=$(rnd $n)
			ops=$("$PROG" $args 2>/dev/null | wc -l | tr -d ' ')
			total=$((total+ops))
			[ "$ops" -gt "$worst" ] && worst=$ops
		done
		local avg=$((total/reps))
		printf "  n=%-4s avg=%-7s worst=%-7s  →  %b   (targets: <%s / <%s / <%s)\n" \
			"$n" "$avg" "$worst" "$(grade $worst $pass $good $exc)" "$pass" "$good" "$exc"
		if [ "$worst" -lt "$pass" ]; then PASS=$((PASS+1)); else FAIL=$((FAIL+1)); fi
	}

	echo "  ($reps runs each; graded on the worst run)"
	perf_at 100 2000  1500 700
	perf_at 500 12000 8000 5500

	hdr "PER-STRATEGY COMPARISON (same input)"
	local args
	args=$(rnd 500)
	printf "  %-10s %s\n" "strategy" "operations for n=500"
	for s in simple medium complex adaptive; do
		printf "  %-10s %s\n" "--$s" "$("$PROG" --$s $args 2>/dev/null | wc -l | tr -d ' ')"
	done
	echo "  (simple is an order of magnitude worse; medium may beat complex on random"
	echo "   input despite the weaker class — O() bounds growth, not the constant)"
}

# -----------------------------------------------------------------------------
# 8. COMPLEXITY PROOF
#
#  A complexity class shows up as a ratio that stops moving. Divide the measured
#  operation count by each candidate function; the one that flattens is the real
#  class. The doubling factor is the same evidence read differently: doubling n
#  multiplies operations by ~4 for n², ~2.83 for n·sqrt(n), ~2.1 for n·log n.
# -----------------------------------------------------------------------------
measure()
{
	local strat=$1 n=$2 reps=$3
	local total=0 i args
	for ((i=0; i<reps; i++)); do
		args=$(rnd $n)
		total=$((total + $("$PROG" --$strat $args 2>/dev/null | wc -l | tr -d ' ')))
	done
	echo $((total/reps))
}

analyse()
{
	local strat=$1 expected=$2; shift 2
	local sizes=("$@")
	local reps=5 prev_n=0 prev_ops=0

	echo -e "\n  ${BLU}--$strat${NC}   expected ${YEL}$expected${NC}"
	printf "  %6s %9s %11s %11s %11s %9s\n" \
		"n" "ops" "ops/n^2" "ops/n^1.5" "ops/nlog2n" "growth"
	printf "  %s\n" "------------------------------------------------------------------"

	for n in "${sizes[@]}"; do
		local ops r2 r15 rlog growth
		ops=$(measure "$strat" "$n" "$reps")
		r2=$(echo   "scale=4; $ops/($n*$n)"                | bc -l)
		r15=$(echo  "scale=4; $ops/($n*sqrt($n))"          | bc -l)
		rlog=$(echo "scale=4; $ops/($n*(l($n)/l(2)))"      | bc -l)
		if [ "$prev_ops" -gt 0 ]; then
			growth=$(echo "scale=2; $ops/$prev_ops" | bc -l)
		else
			growth="  -"
		fi
		printf "  %6s %9s %11s %11s %11s %9s\n" "$n" "$ops" "$r2" "$r15" "$rlog" "$growth"
		prev_n=$n; prev_ops=$ops
	done
}

test_complexity()
{
	hdr "COMPLEXITY — EMPIRICAL PROOF"
	echo "  Read down each ratio column: the one that stays flat is the true class."
	echo "  Growth is ops(2n)/ops(n) — expect ~4.0 for n^2, ~2.83 for n^1.5, ~2.1 for n*log n."

	analyse simple   "O(n^2)"      25 50 100 200 400 500 1000
	analyse medium   "O(n*sqrt n)" 25 50 100 200 400 500 1000
	analyse complex  "O(n*log n)"  25 50 100 200 400 500 1000

	hdr "ADAPTIVE — REGIME SELECTION"
	echo "  Disorder decides the method; the reported class must follow the thresholds."
	printf "  %-26s %-12s %s\n" "input" "disorder" "strategy reported"

	adaptive_case()
	{
		local label="$1"; shift
		local out
		out=$("$PROG" --bench --adaptive "$@" 2>&1 >/dev/null)
		printf "  %-26s %-12s %s\n" "$label" \
			"$(echo "$out" | grep disorder | grep -oE '[0-9.]+%')" \
			"$(echo "$out" | grep strategy | sed 's/.*strategy: *//')"
	}

	adaptive_case "sorted but for one swap" 2 1 $(seq 3 60 | tr '\n' ' ')
	adaptive_case "lightly shuffled"        $(seq 1 30 | tr '\n' ' ') $(shuf -i 31-60 -n 30 | tr '\n' ' ')
	adaptive_case "fully random n=100"      $(rnd 100)
	adaptive_case "fully reversed n=100"    $(seq 100 -1 1 | tr '\n' ' ')
	echo "  (expected: <0.2 → O(n^2), 0.2-0.5 → O(n*sqrt(n)), >=0.5 → O(n*log(n)))"

	hdr "ADAPTIVE PAYS OFF ON STRUCTURE"
	local nearly
	nearly="2 1 $(seq 3 100 | tr '\n' ' ')"
	printf "  %-12s %s\n" "strategy" "ops on a nearly-sorted n=100"
	for s in simple medium complex adaptive; do
		printf "  %-12s %s\n" "--$s" "$("$PROG" --$s $nearly 2>/dev/null | wc -l | tr -d ' ')"
	done
}

# -----------------------------------------------------------------------------
# main
# -----------------------------------------------------------------------------
command -v bc > /dev/null 2>&1 || { echo "bc is required (apt install bc)"; exit 1; }
command -v shuf > /dev/null 2>&1 || { echo "shuf is required (GNU coreutils)"; exit 1; }

case "${1:-default}" in
	basic)      test_build; test_errors; test_output ;;
	correct)    test_correct ;;
	bench)      test_bench ;;
	leaks)      test_leaks ;;
	perf)       test_perf ;;
	complexity) test_complexity ;;
	all)        test_build; test_errors; test_output; test_correct
	            test_bench; test_leaks; test_perf; test_complexity ;;
	default)    test_build; test_errors; test_output; test_correct
	            test_bench; test_perf; test_complexity ;;
	*)          echo "usage: $0 [basic|correct|bench|leaks|perf|complexity|all]"; exit 1 ;;
esac

echo ""
echo "============================================================"
echo -e " passed: ${GRN}$PASS${NC}    failed: ${RED}$FAIL${NC}"
echo "============================================================"
[ "$FAIL" -eq 0 ] && exit 0 || exit 1