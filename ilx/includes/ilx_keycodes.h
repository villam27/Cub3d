/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ilx_keycodes.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 10:17:26 by lcrimet           #+#    #+#             */
/*   Updated: 2023/03/02 12:16:54 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ILX_KEYCODES_H
# define ILX_KEYCODES_H

# ifdef __gnu_linux__

enum
{
	A			= 97,
	S			= 115,
	D			= 100,
	F			= 102,
	H			= 104,
	G			= 103,
	Z			= 122,
	X			= 120,
	C			= 99,
	V			= 118,
	B			= 98,
	Q			= 113,
	W			= 119,
	E			= 101,
	R			= 114,
	Y			= 121,
	T			= 116,
	NUM_1		= 38,
	NUM_2		= 233,
	NUM_3		= 34,
	NUM_4		= 39,
	NUM_6		= 45,
	NUM_5		= 40,
	EQUAL		= 61,
	NUM_9		= 231,
	NUM_7		= 232,
	DEGR		= 41,
	N8			= 95,
	N0			= 224,
	DOLLAR		= 36,
	O			= 111,
	U			= 117,
	DDOT		= 65106,
	I			= 105,
	P			= 112,
	ENTER		= 65293,
	L			= 108,
	J			= 106,
	PERCENT		= 249,
	K			= 107,
	EXCL		= 33,
	COMMA		= 44,
	SLASH		= 58,
	N			= 110,
	M			= 109,
	DOT			= 59,
	TAB			= 65289,
	SPACE		= 32,
	SQUARE		= 178,
	BACK		= 65288,
	ESC			= 65307,
	F5			= 65474,
	F6			= 65475,
	F7			= 65476,
	F3			= 65472,
	F8			= 65477,
	F9			= 65478,
	F10			= 65479,
	F12			= 65481,
	DEL			= 65535,
	F4			= 65473,
	F2			= 65471,
	F1			= 65470,
	LEFT		= 65361,
	RIGHT		= 65363,
	DOWN		= 65364,
	UP			= 65362,
	LCTRL		= 65507,
	LSHIFT		= 65505,
	RSHIFT		= 65506,
	REDIR		= 60,
	LALT		= 65513,
	RALT		= 65027,
	RCTRL		= 65508,
	CPLCK		= 65510,
	LEFT_CLICK	= 1,
	RIGHT_CLICK	= 3,
	MID_CLICK	= 2,
	MID_UP		= 4,
	MID_DOWN	= 5,
};
# else

enum
{
	A			= 0,
	S			= 1,
	D			= 2,
	F			= 3,
	H			= 4,
	G			= 5,
	Z			= 6,
	X			= 7,
	C			= 8,
	V			= 9,
	B			= 11,
	Q			= 12,
	W			= 13,
	E			= 14,
	R			= 15,
	Y			= 16,
	T			= 17,
	N1			= 18,
	N2			= 19,
	N3			= 20,
	N4			= 21,
	N6			= 22,
	N5			= 23,
	EQUAL		= 24,
	N9			= 25,
	N7			= 26,
	MINUS		= 27,
	N8			= 28,
	N0			= 29,
	OPBRK		= 30,
	O			= 31,
	U			= 32,
	CLBRK		= 33,
	I			= 34,
	P			= 35,
	ENTER		= 36,
	L			= 37,
	J			= 38,
	QUOTE		= 39,
	K			= 40,
	SMCLN		= 41,
	BCK_SLASH	= 42,
	COMMA		= 43,
	SLASH		= 44,
	N			= 45,
	M			= 46,
	DOT			= 47,
	TAB			= 48,
	SPACE		= 49,
	TILDE		= 50,
	BACK		= 51,
	ESC			= 53,
	NUM_POINT	= 65,
	NUM_MULT	= 67,
	NUM_ADD		= 69,
	NUM			= 71,
	NUM_DIV		= 75,
	NUM_ENTER	= 76,
	NUM_MINUS	= 78,
	NUM_0		= 82,
	NUM_1		= 83,
	NUM_2		= 84,
	NUM_3		= 85,
	NUM_4		= 86,
	NUM_5		= 87,
	NUM_6		= 88,
	NUM_7		= 89,
	NUM_8		= 91,
	NUM_9		= 92,
	F5			= 96,
	F6			= 97,
	F7			= 98,
	F3			= 99,
	F8			= 100,
	F9			= 101,
	F10			= 109,
	F12			= 111,
	HOME		= 115,
	PG_UP		= 116,
	DEL			= 117,
	F4			= 118,
	END			= 119,
	F2			= 120,
	PG_DOWN		= 121,
	F1			= 122,
	LEFT		= 123,
	RIGHT		= 124,
	DOWN		= 125,
	UP			= 126,
	LCTRL		= 256,
	LSHIFT		= 257,
	RSHIFT		= 258,
	CMD			= 259,
	LALT		= 261,
	RALT		= 262,
	RCTRL		= 269,
	CPLCK		= 272,
	LEFT_CLICK	= 1,
	RIGHT_CLICK	= 2,
	MID_CLICK	= 3,
	MID_UP		= 4,
	MID_DOWN	= 5,
};
# endif
#endif