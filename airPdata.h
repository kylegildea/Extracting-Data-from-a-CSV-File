#ifndef AIRPDATA_H
#define AIRPDATA_H

typedef struct airPdata
{
  char *siteNumber; //FAA Site Number
  char *LocID; //Airport’s ‘‘Short Name’’, ie MCO
  char *fieldName; //Airport Name
  char *city; //Associated City
  char *state; //State
  char *latitude; //Latitude
  char *longitude; //Longitude
  char *controlTower;//Control Tower (Y/N)
} airPdata;

#endif