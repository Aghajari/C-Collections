//
// Created by AmirHossein Aghajari on 3/3/22.
//

#ifndef HASH_MAP_H
#define HASH_MAP_H

struct HashMap {
    void *_Nullable *_Nullable table;
    int size, threshold, capacity;
    float loadFactor;
};

struct HashMapEntry {
    int hashCode;
    void *key, *value;
    void *next_hash;
    int type;
};

/**
 * Creates an empty HashMap with the default initial capacity
 * (16) and the default load factor (0.75).
 */
struct HashMap *hash_map_create();

/**
 * Creates an empty HashMap with the specified initial
 * capacity and the default load factor (0.75).
 */
struct HashMap *hash_map_create2(int initialCapacity);

/**
 * Creates an empty HashMap with the specified initial
 * capacity and load factor.
 */
struct HashMap *hash_map_create3(int initialCapacity, float loadFactory);

/**
 * Returns the number of key-value mappings in the map.
 */
int hash_map_size(struct HashMap *_Nonnull map);

/**
 * Returns an array filled with the map keys.
 */
void **hash_map_keysToArray(struct HashMap *map);

/**
 * Returns an array filled with the map values.
 */
void **hash_map_valuesToArray(struct HashMap *map);

/**
 * Returns an array filled with the map entries (HashMapEntry).
 */
void **hash_map_entriesToArray(struct HashMap *map);

/**
 * Returns the value to which the specified string key is mapped,
 * or NULL if the map contains no mapping for the key.
 */
void * hash_map_string_get(struct HashMap *map, char *key);

/**
 * Returns the value to which the specified integer key is mapped,
 * or NULL if the map contains no mapping for the key.
 */
void * hash_map_int_get(struct HashMap *map, int key);

/**
 * Returns the value to which the specified character key is mapped,
 * or NULL if the map contains no mapping for the key.
 */
void * hash_map_char_get(struct HashMap *map, char key);

/**
 * Returns the value to which the specified key is mapped,
 * or NULL if the map contains no mapping for the key.
 */
void * hash_map_get(struct HashMap *map, void *key);
void * hash_map_get2(struct HashMap *map, void *key, int hashCode, _Bool (*compare)(void *, void *));

/**
 * Associates the specified value with the specified string key in the map.
 * If the map previously contained a mapping for the key, the old
 * value is replaced.
 */
void * hash_map_string_put(struct HashMap *map, char *key, void *value);

/**
 * Associates the specified value with the specified integer key in the map.
 * If the map previously contained a mapping for the key, the old
 * value is replaced.
 */
void * hash_map_int_put(struct HashMap *map, int key, void *value);

/**
 * Associates the specified value with the specified character key in the map.
 * If the map previously contained a mapping for the key, the old
 * value is replaced.
 */
void * hash_map_char_put(struct HashMap *map, char key, void *value);

/**
 * Associates the specified value with the specified key in the map.
 * If the map previously contained a mapping for the key, the old
 * value is replaced.
 */
void * hash_map_put(struct HashMap *map, void *key, void *value);
void * hash_map_put2(struct HashMap *map, void *key, void *value, int hashCode, _Bool (*compare)(void *, void *));

/**
 * Copies all of the mappings from the specified map to the map.
 * These mappings will replace any mappings that the map had for
 * any of the keys currently in the specified map.
 */
void hash_map_putAll(struct HashMap *map, struct HashMap *src);

/**
 * Returns true (1) if the map contains a mapping for the
 * specified string key.
 */
_Bool hash_map_string_containsKey(struct HashMap *map, char *key);

/**
 * Returns true (1) if the map contains a mapping for the
 * specified integer key.
 */
_Bool hash_map_int_containsKey(struct HashMap *map, int key);

/**
 * Returns true (1) if the map contains a mapping for the
 * specified character key.
 */
_Bool hash_map_char_containsKey(struct HashMap *map, char key);

/**
 * Returns true (1) if the map contains a mapping for the
 * specified key.
 */
_Bool hash_map_containsKey(struct HashMap *map, void *key);
_Bool hash_map_containsKey2(struct HashMap *map, void *key, int hashCode, _Bool (*compare)(void *, void *));

/**
 * Returns true (1) if the map maps one or more keys to the
 * specified value.
 */
_Bool hash_map_containsValue(struct HashMap *map, void *value);

/**
 * Removes the mapping for the specified string key from the map if present.
 */
void *hash_map_string_remove(struct HashMap *map, char *key);

/**
 * Removes the mapping for the specified integer key from the map if present.
 */
void *hash_map_int_remove(struct HashMap *map, int key);

/**
 * Removes the mapping for the specified character key from the map if present.
 */
void *hash_map_char_remove(struct HashMap *map, char key);

/**
 * Removes the mapping for the specified key from the map if present.
 * @return the previous value associated with key, or
 *         NULL if there was no mapping for key.
 *         (A NULL return can also indicate that the map
 *         previously associated NULL with key.)
 */
void *hash_map_remove(struct HashMap *map, void *key);
void *hash_map_remove2(struct HashMap *map, void *key, int hashCode, _Bool (*compare)(void *, void *));

/**
* Returns an iterator over the map entries (HashMapEntry).
*/
struct Iterator *hash_map_entryIterator(struct HashMap *map);

/**
* Returns an iterator over the map keys.
*/
struct Iterator *hash_map_keyIterator(struct HashMap *map);

/**
* Returns an iterator over the map values.
*/
struct Iterator *hash_map_valueIterator(struct HashMap *map);

/**
 * Removes and destroys all of the mappings from the map.
 * The map will be empty after this call returns.
 */
void hash_map_clear(struct HashMap *map);

#endif //HASH_MAP_H
