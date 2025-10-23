#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

typedef struct node
{
    int data;
    struct node * next;
}node_t;

extern node_t *head;

/**
 * @brief Push a new node to the end of the list
 *
 * @param head head of the linked list
 * @param val value of the new node
 */
void linked_list_push(node_t **/* head */, int /* val */);

/**
 * @brief Pop the first item from the head of the list
 *
 * @param head head of the linked list
 * @return int value of the popped node
 */
int linked_list_pop(node_t **/* head */);

/**
 * @brief Print the contents of the linked list
 *
 * @param head head of the linked list
 */
void linked_list_print(node_t **/* head */);

#endif // __LINKED_LIST_H__