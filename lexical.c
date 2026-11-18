#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    FILE *fp;
    char ch, word[20];
    int i;

    fp = fopen("input.c", "r");

    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == ' ' || ch == '\n' || ch == '\t')
            continue;

        if (ch == '/')
        {
            char next = fgetc(fp);

            if (next == '/')
                while ((ch = fgetc(fp)) != '\n' && ch != EOF);
            else
                printf("Operator : /\n");
        }

        else if (isalpha(ch))
        {
            i = 0;

            while (isalnum(ch))
            {
                word[i++] = ch;
                ch = fgetc(fp);
            }

            word[i] = '\0';

            if (!strcmp(word, "int") ||
                !strcmp(word, "float") ||
                !strcmp(word, "if") ||
                !strcmp(word, "else") ||
                !strcmp(word, "return"))
                printf("Keyword : %s\n", word);
            else
                printf("Identifier : %s\n", word);

            ungetc(ch, fp);
        }

        else if (isdigit(ch))
            printf("Number : %c\n", ch);

        else if (ch == '+' || ch == '-' || ch == '*' ||
                 ch == '=' || ch == '<' || ch == '>')
            printf("Operator : %c\n", ch);

        else if (ch == ';' || ch == ',' || ch == '(' ||
                 ch == ')' || ch == '{' || ch == '}')
            printf("Special Symbol : %c\n", ch);
    }

    fclose(fp);
    return 0;
}
