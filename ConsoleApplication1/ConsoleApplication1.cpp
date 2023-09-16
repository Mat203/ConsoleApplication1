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

void insert_text(Node*& head, int line, int index, const char* text)
{
    if (line < 0 || index < 0)
    {
        printf("Invalid line or index\n");
        return;
    }

    Node* current = head;
    int current_line = 0;

    while (current != nullptr && current_line < line)
    {
        current = current->next;
        current_line++;
    }

    if (current == nullptr)
    {
        printf("Line not found\n");
        return;
    }

    int length = strlen(current->value);

    if (index > length)
    {
        printf("Index out of range\n");
        return;
    }

    char new_value[80];
    int new_index = 0;
    int old_index = 0;

    while (old_index < index)
    {
        new_value[new_index] = current->value[new_index];
        new_index++;
        old_index++;
    }

    int text_index = 0;
    while (text[text_index] != '\0')
    {
        new_value[new_index] = text[text_index];
        new_index++;
        text_index++;
    }

    while (old_index < length)
    {
        new_value[new_index] = current->value[old_index];
        new_index++;
        old_index++;
    }

    new_value[new_index] = '\0';

    strcpy(current->value, new_value);
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

        if (command == 6)
        {
            int line, index;
            char text[80];

            printf("Enter the number of line and index: ");
            scanf_s("%d %d", &line, &index);
            printf("Enter the text to insert: ");
            scanf_s("%s", text, sizeof(text));

            insert_text(head, line, index, text);
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