*This project has been created as part of the 42 curriculum by <kwlodars@student.42warsaw.pl>*

## Description
Libft is a project dedicated to coding a custom C library that includes numerous general-purpose functions. It provides basic utilities by replicating the behavior of standard `libc` functions, alongside additional custom mechanics like linked list manipulation. This library serves as a foundational toolkit for all future C programming assignments within the 42 network.

## Instructions
### Compilation
The library compiles using the `cc` compiler with the standard flag strictness `-Wall -Wextra -Werror`. To compile the entire repository, navigate to the root directory and use:
* `make` or `make all` — Compiles all source files and generates the static library file `libft.a`.

### Cleaning and Recompilation
* `make clean` — Removes the temporary object files (`.o`) from the root directory.
* `make fclean` — Deletes the object files as well as the compiled `libft.a` library.
* `make re` — Triggers a full clean followed by a complete rebuild of the project from scratch.

## Resources
* Linux System Manual pages (accessible via the `man` command).

## Detailed Library Description
The library features three distinct, mandatory structural segments:

### 1. Standard Libc Functions
These functions follow identical prototypes and native behaviors of their corresponding system originals, using the mandatory `ft_` prefix:
* **Character Classification:** `ft_isalpha`, `ft_isdigit`, `ft_isalnum`, `ft_isascii`, `ft_isprint`.
* **Character Mutation & Conversion:** `ft_toupper`, `ft_tolower`, `ft_atoi`.
* **Memory Management:** `ft_memset`, `ft_bzero`, `ft_memcpy`, `ft_memmove`, `ft_memchr`, `ft_memcmp`, `ft_calloc`.
* **String Manipulation:** `ft_strlen`, `ft_strlcpy`, `ft_strlcat`, `ft_strchr`, `ft_strrchr`, `ft_strncmp`, `ft_strnstr`, `ft_strdup`.

### 2. Additional Functions
Custom helper utilities primarily focused on dynamic string allocations and basic file descriptor outputs:
* `ft_substr` — Extracts a substring slice from a given string index pointer.
* `ft_strjoin` — Concatenates a prefix and suffix string into a newly allocated space.
* `ft_strtrim` — Clips target character sets away from both ends of a sequence.
* `ft_split` — Subdivides a string into a dynamic array of substrings using a delimiter.
* `ft_itoa` — Formats an integer variable into its identical ascii text string form.
* `ft_strmapi` & `ft_striteri` — Map continuous modification logic across string indices via functional arguments.
* `ft_putchar_fd`, `ft_putstr_fd`, `ft_putendl_fd`, `ft_putnbr_fd` — Stream characters, text strings, or numerical formats to a defined target file descriptor.

### 3. Linked List Functions
A collection of node tools meant to build, measure, iterate, and safely destroy instances of the `t_list` struct data type:
* `ft_lstnew` — Allocates memory and setups a brand new standalone list element.
* `ft_lstadd_front` & `ft_lstadd_back` — Append a pre-configured node at the exact front or rear extremity of a structural list sequence.
* `ft_lstsize` — Counts the comprehensive volume of elements linked within a given chain.
* `ft_lstlast` — Safely tracks and references a pointer pointing to the absolute final list node.
* `ft_lstdelone` & `ft_lstclear` — Free dynamic content memory fields inside isolated nodes or down through entire sub-branches.
* `ft_lstiter` & `ft_lstmap` — Execute analytical or mutative function loops systematically on sequential list node elements.
