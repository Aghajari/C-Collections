//
// Created by AmirHossein Aghajari on 2/25/22.
//

#include "collection.h"
#include "array_list.h"
#include "iterator.h"

int collection_size(struct Collection collection) {
    return collection.size(collection.list);
}

void *collection_get(struct Collection collection, int index) {
    return collection.get(collection.list, index);
}

void *collection_set(struct Collection collection, int index, void *new_data) {
    return collection.set(collection.list, index, new_data);
}

void *collection_remove(struct Collection collection, int index) {
    return collection.remove(collection.list, index);
}

void collection_add(struct Collection collection, void *data) {
    collection.add(collection.list, data);
}

void collection_insert(struct Collection collection, void *data, int index) {
    collection.insert(collection.list, data, index);
}

struct Iterator *collection_iterator(struct Collection collection) {
    return collection.iterator(collection.list);
}

void collection_swap(struct Collection collection, int i, int j) {
    if (i == j)
        return;

    collection.set(collection.list, i,
                   collection.set(collection.list, j,
                                  collection.get(collection.list, i)));
}

void __collection_swap(struct Collection *collection, int i, int j) {
    collection->set(collection->list, i,
                    collection->set(collection->list, j,
                                    collection->get(collection->list, i)));
}

struct Collection collection_create(void **elements, int size) {
    return array_list_collection(array_list_create5(elements, size));
}

void merge_sort(struct Collection *src, struct Collection *dest, int low, int high, int off,
                int (*compare)(const void *, const void *));

void collection_sort(struct Collection collection,
                     int (*compare)(const void *, const void *)) {
    collection_sortRangeOf(collection, 0, collection.size(collection.list), compare);
}

void collection_sortRangeOf(struct Collection collection, int fromIndex, int toIndex,
                            int (*compare)(const void *, const void *)) {
    struct Collection src = collection.copy(collection.list, fromIndex, toIndex);
    merge_sort(&src, &collection, fromIndex, toIndex, -fromIndex, compare);
    src.destroy(src.list);
}

void merge_sort(struct Collection *src, struct Collection *dest, int low, int high, int off,
                int (*compare)(const void *, const void *)) {
    int length = high - low;

    // Insertion sort on smallest arrays
    if (length < 7) {
        for (int i = low; i < high; i++)
            for (int j = i; j > low && compare(dest->get(dest->list, j - 1), dest->get(dest->list, j)) > 0; j--)
                __collection_swap(dest, j, j - 1);
        return;
    }

    // Recursively sort halves of dest into src
    int destLow = low;
    int destHigh = high;
    low += off;
    high += off;
    int mid = (int) (((unsigned int) (low + high)) >> 1);
    merge_sort(dest, src, low, mid, -off, compare);
    merge_sort(dest, src, mid, high, -off, compare);

    // If list is already sorted, just copy from src to dest.  This is an
    // optimization that results in faster sorts for nearly ordered lists.
    if (compare(src->get(src->list, mid - 1), src->get(src->list, mid)) <= 0) {
        for (int i = 0; i < length; ++i)
            dest->set(dest->list, destLow + i, src->get(src->list, low + i));
        return;
    }

    // Merge sorted halves (now in src) into dest
    for (int i = destLow, p = low, q = mid; i < destHigh; i++) {
        if (q >= high || p < mid && compare(src->get(src->list, p), src->get(src->list, q)) <= 0)
            dest->set(dest->list, i, src->get(src->list, p++));
        else
            dest->set(dest->list, i, src->get(src->list, q++));
    }
}

unsigned int collection_binarySearch(struct Collection collection, void *key,
                                     int (*compare)(const void *, const void *)) {
    unsigned int low = 0;
    unsigned int high = collection.size(collection.list) - 1;

    while (low <= high) {
        unsigned int mid = (low + high) >> 1;
        int cmp = compare(collection.get(collection.list, (int) mid), key);

        if (cmp < 0)
            low = mid + 1;
        else if (cmp > 0)
            high = mid - 1;
        else
            return mid; // key found
    }
    return -(low + 1);  // key not found
}

void collection_reverse(struct Collection collection) {
    int size = collection.size(collection.list);
    for (int i = 0, mid = size >> 1, j = size - 1; i < mid; i++, j--)
        __collection_swap(&collection, i, j);
}

void collection_rotate(struct Collection collection, int distance) {
    int size = collection.size(collection.list);
    if (size == 0)
        return;

    distance = distance % size;
    if (distance < 0)
        distance += size;
    if (distance == 0)
        return;

    for (int cycleStart = 0, nMoved = 0; nMoved != size; cycleStart++) {
        void *displaced = collection.get(collection.list, cycleStart);
        int i = cycleStart;
        do {
            i += distance;
            if (i >= size)
                i -= size;
            displaced = collection.set(collection.list, i, displaced);
            nMoved++;
        } while (i != cycleStart);
    }
}

void * collection_max(struct Collection collection, int (*compare)(const void *, const void *)) {
    struct Iterator *i = collection.iterator(collection.list);

    void *candidate = iterator_next(i);
    while (iterator_has_next(i)) {
        void *next = iterator_next(i);
        if (compare(next, candidate) > 0)
            candidate = next;
    }
    iterator_destroy(i);
    return candidate;
}

void * collection_min(struct Collection collection, int (*compare)(const void *, const void *)) {
    struct Iterator *i = collection.iterator(collection.list);

    void *candidate = iterator_next(i);
    while (iterator_has_next(i)) {
        void *next = iterator_next(i);
        if (compare(next, candidate) < 0)
            candidate = next;
    }
    iterator_destroy(i);
    return candidate;
}

void collection_fill(struct Collection collection, void * value){
    int size = collection.size(collection.list);
    for (int i = 0; i < size; ++i)
        collection.set(collection.list, i, value);
}