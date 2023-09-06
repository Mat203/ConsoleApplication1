#include <stdio.h>

int main() {
    int command;
    printf("You can use next commands: \n");
    printf("1 - Text append\n");
    printf("2 - New line start\n");
    printf("3 - Save the text to the file\n");
    printf("4 - Load the text from the file\n");
    printf("5 - Current text print\n");
    printf("6 - Insert the text by line and symbol index\n");
    printf("7 - Text search\n");
    printf("8 - Text clear\n");

    while (true)
    {
        printf("Enter the number of command: ");
        scanf_s("%d", &command);

        if (command != 0)
        {
            printf("The command is not implemented\n");
        }
    }

    return 0;
}