//------------------------------------------------------------------
// University of Central Florida
// COP3502C - Fall 2016
// Program Author: Kyle Gildea
//------------------------------------------------------------------

#include <stdio.h> 
#include <string.h> 
#include <unistd.h> 
#include <stdlib.h>
#include <string.h>
#include "airPdata.h"
#define BUFFERSIZE 500

//Function declarations
void errorPrint(char *error);
void print(airPdata *airP);
void freeLineBuffer(char *line);
void freeAirport(airPdata *airP);
void readFile(char *fileName);
void storeSiteNumber(airPdata *airP, char *input);
void storeLocID(airPdata *airP, char *input);
void storeFieldName(airPdata *airP, char *input);
void storeCity(airPdata *airP, char *input);
void storeState(airPdata *airP, char *input);
void storeLatitude(airPdata *airP, char *input);
void storeLongitude(airPdata *airP, char *input);
void storeControlTower(airPdata *airP, char *input);


//Main Function
int main(int argc, char **argv)
{
  readFile(argv[1]); 
  return 0;
}

//Prints error string
void errorPrint(char *error) 
{ 
  fprintf(stderr, "%s", error);
}


/*Reads in file with name given by command line
If the file cannot be opened, prints an error
Otherwise opens file, prints column names and a divider
Then reads file line by line, using fgets
Once a line has been read, strtok() is used to
tokenize the first fields from the string, then
goes into a while loop, tokenizing the rest of the line.
The first 7 fields are always in the same location, and so a counter.
fieldRead is used to determine if the token acquired is one we're
looking for. If it is, switch statement is used to store the value
in a struct. The final field controlTower is not always in the same place but is
always the 13th field or later. so once the first 7 values have been found, 
the counter continues to go up until 13, but any text parsed is discarded.
Upon ariving at the 13th field, the counter stops and text is processed until
a "Y" or "N" is found. Once the struct is filled out, the print function
is called to print the line and the process repeats until EOF.
*/
void readFile(char *fileName)
{
  FILE *inputFile = fopen(fileName, "r");
  airPdata *airport;
  airPdata *header;
  char *comma = ",";
  char *line;
  char *token;
  char *error;
  int fieldRead;
  
  
  
  if (inputFile == NULL)
  {
    error = malloc(BUFFERSIZE * sizeof(char));
    strcpy(error, "ERROR: could not open file ");
    strcat(error, fileName);
    strcat(error, "\n\n");
    errorPrint(error);
    free(error);
  }
  else
  {
    header = malloc(BUFFERSIZE * sizeof(char));
    
    if (header == NULL) 
    {   
      errorPrint("Malloc Failed!\n");   
    }
    
    else
    {
      storeSiteNumber(header,"\nFAA Site #");
      storeLocID(header, " Short Name"); 
      storeFieldName(header," Airport Name");
      storeCity(header," City");
      storeState(header," ST");
      storeLatitude(header, " Latitude");
      storeLongitude(header, " Longitude");
      storeControlTower(header, " Tower");
      
      print(header);
      
      storeSiteNumber(header,"==========");
      storeLocID(header, "=========="); 
      storeFieldName(header,"============");
      storeCity(header,"====");
      storeState(header,"==");
      storeLatitude(header, "========");
      storeLongitude(header, "=========");
      storeControlTower(header, "=====");
      
      print(header);
      freeAirport(header);
      
      
      airport = malloc(sizeof(airPdata));
      line = malloc(BUFFERSIZE * sizeof(char));
      
      while(fgets(line, BUFFERSIZE, inputFile) != NULL)
      {
        token = strtok(line,comma); 
        fieldRead = 1;
          
        while(token != NULL)  
        {
          switch(fieldRead)
          {
            case 1:
              storeSiteNumber(airport, token);
              fieldRead++;                                    
              break;
            case 2:
              storeLocID(airport, token);
              fieldRead++;
              break;            
              
            case 3:
              storeFieldName(airport, token);
              fieldRead++;      
              break;      
        
            case 4:
              storeCity(airport, token);
              fieldRead++;   
              break;         
          
            case 5:
              storeState(airport, token);
              fieldRead++;    
              break;        
        
            case 9:
              storeLatitude(airport, token);
              fieldRead++;
              break;          
        
            case 10:
              storeLongitude(airport, token);
              fieldRead++;
              break;            
            
            case 13:
              if(strcmp(token, "Y") == 0 || strcmp(token, "N") == 0)
                storeControlTower(airport, token);
              break;
        
            default:
              if(fieldRead > 5 && fieldRead < 13)
              {
                fieldRead++;
                break;
              }
              else
                 break;      
        }
        token = strtok(NULL, comma); 
        }
        
        print(airport);
      }
    }
    
    freeAirport(airport);
    free(line);
    fclose(inputFile);
  }
}

/*The next 8 functions take a pointer to struct, 
and an input string, allocate memory for the member of the 
struct and copies the input string into
the struct. There is a function for each member
of the struct
*/
void storeSiteNumber(airPdata *airP, char *input)
{
  
  airP->siteNumber = malloc(BUFFERSIZE * sizeof(char));
  if (airP->siteNumber == NULL) 
  {   
    errorPrint("Site Number Malloc Failed!\n");
  }
  else
    strcpy(airP->siteNumber, input);
}

void storeLocID(airPdata *airP, char *input)
{
  airP->LocID = malloc(BUFFERSIZE * sizeof(char));
  
  if (airP->LocID == NULL) 
  {   
      errorPrint("LocID Malloc Failed!\n");   
  }
  else
    strcpy(airP->LocID, input);
}

void storeFieldName(airPdata *airP, char *input)
{
  
  airP->fieldName = malloc(BUFFERSIZE * sizeof(char));
  
  if (airP->fieldName == NULL) 
  {   
      errorPrint("fieldName Malloc Failed!\n");   
  }
  else
    strcpy(airP->fieldName, input);
}

void storeCity(airPdata *airP, char *input)
{
  airP->city = malloc(BUFFERSIZE * sizeof(char));
  
  if (airP->city == NULL) 
  {   
    errorPrint("storeState Malloc Failed!\n");
  }
  else
    strcpy(airP->city, input);
}

void storeState(airPdata *airP, char *input)
{
  
  airP->state = malloc(BUFFERSIZE * sizeof(char));
  
  if (airP->state == NULL) 
  {   
    errorPrint("storeState Malloc Failed!\n");   

  }
  else
    strcpy(airP->state, input);
}

void storeLatitude(airPdata *airP, char *input)
{
  
  airP->latitude = malloc(BUFFERSIZE * sizeof(char));
  
  if (airP->latitude == NULL) 
  {   
    errorPrint("latitude Malloc Failed!\n");   
  }
  else
    strcpy(airP->latitude, input);
}

void storeLongitude(airPdata *airP, char *input)
{
  airP->longitude = malloc(BUFFERSIZE * sizeof(char));
  
  if (airP->longitude == NULL) 
  {   
    errorPrint("longitude Malloc Failed!\n");
  }
  else
    strcpy(airP->longitude, input);
}

void storeControlTower(airPdata *airP, char *input)
{
  airP->controlTower = malloc(BUFFERSIZE * sizeof(char));
  
  if (airP->controlTower == NULL) 
  {   
    errorPrint("controlTower Malloc Failed!\n");
  }
  else
    strcpy(airP->controlTower, input);
}

//Prints the struct
void print (airPdata *airP)
{
  printf("%-12s",airP->siteNumber); 
  printf("%-12s",airP->LocID);
  printf("%-45s",airP->fieldName);
  printf("%-34s",airP->city);
  printf("%-4s",airP->state);
  printf("%-20s",airP->latitude);
  printf("%-20s",airP->longitude);
  printf("%-2s\n",airP->controlTower);
}

/*Frees the stuff inside the struct before
going on to free the struct itself*/
void freeAirport(airPdata *airP)
{
  free(airP->siteNumber); 
  free(airP->LocID);
  free(airP->fieldName);
  free(airP->city);
  free(airP->state);
  free(airP->latitude);
  free(airP->longitude);
  free(airP->controlTower);
  free(airP);
}