#include "text.h"

void grepLite(int argc, char *argv[]) {
    // TODO: First check if the correct number of arguments is provided
    if (argc < 3) {
        printf("Invalid amount of arguments. Required atleast 3, provided %d\n", argc);
        return;
    }

    char *pattern = argv[1];
    if (strlen(pattern) > 10){
        puts("Search word is too long.");
        puts("Usage: grep <pattern> <filename> with optional [-i] for case insensitive search, [-n] for line number");
        return;
    }
    
    FILE *fp = fopen(argv[2], "r");
    if (fp == NULL) {
        puts("File failed to open. Please try again with a valid file name");
        puts("Usage: grep <pattern> <filename> with optional [-i] for case insensitive search, [-n] for line number");
        return;
    }

    int lineCount = 0;
    char line[1024];
    while (fgets(line, sizeof(line), fp)) {
        ++lineCount;
        int pos = strcspn(line, "\n");
        line[pos] = '\0';
        if (strstr(line, pattern) != NULL) {
            printf("%d %s\n", lineCount, line);

        }
    }
}
