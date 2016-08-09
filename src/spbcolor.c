#include "spbcolor.h"

/*
Create and initialize a new color.
*/
SPBColor spbClrNew(
	spbuint8_t red,
	spbuint8_t green,
	spbuint8_t blue
) {
	SPBColor color;

	color.red = red;
	color.green = green;
	color.blue = blue;

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

	color.red = (snes_color & 0x1F) << 3;
	color.green = ((snes_color >> 5) & 0x1F) << 3;
	color.blue = ((snes_color >> 10) & 0x1F) << 3;

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
	color.red = (color.red & 0x07) | ((red & 0x1F) << 3);
	color.green = (color.green & 0x07) | ((green & 0x1F) << 3);
	color.blue = (color.blue & 0x07) | ((blue & 0x1F) << 3);

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

	snes_color |= (color.red >> 3);
	snes_color |= ((color.green >> 3) << 5);
	snes_color |= ((color.blue >> 3) << 10);

	return snes_color;
}