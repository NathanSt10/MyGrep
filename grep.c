#include "text.h"

void grepLite(int argc, char *argv[]) {
    // TODO: First check if the correct number of arguments is provided
    if (argc < 3) {
        printf("Invalid amount of arguments. Required atleast 3, provided %d\n", argc);
        puts("Usage: grep <pattern> <filename> with optional [-i] for case insensitive search, [-n] for line number");
        return;
    }

    char *pattern = argv[1];
    if (strlen(pattern) > 10){
        puts("Search word is too long. Word must be between 1 and 10 characters.");
        puts("Usage: grep <pattern> <filename> with optional [-i] for case insensitive search, [-n] for line number");
        return;
    }
    
    FILE *fp = fopen(argv[2], "r");
    if (fp == NULL) {
        puts("File failed to open. Please try again with a valid file name.");
        puts("Usage: grep <pattern> <filename> with optional [-i] for case insensitive search, [-n] for line number");
        return;
    }

    if ((argc > 3 && strcmp(argv[3], "-") == 0) || (argc > 4 && strcmp(argv[4], "-") == 0)) {
        puts("Invalid flag.");
        puts("Usage: grep <pattern> <filename> with optional [-i] for case insensitive search, [-n] for line number");
    } 

    char *flag1;
    if (argc > 3) {
        flag1 = argv[3];
    }

    int lineCount = 0;
    char line[1024];
    int didPrint = 0;
    while (fgets(line, sizeof(line), fp)) {
        ++lineCount;
        int pos = strcspn(line, "\n");
        line[pos] = '\0';
        if (argc > 4) {
            char tmpLine[1024];
            strcpy(tmpLine, line);
            for (int i = 0; tmpLine[i] != '\0'; i++) {
                tmpLine[i] = tolower(tmpLine[i]);
            }
            for (int i = 0; pattern[i] != '\0'; i++) {
                pattern[i] = tolower(pattern[i]);
            }
            if (strstr(tmpLine, pattern) != NULL) {
                didPrint = 1;
                printf("%d %s\n", lineCount, line);
            }
        }
        else if (strcmp(flag1, "-n") == 0) {
            if (strstr(line, pattern) != NULL) {
                didPrint = 1;
                printf("%d %s\n", lineCount, line);
            }
        }
        else if (strcmp(flag1, "-i") == 0) {
            char tmpLine[1024];
            strcpy(tmpLine, line);
            for (int i = 0; tmpLine[i] != '\0'; i++) {
                tmpLine[i] = tolower(tmpLine[i]);
            }
            for (int i = 0; pattern[i] != '\0'; i++) {
                pattern[i] = tolower(pattern[i]);
            }
            if (strstr(tmpLine, pattern) != NULL) {
                didPrint = 1;
                printf("%s\n", line);
            }
        }
        else {
            if (strstr(line, pattern) != NULL) {
                didPrint = 1;
                printf("%s\n", line);
            }
        }        
    }
    if (!didPrint) {
        puts("No pattern found.");
    }
    
    fclose(fp);
}
