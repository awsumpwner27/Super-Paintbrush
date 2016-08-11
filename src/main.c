#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "spbintegers.h"
#include "spbtool.h"
#include "spbpalette.h"
#include "spbcolor.h"

#ifdef __linux__

long int randomNumberPls() {
	long int num;
	FILE* random_file;

	random_file = fopen("/dev/urandom", "r");
	fread(&num, sizeof(long int), 1, random_file);
	fclose(random_file);

	return num;
}

void randomBufferPls(void* buffer, size_t count) {
	FILE* random_file;

	random_file = fopen("/dev/urandom", "r");
	fread(buffer, 1, count, random_file);
	fclose(random_file);
}

#elif _WIN32

else
#error Yikes!
#endif 

int main() {
	enum SPBPaletteSORTTYPE sort;
	SPBColor color0;
	char color_str[5];
	unsigned char random_str[17];
	int j;

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

	printf("%ld\n", randomNumberPls());
	printf("%lu\n", sizeof(long int));

	for(j = 0; j < 16; ++j) {
		randomBufferPls(random_str, 16);
		{
			int i;
			for(i = 0; i < 16; ++i) {
				random_str[i] = abs(random_str[i] % 26) + 65;
			}
		}
		random_str[16] = '\0';
		printf("%s\n", random_str);
	}

	return 0;
}