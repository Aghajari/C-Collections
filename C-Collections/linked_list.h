//
// Created by AmirHossein Aghajari on 12/28/21.
//

#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#define COMPARABLE_ARGS struct LinkedListNode*_Nullable list, const void*_Nullable target, \
int (* _Nonnull _finder)(struct LinkedListNode *_Nonnull , int, const void *_Nullable )

/* Creates new LinkedListNode with custom data and other linked nodes */
#define linked_list_new(...) __linked_list_new__(__VA_ARGS__, NULL)
/* Inserts elements at the front of the list */
#define linked_list_connect_before(...) __linked_list_connect_before__(__VA_ARGS__, NULL)
/* Inserts elements at the end of the list */
#define linked_list_connect_after(...) __linked_list_connect_after__(__VA_ARGS__, NULL)

struct LinkedListNode {
    void *_Nullable data;
    struct LinkedListNode *_Nullable next;
};

/*
 * Finder functions can be used sin `linked_list_find',
 * `linked_list_findParent', `linked_list_insert' and `linked_list_remove'
 *
 * @return 0 If the childs does not match the target, otherwise the distance from the childs.
 * (Negative number indicates before and positive after childs)
 */

/* A Finder function to find the childs by index, typeof target must be (int *) */
int linked_list_finder_index(struct LinkedListNode *_Nonnull node, int index, const void *_Nullable target);

/* A Finder function to find the childs by data, typeof target must be (void **) */
int linked_list_finder_data(struct LinkedListNode *_Nonnull node, int index, const void *_Nullable target);

/* A Finder function to find the last childs in list, target can be NULL */
int linked_list_finder_end(struct LinkedListNode *_Nonnull node, int index, const void *_Nullable target);

/* Creates new LinkedListNode */
struct LinkedListNode *_Nullable linked_list_create();

struct LinkedListNode *_Nullable __linked_list_new__(void *_Nullable data, ...);

/* @return the number of elements in this list */
int linked_list_size(struct LinkedListNode *_Nullable list);

/*
 * Returns the element at the specified position found by Finder function in the list.
 * (Or NULL if it doesn't exist)
 */
struct LinkedListNode *_Nullable linked_list_find(COMPARABLE_ARGS);

/* Returns the element at the specified position in the list. (Or NULL if it doesn't exist) */
struct LinkedListNode *_Nullable linked_list_findByIndex(struct LinkedListNode *_Nullable list, int index);

/* Returns the data of element at the specified position in the list. (Or NULL if it doesn't exist) */
void *_Nullable linked_list_get(struct LinkedListNode *_Nullable list, int index);

/* Returns the first element with the specified data in the list. (Or NULL if it doesn't exist) */
struct LinkedListNode *_Nullable
linked_list_findByData(struct LinkedListNode *_Nullable list, const void *_Nullable data);

/*
 * Returns parent of the element at the specified position found by Finder function in the list.
 * (Or NULL if it doesn't exist)
 */
struct LinkedListNode *_Nullable linked_list_findParent(COMPARABLE_ARGS);

/* Returns parent of the element at the specified position in the list. (Or NULL if it doesn't exist)*/
struct LinkedListNode *_Nullable linked_list_findParentByIndex(struct LinkedListNode *_Nullable list, int index);

/* Returns parent of the first element with the specified data in the list. (Or NULL if it doesn't exist) */
struct LinkedListNode *_Nullable
linked_list_findParentByData(struct LinkedListNode *_Nullable list, const void *_Nullable data);

/* Returns parent of the specified childs in the list (Or NULL if it doesn't exist). */
struct LinkedListNode *_Nullable
linked_list_findParentByNode(struct LinkedListNode *_Nullable list, struct LinkedListNode *_Nullable node);

/* @return the last element in this list */
struct LinkedListNode *_Nullable linked_list_peekLast(struct LinkedListNode *_Nullable list);

/* @return parent of the last element in this list (Or NULL if only head element exists)*/
struct LinkedListNode *_Nullable linked_list_peekLastParent(struct LinkedListNode *_Nullable list);

/*
* Returns the index of the first occurrence of the specified element in the list,
* or -1 if the list does not contain the element.
*/
int linked_list_indexOf(struct LinkedListNode *_Nullable node, struct LinkedListNode *_Nullable list);

/*
* Returns the index of the first occurrence of the specified element in the list,
* or -1 if the list does not contain the element.
*/
int linked_list_indexOfData(const void *_Nullable node, struct LinkedListNode *_Nullable list);

/*
* Returns the index of the last occurrence of the specified element in the list,
* or -1 if the list does not contain the element.
*/
int linked_list_lastIndexOfData(const void *_Nullable node, struct LinkedListNode *_Nullable list);

/*
* Inserts the specified element at the specified position found by finder in the list.
* Shifts the element currently at that position (if any) and any
* subsequent elements to the right (adds one to their indices).
* @return 1 If the operation was performed, 0 otherwise
*/
_Bool linked_list_insert(struct LinkedListNode *_Nullable node, COMPARABLE_ARGS);

/*
* Inserts the specified element at the specified position in the list.
* @return 1 If the operation was performed, 0 otherwise
*/
_Bool linked_list_insertAt(struct LinkedListNode *_Nullable node, struct LinkedListNode *_Nullable list, int index);

/*
* Pops an element from the stack represented by the list. In other
* words, removes and frees the first element of the list.
* @return the element that was removed from the list
*/
void *_Nullable linked_list_pop(struct LinkedListNode *_Nullable list);

/*
* removes and frees the last element of the list.
* @return the element that was removed from the list
*/
void *_Nullable linked_list_pollLast(struct LinkedListNode *_Nullable list);

/*
* Pushes an element onto the stack represented by the list. In other
* words, inserts the element at the front of the list.
* @return 1 If the operation was performed, 0 otherwise
*/
_Bool linked_list_push(struct LinkedListNode *_Nullable node, struct LinkedListNode *_Nullable list);

/*
* Appends the specified element to the end of the list.
* @return 1 If the operation was performed, 0 otherwise
*/
_Bool linked_list_append(struct LinkedListNode *_Nullable node, struct LinkedListNode *_Nullable list);


/*
* Replaces the childs's data at the specified position in this list with the specified data.
* @return the element previously at the specified position
*/
void *_Nullable linked_list_set(struct LinkedListNode *_Nullable list, int index, void *_Nullable data);

/*
* Removes and frees the first element found by the finder in the list. Shifts any
* subsequent elements to the left (subtracts one from their indices).
* @return the element previously at the specified position
*/
void *_Nullable linked_list_remove(COMPARABLE_ARGS);

/*
* Removes and frees the element at the specified position in the list.
* @return the element previously at the specified position
*/
void *_Nullable linked_list_removeAt(struct LinkedListNode *_Nullable list, int index);

/*
* Removes and frees the first element with the specified data in the list.
* @return the element that was removed from the list
*/
void *_Nullable linked_list_removeData(struct LinkedListNode *_Nullable list, const void *_Nullable data);

/*
* Removes and frees the specified childs in the list.
* @return the element that was removed from the list
*/
void *_Nullable linked_list_removeNode(struct LinkedListNode *_Nullable list, struct LinkedListNode *_Nullable data);

/*
* Removes the elements at the specified position range in the list.
* Shifts any subsequent elements to the left (subtracts one from their indices).
*/
void linked_list_removeRange(struct LinkedListNode *_Nullable list, int start, int end);

/*
* Removes and frees the elements at the specified position range in the list.
* Shifts any subsequent elements to the left (subtracts one from their indices).
*/
void linked_list_free_and_removeRange(struct LinkedListNode *_Nullable list, int start, int end);

/*
 * Returns a shallow copy of this LinkedList. (The elements
 * themselves are not cloned.)
 *
 * @return a shallow copy of the LinkedList
 */
struct LinkedListNode *_Nullable linked_list_copy(struct LinkedListNode *_Nullable list);
struct LinkedListNode *_Nullable linked_list_copyOfRange(struct LinkedListNode *_Nullable list, int fromIndex, int toIndex);

/*
* Fills an array with elements in the linked list
* in proper sequence (from start to end element).
*
* @return number of inserted elements
*/
int linked_list_toArray(struct LinkedListNode *_Nullable list, void *_Nullable *_Nullable array, int start, int end);

int __linked_list_connect_before__(struct LinkedListNode *_Nullable *_Nullable list1, ...);

int __linked_list_connect_after__(struct LinkedListNode *_Nullable *_Nullable list1, ...);

/**
* Returns an iterator over the elements in the list.
*/
struct Iterator *_Nonnull linked_list_iterator(struct LinkedListNode *_Nonnull list);

/**
* Returns a collection structure of the list
*/
struct Collection linked_list_collection(struct LinkedListNode *_Nonnull list);

#undef COMPARABLE_ARGS
#endif