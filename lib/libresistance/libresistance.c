#include "stdio.h"
#include "libresistance.h"


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