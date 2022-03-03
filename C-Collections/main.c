#include <stdio.h>
#include <string.h>

#include "collection.h"
#include "iterator.h"

void linked_list_test();
void array_list_test();
void hash_map_test();

int main() {
    hash_map_test();
    array_list_test();
    linked_list_test();
}

// *** ARRAY LIST ***
#include "array_list.h"

void print_array_list(struct ArrayList *list) {
    printf("****\n");
    for (int i = 0; i < list->size; ++i) {
        printf("%d. %s\n", i + 1, (char *) array_list_get(list, i));
    }
}

void array_list_test(){
    printf("\nARRAY LIST:\n");
    struct ArrayList *list = array_list_create2(1);
    array_list_add(list, "Hello");
    array_list_add(list, "World");
    array_list_insert(list, "1", 0);

    print_array_list(list);

    char *list2[] = {"Hi", "Hii", "Hiii"};
    array_list_insertAll(list, collection_create((void **) list2, 3), 0);
    print_array_list(list);

    printf("\nITERATOR IN ARRAY LIST:\n");
    struct Iterator *iter = array_list_iterator(list);
    while (iterator_has_next(iter)) {
        printf("%s -> ", (char *) iterator_next(iter));
    }
    printf("\n");
    iterator_destroy(iter);
}

// *** LINKED LIST ***
#include "linked_list.h"

void print_linked_list(struct LinkedListNode *list) {
    while (list != NULL) {
        printf("%s%s", (char *) list->data, list->next != NULL ? " -> " : "");
        list = list->next;
    }
    printf("\n");
}

int finder(struct LinkedListNode *node, int index, const void *target) {
    return strcmp(target, node->data) == 0 ? 2 : 0;
}

void linked_list_test() {
    printf("\nLINKED LIST:\n");

    struct LinkedListNode *list = linked_list_new("Hello");
    print_linked_list(list);

    linked_list_insertAt(linked_list_new("1", linked_list_new("2")), list, 0);
    print_linked_list(list);

    linked_list_insertAt(linked_list_new("3"), list, 1);
    print_linked_list(list);

    linked_list_insertAt(linked_list_new("4"), list, 1);
    print_linked_list(list);

    linked_list_append(linked_list_new("5"), list);
    print_linked_list(list);

    linked_list_connect_before(&list, linked_list_new("NEW", linked_list_new("HI")), linked_list_new("TEST"));
    print_linked_list(list);

    // REMOVE "HI"
    linked_list_removeAt(list, 2);
    print_linked_list(list);

    // INSERT CUSTOM AFTER NEXT ELEMENT OF NEW (+2)
    linked_list_insert(linked_list_new("CUSTOM"), list, "NEW", finder);
    print_linked_list(list);

    printf("\nITERATOR IN LINKED LIST:\n");
    struct Iterator *iter = linked_list_iterator(list);
    while (iterator_has_next(iter)) {
        printf("%s -> ", (char *) iterator_next(iter));
    }
    printf("\n");
    iterator_destroy(iter);
}

// *** HASH MAP ***
#include "hash_map.h"

void hash_map_test(){
    printf("\nHASH MAP:\n");
    struct HashMap *map = hash_map_create();
    hash_map_string_put(map, "Key1", "Item1");
    hash_map_string_put(map, "Key2", "Item2");
    hash_map_string_put(map, "Key3", "Item3");

    printf("Items Count: %d\n", hash_map_size(map));
    printf("Get Key1: %s\n", (char *) hash_map_string_get(map, "Key1"));

    printf("\nITERATOR IN HASH MAP (ENTRY):\n");
    struct Iterator *iter = hash_map_entryIterator(map);
    while (iterator_has_next(iter)) {
        struct HashMapEntry *entry = iterator_next(iter);
        printf("Key: %s, Value: %s\n", (char *) entry->key, (char *) entry->value);
    }
    iterator_destroy(iter);
}