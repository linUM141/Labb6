/**
* @file test_main.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <string.h>
#include "libresistance.h"

/**
* @brief Defines the red colour
*/
#define ANSI_COLOR_RED     "\x1b[31m"
/**
* @brief Defines the green colour
*/
#define ANSI_COLOR_GREEN   "\x1b[32m"

/**
* @brief Define the original color, used when going back to default console colour.
*/
#define ANSI_COLOR_RESET   "\x1b[0m"


/**
* @brief To avoid having to use 1 and 0, there is an enum definition that mimics true and false.*/
typedef enum
{
    FALSE = 0, /**< The same as 0.*/
    TRUE /**< The same as 1. */
} boolean;

/**
* @brief Prints a text with a given colour and a list of arguments
*
* A wrapper around printf that simplifies printing out test result text in different colours.
* @param testName The name of the test
* @param text The text message to print out
* @param colour The colour of the text to print
* @param args The arguments for the text output, it's a va_list so provide it in the same way as for a printf call
* @return void
**/
void printTestText(char* testName, char* text, char* colour, va_list args){
    char* message;
    char* delimiter = ": ";
    char* newLine = "\n";
    message = malloc(strlen(testName) + strlen(delimiter) + strlen(text) + strlen(colour) + strlen(newLine));
    strcpy(message, colour);
    strcat(message, testName);
    strcat(message, delimiter);
    strcat(message, text);
    strcat(message, newLine);

    vprintf( message, args );
    printf(ANSI_COLOR_RESET);
    va_end( args );
}

/**
* @brief Prints failing test messages
*
* Calls printTestText function with red text as pre defined and provide the parameters sent in
* @param testName The name of the test
* @param text The text message to print out
* @return void
**/
void printFailedTestText(char* testName, char* text,...){
    va_list args;
    va_start( args, text );
    printTestText(testName, text, ANSI_COLOR_RED, args);
}

/**
* @brief Prints successful test messages
*
* Calls printTestText function with green text as pre defined and provide the parameters sent in
* @param testName The name of the test
* @param text The text message to print out
* @return void
**/
void printSuccessTestText(char* testName, char* text,...){
    va_list args;
    va_start( args, text );
    printTestText(testName, text, ANSI_COLOR_GREEN, args);
}

/**
* @brief Test method that is used to check if two floats are the same
*
* Compare two float values and returns 1 if it's the same and 0 if it's not. It allso makes an assert(expected == given).
* @param testName The name of the test
* @param expected The value to expect
* @param given The value returned by the test
* @return Returns 1(TRUE) if the test is ok and 0(FALSE) if it's not
**/
unsigned assertIsTheSame(char* testName,float expected, float given){
   
    if(expected == given){
        return TRUE;
    } else{
        printFailedTestText(testName, "The numbers are not the same. Should be %f but was %f", expected, given);
        assert(expected == given);
        return FALSE;
    }
}

/**
* @brief Test method that is used to check if two floats are not the same
*
* Compare two float values and returns 1 if it's not the same and 0 if it is. It allso makes an assert(expected != given).
* @param testName The name of the test
* @param expected The value to expect
* @param given The value returned by the test
* @return Returns 1(TRUE) if the test is ok and 0(FALSE) if it's not
**/
unsigned assertIsNotTheSame(char* testName, float expected, float given){
    
    if(expected != given){
        return TRUE;
    } else{
        printFailedTestText(testName, "The numbers are the same. Should not be %f but was %f", expected, given);
        assert(expected != given);
        return FALSE;
    }
}

/**
* @brief Runs all the tests
*
* Runs all the tests and returns 0 if it's ok and 1 if it's not
* @return Returns 0 if it's ok and 1 if it's not ok.
**/
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

    float testArrayWithOneZeroItem[3] = {0,1,2};
    returnValue = calc_resistance(testArraySize, 'P', testArrayWithOneZeroItem);
    testResult = assertIsTheSame("Sending in one array item with 0 and P should give return value 0", 0, returnValue);

    returnValue = calc_resistance(testArraySize, 'S', testArrayWithOneZeroItem);
    testResult = assertIsNotTheSame("Sending in one array item with 0 and S should not give return value 0", 0, returnValue);

    returnValue = calc_resistance(testArraySize, 'S', testArray);
    testResult = assertIsTheSame("Verify that summary of resistance items for S is working", 3, returnValue);

    float testArrayWithRealResistanceScenario[2] = {150,300};
    returnValue = calc_resistance(sizeof(testArrayWithRealResistanceScenario)/sizeof(testArrayWithRealResistanceScenario[0]), 'P', testArrayWithRealResistanceScenario);
    testResult = assertIsTheSame("Verify that summary of resistance items for P is working", 100, returnValue);

    if(testResult != TRUE){
        printFailedTestText("All", "There were tests failing, se above for more information");
        return 1;
    } else {
        printSuccessTestText("All","All tests were ok!");
        return 0;
    }
}
