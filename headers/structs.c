#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>
#include "menus.h"
#include "functions.h"
#include "structs.h"

extern int Structs;
int AirportCount, AirplaneCount, FlightCount, TicketCount, i, j, k, l, SearchResult, SearchResult1, SearchResult2, Connections, Options;
float Expense, Profit, Total;
char Buffer[200], Buffer1[200], FlightBuffer[5][200][200]; // buffer used to read info from the user input or stuct files

FILE *AirportFile, *AirplaneFile, *FlightFile, *TicketFile; // files declarations

Airport Airports[99];   // struct array declaration
Airplane Airplanes[99]; // struct array declaration
Flight Flights[99];     // struct array declaration
Ticket Tickets[99];     // struct array declaration

int StructRead() // read structs from each structfile
{
   AirportFile = fopen("Airports.txt", "r");
   if (AirportFile == NULL) // Checks if file is created correctly
   {
      printf("Failed to open Airports.txt");
      return 1; // returns error message
   }

   fgets(Buffer, 200, AirportFile); // Gets 1 line from the "AirportFile.txt" and puts it in the Buffer

   AirportCount = 0;          // resets AirportCount to recount it while reading
   while (!feof(AirportFile)) // while pointer is not at the end of the file repeat
   {
      // Reads Airport Struct from the Buffer
      sscanf(Buffer, "%[^,], %[^,], %[^,], %d,", &Airports[AirportCount].IATA, &Airports[AirportCount].Name, &Airports[AirportCount].City, &Airports[AirportCount].Altitude);
      fgets(Buffer, 200, AirportFile); // Gets 1 line from the "AirportFile.txt" and puts it in the Buffer again
      AirportCount++;                  // changes array line to create a new airport in "Airports[AirportCount]" and counts how many lines there are
   }
   fclose(AirportFile);

   AirplaneFile = fopen("Airplanes.txt", "r");
   if (AirplaneFile == NULL) // Checks if file is created correctly
   {
      printf("Failed to open Airplanes.txt");
      return 1; // returns error message
   }

   fgets(Buffer, 200, AirplaneFile); // Gets 1 line from the "AirplaneFile.txt" and puts it in the Buffer

   AirplaneCount = 0;          // resets AirplaneCount to recount it while reading
   while (!feof(AirplaneFile)) // while pointer is not at the end of the file repeat
   {
      // Reads Airport Struct from the Buffer
      sscanf(Buffer, "%[^,], %[^,], %[^,], %d, %d, %f,", &Airplanes[AirplaneCount].Plate, &Airplanes[AirplaneCount].Brand, &Airplanes[AirplaneCount].Model, &Airplanes[AirplaneCount].Seats, &Airplanes[AirplaneCount].CruisingSpeed, &Airplanes[AirplaneCount].AverageFuelConsumption);
      fgets(Buffer, 200, AirplaneFile); // Gets 1 line from the "StructFile.txt" and puts it in the Buffer again
      AirplaneCount++;                  // changes array line to create a new airport in "Airplanes[AirplaneCount]" and counts how many lines there are
   }
   fclose(AirplaneFile);

   FlightFile = fopen("Flights.txt", "r");

   if (FlightFile == NULL) // Checks if file is created correctly
   {
      printf("Failed to open Flights.txt");
      return 1; // returns error message
   }

   fgets(Buffer, 200, FlightFile); // Gets 1 line from the "FlightFile.txt" and puts it in the Buffer

   FlightCount = 0;          // resets FlightCount to recount it while reading
   while (!feof(FlightFile)) // while pointer is not at the end of the file repeat
   {
      // Reads Airport Struct from the Buffer
      sscanf(Buffer, "%[^,], %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %[^,], %[^,], %[^,],", &Flights[FlightCount].FlightNumber, &Flights[FlightCount].Departure.Day, &Flights[FlightCount].Departure.Month, &Flights[FlightCount].Departure.Year, &Flights[FlightCount].Departure.Hour, &Flights[FlightCount].Departure.Minute, &Flights[FlightCount].Arrival.Day, &Flights[FlightCount].Arrival.Month, &Flights[FlightCount].Arrival.Year, &Flights[FlightCount].Arrival.Hour, &Flights[FlightCount].Arrival.Minute, &Flights[FlightCount].OriginIATA, &Flights[FlightCount].DestinyIATA, &Flights[FlightCount].AirplanePlate);
      fgets(Buffer, 200, FlightFile); // Gets 1 line from the "StructFile.txt" and puts it in the Buffer again
      FlightCount++;                  // changes array line to create a new airport in "Flights[FlightCount]" and counts how many lines there are
   }
   fclose(FlightFile);

   TicketFile = fopen("Tickets.txt", "r");
   if (TicketFile == NULL) // Checks if file is created correctly
   {
      printf("Failed to open Tickets.txt");
      return 1; // returns error message
   }

   fgets(Buffer, 200, TicketFile); // Gets 1 line from the "TicketFile.txt" and puts it in the Buffer

   TicketCount = 0;          // resets TicketCount to recount it while reading
   while (!feof(TicketFile)) // while pointer is not at the end of the file repeat
   {
      // Reads Airport Struct from the Buffer
      sscanf(Buffer, "%[^,], %[^,], %f, %f, %[^,], %d,", &Tickets[TicketCount].FlightNumber, &Tickets[TicketCount].Seat, &Tickets[TicketCount].Distance, &Tickets[TicketCount].Price, &Tickets[TicketCount].Name, &Tickets[TicketCount].NIF);
      fgets(Buffer, 200, TicketFile); // Gets 1 line from the "StructFile.txt" and puts it in the Buffer again
      TicketCount++;                  // changes array line to create a new airport in "Tickets[TicketCount]" and counts how many lines there are
   }
   fclose(TicketFile);
}

void StructWrite() // write structs to each structfile
{
   AirportFile = fopen("Airports.txt", "w");
   for (i = 0; i < AirportCount; i++) // loops for the number of airports
   {
      // writes all airports
      fprintf(AirportFile, "%s, %s, %s, %d,\n", Airports[i].IATA, Airports[i].Name, Airports[i].City, Airports[i].Altitude);
   }
   fclose(AirportFile);

   AirplaneFile = fopen("Airplanes.txt", "w");
   for (i = 0; i < AirplaneCount; i++) // loops for the number of airplanes
   {
      // writes all airplanes
      fprintf(AirplaneFile, "%s, %s, %s, %d, %d, %.2f,\n", Airplanes[i].Plate, Airplanes[i].Brand, Airplanes[i].Model, Airplanes[i].Seats, Airplanes[i].CruisingSpeed, Airplanes[i].AverageFuelConsumption);
   }
   fclose(AirplaneFile);

   FlightFile = fopen("Flights.txt", "w");
   for (i = 0; i < FlightCount; i++) // loops for the number of flights
   {
      // writes all flights
      fprintf(FlightFile, "%s, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %s, %s, %s,\n", Flights[i].FlightNumber, Flights[i].Departure.Day, Flights[i].Departure.Month, Flights[i].Departure.Year, Flights[i].Departure.Hour, Flights[i].Departure.Minute, Flights[i].Arrival.Day, Flights[i].Arrival.Month, Flights[i].Arrival.Year, Flights[i].Arrival.Hour, Flights[i].Arrival.Minute, Flights[i].OriginIATA, Flights[i].DestinyIATA, Flights[i].AirplanePlate);
   }
   fclose(FlightFile);

   TicketFile = fopen("Tickets.txt", "w");
   for (i = 0; i < TicketCount; i++) // loops for the number of
   {
      // writes all tickets
      fprintf(TicketFile, "%s, %s, %.2f, %.2f, %s, %d,\n", Tickets[i].FlightNumber, Tickets[i].Seat, Tickets[i].Distance, Tickets[i].Price, Tickets[i].Name, Tickets[i].NIF);
   }
   fclose(TicketFile);
}

void StructPrint() // print struct arrays
{
   system("cls"); // clears console

   switch (Structs) // switch case for witch file to be affected by the operation
   {
   case 'A':
      for (i = 0; i < AirportCount; i++) // repeat for the number of airports
      {
         // print airport info
         printf("\n IATA: %s | Name: %s | City: %s | Altitude: %dm \n", Airports[i].IATA, Airports[i].Name, Airports[i].City, Airports[i].Altitude);
      }
      break;
   case 'P':
      for (i = 0; i < AirplaneCount; i++) // repeat for the number of airplanes
      {
         // print airpane info
         printf("\n Brand: %s | Model: %s | Plate: %s | Seats: %d | Cruising Speed: %d KM/H | Average Fuel Consumption: %.2f L/ 100Km \n", Airplanes[i].Brand, Airplanes[i].Model, Airplanes[i].Plate, Airplanes[i].Seats, Airplanes[i].CruisingSpeed, Airplanes[i].AverageFuelConsumption);
      }
      break;
   case 'F':
      for (i = 0; i < FlightCount; i++) // repeat for the number of flights
      {
         // print flight info
         printf("\n Flight Number: %s | Departure Date: %02d/%02d/%04d %02d:%02d | Arrival Date: %02d/%02d/%04d %02d:%02d | Origin IATA: %s | Destiny IATA: %s | Airplane Plate: %s ", Flights[i].FlightNumber, Flights[i].Departure.Day, Flights[i].Departure.Month, Flights[i].Departure.Year, Flights[i].Departure.Hour, Flights[i].Departure.Minute, Flights[i].Arrival.Day, Flights[i].Arrival.Month, Flights[i].Arrival.Year, Flights[i].Arrival.Hour, Flights[i].Arrival.Minute, Flights[i].OriginIATA, Flights[i].DestinyIATA, Flights[i].AirplanePlate);
         Finance();
      }
      break;
   case 'T':
      for (i = 0; i < TicketCount; i++) // repeat for the number of tickets
      {
         // print ticket info
         printf("\n Flight Number: %s | Seat: %s | Distance: %.1fKm | Price: %.2f | Name: %s | NIF: %d \n", Tickets[i].FlightNumber, Tickets[i].Seat, Tickets[i].Distance, Tickets[i].Price, Tickets[i].Name, Tickets[i].NIF);
      }
      break;
   }
}

void StructSearch() // search for an item on a struct array
{
   int Found = 0, Cancel = 1, LetterCount = 0;

   switch (Structs) // switch case for witch file to be affected by the operation
   {
   case 'A':
      do
      {
         printf("\nSearch IATA: ");
         GetsUppercase();                   // reads line from user input to Buffer in all UPPERCASE
         system("cls");                     // clears the console
         for (i = 0; i < AirportCount; i++) // loops for the number of airports
         {
            LetterCount = 0; // resets LetterCount each time it changes line so it counts every ine correctly

            for (j = 0; j < strlen(Buffer); j++) // loops for the length of the Buffer
            {
               if (Buffer[j] == Airports[i].IATA[j]) // checks if j buffer letter is equal to j array letter
               {
                  Cancel = 0;    // changes cancel to 0 to stop the program from printing the not found error message
                  LetterCount++; // counts the number of correct letters
               }
               else
               {
                  Cancel = 1; // changes cancel to 1 to print the not found error message
               }
            }
            if (Buffer[0] < Airports[i].IATA[0]) // compares IATA in the buffer with each IATA until it finds a lower one in alphabetic order, finding it's spot on the next line of the array
            {
               break;
            }
            if (Cancel == 0 && (LetterCount == strlen(Buffer))) // checks if all the letter are correct by comparing the letter count with the buffer length
            {
               Found = 1;        // changes found to 1 to avoid not found error message
               SearchResult = i; // saves the search result index in SearchResult
               // prints the search result info
               printf("\n IATA: %s | Name: %s | City: %s | Altitude: %dm \n", Airports[i].IATA, Airports[i].Name, Airports[i].City, Airports[i].Altitude);
            }
         }
      } while (strlen(Buffer) != strlen(Airports[SearchResult].IATA)); // repeat search until we find a complete match
      break;

   case 'P':
      StructPrint();
      do
      {
         printf("\nSearch Brand: ");
         GetsUppercase();                    // reads line from user input to Buffer in all UPPERCASE
         system("cls");                      // clears the console
         for (i = 0; i < AirplaneCount; i++) // loops for the number of airplanes
         {
            LetterCount = 0; // resets LetterCount each time it changes line so it counts every ine correctly

            for (j = 0; j < strlen(Buffer); j++) // loops for the length of the Buffer
            {
               if (Buffer[j] == Airplanes[i].Brand[j]) // checks if j buffer letter is equal to j array letter
               {
                  Cancel = 0;    // changes cancel to 0 to stop the program from printing the not found error message
                  LetterCount++; // counts the number of correct letters
               }
               else
               {
                  Cancel = 1; // changes cancel to 1 to print the not found error message
               }
            }
            if (Buffer[0] > Airplanes[i].Brand[0]) // compares Brand in the buffer with each Brand until it finds a lower one in alphabetic order, finding it's spot on the next line of the array
            {
               break;
            }
            if (Cancel == 0 && (LetterCount == strlen(Buffer))) // checks if all the letter are correct by comparing the letter count with the buffer length
            {
               Found++;           // increments found to avoid not found error message and count how many have they found
               SearchResult2 = i; // saves the search result index in SearchResult2
               // prints the search result info
               printf("\n Brand: %s | Model: %s | Plate: %s | Seats: %d | Cruising Speed: %d KM/H | Average Fuel Consumption: %.2f L/ 100Km \n", Airplanes[i].Brand, Airplanes[i].Model, Airplanes[i].Plate, Airplanes[i].Seats, Airplanes[i].CruisingSpeed, Airplanes[i].AverageFuelConsumption);
            }
         }
      } while (strlen(Buffer) != strlen(Airplanes[SearchResult2].Brand)); // repeat search until we find a complete match

      if (Found > 1) // if there is more than 1 airplane of that brand then search them by model
      {
         Found = 0; // resets Found to count the models found
         do
         {
            printf("\nSearch Model: ");
            GetsUppercase(); // reads line from user input to Buffer in all UPPERCASE
            system("cls");   // clears the console
            printf("\tBrand: %s\n", Airplanes[SearchResult2].Brand);

            for (i = 0; i < AirplaneCount; i++) // loops for the number of airplanes
            {
               LetterCount = 0; // resets LetterCount each time it changes line so it counts every ine correctly

               for (j = 0; j < strlen(Buffer); j++) // loops for the length of the Buffer
               {
                  // checks if j buffer letter is equal to j array letter and if the Brand is the same
                  if ((Buffer[j] == Airplanes[i].Model[j]) && (strcmp(Airplanes[i].Brand, Airplanes[SearchResult2].Brand) == 0))
                  {
                     Cancel = 0;    // changes cancel to 0 to stop the program from printing the not found error message
                     LetterCount++; // counts the number of correct letters
                  }
                  else
                  {
                     Cancel = 1; // changes cancel to 1 to print the not found error message
                  }
               }
               if (Buffer[0] > Airplanes[i].Model[0]) // compares Model in the buffer with each Model until it finds a lower one in alphabetic order, finding it's spot on the next line of the array
               {
                  break;
               }
               if (Cancel == 0 && (LetterCount == strlen(Buffer))) // checks if all the letter are correct by comparing the letter count with the buffer length
               {
                  Found++;           // increments found to avoid not found error message and count how many have they found
                  SearchResult1 = i; // saves the search result index in SearchResult1
                  // prints the search result info
                  printf("\n Model: %s | Plate: %s | Seats: %d | Cruising Speed: %d KM/H | Average Fuel Consumption: %.2f L/ 100Km \n", Airplanes[i].Model, Airplanes[i].Plate, Airplanes[i].Seats, Airplanes[i].CruisingSpeed, Airplanes[i].AverageFuelConsumption);
               }
            }
         } while (strlen(Buffer) != strlen(Airplanes[SearchResult1].Model)); // repeat search until we find a complete match
      }

      if (Found > 1) // if there is more than 1 airplane of that model then search them by plate
      {
         Found = 0;
         do
         {
            printf("\nSearch Plate: ");
            GetsUppercase(); // reads line from user input to Buffer in all UPPERCASE
            system("cls");   // clears the console
            printf("\tModel: %s\n", Airplanes[SearchResult1].Model);

            for (i = 0; i < AirplaneCount; i++) // loops for the number of airplanes
            {
               LetterCount = 0; // resets LetterCount each time it changes line so it counts every ine correctly

               for (j = 0; j < strlen(Buffer); j++) // loops for the length of the Buffer
               {
                  // checks if j buffer letter is equal to j array letter and if the Brand is the same and if the Model is the same
                  if ((Buffer[j] == Airplanes[i].Plate[j]) && (strcmp(Airplanes[i].Model, Airplanes[SearchResult1].Model) == 0) && (strcmp(Airplanes[i].Brand, Airplanes[SearchResult2].Brand) == 0))
                  {
                     Cancel = 0;    // changes cancel to 0 to stop the program from printing the not found error message
                     LetterCount++; // counts the number of correct letters
                  }
                  else
                  {
                     Cancel = 1; // changes cancel to 1 to print the not found error message
                  }
               }
               if (Buffer[0] < Airplanes[i].Plate[0]) // compares Plate in the buffer with each Plate until it finds a lower one in alphabetic order, finding it's spot on the next line of the array
               {
                  break;
               }
               if (Cancel == 0 && (LetterCount == strlen(Buffer))) // checks if all the letter are correct by comparing the letter count with the buffer length
               {
                  Found = 1;        // changes found to 1 to avoid not found error message
                  SearchResult = i; // saves the search result index in SearchResult
                  // prints the search result info
                  printf("\n Plate: %s | Seats: %d | Cruising Speed: %d KM/H | Average Fuel Consumption: %.2f L/ 100Km \n", Airplanes[i].Plate, Airplanes[i].Seats, Airplanes[i].CruisingSpeed, Airplanes[i].AverageFuelConsumption);
               }
            }
         } while (strlen(Buffer) != strlen(Airplanes[SearchResult].Plate)); // repeat search until we find a complete match
      }
      system("cls"); // clears the console
      // prints the search result info
      printf("\n Brand: %s | Model: %s | Plate: %s | Seats: %d | Cruising Speed: %d KM/H | Average Fuel Consumption: %.2f L/ 100Km \n", Airplanes[SearchResult].Brand, Airplanes[SearchResult].Model, Airplanes[SearchResult].Plate, Airplanes[SearchResult].Seats, Airplanes[SearchResult].CruisingSpeed, Airplanes[SearchResult].AverageFuelConsumption);
      break;

   case 'F':
      StructPrint();
      do
      {
         printf("\nSearch Flight Number: ");
         GetsUppercase();                  // reads line from user input to Buffer in all UPPERCASE
         system("cls");                    // clears the console
         for (i = 0; i < FlightCount; i++) // loops for the number of flights
         {
            LetterCount = 0; // resets LetterCount each time it changes line so it counts every ine correctly

            for (j = 0; j < strlen(Buffer); j++) // loops for the length of the Buffer
            {
               if (Buffer[j] == Flights[i].FlightNumber[j]) // checks if j buffer letter is equal to j array letter
               {
                  Cancel = 0;    // changes cancel to 0 to stop the program from printing the not found error message
                  LetterCount++; // counts the number of correct letters
               }
               else
               {
                  Cancel = 1; // changes cancel to 1 to print the not found error message
               }
            }
            if (Buffer[0] < Flights[i].FlightNumber[0]) // compares FlightNumber in the buffer with each FlightNumber until it finds a lower one in alphabetic order, finding it's spot on the next line of the array
            {
               break;
            }
            if (Cancel == 0 && (LetterCount == strlen(Buffer))) // checks if all the letter are correct by comparing the letter count with the buffer length
            {
               Found = 1;        // changes found to 1 to avoid not found error message
               SearchResult = i; // saves the search result index in SearchResult
               // prints the search result info
               printf("\n Flight Number: %s | Departure Date: %02d/%02d/%04d %02d:%02d | Arrival Date: %02d/%02d/%04d %02d:%02d | Origin IATA: %s | Destiny IATA: %s | Airplane Plate: %s ", Flights[i].FlightNumber, Flights[i].Departure.Day, Flights[i].Departure.Month, Flights[i].Departure.Year, Flights[i].Departure.Hour, Flights[i].Departure.Minute, Flights[i].Arrival.Day, Flights[i].Arrival.Month, Flights[i].Arrival.Year, Flights[i].Arrival.Hour, Flights[i].Arrival.Minute, Flights[i].OriginIATA, Flights[i].DestinyIATA, Flights[i].AirplanePlate);
               Finance();
            }
         }
      } while (strlen(Buffer) != strlen(Flights[SearchResult].FlightNumber)); // repeat search until we find a complete match
      break;
   case 'T':
      StructPrint();
      do
      {
         printf("\nSearch Flight Number: ");
         GetsUppercase();                  // reads line from user input to Buffer in all UPPERCASE
         system("cls");                    // clears the console
         for (i = 0; i < TicketCount; i++) // loops for the number of flights
         {
            LetterCount = 0; // resets LetterCount each time it changes line so it counts every ine correctly

            for (j = 0; j < strlen(Buffer); j++) // loops for the length of the Buffer
            {
               if (Buffer[j] == Tickets[i].FlightNumber[j]) // checks if j buffer letter is equal to j array letter
               {
                  Cancel = 0;    // changes cancel to 0 to stop the program from printing the not found error message
                  LetterCount++; // counts the number of correct letters
               }
               else
               {
                  Cancel = 1; // changes cancel to 1 to print the not found error message
               }
            }
            if (Buffer[0] < Tickets[i].FlightNumber[0]) // compares FlightNumber in the buffer with each FlightNumber until it finds a lower one in alphabetic order, finding it's spot on the next line of the array
            {
               break;
            }
            if (Cancel == 0 && (LetterCount == strlen(Buffer))) // checks if all the letter are correct by comparing the letter count with the buffer length
            {
               Found = 1;        // changes found to 1 to avoid not found error message
               SearchResult = i; // saves the search result index in SearchResults
               // prints the search result info
               printf("\n Flight Number: %s | Seat: %s | Distance: %.1fKm | Price: %.2f | Name: %s | NIF: %d \n", Tickets[i].FlightNumber, Tickets[i].Seat, Tickets[i].Distance, Tickets[i].Price, Tickets[i].Name, Tickets[i].NIF);
            }
         }
      } while (strlen(Buffer) != strlen(Tickets[SearchResult].FlightNumber)); // repeat search until we find a complete match
      break;
   }

   if (Cancel == 1 && Found == 0) // if search didn't find anything print not found error message
   {
      printf("\t NOT FOUND \n");
   }
}

void StructAdd() // add an item to a struct array
{
   char Name[200], NIF[200];

   switch (Structs) // switch case for witch file to be affected by the operation
   {
   case 'A':
      do
      {
         printf("New IATA (Syntax: 3 Letters): ");
         GetsUppercase(); // reads line from user input to Buffer in all UPPERCASE
      } while ((strlen(Buffer) != 3) || Buffer[0] < 'A' || Buffer[0] > 'Z' || Buffer[1] < 'A' || Buffer[1] > 'Z' || Buffer[2] < 'A' || Buffer[2] > 'Z');
      // repeats until IATA has a correct syntax

      for (i = 0; i < AirportCount; i++) // loops for the number of airports
      {
         if (strcmp(Buffer, Airports[i].IATA) == 0) // checks if IATA already exists in "Airports[]"
         {
            printf("IATA already exists, either input another IATA or modify the old airport from the list\n\n");
            getch(); // pauses program until user presses a key
            return;  // end function
         }
      }

      AirportCount++; // adds 1 to the "AirportCount" so that "StructWrite" writes one more airport than the number of airports read, in order to write the new one aswell

      for (i = 0; i < AirportCount; i++) // loops for the number of airports
      {
         if (strcmp(Buffer, Airports[i].IATA) < 0 || i == AirportCount - 1) // compares IATA in the buffer with each IATA until it finds a lower one in alphabetic order, finding it's spot on the next line of the array || no more lines in the array
         {
            for (j = AirportCount; j > i; j--) // loops from the last airport until the new IATA index
            {
               // pushes all the Airports that com after the new one in alphabetic order 1 position lower to make space for the new one on top
               strcpy(Airports[j].IATA, Airports[j - 1].IATA);
               strcpy(Airports[j].Name, Airports[j - 1].Name);
               strcpy(Airports[j].City, Airports[j - 1].City);
               Airports[j].Altitude = Airports[j - 1].Altitude;
            }
            // Write new airport info to "Airports[]"
            sscanf(Buffer, "%[^\n]", &Airports[i].IATA); // Reads IATA from the Buffer

            printf("New Name: ");
            gets(Airports[i].Name); // reads line from user input to Airports[i].Name

            printf("New City: ");
            gets(Airports[i].City); // reads line from user input to Airports[i].City

            printf("New Altitude: ");
            scanf(" %d", &Airports[i].Altitude); // Reads Altitude from the user input
            break;
         }
      }
      break;

      // FIXME
   case 'P':

      printf("New Model: ");
      gets(Buffer1); // reads line from user input to Buffer1

      for (i = 0; i < AirplaneCount; i++) // loops for the number of airplanes
      {
         if (strcmp(Buffer1, Airplanes[i].Model) == 0) // checks if Model already exists in "Airplanes[]"
         {
            printf("Model already exists, either input another Model or modify the old airplane from the list\n\n");
            getch();
            return;
         }
         else
         {
            printf("New Brand: ");
            GetsUppercase(); // reads line from user input to Buffer in all UPPERCASE
            break;
         }
      }

      AirplaneCount++; // adds 1 to the "AirplaneCount" so that "StructWrite" writes one more airport than the number of airports read, in order to write the new one aswell

      for (i = 0; i < AirplaneCount; i++) // loops for the number of airplanes
      {
         if (strcmp(Buffer, Airplanes[i].Brand) < 0 || i == AirplaneCount - 1) // compares Brand in the buffer with each Brand until it finds a lower one in alphabetic order, finding it's Brand spot on the next line of the array || no more lines in the array
         {
            for (j = AirplaneCount; j > i; j--) // loops from the last aiplane until the new brand index
            {
               // pushes all the Airplanes that com after the new one in alphabetic order 1 position lower to make space for the new one on top
               strcpy(Airplanes[j].Plate, Airplanes[j - 1].Plate);
               strcpy(Airplanes[j].Brand, Airplanes[j - 1].Brand);
               strcpy(Airplanes[j].Model, Airplanes[j - 1].Model);
               Airplanes[j].Seats = Airplanes[j - 1].Seats;
               Airplanes[j].CruisingSpeed = Airplanes[j - 1].CruisingSpeed;
               Airplanes[j].AverageFuelConsumption = Airplanes[j - 1].AverageFuelConsumption;
            }
            // Write new airport info to "Airplanes[]"
            sscanf(Buffer1, "%[^\n]", &Airplanes[i].Model); // Reads Model from the Buffer1
            sscanf(Buffer, "%[^\n]", &Airplanes[i].Brand);  // Reads Brand from the Buffer

            printf("New Seats: ");
            scanf(" %d", &Airplanes[i].Seats); // Reads Seats from from user input

            printf("New Cruising Speed: ");
            scanf(" %d", &Airplanes[i].CruisingSpeed); // Reads CruisingSpeed from from user input

            printf("New Average Fuel Consumption: ");
            scanf(" %f", &Airplanes[i].AverageFuelConsumption); // Reads AverageFuelConsumption from from user input

            // One by one move boundary of unsorted subarray
            for (i = 0; i < AirplaneCount - 1; i++)
            {
               // Find the minimum element in unsorted array
               k = i;
               for (j = i + 1; j < AirplaneCount; j++)
               {
                  if ((strcmp(Airplanes[j].Model, Airplanes[k].Model) < 0) && (strcmp(Airplanes[j].Brand, Airplanes[k].Brand) == 0))
                  {
                     k = j;
                  }
               }
               // Swap the found minimum element
               // with the first element

               int temp;
               strcpy(Buffer, Airplanes[k].Model);
               strcpy(Airplanes[k].Model, Airplanes[i].Model);
               strcpy(Airplanes[i].Model, Buffer);

               temp = Airplanes[k].Seats;
               Airplanes[k].Seats = Airplanes[i].Seats;
               Airplanes[i].Seats = temp;

               temp = Airplanes[k].CruisingSpeed;
               Airplanes[k].CruisingSpeed = Airplanes[i].CruisingSpeed;
               Airplanes[i].CruisingSpeed = temp;

               temp = Airplanes[k].AverageFuelConsumption;
               Airplanes[k].AverageFuelConsumption = Airplanes[i].AverageFuelConsumption;
               Airplanes[i].AverageFuelConsumption = temp;
            }
            break;
         }
      }
      break;

   case 'F':

      printf("New Flight Number: ");
      GetsUppercase(); // reads line from user input to Buffer in all UPPERCASE

      for (i = 0; i < FlightCount; i++) // loops for the number of flights
      {
         if (strcmp(Buffer, Flights[i].FlightNumber) == 0) // checks if FlightNumber already exists in "Flights[]"
         {
            printf("FlightNumber already exists, either input another FlightNumber or modify the old flight from the list\n\n");
            getch();
            return;
         }
      }

      FlightCount++; // adds 1 to the "FlightCount" so that "StructWrite" writes one more airport than the number of airports read, in order to write the new one aswell

      for (i = 0; i < FlightCount; i++) // loops for the number of flights
      {
         if (strcmp(Buffer, Flights[i].FlightNumber) < 0 || i == FlightCount - 1) // compares FlightNumber in the buffer with each FlightNumber until it finds a lower one in alphabetic order, finding it's spot on the next line of the array || no more lines in the array
         {
            for (j = FlightCount; j > i; j--)
            {
               // pushes all the Flights that com after the new one in alphabetic order 1 position lower to make space for the new one on top
               strcpy(Flights[j].FlightNumber, Flights[j - 1].FlightNumber);
               Flights[j].Departure.Day = Flights[j - 1].Departure.Day;
               Flights[j].Departure.Month = Flights[j - 1].Departure.Month;
               Flights[j].Departure.Year = Flights[j - 1].Departure.Year;
               Flights[j].Departure.Hour = Flights[j - 1].Departure.Hour;
               Flights[j].Departure.Minute = Flights[j - 1].Departure.Minute;
               Flights[j].Arrival.Day = Flights[j - 1].Arrival.Day;
               Flights[j].Arrival.Month = Flights[j - 1].Arrival.Month;
               Flights[j].Arrival.Year = Flights[j - 1].Arrival.Year;
               Flights[j].Arrival.Hour = Flights[j - 1].Arrival.Hour;
               Flights[j].Arrival.Minute = Flights[j - 1].Arrival.Minute;
               strcpy(Flights[j].OriginIATA, Flights[j - 1].OriginIATA);
               strcpy(Flights[j].DestinyIATA, Flights[j - 1].DestinyIATA);
               strcpy(Flights[j].AirplanePlate, Flights[j - 1].AirplanePlate);
            }
            // Write new airport info to "Flights[]"
            sscanf(Buffer, "%[^\n]", &Flights[i].FlightNumber); // Reads FlightNumber from the Buffer

            printf("New Departure Date and Time (DD,MM,YYYY,hh,mm): ");
            scanf(" %d,%d,%d,%d,%d", &Flights[i].Departure.Day, &Flights[i].Departure.Month, &Flights[i].Departure.Year, &Flights[i].Departure.Hour, &Flights[i].Departure.Minute);
            // Reads Departure Date from user input

            printf("New Arrival Date and Time (DD,MM,YYYY,hh,mm): ");
            scanf(" %d,%d,%d,%d,%d", &Flights[i].Arrival.Day, &Flights[i].Arrival.Month, &Flights[i].Arrival.Year, &Flights[i].Arrival.Hour, &Flights[i].Arrival.Minute);

            break;
         }
      }
      break;

   case 'T':
      Link();

      for (int m = 0; m < Connections; m++)
      {
         /*RETURNS{ KEEP MULTIPLE ERRORS TO ORGANIZE BETTER
            0 - Error | User canceled ( "0" ), just go back
            1 - Success | Flight not full so just add the ticket
            2 - Error | No other planes found, go back
            3 - Error | Plane 2 has more bought tickets than flight 1 can handle, go back
            4 - Error/Success | Planes swapped successfully, announce the player and go back with a getch()
         }*/
         int available = CheckAvailability();

         if (available == 1)
         {
            TicketCount++;                    // adds 1 to the "TicketCount" so that "StructWrite" writes one more airport than the number of airports read, in order to write the new one aswell
            for (i = 0; i < TicketCount; i++) // loops for the number of tickets
            {
               if (strcmp(FlightBuffer[m][Options], Tickets[i].FlightNumber) < 0 || i == TicketCount - 1) // compares FlightNumber in the buffer with each FlightNumber until it finds a lower one in alphabetic order, finding it's spot on the next line of the array || no more lines in the array
               {
                  // Write new airport info to "Tickets[]"
                  sscanf(FlightBuffer[m][Options], "%[^\n]", &Tickets[i].FlightNumber); // Reads FlightNumber from the Buffer
                  for (j = TicketCount; j > i; j--)
                  {
                     // pushes all the Tickets that com after the new one in alphabetic order 1 position lower to make space for the new one on top
                     strcpy(Tickets[j].FlightNumber, Tickets[j - 1].FlightNumber);
                     strcpy(Tickets[j].Seat, Tickets[j - 1].Seat);
                     Tickets[j].Distance = Tickets[j - 1].Distance;
                     Tickets[j].Price = Tickets[j - 1].Price;

                     strcpy(Tickets[j].Name, Tickets[j - 1].Name);
                     Tickets[j].NIF = Tickets[j - 1].NIF;
                  }

                  printf("New Seat: ");
                  gets(Buffer);                               // reads line from user input to Buffer
                  sscanf(Buffer, "%[^\n]", &Tickets[i].Seat); // Reads Seat from the Buffer

                  printf("New Distance: ");
                  gets(Buffer);                                  // reads line from user input to Buffer
                  sscanf(Buffer, " %.2f", &Tickets[i].Distance); // Reads Distance from the Buffer

                  printf("New Price: ");
                  gets(Buffer);                               // reads line from user input to Buffer
                  sscanf(Buffer, " %.2f", &Tickets[i].Price); // Reads Price from the Buffer

                  if (m == 0)
                  {
                     printf("New Name: ");
                     gets(Name); // reads line from user input to Buffer

                     printf("New NIF: ");
                     gets(NIF); // reads line from user input to Buffer
                  }
                  sscanf(Name, "%[^\n]", &Tickets[i].Name); // Reads Name from the Buffer
                  sscanf(NIF, "%d", &Tickets[i].NIF);       // Reads NIF from the Buffer
                  for (j = 0; j < TicketCount - 1; j++)
                  {
                     // Find the minimum element in unsorted array
                     l = i;
                     for (k = i + 1; k < TicketCount; k++)
                     {
                        if ((Tickets[k].NIF < Tickets[k].NIF) && (strcmp(Tickets[k].FlightNumber, Tickets[l].FlightNumber) == 0))
                        {
                           l = j;
                        }
                     }
                     int temp = Tickets[k].NIF;
                     Tickets[k].NIF = Tickets[i].NIF;
                     Tickets[i].NIF = temp;
                  }
                  break;
               }
            }
         }
         else if (available == 0)
         {
            system("cls");
            printf("\nProcess canceled.");
         }
         else if (available == 2)
         {
            system("cls");
            printf("\nNo other planes found, process canceled.");
         }
         else if (available == 3)
         {
            system("cls");
            printf("\nCan't swap planes because the 2nd plane has more used places than the capacity of the 1st plane.");
         }
         else if (available == 4)
         {
            system("cls");
            printf("\nPlanes swapped successfully!");
         }
      }
      printf("\nPress any key to continue..");
      getch();
      break;
   }
}

void StructRemove() // remove  an item from a struct array
{
   StructPrint();
   switch (Structs) // switch case for witch file to be affected by the operation
   {
   case 'A':
      do
      {
         StructSearch();
      } while (strlen(Buffer) < 3);

      for (j = SearchResult + 1; j <= AirportCount; j++)
      {
         // pushes all the Airports that com after the selected one 1 position higher to close the space of the old airport
         strcpy(Airports[j - 1].IATA, Airports[j].IATA);
         strcpy(Airports[j - 1].Name, Airports[j].Name);
         strcpy(Airports[j - 1].City, Airports[j].City);
         Airports[j - 1].Altitude = Airports[j].Altitude;
      }
      AirportCount--; // subtracts 1 to the "AirportCount" so that "StructWrite" writes one less airport than the number of airports read, in order to write all the airports correctly
      break;
   case 'P':
      do
      {
         StructSearch();
      } while (strlen(Buffer) < 3);

      for (j = SearchResult + 1; j <= AirplaneCount; j++)
      {
         // pushes all the Airports that com after the selected one 1 position higher to close the space of the old airplane
         strcpy(Airplanes[j - 1].Plate, Airplanes[j].Plate);
         strcpy(Airplanes[j - 1].Brand, Airplanes[j].Brand);
         strcpy(Airplanes[j - 1].Model, Airplanes[j].Model);
         Airplanes[j - 1].Seats = Airplanes[j].Seats;
         Airplanes[j - 1].CruisingSpeed = Airplanes[j].CruisingSpeed;
         Airplanes[j - 1].AverageFuelConsumption = Airplanes[j].AverageFuelConsumption;
      }
      AirplaneCount--; // subtracts 1 to the "AirplaneCount" so that "StructWrite" writes one less airplane than the number of airplanes read, in order to write all the airports correctly
      break;
   case 'F':
      do
      {
         StructSearch();
      } while (strlen(Buffer) < 3);

      for (j = SearchResult + 1; j <= FlightCount; j++)
      {
         // pushes all the Airports that com after the selected one 1 position higher to close the space of the old flight
         strcpy(Flights[j - 1].OriginIATA, Flights[j].OriginIATA);
         strcpy(Flights[j - 1].DestinyIATA, Flights[j].DestinyIATA);
         strcpy(Flights[j - 1].AirplanePlate, Flights[j].AirplanePlate);
         strcpy(Flights[j - 1].FlightNumber, Flights[j].FlightNumber);
         Flights[j - 1].Departure.Day = Flights[j].Departure.Day;
         Flights[j - 1].Departure.Month = Flights[j].Departure.Month;
         Flights[j - 1].Departure.Year = Flights[j].Departure.Year;
         Flights[j - 1].Departure.Hour = Flights[j].Departure.Hour;
         Flights[j - 1].Departure.Minute = Flights[j].Departure.Minute;
         Flights[j - 1].Arrival.Day = Flights[j].Arrival.Day;
         Flights[j - 1].Arrival.Month = Flights[j].Arrival.Month;
         Flights[j - 1].Arrival.Year = Flights[j].Arrival.Year;
         Flights[j - 1].Arrival.Hour = Flights[j].Arrival.Hour;
         Flights[j - 1].Arrival.Minute = Flights[j].Arrival.Minute;
      }
      FlightCount--; // subtracts 1 to the "FlightCount" so that "StructWrite" writes one less flight than the number of flights read, in order to write all the airports correctly
      break;
   case 'T':
      do
      {
         StructSearch();
      } while (strlen(Buffer) < 3);

      for (j = SearchResult + 1; j <= TicketCount; j++)
      {
         // pushes all the Airports that com after the selected one 1 position higher to close the space of the old ticket
         strcpy(Tickets[j - 1].FlightNumber, Tickets[j].FlightNumber);
         strcpy(Tickets[j].Seat, Tickets[j - 1].Seat);
         Tickets[j - 1].Distance = Tickets[j].Distance;
         Tickets[j - 1].Price = Tickets[j].Price;

         strcpy(Tickets[j - 1].Name, Tickets[j].Name);
         Tickets[j - 1].NIF = Tickets[j].NIF;
      }
      TicketCount--; // subtracts 1 to the "TicketCount" so that "StructWrite" writes one less ticket than the number of tickets read, in order to write all the airports correctly
      break;
   }
}

void StructModify() // modify  an item from a struct array
{
   StructRemove(); // removes the line
   StructAdd();    // re adds the line
}

void StructReturn() // return to the operation menu after the end of an operation
{
   printf("\n\tPress any key to go back");
   getch();         // pauses program until user presses a key
   system("cls");   // clears the console
   OperationMenu(); // returns to the operation menu
}

Flight GetFlightFromTicket(char TicketFlightNumber[200]) // Gets a flight struct from a given flightnumber of a ticket
{
   for (int i = 0; i < FlightCount; i++) // Runs trough all the flights available
   {
      if (strcmp(Flights[i].FlightNumber, TicketFlightNumber) == 0)
      { // Checks for a match on a flight number between the given one and the available flights
         return Flights[i];
      }
   }
}

Airplane GetAirplaneFromFlight(Flight FlightId) // Gets an Airplane struct from a given flight struct
{
   for (int i = 0; i < AirplaneCount; i++)
   { // Runs trough all the airplanes available
      if (strcmp(Airplanes[i].Plate, FlightId.AirplanePlate) == 0)
      { // Checks for a match on an airplane plate number between the given one and the available airplanes
         return Airplanes[i];
      }
   }
}

int GetFlightFromAirplanePlate(char AirplanePlate[7])
{ // Gets a flight index from a given airplane plate
   for (int i = 0; i < FlightCount; i++)
   { // Runs trough all the flights available
      if (strcmp(Flights[i].AirplanePlate, AirplanePlate) == 0)
      { // Checks for a match on the airplane plate between the given one and the available ones.
         return i;
      }
   }
   return -1; // Returns -1 as a not found value
}

int *CheckForOtherAirplanes(Airplane CurrentAirplane)
{ // returns the pointer to the foundAirplanes array
   static int foundAirplanes[99];
   int j = 0;

   for (int i = 0; i < 99; i++)
   {
      foundAirplanes[i] = -1; // reset values for future reference
   }

   for (int i = 0; i < AirplaneCount; i++)
   {
      if (strcmp(Airplanes[i].Plate, CurrentAirplane.Plate) != 0 && Airplanes[i].Seats > CurrentAirplane.Seats)
      {
         foundAirplanes[j] = i;
         j++;
      }
   }

   return foundAirplanes;
}

int GetBoughtTicketsForFlight(char FlightNumber[99])
{ // Gets the amount of bought tickets for a given flight
   int boughtTickets = 0;

   for (int i = 0; i < TicketCount; i++)
   { // Runs trough all the tickets
      if (strcmp(Tickets[i].FlightNumber, FlightNumber) == 0)
      {                   // Checks if the flight number matches
         boughtTickets++; // Increments the boughtTickets amount.
      }
   }

   return boughtTickets;
}

int CheckAvailability()
{
   int TicketsForPlane = 0; // Quantity of tickets bought for the plane
   char newPlateBuffer[7];
   int foundPlate = 0;

   // Getting current data
   Flight CurrentFlight = GetFlightFromTicket(Buffer);
   Airplane CurrentAirplane = GetAirplaneFromFlight(CurrentFlight);

   for (int i = 0; i <= TicketCount; i++)
   {                                                    // Count tickets on that plane.
      if (strcmp(Buffer, Tickets[i].FlightNumber) == 0) // Checks if buffer == flight number to increment the tickets for that plane
      {
         TicketsForPlane++;
      }
   }

   // Check if plane is full
   if (CurrentAirplane.Seats <= TicketsForPlane) // Ex: if 140 seats is less/ than 141 (incremented on add new ticket start)
   {
      // If full then start swap process

      // Search for other airplanes
      int *otherPlanes = CheckForOtherAirplanes(CurrentAirplane);
      int otherPlanesCount = 0; // to avoid looking for a lot of planes when they don't exist

      for (int i = 0; i < 99; i++)
      {
         if (i == 0 && otherPlanes[0] == -1)
         { // checks if there's actually other planes
            break;
         }

         if (otherPlanes[i] == -1)
         { // stops when it finds the next -1
            otherPlanesCount = i - 1;
            break;
         }
      }

      if (otherPlanesCount > 0)
      {
         // In case there's other planes, ask the user to choose one for the swap process
         while (foundPlate != 1)
         { // Loop to get a valid plate or "0" to cancel de swap process
            system("cls");
            printf("Planes available for swap:\n");
            for (int i = 0; i < otherPlanesCount; i++)
            { // Prints all the available airplanes for the user to choose
               printf("\n Brand: %s | Model: %s | Plate: %s | Seats: %d | Cruising Speed: %d KM/H | Average Fuel Consumption: %.2f L/ 100Km \n", Airplanes[otherPlanes[i]].Brand, Airplanes[otherPlanes[i]].Model, Airplanes[otherPlanes[i]].Plate, Airplanes[otherPlanes[i]].Seats, Airplanes[otherPlanes[i]].CruisingSpeed, Airplanes[otherPlanes[i]].AverageFuelConsumption);
            }
            printf("\nInsert the plate of the plane you want to swap this one with.");
            printf("\nInsert 0 to cancel.\n");
            gets(newPlateBuffer); // Gets the user answer to the buffer

            if (newPlateBuffer[0] == '0')
            { // Verify buffer for the 0 input to cancel the swap process
               return 0;
            }
            else
            { // If the buffer has something else than a 0 (supposed to be an airplane plate)
               for (int i = 0; i < otherPlanesCount; i++)
               { // Verifies the answer to find a plate
                  if (strcmp(newPlateBuffer, Airplanes[otherPlanes[i]].Plate) == 0)
                  {
                     foundPlate = 1;
                     break;
                  }
               }
            }
         } // Loop stop

         int newAirplaneFlight = GetFlightFromAirplanePlate(newPlateBuffer); // Checks if the new airplane has a flight scheduled

         if (newAirplaneFlight != -1)
         {
            // Case true, check if the ocuppied seats of the 2nd plane can fit on the current plane
            int newAirplaneBoughtTickets = GetBoughtTicketsForFlight(Flights[newAirplaneFlight].FlightNumber);

            if (newAirplaneBoughtTickets <= CurrentAirplane.Seats)
            {
               // Case true, swap the planes
               strcpy(CurrentFlight.AirplanePlate, newPlateBuffer);
               strcpy(Flights[newAirplaneFlight].AirplanePlate, CurrentAirplane.Plate);
               return 4;
            }
            else
            {
               // Case false, cancel the process
               return 3;
            }
         }
         else
         {
            // In case it doesn't have a flight scheduled, just swap the planes
            strcpy(CurrentFlight.AirplanePlate, newPlateBuffer);
            strcpy(Flights[newAirplaneFlight].AirplanePlate, CurrentAirplane.Plate);
            return 4;
         }
      }
      else
      {
         // If there are no other planes then cancels
         return 2;
      }
   }
   else
   {
      // If not full just return
      return 1;
   }
}

float FlightTime(char *FligthNumber) // To get the Time spent on the flight
{
   int Hour = 0, Day1, Hour1, Day2, Hour2;
   float Minute = 0, Minute1, Minute2, Time;

   for (int j = 0; j < FlightCount; j++) // Loop through all Flights to get the Flight with the Flight Number given
   {
      if (strcmp(FligthNumber, Flights[j].FlightNumber) == 0) // Find the Flight with the Flight Number given
      {
         Day1 = Flights[j].Departure.Day;       // Puts the Day of departure of the flight on the interger Day1
         Hour1 = Flights[j].Departure.Hour;     // Puts the Hour of departure of the flight on the interger Hour1
         Minute1 = Flights[j].Departure.Minute; // Puts the Minute of departure of the flight on the float Minute1
         Day2 = Flights[j].Arrival.Day;         // Puts the Day of arrival of the flight on the interger Day2
         Hour2 = Flights[j].Arrival.Hour;       // Puts the Hour of arrival of the flight on the interger Hour2
         Minute2 = Flights[j].Arrival.Minute;   // Puts the Minute of arrival of the flight on the float Minute1
         break;                                 // Breaks because it only happens once
      }
   }

   // Gets the Hours spent on the Flight
   if (Day1 == Day2) // If the day doesn't change
   {
      Hour = Hour2 - Hour1; // Subtracts the Hours, to get the Hours spent on the flight
   }
   else // If the day changes, by one <-- I don't know if I need to do more (I don't think flights are longer than 23 hours)
   {
      Hour = (Hour2 + 24) - Hour1; // Adds 24 to the Hour2 and then Subtracts the Hours, to get the hours  spent on the flight
   }

   if (Minute1 != Minute2) // Only changes Minute if the Minutes are different
   {
      Minute = (Minute2 - Minute1) / 60; // Subtracks the Minutes, and then changes the Minutes to a Fraction
   }

   // To get the time spent on the flight
   if (Minute < 0) // If Minute is less than 0
   {
      Time = Hour - Minute; // Than Subtracks Hour with Minute
   }
   else // If Minute is more or equal to 0
   {
      Time = Hour + Minute; // Than Adds Hour with Minute
   }

   return Time; // returns the Time spent on the flight
}

void Finance() // To know if the Flight gives profit or not
{
   int Check;
   float Distance, Time, FlightCrewPrice, Fuel, FuelPrice;

   Total = 0;

   for (int j = 0; j < TicketCount; j++) // To know the money that we will earn from tickets
   {
      if (strcmp(Flights[i].FlightNumber, Tickets[j].FlightNumber) == 0) // All the tickets that will be in the Flight
      {
         Total += Tickets[j].Price; // Total of the Euros that we will earn from tickets
      }
   }

   for (int j = 0; j < TicketCount; j++) // To know the distance of the flight
   {
      if (strcmp(Flights[i].FlightNumber, Tickets[j].FlightNumber) == 0) // Find a ticket with the FlightNumber, to find the distance
      {
         Distance = Tickets[j].Distance; // Distance of the Flight
         break;
      }
   }

   Fuel = Distance / 51;      // The Fuel that will be used in the Flight
   FuelPrice = Fuel * 2.0709; // The Price of the Fuel used in the Flight

   Time = FlightTime(Flights[i].FlightNumber); // Time spent in the Flight
   FlightCrewPrice = 400 * Time;               // Money that will be used to pay the FlightCrew of the Flight

   Expense = FuelPrice + FlightCrewPrice + 5000; // All the money spent in the Flight
   Profit = Total - Expense;                     // Profit made by the Flight

   if (Profit < 0)
   {
      Profit *= -1;
      printf("| Total Gained: %.2f Euros | Expense: %.2f Euros | Loss: %.2f Euros\n", Total, Expense, Profit);
   }
   else
   {
      printf("| Total Gained: %.2f Euros | Expense: %.2f Euros | Profit: %.2f Euros\n", Total, Expense, Profit);
   }

   return;
}

void GetsLink() // To get were you are Staying and your Desination
{
   GetsUppercase();

   for (int i = 0; i < AirportCount; i++) // Loop through all Airport to find if the Answer exists or not
   {
      if (strcmp(Buffer, Airports[i].IATA) == 0) // If it Exists, Valid
      {
         return;
      }
   }

   printf("\n\t//Invalid Option//\n\tPress any key to go back");
   getch();
   system("cls");
   GetsLink(); // Does it again
   return;
}

float WaitTime(char *FlightNumber, char *FlightNumber1) // To get the Time Spent Waiting
{

   int Hour = 0, Day1, Hour1, Day2, Hour2;
   float Minute = 0, Minute1, Minute2, Time;

   for (int i = 0; i < FlightCount; i++) // Loop to get the Flight with FlightNumber
   {
      if (strcmp(FlightNumber, Flights[i].FlightNumber) == 0) // Puts the Arrival time in Day1, Hour1, Minute1
      {
         Day1 = Flights[i].Arrival.Day;
         Hour1 = Flights[i].Arrival.Hour;
         Minute1 = Flights[i].Arrival.Minute;
         break;
      }
   }

   for (int i = 0; i < FlightCount; i++) // Loop to get the Flight with FlightNumber1
   {
      if (strcmp(FlightNumber1, Flights[i].FlightNumber) == 0) // Puts the Departure time in Day2, Hour2, Minute2
      {
         Day2 = Flights[i].Departure.Day;
         Hour2 = Flights[i].Departure.Hour;
         Minute2 = Flights[i].Departure.Minute;
         break;
      }
   }

   // Counts the Hours spent Waiting
   if (Day1 == Day2)
   {
      Hour = Hour2 - Hour1;
   }
   else
   {
      Hour = (Hour2 + 24) - Hour1;
   }

   if (Minute1 != Minute2)
   {
      Minute = (Minute2 - Minute1) / 60;
   }

   if (Minute < 0)
   {
      Time = Hour - Minute;
   }
   else
   {
      Time = Hour + Minute;
   }

   return Time; // Returns Waiting Time
}

float GetsTotalFlightTime(int Connections, char *Origin, char *Middle1, char *Middle2, char *Destination) // To get The Total Flying Time beetwen multiples Flights
{

   float FlightTime1, FlightTime2, FlightTime3, FlightTime4, TotalTime;

   switch (Connections) // Gets how many Flights there are
   {
   case 2:
      FlightTime1 = FlightTime(Origin);      // Gets the Time spent Flying in the First Flight
      FlightTime2 = FlightTime(Destination); // Gets the Time spent Flying in the Second Flight
      TotalTime = FlightTime1 + FlightTime2; // Gets the Total Time Flying for 2 Flights
      break;

   case 3:
      FlightTime1 = FlightTime(Origin);                    // Gets the Time spent Flying in the First Flight
      FlightTime2 = FlightTime(Middle1);                   // Gets the Time spent Flying in the Second Flight
      FlightTime3 = FlightTime(Destination);               // Gets the Time spent Flying in the Third Flight
      TotalTime = FlightTime1 + FlightTime2 + FlightTime3; // Gets the Total Time Flying for 3 Flights
      break;

   case 4:
      FlightTime1 = FlightTime(Origin);                                  // Gets the Time spent Flying in the First Flight
      FlightTime2 = FlightTime(Middle1);                                 // Gets the Time spent Flying in the Second Flight
      FlightTime3 = FlightTime(Middle2);                                 // Gets the Time spent Flying in the Third Flight
      FlightTime4 = FlightTime(Destination);                             // Gets the Time spent Flying in the Forth Flight
      TotalTime = FlightTime1 + FlightTime2 + FlightTime3 + FlightTime4; // Gets the Total Time Flying for 4 Flights
      break;
   default:
      break;
   }

   return TotalTime; // Returns Flying Time
}

float GetsTotalWaitTime(int Connections, char *Origin, char *Middle1, char *Middle2, char *Destination) // To get The Total Waiting Time beetwen Multiples Flights
{

   float WaitTime1, WaitTime2, WaitTime3, TotalTime;

   switch (Connections) // Gets how many Flights there are
   {
   case 2:
      WaitTime1 = WaitTime(Origin, Destination); // Gets the Time spent Waiting Beetwen the First and Second Flight
      TotalTime = WaitTime1;                     // Gets the Total Waiting Flying for 2 Flights
      break;

   case 3:
      WaitTime1 = WaitTime(Origin, Middle1);      // Gets the Time spent Waiting Beetwen the First and Second Flight
      WaitTime2 = WaitTime(Middle1, Destination); // Gets the Time spent Waiting Beetwen the Second and Third Flight
      TotalTime = WaitTime1 + WaitTime2;          // Gets the Total Waiting Flying for 3 Flights
      break;

   case 4:
      WaitTime1 = WaitTime(Origin, Middle1);         // Gets the Time spent Waiting Beetwen the First and Second Flight
      WaitTime2 = WaitTime(Middle1, Middle2);        // Gets the Time spent Waiting Beetwen the Second and Third Flight
      WaitTime3 = WaitTime(Middle2, Destination);    // Gets the Time spent Waiting Beetwen the Third and Forth Flight
      TotalTime = WaitTime1 + WaitTime2 + WaitTime3; // Gets the Total Waiting Flying for 4 Flights
      break;
   default:
      break;
   }

   return TotalTime; // Return Waiting Time
}

int FreeSeats(char *FlightNumber) // Gets the number of free seats
{
   int AllSeats, SeatsOccupied, Check;

   SeatsOccupied = GetBoughtTicketsForFlight(FlightNumber); // Gets All Occupied Seats

   for (int i = 0; i < FlightCount; i++) // Loop to fing Flight with Flight Number
   {
      if (strcmp(FlightNumber, Flights[i].FlightNumber) == 0)
      {
         for (int j = 0; j < AirplaneCount; j++) // Loop to find the Airplane with Airplane Plate
         {
            if (strcmp(Flights[i].AirplanePlate, Airplanes[j].Plate) == 0)
            {
               AllSeats = Airplanes[j].Seats; // To put all the seats that the Airplane has in AllSeats
               break;
            }
         }
      }
   }

   AllSeats = AllSeats - SeatsOccupied; // Operacion to get free seats

   return AllSeats; // Returns all free seats
}

float TicketsPrice(int Passengers, int Connections, char *Origin, char *Middle1, char *Middle2, char *Destination) // To see how much all the tickets cost
{
   float Total = 0;

   switch (Connections) // See how many flights there are
   {
   case 2:
      for (int i = 0; i < FlightCount; i++) // Loop to find the Frist Flight
      {
         if (strcmp(Origin, Tickets[i].FlightNumber) == 0)
         {
            Total += Passengers * Tickets[i].Price; // Adds the price of all the Tickets form the First Flight to the Total
            break;
         }
      }
      for (int i = 0; i < FlightCount; i++) // Loop to find the Second Flight
      {
         if (strcmp(Destination, Tickets[i].FlightNumber) == 0)
         {
            Total += Passengers * Tickets[i].Price; // Adds the price of all the Tickets form the Second Flight to the Total
            break;
         }
      }
      break;
   case 3:
      for (int i = 0; i < FlightCount; i++) // Loop to find the Frist Flight
      {
         if (strcmp(Origin, Tickets[i].FlightNumber) == 0)
         {
            Total += Passengers * Tickets[i].Price; // Adds the price of all the Tickets form the First Flight to the Total
            break;
         }
      }
      for (int i = 0; i < FlightCount; i++) // Loop to find the Second Flight
      {
         if (strcmp(Middle1, Tickets[i].FlightNumber) == 0)
         {
            Total += Passengers * Tickets[i].Price; // Adds the price of all the Tickets form the Second Flight to the Total
            break;
         }
      }
      for (int i = 0; i < FlightCount; i++) // Loop to find the Third Flight
      {
         if (strcmp(Destination, Tickets[i].FlightNumber) == 0)
         {
            Total += Passengers * Tickets[i].Price; // Adds the price of all the Tickets form the Third Flight to the Total
            break;
         }
      }
      break;
   case 4:
      for (int i = 0; i < FlightCount; i++) // Loop to find the Frist Flight
      {
         if (strcmp(Origin, Tickets[i].FlightNumber) == 0)
         {
            Total += Passengers * Tickets[i].Price; // Adds the price of all the Tickets form the First Flight to the Total
            break;
         }
      }
      for (int i = 0; i < FlightCount; i++) // Loop to find the Second Flight
      {
         if (strcmp(Middle1, Tickets[i].FlightNumber) == 0)
         {
            Total += Passengers * Tickets[i].Price; // Adds the price of all the Tickets form the Second Flight to the Total
            break;
         }
      }
      for (int i = 0; i < FlightCount; i++) // Loop to find the Third Flight
      {
         if (strcmp(Middle2, Tickets[i].FlightNumber) == 0)
         {
            Total += Passengers * Tickets[i].Price; // Adds the price of all the Tickets form the Third Flight to the Total
            break;
         }
      }
      for (int i = 0; i < FlightCount; i++) // Loop to find the Forth Flight
      {
         if (strcmp(Destination, Tickets[i].FlightNumber) == 0)
         {
            Total += Passengers * Tickets[i].Price; // Adds the price of all the Tickets form the Forth Flight to the Total
            break;
         }
      }
      break;
   default:
      break;
   }

   return Total; // Returns all the Tickets Price
}

void Link()
{
   int Year, Month, Day, Passengers, FreeSeats1, FreeSeats2, FreeSeats3, FreeSeats4;
   float Time, WaitTime, FlyingTime, TotalTicketsPrice;
   char Origin[99], Destination[99];

   printf("\n\tInsert the Date (Day,Month,Year): \n\t> "); // Aks for Date
   gets(Buffer);
   sscanf(Buffer, " %d,%d,%d\n", &Day, &Month, &Year);
   if (Day < 1 || Day > 31 || Month < 1 || Month > 12 || Year < 2022) // If Invalid
   {
      printf("\n\t//Invalid Option//");
      printf("\n\tPress any key to go back");
      getch();
      system("cls");
      Link(); // Does it Again
      return;
   }
   system("cls");

   printf("\n\tInsert Origin Airport: \n\t> ");
   GetsLink(); // Gets were you are Staying
   strcpy(Origin, Buffer);
   system("cls");

   printf("\n\tInsert Destination Airport: \n\t> ");
   GetsLink(); // Gets your Destiantion
   strcpy(Destination, Buffer);
   system("cls");

   printf("\n\tInsert the Number of Passengers: "); // Gets Passengers
   Passengers = GetInt(1, 999999);
   system("cls");

   Options = 0;
   // Checks if there is already a flight beetwen the 2 places
   for (i = 0; i < FlightCount; i++) // Loops through all Flights
   {
      if (strcmp(Origin, Flights[i].OriginIATA) == 0 && strcmp(Destination, Flights[i].DestinyIATA) == 0 && Year == Flights[i].Departure.Year && Month == Flights[i].Departure.Month && Day == Flights[i].Departure.Day)
      {
         printf("\n\tThere is already a Flight occurring between %s and %s", Origin, Destination);
         printf("\n\tPress any key to go back");
         getch();
         system("cls");
         strcpy(FlightBuffer[0][0], Flights[i].FlightNumber);
         Connections = 1;
         return; // Does not Continue if there is a Flight
      }
   }

   printf("\n\tInsert Number of Connections (2, 3 or 4): \n\t "); // Asks for the number of Connections that you want
   Connections = GetInt(2, 4);                                    // Gets Answer
   system("cls");

   switch (Connections)
   {
   case 2:
      for (i = 0; i < FlightCount; i++) // Loops through all Flights to get one that Starts were you are Staying
      {
         if (strcmp(Origin, Flights[i].OriginIATA) == 0)
         {
            for (j = 0; j < FlightCount; j++) // Loops through all Flights to get one that Finishes in your Destination
            {
               if (strcmp(Flights[i].DestinyIATA, Flights[j].OriginIATA) == 0 && strcmp(Flights[j].DestinyIATA, Destination) == 0)
               {
                  FreeSeats1 = FreeSeats(Flights[i].FlightNumber);                                                                             // Sees how many Free Seats there are
                  FreeSeats1 = FreeSeats(Flights[j].FlightNumber);                                                                             // Sees how many Free Seats there are
                  TotalTicketsPrice = TicketsPrice(Passengers, Connections, Flights[i].FlightNumber, "NULL", "NULL", Flights[j].FlightNumber); // Gets the Pricethat you need to pay
                  FlyingTime = GetsTotalFlightTime(Connections, Flights[i].FlightNumber, "NULL", "NULL", Flights[j].FlightNumber);             // Gets Total Flying Time
                  WaitTime = GetsTotalWaitTime(Connections, Flights[i].FlightNumber, "NULL", "NULL", Flights[j].FlightNumber);                 // Gets Total Waiting Time
                  Time = FlyingTime + WaitTime;
                  if (Time < 72 && Time > 0) // Prints
                  {
                     Options++;
                     printf("\n\tOption: %d\n\n", Options);
                     printf("\n\tFrist Flight:\n");
                     printf("\n Flight Number: %s | Departure Date: %02d/%02d/%04d %02d:%02d | Arrival Date: %02d/%02d/%04d %02d:%02d | Origin IATA: %s | Destiny IATA: %s | Airplane Plate: %s | Free Seats: %d ", Flights[i].FlightNumber, Flights[i].Departure.Day, Flights[i].Departure.Month, Flights[i].Departure.Year, Flights[i].Departure.Hour, Flights[i].Departure.Minute, Flights[i].Arrival.Day, Flights[i].Arrival.Month, Flights[i].Arrival.Year, Flights[i].Arrival.Hour, Flights[i].Arrival.Minute, Flights[i].OriginIATA, Flights[i].DestinyIATA, Flights[i].AirplanePlate, FreeSeats1);
                     printf("\n\tSecondFlight:\n");
                     printf("\n Flight Number: %s | Departure Date: %02d/%02d/%04d %02d:%02d | Arrival Date: %02d/%02d/%04d %02d:%02d | Origin IATA: %s | Destiny IATA: %s | Airplane Plate: %s | Free Seats: %d ", Flights[j].FlightNumber, Flights[j].Departure.Day, Flights[j].Departure.Month, Flights[j].Departure.Year, Flights[j].Departure.Hour, Flights[j].Departure.Minute, Flights[j].Arrival.Day, Flights[j].Arrival.Month, Flights[j].Arrival.Year, Flights[j].Arrival.Hour, Flights[j].Arrival.Minute, Flights[j].OriginIATA, Flights[j].DestinyIATA, Flights[j].AirplanePlate, FreeSeats2);
                     printf("\n\n\tTotal Time: %.2f | Time Waiting: %.2f | Time Flying: %.2f | Price: %.2f", Time, WaitTime, FlyingTime, TotalTicketsPrice);
                     strcpy(FlightBuffer[0][Options], Flights[i].FlightNumber);
                     strcpy(FlightBuffer[1][Options], Flights[j].FlightNumber);
                     strcpy(FlightBuffer[2][Options], Flights[k].FlightNumber);
                     strcpy(FlightBuffer[3][Options], Flights[l].FlightNumber);
                  }
               }
            }
         }
      }

      break;
   case 3:
      for (i = 0; i < FlightCount; i++) // Loops through all Flights to get one that Starts were you are Staying
      {
         if (strcmp(Origin, Flights[i].OriginIATA) == 0)
         {
            for (j = 0; j < FlightCount; j++) // Loops through all Flights to get one that will work for the Middle one
            {
               if (strcmp(Flights[i].DestinyIATA, Flights[j].OriginIATA) == 0)
               {
                  for (k = 0; k < FlightCount; k++) // Loops through all Flights to get one that starts in the Middle one and Finishes in your Destination
                  {
                     if (strcmp(Flights[j].DestinyIATA, Flights[k].OriginIATA) == 0 && strcmp(Flights[k].DestinyIATA, Destination) == 0)
                     {
                        FreeSeats1 = FreeSeats(Flights[i].FlightNumber); // Sees how many Free Seats there are
                        FreeSeats2 = FreeSeats(Flights[j].FlightNumber); // Sees how many Free Seats there are
                        FreeSeats3 = FreeSeats(Flights[k].FlightNumber); // Sees how many Free Seats there are

                        TotalTicketsPrice = TicketsPrice(Passengers, Connections, Flights[i].FlightNumber, Flights[j].FlightNumber, "NULL", Flights[k].FlightNumber); // Gets the Pricethat you need to pay
                        FlyingTime = GetsTotalFlightTime(Connections, Flights[i].FlightNumber, Flights[j].FlightNumber, "NULL", Flights[k].FlightNumber);             // Gets Total Flying Time
                        WaitTime = GetsTotalWaitTime(Connections, Flights[i].FlightNumber, Flights[j].FlightNumber, "NULL", Flights[k].FlightNumber);                 // Gets Total Waiting Time
                        Time = FlyingTime + WaitTime;

                        if (Time < 72 && Time > 0) // Prints
                        {
                           Options++;
                           printf("\n\tOption: %d\n\n", Options);
                           printf("\n\tFrist Flight:\n");
                           printf("\n Flight Number: %s | Departure Date: %02d/%02d/%04d %02d:%02d | Arrival Date: %02d/%02d/%04d %02d:%02d | Origin IATA: %s | Destiny IATA: %s | Airplane Plate: %s | Free Seats: %d ", Flights[i].FlightNumber, Flights[i].Departure.Day, Flights[i].Departure.Month, Flights[i].Departure.Year, Flights[i].Departure.Hour, Flights[i].Departure.Minute, Flights[i].Arrival.Day, Flights[i].Arrival.Month, Flights[i].Arrival.Year, Flights[i].Arrival.Hour, Flights[i].Arrival.Minute, Flights[i].OriginIATA, Flights[i].DestinyIATA, Flights[i].AirplanePlate, FreeSeats1);
                           printf("\n\tSecondFlight:\n");
                           printf("\n Flight Number: %s | Departure Date: %02d/%02d/%04d %02d:%02d | Arrival Date: %02d/%02d/%04d %02d:%02d | Origin IATA: %s | Destiny IATA: %s | Airplane Plate: %s | Free Seats: %d ", Flights[j].FlightNumber, Flights[j].Departure.Day, Flights[j].Departure.Month, Flights[j].Departure.Year, Flights[j].Departure.Hour, Flights[j].Departure.Minute, Flights[j].Arrival.Day, Flights[j].Arrival.Month, Flights[j].Arrival.Year, Flights[j].Arrival.Hour, Flights[j].Arrival.Minute, Flights[j].OriginIATA, Flights[j].DestinyIATA, Flights[j].AirplanePlate, FreeSeats2);
                           printf("\n\tThird Flight:\n");
                           printf("\n Flight Number: %s | Departure Date: %02d/%02d/%04d %02d:%02d | Arrival Date: %02d/%02d/%04d %02d:%02d | Origin IATA: %s | Destiny IATA: %s | Airplane Plate: %s | Free Seats: %d ", Flights[k].FlightNumber, Flights[k].Departure.Day, Flights[k].Departure.Month, Flights[k].Departure.Year, Flights[k].Departure.Hour, Flights[k].Departure.Minute, Flights[k].Arrival.Day, Flights[k].Arrival.Month, Flights[k].Arrival.Year, Flights[k].Arrival.Hour, Flights[k].Arrival.Minute, Flights[k].OriginIATA, Flights[k].DestinyIATA, Flights[k].AirplanePlate, FreeSeats3);
                           printf("\n Total Time: %.2f | Time Waiting: %.2f | Time Flying: %.2f | Price: %.2f", Time, WaitTime, FlyingTime, TotalTicketsPrice);
                           strcpy(FlightBuffer[0][Options], Flights[i].FlightNumber);
                           strcpy(FlightBuffer[1][Options], Flights[j].FlightNumber);
                           strcpy(FlightBuffer[2][Options], Flights[k].FlightNumber);
                           strcpy(FlightBuffer[3][Options], Flights[l].FlightNumber);
                        }
                     }
                  }
               }
            }
         }
      }
      break;
   case 4:
      for (i = 0; i < FlightCount; i++) // Loops through all Flights to get one that Starts were you are Staying
      {
         if (strcmp(Origin, Flights[i].OriginIATA) == 0)
         {
            for (j = 0; j < FlightCount; j++) // Loops through all Flights to get one that will work for the Middle One
            {
               if (strcmp(Flights[i].DestinyIATA, Flights[j].OriginIATA) == 0)
               {
                  for (k = 0; k < FlightCount; k++) // Loops through all Flights to get one that will work for the Middle Two
                  {
                     if (strcmp(Flights[j].DestinyIATA, Flights[k].OriginIATA) == 0)
                     {
                        for (l = 0; l < FlightCount; l++) // Loops through all Flights to get one that starts in the Middle one and Finishes in your Destination
                        {
                           if (strcmp(Flights[k].DestinyIATA, Flights[l].OriginIATA) == 0 && strcmp(Flights[l].DestinyIATA, Destination) == 0)
                           {
                              FreeSeats1 = FreeSeats(Flights[i].FlightNumber); // Sees how many Free Seats there are
                              FreeSeats2 = FreeSeats(Flights[j].FlightNumber); // Sees how many Free Seats there are
                              FreeSeats3 = FreeSeats(Flights[k].FlightNumber); // Sees how many Free Seats there are
                              FreeSeats4 = FreeSeats(Flights[l].FlightNumber); // Sees how many Free Seats there are

                              TotalTicketsPrice = TicketsPrice(Passengers, Connections, Flights[i].FlightNumber, Flights[j].FlightNumber, Flights[k].FlightNumber, Flights[l].FlightNumber); // Gets the Pricethat you need to pay
                              FlyingTime = GetsTotalFlightTime(Connections, Flights[i].FlightNumber, Flights[j].FlightNumber, Flights[k].FlightNumber, Flights[l].FlightNumber);             // Gets Total Flying Time
                              WaitTime = GetsTotalWaitTime(Connections, Flights[i].FlightNumber, Flights[j].FlightNumber, Flights[k].FlightNumber, Flights[l].FlightNumber);                 // Gets Total Waiting Time
                              Time = FlyingTime + WaitTime;
                              if (Time < 72 && Time > 0) // Prints
                              {
                                 Options++;
                                 printf("\n\tOption: %d\n\n", Options);
                                 printf("\n\tFrist Flight:\n");
                                 printf("\n Flight Number: %s | Departure Date: %02d/%02d/%04d %02d:%02d | Arrival Date: %02d/%02d/%04d %02d:%02d | Origin IATA: %s | Destiny IATA: %s | Airplane Plate: %s | Free Seats: %d ", Flights[i].FlightNumber, Flights[i].Departure.Day, Flights[i].Departure.Month, Flights[i].Departure.Year, Flights[i].Departure.Hour, Flights[i].Departure.Minute, Flights[i].Arrival.Day, Flights[i].Arrival.Month, Flights[i].Arrival.Year, Flights[i].Arrival.Hour, Flights[i].Arrival.Minute, Flights[i].OriginIATA, Flights[i].DestinyIATA, Flights[i].AirplanePlate, FreeSeats1);
                                 printf("\n\tSecondFlight:\n");
                                 printf("\n Flight Number: %s | Departure Date: %02d/%02d/%04d %02d:%02d | Arrival Date: %02d/%02d/%04d %02d:%02d | Origin IATA: %s | Destiny IATA: %s | Airplane Plate: %s | Free Seats: %d ", Flights[j].FlightNumber, Flights[j].Departure.Day, Flights[j].Departure.Month, Flights[j].Departure.Year, Flights[j].Departure.Hour, Flights[j].Departure.Minute, Flights[j].Arrival.Day, Flights[j].Arrival.Month, Flights[j].Arrival.Year, Flights[j].Arrival.Hour, Flights[j].Arrival.Minute, Flights[j].OriginIATA, Flights[j].DestinyIATA, Flights[j].AirplanePlate, FreeSeats2);
                                 printf("\n\tThird Flight:\n");
                                 printf("\n Flight Number: %s | Departure Date: %02d/%02d/%04d %02d:%02d | Arrival Date: %02d/%02d/%04d %02d:%02d | Origin IATA: %s | Destiny IATA: %s | Airplane Plate: %s | Free Seats: %d ", Flights[k].FlightNumber, Flights[k].Departure.Day, Flights[k].Departure.Month, Flights[k].Departure.Year, Flights[k].Departure.Hour, Flights[k].Departure.Minute, Flights[k].Arrival.Day, Flights[k].Arrival.Month, Flights[k].Arrival.Year, Flights[k].Arrival.Hour, Flights[k].Arrival.Minute, Flights[k].OriginIATA, Flights[k].DestinyIATA, Flights[k].AirplanePlate, FreeSeats3);
                                 printf("\n\tFourth Flight:\n");
                                 printf("\n Flight Number: %s | Departure Date: %02d/%02d/%04d %02d:%02d | Arrival Date: %02d/%02d/%04d %02d:%02d | Origin IATA: %s | Destiny IATA: %s | Airplane Plate: %s | Free Seats: %d ", Flights[l].FlightNumber, Flights[l].Departure.Day, Flights[l].Departure.Month, Flights[l].Departure.Year, Flights[l].Departure.Hour, Flights[l].Departure.Minute, Flights[l].Arrival.Day, Flights[l].Arrival.Month, Flights[l].Arrival.Year, Flights[l].Arrival.Hour, Flights[l].Arrival.Minute, Flights[l].OriginIATA, Flights[l].DestinyIATA, Flights[l].AirplanePlate, FreeSeats4);
                                 printf("\n Total Time: %.2f | Time Waiting: %.2f | Time Flying: %.2f | Price: %.2f", Time, WaitTime, FlyingTime, TotalTicketsPrice);
                                 strcpy(FlightBuffer[0][Options], Flights[i].FlightNumber);
                                 strcpy(FlightBuffer[1][Options], Flights[j].FlightNumber);
                                 strcpy(FlightBuffer[2][Options], Flights[k].FlightNumber);
                                 strcpy(FlightBuffer[3][Options], Flights[l].FlightNumber);
                              }
                           }
                        }
                     }
                  }
               }
            }
         }
      }
      break;
   }

   if (Options == 0)
   {
      printf("There are no Flights");
      return;
   }
   else
   {
      printf("\n\n\tChose an option: ");
      Options = GetInt(0, Options);
   }
}
