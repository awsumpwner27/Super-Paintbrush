#ifndef SPBCOLOR_H
#define SPBCOLOR_H

#include "spbintegers.h"

typedef struct {
	spbuint8_t r, g, b;
} SPBColor; /* Clr */

typedef struct {
	/*Color channels. All must be on the range [0, 1].*/
	float r, g, b;
} SPBColorf; /* Clf */

/** Clr **/

/*
Create and initialize a new color.
*/
SPBColor spbClrNew(
	spbuint8_t red,
	spbuint8_t green,
	spbuint8_t blue
);

/*
Create and initialize a new color via a SNES color word.
*/
SPBColor spbClrFromSNESColorWord(
	spbuint16_t snes_color
);

/*
Adjust the value of an existing color in terms of 15-bit high color while preserving the information of the 24-bit true color.
	The given individual color channels must be no higher than 31.
*/
SPBColor spbClrAdjustByHighColor(
	SPBColor,
	spbuint8_t red,
	spbuint8_t green,
	spbuint8_t blue
);

/*
Returns color data in the 16-bit format used by the SNES.
	-bbbbbgg gggrrrrr
	This is a representation of the format of the bits of the return value.
*/
spbuint16_t spbClrGetSNESColorWord(
	SPBColor
);

/** Clf **/
/*
All values returned from "Get" functions returning floats are on the range [0, 1].
*/

SPBColorf spbClfNew(
	float red,
	float green,
	float blue
);

SPBColorf spbClfFromClr(
	SPBColor
);

SPBColorf spbClfFromHSL(
	float hue,
	float saturation,
	float lightness
);

SPBColor spbClfToClr(
	SPBColorf
);

float spbClfGetChromaticity(
	SPBColorf
);

float spbClfGetHue(
	SPBColorf
);

float spbClfGetSaturationHSL(
	SPBColorf
);

float spbClfGetLightnessHSL(
	SPBColorf
);

#endif