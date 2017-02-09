#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include "libresistance.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef enum {FALSE = 0, TRUE} boolean;

unsigned assertIsTheSame(char* testName,float expected, float given){
   
    if(expected == given){
        return TRUE;
    } else{
        printFailedTestText(testName, "The numbers are not the same. Should be %f but was %f", expected, given);
        assert(expected == given);
        return FALSE;
    }
}


unsigned assertIsNotTheSame(char* testName, float expected, float given){
    
    if(expected != given){
        return TRUE;
    } else{
        printFailedTestText(testName, "The numbers are the same. Should not be %f but was %f", expected, given);
        assert(expected != given);
        return FALSE;
    }
}

void printTestText(char* testName, char* text, char* colour, va_list args){
    char* message;
    char* delimiter = ": ";
    char* newLine = "\n";
    message = malloc(strlen(testName) + strlen(delimiter) + strlen(text) + strlen(ANSI_COLOR_RED) + strlen(newLine));
    strcpy(message, colour);
    strcat(message, testName);
    strcat(message, delimiter);
    strcat(message, text);
    strcat(message, newLine);

    vprintf( message, args );
    printf(ANSI_COLOR_RESET);
    va_end( args );
}

void printFailedTestText(char* testName, char* text,...){
    va_list args;
    va_start( args, text );
    printTestText(testName, text, ANSI_COLOR_RED, args);
}

void printSuccessTestText(char* testName, char* text,...){
    va_list args;
    printTestText(testName, text, ANSI_COLOR_GREEN, args);
}

int main(){
    unsigned int testResult = TRUE;
    float returnValue;
    int INVALID_ARGUMENT = -1;

    float testArray[2] = {1,2};
    int testArraySize = sizeof(testArray)/sizeof(testArray[0]);

    returnValue = calc_resistance(0,'P',0);
    testResult = assertIsTheSame("Check that count 0 is not allowed", INVALID_ARGUMENT, returnValue);

    returnValue = calc_resistance(-1,'P',0);
    testResult = assertIsTheSame("Check that count lower than 0 is not allowed",INVALID_ARGUMENT, returnValue);
    
    returnValue = calc_resistance(testArraySize, 'V', testArray);
    testResult = assertIsTheSame("Sending in V in conn and should get -1 as a result", INVALID_ARGUMENT, returnValue);

    float* nullPointer = 0;
    returnValue = calc_resistance(4, 'P', nullPointer);
    testResult = assertIsTheSame("Sending in the array with a null pointer gives -1 as result", INVALID_ARGUMENT, returnValue);

    //float values[5] = {1,2,3,4,5};
    //returnValue = calc_resistance(4, 'P', values);
    //testResult = assertIsTheSame("Sending in array with different items than count in should get -1 as a result", INVALID_ARGUMENT, returnValue);

    float testArrayWithOneZeroItem[3] = {0,1,2};
    returnValue = calc_resistance(testArraySize, 'P', testArrayWithOneZeroItem);
    testResult = assertIsTheSame("Sending in one array item with 0 and P should give return value 0", 0, returnValue);

    returnValue = calc_resistance(testArraySize, 'S', testArrayWithOneZeroItem);
    testResult = assertIsNotTheSame("Sending in one array item with 0 and S should not give return value 0", 0, returnValue);

    returnValue = calc_resistance(testArraySize, 'S', testArray);
    testResult = assertIsTheSame("Verify that summary of resistance items for S is working", 3, returnValue);

    returnValue = calc_resistance(testArraySize, 'P', testArray);
    testResult = assertIsTheSame("Verify that summary of resistance items for P is working", 1.5, returnValue);

    if(testResult != TRUE){
        printFailedTestText("All", "There were tests failing, se above for more information");
        return 1;
    } else {
        printSuccessTestText("All","All tests were ok!");
        return 0;
    }
}