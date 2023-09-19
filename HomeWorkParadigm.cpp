#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXT_SIZE 1024

char text[MAX_TEXT_SIZE] = "";

void append_text() {
    char input[100];
    printf("Enter text to append: ");
    fgets(input, sizeof(input), stdin);
    strncat_s(text, sizeof(text), input, sizeof(text) - strlen(text) - 1);
}

void start_new_line() {
    strcat_s(text, sizeof(text), "\n");
    printf("New line is started\n");
}

void save_to_file() {
    char filename[100];
    printf("Enter the file name for saving: ");
    fgets(filename, sizeof(filename), stdin);
    if (filename[strlen(filename) - 1] == '\n') {
        filename[strlen(filename) - 1] = '\0';
    }

    FILE* file;
    errno_t err = fopen_s(&file, filename, "w");
    if (err != 0 || !file) {
        perror("Error opening file");
        return;
    }

    fputs(text, file);
    fclose(file);
    printf("Text has been saved successfully\n");
}

void load_from_file() {
    char filename[100];
    printf("Enter the file name for loading: ");
    fgets(filename, sizeof(filename), stdin);
    if (filename[strlen(filename) - 1] == '\n') {
        filename[strlen(filename) - 1] = '\0';
    }

    FILE* file;
    errno_t err = fopen_s(&file, filename, "r");
    if (err != 0 || !file) {
        perror("Error opening file");
        return;
    }

    fread(text, sizeof(char), sizeof(text), file);
    fclose(file);
    printf("Text has been loaded successfully\n");
}

void print_text() {
    printf("%s\n", text);
}

void insert_text_by_index() {
    // Залишаємо функцію без змін, оскільки вона вже використовує _s функції.
    int line, index;
    char input[100];

    printf("Choose line and index: ");
    scanf_s("%d %d", &line, &index, 1);
    while (getchar() != '\n');

    printf("Enter text to insert: ");
    fgets(input, sizeof(input), stdin);

    char* lines[MAX_TEXT_SIZE];
    char* next_token = NULL;
    char* token = strtok_s(text, "\n", &next_token);
    int i = 0;
    while (token) {
        lines[i++] = token;
        token = strtok_s(NULL, "\n", &next_token);
    }

    if (line >= i) {
        strcat_s(text, sizeof(text), input);
        return;
    }

    char new_text[MAX_TEXT_SIZE] = "";

    for (int j = 0; j < line; j++) {
        strcat_s(new_text, sizeof(new_text), lines[j]);
        strcat_s(new_text, sizeof(new_text), "\n");
    }

    strncat_s(new_text, sizeof(new_text), lines[line], index);
    strcat_s(new_text, sizeof(new_text), input);
    strcat_s(new_text, sizeof(new_text), lines[line] + index);
    strcat_s(new_text, sizeof(new_text), "\n");

    for (int j = line + 1; j < i; j++) {
        strcat_s(new_text, sizeof(new_text), lines[j]);
        if (j < i - 1) {
            strcat_s(new_text, sizeof(new_text), "\n");
        }
    }

    strcpy_s(text, sizeof(text), new_text);
}

int main() {
    while (1) {
        printf("Choose the command:\n");
        printf("1. Append text symbols to the end\n");
        printf("2. Start the new line\n");
        printf("3. Use files to loading/saving the information\n");
        printf("4. Print the current text to console\n");
        printf("5. Insert the text by line and symbol index\n");
        printf("6. Exit\n");

        int choice;
        scanf_s("%d", &choice, 1);
        while (getchar() != '\n');

        switch (choice) {
        case 1:
            append_text();
            break;
        case 2:
            start_new_line();
            break;
        case 3:
            printf("Choose:\n");
            printf("1. Save to file\n");
            printf("2. Load from file\n");
            int file_choice;
            scanf_s("%d", &file_choice, 1);
            while (getchar() != '\n');
            if (file_choice == 1) {
                save_to_file();
            }
            else if (file_choice == 2) {
                load_from_file();
            }
            else {
                printf("Invalid choice!\n");
            }
            break;
        case 4:
            print_text();
            break;
        case 5:
            insert_text_by_index();
            break;
        case 6:
            return 0;
        default:
            printf("Invalid choice!\n");
        }
    }

    return 0;
}
