#ifndef SPBPALETTE_H
#define SPBPALETTE_H

#include "spbcolor.h"

typedef struct {
	/*Number of palette entries.*/
	unsigned int num_entries;
	/*Array of colors.*/
	SPBColor* entries;
} SPBPalette; /* Plt */

enum SPBPaletteSORTTYPE {
	SPB_SORT_HUE			= 0x00,
	SPB_SORT_SATURATION_HSL	= 0x01,
	SPB_SORT_LIGHTNESS_HSL	= 0x02,
	SPB_SORT_RED			= 0x03,
	SPB_SORT_GREEN			= 0x04,
	SPB_SORT_BLUE			= 0x05,

	SPB_SORT_ASCENDING		= 0x00, /* default */
	SPB_SORT_DESCENDING		= 0x08,

	SPB_SORT_PRESERVE_FIRST	= 0x10,

	SPB_SORT_INDIVIDUAL		= 0x00, /* default */
	SPB_SORT_GROUP_SIMILAR	= 0x20
};

/*
Create a new palette, allocating memory for its array as appropriate and filling the new array with the specified color.
*/
SPBPalette* spbPltNew(
	unsigned int num_entries,
	SPBColor fill_param
);

/*
Adjust the size of the palette's array, filling in the difference.
*/
void spbPltResize(
	SPBPalette*, /* modify */
	unsigned int num_entries,
	SPBColor fill_param
);

/*
Free the palette's memory.
*/
void spbPltFree(
	SPBPalette**
);

/*
Read little-endian SNES color data from a byte buffer.
	The word count corresponds to the count of pairs of bytes to be read in. If the word count passed in differs from the palette's number of available entries, a call is made to spbPltResize prior to the buffer being evaluated.
*/
void spbPltReadSNESColorsFromByteBuffer(
	SPBPalette*, /* modify */
	spbuint8_t* buffer,
	unsigned int word_count
);

/*
Swap two colors in a palette, but make no change itself accounting for the image data.
*/
void spbPltSwap(
	SPBPalette*, /* modify */
	unsigned int index0,
	unsigned int index1
);


/*
Sort the colors in a palette by some criteria, making no change to the image data.
	Note the order proxy buffer. It provides a facility for the rearrangement of colors in image data manipulation functions by representing the changes made to the palette order as some permutation of the numbers from 0 to n-1, with n being the number of colors in the palette.
*/
void spbPltSort(
	SPBPalette*, /* modify */
	unsigned int* order_proxy_buffer, /* out */
	float plateau_frequency,
	enum SPBPaletteSORTTYPE /* options */
);


#endif