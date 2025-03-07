#include "memory_management.h"
#include <stdlib.h>

// Initialize counters for memory usage
int heap_allocations = 0;
int heap_deallocations = 0;
int stack_allocations = 0;
int stack_deallocations = 0;

typedef struct MemoryRecord {
    void *pointer;
    size_t size;
    struct MemoryRecord *next;
} MemoryRecord;

MemoryRecord *heap_memory_records = NULL;

void addMemoryRecord(void *pointer, size_t size) {
    MemoryRecord *record = (MemoryRecord *)malloc(sizeof(MemoryRecord));
    record->pointer = pointer;
    record->size = size;
    record->next = heap_memory_records;
    heap_memory_records = record;
}

void removeMemoryRecord(void *pointer) {
    MemoryRecord **current = &heap_memory_records;
    while (*current) {
        if ((*current)->pointer == pointer) {
            MemoryRecord *to_free = *current;
            *current = (*current)->next;
            free(to_free);
            return;
        }
        current = &(*current)->next;
    }
}

#if MEMORY_MANAGEMENT_DISPLAY
void displayMemoryUsage() {
    printf("\n");
    printf("-------------------------------------------------\n");
    printf("|                   Uso de Memoria              |\n");
    printf("-------------------------------------------------\n");
    printf("| Segmento de Texto (Codigo)                    |\n");
    printf("|-----------------------------------------------|\n");
    printf("| Segmento de Datos (Globales y Estaticos)      |\n");
    printf("|-----------------------------------------------|\n");
    printf("| Segmento BSS (Globales y Estaticos no inicializados) |\n");
    printf("|-----------------------------------------------|\n");
    printf("| Heap (Memoria Dinamica)                       |\n");
    printf("|   Asignaciones: %-28d |\n", heap_allocations);
    printf("|   Liberaciones: %-28d |\n", heap_deallocations);
    printf("|-----------------------------------------------|\n");
    printf("| Stack (Variables Locales)                     |\n");
    printf("|   Asignaciones: %-28d |\n", stack_allocations);
    printf("|   Liberaciones: %-28d |\n", stack_deallocations);
    printf("-------------------------------------------------\n");
    printf("\n");

    printf("-------------------------------------------------\n");
    printf("|             Detalles de Memoria Heap          |\n");
    printf("-------------------------------------------------\n");
    printf("| Puntero          | Tamano (bytes)             |\n");
    printf("-------------------------------------------------\n");
    MemoryRecord *current = heap_memory_records;
    while (current) {
        printf("| 0x%-14p | %-27zu |\n", current->pointer, current->size);
        current = current->next;
    }
    printf("-------------------------------------------------\n");
    printf("\n");
}

void incrementHeapAllocations(void *pointer, size_t size) {
    heap_allocations++;
    addMemoryRecord(pointer, size);
    #if MEMORY_MANAGEMENT_DISPLAY
    printf("Memoria asignada en el heap: Puntero=0x%p, Tamano=%zu bytes\n", pointer, size);
    #endif
}

void incrementHeapDeallocations(void *pointer) {
    heap_deallocations++;
    removeMemoryRecord(pointer);
    #if MEMORY_MANAGEMENT_DISPLAY
    printf("Memoria liberada en el heap: Puntero=0x%p\n", pointer);
    #endif
}

void incrementStackAllocations() {
    stack_allocations++;
}

void incrementStackDeallocations() {
    stack_deallocations++;
}
#endif
