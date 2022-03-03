# C-Collections
 Java collections and lists for C
 
 ## Table of Contents  
- [ArrayList](#arraylist)  
- [LinkedList](#linkedlist)
- [Iterator](#iterator)
- [Collection](#collection)
  - [Swap](https://www.geeksforgeeks.org/collections-swap-method-in-java-with-examples/)
  - [Sort & SortRangeOf](https://www.geeksforgeeks.org/collections-sort-java-examples/)
  - [BinarySearch](https://www.geeksforgeeks.org/collections-binarysearch-java-examples/)
  - [Max](https://www.geeksforgeeks.org/collections-max-method-in-java-with-examples/)
  - [Min](https://www.geeksforgeeks.org/collections-min-method-in-java-with-examples/)
  - [Fill](https://www.geeksforgeeks.org/collections-fill-method-in-java-with-examples/)
  - [Reverse](https://www.geeksforgeeks.org/collections-reverse-method-in-java-with-examples/)
  - [Rotate](https://www.geeksforgeeks.org/java-util-collections-rotate-method-java-examples/)
- [HashMap](#hashmap)
- HashSet (TO-DO)



## ArrayList

What is [ArrayList](https://www.geeksforgeeks.org/arraylist-in-java/)?
> ArrayList is a dynamic array and we do not have to specify the size while creating it, the size of the array automatically increases when we dynamically add and remove items.

### Usage

- include ArrayList header file
```c
#include "array_list.h"
```

- Create ArrayList struct :
```c
struct ArrayList *list = array_list_create(); // or array_list_create2(capacity);
```

- Add items to the list :
```c
array_list_add(list, "Hello");
array_list_add(list, "World");
```

Result : 
1. Hello
2. World

- Insert item :
```c
array_list_insert(list, "First", 0);
```

Result :
1. First
2. Hello
3. World

- InsertAll (Or AddAll) :
```c
char *list2[] = {"Hi", "Hii", "Hiii"};
array_list_insertAll(list, collection_create((void **) list2, 3), 1);
```

Result :
1. First
2. Hi
3. Hii
4. Hiii
5. Hello
6. World

- Remove item (Or removeRange/ removeData) :
```c
array_list_remove(list, index);
```


## LinkedList

What is [LinkedList](https://geeksforgeeks.org/data-structures/linked-list/)?
> A linked list is a linear data structure, in which the elements are not stored at contiguous memory locations. The elements in a linked list are linked using pointers

### Usage

- include LinkedList header file
```c
#include "linked_list.h"
```

- Create the Head element :
```c
struct LinkedListNode *list = linked_list_new("Hello");
```

- Append
```c
linked_list_append(linked_list_new("Test"), list);
```

Result: Hello -> Test

- Push
```c
linked_list_push(linked_list_new("1", linked_list_new("2")), list);
```

Result: 1 -> 2 -> Hello -> Test

- Pop
```c
linked_list_pop(list);
```
Result: 2 -> Hello -> Test

- Insert
```c
linked_list_insertAt(linked_list_new("A"), list, 1);
```
Result: 2 -> A -> Hello -> Test

- Insert with Finder function
```c
// -1 = insert before target
// +1 = insert after target
// +2 = insert after the next position of target, ...
int finder(struct LinkedListNode* node, int index, const void *target) {
    return strcmp(target, node->data) == 0 ? 2 : 0;
}

linked_list_insert(linked_list_new("B"), list, "A", finder);
```
Result: 2 -> A -> Hello -> B -> Test

- Remove
```c
linked_list_removeAt(list, 2);
```
Result: 2 -> A -> B -> Test

- Connect
```c
linked_list_connect_before(&list, linked_list_new("NEW", linked_list_new("HI")), linked_list_new("TEST"));
```
Result: TEST -> NEW -> HI -> 2 -> A -> B -> Test

- Check out other functions such as `connect_after`, `pollLast`, `peekLast`, `removeRange`, `copy`, `toArray`, `indexOf`, `lastIndexOf`, `swap`, `set`, `find`, ...

## Iterator

What is [Iterator](https://www.w3schools.com/java/java_iterator.asp)?
> Iterator can be used to loop through collections

### Usage

```c
#include "iterator.h"

struct Iterator *iter = collection_iterator(collection);
// struct Iterator *iter = array_list_iterator(arrayList);
// struct Iterator *iter = linked_list_iterator(linkedList);

while (iterator_has_next(iter)) {
    printf("%s -> ", (char *) iterator_next(iter));
    // iterator_remove(iter) if needed to remove the element from the collection
}
iterator_destroy(iter);
```

## Collection
```c
#include "collection.h"

struct Collection coll = collection_create(array, size);
// struct Collection coll = array_list_collection(arrayList);
// struct Collection coll = linked_list_collection(linkedList);

collection_sort(coll, comparator);
collection_reverse(coll);
collection_rotate(coll, 1);
void * value = collection_binarySearch(coll, key, comparator);
void * value = collection_max(coll, comparator);
void * value = collection_min(coll, comparator);
collection_fill(coll, value);
```

## HashMap

What is [HashMap](https://www.geeksforgeeks.org/java-util-hashmap-in-java-with-examples/)?
> HashMap stores the data in (Key, Value) pairs...

### Usage

- include HashMap header file
```c
#include "hash_map.h"
```

- Create HashMap struct :
```c
struct HashMap *map = hash_map_create(); // or hash_map_create2(capacity);
```

- Put key-values :
```c
hash_map_string_put(map, "Key1", "Item1");
hash_map_int_put(map, 2, "Item2");
hash_map_put(map, key, value);
```

- Get value by key :
```c
printf("%s\n", (char *) hash_map_string_get(map, "Key1"));
printf("%s\n", (char *) hash_map_int_get(map, 2));
```

- Remove value by key
```c
hash_map_int_remove(map, 2);
```

- Checkout other functions such as `containsKey`, `containsValue`, `putAll`, ...

### Iterator over keys, values and entries

`hash_map_entryIterator`, `hash_map_keyIterator` and `hash_map_valueIterator`

```c
struct Iterator *iter = hash_map_entryIterator(map);
while (iterator_has_next(iter)) {
    struct HashMapEntry *entry = iterator_next(iter);
    printf("Key: %s, Value: %s\n", (char *) entry->key, (char *) entry->value);
}
iterator_destroy(iter);
```
