#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int command;
    char** textArray = NULL;
    int numRows = 0;
    int currentRow = 0;
    const int maxLineLength = 100;

    printf("You can use next commands: \n");
    printf("1 - Text append\n");
    printf("2 - New line start\n");
    printf("3 - Save the text to the file\n");
    printf("4 - Load the text from the file\n");
    printf("5 - Current text print\n");
    printf("6 - Insert the text by line and symbol index\n");
    printf("7 - Text search\n");
    printf("8 - Text clear\n");

    while (1)
    {
        printf("Enter the number of command: ");
        scanf_s("%d", &command);
        getchar();

        if (command == 1)
        {
            char input[maxLineLength];
            printf("Enter the text: ");
            scanf_s("%s", input, sizeof(input));

            if (currentRow == 0) {
                textArray = (char**)realloc(textArray, (currentRow + 1) * sizeof(char*));
                textArray[currentRow] = (char*)malloc((strlen(input) + 1) * sizeof(char));
                strcpy_s(textArray[currentRow], strlen(input) + 1, input);
                currentRow++;
            }
            else {
                textArray[currentRow - 1] = (char*)realloc(textArray[currentRow - 1], (strlen(textArray[currentRow - 1]) + strlen(input) + 1) * sizeof(char));
                strcat_s(textArray[currentRow - 1], strlen(textArray[currentRow - 1]) + strlen(input) + 1, input);
            }
        }

        else if (command == 5)
        {
            for (int i = 0; i < currentRow; i++)
            {
                printf("%s\n", textArray[i]);
            }
        }
    }

    return 0;
}
