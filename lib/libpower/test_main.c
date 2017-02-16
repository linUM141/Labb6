#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "libpower.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef enum {FALSE = 0, TRUE} boolean;

void printFailedTestText(char* testName, char* text,...);

unsigned assertIsTheSame(char* testName, float expected, float given){
   
    if(fabsf(expected / given - 1) < epsilon){
        return TRUE;
    } else{
        printFailedTestText(testName, "The numbers are not the same. Should be %f but was %f", expected, given);
        return FALSE;
    }
}


unsigned assertIsNotTheSame(char* testName, float expected, float given){
    
    if(fabsf(expected / given - 1) > epsilon){
        return TRUE;
    } else{
        printFailedTestText(testName, "The numbers are the same. Should not be %f but was %f", expected, given);
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

int main (){
    float returnValue;
    int INVALID_ARGUMENT = -1;

    int passedTests = 0;
    int totalTests = 0;

    // Test Correct Arguments
    returnValue = calc_power_r(3.0f, 5.0f);
    totalTests++;
    if (assertIsTheSame("Check correct argument #1", 1.8f, returnValue))
    {
        passedTests++;
    }

    returnValue = calc_power_i(4.2f, 3.6f);
    totalTests++;
    if (assertIsTheSame("Check correct argument #2", 15.12f, returnValue))
    {
        passedTests++;
    }

    // Test Big  Arguments
    returnValue = calc_power_r(1000000000.0f, 5000000000.0f);
    totalTests++;
    
    if (assertIsTheSame("Check correct argument #3", 200000000.0f, returnValue))
    {
        passedTests++;
    }

    returnValue = calc_power_i(1000000000.0f, 5000000000.0f);
    totalTests++;
    if (assertIsTheSame("Check correct argument #4", 5000000000000000000.0f, returnValue))
    {
        passedTests++;
    }

    // Test Invalid Arguments
    returnValue = calc_power_r(0.0f, 5.0f);
    totalTests++;
    if (assertIsTheSame("Check invalid argument #1", INVALID_ARGUMENT, returnValue))
    {
        passedTests++;
    }

    returnValue = calc_power_r(5.0f, 0.0f);
    totalTests++;
    if (assertIsTheSame("Check invalid argument #2", INVALID_ARGUMENT, returnValue))
    {
        passedTests++;
    }

    returnValue = calc_power_i(0.0f, 5.0f);
    totalTests++;
    if (assertIsTheSame("Check invalid argument #3", INVALID_ARGUMENT, returnValue))
    {
        passedTests++;
    }

    returnValue = calc_power_i(5.0f, 0.0f);
    totalTests++;
    if (assertIsTheSame("Check invalid argument #4", INVALID_ARGUMENT, returnValue))
    {
        passedTests++;
    }

    returnValue = calc_power_i(0.0f, -5.0f);
    totalTests++;
    if (assertIsTheSame("Check invalid argument #5", INVALID_ARGUMENT, returnValue))
    {
        passedTests++;
    }

    returnValue = calc_power_i(-5.0f, 0.0f);
    totalTests++;
    if (assertIsTheSame("Check invalid argument #6", INVALID_ARGUMENT, returnValue))
    {
        passedTests++;
    }

    if (passedTests != totalTests)
    {
        printf("%d out of %d tests passed.\n", passedTests, totalTests);
        return 1;
    } 
    else 
    {
        printSuccessTestText("All","All tests were ok!\n");
        return 0;
    }
} 
