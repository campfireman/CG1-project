/*
 * FhhEnums.h
 *
 *  Created on: 23.01.2012
 *      Author: ginkel
 */

#ifndef CGENUMS_H_
#define CGENUMS_H_

namespace Cg
{

	typedef enum EventType
	{
		CgMouseButtonPress = 0x00000001,
		CgMouseButtonRelease = 0x00000002,
		CgMouseMove = 0x00000004,
		CgMouseWheel = 0x00000008,
		CgMouseEvent = 0x0000000F,
		CgKeyPressEvent = 0x00000010,
		CgKeyReleaseEvent = 0x00000020,
		CgKeyEvent = 0x000000F0,

		WindowResizeEvent = 0x0000100,
		LoadObjFileEvent = 0x0000200,
		CgTrackballEvent = 0x0000400,
		CgColorChangeEvent = 0x0001000,
		CgButtonPressedEvent = 0x0002000,
		CgCheckboxChangedEvent = 0x0004000,
		CgSelectionChangedEvent = 0x0008000,
		CgSORChangedEvent = 0x000f000,

		// unused, may be changed to whatever

		// feel free to add whatever you like
	} EventType;

	typedef enum MouseButtons
	{
		NoButton = 0x00000000,
		LeftButton = 0x00000001,
		RightButton = 0x00000002,
		MiddleButton = 0x00000004
	} MouseButtons;

	typedef enum KeyboardModifiers
	{
		NoModifier = 0x00000000,	  //No modifier key is pressed.
		ShiftModifier = 0x02000000,	  //A Shift key on the keyboard is pressed.
		ControlModifier = 0x04000000, //A Ctrl key on the keyboard is pressed.
		AltModifier = 0x08000000,	  //An Alt key on the keyboard is pressed.
		MetaModifier = 0x10000000	  //A Meta key on the keyboard is pressed.
	} KeyboardModifiers;

	typedef enum Key
	{
		Key_Escape = 0x01000000,
		Key_Tab = 0x01000001,
		Key_Backtab = 0x01000002,
		Key_Backspace = 0x01000003,
		Key_Return = 0x01000004,
		Key_Enter = 0x01000005,
		Key_Insert = 0x01000006,
		Key_Delete = 0x01000007,
		Key_Pause = 0x01000008,
		Key_Print = 0x01000009,
		Key_SysReq = 0x0100000a,
		Key_Clear = 0x0100000b,
		Key_Home = 0x01000010,
		Key_End = 0x01000011,
		Key_Left = 0x01000012,
		Key_Up = 0x01000013,
		Key_Right = 0x01000014,
		Key_Down = 0x01000015,
		Key_PageUp = 0x01000016,
		Key_PageDown = 0x01000017,
		Key_Shift = 0x01000020,
		Key_Control = 0x01000021, //On Mac OS X, this corresponds to the Command keys.
		Key_Meta = 0x01000022,	  //On Mac OS X, this corresponds to the Control keys.
		Key_Alt = 0x01000023,
		Key_AltGr = 0x01001103,
		Key_CapsLock = 0x01000024,
		Key_NumLock = 0x01000025,
		Key_ScrollLock = 0x01000026,
		Key_F1 = 0x01000030,
		Key_F2 = 0x01000031,
		Key_F3 = 0x01000032,
		Key_F4 = 0x01000033,
		Key_F5 = 0x01000034,
		Key_F6 = 0x01000035,
		Key_F7 = 0x01000036,
		Key_F8 = 0x01000037,
		Key_F9 = 0x01000038,
		Key_F10 = 0x01000039,
		Key_F11 = 0x0100003a,
		Key_F12 = 0x0100003b,
		Key_F13 = 0x0100003c,
		Key_F14 = 0x0100003d,
		Key_F15 = 0x0100003e,
		Key_F16 = 0x0100003f,
		Key_F17 = 0x01000040,
		Key_F18 = 0x01000041,
		Key_F19 = 0x01000042,
		Key_F20 = 0x01000043,
		Key_F21 = 0x01000044,
		Key_F22 = 0x01000045,
		Key_F23 = 0x01000046,
		Key_F24 = 0x01000047,
		Key_F25 = 0x01000048,
		Key_F26 = 0x01000049,
		Key_F27 = 0x0100004a,
		Key_F28 = 0x0100004b,
		Key_F29 = 0x0100004c,
		Key_F30 = 0x0100004d,
		Key_F31 = 0x0100004e,
		Key_F32 = 0x0100004f,
		Key_F33 = 0x01000050,
		Key_F34 = 0x01000051,
		Key_F35 = 0x01000052,
		Key_Super_L = 0x01000053,
		Key_Super_R = 0x01000054,
		Key_Menu = 0x01000055,
		Key_Hyper_L = 0x01000056,
		Key_Hyper_R = 0x01000057,
		Key_Help = 0x01000058,
		Key_Direction_L = 0x01000059,
		Key_Direction_R = 0x01000060,
		Key_Space = 0x20,
		Key_Any = Key_Space,
		Key_Exclam = 0x21,
		Key_QuoteDbl = 0x22,
		Key_NumberSign = 0x23,
		Key_Dollar = 0x24,
		Key_Percent = 0x25,
		Key_Ampersand = 0x26,
		Key_Apostrophe = 0x27,
		Key_ParenLeft = 0x28,
		Key_ParenRight = 0x29,
		Key_Asterisk = 0x2a,
		Key_Plus = 0x2b,
		Key_Comma = 0x2c,
		Key_Minus = 0x2d,
		Key_Period = 0x2e,
		Key_Slash = 0x2f,
		Key_0 = 0x30,
		Key_1 = 0x31,
		Key_2 = 0x32,
		Key_3 = 0x33,
		Key_4 = 0x34,
		Key_5 = 0x35,
		Key_6 = 0x36,
		Key_7 = 0x37,
		Key_8 = 0x38,
		Key_9 = 0x39,
		Key_Colon = 0x3a,
		Key_Semicolon = 0x3b,
		Key_Less = 0x3c,
		Key_Equal = 0x3d,
		Key_Greater = 0x3e,
		Key_Question = 0x3f,
		Key_At = 0x40,
		Key_A = 0x41,
		Key_B = 0x42,
		Key_C = 0x43,
		Key_D = 0x44,
		Key_E = 0x45,
		Key_F = 0x46,
		Key_G = 0x47,
		Key_H = 0x48,
		Key_I = 0x49,
		Key_J = 0x4a,
		Key_K = 0x4b,
		Key_L = 0x4c,
		Key_M = 0x4d,
		Key_N = 0x4e,
		Key_O = 0x4f,
		Key_P = 0x50,
		Key_Q = 0x51,
		Key_R = 0x52,
		Key_S = 0x53,
		Key_T = 0x54,
		Key_U = 0x55,
		Key_V = 0x56,
		Key_W = 0x57,
		Key_X = 0x58,
		Key_Y = 0x59,
		Key_Z = 0x5a,
		Key_BracketLeft = 0x5b,
		Key_Backslash = 0x5c,
		Key_BracketRight = 0x5d,
		Key_AsciiCircum = 0x5e,
		Key_Underscore = 0x5f,
		Key_QuoteLeft = 0x60,
		Key_BraceLeft = 0x7b,
		Key_Bar = 0x7c,
		Key_BraceRight = 0x7d,
		Key_AsciiTilde = 0x7e,
		Key_nobreakspace = 0x0a0,
		Key_exclamdown = 0x0a1,
		Key_cent = 0x0a2,
		Key_sterling = 0x0a3,
		Key_currency = 0x0a4,
		Key_yen = 0x0a5,
		Key_brokenbar = 0x0a6,
		Key_section = 0x0a7,
		Key_diaeresis = 0x0a8,
		Key_copyright = 0x0a9,
		Key_ordfeminine = 0x0aa,
		Key_guillemotleft = 0x0ab,
		Key_notsign = 0x0ac,
		Key_hyphen = 0x0ad,
		Key_registered = 0x0ae,
		Key_macron = 0x0af,
		Key_degree = 0x0b0,
		Key_plusminus = 0x0b1,
		Key_twosuperior = 0x0b2,
		Key_threesuperior = 0x0b3,
		Key_acute = 0x0b4,
		Key_mu = 0x0b5,
		Key_paragraph = 0x0b6,
		Key_periodcentered = 0x0b7,
		Key_cedilla = 0x0b8,
		Key_onesuperior = 0x0b9,
		Key_masculine = 0x0ba,
		Key_guillemotright = 0x0bb,
		Key_onequarter = 0x0bc,
		Key_onehalf = 0x0bd,
		Key_threequarters = 0x0be,
		Key_questiondown = 0x0bf,
		Key_Agrave = 0x0c0,
		Key_Aacute = 0x0c1,
		Key_Acircumflex = 0x0c2,
		Key_Atilde = 0x0c3,
		Key_Adiaeresis = 0x0c4,
		Key_Aring = 0x0c5,
		Key_AE = 0x0c6,
		Key_Ccedilla = 0x0c7,
		Key_Egrave = 0x0c8,
		Key_Eacute = 0x0c9,
		Key_Ecircumflex = 0x0ca,
		Key_Ediaeresis = 0x0cb,
		Key_Igrave = 0x0cc,
		Key_Iacute = 0x0cd,
		Key_Icircumflex = 0x0ce,
		Key_Idiaeresis = 0x0cf,
		Key_ETH = 0x0d0,
		Key_Ntilde = 0x0d1,
		Key_Ograve = 0x0d2,
		Key_Oacute = 0x0d3,
		Key_Ocircumflex = 0x0d4,
		Key_Otilde = 0x0d5,
		Key_Odiaeresis = 0x0d6,
		Key_multiply = 0x0d7,
		Key_Ooblique = 0x0d8,
		Key_Ugrave = 0x0d9,
		Key_Uacute = 0x0da,
		Key_Ucircumflex = 0x0db,
		Key_Udiaeresis = 0x0dc,
		Key_Yacute = 0x0dd,
		Key_THORN = 0x0de,
		Key_ssharp = 0x0df,
		Key_division = 0x0f7,
		Key_ydiaeresis = 0x0ff,
		Key_Multi_key = 0x01001120,
		Key_Codeinput = 0x01001137,
		Key_SingleCandidate = 0x0100113c,
		Key_MultipleCandidate = 0x0100113d,
		Key_PreviousCandidate = 0x0100113e,
		Key_Mode_switch = 0x0100117e,
		Key_Kanji = 0x01001121,
		Key_Muhenkan = 0x01001122,
		Key_Henkan = 0x01001123,
		Key_Romaji = 0x01001124,
		Key_Hiragana = 0x01001125,
		Key_Katakana = 0x01001126,
		Key_Hiragana_Katakana = 0x01001127,
		Key_Zenkaku = 0x01001128,
		Key_Hankaku = 0x01001129,
		Key_Zenkaku_Hankaku = 0x0100112a,
		Key_Touroku = 0x0100112b,
		Key_Massyo = 0x0100112c,
		Key_Kana_Lock = 0x0100112d,
		Key_Kana_Shift = 0x0100112e,
		Key_Eisu_Shift = 0x0100112f,
		Key_Eisu_toggle = 0x01001130,
		Key_Hangul = 0x01001131,
		Key_Hangul_Start = 0x01001132,
		Key_Hangul_End = 0x01001133,
		Key_Hangul_Hanja = 0x01001134,
		Key_Hangul_Jamo = 0x01001135,
		Key_Hangul_Romaja = 0x01001136,
		Key_Hangul_Jeonja = 0x01001138,
		Key_Hangul_Banja = 0x01001139,
		Key_Hangul_PreHanja = 0x0100113a,
		Key_Hangul_PostHanja = 0x0100113b,
		Key_Hangul_Special = 0x0100113f,
		Key_Dead_Grave = 0x01001250,
		Key_Dead_Acute = 0x01001251,
		Key_Dead_Circumflex = 0x01001252,
		Key_Dead_Tilde = 0x01001253,
		Key_Dead_Macron = 0x01001254,
		Key_Dead_Breve = 0x01001255,
		Key_Dead_Abovedot = 0x01001256,
		Key_Dead_Diaeresis = 0x01001257,
		Key_Dead_Abovering = 0x01001258,
		Key_Dead_Doubleacute = 0x01001259,
		Key_Dead_Caron = 0x0100125a,
		Key_Dead_Cedilla = 0x0100125b,
		Key_Dead_Ogonek = 0x0100125c,
		Key_Dead_Iota = 0x0100125d,
		Key_Dead_Voiced_Sound = 0x0100125e,
		Key_Dead_Semivoiced_Sound = 0x0100125f,
		Key_Dead_Belowdot = 0x01001260,
		Key_Dead_Hook = 0x01001261,
		Key_Dead_Horn = 0x01001262,
		Key_Back = 0x01000061,
		Key_Forward = 0x01000062,
		Key_Stop = 0x01000063,
		Key_Refresh = 0x01000064,
		Key_VolumeDown = 0x01000070,
		Key_VolumeMute = 0x01000071,
		Key_VolumeUp = 0x01000072,
		Key_BassBoost = 0x01000073,
		Key_BassUp = 0x01000074,
		Key_BassDown = 0x01000075,
		Key_TrebleUp = 0x01000076,
		Key_TrebleDown = 0x01000077,
		Key_MediaPlay = 0x01000080,
		Key_MediaStop = 0x01000081,
		Key_MediaPrevious = 0x01000082,
		Key_MediaNext = 0x01000083,
		Key_MediaRecord = 0x01000084,
		Key_HomePage = 0x01000090,
		Key_Favorites = 0x01000091,
		Key_Search = 0x01000092,
		Key_Standby = 0x01000093,
		Key_OpenUrl = 0x01000094,
		Key_LaunchMail = 0x010000a0,
		Key_LaunchMedia = 0x010000a1,
		Key_Launch0 = 0x010000a2,
		Key_Launch1 = 0x010000a3,
		Key_Launch2 = 0x010000a4,
		Key_Launch3 = 0x010000a5,
		Key_Launch4 = 0x010000a6,
		Key_Launch5 = 0x010000a7,
		Key_Launch6 = 0x010000a8,
		Key_Launch7 = 0x010000a9,
		Key_Launch8 = 0x010000aa,
		Key_Launch9 = 0x010000ab,
		Key_LaunchA = 0x010000ac,
		Key_LaunchB = 0x010000ad,
		Key_LaunchC = 0x010000ae,
		Key_LaunchD = 0x010000af,
		Key_LaunchE = 0x010000b0,
		Key_LaunchF = 0x010000b1,
		Key_MediaLast = 0x0100ffff,
		Key_unknown = 0x01ffffff,
		Key_Call = 0x01100004,
		Key_Context1 = 0x01100000,
		Key_Context2 = 0x01100001,
		Key_Context3 = 0x01100002,
		Key_Context4 = 0x01100003,
		Key_Flip = 0x01100006,
		Key_Hangup = 0x01100005,
		Key_No = 0x01010002,
		Key_Select = 0x01010000,
		Key_Yes = 0x01010001,
		Key_Execute = 0x01020003,
		Key_Printer = 0x01020002,
		Key_Play = 0x01020005,
		Key_Sleep = 0x01020004,
		Key_Zoom = 0x01020006,
		Key_Cancel = 0x01020001
	} Key;

	typedef enum ObjectType
	{
		PointCloud = 0x00000001,
		Polyline = 0x00000002,
		TriangleMesh = 0x00000004,
		PolygonalMesh = 0x00000008,
		Cube = 0x00000020,
		SolidOfRevolution = 0x00000040,
		LoadedObj = 0x00000080,
		//the following are unused, feel free to change
		SomeOtherType5 = 0x000000A0,
		SomeOtherType6 = 0x00000100,
		SomeOtherType7 = 0x00000200,
	} ObjectType;

	typedef enum Color
	{
		Red,
		Green,
		Blue
	} Color;

	typedef enum ButtonType
	{
		Draw
	} ButtonType;

	typedef enum CheckboxType
	{
		FaceNormals
	} CheckboxType;

	typedef enum SelectionType
	{
		Object
	} SelectionType;
	typedef enum SOROptionType
	{
		LateralSteps,
		Iterations,
		N,
	} SOROptionType;
} // namespace Cg

#endif /* CGENUMS_H_ */
