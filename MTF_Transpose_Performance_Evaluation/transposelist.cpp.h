//
// Created by Alex Hayden van Zuiden-Rylander on 2019-02-25.
//

#ifndef TRANSPOSELIST_TRANSPOSELIST_CPP_H
#define TRANSPOSELIST_TRANSPOSELIST_CPP_H

template<class Object>
int TransposeList<Object>::find(const Object &obj) {
    DListNode<Object> *found = DList<Object>::header->next;

    int i = 0;
    for (; found != NULL && found->item != obj; found = found->next, ++i)
        ++DList<Object>::cost;

    if (found == NULL)
        return -1; // not found

    if (found == DList<Object>::header->next)
        return 0;  // no need to swap

    // remove found from the current position
    found->prev->next = found->next;
    if (found->next != NULL)
        found->next->prev = found->prev;
    // insert found before previous
    found->next = found->prev;
    found->next->prev->next = found;
    found->prev = found->next->prev;
    found->next->prev = found;

    return i;
}

#endif //TRANSPOSELIST_TRANSPOSELIST_CPP_H
