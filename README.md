# Extracting-Data-from-a-CSV-File
COP3502 HW1


AbstractThis assignment is based on a class of problem solved in enterprise comput-ing; extraction, transformation, and loading. This is often referred to as ETL. Theinputs will be data extracted from a leading aviation industry data and consultingfirm, GCR. (See GCR.com for additional data.)  The data is in a well known for-mat where each data element is separated from the previous and following dataelements by using a comma.  It should be noted that this method of data manipu-lation is extremely common.  The explicit order of the data fields and the desiredoutputs are defined in the "Specifications".1    ObjectivesThe objectives of this assignment are to demonstrate proficiency in file I/O, data struc-tures, and data transformation using C language resources.1.1    InputsThere are two basic inputs, the input file name, passed via the command line, and theinput file data defined below.1.1.1    Command Line argumentsThe input file name will be input as follows:•hw1etl filename.ext•In the event that the input file is not available or there is an error finding thefile, an appropriate error message shall be displayed. Use the example below forguidance.•hw1etl ERROR: File “bogusFilename” not found.1
1.1.2    Input File fieldsThe CSV input file contains the following fields.  Please note these fields may vary insize, content, and validity of the data.  Also note that some of the data formats are amelangeof types.  Specifically, note that both latitude and longitude contain numbers,punctuation,  and  text.   Likewise,  the  FAA  Site  number  contains  digits,  letters,  andpunctuation. (This assignment will treat all input data as character data.)Table 1: Airports Data FieldsField TitleDescriptionSizeFAA Site NumberContains  leading  digits  fol-lowed  by  a  decimal  pointand short textLeading   digits   fol-lowed  by  a  decimalpoint and zero to twodigits and a letterLoc IDThe airport’s short name, i.e.MCO for Orlando4 charactersAirport NameThe airport’s full name,  i.e.Orlando International~30 charactersAssociated CityThe nearest city~25 charactersStateState2 charactersRegionFAA Region3 charactersADOAirline Dispatch Office3 charactersUsePublic or Private2 charactersLatitudeDD-HH-MM.MASDirectionDegrees, hours, min-utes.milliarcsecondsfollowed   by   eitherN,S,E  or  W.  Treatedas a string, for nowLongitudeSee Latitude above.dittoAirport OwnershipPublic or Private2 charactersPart 139FAA RegulationNo dataNPIAS Service LevelNationalPlanIntegratedAirport Systems Descriptor~10 charactersNPIAS Hub TypeIntentionally left blankn/aAirport Control TowerY/None characterFuelFuel types availableup to 6 charactersOther ServicesCollections of tag indicatingINSTRuction, etc.12 charactersBased Aircraft TotalNumber of aircraft (may beblank)Integer numberTotal OperationsTakeoffs/Landings/etc  (maybe blank)Integer number2
2    OutputsThe outputs of the program will be populatedStruct airPdatadata.  This datawill be formatted so as to provide output define in the following sections.2.1    Data StructureThe structurestruct airPdatais described below.   Please note the correlationwith the data file’sField Namesrefer to Table 1 on page 2 for more information.typedef struct airPdata{char*siteNumber; //FAA Site Numberchar*LocID;   //Airport’s ‘‘Short Name’’, ie MCOchar*fieldName; //Airport Namechar*city;    //Associated Citychar*state;   //Statechar*latitude; //Latitudechar*longitude; //Longitudechar controlTower;//Control Tower (Y/N)} airPdata;2.2    File outputThe file output for this assignment isstdout,  aka the console.   Make sure there is aheadline that names each column. For example:FAA Site#    Short Name Airport Name                    City    ST      Latitude        Longitude      Tower==========   ========== ================                ======= ==      ==============  =============== =03406.20*H      2FD7    AIR ORLANDO                     ORLANDO FL      28-26-08.0210N  081-28-23.2590W N03406.31*H      3FD5    ARNOLD PALMER HOSPITAL          ORLANDO FL      28-31-21.0090N  081-22-49.2520W N03406.36*H      2FL5    BROOKSVILLE INTL AIRWAYS- INC   ORLANDO FL      28-25-26.0000N  081-27-35.0000W N03406.24*H      FD99    DR P PHILLIPS HOSPITAL          ORLANDO FL      28-25-43.0220N  081-28-38.2590W N03408.*A        ORL     EXECUTIVE                       ORLANDO FL      28-32-43.7000N  081-19-58.5000W Y03406.11*H      37FA    FLORIDA HOSPITAL                ORLANDO FL      28-34-32.0020N  081-22-06.2490W N03406.22*H      FD36    FLORIDA HOSPITAL EAST ORLANDO   ORLANDO FL      28-32-26.7000N  081-16-51.0000W N03406.40*H      FL76    HELI-PARTNERS I-DRIVE           ORLANDO FL      27-23-04.0000N  081-29-07.0000W N03406.39*H      97FD    HELICOPTERS INTL                ORLANDO FL      28-27-51.8300N  081-27-35.8800W N03407.2*A       ISM     KISSIMMEE GATEWAY               ORLANDO FL      28-17-23.3000N  081-26-13.5000W Y03406.*C        91FL    LAKE CONWAY NORTH               ORLANDO FL      28-28-45.0140N  081-22-03.2510W N03406.33*C      89FL    LAKE HIAWASSEE                  ORLANDO FL      28-31-45.0100N  081-28-51.2600W N03407.15*A      54FD    LM-ETS                          ORLANDO FL      28-22-03.0000N  081-04-34.0000W N03407.09*H      82FD    LOCKHEED MARTIN                 ORLANDO FL      28-26-48.4900N  081-27-03.6900W N03406.18*H      32FL    MEYER                           ORLANDO FL      28-30-05.0120N  081-26-39.2560W N03408.4*H       27FA    ORANGE COUNTY SHERIFF’S OFFICE  ORLANDO FL      28-30-27.0110N  081-24-48.2540W N03407.*A        MCO     ORLANDO INTL                    ORLANDO FL      28-25-45.8000N  081-18-32.4000W Y03406.21*H      FD28    ORLANDO RGNL MEDICAL CENTER     ORLANDO FL      28-31-31.0090N  081-22-37.2510W N03407.1*A       SFB     ORLANDO SANFORD INTL            ORLANDO FL      28-46-37.1000N  081-14-05.7000W Y03406.29*H      7FA5    PREMIUM                         ORLANDO FL      28-23-21.0000N  081-29-19.0000W N03406.113*H     26FA    PRINCETON HOSPITAL              ORLANDO FL      28-34-06.0040N  081-26-02.2550W N03406.14*A      01FA    RYBOLT RANCH                    ORLANDO FL      28-35-21.9970N  081-08-39.2290W N03406.38*C      12FL    TIMBERLACHEN                    ORLANDO FL      28-35-34.0000N  081-24-14.0000W N03406.34*H      0FL7    WKMG-TV                         ORLANDO FL      28-35-38.7000N  081-25-11.6000W N03406.3*H       13FD    YELVINGTON                      ORLANDO FL      28-31-07.0090N  081-22-59.2520W N3
3    ProcessingThe primary goal is to provide programmatic access to the data from the input CSVfile.  This must be accomplished using standard C file IO techniques.  Also note that itis vital to utilize thestuct airPdatafor all data retrieval/extraction. Likewise, use of thestuct airPdatais required for the file output.3.1    Reading the inputThere are several approaches to read the input. Perhaps the most important considera-tion is reading the line in for each airport. Please note that there is one line per airport.Also note, that once the line is read into the input buffer it might be advantageous toparse the input buffer based on thecommadelimiter.There are several approaches possible. Make sure to test onEustisas line termina-tion characters/behaviors vary amongst operating systems.3.2    Displaying the data structureThere are no data conversions for this assignment, therefore it is to your advantage todeal with all data elements ascharacter data.3.3    TestingThere will be four (4) input files provided for program testing.   They are describedbelow.
