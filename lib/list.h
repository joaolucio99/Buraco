#ifndef LIST
#define LIST
#include "tools.h"
#include "structs.h"

    list*new_list();

    int list_is_empty();

    int list_insert();

    int list_remove();

    int list_insert_pos();

    int list_remove_pos();

    int list_count_size();

    int list_search_key();

    int list_search_pos();

    void list_print();

    void list_free();

#endif  