#include <stddef.h>
#include <stdlib.h>
#include "spbutility.h"

#include "spbpalette.h"

/*
Create a new palette, allocating memory for its array as appropriate and filling the new array with the specified color.
*/
SPBPalette* spbPltNew(
	unsigned int num_entries,
	SPBColor fill_param
) {
	SPBPalette* palette = NULL;
	int i;

	palette = malloc(sizeof(SPBPalette));

	palette->num_entries = num_entries;

	palette->entries = malloc(num_entries * sizeof(SPBColor));
	for(i = 0; i < num_entries; ++i) {
		palette->entries[i] = fill_param;
	}

	return palette;
}

/*
Adjust the size of the palette's array, filling in the difference.
*/
void spbPltResize(
	SPBPalette* palette, /* modify */
	unsigned int num_entries,
	SPBColor fill_param
) {
	int old_num;

	palette->entries = realloc(palette->entries, num_entries);

	old_num = palette->num_entries;
	palette->num_entries = num_entries;

	if(num_entries > old_num) {
		unsigned int entries_diff = num_entries - old_num;
		int i;

		for(i = 0; i < entries_diff; ++i) {
			palette->entries[i + old_num] = fill_param;
		}
	}
}

/*
Free the palette's memory.
*/
void spbPltFree(
	SPBPalette** palette
) {
	free((*palette)->entries);
	(*palette)->entries = NULL;

	free(*palette);
	*palette = NULL;
}

/*
Read little-endian SNES color data from a byte buffer.
	The word count corresponds to the count of pairs of bytes to be read in. If the word count passed in differs from the palette's number of available entries, a call is made to spbPltResize prior to the buffer being evaluated.
*/
void spbPltReadSNESColorsFromByteBuffer(
	SPBPalette* palette, /* modify */
	spbuint8_t* buffer,
	unsigned int word_count
) {
	int i;

	if(word_count != palette->num_entries) {
		spbPltResize(palette, word_count, spbClrNew(0u, 0u, 0u));
	}

	for(i = 0; i < word_count; ++i) {
		spbuint16_t tmp_color_word;

		tmp_color_word =
			((spbuint16_t)buffer[i * 2 + 0]) << 0 ||
			((spbuint16_t)buffer[i * 2 + 1]) << 8;
		palette->entries[i] = spbClrFromSNESColorWord(tmp_color_word);
	}
}

/*
Swap two colors in a palette, but make no change itself accounting for the image data.
*/
void spbPltSwap(
	SPBPalette* palette, /* modify */
	unsigned int index0,
	unsigned int index1
) {
	SPBColor tmp_color;

	if(
		index0 > palette->num_entries - 1 ||
		index1 > palette->num_entries - 1
	){
		return;
	}

	tmp_color = palette->entries[index0];
	palette->entries[index0] = palette->entries[index1];
	palette->entries[index1] = tmp_color;
}

/*
Sort the colors in a palette by some criteria, making no change to the image data.
	Note the order proxy buffer. It provides a facility for the rearrangement of colors in image data manipulation functions by representing the changes made to the palette order as some permutation of the numbers from 0 to n-1, with n being the number of colors in the palette.
*/
void spbPltSort(
	SPBPalette* palette, /* modify */
	unsigned int* order_proxy_buffer, /* out */
	enum SPBPaletteSORTTYPE sort_type /* options */
) {
	typedef struct {
		unsigned int index;
		/*The criteria depends on the sort type. For example, it varies depending on if the sort is by the red channel or by hue, and in particular depends on whether the sort is ascending or descending, as in descending order, the calculated criteria value is inverted. For simplicity's sake, the criteria must be a value on the range [0, 1].*/
		float criteria;
	} IndexCriteriaPair;

	IndexCriteriaPair* sort_pairs;
	int option_criteria = sort_type & 0x07;				/*enum		0000 0111*/
	int option_order = sort_type & 0x08;				/*enum		0000 1000*/
	int option_preserve_first = (sort_type >> 5) & 0x01;/*bool		0001 0000*/
	int i;

	sort_pairs = malloc(palette->num_entries * sizeof(IndexCriteriaPair));
	/*Generate the data to be sorted.*/
	for(i = 0; i < palette->num_entries; ++i) {
		SPBColorf colorf = spbClfFromClr(palette->entries[i]);

		sort_pairs[i].index = i;

		switch(option_criteria) {
		case SPB_SORT_HUE:
			{
				sort_pairs[i].criteria = spbClfGetHue(colorf);
				break;
			}
		case SPB_SORT_SATURATION_HSL:
			{
				sort_pairs[i].criteria = spbClfGetSaturationHSL(colorf);
				break;
			}
		case SPB_SORT_LIGHTNESS_HSL:
			{
				sort_pairs[i].criteria = spbClfGetLightnessHSL(colorf);
				break;
			}
		case SPB_SORT_RED:
			{
				sort_pairs[i].criteria = colorf.r;
				break;
			}
		case SPB_SORT_GREEN:
			{
				sort_pairs[i].criteria = colorf.g;
				break;
			}
		case SPB_SORT_BLUE:
			{
				sort_pairs[i].criteria = colorf.b;
				break;
			}
		}

		if(option_order == SPB_SORT_DESCENDING) {
			/*Invert criteria variable to facilitate a reverse in the default sorting order.*/
			sort_pairs[i].criteria = 1 - sort_pairs[i].criteria;
		}
	}

	free(sort_pairs);
}