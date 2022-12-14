#include <stdlib.h>

#include "memory.h"
#include "vm.h"

static void freeObject(Obj *obj);

void *reallocate(void *pointer, size_t oldSize, size_t newSize) {
    if (newSize == 0) {
        free(pointer);
        return NULL;
    }

    void *result = realloc(pointer, newSize);
    if (result == NULL) exit(1);
    return result;
}

void freeObjects() {
    Obj *obj = vm.objects;
    while (obj != NULL) {
        Obj *next = obj->next;
        freeObject(obj);
        obj = next;
    }
}

static void freeObject(Obj *obj) {
    switch (obj->type) {
        case OBJ_FUNCTION: {
            ObjFunction *function = (ObjFunction *)obj;
            freeChunk(&function->chunk);
            FREE(ObjFunction, obj);
            break;
        }
        case OBJ_NATIVE: 
            FREE(ObjNative, obj);
            break;
        case OBJ_STRING: {
            ObjString *string = (ObjString *)obj;
            FREE_ARRAY(char, string->chars, string->length + 1);
            FREE(ObjString, obj);
            break;
        }
        default: return;
    }
}