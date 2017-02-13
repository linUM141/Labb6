#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include <stdlib.h>
#include "libcomponent.h"

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

//TEST UNDER CONSTRUCTION
int main(){
    unsigned int testResult = TRUE;
    float returnValue;
    int INVALID_ARGUMENT = -1;

    //Test INVALID ARGUMENTS
    //Test very high resistance
    //Test negative resistance
    //Test non-allocated array
    
    //Test correctness of resistances
    
    return testResult;
}
