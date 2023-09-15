#define _CRT_SECURE_NO_WARNINGS
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

void new_line(Node*& head)
{
    Node* new_node = new Node();
    new_node->next = nullptr;

    if (head == nullptr)
    {
        head = new_node;
    }
    else
    {
        Node* current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = new_node;
    }
}

void append_text(Node*& head, const char* text)
{
    if (head == nullptr)
    {
        head = new Node();
        strcpy_s(head->value, text);
        head->next = nullptr;
    }
    else
    {
        Node* current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
 
        strcat_s(current->value, text);
    }
}
void save_text_to_file(Node* head, const char* filename)
{
    FILE* file;
    file  = fopen(filename, "w"); 

    Node* current = head;
    while (current != NULL)
    {
        fprintf(file, "%s\n", current->value); 
        current = current->next;
    }

    fclose(file); 
}


int main()
{
    printf("You can use next commands: \n");
    printf("1 - Text append\n");
    printf("2 - New line start\n");
    printf("3 - Save the text to the file\n");
    printf("4 - Load the text from the file\n");
    printf("5 - Current text print\n");
    printf("6 - Insert the text by line and symbol index\n");
    printf("7 - Text search\n");
    printf("8 - Text clear\n");

    Node* head = nullptr;

    while (true)
    {
        int command;
        printf("Write your command:");
        scanf_s("%d", &command);

        if (command == 1)
        {
            char text[80];
            printf("Enter text to append: ");
            scanf_s("%s", text, sizeof(text));
            append_text(head, text);

            Node* print_current = head;
            while (print_current != nullptr)
            {
                printf("%s \n", print_current->value);
                print_current = print_current->next;
            }
            printf("\n");
        }

        if (command == 2)
        {
            printf("Hew line has started\n");
            new_line(head);
        }
        if (command == 3)
        {
            char filename[80];
            printf("Enter the file name for saving: ");
            scanf_s("%s", filename, sizeof(filename));
            save_text_to_file(head, filename);
            printf("Text has been saved successfully");
        }
    }

    while (head != nullptr)
    {
        Node* current = head;
        head = head->next;
        delete current;
    }

    return 0;
}