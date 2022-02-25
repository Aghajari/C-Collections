//
// Created by AmirHossein Aghajari on 2/25/22.
//

#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

struct ArrayList {
    void *_Nullable *_Nullable elements;
    int size, capacity;
};

/**
 * Creates an empty list with an initial capacity of ten.
 */
struct ArrayList *_Nullable array_list_create();

/**
 * Creates an empty list with the specified initial capacity.
 */
struct ArrayList *_Nullable array_list_create2(int capacity);

/**
* Creates a list containing the elements of the specified
* collection, in the order they are returned by the iterator.
*/
struct ArrayList *_Nullable array_list_create3(struct Collection collection);

/**
* Creates a list containing the elements of the specified iterator.
*/
struct ArrayList *_Nullable array_list_create4(struct Iterator *_Nonnull iterator);

/**
* Creates a list containing the elements of the array
*/
struct ArrayList *_Nullable array_list_create5(void *_Nullable*_Nullable array, int size);

/**
 * Trims the capacity of the {@code ArrayList} to be the
 * list's current size. An application can use this operation to minimize
 * the storage of an {@code ArrayList}.
 */
void array_list_trim_to_size(struct ArrayList *_Nonnull list);

/**
 * Returns an array containing all of the elements in this list
 * in proper sequence (from first to last element).
 */
void *_Nullable *_Nullable array_list_toArray(struct ArrayList *_Nonnull list);
void *_Nullable *_Nullable array_list_toArrayOfRange(struct ArrayList *_Nonnull list, int fromIndex, int toIndex);

/**
 * Returns the number of elements in the list.
 */
int array_list_size(struct ArrayList *_Nonnull list);

/**
 * Returns {@code true} if the list contains the specified element.
 */
_Bool array_list_contains(struct ArrayList *_Nonnull list, void *_Nullable data);

/**
 * Returns the index of the first occurrence of the specified element
 * in the list, or -1 if the list does not contain the element.
 */
int array_list_indexOf(struct ArrayList *_Nonnull list, void *_Nullable data);

/**
 * Returns {@code true} if finder can find the specified element in the list.
 */
_Bool array_list_contains2(struct ArrayList *_Nonnull list, void *_Nullable data,
                           _Bool (*_Nonnull finder)(void *_Nullable, void *_Nullable));

/**
 * Returns the index of the first occurrence of the specified element
 * in the list (found by finder), or -1 if the list does not contain the element.
 */
int array_list_indexOf2(struct ArrayList *_Nonnull list, void *_Nullable data,
                        _Bool (*_Nonnull finder)(void *_Nullable, void *_Nullable));

/**
 * Returns the index of the last occurrence of the specified element
 * in the list, or -1 if the list does not contain the element.
 */
int array_list_lastIndexOf(struct ArrayList *_Nonnull list, void *_Nullable data);

/**
 * Returns the index of the last occurrence of the specified element
 * in the list (found by finder), or -1 if the list does not contain the element.
 */
int array_list_lastIndexOf2(struct ArrayList *_Nonnull list, void *_Nullable data,
                            _Bool (*_Nonnull finder)(void *_Nullable, void *_Nullable));

/**
 * Returns the element at the specified position in the list.
 */
void *_Nullable array_list_get(struct ArrayList *_Nonnull list, int index);

/**
 * Replaces the element at the specified position in the list with
 * the specified element.
 * @return the element previously at the specified position
 */
void *_Nullable array_list_set(struct ArrayList *_Nonnull list, int index, void *_Nullable newValue);

/**
 * Appends the specified element to the end of the list.
 */
void array_list_add(struct ArrayList *_Nonnull list, void *_Nullable data);

/**
 * Inserts the specified element at the specified position in the
 * list. Shifts the element currently at that position (if any) and
 * any subsequent elements to the right (adds one to their indices).
 */
void array_list_insert(struct ArrayList *_Nonnull list, void *_Nullable data, int index);

/**
 * Removes the element at the specified position in the list.
 * Shifts any subsequent elements to the left (subtracts one from their
 * indices).
 * @return the element that was removed from the list
 */
void *_Nullable array_list_remove(struct ArrayList *_Nonnull list, int index);

/**
* Removes the first occurrence of the specified element from this list,
* if it is present. If the list does not contain the element, it is
* unchanged.
* @return the element that was removed from the list
*/
void *_Nullable array_list_removeData(struct ArrayList *_Nonnull list, void *_Nullable data);

/**
 * Removes the first occurrence of the specified element from this list,
 * if finder return True. If the list does not contain the element, it is
 * unchanged.
 * @return the element that was removed from the list
 */
void *_Nullable array_list_removeData2(struct ArrayList *_Nonnull list, void *_Nullable data,
                                       _Bool (*_Nonnull finder)(void *_Nullable, void *_Nullable));

/**
 * Appends all of the elements in the specified collection to the end of
 * this list, in the order that they are returned by the
 * specified collection's Iterator.
 */
void array_list_addAll(struct ArrayList *_Nonnull list, struct Collection collection);

/**
 * Appends all of the elements in the specified collection to the end of
 * this list, in the order that they are returned by the
 * specified collection's Iterator.
 */
void array_list_insertAll(struct ArrayList *_Nonnull list, struct Collection collection, int index);

/**
 * Removes all of the elements from this list.  The list will
 * be empty after this call returns.
 */
void array_list_clear(struct ArrayList *_Nonnull list);

/**
 * Removes from this list all of the elements whose index is between
 * {@code fromIndex}, inclusive, and {@code toIndex}, exclusive.
 * Shifts any succeeding elements to the left (reduces their index).
 * This call shortens the list by {@code (toIndex - fromIndex)} elements.
 * (If {@code toIndex==fromIndex}, this operation has no effect.)
 */
void array_list_removeRange(struct ArrayList *_Nonnull list, int fromIndex, int toIndex);

/**
 * Removes and frees all of the elements from this list.  The list will
 * be empty after this call returns.
 */
void array_list_free_and_clear(struct ArrayList *_Nonnull list);

/**
 * Removes and frees from this list all of the elements whose index is between
 * {@code fromIndex}, inclusive, and {@code toIndex}, exclusive.
 * Shifts any succeeding elements to the left (reduces their index).
 * This call shortens the list by {@code (toIndex - fromIndex)} elements.
 * (If {@code toIndex==fromIndex}, this operation has no effect.)
 */
void array_list_free_and_removeRange(struct ArrayList *_Nonnull list, int fromIndex, int toIndex);

/**
 * Returns a shallow copy of the list.
 * The elements themselves are not copied.
 */
struct ArrayList *_Nonnull array_list_copy(struct ArrayList *_Nonnull list);
struct ArrayList *_Nonnull array_list_copyOfRange(struct ArrayList *_Nonnull list, int fromIndex, int toIndex);

/**
* Returns an iterator over the elements in the list.
*/
struct Iterator *_Nonnull array_list_iterator(struct ArrayList *_Nonnull list);

/**
* Returns a collection structure of the list
*/
struct Collection array_list_collection(struct ArrayList *_Nonnull list);

#endif //ARRAY_LIST_H
