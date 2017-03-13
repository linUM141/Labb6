/**
* @file libresistance.h
*/

#ifndef LIBRESISTANCE
#define LIBRESISTANCE
/**
* @brief Calculate the resistance for either parallell or serial connections.
*
* Calculates the resistance values for either a series of components that are connected in parallell or serial.
* @param count The number of components
* @param conn The type of connection, can be either P(Parallell) or S(Serial)
* @param *array The resistance values of the components
* @return The summarized resistance value. If any of the input arguments are incorrect, -1 will be returned.
**/
float calc_resistance(int count, char conn, float *array);

#endif
