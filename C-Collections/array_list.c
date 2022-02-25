//
// Created by AmirHossein Aghajari on 2/25/22.
//

#include <stdio.h>
#include <stdlib.h>
#include "iterator.h"
#include "collection.h"
#include "array_list.h"

#define DEFAULT_CAPACITY 10
#define MAX(a, b) ((a) > (b) ? (a) : (b))

struct ArrayList *array_list_create() {
    return array_list_create2(DEFAULT_CAPACITY);
}

struct ArrayList *array_list_create2(int capacity) {
    struct ArrayList *list = malloc(sizeof(struct ArrayList));
    if (list == NULL)
        return list;

    list->size = 0;
    list->elements = malloc(sizeof(void *) * capacity);
    list->capacity = capacity;
    return list;
}

struct ArrayList *array_list_create3(const struct Collection collection) {
    return array_list_create4(collection_iterator(collection));
}

struct ArrayList *array_list_create4(struct Iterator *iterator) {
    int size = iterator_size(iterator);
    struct ArrayList *list = array_list_create2(size);
    if (list == NULL)
        return list;

    list->size = size;
    for (int i = 0; i < size; ++i) {
        list->elements[i] = iterator->next;
    }
    iterator_destroy(iterator);
    return list;
}

struct ArrayList *array_list_create5(void **array, int size) {
    struct ArrayList *list = malloc(sizeof(struct ArrayList));
    list->size = list->capacity = size;
    list->elements = array;
    list->elements = array_list_toArray(list); // copy
    return list;
}

void array_list_new_elements(struct ArrayList *list, int newSize) {
    list->elements = realloc(list->elements, sizeof(void *) * newSize);
    list->capacity = newSize;
    if (newSize < list->size)
        list->size = newSize;
}

void array_list_trim_to_size(struct ArrayList *list) {
    if (list->capacity > list->size)
        array_list_new_elements(list, list->size);
}

void array_list_grow(struct ArrayList *list, int minCapacity) {
    int oldCapacity = list->capacity;
    array_list_new_elements(list, oldCapacity + MAX(minCapacity - oldCapacity, oldCapacity >> 1));
}

void array_list_growOne(struct ArrayList *list) {
    array_list_grow(list, list->size + 1);
}

int array_list_size(struct ArrayList *list) {
    return list->size;
}

_Bool array_list_contains(struct ArrayList *_Nonnull list, void *_Nullable data) {
    return array_list_indexOf(list, data) != -1;
}

int array_list_indexOf(struct ArrayList *_Nonnull list, void *_Nullable data) {
    for (int i = 0; i < list->size; ++i) {
        if (list->elements[i] == data)
            return i;
    }
    return -1;
}

_Bool array_list_contains2(struct ArrayList *_Nonnull list, void *_Nullable data, _Bool (*_Nonnull finder)(void *, void *)) {
    return array_list_indexOf2(list, data, finder) != -1;
}

int array_list_indexOf2(struct ArrayList *_Nonnull list, void *_Nullable data, _Bool (*_Nonnull finder)(void *, void *)) {
    for (int i = 0; i < list->size; ++i) {
        if (finder(list->elements[i], data))
            return i;
    }
    return -1;
}

int array_list_lastIndexOf(struct ArrayList *_Nonnull list, void *_Nullable data) {
    for (int i = list->size - 1; i >= 0; --i) {
        if (list->elements[i] == data)
            return i;
    }
    return -1;
}

int array_list_lastIndexOf2(struct ArrayList *_Nonnull list, void *_Nullable data, _Bool (*_Nonnull finder)(void *, void *)) {
    for (int i = list->size - 1; i >= 0; --i) {
        if (finder(list->elements[i], data))
            return i;
    }
    return -1;
}

void **array_list_toArray(struct ArrayList *list) {
    void **elements = malloc(sizeof(void *) * list->size);
    for (int i = 0; i < list->size; ++i)
        elements[i] = list->elements[i];
    return elements;
}

void **array_list_toArrayOfRange(struct ArrayList *list, int fromIndex, int toIndex) {
    void **elements = malloc(sizeof(void *) * list->size);
    for (int i = fromIndex; i < toIndex; ++i)
        elements[i] = list->elements[i];
    return elements;
}

void *array_list_get(struct ArrayList *list, int index) {
    return list->elements[index];
}

void *array_list_set(struct ArrayList *list, int index, void *newValue) {
    void *oldValue = list->elements[index];
    list->elements[index] = newValue;
    return oldValue;
}

void array_list_add(struct ArrayList *list, void *data) {
    if (list->capacity == list->size)
        array_list_growOne(list);
    list->elements[list->size] = data;
    list->size++;
}

void array_list_insert(struct ArrayList *list, void *data, int index) {
    int size = list->size;
    if (list->capacity == size)
        array_list_growOne(list);

    for (int i = size; i >= index + 1; --i)
        list->elements[i] = list->elements[i - 1];
    list->elements[index] = data;
    list->size++;
}

void *array_list_remove(struct ArrayList *list, int index) {
    void *oldValue = list->elements[index];

    int newSize;
    if ((newSize = list->size - 1) > index) {
        for (int i = index; i < list->size - 1; ++i)
            list->elements[i] = list->elements[i + 1];
    }
    list->elements[list->size = newSize] = NULL;

    return oldValue;
}

void array_list_removeRange(struct ArrayList *list, int fromIndex, int toIndex) {
    int removeSize = toIndex - fromIndex;
    for (int i = fromIndex; i < list->size - removeSize; ++i)
        list->elements[i] = list->elements[i + removeSize];
    list->size -= removeSize;
}

void array_list_free_and_removeRange(struct ArrayList *list, int fromIndex, int toIndex) {
    for (int i = fromIndex; i < toIndex; ++i)
        free(list->elements[i]);

    array_list_removeRange(list, fromIndex, toIndex);
}

void *array_list_removeData(struct ArrayList *list, void *data) {
    int index = array_list_indexOf(list, data);
    if (index == -1)
        return NULL;
    else
        return array_list_remove(list, index);
}

void *array_list_removeData2(struct ArrayList *list, void *data, _Bool (*_Nonnull finder)(void *, void *)) {
    int index = array_list_indexOf2(list, data, finder);
    if (index == -1)
        return NULL;
    else
        return array_list_remove(list, index);
}

void array_list_clear(struct ArrayList *list) {
    list->size = 0;
    list->capacity = DEFAULT_CAPACITY;
    void **old = list->elements;
    list->elements = malloc(sizeof(void *) * list->capacity);
    free(old);
}

void array_list_free_and_clear(struct ArrayList *list) {
    for (int i = 0; i < list->size; ++i)
        free(list->elements[i]);
    array_list_clear(list);
}

void array_list_addAll(struct ArrayList *list, const struct Collection collection) {
    struct Iterator * iterator = collection_iterator(collection);
    int numNew = iterator_size(iterator);
    if (numNew == 0)
        return;

    if (numNew > list->capacity - list->size)
        array_list_grow(list, list->size + numNew);

    for (int i = list->size; i < list->size + numNew; ++i)
        list->elements[i] = iterator_next(iterator);

    list->size += numNew;
    iterator_destroy(iterator);
}

void array_list_insertAll(struct ArrayList *list, const struct Collection collection, int index) {
    struct Iterator * iterator = collection_iterator(collection);
    int numNew = iterator_size(iterator);
    if (numNew == 0)
        return;

    if (numNew > list->capacity - list->size)
        array_list_grow(list, list->size + numNew);

    list->size += numNew;

    for (int i = list->size; i >= index + numNew; --i)
        list->elements[i] = list->elements[i - numNew];

    for (int i = index; i < index + numNew; ++i)
        list->elements[i] = iterator_next(iterator);
    iterator_destroy(iterator);
}

struct ArrayListIterator {
    struct ArrayList *list;
    int index;
};

_Bool array_list_iterator_has_next(struct Iterator *iterator) {
    struct ArrayListIterator *data = iterator->data;
    return data->index < data->list->size;
}

void *array_list_iterator_next(struct Iterator *iterator) {
    struct ArrayListIterator *data = iterator->data;
    return data->list->elements[data->index++];
}

void array_list_iterator_remove(struct Iterator *iterator) {
    struct ArrayListIterator *data = iterator->data;
    array_list_remove(data->list, --data->index);
}

int array_list_iterator_size(struct Iterator *iterator) {
    struct ArrayListIterator *data = iterator->data;
    return data->list->size - data->index;
}

void array_list_iterator_destroy(struct Iterator *iterator) {
    free(iterator->data);
    free(iterator);
}

struct Iterator *array_list_iterator(struct ArrayList *list) {
    struct Iterator *iter = malloc(sizeof(struct Iterator));
    struct ArrayListIterator *data = malloc(sizeof(struct ArrayListIterator));
    data->list = list;
    data->index = 0;
    iter->data = data;
    iter->has_next = array_list_iterator_has_next;
    iter->next = array_list_iterator_next;
    iter->remove = array_list_iterator_remove;
    iter->destroy = array_list_iterator_destroy;
    iter->size = array_list_iterator_size;
    return iter;
}

struct Collection __array_list_copy(struct ArrayList *list, int fromIndex, int toIndex) {
    return array_list_collection(array_list_copyOfRange(list, fromIndex, toIndex));
}

void __array_list_destroy(struct ArrayList* list){
    free(list->elements);
    free(list);
}

struct Collection array_list_collection(struct ArrayList *list){
    struct Collection c;
    c.list = list;
    c.size = (int (*)(void *)) array_list_size;
    c.get = (void *(*)(void *, int)) array_list_get;
    c.set = (void *(*)(void *, int, void *)) array_list_set;
    c.add = (void (*)(void *, void *)) array_list_add;
    c.remove = (void *(*)(void *, int)) array_list_remove;
    c.insert = (void (*)(void *, void *, int)) array_list_insert;
    c.iterator = (struct Iterator *(*)(void *)) array_list_iterator;
    c.copy = (struct Collection (*)(void *, int, int)) __array_list_copy;
    c.destroy = (void (*)(void *)) __array_list_destroy;
    return c;
}

struct ArrayList *array_list_copy(struct ArrayList *list) {
    struct ArrayList *l = malloc(sizeof(struct ArrayList));
    l->size = l->capacity = list->size;
    l->elements = array_list_toArray(list);
    return l;
}

struct ArrayList *array_list_copyOfRange(struct ArrayList *list, int fromIndex, int toIndex) {
    struct ArrayList *l = malloc(sizeof(struct ArrayList));
    l->size = l->capacity = toIndex - fromIndex;
    l->elements = array_list_toArrayOfRange(list, fromIndex, toIndex);
    return l;
}