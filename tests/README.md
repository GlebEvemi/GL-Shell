# Unit Tests for GL-Shell

This directory contains unit tests for the GL-Shell project using the Check framework.

## Test Structure

### test_functions.c
Tests for shell command functions in `src/functions.c`:

**Command Handler Tests (11 tests)**
- `test_get_command_handler_*` - Tests for `getCommandHandlerByName()` function
  - Verifies correct handler is returned for each command (ls, cd, pwd, mkdir, rm, clear, pcsearch, exit)
  - Tests error cases (unknown command, null input, empty string)

**mkdir Tests (2 tests)**
- `test_mkdir_creates_directory` - Verifies directory creation
- `test_mkdir_with_null_args` - Tests null argument handling

**rm Tests (2 tests)**
- `test_rm_deletes_file` - Verifies file deletion
- `test_rm_with_null_args` - Tests null argument handling

**cd Tests (3 tests)**
- `test_cd_changes_directory` - Verifies directory change
- `test_cd_with_null_args` - Tests that directory doesn't change with null args
- `test_cd_with_invalid_path` - Tests that invalid path doesn't change directory

### test_api.c
Tests for HTTP API functions in `src/api.c`:

**getAllComputers Tests (4 tests)**
- `test_get_all_computers_invalid_url` - Tests invalid URL handling
- `test_get_all_computers_null_url` - Tests null URL handling
- `test_get_all_computers_null_username` - Tests null username handling
- `test_get_all_computers_null_password` - Tests null password handling

**getComputerByHostname Tests (4 tests)**
- `test_get_computer_by_hostname_invalid_url` - Tests invalid URL handling
- `test_get_computer_by_hostname_null_hostname` - Tests null hostname handling
- `test_get_computer_by_hostname_empty_hostname` - Tests empty hostname handling
- `test_get_computer_by_hostname_with_special_chars` - Tests URL encoding of special characters

## Building and Running Tests

### Build All Targets
```bash
cd build
cmake ..
make
```

### Run All Tests
```bash
cd build
make run_tests
```

Or directly:
```bash
cd build
ctest --verbose
```

### Run Specific Test Suite
```bash
cd build
./test_functions   # Run functions tests
./test_api         # Run API tests
```

## Test Results

All 26 tests pass successfully:
- **Functions Tests**: 18/18 ✅
- **API Tests**: 8/8 ✅

### Example Output
```
100%: Checks: 26, Failures: 0, Errors: 0
Total Test time (real) = 7.56 sec
```

## Test Coverage

The tests cover:
- ✅ Command routing and handler lookup
- ✅ File system operations (mkdir, rm, cd)
- ✅ NULL and invalid parameter handling
- ✅ API error conditions and edge cases
- ✅ URL encoding for special characters

## Adding New Tests

To add new tests:

1. Add test case in appropriate file (`test_functions.c` or `test_api.c`)
2. Follow the pattern:
   ```c
   START_TEST(test_my_new_test)
   {
       // Your test code here
       ck_assert(condition);
   }
   END_TEST
   ```
3. Add test to suite in the `*_suite()` function:
   ```c
   tcase_add_test(tc_section, test_my_new_test);
   ```
4. Rebuild and run:
   ```bash
   cd build && make && make run_tests
   ```

## Check Framework Documentation

Learn more about Check framework:
- [Check Documentation](https://libcheck.github.io/check/)
- [Check GitHub Repository](https://github.com/libcheck/check)

## Dependencies

- libcheck - C unit testing framework
- libcurl - For HTTP functions
- pkg-config - For finding libraries

Install on Ubuntu/Debian:
```bash
sudo apt-get install check pkg-config libcurl4-openssl-dev
```

Install on Fedora/RHEL:
```bash
sudo dnf install check check-devel pkgconf-pkg-config libcurl-devel
```

## Notes

- Tests use `/tmp` directory for file system tests to avoid affecting the project structure
- API tests expect connection failures (no mock server), which is expected behavior
- All fixtures properly clean up temporary files/directories
- Tests are isolated and can run in any order
