### Functions

#### Name

All functions in this library will start with ``sea_turtle_``. 

Functions that get and set values must contain ``get`` or ``set`` in 
their name unless you can only get a value then the prefix is omitted.

#### Return Types

If there is no possibility of failure then the function must have a
``void`` return type.

```c
void sea_turtle_required(const void *object);
```

If the function can fail then the return type must be a ``bool`` where 
``true`` means that the function completed without error and ``false`` 
otherwise.

```c
bool sea_turtle_add_size_t(const size_t a, const size_t b, size_t *out)
```

There are a few exceptions to this rule where already established 
conventions makes more sense for example when an ``int`` return type is 
used for comparison functions.

```c
int memcmp(const void *s1, const void *s2, size_t n);
```

#### Errors

Errors are reported by setting the ``sea_turtle_error`` to the correct error value 
and then returning ``false``.

```c
bool sea_turtle_add_size_t(const size_t a, const size_t b, size_t *out) {
    if (!out) {
        sea_turtle_error = SEA_TURTLE_ERROR_OUT_IS_NULL;
        return false;
    }
    ...
```

It is always preferred to have domain specific error codes than a generic 
one.

```c
// preferred a domain specific error
#define SEA_TURTLE_RED_BLACK_TREE_ERROR_OUT_IS_NULL   2

// generic error
#define SEA_TURTLE_ERROR_OUT_IS_NULL                  1
```

