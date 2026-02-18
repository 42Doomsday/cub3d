# Copilot Instructions for C Code (42 / Norminette)

## Repository Overview
This repository contains C code implementing functionality described in `subject.pdf`.
- Language: C (C99 or C11)
- Project type: Command-line programs / libraries
- Main source: `src/`
- Header files: `include/`
- Tests: `tests/`
- Build scripts: `Makefile` or `scripts/`

## Validation Steps
Before submitting any code, **always** ensure:
1. **Style & standards:** Code strictly follows 42 School rules and passes Norminette.
2. **Lint / Format:** Run `norminette src/ include/` to check compliance.
3. **Static analysis:** Use `clang-tidy` or `cppcheck` to detect potential errors.
4. **Build:** Run `make clean && make` to catch compilation errors.
5. **Tests:** Execute all unit and integration tests (`make test` or `./run_tests.sh`) and verify they pass.
6. **Safety checks:** Look for uninitialized variables, memory leaks, buffer overflows, or unsafe operations.

## Build & Test Commands
- **Setup:** Install required dependencies (gcc/clang, make, libraries).
- **Build:** `make clean && make`
- **Test:** `make test` or `./run_tests.sh`
- **Norminette:** `norminette src/ include/`
- **Static analysis:** `cppcheck --enable=all src/ include/`

## Notes for Copilot
- **Trust these instructions first.** Only explore the repo if instructions are incomplete.
- Focus on writing **correct, safe, and style-compliant C code** according to 42 School rules and Norminette.
- Validate every change against `subject.pdf`, Norminette, build, and tests before proposing changes.
