# Generic Dynamic Array (C Vector)

![Build](https://img.shields.io/badge/build-passing-brightgreen)
![License](https://img.shields.io/badge/license-MIT-blue)

A production-ready, **generic (`void*`)** dynamic array implementation for C. It utilizes an **Opaque Pointer** design to ensure strict encapsulation and provides a robust API for data-intensive applications.



---

## Key Features

* **Type-Agnostic:** Stores any pointer type using `void*` handles—mimicking generic behavior in C.
* **Optimal Resizing:**
    * **Geometric Growth:** $2\times$ expansion ensures $O(1)$ amortized insertion.
    * **Hysteresis Shrinking:** Contraction is delayed until capacity hits $25\%$ to prevent "thrashing" (repeated allocations during edge-case workloads).
* **Encapsulation:** The `DynArray` struct is opaque, preventing accidental corruption of internal `size` or `capacity` counters.
* **Safety Integrated:** Automatic bounds checking on `get/set` and memory zeroing via `calloc`.



---

## Performance Profile

| Operation | Complexity | Note |
| :--- | :--- | :--- |
| **Push** | $O(1)$ | Amortized constant time via $2\times$ growth. |
| **Pop / Delete** | $O(n)$ | Linear time due to required element shifting. |
| **Access (Get/Set)** | $O(1)$ | Direct index-based pointer arithmetic. |
| **Clear** | $O(1)$ | Resets size counter (does not free user items). |

---

## API Usage

```c
// 1. Create - Initialize with a starting capacity
DynArray* list = da_create(8);

// 2. Add Data - Caller retains ownership of the heap memory
User* u = malloc(sizeof(User));
u->id = 101;
da_push(list, u);

// 3. Iterate - Robust macro handles NULL elements and type casting
User* item;
da_foreach(list, User*, item) {
    printf("User ID: %d\n", item->id);
}

// 4. Cleanup - User must free items before destroying the container
da_foreach(list, User*, item) {
    free(item);
}
da_destroy(list);


## Memory Ownership Policy

Since this is a `void*` container, it follows the **Borrower Model**. Understanding the ownership lifecycle is critical to avoiding memory leaks:

1.  **Container Ownership:** The `DynArray` owns the internal `void**` buffer. When you call `da_destroy`, **only** this buffer is freed.
2.  **User Ownership:** The user (caller) owns the life-cycle of the actual data objects. You must `free()` the items yourself before destroying the array.
3.  **Transfer on Delete:** When calling `da_delete`, the pointer is returned to you. This transfers ownership back to you to either reuse or `free()` the memory.

## Development & Tooling

The project includes a robust `Makefile` with dependency tracking (`-MMD`) and integrated static analysis to ensure code quality and build reliability.



| Command | Action | Description |
| :--- | :--- | :--- |
| `make` | **Compile** | Builds the binary to `bin/app`. |
| `make run` | **Execute** | Builds and runs the application immediately. |
| `make format` | **Style** | Applies `clang-format` to all source and headers. |
| `make lint` | **Analyze** | Runs `clang-tidy` for deep static analysis. |
| `make check` | **Workflow** | Full pipeline: Format $\rightarrow$ Lint $\rightarrow$ Build. |
| `make clean` | **Reset** | Removes all `build/` and `bin/` artifacts. |
