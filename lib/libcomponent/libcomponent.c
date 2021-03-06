/**
 * @file	libcomponent.c
 * Source file for the libcomponent library
 * TODO implementation details
 *	
 * @author Thomas Larsson
 * @version 0.1
 *
 */

#define NULL ( (void *) 0)
#include <malloc.h>
#include <float.h>
#include <math.h>
#include "libcomponent.h"

int e_resistance(float orig_resistance, float *res_array) {

	const int ARRAYMAX = 3;
	//Maximum magnitude is MOhm
	const int MAX_MAGNITUDE=6;
	//The twelve relative values in each order of magnitude
	const float e12series[12] = { 1.00f, 1.20f, 1.50f, 1.80f, 2.20f, 2.70f, 3.30f,
			3.90f, 4.70f, 5.60f, 6.80f, 8.20f };
	//powers of 10 as floats
	const float powersOf10[6] = { 1000000.0f, 100000.0f, 10000.0f, 1000.0f, 100.0f, 10.0f };

	//Test tolerance, as minimum resistor value is 10 and minimum deltaresistance is 2 this should work
	const float TOLERANCE=0.1f;
	int magnitude = 0;

	//Negative resistance cant be built, nor does the series extend above MegaOhm values
	if (orig_resistance < 0.0f || orig_resistance > 10 * powersOf10[0]){
		return -1;
	}

	//If total resistance is less than 10 Ohms, this function cannot construct it
	if (orig_resistance < 10.0f){
		return -1;
	}

	//Is res_array a null pointer?
	if(NULL==res_array){
		return -2;
	}

	//Is res_array allocated big enough to hold 3 floats
	if(malloc_usable_size(res_array)<(3*sizeof(float))){
		return -2;
	}

	//From Highest to Lowest power of 10, loop e12 series backwards, compare to orig res value
	//Iff value is smaller, save value in res array, subtract from orig_resistance and repeat
	int i;
	int res_array_index = 0;
	for (; magnitude < MAX_MAGNITUDE; magnitude++) {
		for (i = 0; i < 12; i++) {
			if(isgreaterequal(orig_resistance+TOLERANCE, e12series[11 - i] * powersOf10[magnitude])){
				if (res_array_index < ARRAYMAX) {
					res_array[res_array_index] = e12series[11 - i]
							* powersOf10[magnitude];
					orig_resistance -= e12series[11 - i]
							* powersOf10[magnitude];
					res_array_index++;
				}
			}
		}
	}

	//Fill unused values as per specification, we cannot be sure that the array is 0-init
	for (i = res_array_index; i < ARRAYMAX; i++) {
		*(res_array + i) = 0.0f;
	}

	return res_array_index;

}
