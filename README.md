# Generic Dynamic Array (C Vector)

![Build](https://img.shields.io/badge/build-passing-brightgreen)
![License](https://img.shields.io/badge/license-MIT-blue)

A production-ready, generic (\`void*\`) dynamic array implementation.

## Features
- **Generic:** Stores any pointer type.
- **Smart Resizing:** Geometric growth ($2x$) and hysteresis shrinking ($0.5x$).
- **Safety:** Bounds checking and safe memory handling.
- **Tooling:** Integrated Linting and Formatting.

## API Usage

\`\`\`c
// 1. Create
DynArray* list = da_create(8);

// 2. Add Data
User* u = malloc(sizeof(User));
da_push(list, u);

// 3. Iterate
User* item;
da_foreach(list, User*, item) {
    printf("%s\n", item->name);
}

// 4. Cleanup
da_destroy(list);
\`\`\`

## Build Commands
| Command | Description |
| :--- | :--- |
| \`make\` | Build executable |
| \`make run\` | Build and run |
| \`make check\`| Format, Lint, and Build |
