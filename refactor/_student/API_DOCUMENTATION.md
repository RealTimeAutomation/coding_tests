# API Documentation

This directory contains the student workspace with buggy code that needs to be fixed. All header files include comprehensive API documentation.

## Module Overview

### Core Modules

#### `metrics.h` - Mathematical Operations
Provides functions for computing statistics on integer arrays:
- `metrics_sum()` - Sum of array elements
- `metrics_average()` - Average (integer division)
- `metrics_argmax()` - Index of maximum element
- `metrics_sort()` - In-place bubble sort
- `metrics_median()` - Median value (sorts array)

#### `text.h` - Text Manipulation
Functions for text transformation:
- `text_normalize_whitespace()` - Collapse whitespace sequences
- `text_to_upper()` - Create uppercased copy
- `text_replace_all()` - Replace substring occurrences

#### `string_utils.h` - String Utilities
Comprehensive string operations:
- `string_split()` - Split by delimiter
- `string_join()` - Join with delimiter
- `string_starts_with()` / `string_ends_with()` - Prefix/suffix checks
- `string_parse_int()` / `string_format_int()` - Integer conversion
- `string_remove_chars()` / `string_remove_duplicates()` - Character removal
- `string_count_substring()` - Count occurrences

#### `list.h` - Linked List
Singly-linked list for integers:
- `list_create()` / `list_destroy()` - Lifecycle
- `list_append()` / `list_insert()` - Insertion
- `list_remove_at()` / `list_get()` - Access
- `list_find()` - Search
- `list_reverse()` / `list_sort()` - Manipulation
- `list_merge_sorted()` - Merge sorted lists

#### `config.h` - Configuration Parsing
Simple key=value config file parser:
- `config_parse_file()` - Parse config file
- Supports comments (#), whitespace trimming
- Keys: port, enable_tls, host

#### `logger.h` - Logging System
Configurable logging with levels:
- `logger_init()` - Initialize (reads LOG_LEVEL env var)
- `logger_set_level()` / `logger_get_level()` - Level control
- `log_error()`, `log_warn()`, `log_info()`, `log_debug()` - Log functions

### Protocol Modules

#### `protocol_apple.h`, `protocol_banana.h`, `protocol_carrot.h`
Three protocol implementations with identical APIs:
- `*_parse()` - Parse message from buffer
- `*_serialize()` - Serialize message to buffer
- `*_validate()` - Validate message
- `*_checksum()` - Compute checksum

**Protocol Format:**
- Version: 4 hex digits (0-65535)
- Device ID: Up to 63 chars, padded to 64 bytes
- Temperature: 8 hex digits (-1000 to 1000)
- Active: 1 char ('0' or '1')
- Minimum buffer: 77 bytes

## Using the Documentation

All header files use Doxygen-style documentation with:
- `@file` - File description
- `@brief` - Function summary
- `@param` - Parameter descriptions
- `@return` - Return value description
- `@note` - Important notes
- `@example` - Usage examples

## Generating Documentation

To generate HTML documentation from the headers:

```bash
# Install Doxygen (if not installed)
# sudo apt-get install doxygen  # Linux
# brew install doxygen          # macOS

# Generate documentation
doxygen Doxyfile
```

## Reading Headers

You can view the documentation directly in the header files:
```bash
# View a header file
cat include/metrics.h

# Or use your editor/IDE
code include/metrics.h
```

## Key Documentation Features

1. **Function Signatures**: Clear parameter and return types
2. **NULL Safety**: Notes on NULL pointer handling
3. **Error Handling**: Return values and error conditions
4. **Time Complexity**: Performance characteristics
5. **Usage Examples**: Code snippets showing how to use functions
6. **Edge Cases**: Behavior with edge cases documented

## Testing

The code includes unit tests in the `tests/` directory. Run tests with:

```bash
make test
```

See `README.md` for more testing information.

