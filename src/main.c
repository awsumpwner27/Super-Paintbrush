#include <stdio.h>
#include <ctype.h>
#include <math.h>

#include "spbintegers.h"
#include "spbtool.h"
#include "spbpalette.h"
#include "spbcolor.h"

int main() {
	enum SPBPaletteSORTTYPE sort;
	SPBColor color0;
	char color_str[5];

	/* SPB Testing */

	color0 = spbClrNew(31, 127, 255);
	sprintf(color_str, "%x", spbClrGetSNESColorWord(color0));
	{
		int i = -1;
		while(color_str[++i]) {
			color_str[i] = toupper(color_str[i]);
		}
	}
	printf("0x%s\n", color_str);
	sort = SPB_SORT_RED | SPB_SORT_DESCENDING | SPB_SORT_PRESERVE_FIRST;
	printf("%d\n", sort);

	/* END */

	return 0;
}