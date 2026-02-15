# Generic Dynamic Array (C Vector)

![Build](https://img.shields.io/badge/build-passing-brightgreen)
![License](https://img.shields.io/badge/license-MIT-blue)

---

A production-ready, **generic (`void*`)** dynamic array implementation designed for high-performance C applications.

## Key Features

* **Generic Storage:** Capable of storing any pointer type using `void*`.
* **Smart Resizing:** * **Geometric Growth:** $2\times$ expansion to maintain $O(1)$ amortized insertion.
    * **Hysteresis Shrinking:** $0.5\times$ reduction to prevent "thrashing" during frequent add/remove cycles.
* **Safety First:** Integrated bounds checking and safe memory zeroing.
* **Developer Tooling:** Pre-configured integration for **Linting** and **Auto-formatting**.



---

## API Usage

```c
// 1. Create - Initialize with a starting capacity
DynArray* list = da_create(8);

// 2. Add Data - Dynamically scales as needed
User* u = malloc(sizeof(User));
da_push(list, u);

// 3. Iterate - Using the built-in iterator macro
User* item;
da_foreach(list, User*, item) {
    printf("%s\n", item->name);
}

// 4. Cleanup - Release memory safely
da_destroy(list);
