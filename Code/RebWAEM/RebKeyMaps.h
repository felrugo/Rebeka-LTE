#ifndef REBKEYMAPS_H
#define REBKEYMAPS_H
#include "..\Rimba\IEvent.h"

RebKeyCode VKtoRKC[] = {
	/*
	* Virtual Keys, Standard Set
	*/
RK_NI,
RK_LMOUSE,
RK_RMOUSE,
RK_NI,
RK_MMOUSE,

#if(_WIN32_WINNT >= 0x0500)
#define VK_XBUTTON1       0x05    /* NOT contiguous with L & RBUTTON */
#define VK_XBUTTON2       0x06    /* NOT contiguous with L & RBUTTON */
#endif /* _WIN32_WINNT >= 0x0500 */
RK_NI, RK_NI,

	/*
	* 0x07 : unassigned
	*/
RK_NI,

RK_BACKSPACE,
RK_TAB,

	/*
	* 0x0A - 0x0B : reserved
	*/
RK_NI, RK_NI, //11

RK_NI, //clear
RK_ENTER, //good 13

RK_NI, RK_NI,

RK_LSHIFT,
RK_LCTRL,
RK_LALT,
RK_NI, //pause
RK_NI,//capital 20

/*
#define VK_KANA           0x15
#define VK_HANGEUL        0x15  
#define VK_HANGUL         0x15
#define VK_JUNJA          0x17
#define VK_FINAL          0x18
#define VK_HANJA          0x19
#define VK_KANJI          0x19
*/
RK_NI, RK_CAPSLOCK, RK_NI, RK_NI, RK_NI, RK_NI,

RK_ESCAPE, //27

/*
#define VK_CONVERT        0x1C
#define VK_NONCONVERT     0x1D
#define VK_ACCEPT         0x1E
#define VK_MODECHANGE     0x1F
*/
RK_NI, RK_NI, RK_NI, RK_NI,


RK_SPACE,
RK_PGUP,
RK_PGDN,
RK_END,
RK_HOME,
RK_LEFT,
RK_UP,
RK_RIGHT,
RK_DOWN,
/*
#define VK_SELECT         0x29
#define VK_PRINT          0x2A
#define VK_EXECUTE        0x2B
#define VK_SNAPSHOT       0x2C
*/
RK_NI, RK_NI, RK_NI, RK_NI,

RK_INS,
RK_DEL,
RK_NI, //help



	/*
	* VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
	* 0x40 : unassigned
	* VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
	*/
RK_0, RK_1, RK_2, RK_3, RK_4, RK_5, RK_6, RK_7, RK_8, RK_9, 
RK_NI, RK_NI, RK_NI, RK_NI, RK_NI, RK_NI,
RK_NI,
RK_A, RK_B, RK_C, RK_D, RK_E, RK_F, RK_G, RK_H, RK_I, RK_J, RK_K, RK_L, RK_M, RK_N, RK_O, RK_P, RK_Q, RK_R, RK_S, RK_T, RK_U, RK_V, RK_W, RK_X, RK_Y, RK_Z,

RK_LWIN,
RK_RWIN,
RK_NI, //apps

	/*
	* 0x5E : reserved
	*/
RK_NI,

RK_NI, //sleep

RK_NUM0, RK_NUM1, RK_NUM2, RK_NUM3, RK_NUM4, RK_NUM5, RK_NUM6, RK_NUM7, RK_NUM8, RK_NUM9,
RK_NUMMUL,
RK_NUMADD,
RK_NUMDOT,
RK_NUMSUB,
RK_NI, //decimal
RK_NUMDIV,
RK_F1, RK_F2, RK_F3, RK_F4, RK_F5, RK_F6, RK_F7, RK_F8, RK_F9, RK_F10, RK_F11, RK_F12,
/*
#define VK_F13            0x7C
#define VK_F14            0x7D
#define VK_F15            0x7E
#define VK_F16            0x7F
#define VK_F17            0x80
#define VK_F18            0x81
#define VK_F19            0x82
#define VK_F20            0x83
#define VK_F21            0x84
#define VK_F22            0x85
#define VK_F23            0x86
#define VK_F24            0x87
*/
RK_NI, RK_NI, RK_NI, RK_NI, RK_NI, RK_NI, RK_NI, RK_NI, RK_NI, RK_NI, RK_NI, RK_NI,
	/*
	* 0x88 - 0x8F : unassigned
	*/
RK_NI, RK_NI, RK_NI, RK_NI, RK_NI, RK_NI, RK_NI, RK_NI,

RK_NUMLOCK,
RK_SCROLLLOCK,

//...
};


const char * RKtoReadable[] =
{
	"NI", "LMOUSE", "RMOUSE", "MMOUSE", "RUPMOUSE", "RDOWNMOUSE",
	"NUM0", "NUM1", "NUM2", "NUM3", "NUM4", "NUM5", "NUM6", "NUM7", "NUM8", "NUM9",
	"NUMDIV", "NUMMUL", "NUMSUB", "NUMADD", "NUMENTER", "NUMDOT",
	"INS", "DEL", "PGUP", "PGDN", "HOME", "END",
	"BACKSPACE", "ENTER", "SPACE", "TAB", "NUMLOCK", "CAPSLOCK", "SCROLLLOCK",
	"LSHIFT", "RSHIFT", "LCTRL", "RCTRL", "LWIN", "RWIN", "LALT", "RALT", "ESCAPE", "NI", "NI", "NI", "NI", //placeholders
	"0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
	"UP", "DOWN", "LEFT", "RIGHT", //61
	"NI", "NI", "NI",
	"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
	"F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12",
};


#endif