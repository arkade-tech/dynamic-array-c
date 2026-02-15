#include <stdio.h>
#include <stdlib.h>
#include "dyn_array.h"

// Example Struct
typedef struct {
    int id;
    char name[32];
} User;

int main() {
    printf("--- Industry Grade Generic Vector ---\n");
    
    DynArray* list = da_create(4);

    // 1. Populate
    for(int i=0; i<5; ++i) {
        User* u = malloc(sizeof(User));
        u->id = i * 100;
        snprintf(u->name, 32, "User_%d", i);
        da_push(list, u);
    }

    // 2. Iterate using Macro
    printf(">> Current List:\n");
    User* iter;
    da_foreach(list, User*, iter) {
        printf("   ID: %d | Name: %s\n", iter->id, iter->name);
    }

    // 3. Delete Index 2
    printf("\n>> Deleting Index 2...\n");
    User* removed = (User*)da_delete(list, 2);
    if (removed) {
        printf("   Removed: %s\n", removed->name);
        free(removed); // CRITICAL: User owns the data
    }

    // 4. Cleanup
    printf("\n>> Cleaning up...\n");
    da_foreach(list, User*, iter) {
        free(iter);
    }
    da_destroy(list);
    
    return 0;
}
