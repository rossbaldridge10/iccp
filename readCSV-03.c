#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcHeader.h"

int main(void)
{
    // open file
    FILE *file = fopen("exported_sql_data_rev2.csv", "r");
    
    // declare variables to hold data/headers/tmpData
    iccpData dataLines[100];
    iccpTemp headers;
    iccpTemp tmpData;
    readReturn dataStruct;

    // keep track of items in each line
    int read = 0;
    // number of lines
    int records = 0;

    if (file == NULL)
    {
        errorHandler(ERROR_OPEN);
    } // if (file == NULL)
    
    // scan for headers
    read = fscanf(file,
        "%49[^,],%49[^,],%49[^,],%49[^,],%49[^,],%49[^,],%49[^,],%49[^\n]",
        headers.idHeader,
        headers.timeHeader,
        headers.gen2Header,
        headers.gen3Header,
        headers.ace2Header,
        headers.ace3Header,
        headers.set2Header,
        headers.set3Header);
    printf("Number of headers read:\t%d\n", read);
    // print headers
    printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n",
        headers.idHeader,
        headers.timeHeader,
        headers.gen2Header,
        headers.gen3Header,
        headers.ace2Header,
        headers.ace3Header,
        headers.set2Header,
        headers.set3Header);
    do 
    {
        // read data
        read = fscanf(file,
            "%49[^,],%49[^,],%49[^,],%49[^,],%49[^,],%49[^,],%49[^,],%49[^\n]",
            tmpData.idHeader,
            tmpData.timeHeader,
            tmpData.gen2Header,
            tmpData.gen3Header,
            tmpData.ace2Header,
            tmpData.ace3Header,
            tmpData.set2Header,
            tmpData.set3Header);
        // dataStruct = readData(file,tmpData);

        /**
         * convert data to correct datatypes
        */
        dataLines[records] = transformData(tmpData);

        if (read == 8) 
        {
            records++;
            printf("\nItems per line:\t\t%d\nLine number:\t\t%d\n", read, records);
        } // if (read == 8) 
        
        // in case of errors
        if (read != 8 && !feof(file))
        {
            errorHandler(ERROR_FORMAT);
        } // if (read != 4 && !feof(file))

        // in case of error
        if (ferror(file))
        {
            errorHandler(ERROR_READ);
        } // if (ferror(file))

    } while (!feof(file));
    // close file
    fclose(file);

    // print number of lines read
    printf("\n%d lines read\n\n", records);
    // print line by line
    for (int i = 0; i< records; i++)
    {
        printf("%d\t%s\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n",
            dataLines[i].id,
            dataLines[i].time,
            dataLines[i].gen2,
            dataLines[i].gen3,
            dataLines[i].ace2,
            dataLines[i].ace3,
            dataLines[i].set2,
            dataLines[i].set3);
    } // for (int i = 0; i< records; i++)
    printf("\n");

    return 0;
} // main(void)