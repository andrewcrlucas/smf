/*************************************************************************//**

  @file const.h
  @brief

******************************************************************************/

#ifndef CONST_H_
#define CONST_H_

#include <stdint.h>

/* Bit definitions */
#define BIT0 (1 << 0)
#define BIT1 (1 << 1)
#define BIT2 (1 << 2)
#define BIT3 (1 << 3)
#define BIT4 (1 << 4)
#define BIT5 (1 << 5)
#define BIT6 (1 << 6)
#define BIT7 (1 << 7)
#define BIT8 (1 << 8)
#define BIT9 (1 << 9)
#define BIT10 (1 << 10)
#define BIT11 (1 << 11)
#define BIT12 (1 << 12)
#define BIT13 (1 << 13)
#define BIT14 (1 << 14)
#define BIT15 (1 << 15)
#define BIT16 (1 << 16)
#define BIT17 (1 << 17)
#define BIT18 (1 << 18)
#define BIT19 (1 << 19)
#define BIT20 (1 << 20)
#define BIT21 (1 << 21)
#define BIT22 (1 << 22)
#define BIT23 (1 << 23)
#define BIT24 (1 << 24)
#define BIT25 (1 << 25)
#define BIT26 (1 << 26)
#define BIT27 (1 << 27)
#define BIT28 (1 << 28)
#define BIT29 (1 << 29)
#define BIT30 (1 << 30)
#define BIT31 (1 << 31)

/* Flag definitions */
#define FLAG0 (BIT0)
#define FLAG1 (BIT1)
#define FLAG2 (BIT2)
#define FLAG3 (BIT3)
#define FLAG4 (BIT4)
#define FLAG5 (BIT5)
#define FLAG6 (BIT6)
#define FLAG7 (BIT7)
#define FLAG8 (BIT8)
#define FLAG9 (BIT9)
#define FLAG10 (BIT10)
#define FLAG11 (BIT11)
#define FLAG12 (BIT12)
#define FLAG13 (BIT13)
#define FLAG14 (BIT14)
#define FLAG15 (BIT15)
#define FLAG16 (BIT16)
#define FLAG17 (BIT17)
#define FLAG18 (BIT18)
#define FLAG19 (BIT19)
#define FLAG20 (BIT20)
#define FLAG21 (BIT21)
#define FLAG22 (BIT22)
#define FLAG23 (BIT23)
#define FLAG24 (BIT24)
#define FLAG25 (BIT25)
#define FLAG26 (BIT26)
#define FLAG27 (BIT27)
#define FLAG28 (BIT28)
#define FLAG29 (BIT29)
#define FLAG30 (BIT30)
#define FLAG31 (BIT31)

/* Most and Least significant byte macros */
#define MSB(word)      (uint8_t)((((uint16_t)(word)) >> 8) & 0x00ffU)
#define LSB(word)      (uint8_t)(((uint16_t)(word)) & 0x00ffU)

/* Uppwer and lower nibble macros */
#define LOWER_NIB(byte) (uint8_t)(byte & 0x0fU)
#define UPPER_NIB(byte) (uint8_t)((byte & 0xf0U) >> 4)

/* MACRO to determine the size in bytes of an element in a struct */
#define SIZEOF(s, m) ((size_t) sizeof(((s *) 0)->m))
/* MACRO to determine the number of elements in an array */
#define NUM_ELEMENTS(x) (sizeof(x) / sizeof((x)[0]))

/* MACRO to determine the number of element in an array that is a member of a
 * struct */
#define N_ELEMENTS(s, m) (SIZEOF(s, m) / SIZEOF(s, m[0]))

/* MACRO to swap the byte ordering of a 16bit value */
#define SWAP16(x) ((((x) >> 8) & 0x00ffU) | (((x) << 8) & 0xff00U))

/* MACRO to swap the byte ordering of a 32bit value */
#define SWAP32(x)                  \
    ((((x) >> 24) & 0x000000ffu) | \
     (((x) >> 8)  & 0x0000ff00u) | \
     (((x) << 8)  & 0x00ff0000u) | \
     (((x) << 24) & 0xff000000u))

#define B8__(x)                                                       \
    (((x & 0x0000000FUL) ?  1 : 0) + ((x & 0x000000F0UL) ?   2 : 0) + \
     ((x & 0x00000F00UL) ?  4 : 0) + ((x & 0x0000F000UL) ?   8 : 0) + \
     ((x & 0x000F0000UL) ? 16 : 0) + ((x & 0x00F00000UL) ?  32 : 0) + \
     ((x & 0x0F000000UL) ? 64 : 0) + ((x & 0xF0000000UL) ? 128 : 0))

#define HEX__(n) 0x##n##LU

/* Convert a binary literal */
#define B8(d) ((uint8_t) B8__(HEX__(d)))

/* Macro to eliminate unused parameter warning */
#define UNUSED_PARAMETER(p) { (p) = (p); }

#endif /* CONST_H_ */
