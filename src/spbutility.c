#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "spbutility.h"

/*
Wrap x into the range [0, y). Undefined for a negative or zero y.
    Example usage:
    spb_fwrapf(10.6f, 3.f) -> 1.6f
    spb_fwrapf(-5.5f, 4.f) -> 2.5f
*/
float spb_fwrapf(float x, float y){
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
For an unsigned int, compute the highest power of two less than a given number.
*/
unsigned int spb_floorToPowerOfTwo(unsigned int a) {
	unsigned int result; 
	const size_t bit_count = 8 * sizeof(unsigned int);
	int i;

	for(i = 1; i <= bit_count; ++i) {
		if((a >> (bit_count - i)) & 0x01u) {
			result = a & (0x80000000u >> (i - 1));
			break;
		}
	}
	return result;
}

/*
Compute log base 2 for a given float.
*/
float spb_log2f(float a) {
	return log(a) / log(2.f);
}

/*
Swap the position of two objects in memory.
*/
void spb_swap(
	void* a,
	void* b,
	size_t size
) {
	void* tmp = malloc(size);

	memcpy(tmp, a, size);
	memcpy(a, b, size);
	memcpy(b, tmp, size);

	free(tmp);
}

/*
Takes two ordered lists and combines them in order while placing them in a buffer (out_buffer) of num_items0 + num_items1 size.
*/
void spb_orderedMerge(
	void* base0,
	void* base1,
	void* out_buffer,
	size_t num_items0,
	size_t num_items1,
	size_t size,
	int (*comparator)(const void*, const void*)
) {
	/*Pointer math macro. Depends on size parameter. Undefined with the end of the function body.*/
	#define ACCESS(ptr, offset) ((void*)((char*)(ptr) + ((offset) * size)))

	int item_counter0, item_counter1;
	for(
		item_counter0 = 0, item_counter1 = 0;
		item_counter0 < num_items0 || item_counter1 < num_items1;
	) {
		int result = comparator(
			ACCESS(base0, item_counter0),
			ACCESS(base1, item_counter1)
		);

		if(
			item_counter0 > num_items0 - 1 &&
			!(item_counter1 > num_items1 - 1)
		) {
			/*End of array 0, auto-favor array 1.*/
			result = 1;
		} else
		if(
			item_counter1 > num_items1 - 1 &&
			!(item_counter0 > num_items0 - 1)
		) {
			/*End of array 1, auto-favor array 0.*/
			result = -1;
		}
		
		if(result <= 0) {
			memcpy(
				ACCESS(out_buffer, item_counter0 + item_counter1),
				ACCESS(base0, item_counter0),
				size
			);
			item_counter0++;
		} else {
			memcpy(
				ACCESS(out_buffer, item_counter0 + item_counter1),
				ACCESS(base1, item_counter1),
				size
			);
			item_counter1++;
		}
	}

	#undef ACCESS
}

/*
A stable sort. It retains the pre-existing order of items with identical sorting criteria.
*/
void spb_stableSort(
    void* base,
    size_t num_items,
    size_t size,
    int (*comparator)(const void*, const void*)
) {
	/*Pointer math macro. Depends on size parameter. Undefined with the end of the function body.*/
	#define ACCESS(ptr, offset) ((void*)((char*)(ptr) + ((offset) * size)))
	
	size_t num_items_2floor = spb_floorToPowerOfTwo(num_items);
	int pass_counter = 0;
	/*Reserve space equal to the initially given array to have space for later merge operations.*/
	void* scratchpad = malloc(num_items * size);

	for(
		pass_counter = 0;
		spb_2powi(pass_counter + 0) < num_items_2floor;
		++pass_counter
	) {
		size_t group_size = spb_2powi(pass_counter);
		int group_index = 0;

		for(
			group_index = 0;
			group_index < num_items_2floor / group_size;
			group_index += 2 /*Jump two *groups* at a time. Not two elements.*/
		) {
			spb_orderedMerge(
				ACCESS(base, (group_index + 0) * group_size),
				ACCESS(base, (group_index + 1) * group_size),
				ACCESS(scratchpad, (group_index + 0) * group_size),
				group_size,
				group_size,
				size,
				comparator
			);
		}
		memcpy(
			base,
			scratchpad,
			num_items_2floor * size
		);
	}

	if(num_items > num_items_2floor) {
		/*Recursive call to operate on the end of the array. After this returns, we can assume the end-portion of the array is sorted and merge with it.*/
		spb_stableSort(
			ACCESS(base, num_items_2floor),
			num_items - num_items_2floor,
			size,
			comparator
		);
		spb_orderedMerge(
			base,
			ACCESS(base, num_items_2floor),
			scratchpad,
			num_items_2floor,
			num_items - num_items_2floor,
			size,
			comparator
		);
		memcpy(
			base,
			scratchpad,
			num_items * size
		);
	}

	free(scratchpad);
	#undef ACCESS
}