#include <stddef.h>
#include <stdlib.h>

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