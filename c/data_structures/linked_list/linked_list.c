#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

/**
 *  head
 *    v
 *   +---+
 *   |a|*|-> NULL
 *   +---+
 *  PUSH 4
 *  head
 *    v
 *   +---+  +---+  +---+  +---+  +---+
 *   |e|*|->|d|*|->|c|*|->|b|*|->|a|*|->NULL
 *   +---+  +---+  +---+  +---+  +---+
 *  POP 2
 *  head
 *    v
 *   +---+  +---+  +---+
 *   |c|*|->|b|*|->|a|*|->NULL
 *   +---+  +---+  +---+
 */

void linked_list_push(node_t **head, int val)
{
    /** head *head  node
     *  +-+   +-+  +---+
     *  |*| ->|*|->|c|*|
     *  +-+   +-+  +---+
     */
    node_t *new_node = (node_t *)malloc(sizeof(node_t));

    if (new_node)
    {
        new_node->data = val;
        new_node->next = *head;
        *head = new_node;
    }
}

int linked_list_pop(node_t **head)
{
    int ret = INT_MIN;
    if (*head != NULL)
    {
        node_t *current = *head;
        *head = current->next;
        ret = current->data;
        free(current);
    }

    return ret;
}

void linked_list_print(node_t **head)
{
    node_t *current = *head;
    printf("head->");
    while(current != NULL)
    {
        printf("|%d|", current->data);
        current = current->next;
    }
    printf("->NULL\n");
}