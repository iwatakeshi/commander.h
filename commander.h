/**
 * Author: Takeshi Iwana
 * License: MIT
 * Credits: http://www.zentut.com/c-tutorial/c-linked-list/
 */
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
  void* value;
  bool flagable;
  bool valuable;
  struct node* next;
} Node;

static int node_id = 1;
static int node_id_copy = 1;

typedef void (*callback)(struct node* n);
static struct node* create(struct node* next, bool increment_id);
static struct node* create_with_flag(char* flag, char* name, bool valuable, struct node* next, bool increment_id);
static struct node* append(struct node* head, bool increment_id);
static struct node* append_with_flag(struct node* head, bool increment_id, char* flag, char* name, bool valuable);
static void traverse(struct node* head, callback f);
static struct node* remove_front(struct node* head);
static struct node* remove_back(struct node* head);
static struct node* remove_any(struct node* head, struct node* nd);
static void display(struct node* n);
static void display_all(struct node* n);
static struct node* search_by_id(struct node* head, int id);
static struct node* search_by_flag(struct node* head, char* flag, char* name);
static void dispose(struct node* head);
static void node_id_reset();
static void node_id_copy_reset();
static int node_count();
static int node_count(struct node* head);

/**
 * Commander
 */
static struct node* cmd_flags;
static struct node* cmd_flags_copy;

static int cmd_option_index;
static int cmd_value_index;

int cmd_opt_count() {
  return node_count(cmd_flags_copy);
}

void cmd_opt_print() {
  display_all(cmd_flags_copy);
}

int cmd_opt_index() {
  return cmd_option_index;
}

int cmd_val_index() {
  return cmd_value_index;
}

int cmd_free() {
  dispose(cmd_flags);
  dispose(cmd_flags_copy);
  return 0;
}

void cmd_opt_value() {
  if (cmd_flags == NULL) {
    cmd_flags = create(cmd_flags, true);
    cmd_flags_copy = create(cmd_flags_copy, false);
  } else {
    cmd_flags = append(cmd_flags, true);
    cmd_flags_copy = append(cmd_flags_copy, false);
  }
}

void cmd_opt(char* flag, char* name, bool valuable) {
  if (cmd_flags == NULL) {
    cmd_flags = create_with_flag(flag, name, valuable, cmd_flags, true);
    cmd_flags_copy = create_with_flag(flag, name, valuable, cmd_flags_copy, false);
  } else {
    cmd_flags = append_with_flag(cmd_flags, true, flag, name, valuable);
    cmd_flags_copy = append_with_flag(cmd_flags_copy, false, flag, name, valuable);
  }
}

static int cmd_update(struct node* n, int argc, char* argv[], int index) {
  int id = n->id;
  cmd_option_index = index;
  // Find the copy of the current node
  struct node* n_copy = search_by_id(cmd_flags_copy, id);
  // Set the value of the copy if required
  if (n->flagable && n->valuable) {
    // Since we expect a value next to the flag,
    // make sure we don't go over argc
    if (index + 1 < argc) {
      if (n_copy != NULL) n_copy->value = argv[index + 1];
      cmd_value_index = index + 1;
    }
  } else if (n->valuable && argv[index][0] != '-') {
    // Copy the value as long the value at the current
    // index isn't a lonely flag
    if (n_copy != NULL) n_copy->value = argv[index];
    // Set the value index to the current index of argv
    cmd_value_index = index;
  } else
    // Just set it the index to argv[0]
    cmd_value_index = 0;
  
  // Remove the node so we won't have 
  // an endless loop.
  cmd_flags = remove_any(cmd_flags, n);
  // Return the option id
  return id;
}

int cmd_parse(int argc, char* argv[]) {
  for (int i = 1; i < argc; i++) {
    if (cmd_flags != NULL) {
      struct node* n = search_by_flag(cmd_flags, argv[i], argv[i]);
      if (n != NULL) {
        return cmd_update(n, argc, argv, i);
      }

      if (argv[i][0] != '-') n = search_by_id(cmd_flags, i);
      if (n != NULL && !(n->flagable) && n->valuable) {
        return cmd_update(n, argc, argv, i);
      }
    } else
      break;
  }
  // printf("linked list original:\n");
  // display_all(cmd_flags);
  // printf("----------------------\n");
  node_id_reset();
  node_id_copy_reset();
  return -1;
}



/**
 * Linked List
 * Credits: http://www.zentut.com/c-tutorial/c-linked-list/
 */

/*
    create a new node
    initialize the flag and next field
 
    return the newly created node
*/
static struct node* create(struct node* next, bool increment_id) {
  struct node* new_node = (struct node*)malloc(sizeof(struct node));
  if (new_node == NULL) {
    printf("Error creating a new node.\n");
    exit(0);
  }
  if (increment_id) {
    new_node->id = node_id++;
  } else
    new_node->id = node_id_copy++;
  new_node->flag = "";
  new_node->name = "";
  new_node->next = next;
  new_node->flagable = false;
  new_node->valuable = true;

  return new_node;
}

static struct node* create_with_flag(char* flag, char* name, bool valuable, struct node* next, bool increment_id) {
  struct node* new_node = (struct node*)malloc(sizeof(struct node));
  if (new_node == NULL) {
    printf("Error creating a new node.\n");
    exit(0);
  }

  if (increment_id) {
    new_node->id = node_id++;
  } else
    new_node->id = node_id_copy++;
  new_node->next = next;
  new_node->flag = flag;
  new_node->name = name;
  new_node->flagable = true;
  new_node->valuable = valuable;
  return new_node;
}

/*
    add a new node at the end of the list
*/
static struct node* append(struct node* head, bool increment_id) {
  if (head == NULL)
    return NULL;
  /* go to the last node */
  struct node* cursor = head;
  while (cursor->next != NULL)
    cursor = cursor->next;

  /* create a new node */
  struct node* new_node = create(NULL, increment_id);
  cursor->next = new_node;

  return head;
}

static struct node* append_with_flag(struct node* head, bool increment_id, char* flag, char* name, bool valuable) {
  if (head == NULL)
    return NULL;
  /* go to the last node */
  struct node* cursor = head;
  while (cursor->next != NULL)
    cursor = cursor->next;

  /* create a new node */
  struct node* new_node = create_with_flag(flag, name, valuable, NULL, increment_id);
  cursor->next = new_node;

  return head;
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
  if (nd->id == head->id)
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
  if (n->flagable && !(n->valuable)) {
    printf("%d, %s, %s\n", n->id, n->flag, n->name);
  } else if (n->flagable && n->valuable) {
    printf("%d, %s, %s, %p\n", n->id, n->flag, n->name, n->value);
  } else if (!(n->flagable) && n->valuable) {
    printf("\%d, %p\n", n->id, n->value);
  } else if (!(n->flagable) && !(n->valuable)) {
    printf("\%d, ", n->id);
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

static struct node* search_by_id(struct node* head, int id) {
  struct node* cursor = head;
  while (cursor != NULL) {
    if (cursor->id == id)
      return cursor;
    cursor = cursor->next;
  }
  return NULL;
}

static struct node* search_by_flag(struct node* head, char* flag, char* name) {
  struct node* cursor = head;
  while (cursor != NULL) {
    if (cursor->flag != NULL && cursor->name != NULL) {
      if (strcmp(cursor->flag, flag) == 0)
        return cursor;
    }
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

static void node_id_reset() {
  node_id = 1;
}
static void node_id_copy_reset() {
  node_id_copy = 1;
}
/*
    return the number of elements in the list
*/
static int node_count(struct node* head) {
  struct node* cursor = head;
  int c = 0;
  while (cursor != NULL) {
    c++;
    cursor = cursor->next;
  }
  return c;
}

#endif
