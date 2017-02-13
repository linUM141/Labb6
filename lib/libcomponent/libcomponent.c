/**
 * @file	libcomponent.c
 * Source file for the libcomponent library
 * TODO implementation details
 *	
 * @author Thomas Larsson
 * @version 0.1
 *
 */

#include "libcomponent.h"

int e_resistance(float orig_resistance, float *res_array) {

	const int ARRAYMAX = 3;

	//Maximum magnitude is MOhm
	int magnitude = 0;
	//The twelve relative values in each order of magnitude
	float e12series[12] = { 1.00f, 1.20f, 1.50f, 1.80f, 2.20f, 2.70f, 3.30f,
			3.90f, 4.70f, 5.60f, 6.80f, 8.20 };
	//powers of 10 as floats
	float powersOf10[6] = { 1000000.0f, 100000.0f, 10000.0f, 1000.0f, 100.0f, 10.0f };

	//Negative resistance cant be built, nor does the series extend above MegaOhm values
	if (orig_resistance < 0.0f || orig_resistance > 10 * powersOf10[0])
		return -1;

	//From Highest to Lowest power of 10, loop e12 series backwards, compare to orig res value
	//Iff value is smaller, save value in res array, subtract from orig_resistance and repeat
	int i;
	int res_array_index = 0;
	for (; magnitude < 6; magnitude++) {
		for (i = 0; i < 12; i++) {
			if (orig_resistance >= e12series[11 - i] * powersOf10[magnitude]) {
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
	for (i = res_array_index; res_array_index < ARRAYMAX; res_array_index++) {
		*(res_array + i) = 0.0f;
	}

	return res_array_index;

}
