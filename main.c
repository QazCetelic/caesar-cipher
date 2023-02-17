#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: executable <path> <offset>\n");
        return 1;
    }

    char *path = argv[1];
    long offset = strtol(argv[2], NULL, 10);

    if (offset == 0) {
        printf("Invalid offset '%s'\n", argv[2]);
        return 1;
    }

    printf("Applied an offset of %ld to the file %s\n", offset, path);

    FILE *file_input = fopen(path, "r");
    if (file_input == NULL) {
        puts("File not found");
        return 1;
    }

    fseek(file_input, 0, SEEK_END);
    long size = ftell(file_input);
    fseek(file_input, 0, SEEK_SET);

    char *buff = (char *) malloc(size * sizeof(char));
    fread(buff, size, 1, file_input);
    fclose(file_input);

    for (long i = size - 1; i > 0; i--) {
        const int MIN = 33;
        const int MAX = 126;
        if (buff[i] >= MIN && buff[i] <= MAX) {
            long val = (long) buff[i];
            val = (val - MIN + offset) % (MAX - MIN + 1) + MIN;
            buff[i] = (char) val;
        }
        else {
            buff[i] = buff[i];
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
