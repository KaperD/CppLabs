#include "clist.h"

void init_list(intrusive_list* list) {
  list->head = NULL;
}

void add_node(intrusive_list* list, intrusive_node* node) {
  node->next = list->head;
  if (list->head != NULL) {
    list->head->prev = node;
  }
  list->head = node;
}

void remove_node(intrusive_list* list, intrusive_node* node) {
  if (list->head == node) {
    list->head = node->next;
  } else if (node->next == NULL) {
    node->prev->next = NULL;
  } else {
    node->prev->next = node->next;
    node->next->prev = node->prev;
  }
}

int get_length(intrusive_list* list) {
  int len = 0;
  intrusive_node* node = list->head;
  while (node != NULL) {
    len++;
    node = node->next;
  }
  return len;
}