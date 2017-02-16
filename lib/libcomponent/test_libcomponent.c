#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "libcomponent.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef enum {FALSE = 0, TRUE} boolean;

void printFailedTestText(char* testName, char* text,...);

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

//TEST UNDER CONSTRUCTION
int main(){
    unsigned int testResult = TRUE;
    float *testarray = NULL;
    int returnValue;
    int INVALID_ARGUMENT = -1;
    int INVALID_ARRAY = -2;

    //Test INVALID ARGUMENTS
    returnValue = e_resistance(100.0f, testarray);
    testResult = assertIsTheSame("Check NULL pointer argument", INVALID_ARRAY, returnValue);

    //Test too small array*
    /*
    testarray = malloc(2*sizeof(float));
    returnValue = e_resistance(20.f, &value);
    testResult = assertIsTheSame("Check too small argument array", INVALID_ARRAY, returnValue);
    free(testarray);
	*/

    testarray = malloc(3*sizeof(float));

    returnValue = e_resistance(1000000000000.0f, testarray);
    testResult = assertIsTheSame("Check very high resistance", INVALID_ARGUMENT, returnValue);

    returnValue = e_resistance(-100.0f, testarray);
    testResult = assertIsTheSame("Check negative resistance", INVALID_ARGUMENT, returnValue);

    
    //Test correctness of resistances
    returnValue = e_resistance(1398.f, testarray);
    testResult = assertIsTheSame("Check Index 0", 1200, *testarray );
    testResult = assertIsTheSame("Check Index 1", 180, *(testarray+1));
    testResult = assertIsTheSame("Check Index 2", 18, *(testarray+2));

    returnValue = e_resistance(8210.f, testarray);
    testResult = assertIsTheSame("Check Index 0", 8200, *testarray );
    testResult = assertIsTheSame("Check Index 1", 10, *(testarray+1));
    testResult = assertIsTheSame("Check Index 2", 0, *(testarray+2));
    
    returnValue = e_resistance(1200.f, testarray);
    testResult = assertIsTheSame("Check Index 0", 1200, *testarray );
    testResult = assertIsTheSame("Check Index 1", 0, *(testarray+1));
    testResult = assertIsTheSame("Check Index 2", 0, *(testarray+2));

    returnValue = e_resistance(68445.f, testarray);
    testResult = assertIsTheSame("Check Index 0", 68000, *testarray );
    testResult = assertIsTheSame("Check Index 1", 390, *(testarray+1));
    testResult = assertIsTheSame("Check Index 2", 47, *(testarray+2));

    returnValue = e_resistance(11.f, testarray);
    testResult = assertIsTheSame("Check Index 0", 10, *testarray );
    testResult = assertIsTheSame("Check Index 1", 0, *(testarray+1));
    testResult = assertIsTheSame("Check Index 2", 0, *(testarray+2));

    //Is this acceptable behavior?
    returnValue = e_resistance(269.99f, testarray);
    testResult = assertIsTheSame("Check Index 0", 270, *testarray );
    testResult = assertIsTheSame("Check Index 1", 0, *(testarray+1));
    testResult = assertIsTheSame("Check Index 2", 0, *(testarray+2));

    free(testarray);

    if(testResult != TRUE){
            printFailedTestText("All", "There were tests failing, se above for more information");
            return 1;
        } else {
            printSuccessTestText("All","All tests were ok!");
            return 0;
        }
}
