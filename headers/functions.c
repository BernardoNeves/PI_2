#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>
#include "menus.h"
#include "functions.h"
#include "structs.h"

extern char Buffer[200]; /* extern loads de Buffer[200] global string from structs.c in order
to edit it without using functions with arguments */

char GetsUppercase()
{
    gets(Buffer);                            // reads line from user input to Buffer
    for (int i = 0; i < strlen(Buffer); i++) // loops for the length of Buffer
    {
        Buffer[i] = toupper(Buffer[i]); // swaps each letter for it's upper case version
    }
}

int GetInt(int min, int max)
{
    int ChoiceInt = -1;
    char ChoiceChar;

    while (ChoiceInt < min || ChoiceInt > max)
    {
        printf("\n\t> ");
        scanf("%d", &ChoiceInt);
        scanf("%[^\n]", &ChoiceChar);
    }
    system("cls");
    return ChoiceInt;
}
