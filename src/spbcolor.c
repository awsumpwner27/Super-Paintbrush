#include <math.h>
#include <stdlib.h>
#include "spbutility.h"

#include "spbcolor.h"

/** Clr **/

/*
Create and initialize a new color.
*/
SPBColor spbClrNew(
	spbuint8_t red,
	spbuint8_t green,
	spbuint8_t blue
) {
	SPBColor color;

	color.r = red;
	color.g = green;
	color.b = blue;

	return color;
}

/*
Create and initialize a new color via a SNES color word.
	The SNES represents color data using 15 bits, with the most significant bit being left unused. Each color channel then has 5 bits, with red having the least significant bits, and blue having the most significant bits.
*/
SPBColor spbClrFromSNESColorWord(
	spbuint16_t snes_color
) {
	SPBColor color;

	color.r = (snes_color & 0x1F) << 3;
	color.g = ((snes_color >> 5) & 0x1F) << 3;
	color.b = ((snes_color >> 10) & 0x1F) << 3;

	return color;
}

/*
Adjust the value of an existing color in terms of 15-bit high color while preserving the information of the 24-bit true color.
	The given individual color channels must be no higher than 31, as any bits beyond the least significant 5 will be masked out.
*/
SPBColor spbClrAdjustByHighColor(
	SPBColor color,
	spbuint8_t red,
	spbuint8_t green,
	spbuint8_t blue
) {
	/*First, for each channel, all but the least significant 3 bits are zeroed out. Then the adjustments passed in are shifted into placed and OR'd with the channel.*/
	color.r = (color.r & 0x07) | ((red & 0x1F) << 3);
	color.g = (color.g & 0x07) | ((green & 0x1F) << 3);
	color.b = (color.b & 0x07) | ((blue & 0x1F) << 3);

	return color;
}


/*
Returns color data in the 16-bit format used by the SNES.
	-bbbbbgg gggrrrrr
	This is a representation of the format of the bits of the return value.
*/
spbuint16_t spbClrGetSNESColorWord(
	SPBColor color
) {
	spbuint16_t snes_color = 0;

	snes_color |= (color.r >> 3);
	snes_color |= ((color.g >> 3) << 5);
	snes_color |= ((color.b >> 3) << 10);

	return snes_color;
}

/** Clf **/

SPBColorf spbClfNew(
	float red,
	float green,
	float blue
) {
	SPBColorf colorf;

	colorf.r = red;
	colorf.g = green;
	colorf.b = blue;

	return colorf;
}

SPBColorf spbClfFromClr(
	SPBColor color
) {
	SPBColorf colorf;

	colorf.r = (float)color.r / 255.f;
	colorf.g = (float)color.g / 255.f;
	colorf.b = (float)color.b / 255.f;

	return colorf;
}

SPBColor spbClfToClr(
	SPBColorf colorf
) {
	SPBColor color;

	color.r = (spbuint8_t)floor(colorf.r * 255.f + 0.5f);
	color.g = (spbuint8_t)floor(colorf.g * 255.f + 0.5f);
	color.b = (spbuint8_t)floor(colorf.b * 255.f + 0.5f);

	return color;
}

float spbClfGetChromaticity(
	SPBColorf colorf
) {
	float min_channel = spb_min(spb_min(colorf.r, colorf.g), colorf.b);
	float max_channel = spb_max(spb_max(colorf.r, colorf.g), colorf.b);

	return max_channel - min_channel;
}

float spbClfGetHue(
	SPBColorf colorf
) {
	float hue;
	float chromaticity = spbClfGetChromaticity(colorf);
	float max_channel = spb_max(spb_max(colorf.r, colorf.g), colorf.b);

	if(chromaticity == 0.f) {
		/*Hue is undefined.*/
		hue = 0.f;
	} else
	if(max_channel == colorf.r) {
		hue =
		(1.f / 6.f) * spb_fwrap((colorf.g - colorf.b) / chromaticity, 6.f);
	} else
	if(max_channel == colorf.g) {
		hue =
		(1.f / 6.f) * (colorf.b - colorf.r) / chromaticity + 2.f;
	} else
	if(max_channel == colorf.b) {
		hue =
		(1.f / 6.f) * (colorf.r - colorf.g) / chromaticity + 4.f;
	}
	return hue;
}

float spbClfGetSaturationHSL(
	SPBColorf colorf
) {
	float chromaticity = spbClfGetChromaticity(colorf);
	float lightness = spbClfGetLightnessHSL(colorf);

	return chromaticity / (1.f - abs(2.f * lightness - 1.f));
}

float spbClfGetLightnessHSL(
	SPBColorf colorf
) {
	float min_channel = spb_min(spb_min(colorf.r, colorf.g), colorf.b);
	float max_channel = spb_max(spb_max(colorf.r, colorf.g), colorf.b);

	return (1.f / 2.f) * (min_channel + max_channel);
}