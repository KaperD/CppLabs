#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "clist.h"

typedef struct point {
  int x, y;
  struct intrusive_node node;
} point;

void add_point(intrusive_list *list, int x, int y) {
  point *p = malloc(sizeof(point));
  assert(p != NULL);
  p->x = x;
  p->y = y;
  add_node(list, &p->node);
}

void remove_point(intrusive_list *list, int x, int y) {
  intrusive_node *n = list->head;
  while (n != NULL) {
    point *p = container_of(n, point, node);
    n = n->next;
    if (p->x == x && p->y == y) {
      remove_node(list, &p->node);
      free(p);
    }
  }
}

void show_all_points(intrusive_list *list) {
  intrusive_node *n = list->head;
  while (n != NULL) {
    point *p = container_of(n, point, node);
    printf("(%d %d) ", p->x, p->y);
    n = n->next;
  }
}

void remove_all_points(intrusive_list *list) {
  intrusive_node *n = list->head;
  while (n != NULL) {
    point *p = container_of(n, point, node);
    n = n->next;
    free(p);
  }
  list->head = NULL;
}

int main() {
  intrusive_list l;
  init_list(&l);

  char str[6];
  int x, y;

  while (1) {
    scanf("%5s", str);
    if (!strcmp(str, "exit")) {
      remove_all_points(&l);
      break;
    } else if (!strcmp(str, "add")) {
      scanf("%d %d", &x, &y);
      add_point(&l, x, y);
    } else if (!strcmp(str, "rm")) {
      scanf("%d %d", &x, &y);
      remove_point(&l, x, y);
    } else if (!strcmp(str, "print")) {
      show_all_points(&l);
      printf("\n");
    } else if (!strcmp(str, "rma")) {
      remove_all_points(&l);
    } else if (!strcmp(str, "len")) {
      printf("%d\n", get_length(&l));
    } else {
      printf("Unknown command\n");
    }
  }

  return 0;
}