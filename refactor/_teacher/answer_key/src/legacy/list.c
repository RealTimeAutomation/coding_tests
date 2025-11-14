#include "list.h"
#include <stdlib.h>
#include <string.h>

int_list* list_create(void) {
    int_list* list = (int_list*)malloc(sizeof(int_list));
    if (!list) return NULL;

    list->head = NULL;
    list->size = 0;
    return list;
}

void list_destroy(int_list* list) {
    if (list == NULL) {
        return;
    }
    
    list_node* current = list->head;
    while (current != NULL) {
        list_node* next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

void list_append(int_list* list, int value) {
    if (list == NULL) {
        return;
    }
    
    list_node* new_node = (list_node*)malloc(sizeof(list_node));
    if (!new_node) return;

    new_node->data = value;
    new_node->next = NULL;
    
    if (list->head == NULL) {
        list->head = new_node;
    } else {
        list_node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    list->size++;
}

void list_insert(int_list* list, size_t index, int value) {
    if (list == NULL) {
        return;
    }
    
    list_node* new_node = (list_node*)malloc(sizeof(list_node));
    if (!new_node) return;

    new_node->data = value;
    
    if (index == 0) {
        new_node->next = list->head;
        list->head = new_node;
        list->size++;
    } else if (index >= list->size) {
        list_append(list, value);
    } else {
        list_node* current = list->head;
        for (size_t i = 0; i < index - 1; ++i) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
        list->size++;
    }
}

int list_remove_at(int_list* list, size_t index) {
    if (list == NULL || list->head == NULL || index >= list->size) {
        return 0;
    }
    
    int value;
    if (index == 0) {
        list_node* to_remove = list->head;
        value = to_remove->data;
        list->head = to_remove->next;
        free(to_remove);
        list->size--;
    } else {
        list_node* current = list->head;
        for (size_t i = 0; i < index - 1; ++i) {
            current = current->next;
        }
        list_node* to_remove = current->next;
        value = to_remove->data;
        current->next = to_remove->next;
        free(to_remove);
        list->size--;
    }
    return value;
}

int list_get(const int_list* list, size_t index) {
    if (list == NULL || index >= list->size) {
        return 0;
    }

    list_node* current = list->head;
    for (size_t i = 0; i < index; ++i) {
        current = current->next;
    }
    return current->data;
}

int list_find(const int_list* list, int value) {
    if (list == NULL) {
        return -1;
    }
    
    list_node* current = list->head;
    int index = 0;

    while (current != NULL) {
        if (current->data == value) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;
}

void list_reverse(int_list* list) {
    if (list == NULL || list->head == NULL || list->head->next == NULL) {
        return;
    }

    list_node* prev = NULL;
    list_node* current = list->head;
    list_node* next = NULL;
    
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    list->head = prev;
}

void list_sort(int_list* list) {
    if (list == NULL || list->head == NULL || list->head->next == NULL) {
        return;
    }

    int swapped = 1;
    while (swapped) {
        swapped = 0;
        list_node* current = list->head;
        list_node* prev = NULL;
        
        while (current != NULL && current->next != NULL) {
            if (current->data > current->next->data) {
                list_node* next = current->next;
                if (prev == NULL) {
                    list->head = next;
                } else {
                    prev->next = next;
                }
                current->next = next->next;
                next->next = current;
                swapped = 1;
                prev = next;
            } else {
                prev = current;
                current = current->next;
            }
        }
    }
}

int_list* list_merge_sorted(const int_list* a, const int_list* b) {
    if (a == NULL || b == NULL) {
        return NULL;
    }
    
    int_list* result = list_create();
    if (!result) return NULL;

    list_node* current_a = a->head;
    list_node* current_b = b->head;
    
    while (current_a != NULL && current_b != NULL) {
        if (current_a->data <= current_b->data) {
            list_append(result, current_a->data);
            current_a = current_a->next;
        } else {
            list_append(result, current_b->data);
            current_b = current_b->next;
        }
    }

    while (current_a != NULL) {
        list_append(result, current_a->data);
        current_a = current_a->next;
    }
    
    while (current_b != NULL) {
        list_append(result, current_b->data);
        current_b = current_b->next;
    }
    
    return result;
}

