#pragma once
#include <tchar.h>
#define NUMLINES (int)((sizeof sysmetrics / sizeof sysmetrics[0]))
struct {
	int iIndex;
	LPCWSTR szLabel;
	LPCWSTR szDesc;
} sysmetrics[] = {
	SM_CXSCREEN, _T("SM_CXSCREEN"), _T("Screen width in pixels"),
	SM_CYSCREEN, _T("SM_CYSCREEN"), _T("Screen height in pixels"),
	SM_CXVSCROLL, _T("SM_CXVSCROLL"), _T("Vertical scroll arrow width"),
	SM_CYHSCROLL, _T("SM_CYHSCROLL"), _T("Horizontal scroll arrow height"),
	SM_CYCAPTION, _T("SM_CYCAPTION"), _T("Caption bar height"),
	SM_CXBORDER, _T("SM_CXBORDER"), _T("Window border width"),
	SM_CYBORDER, _T("SM_CYBORDER"), _T("Window border height"),
	SM_CXDLGFRAME, _T("SM_CXDLGFRAME"), _T("Dialog window frame width"),
	SM_CYDLGFRAME, _T("SM_CYDLGFRAME"), _T("Dialog window frame height"),
	SM_CYVTHUMB, _T("SM_CYVTHUMB"), _T("Vertical scroll thumb height"),
	SM_CXHTHUMB, _T("SM_CXHTHUMB"), _T("Horizontal scroll thumb width"),
	SM_CXICON, _T("SM_CXICON"), _T("Icon width"),
	SM_CYICON, _T("SM_CYICON"), _T("Icon height"),
	SM_CXCURSOR, _T("SM_CXCURSOR"), _T("Cursor width"),
	SM_CYCURSOR, _T("SM_CYCURSOR"), _T("Cursor height"),
	SM_CYMENU, _T("SM_CYMENU"), _T("Menu bar height"),
	SM_CXFULLSCREEN, _T("SM_CXFULLSCREEN"), _T("Full screen client area width"),
	SM_CYFULLSCREEN, _T("SM_CYFULLSCREEN"), _T("Full screen client area height"),
	SM_CYKANJIWINDOW, _T("SM_CYKANJIWINDOW"), _T("Kanji window height"),
	SM_MOUSEPRESENT, _T("SM_MOUSEPRESENT"), _T("Mouse present flag"),
	SM_CYVSCROLL, _T("SM_CYVSCROLL"), _T("Vertical scroll arrow width"),
	SM_CXHSCROLL, _T("SM_CXHSCROLL"), _T("Horizontal scroll arrow width"),
	SM_DEBUG, _T("SM_DEBUG"), _T("Debug version flag"),
	SM_SWAPBUTTON, _T("SM_SWAPBUTTON"), _T("Mouse buttons swapped flag"),
	SM_RESERVED1, _T("SM_RESERVED1"), _T("Reserved"),
	SM_RESERVED2, _T("SM_RESERVED2"), _T("Reserved"),
	SM_RESERVED3, _T("SM_RESERVED3"), _T("Reserved"),
	SM_RESERVED4, _T("SM_RESERVED4"), _T("Reserved"),
	SM_CXMIN, _T("SM_CXMIN"), _T("Minimum window width"),
	SM_CYMIN, _T("SM_CYMIN"), _T("Minimum window height"),
	SM_CXSIZE, _T("SM_CXSIZE"), _T("Minimize/Maximize icon width"),
	SM_CYSIZE, _T("SM_CYSIZE"), _T("Minimize/Maximize icon height"),
	SM_CXFRAME, _T("SM_CXFRAME"), _T("Window frame width"),
	SM_CYFRAME, _T("SM_CYFRAME"), _T("Window frame height"),
	SM_CXMINTRACK, _T("SM_CXMINTRACK"), _T("Minimum window tracking width"),
	SM_CYMINTRACK, _T("SM_CYMINTRACK"), _T("Minimum window tracking height"),
	SM_CXDOUBLECLK, _T("SM_CXDOUBLECLK"), _T("Double click x tolerance"),
	SM_CYDOUBLECLK, _T("SM_CYDOUBLECLK"), _T("Double click y tolerance"),
	SM_CXICONSPACING, _T("SM_CXICONSPACING"), _T("Horizontal icon spacing"),
	SM_CYICONSPACING, _T("SM_CYICONSPACING"), _T("Vertical icon spacing"),
	SM_MENUDROPALIGNMENT, _T("SM_MENUDROPALIGNMENT"), _T("Left or right menu drop"),
	SM_PENWINDOWS, _T("SM_PENWINDOWS"), _T("Pen extensions installed"),
	SM_DBCSENABLED, _T("SM_DBCSENABLED"), _T("Double-Byte Char Set enabled"),
	SM_CMOUSEBUTTONS, _T("SM_CMOUSEBUTTONS"), _T("Number of mouse buttons"),
	SM_SHOWSOUNDS, _T("SM_SHOWSOUNDS"), _T("Present sounds visually")
};
