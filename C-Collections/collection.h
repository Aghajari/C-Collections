//
// Created by AmirHossein Aghajari on 2/25/22.
//

#ifndef COLLECTION_H
#define COLLECTION_H

struct Collection {
    void *_Nonnull list;
    int (*_Nonnull size)(void *_Nonnull);
    void *_Nullable (*_Nonnull get)(void *_Nonnull, int);
    void *_Nullable (*_Nonnull set)(void *_Nonnull, int, void *_Nullable);
    void (*_Nonnull add)(void *_Nonnull, void *_Nullable);
    void (*_Nonnull insert)(void *_Nonnull, void *_Nullable, int);
    void *_Nullable (*_Nonnull remove)(void *_Nonnull, int);
    struct Iterator*_Nonnull (*_Nonnull iterator)(void *_Nonnull);
    struct Collection (*_Nonnull copy)(void *_Nonnull, int, int);
    void (*_Nonnull destroy)(void *_Nonnull);
};

int collection_size(struct Collection collection);
void *_Nullable collection_get(struct Collection collection, int index);
void *_Nullable collection_set(struct Collection collection, int index, void *_Nullable new_data);
void *_Nullable collection_remove(struct Collection collection, int index);
void collection_add(struct Collection collection, void *_Nullable data);
void collection_insert(struct Collection collection, void *_Nullable data, int index);

/**
* Returns an iterator over the elements in the collection.
*/
struct Iterator *_Nonnull collection_iterator(struct Collection collection);

/**
* Swaps the elements at the specified positions in the specified collection.
* (If the specified positions are equal, invoking this method leaves
* the list unchanged.)
*/
void collection_swap(struct Collection collection, int i, int j);

struct Collection collection_create(void *_Nullable*_Nullable elements, int size);


/**
 * Sorts the specified collection according to the order induced by
 * the specified comparator.
 */
void collection_sort(struct Collection collection,
                     int (*_Nonnull compare)(const void *_Nullable, const void *_Nullable));

/**
 * Sorts the specified collection according to the order induced by
 * the specified comparator. The range to be
 * sorted extends from index {@code fromIndex}, inclusive, to index
 * {@code toIndex}, exclusive.
 */
void collection_sortRangeOf(struct Collection collection, int fromIndex, int toIndex,
                            int (*_Nonnull compare)(const void *_Nullable, const void *_Nullable));

/**
 * Searches the specified collection for the specified key using the binary
 * search algorithm.
 */
unsigned int collection_binarySearch(struct Collection collection, void *_Nullable key,
                                 int (*_Nonnull compare)(const void *_Nullable, const void *_Nullable));

/**
 * Returns the maximum element of the given collection, according to the
 * order induced by the specified comparator.
 */
void * collection_max(struct Collection collection, int (*compare)(const void *, const void *));

/**
 * Returns the minimum element of the given collection, according to the
 * order induced by the specified comparator.
 */
void * collection_min(struct Collection collection, int (*compare)(const void *, const void *));

/**
 * Replaces all of the elements of the specified collection with the specified value.
 */
void collection_fill(struct Collection collection, void * value);

/**
* Reverses the order of the elements in the specified collection.
*/
void collection_reverse(struct Collection collection);

/**
 * Rotates the elements in the specified collection by the specified distance.
 * After calling this method, the element at index {@code i} will be
 * the element previously at index {@code (i - distance)} mod
 * {@code collection.size()}, for all values of {@code i} between {@code 0}
 * and {@code collection.size()-1}, inclusive. (This method has no effect on
 * the size of the list.)
 */
void collection_rotate(struct Collection collection, int distance);

#endif //COLLECTION_H
