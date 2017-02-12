#include <stdio.h>
#include "lib/libresistance/libresistance.h"

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
    for(int i = 0; i < numberOfConnections; i++){
        printf("Komponent %i i ohm: ", i+1);
        float* resistance = (resistanceValues + i);
        scanf(" %f", resistance);
    }

    printf("\n======================================= \n");
    //Calculate resistance(Emil)
    float totalresistance = calc_resistance(numberOfConnections, connectionType, resistanceValues);
    printf("\nErsättningsresistans:\n%.1f ohm", totalresistance);
    //Calculate voltage(Daniel)
    //Calc code
    printf("\nEffekt:\n%.2f W", 1.78);

    //Calculate resistance E12 components(Thomas)
    //Calc code
    printf("\nErsättningsresistans i E12-serien kopplade i serie:\n%i\n%i\n%i\n", 1200, 180, 18);
}