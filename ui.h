#pragma once
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "conio.h"
#include "resource.h"
#include "locale.h"
#include "windows.h"

DWORD WINAPI Timer(LPVOID);
class UI {

public:
	UI();
	~UI();
	int k_c;	
	int size;
	int maxcount;
	int menucounter;
	bool EnterMenu;
	bool BackMenu;
	bool kbhit;
	HANDLE hTreadTimer;
	HANDLE hConsole;

	unsigned short cursor_pos;
	unsigned short inputnum;
	int count;
	unsigned char sym;
	unsigned char bufASCIIstr[IN_BUF_SZ];
	char passOK;
	input ResultForInputNum;

	typedef struct  menuItem
	{
		int id;
		const char *text;
		struct menuItem *up;
		struct menuItem *down;
		struct menuItem *enter;
		struct menuItem *stop;
	}  menuItem;
	menuItem *curItem, mStart,mDiag[11], mAllpar[8], mDebugMode[6],inputPass, mAbout;

/////////////// main functions of these
	int SwitchMenu();
	void update_menuStart(const int &i = 0);
	void update_menuAbout();
	void update_menuDiagn(const int &i);
	void update_menuAllpar(const int &i);
	void update_menuDebugMode(const int &i);
	void update_menuInputPass();

	void flashing_cursor(unsigned int x_, unsigned int y_);
	void DrawMenu(const menuItem *menu, const int &size);
	void initmenu();	
	void inversemenuitem();		
	void up();
	void down();
	void enter();
	void stop();
	
	void update();
	void check_pointer();
	void actions();
	void number_key();
	void command_key();
	
	int GetSizeMenu(menuItem &item);
	void gotoxy(int x, int y);
	int goto_menuDiagnostika();
	void check_pass();
	void reset_input_buf();
/////////////////////////
};