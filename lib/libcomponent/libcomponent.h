/**
 * @file	libcomponent.h
 * Header file for the libcomponent library functions
 * libcomponent is a library for calculating which resistors from the 
 * E12 series that should be used to get, approximately, a given resistance
 *
 * @author Thomas Larsson
 * @version 0.1
 *
 */
#ifndef LIBCOMPONENT_H_
#define LIBCOMPONENT_H_

int e_resistance(float res, float *res_array);

#endif /* LIBCOMPONENT_H_ */
