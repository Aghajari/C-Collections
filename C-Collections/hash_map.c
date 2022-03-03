//
// Created by AmirHossein Aghajari on 3/3/22.
//

#include <stdlib.h>
#include "iterator.h"
#include "hash_map.h"
#include <string.h>

#define DEFAULT_INITIAL_CAPACITY (1 << 4)
#define DEFAULT_LOAD_FACTOR 0.75f
#define MAXIMUM_CAPACITY (1 << 30)

_Bool hash_map_compare(void *a, void *b) {
    return a == b;
}

_Bool hash_map_compareInteger(void *a, void *b) {
    return *(int *) a == *(int *) b;
}

_Bool hash_map_compareChar(void *a, void *b) {
    return *(char *) a == *(char *) b;
}

_Bool hash_map_compareString(void *a, void *b) {
    return strcmp(a, b) == 0;
}

int hash_integer(int value) {
    return value;
}

int hash_character(char value) {
    return (int) value;
}

int hash_string(const char *value) {
    int hash = 0;
    int index = 0;
    while (1) {
        if (value[index] == '\0')
            return hash;
        hash += 31 * hash + (int) value[index++];
    }
}

struct HashMapNode {
    int hash;
    void *key, *value;
    struct HashMapNode *next;
    int type;
};

int hash_map_key_hash(int key) {
    unsigned int h = key;
    return (int) (h ^ (h >> 16));
}

int hash_map_tableSizeFor(int cap) {
    cap -= 1;
    unsigned int leadingZeros;

    if (cap -= 0)
        leadingZeros = cap == 0 ? 32 : 0;
    else {
        unsigned int c = 31;
        unsigned int i = cap;
        if (i >= 1 << 16) { c -= 16; i >>= 16; }
        if (i >= 1 <<  8) { c -=  8; i >>=  8; }
        if (i >= 1 <<  4) { c -=  4; i >>=  4; }
        if (i >= 1 <<  2) { c -=  2; i >>=  2; }
        leadingZeros = c - (i >> 1);
    }

    int n = (int) ((unsigned int) 0xffffffff >> leadingZeros);
    return (n < 0) ? 1 : (n >= MAXIMUM_CAPACITY) ? MAXIMUM_CAPACITY : n + 1;
}

struct HashMap *hash_map_create3(int initialCapacity, float loadFactory) {
    if (initialCapacity < 0)
        initialCapacity = 0;
    else if (initialCapacity > MAXIMUM_CAPACITY)
        initialCapacity = MAXIMUM_CAPACITY;
    if (loadFactory <= 0)
        loadFactory = DEFAULT_LOAD_FACTOR;

    struct HashMap *map = malloc(sizeof(struct HashMap));
    map->loadFactor = loadFactory;
    map->table = NULL;
    map->size = map->capacity = 0;
    map->threshold = hash_map_tableSizeFor(initialCapacity);
    return map;
}

struct HashMap *hash_map_create2(int initialCapacity) {
    return hash_map_create3(initialCapacity, DEFAULT_LOAD_FACTOR);
}

struct HashMap *hash_map_create() {
    return hash_map_create3(DEFAULT_INITIAL_CAPACITY, DEFAULT_LOAD_FACTOR);
}

int hash_map_size(struct HashMap *_Nonnull map) {
    return map->size;
}

struct HashMapNode *hash_map_getNode(struct HashMap *map, int hashCode, void *key, _Bool (*compare)(void *, void *)) {
    hashCode = hash_map_key_hash(hashCode);
    struct HashMapNode *first, *e;
    int n, hash;
    void *k;

    if (map->table != NULL && (n = map->capacity) > 0 &&
        (first = map->table[(n - 1) & (hash = hashCode)]) != NULL) {
        if (first->hash == hash && // always check first node
            ((k = first->key) == key || (compare != NULL && compare(k, key))))
            return first;
        if ((e = first->next) != NULL) {
            do {
                if (e->hash == hash &&
                    ((k = e->key) == key || (compare != NULL && compare(k, key))))
                    return e;
            } while ((e = e->next) != NULL);
        }
    }
    return NULL;
}

void *hash_map_string_get(struct HashMap *map, char *key) {
    struct HashMapNode *e = hash_map_getNode(map, hash_string(key), key, hash_map_compareString);
    return e == NULL ? NULL : e->value;
}

void *hash_map_int_get(struct HashMap *map, int key) {
    struct HashMapNode *e = hash_map_getNode(map, hash_integer(key), &key, hash_map_compareInteger);
    return e == NULL ? NULL : e->value;
}

void *hash_map_char_get(struct HashMap *map, char key) {
    struct HashMapNode *e = hash_map_getNode(map, hash_character(key), &key, hash_map_compareChar);
    return e == NULL ? NULL : e->value;
}

void *hash_map_get(struct HashMap *map, void *key) {
    struct HashMapNode *e = hash_map_getNode(map, (int) (long) key, key, hash_map_compare);
    return e == NULL ? NULL : e->value;
}

void *hash_map_get2(struct HashMap *map, void *key, int hashCode, _Bool (*compare)(void *, void *)) {
    struct HashMapNode *e = hash_map_getNode(map, hashCode, key, compare);
    return e == NULL ? NULL : e->value;
}

struct HashMapNode *hash_map_createNode(int hash, void *key, void *value, struct HashMapNode *next, int type) {
    struct HashMapNode *node = malloc(sizeof(struct HashMapNode));
    node->next = next;
    node->key = key;
    node->value = value;
    node->hash = hash;
    node->type = type;
    return node;
}

void hash_map_resize(struct HashMap *map) {
    void **oldTab = map->table;
    int oldCap = (oldTab == NULL) ? 0 : map->capacity;
    int oldThr = map->threshold;
    int newCap, newThr = 0;
    if (oldCap > 0) {
        if (oldCap >= MAXIMUM_CAPACITY) {
            map->threshold = INT32_MAX;
            return;
        } else if ((newCap = oldCap << 1) < MAXIMUM_CAPACITY &&
                   oldCap >= DEFAULT_INITIAL_CAPACITY)
            newThr = oldThr << 1; // double threshold
    } else if (oldThr > 0) // initial capacity was placed in threshold
        newCap = oldThr;
    else {               // zero initial threshold signifies using defaults
        newCap = DEFAULT_INITIAL_CAPACITY;
        newThr = (int) (DEFAULT_LOAD_FACTOR * DEFAULT_INITIAL_CAPACITY);
    }
    if (newThr == 0) {
        float ft = (float) newCap * map->loadFactor;
        newThr = (newCap < MAXIMUM_CAPACITY && ft < (float) MAXIMUM_CAPACITY ?
                  (int) ft : INT32_MAX);
    }
    map->threshold = newThr;

    void **newTab = calloc(newCap, sizeof(void *));
    map->capacity = newCap;
    map->table = newTab;
    if (oldTab != NULL) {
        for (int j = 0; j < oldCap; ++j) {
            struct HashMapNode *e;
            if ((e = oldTab[j]) != NULL) {
                oldTab[j] = NULL;
                if (e->next == NULL)
                    newTab[e->hash & (newCap - 1)] = e;
                else {
                    struct HashMapNode *loHead = NULL, *loTail = NULL;
                    struct HashMapNode *hiHead = NULL, *hiTail = NULL;
                    struct HashMapNode *next;
                    do {
                        next = e->next;
                        if ((e->hash & oldCap) == 0) {
                            if (loTail == NULL)
                                loHead = e;
                            else
                                loTail->next = e;
                            loTail = e;
                        } else {
                            if (hiTail == NULL)
                                hiHead = e;
                            else
                                hiTail->next = e;
                            hiTail = e;
                        }
                    } while ((e = next) != NULL);
                    if (loTail != NULL) {
                        loTail->next = NULL;
                        newTab[j] = loHead;
                    }
                    if (hiTail != NULL) {
                        hiTail->next = NULL;
                        newTab[j + oldCap] = hiHead;
                    }
                }
            }
        }
    }
    free(oldTab);
}

void *hash_map_putVal(struct HashMap *map, int hash, void *key, void *value, _Bool (*compare)(void *, void *),
                      int type) {
    hash = hash_map_key_hash(hash);
    struct HashMapNode *p;
    int n, i;
    if (map->table == NULL || (n = map->capacity) == 0) {
        hash_map_resize(map);
        n = map->capacity;
    }
    if ((p = map->table[i = (n - 1) & hash]) == NULL)
        map->table[i] = hash_map_createNode(hash, key, value, NULL, type);
    else {
        struct HashMapNode *e;
        void *k;
        if (p->hash == hash &&
            ((k = p->key) == key || (compare != NULL && compare(k, key))))
            e = p;
        else {
            for (int binCount = 0;; ++binCount) {
                if ((e = p->next) == NULL) {
                    p->next = hash_map_createNode(hash, key, value, NULL, type);
                    break;
                }
                if (e->hash == hash &&
                    ((k = e->key) == key || (compare != NULL && compare(k, key))))
                    break;
                p = e;
            }
        }
        if (e != NULL) { // existing mapping for key
            void *oldValue = e->value;
            e->value = value;
            return oldValue;
        }
    }
    if (++map->size > map->threshold)
        hash_map_resize(map);

    return NULL;
}

void *hash_map_string_put(struct HashMap *map, char *key, void *value) {
    char *keyCopy = malloc(strlen(key) + 1);
    strcpy(keyCopy, key);
    return hash_map_putVal(map, hash_string(keyCopy), keyCopy, value, hash_map_compareString, 1);
}

void *hash_map_int_put(struct HashMap *map, int key, void *value) {
    int *k = malloc(sizeof(int));
    *k = key;
    return hash_map_putVal(map, hash_integer(key), k, value, hash_map_compareInteger, 2);
}

void *hash_map_char_put(struct HashMap *map, char key, void *value) {
    char *k = malloc(sizeof(char));
    *k = key;
    return hash_map_putVal(map, hash_character(key), k, value, hash_map_compareChar, 3);
}

void *hash_map_put(struct HashMap *map, void *key, void *value) {
    return hash_map_putVal(map, (int) (long) key, key, value, hash_map_compare, 0);
}

void *hash_map_put2(struct HashMap *map, void *key, void *value, int hashCode, _Bool (*compare)(void *, void *)) {
    return hash_map_putVal(map, hashCode, key, value, compare, 0);
}

_Bool hash_map_string_containsKey(struct HashMap *map, char *key) {
    return hash_map_getNode(map, hash_string(key), key, hash_map_compareString) != NULL;
}

_Bool hash_map_int_containsKey(struct HashMap *map, int key) {
    return hash_map_getNode(map, hash_integer(key), &key, hash_map_compareInteger) != NULL;
}

_Bool hash_map_char_containsKey(struct HashMap *map, char key) {
    return hash_map_getNode(map, hash_character(key), &key, hash_map_compareChar) != NULL;
}

_Bool hash_map_containsKey(struct HashMap *map, void *key) {
    return hash_map_getNode(map, (int) (long) key, key, hash_map_compare) != NULL;
}

_Bool hash_map_containsKey2(struct HashMap *map, void *key, int hashCode, _Bool (*compare)(void *, void *)) {
    return hash_map_getNode(map, hashCode, key, compare) != NULL;
}

void *hash_map_removeNode(struct HashMap *map, int hash, void *key, _Bool (*compare)(void *, void *)) {
    hash = hash_map_key_hash(hash);

    struct HashMapNode *p;
    int n, index;
    if ((map->table) != NULL && (n = map->capacity) > 0 &&
        (p = map->table[index = (n - 1) & hash]) != NULL) {
        struct HashMapNode *node = NULL, *e;
        void *k;

        if (p->hash == hash &&
            ((k = p->key) == key || (compare != NULL && compare(k, key))))
            node = p;
        else if ((e = p->next) != NULL) {
            do {
                if (e->hash == hash &&
                    ((k = e->key) == key ||
                     (compare != NULL && compare(k, key)))) {
                    node = e;
                    break;
                }
                p = e;
            } while ((e = e->next) != NULL);
        }
        if (node != NULL) {
            if (node == p)
                map->table[index] = node->next;
            else
                p->next = node->next;
            map->size--;
            void *v = node->value;
            if (node->type != 0)
                free(node->key);
            free(node);
            return v;
        }
    }
    return NULL;
}

void *hash_map_string_remove(struct HashMap *map, char *key) {
    return hash_map_removeNode(map, hash_string(key), key, hash_map_compareString);
}

void *hash_map_int_remove(struct HashMap *map, int key) {
    return hash_map_removeNode(map, hash_integer(key), &key, hash_map_compareInteger);
}

void *hash_map_char_remove(struct HashMap *map, char key) {
    return hash_map_removeNode(map, hash_character(key), &key, hash_map_compareChar);
}

void *hash_map_remove(struct HashMap *map, void *key) {
    return hash_map_removeNode(map, (int) (long) key, key, hash_map_compare);
}

void *hash_map_remove2(struct HashMap *map, void *key, int hashCode, _Bool (*compare)(void *, void *)) {
    return hash_map_removeNode(map, hashCode, key, compare);
}

_Bool hash_map_containsValue(struct HashMap *map, void *value) {
    if (map->table != NULL && map->size > 0) {
        for (int i = 0; i < map->capacity; i++) {
            struct HashMapNode *e = map->table[i];
            for (; e != NULL; e = e->next) {
                if (e->value == value)
                    return 1;
            }
        }
    }
    return 0;
}

void hash_map_putAll(struct HashMap *map, struct HashMap *src) {
    int s = src->size;
    if (s > 0) {
        if (map->table == NULL) { // pre-size
            float ft = ((float) s / map->loadFactor) + 1.0F;
            int t = ((ft < (float) MAXIMUM_CAPACITY) ?
                     (int) ft : MAXIMUM_CAPACITY);
            if (t > map->threshold)
                map->threshold = hash_map_tableSizeFor(t);
        } else {
            while (s > map->threshold && map->capacity < MAXIMUM_CAPACITY)
                hash_map_resize(map);
        }

        struct Iterator *iter = hash_map_entryIterator(map);
        while (iterator_has_next(iter)) {
            struct HashMapNode *node = iterator_next(iter);
            if (node->type == 1) {
                hash_map_string_put(map, node->key, node->value);
            } else if (node->type == 2) {
                hash_map_int_put(map, *(int *) (node->key), node->value);
            } else if (node->type == 3) {
                hash_map_char_put(map, *(char *) (node->key), node->value);
            } else {
                hash_map_put(map, node->key, node->value);
            }
        }
        iterator_destroy(iter);
    }
}

struct HashMapIterator {
    struct HashMap *map;
    struct HashMapNode *next, *current;
    int index, passed;
};

_Bool hash_map_iterator_has_next(struct Iterator *iterator) {
    struct HashMapIterator *data = iterator->data;
    return data->next != NULL;
}

struct HashMapNode *hash_map_iterator_nextNode(struct HashMapIterator *data) {
    struct HashMapNode *e = data->next;
    if ((data->next = (data->current = e)->next) == NULL && data->map->table != NULL) {
        do {} while (data->index < data->map->capacity && (data->next = data->map->table[data->index++]) == NULL);
    }
    data->passed++;
    return e;
}

void *hash_map_iterator_next(struct Iterator *iterator) {
    return hash_map_iterator_nextNode(iterator->data);
}

void *hash_map_iterator_nextKey(struct Iterator *iterator) {
    return hash_map_iterator_nextNode(iterator->data)->key;
}

void *hash_map_iterator_nextValue(struct Iterator *iterator) {
    return hash_map_iterator_nextNode(iterator->data)->value;
}

void hash_map_iterator_remove(struct Iterator *iterator) {
    struct HashMapIterator *data = iterator->data;
    struct HashMapNode *p = data->current;
    data->current = NULL;
    hash_map_removeNode(data->map, p->hash, p->key, NULL);
}

int hash_map_iterator_size(struct Iterator *iterator) {
    struct HashMapIterator *data = iterator->data;
    return data->map->size - data->passed;
}

void hash_map_iterator_destroy(struct Iterator *iterator) {
    free(iterator->data);
    free(iterator);
}

struct Iterator *hash_map_entryIterator(struct HashMap *map) {
    struct Iterator *iter = malloc(sizeof(struct Iterator));
    struct HashMapIterator *data = malloc(sizeof(struct HashMapIterator));

    data->map = map;
    data->current = data->next = NULL;
    data->index = data->passed = 0;
    if (map->table != NULL && map->size > 0) { // advance to first entry
        do {} while (data->index < map->capacity && (data->next = map->table[data->index++]) == NULL);
    }

    iter->data = data;
    iter->has_next = hash_map_iterator_has_next;
    iter->next = hash_map_iterator_next;
    iter->remove = hash_map_iterator_remove;
    iter->destroy = hash_map_iterator_destroy;
    iter->size = hash_map_iterator_size;
    return iter;
}

struct Iterator *hash_map_keyIterator(struct HashMap *map) {
    struct Iterator *iter = hash_map_entryIterator(map);
    iter->next = hash_map_iterator_nextKey;
    return iter;
}

struct Iterator *hash_map_valueIterator(struct HashMap *map) {
    struct Iterator *iter = hash_map_entryIterator(map);
    iter->next = hash_map_iterator_nextValue;
    return iter;
}

void **hash_map_keysToArray(struct HashMap *map) {
    if (map->size > 0 && map->table != NULL) {
        void **arr = malloc(map->size * sizeof(void *));
        int idx = 0;
        for (int i = 0; i < map->capacity; ++i) {
            struct HashMapNode *e = map->table[i];
            for (; e != NULL; e = e->next) {
                arr[idx++] = e->key;
            }
        }
        return arr;
    }
    return NULL;
}

void **hash_map_valuesToArray(struct HashMap *map) {
    if (map->size > 0 && map->table != NULL) {
        void **arr = malloc(map->size * sizeof(void *));
        int idx = 0;
        for (int i = 0; i < map->capacity; ++i) {
            struct HashMapNode *e = map->table[i];
            for (; e != NULL; e = e->next) {
                arr[idx++] = e->value;
            }
        }
        return arr;
    }
    return NULL;
}

void **hash_map_entriesToArray(struct HashMap *map) {
    if (map->size > 0 && map->table != NULL) {
        void **arr = malloc(map->size * sizeof(void *));
        int idx = 0;
        for (int i = 0; i < map->capacity; ++i) {
            struct HashMapNode *e = map->table[i];
            for (; e != NULL; e = e->next) {
                arr[idx++] = e;
            }
        }
        return arr;
    }
    return NULL;
}

void hash_map_clear(struct HashMap *map) {
    if (map->table != NULL && map->size > 0) {
        for (int i = 0; i < map->capacity; ++i) {
            struct HashMapNode *e = map->table[i], *e2;
            while (e != NULL) {
                if (e->type != 0)
                    free(e->key);
                e2 = e;
                e = e->next;
                free(e2);
            }
            map->table[i] = NULL;
        }
        map->size = 0;
    }
}

