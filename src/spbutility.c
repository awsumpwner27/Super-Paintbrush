#include <math.h>
#include <stdlib.h>

#include "spbutility.h"

/*
Wrap x into the range [0, y). Undefined for a negative or zero y.
    Example usage:
    spb_fwrap(10.6f, 3.f) -> 1.6f
    spb_fwrap(-5.5f, 4.f) -> 2.5f
*/
float spb_fwrap(float x, float y){
	float wrapped;

	if(x >= 0 && y > 0){
		wrapped = fmod(x, y);
	} else 
	if(x < 0 && y > 0) {
		wrapped = y - abs(fmod(x, y));
	} else {
		/*Undefined. Return NaN.*/
		wrapped = (0.f / 0.f);
	}

	return wrapped;
}

/*
A stable sort. It retains the pre-existing order of items with identical sorting criteria.
*/
void spb_stableSort(
    void* base,
    unsigned int num_items,
    size_t size,
    int (*comparator)(const void*, const void*)
) {

}