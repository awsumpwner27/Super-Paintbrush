#ifndef SPBINTEGERS_H
#define SPBINTEGERS_H

#if defined __STDC_VERSION__ && __STDC_VERSION__ >= 199901L

#include <stdint.h>

typedef uint8_t spbuint8_t;
typedef uint16_t spbuint16_t;

#else

#include <limits.h>

#if UCHAR_MAX == 0xFFu
typedef unsigned char spbuint8_t;
#else
#error unsigned char is not an 8-bit integer!
#endif

#if USHRT_MAX == 0xFFFFu
typedef unsigned short spbuint16_t;
#else
#error unsigned short is not an 16-bit integer!
#endif

#endif

#endif