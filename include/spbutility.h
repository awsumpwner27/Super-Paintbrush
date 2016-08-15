#ifndef SPBUTILITY_H
#define SPBUTILITY_H

/*#define M_SQRT3 1.73205080756887729353*/
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

unsigned int spb_floorToPowerOfTwo(unsigned int a);

float spb_log2f(float);

/*

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
Sort guaranteed to be stable.
*/
void spb_stableSort(
    void* base,
    size_t num_items,
    size_t size,
    int (*comparator)(const void*, const void*)
);

#endif