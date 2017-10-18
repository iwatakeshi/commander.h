#ifndef COMMANDER_H
#define COMMANDER_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static struct node {
  int id;
  char* flag;
  char* name;
  char* format;
  void* value;
  bool valuable;
  struct node* next;
} Node;

static int node_id = 1;

typedef void (*callback)(struct node* n);

/**
 * Linked List
 * Credits: http://www.zentut.com/c-tutorial/c-linked-list/
 */

/*
    create a new node
    initialize the flag and next field
 
    return the newly created node
*/
static struct node* create(char* flag, struct node* next) {
  struct node* new_node = (struct node*)malloc(sizeof(struct node));
  if (new_node == NULL) {
    printf("Error creating a new node.\n");
    exit(0);
  }
  new_node->id = node_id;
  new_node->flag = flag;
  new_node->next = next;
  new_node->valuable = false;
  node_id++;
  return new_node;
}

static struct node* create_with_value(char* format, struct node* next) {
  struct node* new_node = (struct node*)malloc(sizeof(struct node));
  if (new_node == NULL) {
    printf("Error creating a new node.\n");
    exit(0);
  }
  new_node->id = node_id;
  new_node->next = next;
  new_node->format = format;
  new_node->valuable = true;
  node_id++;
  return new_node;
}

static struct node* create_with_name(char* flag, char* name, struct node* next) {
  struct node* new_node = (struct node*)malloc(sizeof(struct node));
  if (new_node == NULL) {
    printf("Error creating a new node.\n");
    exit(0);
  }

  new_node->id = node_id;
  new_node->flag = flag;
  new_node->name = name;
  new_node->next = next;
  new_node->valuable = false;
  node_id++;
  return new_node;
}

static struct node* create_with_name_and_value(char* flag, char* name, char* format, struct node* next) {
  struct node* new_node = (struct node*)malloc(sizeof(struct node));
  if (new_node == NULL) {
    printf("Error creating a new node.\n");
    exit(0);
  }

  new_node->id = node_id;
  new_node->flag = flag;
  new_node->name = name;
  new_node->next = next;
  new_node->format = format;
  new_node->valuable = true;
  node_id++;
  return new_node;
}

/*
    add a new node at the beginning of the list
*/
static struct node* prepend(struct node* head, char* flag) {
  struct node* new_node = create(flag, head);
  head = new_node;
  return head;
}

/*
    add a new node at the end of the list
*/
static struct node* append(struct node* head, char* flag) {
  if (head == NULL)
    return NULL;
  /* go to the last node */
  struct node* cursor = head;
  while (cursor->next != NULL)
    cursor = cursor->next;

  /* create a new node */
  struct node* new_node = create(flag, NULL);
  cursor->next = new_node;

  return head;
}
static struct node* append_with_value(struct node* head, char* format) {
  if (head == NULL)
    return NULL;
  /* go to the last node */
  struct node* cursor = head;
  while (cursor->next != NULL)
    cursor = cursor->next;

  /* create a new node */
  struct node* new_node = create_with_value(format, NULL);
  cursor->next = new_node;

  return head;
}

static struct node* append_with_name(struct node* head, char* flag, char* name) {
  if (head == NULL)
    return NULL;
  /* go to the last node */
  struct node* cursor = head;
  while (cursor->next != NULL)
    cursor = cursor->next;

  /* create a new node */
  struct node* new_node = create_with_name(flag, name, NULL);
  cursor->next = new_node;

  return head;
}

/*
    insert a new node after the prev node
*/
static struct node* insert_after(struct node* head, char* flag, struct node* prev) {
  if (head == NULL || prev == NULL)
    return NULL;
  /* find the prev node, starting from the first struct node*/
  struct node* cursor = head;
  while (cursor != prev)
    cursor = cursor->next;

  if (cursor != NULL) {
    struct node* new_node = create(flag, cursor->next);
    cursor->next = new_node;
    return head;
  } else {
    return NULL;
  }
}

/*
    insert a new node before the nxt node
*/
static struct node* insert_before(struct node* head, char* flag, struct node* nxt) {
  if (nxt == NULL || head == NULL)
    return NULL;

  if (head == nxt) {
    head = prepend(head, flag);
    return head;
  }

  /* find the prev node, starting from the first struct node*/
  struct node* cursor = head;
  while (cursor != NULL) {
    if (cursor->next == nxt)
      break;
    cursor = cursor->next;
  }

  if (cursor != NULL) {
    struct node* new_node = create(flag, cursor->next);
    cursor->next = new_node;
    return head;
  } else {
    return NULL;
  }
}

/*
    traverse the linked list
*/
static void traverse(struct node* head, callback f) {
  struct node* cursor = head;
  while (cursor != NULL) {
    f(cursor);
    cursor = cursor->next;
  }
}
/*
    remove node from the front of list
*/
static struct node* remove_front(struct node* head) {
  if (head == NULL)
    return NULL;
  struct node* front = head;
  head = head->next;
  front->next = NULL;
  /* is this the last node in the list */
  if (front == head)
    head = NULL;
  free(front);
  return head;
}

/*
    remove node from the back of the list
*/
static struct node* remove_back(struct node* head) {
  if (head == NULL)
    return NULL;

  struct node* cursor = head;
  struct node* back = NULL;
  while (cursor->next != NULL) {
    back = cursor;
    cursor = cursor->next;
  }

  if (back != NULL)
    back->next = NULL;

  /* if this is the last node in the list*/
  if (cursor == head)
    head = NULL;

  free(cursor);

  return head;
}

/*
    remove a node from the list
*/
static struct node* remove_any(struct node* head, struct node* nd) {
  if (nd == NULL)
    return NULL;
  /* if the node is the first node */
  if (nd == head)
    return remove_front(head);

  /* if the node is the last node */
  if (nd->next == NULL)
    return remove_back(head);

  /* if the node is in the middle */
  struct node* cursor = head;
  while (cursor != NULL) {
    if (cursor->next == nd)
      break;
    cursor = cursor->next;
  }

  if (cursor != NULL) {
    struct node* tmp = cursor->next;
    cursor->next = tmp->next;
    tmp->next = NULL;
    free(tmp);
  }
  return head;
}
/*
    display a node
*/

static void display_callback(struct node* n) {
  char format[100];
  if (n->flag != NULL && n->name != NULL) {
    printf("%d, %s, %s\n", n->id, n->flag, n->name);
  }
  else if (n->flag != NULL && n->name != NULL && n->value != NULL) {
    printf("%d, %s, %s, %p\n", n->id, n->flag, n->name, n->value);
  }
  else if(n->value != NULL) {
    printf("%d, %p\n", n->id, n->value);
  }
}

static void display(struct node* n) {
  if (n != NULL)
    display_callback(n);
}

static void display_all(struct node* n) {
  traverse(n, display_callback);
}

/*
    Search for a specific node with input flag
 
    return the first matched node that stores the input flag,
    otherwise return NULL
*/

static struct node* search_by_flag_and_name(struct node* head, char* flag, char* name) {

  struct node* cursor = head;
  while (cursor != NULL) {
    if (cursor->flag != NULL && cursor->name != NULL) {
      printf("here\n");
      if (strcmp(cursor->flag, flag) == 0 && strcmp(cursor->name, name) == 0)
      return cursor;
    }
    cursor = cursor->next;
  }
  return NULL;
}

static struct node* search_by_flag(struct node* head, char* flag) {

  struct node* cursor = head;
  while (cursor != NULL) {
    if (cursor->flag != NULL) {
      if (strcmp(cursor->flag, flag) == 0)
      return cursor;
    }
    cursor = cursor->next;
  }
  return NULL;
}

static struct node* search_by_name(struct node* head, char* name) {

  struct node* cursor = head;
  while (cursor != NULL) {
    if (strcmp(cursor->name, name) == 0)
      return cursor;
    cursor = cursor->next;
  }
  return NULL;
}

static struct node* search_by_id(struct node* head, int id) {
  struct node* cursor = head;
  while (cursor != NULL) {
    if (cursor->id == id)
      return cursor;
    cursor = cursor->next;
  }
  return NULL;
}

/*
    remove all element of the list
*/
static void dispose(struct node* head) {
  struct node *cursor, *tmp;

  if (head != NULL) {
    cursor = head->next;
    head->next = NULL;
    while (cursor != NULL) {
      tmp = cursor->next;
      free(cursor);
      cursor = tmp;
    }
  }
}
/*
    return the number of elements in the list
*/
static int count(struct node* head) {
  struct node* cursor = head;
  int c = 0;
  while (cursor != NULL) {
    c++;
    cursor = cursor->next;
  }
  return c;
}
/*
    sort the linked list using insertion sort
*/
static struct node* insertion_sort(struct node* head) {
  struct node *x, *y, *e;

  x = head;
  head = NULL;

  while (x != NULL) {
    e = x;
    x = x->next;
    if (head != NULL) {
      if (e->flag > head->flag) {
        y = head;
        while ((y->next != NULL) && (e->flag > y->next->flag)) {
          y = y->next;
        }
        e->next = y->next;
        y->next = e;
      } else {
        e->next = head;
        head = e;
      }
    } else {
      e->next = NULL;
      head = e;
    }
  }
  return head;
}

/*
    reverse the linked list
*/
static struct node* reverse(struct node* head) {
  struct node* prev = NULL;
  struct node* current = head;
  struct node* next;
  while (current != NULL) {
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }
  head = prev;
  return head;
}

/**
 * Commander
 */

static struct node* cmd_flags;
static int cmd_index;
static void * cmd_value;

int cmdcount() {
  return count(cmd_flags);
}

void cmdprint() {
  display_all(cmd_flags);
}

int cmdindex() {
  return cmd_index;
}

void * cmdvalue() {
  return cmd_value;
}

void cmdopt1(char* format) {
  if (cmd_flags == NULL)
    cmd_flags = create_with_value(format, cmd_flags);
  else
    cmd_flags = append_with_value(cmd_flags, format);
}

void cmdopt2(char* flag, char* name) {
  if (cmd_flags == NULL)
    cmd_flags = create_with_name(flag, name, cmd_flags);
  else
    cmd_flags = append_with_name(cmd_flags, flag, name);
}

void cmdopt3(char* flag, char* name, char* format) {
  if (cmd_flags == NULL)
    cmd_flags = create_with_name_and_value(flag, name, format, cmd_flags);
  else
    cmd_flags = append_with_name(cmd_flags, flag, name);
}

static int cmdupdate(struct node *n, int argc, char* argv[], int index) {
  int id = n->id;
  cmd_index = index;
  if (n->format != NULL) {
    n->value = malloc(sizeof(argv[index]));
    sscanf(argv[index], n->format, n->value);
    cmd_value = n->value;
  }
  cmd_flags = remove_any(cmd_flags, n);
  return id;
}

int cmdparse(int argc, char* argv[]) {
  for (int i = 0; i < argc; i++) {
    if (cmd_flags != NULL) {
      struct node* n = search_by_flag_and_name(cmd_flags, argv[i], argv[i]);
      if (n == NULL) n = search_by_id(cmd_flags, i);
      if (n != NULL) {
        return cmdupdate(n, argc, argv, i);
      }
    } else
      break;
  }
  return -1;
}

#endif
