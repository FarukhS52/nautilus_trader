/* Generated with cbindgen:0.24.3 */

/* Warning, this file is autogenerated by cbindgen. Don't modify this manually. */

#include <stdint.h>
#include <Python.h>

typedef struct Arc_String Arc_String;

/**
 * `CVec` is a C compatible struct that stores an opaque pointer to a block of
 * memory, it's length and the capacity of the vector it was allocated from.
 *
 * NOTE: Changing the values here may lead to undefined behaviour when the
 * memory is dropped.
 */
typedef struct CVec {
    /**
     * Opaque pointer to block of memory storing elements to access the
     * elements cast it to the underlying type.
     */
    void *ptr;
    /**
     * The number of elements in the block.
     */
    uintptr_t len;
    /**
     * The capacity of vector from which it was allocated.
     * Used when deallocating the memory
     */
    uintptr_t cap;
} CVec;

typedef struct UUID4_t {
    struct Arc_String *value;
} UUID4_t;

void cvec_drop(struct CVec cvec);

struct CVec cvec_new(void);

/**
 * Converts seconds to nanoseconds (ns).
 */
uint64_t secs_to_nanos(double secs);

/**
 * Converts seconds to milliseconds (ms).
 */
uint64_t secs_to_millis(double secs);

/**
 * Converts milliseconds (ms) to nanoseconds (ns).
 */
uint64_t millis_to_nanos(double millis);

/**
 * Converts microseconds (μs) to nanoseconds (ns).
 */
uint64_t micros_to_nanos(double micros);

/**
 * Converts nanoseconds (ns) to seconds.
 */
double nanos_to_secs(uint64_t nanos);

/**
 * Converts nanoseconds (ns) to milliseconds (ms).
 */
uint64_t nanos_to_millis(uint64_t nanos);

/**
 * Converts nanoseconds (ns) to microseconds (μs).
 */
uint64_t nanos_to_micros(uint64_t nanos);

/**
 * Return the decimal precision inferred from the given C string.
 *
 * # Safety
 *
 * - Assumes `ptr` is a valid C string pointer.
 *
 * # Panics
 *
 * - If `ptr` is null.
 */
uint8_t precision_from_cstr(const char *ptr);

/**
 * Drops the C string memory at the pointer.
 *
 * # Safety
 *
 * - Assumes `ptr` is a valid C string pointer.
 *
 * # Panics
 *
 * - If `ptr` is null.
 */
void cstr_drop(const char *ptr);

/**
 * Returns the current seconds since the UNIX epoch.
 */
double unix_timestamp(void);

/**
 * Returns the current milliseconds since the UNIX epoch.
 */
uint64_t unix_timestamp_ms(void);

/**
 * Returns the current microseconds since the UNIX epoch.
 */
uint64_t unix_timestamp_us(void);

/**
 * Returns the current nanoseconds since the UNIX epoch.
 */
uint64_t unix_timestamp_ns(void);

struct UUID4_t uuid4_new(void);

struct UUID4_t uuid4_clone(const struct UUID4_t *uuid4);

void uuid4_drop(struct UUID4_t uuid4);

/**
 * Returns a [`UUID4`] from C string pointer.
 *
 * # Safety
 *
 * - Assumes `ptr` is a valid C string pointer.
 *
 * # Panics
 *
 * - If `ptr` cannot be cast to a valid C string.
 */
struct UUID4_t uuid4_from_cstr(const char *ptr);

const char *uuid4_to_cstr(const struct UUID4_t *uuid);

uint8_t uuid4_eq(const struct UUID4_t *lhs, const struct UUID4_t *rhs);

uint64_t uuid4_hash(const struct UUID4_t *uuid);
