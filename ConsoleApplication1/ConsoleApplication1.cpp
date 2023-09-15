#include <stdio.h>
#include <string.h>

struct Node
{
    char value[80]; 
    Node* next;
};

void delete_element(Node*& head, const char* val)
{
    Node* current = head;
    Node* previous = nullptr;

    while (current != nullptr)
    {
        if (strcmp(current->value, val) == 0)
        {
            if (previous == nullptr)
            {
                head = current->next;
                delete current;
                current = head;
            }
            else
            {
                previous->next = current->next;
                delete current;
                current = previous->next;
            }
        }
        else
        {
            previous = current;
            current = current->next;
        }
    }
}

int main()
{
    Node* head = new Node();
    strcpy_s(head->value, "Hello");

    Node* current = new Node();
    strcpy_s(current->value, "World");
    head->next = current;

    current->next = new Node();
    strcpy_s(current->next->value, "This");

    current = current->next;
    current->next = new Node();
    strcpy_s(current->next->value, "Is");

    current = current->next;
    current->next = new Node();
    strcpy_s(current->next->value, "A");

    current = current->next;
    current->next = new Node();
    strcpy_s(current->next->value, "Linked");

    current = current->next;
    current->next = new Node();
    strcpy_s(current->next->value, "List");

    current->next->next = nullptr;

    Node* print_current = head;
    while (print_current != nullptr)
    {
        printf("%s ", print_current->value);
        print_current = print_current->next;
    }
    printf("\n");

    delete_element(head, "This");

    print_current = head;
    while (print_current != nullptr)
    {
        printf("%s ", print_current->value);
        print_current = print_current->next;
    }
    printf("\n");

    while (head != nullptr)
    {
        current = head;
        head = head->next;
        delete current;
    }

    return 0;
}
