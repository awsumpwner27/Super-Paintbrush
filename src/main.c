#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "spbintegers.h"
#include "spbtool.h"
#include "spbpalette.h"
#include "spbcolor.h"
#include "spbutility.h"

typedef struct {
	int x, y;
} pairInt;

pairInt newPairInt(int x, int y) {
	pairInt tmp;
	tmp.x = x; tmp.y = y;
	return tmp;
}

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

int compareInt(const void* a, const void* b) {
	int c = *((int*)a);
	int d = *((int*)b);

	return (c > d) - (c < d);
}

int comparePairInt(const void* a, const void* b) {
	pairInt c = *((pairInt*)a);
	pairInt d = *((pairInt*)b);

	return (c.x > d.x) - (c.x < d.x);
}

int main() {
	enum SPBPaletteSORTTYPE sort;
	SPBColor color0;
	char color_str[5];
	unsigned char random_str[17];
	int sort_arr[11] = {8, 1, 4, 3, 6, 4, 7, 6, 7, 8, 1};
	int sort_pai[11] = {0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1};
	pairInt sort_final[15];
	int sort_arr0[7] = {1, 3, 6, 7, 8, 9, 10};
	int sort_arr1[5] = {0, 2, 4, 5, 11};
	int sort_res[12];
	int j;

	/* SPB Testing */

	spb_orderedMerge(sort_arr0, sort_arr1, sort_res, 7, 5, sizeof(int), compareInt);
	{
		int i;
		for(i = 0; i < sizeof(sort_res) / sizeof(int); ++i) {
			printf("%d ", sort_res[i]);
		}
		putchar('\n');
	}

	{
		int i;
		for(i = 0; i < sizeof(sort_final) / sizeof(pairInt); ++i) {
			int rand_entry = rand()%10;
			int prev_exist = 0;
			int k = 0;
			for(k = 0; k < i; ++k) {
				if(sort_final[k].x == rand_entry) {
					prev_exist++;
				}
			}
			sort_final[i] = newPairInt(rand_entry, prev_exist);
		}
		for(i = 0; i < sizeof(sort_final) / sizeof(pairInt); ++i) {
			printf("%d ", sort_final[i].x);
		}
		putchar('\n');
		for(i = 0; i < sizeof(sort_final) / sizeof(pairInt); ++i) {
			printf("%d ", sort_final[i].y);
		}
		putchar('\n');
		putchar('\n');
		spb_stableSort(
			sort_final,
			sizeof(sort_final) / sizeof(pairInt),
			sizeof(pairInt),
			comparePairInt
		);
		for(i = 0; i < sizeof(sort_final) / sizeof(pairInt); ++i) {
			printf("%d ", sort_final[i].x);
		}
		putchar('\n');
		for(i = 0; i < sizeof(sort_final) / sizeof(pairInt); ++i) {
			printf("%d ", sort_final[i].y);
		}
		putchar('\n');
	}

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

	/*printf("%ld\n", randomNumberPls());
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
	}*/

	return 0;
}