#include <stdio.h>
#include <malloc.h>

struct node
{
    struct node *prev;
    int data;
    struct node *next;
};

int count_nodes(struct node *head, struct node *tail);
void display(struct node *head, struct node *tail);
void insert_first(struct node **head, struct node **tail, int data);
void insert_last(struct node **head, struct node **tail, int data);
void insert_at_position(struct node **head, struct node **tail, int data, int pos);
int delete_first(struct node **head, struct node **tail);
int delete_last(struct node **head, struct node **tail);
int delete_at_position(struct node **head, struct node **tail, int pos);
int search_first_occurrence(struct node *head, struct node *tail, int key);
int search_last_occurrence(struct node *head, struct node *tail, int key);
int search_all_occurrence(struct node *head, struct node *tail, int key);
void concat_list(struct node **head1, struct node **tail1, struct node **head2, struct node **tail2);
void concat_at_position(struct node **head1, struct node **tail1, struct node **head2, struct node **tail2, int pos);
void physical_reverse(struct node **head, struct node **tail);
void reverse_display(struct node *head, struct node *tail);
void delete_all(struct node **head, struct node **tail);

/* Test functions */
/*
void test_normal(struct node *head, struct node *tail)
{
    int count = count_nodes(head, tail) * 5;

    for (int i = 1; i <= count; i++)
    {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n\n");
}

void test_reverse(struct node *head, struct node *tail)
{
    int count = count_nodes(head, tail) * 5;

    for (int i = 1; i <= count; i++)
    {
        printf("%d ", tail->data);
        tail = tail->prev;
    }
    printf("\n\n");
}
*/

int main(void)
{
    int flag = 1, choice, result;
    int data, position, concat_position;
    struct node *first = NULL;
    struct node *last = NULL;
    struct node *first1 = NULL;
    struct node *last1 = NULL;

    while (flag)
    {
        printf("\n1. Insert\n2. Delete\n3. Search\n4. Count\n5. Reverse\n6. Concat\n7. Exit\n>_");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:

            while (flag)
            {
                printf("\n1. Insert First\n2. Insert Last\n3. Insert at Position\n4. Back\n>_");
                scanf("%d", &choice);

                switch (choice)
                {
                case 1:

                    printf("\nEnter the data: ");
                    scanf("%d", &data);

                    insert_first(&first, &last, data);

                    printf("\nList is: ");
                    display(first, last);

                    break;

                case 2:

                    printf("\nEnter the data: ");
                    scanf("%d", &data);

                    insert_last(&first, &last, data);

                    printf("\nList is: ");
                    display(first, last);

                    break;

                case 3:

                    printf("\nEnter the position: ");
                    scanf("%d", &position);

                    if (position < 1 || position > count_nodes(first, last) + 1)
                    {
                        printf("\nInvalid position.\n");
                        break;
                    }

                    printf("\nEnter the data: ");
                    scanf("%d", &data);

                    insert_at_position(&first, &last, data, position);

                    printf("\nList is: ");
                    display(first, last);

                    break;

                case 4:
                    flag = 0;
                    break;

                default:
                    printf("\nInvalid choice.\n");
                }
            }

            flag = 1;

            break;

        case 2:

            if (first == NULL)
            {
                printf("\nList is empty.\n");
                break;
            }

            while (flag)
            {
                printf("\n1. Delete First\n2. Delete Last\n3. Delete at Position\n4. Back\n>_");
                scanf("%d", &choice);

                switch (choice)
                {
                case 1:

                    result = delete_first(&first, &last);

                    if (result == -1)
                    {
                        printf("\nList is empty.\n");
                        break;
                    }

                    printf("\nDeleted data from the list is: %d\n", result);

                    printf("\nList is: ");
                    display(first, last);

                    break;

                case 2:

                    result = delete_last(&first, &last);

                    if (result == -1)
                    {
                        printf("\nList is empty.\n");
                        break;
                    }

                    printf("\nDeleted data from the list is: %d\n", result);

                    printf("\nList is: ");
                    display(first, last);

                    break;

                case 3:

                    if (first == NULL)
                    {
                        printf("\nList is empty.\n");
                        break;
                    }

                    printf("\nEnter the position: ");
                    scanf("%d", &position);

                    if (position < 1 || position > count_nodes(first, last))
                    {
                        printf("\nInvalid position.\n");
                        break;
                    }

                    printf("\nDeleted data from the list is: %d\n", delete_at_position(&first, &last, position));

                    printf("\nList is: ");
                    display(first, last);

                    break;

                case 4:

                    flag = 0;

                    break;

                default:
                    printf("\nInvalid choice.\n");
                }
            }

            flag = 1;

            break;

        case 3:

            if (first == NULL)
            {
                printf("\nList is empty.\n");
                break;
            }

            while (flag)
            {
                printf("\n1. Search First Occurrence\n2. Search Last Occurrence\n3. Search All Occurrences\n4. Back\n>_");
                scanf("%d", &choice);

                if (choice >= 1 && choice <= 3)
                {
                    printf("\nEnter the key to search: ");
                    scanf("%d", &data);
                }

                switch (choice)
                {
                case 1:

                    result = search_first_occurrence(first, last, data);

                    if (result == -2)
                        printf("\nKey not found.\n");
                    else
                        printf("\nKey %d first occurred at position: %d\n", data, result);

                    break;

                case 2:

                    result = search_last_occurrence(first, last, data);

                    if (result == -2)
                        printf("\nKey not found.\n");
                    else
                        printf("\nKey %d last occurred at position: %d\n", data, result);

                    break;

                case 3:

                    result = search_all_occurrence(first, last, data);

                    printf("\nKey %d occurred %d times.\n", data, result);

                    break;

                case 4:

                    flag = 0;

                    break;

                default:
                    printf("\nInvalid choice.\n");
                }
            }

            flag = 1;

            break;

        case 4:

            printf("\nCount of nodes is: %d\n", count_nodes(first, last));

            break;

        case 5:

            if (first == NULL)
            {
                printf("\nList is empty.\n");
                break;
            }

            while (flag)
            {
                printf("\n1. Physical Reverse\n2. Display Reverse\n3. Back\n>_");
                scanf("%d", &choice);

                switch (choice)
                {
                case 1:

                    physical_reverse(&first, &last);

                    printf("\nList after physical reverse: ");
                    display(first, last);

                    break;

                case 2:

                    reverse_display(first, last);

                    break;

                case 3:

                    flag = 0;

                    break;

                default:
                    printf("\nInvalid choice.\n");
                }
            }

            flag = 1;

            break;

        case 6:

            while (flag)
            {
                printf("\n1. Concat List\n2. Concat at Position\n3. Back\n>_");
                scanf("%d", &choice);

                switch (choice)
                {
                case 1:

                    while (flag)
                    {
                        printf("\n1. Insert First\n2. Insert Last\n3. Insert at Position\n4. Concat & Back\n>_");
                        scanf("%d", &choice);

                        switch (choice)
                        {
                        case 1:

                            printf("\nEnter the data: ");
                            scanf("%d", &data);

                            insert_first(&first1, &last1, data);

                            printf("\nList is: ");
                            display(first1, last1);

                            break;

                        case 2:

                            printf("\nEnter the data: ");
                            scanf("%d", &data);

                            insert_last(&first1, &last1, data);

                            printf("\nList is: ");
                            display(first1, last1);

                            break;

                        case 3:

                            printf("\nEnter the position: ");
                            scanf("%d", &position);

                            if (position < 1 || position > count_nodes(first1, last1) + 1)
                            {
                                printf("\nInvalid position.\n");
                                break;
                            }

                            printf("\nEnter the data: ");
                            scanf("%d", &data);

                            insert_at_position(&first1, &last1, data, position);

                            printf("\nList is: ");
                            display(first1, last1);

                            break;

                        case 4:

                            concat_list(&first, &last, &first1, &last1);
                            printf("\nList is: ");
                            display(first, last);
                            flag = 0;

                            break;

                        default:
                            printf("\nInvalid choice.\n");
                        }
                    }

                    flag = 1;

                    break;

                case 2:

                    printf("\nEnter the postion: ");
                    scanf("%d", &concat_position);

                    if (concat_position < 1 || concat_position > count_nodes(first, last) + 1)
                    {
                        printf("\nInvalid position.\n");
                        break;
                    }

                    while (flag)
                    {
                        printf("\n1. Insert First\n2. Insert Last\n3. Insert at Position\n4. Concat & Back\n>_");
                        scanf("%d", &choice);

                        switch (choice)
                        {
                        case 1:

                            printf("\nEnter the data: ");
                            scanf("%d", &data);

                            insert_first(&first1, &last1, data);

                            printf("\nList is: ");
                            display(first1, last1);

                            break;

                        case 2:

                            printf("\nEnter the data: ");
                            scanf("%d", &data);

                            insert_last(&first1, &last1, data);

                            printf("\nList is: ");
                            display(first1, last1);

                            break;

                        case 3:

                            printf("\nEnter the position: ");
                            scanf("%d", &position);

                            if (position < 1 || position > count_nodes(first1, last1) + 1)
                            {
                                printf("\nInvalid position.\n");
                                break;
                            }

                            printf("\nEnter the data: ");
                            scanf("%d", &data);

                            insert_at_position(&first1, &last1, data, position);

                            printf("\nList is: ");
                            display(first1, last1);

                            break;

                        case 4:

                            concat_at_position(&first, &last, &first1, &last1, concat_position);
                            printf("\nList is: ");
                            display(first, last);
                            flag = 0;

                            break;

                        default:
                            printf("\nInvalid choice.\n");
                        }
                    }

                    flag = 1;

                    break;

                case 3:

                    flag = 0;

                    break;

                default:
                    printf("\nInvalid choice.\n");
                }
            }

            flag = 1;

            break;

        case 7:

            delete_all(&first, &last);

            flag = 0;
            break;

        default:
            printf("\nInvalid choice.\n");
        }
    }

    printf("\nThank You!\n");

    return 0;
}

int count_nodes(struct node *head, struct node *tail)
{
    int counter = 0;

    if (head == NULL)
        return 0;
    do
    {
        counter++;
        head = head->next;
    } while (head != tail->next);

    return counter;
}

void display(struct node *head, struct node *tail)
{
    if (head == NULL)
    {
        printf("\nList is empty.\n");
        return;
    }

    do
    {
        printf("%d ", head->data);
        head = head->next;

    } while (head != tail->next);
    printf("\n");
}

void reverse_display(struct node *head, struct node *tail)
{
    if (head == NULL)
    {
        printf("\nList is empty.\n");
        return;
    }

    printf("\nReversed list is: ");

    do
    {
        printf("%d ", tail->data);
        tail = tail->prev;

    } while (tail != head->prev);
    printf("\n");
}

void insert_first(struct node **head, struct node **tail, int data)
{
    struct node *new_node = NULL;

    new_node = (struct node *)malloc(sizeof(struct node));
    if (new_node == NULL)
        return; /* Memory allocation failed */

    new_node->data = data;

    if (*head == NULL)
        *head = *tail = new_node;
    else
    {
        new_node->next = *head;
        (*head)->prev = new_node;
        *head = new_node;
    }
    (*head)->prev = *tail;
    (*tail)->next = *head;
}

void insert_last(struct node **head, struct node **tail, int data)
{
    struct node *new_node = NULL;

    new_node = (struct node *)malloc(sizeof(struct node));
    if (new_node == NULL)
        return; /* Memory allocation failed */

    new_node->data = data;

    if (*head == NULL)
        *head = *tail = new_node;
    else
    {
        (*tail)->next = new_node;
        new_node->prev = *tail;
        *tail = new_node;
    }
    (*head)->prev = *tail;
    (*tail)->next = *head;
}

void insert_at_position(struct node **head, struct node **tail, int data, int pos)
{
    struct node *new_node = NULL;
    struct node *temp_node = NULL;
    int counter, node_count = count_nodes(*head, *tail);

    if (pos < 1 || pos > node_count + 1)
        return; /* Position is invalid */

    if (pos == 1)
        insert_first(head, tail, data);
    else if (pos == node_count + 1)
        insert_last(head, tail, data);
    else
    {
        temp_node = *head;

        new_node = (struct node *)malloc(sizeof(struct node));
        if (new_node == NULL)
            return; /* Memory allocation failed */
        new_node->data = data;

        for (counter = 1; counter < pos - 1; counter++)
            temp_node = temp_node->next;

        new_node->next = temp_node->next;
        new_node->next->prev = new_node;
        temp_node->next = new_node;
        new_node->prev = temp_node;
    }
}

int delete_first(struct node **head, struct node **tail)
{
    int deleted_data;

    if (*head == NULL)
        return -1; /* List is empty */

    deleted_data = (*head)->data;

    if (*head == *tail)
    {
        free(*head);
        *head = *tail = NULL;
    }
    else
    {
        *head = (*head)->next;
        free((*tail)->next);

        (*head)->prev = *tail;
        (*tail)->next = *head;
    }
    return deleted_data;
}

int delete_last(struct node **head, struct node **tail)
{
    int deleted_data;

    if (*head == NULL)
        return -1; /* List is empty */

    deleted_data = (*tail)->data;

    if (*head == *tail)
    {
        free(*tail);
        *head = *tail = NULL;
    }
    else
    {
        *tail = (*tail)->prev;
        free((*head)->prev);

        (*head)->prev = *tail;
        (*tail)->next = *head;
    }
    return deleted_data;
}

int delete_at_position(struct node **head, struct node **tail, int pos)
{
    int counter, deleted_data;
    int node_count = count_nodes(*head, *tail);
    struct node *temp_node = NULL;

    if (pos < 1 || pos > node_count)
        return -1; /* Position is invalid */

    if (pos == 1)
        return delete_first(head, tail);
    else if (pos == node_count)
        return delete_last(head, tail);
    else
    {
        temp_node = *head;

        for (counter = 1; counter < pos - 1; counter++)
            temp_node = temp_node->next;

        deleted_data = temp_node->next->data;
        temp_node->next = temp_node->next->next;
        free(temp_node->next->prev);
        temp_node->next->prev = temp_node;
    }
    return deleted_data;
}

int search_first_occurrence(struct node *head, struct node *tail, int key)
{
    int position = 1;

    if (head == NULL)
        return -1; /* List is empty */

    do
    {
        if (head->data == key)
            return position;
        position++;
        head = head->next;
    } while (head != tail->next);

    return -2; /* Key not found */
}

int search_last_occurrence(struct node *head, struct node *tail, int key)
{
    int position = 1, ret_position = -2;

    if (head == NULL)
        return -1; /* List is empty */

    do
    {
        if (head->data == key)
            ret_position = position;
        position++;
        head = head->next;
    } while (head != tail->next);

    return ret_position;
}

int search_all_occurrence(struct node *head, struct node *tail, int key)
{
    int count_occurrences = 0;

    if (head == NULL)
        return 0; /* List is empty */

    do
    {
        if (head->data == key)
            count_occurrences++;
        head = head->next;
    } while (head != tail->next);

    return count_occurrences;
}

void concat_list(struct node **head1, struct node **tail1, struct node **head2, struct node **tail2)
{
    if (*head2 == NULL) /* If second list is empty */
        return;
    else if (*head1 == NULL) /* If first list is empty */
    {
        *head1 = *head2;
        *tail1 = *tail2;
        *head2 = *tail2 = NULL;
    }
    else /* Both list are not empty */
    {
        (*tail1)->next = *head2;
        (*head2)->prev = *tail1;
        (*tail2)->next = *head1;
        (*head1)->prev = *tail2;
        *tail1 = *tail2;
        *head2 = *tail2 = NULL;
    }
}

void concat_at_position(struct node **head1, struct node **tail1, struct node **head2, struct node **tail2, int pos)
{
    int counter;
    struct node *temp_node = NULL;
    int node_count = count_nodes(*head1, *tail1);

    if (pos < 1 || pos > node_count + 1)
        return; /* Position is invalid */

    if (*head2 == NULL)
        return;

    if (pos == 1)
    {
        concat_list(head2, tail2, head1, tail1);
        *head1 = *head2;
        *tail1 = *tail2;
        *head2 = *tail2 = NULL;

        return;
    }

    temp_node = *head1;

    for (counter = 1; counter < pos - 1; counter++)
        temp_node = temp_node->next;

    (*tail2)->next = temp_node->next;
    temp_node->next->prev = (*tail2);
    temp_node->next = *head2;
    (*head2)->prev = temp_node;

    *head2 = *tail2 = NULL;
}

void physical_reverse(struct node **head, struct node **tail)
{
    struct node *current = *head;
    struct node *next = NULL;

    if (*head == NULL)
        return;

    do
    {
        next = current->next;
        current->next = current->prev;
        current->prev = next;
        current = next;
    } while (current != *head);

    *head = *tail;
    *tail = current;
}

void delete_all(struct node **head, struct node **tail)
{
    struct node *temp_node = *head;

    if (temp_node == NULL)
        return; /* List is empty */

    (*tail)->next = NULL;

    while (temp_node != NULL)
    {
        *head = temp_node->next;
        temp_node->next = NULL;
        free(temp_node);
        temp_node = *head;
    }
}