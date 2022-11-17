/**
 * Includes
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Definitions
*/
#define ERROR_OPEN      0
#define ERROR_FORMAT    1
#define ERROR_READ      2

typedef struct 
{
    int id;
    char time[20];
    float gen2;
    float gen3;
    float ace2;
    float ace3;
    float set2;
    float set3;
}iccpData;

typedef struct 
{
    char idHeader[50];
    char timeHeader[50];
    char gen2Header[50];
    char gen3Header[50];
    char ace2Header[50];
    char ace3Header[50];
    char set2Header[50];
    char set3Header[50];
}iccpTemp;

typedef struct 
{
    int count;
    iccpTemp readStruct;
} readReturn;


/**
 * Functions
*/

/**
 * Function to print specific error messages to the console
 * @params: int index: tells the switch what error to display
 * @return: 0 if no error
 *          1 if error exists
*/
int errorHandler(int index)
{
    if (index == ERROR_OPEN)
    {
        printf("Error opening file\n");
        return 1;
    }
    switch (index)
    {
    case ERROR_OPEN:
        printf("Error opening file\n");
        return 1;/* code */
        break;
    case ERROR_FORMAT:
        printf("File format incorrect\n");
        return 1;
        break;
    case ERROR_READ:
        printf("Error reading file\n");
        return 1;
        break;
    default:
        break;
    } // switch (index)
    return 0;
} // void errorHandler(int index)

/**
 * The values are read as string, and this function converts each
 *   item into the appropriate data type and returns the structure
 * 
 * @params: iccpTemp inputStruct: structure that holds string 
 *   representation of the values
 * @return: iccpData retStruct: contains the transformed values in the
 *   correct data types 
*/
iccpData transformData(iccpTemp inputStruct)
{
    iccpData retStruct;
    
    retStruct.id = atoi(inputStruct.idHeader);
    memcpy(retStruct.time, inputStruct.timeHeader, sizeof(inputStruct.timeHeader));
    retStruct.gen2 = atof(inputStruct.gen2Header),
    retStruct.gen3 = atof(inputStruct.gen3Header),
    retStruct.ace2 = atof(inputStruct.ace2Header),
    retStruct.ace3 = atof(inputStruct.ace3Header),
    retStruct.set2 = atof(inputStruct.set2Header),
    retStruct.set3 = atof(inputStruct.set3Header);

    return retStruct;
} // iccpData transformData(iccpTemp inputStruct)
