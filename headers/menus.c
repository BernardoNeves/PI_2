#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>
#include "menus.h"
#include "functions.h"
#include "structs.h"

int ChoiceInt;
char Structs;

void MainMenu()
{
   printf("\t--- MAIN MENU ---\n"
          "\t Enter 1 - Airports \n"
          "\t Enter 2 - Airplanes \n"
          "\t Enter 3 - Flights \n"
          "\t Enter 4 - Tickets \n"
          "\n\t Enter 0 - Quit\n");

   ChoiceInt = GetInt(0, 4);
   switch (ChoiceInt)
   {
   case 1:
      Structs = 'A'; // Changes the struct.c switch case in each function to change the file affected by the operation
      break;
   case 2:
      Structs = 'P'; // Changes the struct.c switch case in each function to change the file affected by the operation
      break;
   case 3:
      Structs = 'F'; // Changes the struct.c switch case in each function to change the file affected by the operation
      break;
   case 4:
      Structs = 'T'; // Changes the struct.c switch case in each function to change the file affected by the operation
      break;
   case 0:
      StructWrite();
      _Exit(0); // Exits the program
      break;
   default:
      printf("\n\t//Invalid Option//\n\n");
      MainMenu();
      break;
   }
   OperationMenu(); // after user choses which file should be affected calls operation menu
}

void OperationMenu()
{
   printf("\t--- OPERATION MENU ---\n"
          "\t Enter 1 - List \n"
          "\t Enter 2 - Search \n"
          "\t Enter 3 - Add \n"
          "\t Enter 4 - Remove \n"
          "\t Enter 5 - Modify \n"
          "\n\t Enter 0 - Back\n");

   ChoiceInt = GetInt(0, 5);
   switch (ChoiceInt)
   {
   case 1:
      StructPrint();
      StructReturn();
      break;
   case 2:
      StructSearch();
      StructReturn();
      break;
   case 3:
      StructAdd();
      StructPrint();
      StructReturn();
      break;
   case 4:
      StructRemove();
      StructPrint();
      StructReturn();
      break;
   case 5:
      StructModify();
      StructPrint();
      StructReturn();
      break;
   case 0:
      MainMenu(); // goes back to main menu
      break;
   default:
      printf("\n\t//Invalid Option//\n\n");
      OperationMenu();
      break;
   }
}
