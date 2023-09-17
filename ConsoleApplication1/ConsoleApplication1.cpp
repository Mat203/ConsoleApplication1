#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

struct Node
{
    char value[80]; 
    Node* next;
};

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

void search_text(Node* head, const char* substr) {
    int line_number = 0;
    int check = 0;

    Node* current = head;
    while (current != nullptr) {
        const char* line = current->value;
        int line_len = strlen(line);
        int substr_len = strlen(substr);

        for (int i = 0; i <= line_len - substr_len; i++) {
            int j;
            for (j = 0; j < substr_len; j++) {
                if (line[i + j] != substr[j]) {
                    break; 
                }
            }

            if (j == substr_len) {
                printf("Text is present in this position: Line %d, Index %d\n", line_number, i);
                check = 1;
            }
        }

        line_number++;
        current = current->next;
    }

    if (check == 0)
    {
        printf("There is no such text in the lines\n");
    }
}

void load_text_from_file(Node*& head, const char* filename)
{
    FILE* file;
    file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    while (head != nullptr)
    {
        Node* current = head;
        head = head->next;
        delete current;
    }

    char line[80];
    new_line(head);
    Node* current = head;
    while (fgets(line, 80, file))
    {
        for (int i = 0; i < sizeof(line); i++)
        {
            if (line[i] == '\n')
            {
                line[i] = '\0';
                break;
            }
        }

        strcpy_s(current->value, line);

        new_line(current);
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
    printf("8 - Console clearing\n");

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
            printf("Text has been saved successfully\n");
        }

        if (command == 4)
        {
            char filename[80];
            printf("Enter the file name for loading: ");
            scanf_s("%s", filename, sizeof(filename));
            load_text_from_file(head, filename);
            printf("Text has been loaded successfully\n");
        }

        if (command == 5)
        {
            Node* current = head;

            while (current != nullptr)
            {
                printf("%s\n", current->value);
                current = current->next;
            }
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

        if (command == 7) {
            char substring[80];
            printf("Enter text to search: ");
            scanf_s("%s", substring, sizeof(substring));
            search_text(head, substring);
        }

        if (command == 8) {
            printf("\033[H\033[J");
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