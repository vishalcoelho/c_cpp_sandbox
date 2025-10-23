#include "linked_list.h"
#include <stdio.h>
#include <assert.h>

int main(void)
{

    node_t *head = NULL;

    for (int i = 1; i <= 10; ++i)
    {
        linked_list_push(&head, i);
    }
    linked_list_print(&head);

    printf("Popping half\n");
    for (int i = 0; i < 5; ++i)
    {
        printf("%d ", linked_list_pop(&head));
    }
    printf("\n");
    linked_list_print(&head);

    printf("Popping rest\n");
    for (int i = 0; i < 5; ++i)
    {
        printf("%d ", linked_list_pop(&head));
    }
    printf("\n");
    linked_list_print(&head);

    return 0;
}