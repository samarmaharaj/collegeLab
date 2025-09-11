%{
#include <stdio.h>
int chars = 0, words = 0, lines = 0, spaces = 0;
int lastWasNewline = 0;
%}

%%

[ \t]+        { spaces += yyleng; chars += yyleng; lastWasNewline = 0; }
\n            { lines++; chars++; lastWasNewline = 1; }
[A-Za-z']+     { words++; chars += yyleng; lastWasNewline = 0; }
.             { chars++; lastWasNewline = 0; }

%%

int main() {
    yylex();
    if (chars > 0 && !lastWasNewline)  // if no newline at end
        lines++;

    printf("Characters: %d\nWords: %d\nSpaces: %d\nLines: %d\n",
           chars, words, spaces, lines);
    return 0;
}
