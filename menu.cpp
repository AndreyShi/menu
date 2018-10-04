#include "menu.h"
#include "windows.h"
#pragma warning(disable : 4996)

void CMenu::Createmenu(const char items[][23],menuItem & menu_uk, int title1)
{
	menuItem *menu = &menu_uk;

	int x = 0;
	int size = 0;
	for (; x < 16; x++)
	{
		if ((int)items[x][0] == -1) break;
		if (x == 6)
		{
			menu[x].id = 0;
			menu[x].text = "-------------------------------";
			x++;
		}
		menu[x].id = x + 1;
		menu[x].text = items[x];		
	}
	size = x;
	printf("%d", size);

	for (int x = 0; x < size; x++)
	{

		if (x == 0) { 
			menu[x].up = &menu[size-1]; x++; 
		}
		menu[x].up = &menu[x - 1];
	}

	for (int x = 0; x < size; x++)
	{
		if (x == 6) x++;
		if (x == size - 1) {
			menu[x].down = &menu[0]; break;
		}
		menu[x].down = &menu[x + 1];		
	}
}

void CMenu::CreatemenuDiag_static()
{
	int x = 0;
	int size = 0;
	for (; x < 16; x++)
	{
		if ((int)sDiag[x][0] == -1) break;
		mDiag[x].id = x + 1;
		mDiag[x].text = sDiag[x];
	}
	size = x;
	printf("%d", size);

	for (int x = 0; x < size; x++)
	{
		if (x == 0) {
			mDiag[x].up = &mDiag[size - 1]; x++;
		}
		mDiag[x].up = &mDiag[x - 1];
	}

	for (int x = 0; x < size; x++)
	{
		if (x == size - 1) {
			mDiag[x].down = &mDiag[0]; break;
		}
		mDiag[x].down = &mDiag[x + 1];
	}
}

void CMenu::InsertItem_static(const char * str, menuItem & menu_uk, int insert)
{
	menuItem *menu = &menu_uk;

	int x = 0;
	int size = 0;
	char buf[50];
	for (; x < 16; x++)
	{
		strncpy(buf, menu[x].text, 50);
		if ((int)buf[0] == -1)break;
	}
	size = x;

	for (int x = 0; x < size; x++)
	{
		menu[(size - x) + 1].text = menu[size - x].text;
		if (x == insert)
		{
			menu[insert].text = str;
		}
	}

	

}

int CMenu::Createitem(const char * item, menuItem & menu_uk,int count, int id)
{
	menuItem *menu = &menu_uk;

	int x = count;
	int size = sizeof menu_uk;

	if ((int)item[0] == -1) return 0;
	menu[x].id = count;
	menu[x].text = item;

	size = x;

	if (x == 0) {
		menu[x].up = &menu[size]; 
	}
	menu[x].up = &menu[x - 1];

	if (x == size) {
		menu[x].down = &menu[0]; return 1;
	}
	menu[x].down = &menu[x + 1];
	return 1;
}



void CMenu::initmenu_static()
{
	mStart = { txt,"mStart" ,0,0,0,0,0,0};
	inputPass = { idPass };

	mDiag[0] = { 1,sDiag[0],&mDiag[9],&mDiag[1],nullptr,nullptr,&mAllpar[1],&mStart };
	mDiag[1] = { 2,sDiag[1],&mDiag[0],&mDiag[2],nullptr,nullptr,nullptr,&mStart };
	mDiag[2] = { 3,sDiag[2],&mDiag[1],&mDiag[3],nullptr,nullptr,nullptr,&mStart };
	mDiag[3] = { 4,sDiag[3],&mDiag[2],&mDiag[4],nullptr,nullptr,nullptr,&mStart };
	mDiag[4] = { 5,sDiag[4],&mDiag[3],&mDiag[5],nullptr,nullptr,nullptr,&mStart };
	mDiag[5] = { 6,sDiag[5],&mDiag[4],&mDiag[7],nullptr,nullptr,nullptr,&mStart };
	mDiag[6] = { 0,line,0,0,0,0,0,0 };
	mDiag[7] = { 8,sDiag[6],&mDiag[5],&mDiag[8],nullptr,nullptr,nullptr,&mStart };
	mDiag[8] = { 9,sDiag[7],&mDiag[7],&mDiag[9],nullptr,nullptr,&mDebugMode[1],&mStart };
	mDiag[9] = { 10,sDiag[8],&mDiag[8],&mDiag[0],nullptr,nullptr,nullptr,&mStart };
	mDiag[10] = { end };

	mAllpar[0] = { title,sAllpar[0],0,0,0,0 };
	mAllpar[1] = { 2,sAllpar[1],&mAllpar[6],&mAllpar[2],nullptr,nullptr,0,&mDiag[0] };
	mAllpar[2] = { 3,sAllpar[2],&mAllpar[1],&mAllpar[4],nullptr,nullptr,0,&mDiag[0] };
	mAllpar[3] = { 0,line,0,0,0,0 };
	mAllpar[4] = { 5,sAllpar[3],&mAllpar[2],&mAllpar[5],nullptr,nullptr,0,&mDiag[0] };
	mAllpar[5] = { 6,sAllpar[4],&mAllpar[4],&mAllpar[6],nullptr,nullptr,0,&mDiag[0] };
	mAllpar[6] = { 7,sAllpar[5],&mAllpar[5],&mAllpar[1],nullptr,nullptr,0,&mDiag[0] };
	mAllpar[7] = { end };

	mDebugMode[0] = { title,sDebugMode[0],0,0,0,0 };
	mDebugMode[1] = { 2,sDebugMode[1],&mDebugMode[4],&mDebugMode[2],nullptr,nullptr,0,&mDiag[8] };
	mDebugMode[2] = { 3,sDebugMode[2],&mDebugMode[1],&mDebugMode[3],nullptr,nullptr,0,&mDiag[8] };
	mDebugMode[3] = { 4,sDebugMode[3],&mDebugMode[2],&mDebugMode[4],nullptr,nullptr,0,&mDiag[8] };
	mDebugMode[4] = { 5,sDebugMode[4],&mDebugMode[3],&mDebugMode[1],nullptr,nullptr,0,&mDiag[8] };
	mDebugMode[5] = { end };
}

void CMenu::updatemenu()
{
	detectmenu();
	switch (menu)
	{
	case menu_e::allpar:
		update_menu(*mAllpar);
		break;
	case menu_e::debugmode:
		update_menu(*mDebugMode);
		break;
	case menu_e::start:
		update_menu(mStart);
		break;
	case menu_e::diagnostika:
		update_menu(*mDiag);
		break;
	default:
		break;
	}
}

int CMenu::updatemenu_m()
{	
	for (int x = 0; mDiag[x].id != end; x++)
	{
		if (curItem == &mDiag[x])
		{
			update_menuDiagn(*mDiag,x);
			return 0;
		}
	}
	for (int x = 0; mAllpar[x].id != end; x++)
	{
		if (curItem == &mAllpar[x])
		{
			update_menuAllpar(*mAllpar,x);
			return 0;
		}
	}
	for (int x = 0; mDebugMode[x].id != end; x++)
	{
		if (curItem == &mDebugMode[x])
		{			
			update_menuDebugMode(*mDebugMode,x);
			return 0;
		}
	}

	if (curItem == &mStart)
	{
		update_menuStart(mStart);
		return 0;
	}

	return -1;
	
}

void CMenu::menu_actions()
{
	if (kbhit == false) return;

	check_pointer();

	if (updatemenu_m() == pointer_not_found)
	{
		//if the pointer is not processed, an error will appear
		//this code should always be at the end of this function
		system("cls");
		printf("updatemenu_m() : указатель не найден!\n");
		printf("id указателя: %d\n", curItem->id);
		Sleep(3500);
		curItem = &mStart;
		EnterMenu = true;
	}
	inversemenuitem();
	kbhit = false;

	gotoxy(0, 15);
	printf("size_menu:%d  maxcount:%d  menucounter:%d\n", size, maxcount, menucounter);
	printf("k_c : %d\n", k_c);
	printf("СТОП - esc\nПУСК - s\nДИАГНОСТИКА - d\n");
}

void CMenu::check_pointer()
{
	if (curItem->id == 0 &&
		curItem->text == 0 &&
		curItem->up == 0 &&
		curItem->down == 0 &&
		curItem->left == 0 &&
		curItem->right == 0 &&
		curItem->enter == 0 &&
		curItem->stop == 0
		)
	{
		system("cls");
		printf("check_pointer(): указатель пуст!\n");
		printf("адрес указателя: %p\n", curItem);
		Sleep(3500);
		curItem = &mStart;
		EnterMenu = true;
	}
}


void CMenu::inversemenuitem()
{
	 int  y = curItem->id;
	 if (y < max_items)
	 {
		 y = y - 1;
		 HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		 gotoxy(0, y);
		 SetConsoleTextAttribute(hConsole, (WORD)((7 << 4) | 0));
		 printf("%s", curItem->text);
		 SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
	 }
}

void CMenu::update_menu(menuItem & menu_p,int x)
{
	menuItem *menu = &menu_p;
	gotoxy(0, 0);
	if (updown == true)
	{
		for (int x = 0; x < size; x++)
		{
			printf("%s\n", menu[x].text);
		}
		updown = false;
	}
}

void CMenu::update_menuStart(menuItem & menu_p, int x)
{
	menuItem *menu = &menu_p;
	gotoxy(0, 0);
	if (EnterMenu == true || BackMenu == true) {
		size = GetSizeMenu(*curItem);
		system("cls");
		EnterMenu = BackMenu = false;
	}

	for (int x = 0; x < size; x++)
	{
		printf("%s\n", menu[x].text);
	}


}

void CMenu::update_menuDiagn(menuItem & menu_p, int x)
{
	menuItem *menu = &menu_p;
	gotoxy(0, 0);
	if (EnterMenu == true || BackMenu == true) {
		system("cls");
		updown = true;
		size = GetSizeMenu(*curItem);
		menucounter = 0;
		maxcount = size - 2;
		if (BackMenu == true)
		{
			menucounter = x - 1;
		}
		EnterMenu = BackMenu = false;
	}
	if (updown == true)
	{
		for (int x = 0; x < size; x++)
		{
			printf("%s\n", menu[x].text);
		}
		updown = false;
	}
}

void CMenu::update_menuAllpar(menuItem & menu_p, int x)
{
	menuItem *menu = &menu_p;
	gotoxy(0, 0);
	if (EnterMenu == true || BackMenu == true) {
		system("cls");
		updown = true;
		size = GetSizeMenu(*curItem);
		menucounter = 0;
		maxcount = size - 3;
		if (BackMenu == true)
		{
			menucounter = x - 1;
		}
		EnterMenu = BackMenu = false;
	}
	if (updown == true)
	{
		for (int x = 0; x < size; x++)
		{
			printf("%s\n", menu[x].text);
		}
		updown = false;
	}
}

void CMenu::update_menuDebugMode(menuItem & menu_p, int x)
{
	menuItem *menu = &menu_p;
	gotoxy(0, 0);
	if (EnterMenu == true || BackMenu == true) {
		system("cls");
		updown = true;
		size = GetSizeMenu(*curItem);
		menucounter = 0;
		maxcount = size - 2;
		if (BackMenu == true)
		{
			menucounter = x - 1;
		}
		EnterMenu = BackMenu = false;
	}
	if (updown == true)
	{
		for (int x = 0; x < size; x++)
		{
			printf("%s\n", menu[x].text);
		}
		updown = false;
	}
}

int CMenu::GetSizeMenu(menuItem & menu_p)
{
	menuItem *menu = &menu_p;
	int x = 0;
	int l = 0;
	int i = menu[0].id;
	for (; x < max_items; x++)
	{	
		//if (menu[x].id == 0) l++;
		if (menu[x].id == txt) { return 1; }
		if (menu[x].id == end) { x = (x - 1 - l) + i; return x; }
	}
	return 0;
}

void CMenu::menu_UP()
{
	if (curItem->up)
	{
		curItem = curItem->up;
		menucounter--;
		if (menucounter < 0) menucounter = maxcount;
		updown = true;
	}
}

void CMenu::menu_DOWN()
{
	if (curItem->down)
	{
		curItem = curItem->down;
		menucounter++;
		if (menucounter > maxcount) menucounter = 0;
		updown = true;
	}
}

void CMenu::menu_LEFT()
{
	if (curItem->left)
	{
		curItem = curItem->left;
		updown = false;
	}
}

void CMenu::menu_RIGHT()
{
	if (curItem->right)
	{
		curItem = curItem->right;
		updown = false;
	}
}

void CMenu::menu_ENTER()
{
	if (curItem->enter)
	{
		curItem = curItem->enter;
		EnterMenu = true;
	}
}

void CMenu::menu_STOP()
{
	if (curItem->stop)
	{
		curItem = curItem->stop;
		BackMenu = true;
	}
}

void CMenu::SetMenu(menuItem & item, int menu_enum, int offset_maxcounter, int counter)
{
	curItem = &item;
	menu = menu_enum;	
	size = GetSizeMenu(*curItem);
	maxcount = size - offset_maxcounter;
	menucounter = counter;
	EnterMenu = true;
}

void CMenu::detectmenu()
{
	int menuold = menu;

	for (int x = 0; mDiag[x].id != end; x++)
	{
		if (curItem == &mDiag[x])
		{
			menu = menu_e::diagnostika; 
			break;
		}
	}
	for (int x = 0; mAllpar[x].id != end; x++)
	{
		if (curItem == &mAllpar[x])
		{
			menu = menu_e::allpar; 
			break;
		}
	}
	for (int x = 0; mDebugMode[x].id != end; x++)
	{
		if (curItem == &mDebugMode[x])
		{
			menu = menu_e::debugmode; 
			break;
		}
	}

	if (curItem == &mStart)
	{
		menu = menu_e::start; 
	}

	if (menu != menuold)
	{
		switchmenu(menuold);
		updown = true;
	}
}

void CMenu::switchmenu(int menuold)
{
#if(configUseX86 == 1)
	system("cls");
#else
	/*insert your code for clean display on your machine*/
#endif

	switch (menu)
	{
	case menu_e::allpar:
		if (menuold == menu_e::diagnostika) SetMenu(mAllpar[1], menu_e::allpar, 3, 0);
		break;
	case menu_e::diagnostika:
		if (menuold == menu_e::start)       SetMenu(mDiag[0], menu_e::diagnostika, 2, 0);
		if (menuold == menu_e::allpar)      SetMenu(mDiag[0], menu_e::diagnostika, 2, 0);
		if (menuold == menu_e::debugmode)   SetMenu(mDiag[8], menu_e::diagnostika, 2, 7);
		break;
	case menu_e::debugmode:
		if (menuold == menu_e::diagnostika) SetMenu(mDebugMode[1], menu_e::debugmode, 2, 0);
		break;
	case menu_e::start:
		if (menuold == menu_e::diagnostika) SetMenu(mStart, menu_e::start, 1, 0);
		break;
	default:
		break;
	}
}

void CMenu::gotoxy(int x, int y)
{
#if(configUseX86 == 1)
	COORD coord = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#endif
}

int CMenu::goto_menuDiagnostika()
{
	if (curItem == &mStart)
	{
		curItem = &mDiag[0];
		EnterMenu = true;
		return 1;
	}
	return 0;
}



