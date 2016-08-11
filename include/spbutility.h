#ifndef SPBUTILITY_H
#define SPBUTILITY_H

/*#define M_SQRT3 1.73205080756887729353*/
#define spb_min(a, b) (a < b ? a : b)
#define spb_max(a, b) (a > b ? a : b)

/*
Wrap x into the range [0, y). Undefined for a negative or zero y.
    Example usage:
    spb_fwrap(10.6f, 3.f) -> 1.6f
    spb_fwrap(-5.5f, 4.f) -> 2.5f
*/
float spb_fwrap(float x, float y);

/*
Sort guaranteed to be stable.
*/
void spb_stableSort(
    void* base,
    unsigned int num_items,
    size_t size,
    int (*comparator)(const void*, const void*)
);

#endif