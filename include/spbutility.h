#ifndef SPBUTILITY_H
#define SPBUTILITY_H

#define spb_min(a, b) ((a) < (b) ? (a) : (b))
#define spb_max(a, b) ((a) > (b) ? (a) : (b))

#define spb_2powi(a) (1 << (a))

/*
Wrap x into the range [0, y). Undefined for a negative or zero y.
    Example usage:
    spb_fwrap(10.6f, 3.f) -> 1.6f
    spb_fwrap(-5.5f, 4.f) -> 2.5f
*/
float spb_fwrapf(float x, float y);

/*
For an unsigned int, compute the highest power of two less than a given number.
*/
unsigned int spb_floorToPowerOfTwo(unsigned int a);

/*
Compute log base 2 for a given float.
*/
float spb_log2f(float);

/*
Swap the position of two objects in memory.
*/
void spb_swap(
    void* a,
    void* b,
    size_t size
);

/*

*/
void spb_shift(
	int amount,
	void* subarray_start,
	void* subarray_end,
	void* bound_start,
	void* bound_end,
	size_t size
);

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
);

/*
A stable sort. It retains the pre-existing order of items with identical sorting criteria.
*/
void spb_stableSort(
    void* base,
    size_t num_items,
    size_t size,
    int (*comparator)(const void*, const void*)
);

#endif