//
// Created by AmirHossein Aghajari on 2/25/22.
//

#ifndef ITERATOR_H
#define ITERATOR_H

struct Iterator {
    void *_Nullable data;
    _Bool (*_Nonnull has_next)(struct Iterator *_Nonnull iterator);
    void *_Nullable (*_Nonnull next)(struct Iterator *_Nonnull iterator);
    void (*_Nullable remove)(struct Iterator *_Nonnull iterator);
    void (*_Nonnull destroy)(struct Iterator *_Nonnull iterator);
    int (*_Nullable size)(struct Iterator *_Nonnull iterator);
};

_Bool iterator_has_next(struct Iterator *_Nonnull iterator);
void *_Nullable iterator_next(struct Iterator *_Nonnull iterator);
void iterator_remove(struct Iterator *_Nonnull iterator);
void iterator_destroy(struct Iterator *_Nonnull iterator);
int iterator_size(struct Iterator *_Nonnull iterator);

struct Iterator *_Nonnull iterator_create(void *_Nullable*_Nullable elements, int size);
#endif //ITERATOR_H
