#include <stdio.h>
#include <stdlib.h>

struct node* addTail(struct node* head, int value);

struct node { 
    int value;
    struct node* next;
};

struct node* addTail(struct node* head, int value) {
    struct node* temp = malloc(sizeof(struct node));
    temp->value = value;
    temp->next = NULL;

    // If head is null we will assign temp to it
    if (head == NULL) {
        return temp;
    }
    else { 
        struct node* p = head;
        while (p->next != NULL) { //Find end
            p = p->next;
        }
        p->next = temp;
    }

    //But if not null the head will hold it's original value 
    return head;
}

int main() {
    struct node* head = NULL;

    head = addTail(head, 11);
    head = addTail(head, 22);
    head = addTail(head, 33);

    // Print the linked list
    struct node* p = head;
    int i = 1;
    while (p != NULL) {
        printf("n%d value: %d\n", i, p->value);
        p = p->next;
        i++;
    }

    // Free allocated memory
    p = head;
    while (p != NULL) {
        struct node* next = p->next;
        free(p);
        p = next;
    }

    return 0;
}
