#pragma once
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "conio.h"
#include "constant.h"
#include "locale.h"


class CMenu {

public:
	int k_c;
	bool kbhit;
	int size;
	int maxcount;
	int menucounter;
	int menu;
	bool updown;
	bool EnterMenu;
	bool BackMenu;

	typedef struct  menuItem
	{
		int id;
		const char *text;
		struct menuItem *up;
		struct menuItem *down;
		struct menuItem *enter;
		struct menuItem *stop;
	}  menuItem;

	menuItem *curItem, mStart,mDiag[11], mAllpar[8], mDebugMode[4];

	void Createmenu(const char items[][23],menuItem &menu,int title1=0);
	void CreatemenuDiag_static();
	void InsertItem_static(const char *item, menuItem &menu, int insert);
	int Createitem(const char *item, menuItem &menu,int count, int id = 0);
	void update_menu(menuItem & menu_p,int x = 0);


	void initmenu_static();		
	void inversemenuitem();
	
	
	void menu_UP();
	void menu_DOWN();
	void menu_ENTER();
	void menu_STOP();
	
	void updatemenu();
	void updatemenu_simple();
	void detectmenu();
	void switchmenu(int menuold);
	void SetMenu(menuItem &item, int menu, int offset_maxcounter, int counter);
	int GetSizeMenu(menuItem &item);


	void gotoxy(int x, int y);
	int goto_menuDiagnostika();

};