//
// Created by AmirHossein Aghajari on 2/25/22.
//

#include "array_list.h"
#include "iterator.h"
#include "stdlib.h"

_Bool iterator_has_next(struct Iterator *_Nonnull iterator) {
    return iterator->has_next(iterator);
}

void *_Nullable iterator_next(struct Iterator *_Nonnull iterator) {
    return iterator->next(iterator);
}

void iterator_remove(struct Iterator *_Nonnull iterator) {
    iterator->remove(iterator);
}

void iterator_destroy(struct Iterator *_Nonnull iterator) {
    iterator->destroy(iterator);
}

int iterator_size(struct Iterator *_Nonnull iterator) {
    return iterator->size(iterator);
}

struct Iterator *iterator_create(void **elements, int size) {
    struct ArrayList *list = malloc(sizeof(struct ArrayList));
    list->elements = elements;
    list->size = size;
    return array_list_iterator(list);
}