/**
* @file libresistance.c
*/
#include "stdio.h"
#include "libresistance.h"

/**
* @brief Checks if any of the arguments are incorrect
*
* Checks if any of the arguments are incorrect. It checks:
* conn is P or S
* count is larger than 0
* array is not an empty array
* @param count The number of components
* @param conn The type of connection, can be either P(Parallell) or S(Serial)
* @param *array The resistance values of the components
* @return Returns -1 if any of the arguments is incorrect, otherwise 0.
**/
unsigned hasInvalidArguments(int count, char conn, float *array){
    if(count <= 0){
        return -1;
    }
    if(conn != 'P' && conn != 'S'){
        return -1;
    }

    if(!array){
        return -1;
    }

    return 0;
}

float calc_resistance(int count, char conn, float *array){
    //printf("Calc resistance %i \n", count);

    if(hasInvalidArguments(count, conn, array)){
        return -1;
    }

    
    int i = 0;
    unsigned hasZeroItem = 0;
    float resistanceSum = 0;
    do {
        float resValue = *(array + i);

        if(resValue == 0 && conn == 'P'){
            hasZeroItem = 1;
            break;
        } else if(conn == 'S'){
            resistanceSum = resistanceSum + resValue;
        } else{
            resistanceSum = resistanceSum + 1/resValue;
        }
        i = i + 1;
    } while(i < count);

    if(hasZeroItem == 1){
        //printf("Found zero item\n");
        return 0;
    }

    if(conn == 'P'){
        resistanceSum = 1/resistanceSum;
    }

    return resistanceSum;
}