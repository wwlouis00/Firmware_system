
````markdown
# Interactive Command-Based Test Application

## Overview

This project is an **interactive command-based test application** written in C. It provides a simple command-line interface to execute various test modules, perform mathematical operations, and display build/version information. It is suitable for both desktop and embedded environments.

---

## Features

- Run test modules
- Perform basic math operations (`add`, `multiply`)
- Display build and version information
- Interactive command-line interface
- Help command to list available commands
- Supports both desktop and embedded builds

---

## Build Information

- **Author:** Louis Wang  
- **Date:** 2025-11-21  
- **Versioning:** Configured via `version.h`  
- **Embedded / Desktop Mode:** Controlled by `EMBEDDED` and `EMBEDDED_TEST` macros

---

## Commands

| Command | Description |
|---------|-------------|
| `.TEST` | Run all test modules |
| `.MATH` | Perform math operations: `.MATH a b` |
| `.INFO` | Print build and version information |
| `.HELP` | Show this help message |
| `.EXIT` | Exit the program |

---

## Usage

### Desktop Mode

1. Compile the program:

```bash
gcc -o test_app main.c math_utils.c
````

2. Run the program:

```bash
./test_app
```

3. Type commands at the prompt:

```text
> .HELP
> .INFO
> .MATH 2 3
> .TEST
> .EXIT
```

### Embedded Mode

* Define `EMBEDDED` in your build system.
* The program will run the `SwitchTest()` function in an infinite loop for embedded testing.

---

## Example Output

```
[BUILD INFO] Nov 21 2025 14:55:00
[VERSION]    PROJECT001_V001

=== Command Test System Ready ===
Type .HELP for available commands.

> .MATH 5 7
add(5, 7) = 12
multiply(5, 7) = 35

> .TEST
Executing test_module_name()...
[PASS] add(2, 3) == 5

> .EXIT
Exiting...
```

---

## Test Modules

* `test_module_name()`: Validates the `add()` function from `math_utils.c`.
* `SwitchTest()`: Tests switch-case execution in a loop (embedded-specific).

---

## Dependencies

* Standard C library (`stdio.h`, `stdlib.h`, `string.h`)
* Custom headers:

  * `math_utils.h` – provides `add()` and `multiply()`
  * `version.h` – defines project version macros
  * `define.h` – defines macros like `EMBEDDED`, `EMBEDDED_TEST`

---

## Notes

* Maximum command length: 64 characters
* Maximum arguments: 4
* Maximum command name length: 16 characters

---

## Author
Louis Wang

