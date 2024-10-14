/*******************************************************************

* Description: 
* This C program implements modified versions of the 'grep' command commonly found in Unix-like operating systems. 
* The 'grep' command is used to search for specific patterns within text files.

Usage:
* Compile it using a C compiler and run the executable from the command line with appropriate arguments.
*    - ./main <pattern> <file> [-i] [-n]
*    - optional arguments are specified in [ ]
*******************************************************************/

#include "text.h"

void grepLite(int argc, char *argv[]) {
    // Check program is recieving minimum required arguments
    if (argc < 3) {
        printf("Invalid amount of arguments. Required atleast 3, provided %d\n", argc);
        puts("Usage: grep <pattern> <filename> with optional [-i] for case insensitive search, [-n] for line number");
        return;
    }

    // User pattern length validation
    char *pattern = argv[1];
    if (strlen(pattern) > 10){
        puts("Search word is too long. Word must be between 1 and 10 characters.");
        puts("Usage: grep <pattern> <filename> with optional [-i] for case insensitive search, [-n] for line number");
        return;
    }
    
    // open user provided file
    FILE *fp = fopen(argv[2], "r");
    if (fp == NULL) {
        puts("File failed to open. Please try again with a valid file name.");
        puts("Usage: grep <pattern> <filename> with optional [-i] for case insensitive search, [-n] for line number");
        return;
    }

    // user input validation on flag symbol. Check just '-' is not being provided
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
        // case where both flags are active
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
                printf("%d %s", lineCount, line);
            }
        }
        // case: number is printed before the line
        else if (strcmp(flag1, "-n") == 0) {
            if (strstr(line, pattern) != NULL) {
                didPrint = 1;
                printf("%d %s", lineCount, line);
            }
        }
        // case: insensitive 
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
                printf("%s", line);
            }
        }
        // no flags provided
        else {
            if (strstr(line, pattern) != NULL) {
                didPrint = 1;
                printf("%s", line);
            }
        }        
    }
    if (!didPrint) {
        puts("No pattern found.");
    }
    
    fclose(fp);
}
