#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: executable <path> <offset>\n");
        return 1;
    }

    char *path = argv[1];
    long offset = strtol(argv[2], NULL, 10);

    const long MAX_OFFSET = 1000;
    if (offset == 0 || offset > MAX_OFFSET || offset < -MAX_OFFSET) {
        printf("Invalid offset '%s'\n", argv[2]);
        return 1;
    }

    FILE *file_input = fopen(path, "r");
    if (file_input == NULL) {
        puts("File not found");
        return 1;
    }

    printf("Applied an offset of %ld to the file %s\n", offset, path);

    fseek(file_input, 0, SEEK_END);
    long size = ftell(file_input);
    fseek(file_input, 0, SEEK_SET);

    char *buff = (char *) malloc(size * sizeof(char));
    fread(buff, size, 1, file_input);
    fclose(file_input);

    char *str = buff;
    for (; *str != '\0'; ++str) {
        if (*str >= 'a' && *str <= 'z') {
            *str = (*str - 'a' + offset) % 26 + 'a';
        }
        else if (*str >= 'A' && *str <= 'Z') {
            *str = (*str - 'A' + offset) % 26 + 'A';
        }
    }

    FILE *file_output = fopen(path, "w");
    if (file_output == NULL) {
        puts("File not found");
        return 1;
    }

    fwrite(buff, size, 1, file_output);
    fclose(file_output);
    free(buff);

    return 0;
}
