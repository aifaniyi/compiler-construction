#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

// ############ defines
#define MAXIDLEN 30
typedef enum {
    elsesym, ifsym, intsym, printsym, readsym, returnrym, whilesym, semicolonsym, commasym, opencurlsystem, closecurlsym, opensquaresym, closesquaresym, openbracketsym, closebracketsym, dividesym, multiplysym, plussym, minussym, assignsym, eqsym, nesym, ltsym, lesym, gtsym, gesym, eofsym, constantsym, identifiersym, errorsym
} lextokens;

// ############ global vars
FILE *fp;
char identifier[MAXIDLEN+1];
char ch;
lextokens lextoken;

// ############ functions
char getch(FILE *fp) {
    return fgetc(fp);
}

int white(char ch) {
    return ch == ' ' || ch == '\n' || ch == '\t';
}

lextokens get_token(char ch, FILE *fp) {
    switch (ch) {
        case ';': lextoken = semicolonsym; ch = getch(fp); break;
        case ',': lextoken = commasym; ch = getch(fp); break;
        case '+': lextoken = plussym; ch = getch(fp); break;
        case '-': lextoken = minussym; ch = getch(fp); break;
        case '/': lextoken = dividesym; ch = getch(fp); break;
        case '*': lextoken = multiplysym; ch = getch(fp); break;
        case '(': lextoken = openbracketsym; ch = getch(fp); break;
        case ')': lextoken = closebracketsym; ch = getch(fp); break;
        case '{': lextoken = opencurlsystem; ch = getch(fp); break;
        case '}': lextoken = closecurlsym; ch = getch(fp); break;
        case '[': lextoken = opensquaresym; ch = getch(fp); break;
        case ']': lextoken = closesquaresym; ch = getch(fp); break;
        case EOF: lextoken = eofsym; break;

        case '<':
        ch = getch(fp);
        if (ch == '=') {
            lextoken = lesym;
            ch = getch(fp);
        }
        else lextoken = ltsym;
        break;

        case '>':
        ch = getch(fp);
        if (ch == '=') {
            lextoken = gesym;
            ch = getch(fp);
        }
        else lextoken = gtsym;
        break;

        case '=':
        ch = getch(fp);
        if (ch == '=') {
            lextoken = eqsym;
            ch = getch(fp);
        }
        else lextoken = assignsym;
        break;

        case '!':
        ch = getch(fp);
        if (ch != '=') {
            fprintf(stderr, "***Error - expected = after ! (%c)\n", ch);
            lextoken = errorsym;
        } else {
            ch = getch(fp);
            lextoken = nesym;
        }
        break;

        // identifiers
        case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
        case 'g': case 'h': case 'i': case 'j': case 'k': case 'l':
        case 'm': case 'n': case 'o': case 'p': case 'q': case 'r':
        case 's': case 't': case 'u': case 'v': case 'w': case 'x':
        case 'y': case 'z':
        {
            int i = 0;
            while (islower(ch) || isdigit(ch)) {
                if (i < MAXIDLEN) identifier[i++] = ch;
                ch = getch(fp);
            }
            identifier[i] = '\0';

            if (strcmp(identifier, "else") == 0) lextoken = elsesym;
            else if (strcmp(identifier, "if ") == 0) lextoken = elsesym;
            else if (strcmp(identifier, "int") == 0) lextoken = elsesym;
            else if (strcmp(identifier, "print") == 0) lextoken = elsesym;
            else if (strcmp(identifier, "read") == 0) lextoken = elsesym;
            else if (strcmp(identifier, "return") == 0) lextoken = elsesym;
            else if (strcmp(identifier, "while") == 0) lextoken = elsesym;
            else lextoken = identifiersym;
            break;
        }
    }

    return lextoken;
}

lextokens lex(FILE *fp) {
    // while ((ch = getch(fp)) != EOF) printf("%c", ch);
    ch = getch(fp);
    while (white(ch)) { ch = getch(fp); }
    
    return get_token(ch, fp);
}

// ############ main
int main() {
    printf("%s", "starting program\n");

    fp = fopen("program.txt", "r"); 
    if (fp == NULL) {
        printf("%s", "error opening file\n");
        return 1;
    }
    lex(fp);

    fclose(fp);
    printf("%s", "ending program\n");
    return 0;
}

