# Project Overview and API Documentation

## What This Project Does

This is a **legacy C codebase** that implements a collection of utility libraries for:

1. **Mathematical operations** on integer arrays (sum, average, max, sorting, median)
2. **Text manipulation** (whitespace normalization, case conversion, string replacement)
3. **Configuration file parsing** (key=value format with comments)
4. **Linked list data structure** for integers with full CRUD operations
5. **String utilities** (split, join, parsing, formatting, substring operations)
6. **Protocol message handling** for three device protocols (Apple, Banana, Carrot)
7. **Logging system** with configurable severity levels

The project demonstrates a typical embedded systems or IoT device communication stack where:
- Devices send protocol messages with version, device ID, temperature, and active status
- Messages are serialized to/from binary format for network transmission
- Configuration files control application behavior
- Various utility functions process and manipulate data

---

## Project Architecture

### Module Organization

```
src/legacy/
├── metrics.c          # Array statistics and operations
├── text.c             # Text transformation functions
├── config.c           # Configuration file parser
├── list.c             # Linked list implementation
├── string_utils.c     # String manipulation utilities
├── protocol.c         # Generic protocol implementation
├── protocol_apple.c   # Apple protocol wrapper
├── protocol_banana.c  # Banana protocol wrapper
└── protocol_carrot.c  # Carrot protocol wrapper

src/
├── logger.c           # Logging system
└── main.c             # Demonstration program
```

### Protocol Architecture

The three protocol modules (Apple, Banana, Carrot) are **nearly identical** - they all use the same underlying generic protocol (`protocol.c`) but provide separate APIs for type safety and future extensibility.

---

## API Documentation

### 1. Metrics Module (`metrics.h`)

**Purpose:** Mathematical operations and statistics on integer arrays.

#### Functions

**`long metrics_sum(const int* arr, size_t n)`**
- Computes the sum of all integers in an array
- Returns 0 if `arr` is NULL
- Time complexity: O(n)

**`int metrics_average(const int* arr, size_t n)`**
- Computes the average (integer division, truncated)
- Returns 0 if `arr` is NULL or `n` is 0
- Time complexity: O(n)

**`int metrics_argmax(const int* arr, size_t n)`**
- Finds the index of the maximum element
- Returns -1 if `arr` is NULL or `n` is 0
- If multiple elements have the max value, returns the first occurrence
- Time complexity: O(n)

**`void metrics_sort(int* arr, size_t n)`**
- Sorts array in-place using bubble sort with early termination
- Modifies the array in-place
- Safe to call with NULL pointer (no-op)
- Time complexity: O(n²) worst case, O(n) best case

**`int metrics_median(int* arr, size_t n)`**
- Computes the median value
- For even-length arrays: returns lower median (element at index (n/2)-1)
- For odd-length arrays: returns middle element (element at index n/2)
- **Side effect:** Sorts the array in-place
- Returns 0 if `arr` is NULL or `n` is 0
- Time complexity: O(n²) due to sorting

---

### 2. Text Module (`text.h`)

**Purpose:** Text transformation and manipulation functions.

#### Functions

**`size_t text_normalize_whitespace(char* s)`**
- Collapses sequences of whitespace into single spaces
- Trims leading/trailing whitespace
- Modifies string in-place
- Returns new length, or 0 if `s` is NULL
- Time complexity: O(n)

**`char* text_to_upper(const char* s)`**
- Creates an uppercased copy of a string
- Caller must free the returned string
- Returns NULL if `s` is NULL or allocation fails
- Time complexity: O(n)

**`char* text_replace_all(const char* s, const char* from, const char* to)`**
- Replaces all occurrences of `from` with `to`
- Returns newly allocated string (caller must free)
- Returns NULL if `s` is NULL or allocation fails
- If `from` is NULL or empty, returns a copy of `s`
- Has safety limit of 1000 iterations to prevent infinite loops
- Time complexity: O(n*m) where n is string length, m is number of replacements

---

### 3. Config Module (`config.h`)

**Purpose:** Parse simple key=value configuration files.

#### Data Structure

```c
typedef struct {
    int port;           // Port number (default: 80)
    bool enable_tls;    // TLS/SSL enabled (default: false)
    char host[128];     // Hostname or IP (default: "localhost")
} app_config;
```

#### Functions

**`bool config_parse_file(const char* path, app_config* out_cfg)`**
- Parses a configuration file in key=value format
- Supports comments (lines starting with '#')
- Trims whitespace around '=' and values
- Keys: "port", "enable_tls", "host" (case-insensitive)
- Values:
  - `port`: Integer (parsed with `atoi`)
  - `enable_tls`: Boolean (true/false, TRUE/FALSE, 1/0, case-insensitive)
  - `host`: String (max 127 characters)
- Sets default values before parsing
- Returns false if `path` or `out_cfg` is NULL, or file cannot be opened

**Example Config File:**
```
# This is a comment
host = example.com
port=8080
enable_tls=true
```

---

### 4. List Module (`list.h`)

**Purpose:** Singly-linked list data structure for integers.

#### Data Structures

```c
typedef struct list_node {
    int data;
    struct list_node* next;
} list_node;

typedef struct {
    list_node* head;   // Pointer to first node, NULL if empty
    size_t size;       // Number of elements
} int_list;
```

#### Functions

**`int_list* list_create(void)`**
- Creates a new empty linked list
- Returns NULL on allocation failure
- Caller must destroy with `list_destroy()`

**`void list_destroy(int_list* list)`**
- Frees all nodes and the list structure
- Safe to call with NULL pointer (no-op)

**`void list_append(int_list* list, int value)`**
- Appends a value to the end of the list
- Time complexity: O(n) where n is list size
- Safe to call with NULL pointer (no-op)

**`void list_insert(int_list* list, size_t index, int value)`**
- Inserts a value at a specific index (0-based)
- If index >= size, appends to the end
- Time complexity: O(n) where n is index
- Safe to call with NULL pointer (no-op)

**`int list_remove_at(int_list* list, size_t index)`**
- Removes and returns the value at a specific index
- Returns 0 if list is NULL, empty, or index is invalid
- Time complexity: O(n) where n is index

**`int list_get(const int_list* list, size_t index)`**
- Gets the value at a specific index without removing it
- Returns 0 if list is NULL, empty, or index is invalid
- Does not modify the list
- Time complexity: O(n) where n is index

**`int list_find(const int_list* list, int value)`**
- Finds the first index of a value
- Returns index (0-based) or -1 if not found
- Returns -1 if list is NULL
- Time complexity: O(n)

**`void list_reverse(int_list* list)`**
- Reverses the list in-place
- Safe to call with NULL pointer or empty list (no-op)
- Time complexity: O(n)

**`void list_sort(int_list* list)`**
- Sorts the list in-place using bubble sort
- Safe to call with NULL pointer or empty/single-element list (no-op)
- Time complexity: O(n²)

**`int_list* list_merge_sorted(const int_list* a, const int_list* b)`**
- Merges two sorted lists into a new sorted list
- Both input lists must be sorted (ascending)
- Returns NULL if either list is NULL or allocation fails
- Caller must destroy the returned list
- Original lists are not modified
- Time complexity: O(n+m)

---

### 5. String Utils Module (`string_utils.h`)

**Purpose:** Comprehensive string manipulation and utility functions.

#### Functions

**`char** string_split(const char* str, char delimiter, size_t* count)`**
- Splits a string into tokens by delimiter
- Returns NULL-terminated array of strings
- Caller must free each token string AND the array itself
- Sets `*count` to number of tokens
- Returns NULL if `str` or `count` is NULL
- Time complexity: O(n)

**`char* string_join(const char* const* strings, size_t count, char delimiter)`**
- Joins an array of strings with a delimiter
- Returns newly allocated string (caller must free)
- Returns empty string if count is 0
- Returns NULL if `strings` is NULL or contains NULL elements
- Time complexity: O(n) where n is total length of all strings

**`void string_remove_chars(char* str, const char* chars)`**
- Removes specified characters from a string in-place
- Modifies the string in-place
- Safe to call with NULL pointers (no-op)
- Time complexity: O(n*m) where n is str length, m is chars length

**`bool string_starts_with(const char* str, const char* prefix)`**
- Checks if a string starts with a prefix
- Returns true if prefix is empty string
- Returns false if `str` or `prefix` is NULL
- Time complexity: O(min(n, m))

**`bool string_ends_with(const char* str, const char* suffix)`**
- Checks if a string ends with a suffix
- Returns true if suffix is empty string
- Returns false if `str` or `suffix` is NULL, or if suffix is longer than str
- Time complexity: O(min(n, m))

**`bool string_parse_int(const char* str, int* out_value)`**
- Parses an integer from a string
- Supports optional leading '+' or '-' sign
- Returns false if `str` is NULL, empty, or contains non-digit characters
- Returns false if value is out of INT_MIN..INT_MAX range
- Time complexity: O(n)

**`int string_format_int(char* buffer, size_t buffer_size, int value)`**
- Formats an integer to a string buffer
- Returns number of characters written, or -1 on error
- Returns -1 if `buffer` is NULL, `buffer_size` is 0, or buffer is too small
- Time complexity: O(log10(value))

**`void string_remove_duplicates(char* str)`**
- Removes duplicate characters from a string in-place
- Keeps only the first occurrence of each character
- Preserves order of first occurrences
- Safe to call with NULL pointer (no-op)
- Time complexity: O(n²)

**`size_t string_count_substring(const char* str, const char* substring)`**
- Counts occurrences of a substring in a string
- Returns 0 if `str` or `substring` is NULL, or if substring is empty
- Counts non-overlapping matches only
- Time complexity: O(n*m)

---

### 6. Protocol Modules

**Purpose:** Serialize, parse, validate, and compute checksums for device protocol messages.

#### Protocol Format

All three protocols (Apple, Banana, Carrot) use the **same binary format**:

```
Offset  Size    Field         Format
------  ----    -----         ------
0       4       Version       4 hex digits (0-65535)
4       64      Device ID     Up to 63 chars, null-padded to 64 bytes
68      8       Temperature   8 hex digits (signed integer, -1000 to 1000)
76      1       Active        '0' or '1'
```

**Total message size:** 77 bytes minimum

**Example serialized message:**
```
0001APPLE_DEVICE_001\0...\00000000FA1
```
- Version: `0001` (hex) = 1
- Device ID: `APPLE_DEVICE_001` (padded with nulls to 64 bytes)
- Temperature: `000000FA` (hex) = 250
- Active: `1`

#### Data Structure

All three protocols use the same structure (with different type names):

```c
typedef struct {
    int version;           // Protocol version (0-65535)
    char device_id[64];     // Device identifier (null-terminated, max 63 chars)
    int temperature;        // Temperature value (-1000 to 1000)
    bool active;           // Active status flag
} apple_message;  // or banana_message, carrot_message
```

#### Generic Protocol API (`protocol.h`)

**`bool gen_parse(const char* buffer, size_t buffer_len, gen_message* out)`**
- Parses a protocol message from a buffer
- Returns false if `buffer` is NULL, `out` is NULL, or `buffer_len < 77`
- Returns false if version is out of range (0-65535)
- Returns false if temperature parsing fails
- Returns false if active flag is not '0' or '1'
- Device ID is copied up to 63 characters or until null/pipe character

**`int gen_serialize(const gen_message* msg, char* buffer, size_t buffer_size)`**
- Serializes a protocol message to a buffer
- Returns number of bytes written, or -1 on error
- Returns -1 if `msg` is NULL, `buffer` is NULL, or `buffer_size < 77`
- Version is formatted as 4 uppercase hex digits
- Device ID is padded to 64 bytes with nulls
- Temperature is formatted as 8 uppercase hex digits
- Active is written as '1' or '0'

**`bool gen_validate(const gen_message* msg)`**
- Validates a protocol message
- Returns false if `msg` is NULL
- Validates version is in range 0-65535
- Validates device_id is non-empty
- Validates device_id contains only printable ASCII (32-126)
- Validates temperature is in range -1000 to 1000

**`unsigned int gen_checksum(const gen_message* msg)`**
- Computes a checksum for a protocol message
- Checksum = version + temperature + active (0 or 1) + sum of device_id bytes
- Returns 0 if `msg` is NULL

#### Protocol-Specific APIs

Each protocol (Apple, Banana, Carrot) provides wrapper functions that convert to/from the generic protocol:

- `bool apple_parse(const char* buffer, size_t buffer_len, apple_message* out)`
- `int apple_serialize(const apple_message* msg, char* buffer, size_t buffer_size)`
- `bool apple_validate(const apple_message* msg)`
- `unsigned int apple_checksum(const apple_message* msg)`

(Same pattern for `banana_*` and `carrot_*` functions)

**Note:** The three protocol modules are **nearly identical** - they all delegate to the generic protocol functions.

---

### 7. Logger Module (`logger.h`)

**Purpose:** Logging system with configurable severity levels.

#### Log Levels

```c
typedef enum {
    LOG_NONE = 0,   // No logging
    LOG_ERROR = 1,  // Error messages only
    LOG_WARN = 2,   // Warnings and errors
    LOG_INFO = 3,   // Informational messages, warnings, and errors
    LOG_DEBUG = 4   // All messages including debug
} log_level_t;
```

#### Functions

**`void logger_init(void)`**
- Initializes the logger system
- Reads `LOG_LEVEL` environment variable (case-insensitive: NONE, ERROR, WARN, INFO, DEBUG)
- Defaults to `LOG_WARN` if not set or invalid
- Should be called once at program startup

**`void logger_set_level(log_level_t level)`**
- Sets the log level programmatically
- Overrides environment variable setting
- Only sets level if it's in valid range

**`log_level_t logger_get_level(void)`**
- Gets the current log level

**`void log_error(const char* format, ...)`**
- Logs an error message (printf-style format)
- Only logs if current level >= LOG_ERROR
- Output format: `[ERROR] <message>\n`

**`void log_warn(const char* format, ...)`**
- Logs a warning message
- Only logs if current level >= LOG_WARN
- Output format: `[WARN] <message>\n`

**`void log_info(const char* format, ...)`**
- Logs an informational message
- Only logs if current level >= LOG_INFO
- Output format: `[INFO] <message>\n`

**`void log_debug(const char* format, ...)`**
- Logs a debug message
- Only logs if current level >= LOG_DEBUG
- Output format: `[DEBUG] <message>\n`

**Usage Example:**
```c
logger_init();  // Reads LOG_LEVEL from environment
log_info("Server started on port %d", port);
log_debug("Processing item %d of %d", current, total);
```

---

## Common Patterns and Conventions

### Error Handling

- Most functions return `false` (or -1 for integers) on error
- Functions that return pointers return NULL on error
- Functions that modify in-place are safe to call with NULL (no-op)

### Memory Management

- Functions that return allocated memory require the caller to free it
- Functions that modify strings in-place require a modifiable buffer
- List operations require proper cleanup with `list_destroy()`

---

## Usage Example

```c
#include "protocol_apple.h"
#include "logger.h"
#include "metrics.h"

int main() {
    // Initialize logger
    logger_init();
    
    // Parse a protocol message
    apple_message msg;
    char buffer[128] = "0001APPLE_DEVICE_001\0...\00000000FA1";
    if (apple_parse(buffer, 77, &msg)) {
        log_info("Parsed message: device=%s, temp=%d", 
                 msg.device_id, msg.temperature);
        
        // Validate message
        if (apple_validate(&msg)) {
            log_info("Message is valid");
        }
    }
    
    // Compute array statistics
    int arr[] = {1, 2, 3, 4, 5};
    long sum = metrics_sum(arr, 5);
    int avg = metrics_average(arr, 5);
    log_info("Sum: %ld, Average: %d", sum, avg);
    
    return 0;
}
```

---

## Build and Test

See `README.md` for build instructions. The project uses CMake and provides a Makefile for convenience.

**Quick Start:**
```bash
cd refactor/_student
make test
```

---

## Summary

This project implements a collection of utility libraries for a device communication system. The modules provide functionality for mathematical operations, text manipulation, configuration parsing, data structures, string utilities, protocol message handling, and logging.
