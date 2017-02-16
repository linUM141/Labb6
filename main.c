#include <stdio.h>
//malloc etc
#include <stdlib.h>
#include "lib/libresistance/libresistance.h"
#include "lib/libpower/libpower.h"
#include "lib/libcomponent/libcomponent.h"

int main(){
    float voltage = 0;
    char connectionType;
    int numberOfConnections = 0;

    printf("Ange spänningskälla i V: ");
    scanf("%f", &voltage);
    
    printf("Ange koppling[S | P]: ");
    scanf(" %c", &connectionType);
    
    printf("Antal komponenter: ");
    scanf(" %i", &numberOfConnections);

    float* resistanceValues = malloc(numberOfConnections*sizeof(float));
    int i = 0;
    for(; i < numberOfConnections; i++){
        printf("Komponent %i i ohm: ", i+1);
        float* resistance = (resistanceValues + i);
        scanf(" %f", resistance);
    }

    //printf("\n======================================= \n");
    //Calculate resistance(Emil)
    float totalresistance = calc_resistance(numberOfConnections, connectionType, resistanceValues);
    printf("\nErsättningsresistans:\n%.1f ohm", totalresistance);
    //Calculate voltage(Daniel)
    //Calc code
    printf("\nEffekt:\n%.2f W", calc_power_r(voltage, totalresistance));

    //Calculate resistance E12 components(Thomas)
    float* replaceResistanceValues = calloc(3,sizeof(float));
    if(NULL==replaceResistanceValues){
    	printf("\nMalloc failure\n");
    	return -1;
    }
    //Calc code
	int numberOfResistors = e_resistance(totalresistance, replaceResistanceValues);
    if(numberOfResistors<0){
    	printf("\nError in replacement resistor calculation\n");
    } else {
    printf("\nErsättningsresistans i E12-serien kopplade i serie:\n%.0f\n%.0f\n%.0f\n", *replaceResistanceValues, *(replaceResistanceValues+1), *(replaceResistanceValues+2));
    }

    free(replaceResistanceValues);
}
