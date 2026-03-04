# SHA-1 Implementation

A SHA-1 hash implementation in C, following [RFC 3174](https://www.rfc-editor.org/rfc/rfc3174).

## Project Structure
```
.
├── src/
│   ├── sha1.c / sha1.h       # SHA-1 core implementation
│   ├── file_io.c / file_io.h # File reading utilities
│   └── main.c                # CLI entry point
├── tests/
│   ├── test_sha1.c           # Test suite
│   └── inputs/               # Input files for make check
│       ├── abc.txt
│       └── hello.txt
└── Makefile
```

## Building

**Build the main tool:**
```bash
make
```
This produces `build/my_sha1`.

**Build the test runner:**
```bash
make build/tests
```

**Clean build artifacts:**
```bash
make clean
```

## Usage

The tool takes a file as input and prints its SHA-1 hash:
```bash
./build/my_sha1 <filename>
```

**Example:**
```bash
./build/my_sha1 ./tests/inputs/hello.txt
# Output: aaf4c61ddcc5e8a2dabede0f3b482cd9aea9434d ./tests/inputs/hello.txt
```

The output format is `<sha1_hex> <filename>`, matching the style of standard tools like `sha1sum`.

## Running Tests
```bash
make run_tests
```

This builds and runs the test suite in `build/tests`.

**Verify file hashing against the system SHA-1 tool (Linux):**
```bash
make check
```

Test input files should be created without a trailing newline:
```bash
echo -n "hello" > tests/inputs/hello.txt
echo -n "abc"   > tests/inputs/abc.txt
```
