%{
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int count = 0;
char find_word[50];
char replace_word[50];
FILE *input_file = NULL;
%}

%%

[[:alpha:]]+   {   // Match any word (sequence of letters)
    if (strcmp(yytext, find_word) == 0) {
        count++;
        printf("%s", replace_word);
    } else {
        printf("%s", yytext);
    }
}

.|\n            { ECHO; }   // Print all other characters as-is

%%

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <word_to_find> <word_to_replace> [input_file]\n", argv[0]);
        return 1;
    }

    strcpy(find_word, argv[1]);
    strcpy(replace_word, argv[2]);

    if (argc == 4) {
        input_file = fopen(argv[3], "r");
        if (!input_file) {
            perror("Error opening file");
            return 1;
        }
        yyin = input_file;
    } else {
        printf("Enter text (Ctrl+D to finish):\n");
        yyin = stdin;
    }

    yylex();

    printf("\n\nTotal occurrences of '%s': %d\n", find_word, count);

    if (input_file) fclose(input_file);
    return 0;
}

int yywrap() { return 1; }
