*This project has been created as part of the 42 curriculum by kwlodars and pkruszyn*

# Push_swap
 
## Description
 

## Instructions
 
### Build
 
```bash
make        # builds push_swap.a in the root of the repository
make clean  # removes .o files
make fclean # removes .o files and push_swap.a
make re     # fclean + all
```
 
### Use in your own project
 
```bash
cc your_file.c -I/path/to/libft -L/path/to/libft -lft -o your_program
```
 
Make sure `libft.h` is reachable via `-I` and `libft.a` via `-L`.
 
```c
#include "libft.h"
```
 
## Resources
 
- The [Linux man-pages project](https://man7.org/linux/man-pages/) — used to look
  up exact prototypes and behaviors for every Part 1 function (`man 3 <function>`).
- [cppreference.com](https://en.cppreference.com/w/c) — C standard library reference,
  used to double check edge-case behaviors (e.g. `strlcpy` return value, `calloc`
  overflow handling).
- 42 Libft subject PDF — the source of truth for prototypes, return values, and
  the `t_list` structure.

### AI usage
 
An AI assistant (Claude) was used to assist in:
- Structuring and formatting this README.md document.
- Help design test cases.

All function logic was written and typed by hand; the AI's role was limited to explanation, code review, and test-case suggestions.
 
## Library content
 
 
### Part 1 
 
### Part 2 

## License

This project is provided as open‑source under the terms of the [MIT License](https://opensource.org/licenses/MIT). Feel free to use, modify, and distribute it in your own projects.

---