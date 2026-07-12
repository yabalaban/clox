# clox

A bytecode virtual machine for the Lox language, built while working through
[*Crafting Interpreters*](https://craftinginterpreters.com/) by Robert Nystrom
(Part III: A Bytecode Virtual Machine).

## Build

```sh
make
```

Compiles to `build/bin/app`.

## Run

```sh
make run
```

Builds (if needed) and runs the binary.

## Clean

```sh
make clean
```

Removes the `build/` directory.

## Requirements

- `clang`
- GNU Make
