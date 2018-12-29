#include "ui.h"

#pragma warning(disable : 4996)

void UI::flashing_cursor(unsigned int x_, unsigned int y_)
{
	if (count >= 100)
	{
		count = 0;
		gotoxy(x_ + cursor_pos, y_);
		printf(" ");
	}
	else
	{
		gotoxy(x_ + cursor_pos, y_);
		if (count >= 50)
			printf(" ");
		else
			printf("#");
	}

	if (cursor_pos > 0)
	{
		gotoxy((x_ - 1) + cursor_pos, y_);
		printf("%c", sym);
	}
	gotoxy(x_ + cursor_pos + 1, y_);
	printf(" ");

	/*if (Update_input_str)
	{
		display.print_ram_local((char*)bufASCIIstr, page, x_, y_);
		Update_input_str = false;
	} */
}
void UI::DrawMenu(const menuItem * menu, const int & size)
{
	for (int x = 0; x < size; x++)
	{
		if (menu[x].text == 0)
		{
			printf("(текст не найден)\n");
		}
		else
			printf("%s\n", menu[x].text);
	}
}

void UI::initmenu()
{
	mStart = { txt,"to enter the menu Diagnostika, press: d "};
	mAbout = { txt,"О ПРОГРАММЕ\n",0,0,0,&mDiag[9] };
	inputPass = { idPass };
  //menuitem   |id|string  |   up    |  down   |   enter   |  stop  |
	mDiag[0] = { 1,sDiag[0],&mDiag[9],&mDiag[1],&inputPass,&mStart };
	mDiag[1] = { 2,sDiag[1],&mDiag[0],&mDiag[2],&inputPass,&mStart };
	mDiag[2] = { 3,sDiag[2],&mDiag[1],&mDiag[3],0,&mStart };
	mDiag[3] = { 4,sDiag[3],&mDiag[2],&mDiag[4],0,&mStart };
	mDiag[4] = { 5,sDiag[4],&mDiag[3],&mDiag[5],0,&mStart };
	mDiag[5] = { 6,sDiag[5],&mDiag[4],&mDiag[7],0,&mStart };
	mDiag[6] = { 0,line};
	mDiag[7] = { 8,sDiag[6],&mDiag[5],&mDiag[8],0,&mStart };
	mDiag[8] = { 9,sDiag[7],&mDiag[7],&mDiag[9],&mDebugMode[1],&mStart };
	mDiag[9] = { 10,sDiag[8],&mDiag[8],&mDiag[0],&mAbout,&mStart };
	mDiag[10] = { endmenu };

	mAllpar[0] = { title,sAllpar[0]};
	mAllpar[1] = { 2,sAllpar[1],&mAllpar[6],&mAllpar[2],0,&mDiag[0] };
	mAllpar[2] = { 3,sAllpar[2],&mAllpar[1],&mAllpar[4],0,&mDiag[0] };
	mAllpar[3] = { 0,line,0,0,0,0 };
	mAllpar[4] = { 5,sAllpar[3],&mAllpar[2],&mAllpar[5],0,&mDiag[0] };
	mAllpar[5] = { 6,sAllpar[4],&mAllpar[4],&mAllpar[6],0,&mDiag[0] };
	mAllpar[6] = { 7,sAllpar[5],&mAllpar[5],&mAllpar[1],0,&mDiag[0] };
	mAllpar[7] = { endmenu };

	mDebugMode[0] = { title,sDebugMode[0]};
	mDebugMode[1] = { 2,sDebugMode[1],&mDebugMode[4],&mDebugMode[2],0,&mDiag[8] };
	mDebugMode[2] = { 3,sDebugMode[2],&mDebugMode[1],&mDebugMode[3],0,&mDiag[8] };
	mDebugMode[3] = { 4,sDebugMode[3],&mDebugMode[2],&mDebugMode[4],0,&mDiag[8] };
	mDebugMode[4] = { 5,sDebugMode[4],&mDebugMode[3],&mDebugMode[1],0,&mDiag[8] };
	mDebugMode[5] = { endmenu };
}


UI::UI()
{
	setlocale(LC_ALL, "Russian");
	initmenu();
	curItem = &mStart;
	printf("to enter the menu Diagnostika, press: d ");

	hTreadTimer = CreateThread(NULL, 0, Timer, this, 0, NULL);

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	//hide system cursor
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hConsole, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hConsole, &structCursorInfo);

	inputnum = 11;

}

UI::~UI()
{
	CloseHandle(hTreadTimer);
	hTreadTimer = NULL;
}

int UI::SwitchMenu()
{	
	for (int i = 0; mDiag[i].id != endmenu; i++)
	{
		if (curItem == &mDiag[i])
		{
			update_menuDiagn(i);
			return pointer_processed;
		}
	}
	for (int i = 0; mAllpar[i].id != endmenu; i++)
	{
		if (curItem == &mAllpar[i])
		{
			update_menuAllpar(i);
			return pointer_processed;
		}
	}
	for (int i = 0; mDebugMode[i].id != endmenu; i++)
	{
		if (curItem == &mDebugMode[i])
		{			
			update_menuDebugMode(i);
			return pointer_processed;
		}
	}
	if (curItem->id == idPass)
	{
		update_menuInputPass();
		return pointer_processed;
	}

	if (curItem == &mStart)
	{
		update_menuStart();
		return pointer_processed;
	}
	if (curItem == &mAbout)
	{
		update_menuAbout();
		return pointer_processed;
	}

	return pointer_not_found;
	
}

void UI::update()
{
	if (kbhit == false) return;
	check_pointer();

	if (SwitchMenu() == pointer_not_found)
	{
		//if the pointer is not processed, an error will appear
		system("cls");
		printf("SwitchMenu() : указатель не найден!\n");
		printf("id указателя: %d\n", curItem->id);
		Sleep(3500);
		curItem = &mStart;
		EnterMenu = true;
	}
	inversemenuitem();
	kbhit = false;

	gotoxy(0, 15);
	printf("size_menu:%d  maxcount:%d  menucounter:%d\n", size, maxcount, menucounter);
	printf("key_press : %d \n", k_c);
	//printf("СТОП - esc\nПУСК - s\nДИАГНОСТИКА - d\n");
}

void UI::check_pointer()
{
	if (curItem->id == 0 &&
		curItem->text == 0 &&
		curItem->up == 0 &&
		curItem->down == 0 &&
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

void UI::actions()
{

	switch (curItem->id)
	{
	case idPass:
		if (!passOK)
		{
			flashing_cursor(15, 12);
			check_pass();
		}
		if (passOK)
		{
			if (menucounter == 0) curItem = &mAllpar[1];
			if (menucounter == 1) curItem = &mDiag[1];
			kbhit = true;
			EnterMenu = true;
			update();
		}
		break;
	default:
		break;
	}
}

void UI::number_key()
{
	switch (curItem->id)
	{
		case idPass:
			if (cursor_pos < inputnum)
			{				
				switch (k_c) {
				case _key_0:  sym = 0x30; bufASCIIstr[cursor_pos] = sym; cursor_pos++; break;
				case _key_1:  sym = 0x31; bufASCIIstr[cursor_pos] = sym; cursor_pos++; break;
				case _key_2:  sym = 0x32; bufASCIIstr[cursor_pos] = sym; cursor_pos++; break;
				case _key_3:  sym = 0x33; bufASCIIstr[cursor_pos] = sym; cursor_pos++; break;
				case _key_4:  sym = 0x34; bufASCIIstr[cursor_pos] = sym; cursor_pos++; break;
				case _key_5:  sym = 0x35; bufASCIIstr[cursor_pos] = sym; cursor_pos++; break;
				case _key_6:  sym = 0x36; bufASCIIstr[cursor_pos] = sym; cursor_pos++; break;
				case _key_7:  sym = 0x37; bufASCIIstr[cursor_pos] = sym; cursor_pos++; break;
				case _key_8:  sym = 0x38; bufASCIIstr[cursor_pos] = sym; cursor_pos++; break;
				case _key_9:  sym = 0x39; bufASCIIstr[cursor_pos] = sym; cursor_pos++; break;

				case _key_C:
					if (cursor_pos > 0)cursor_pos--; // дикрементируем курсор т е сдвигаем влево
					bufASCIIstr[cursor_pos] = 0;  // удаляем символ в буфере(Важно! в этом буфере хранится нужная нам строка)
					if (cursor_pos > 0)sym = bufASCIIstr[cursor_pos - 1]; // выводим символ перед курсором который стоит перед удаленным символом
					break;
				case _key_ENTER:
					ResultForInputNum = input::enter_;
					break;
				case _key_STOP:
					ResultForInputNum = input::cancel_;
					break;
				default:break;
				}
				if (curItem->id == idPass ) sym = '*'; // for pass
			}
			else
			{
				switch (k_c) {
				case _key_C:
					if (cursor_pos > 0)cursor_pos--; // дикрементируем курсор т е сдвигаем влево
					bufASCIIstr[cursor_pos] = 0;  // удаляем символ в буфере(Важно! в этом буфере хранится нужная нам строка)
					if (cursor_pos > 0)sym = bufASCIIstr[cursor_pos - 1]; // выводим символ перед курсором который стоит перед удаленным символом
					break;
				case _key_ENTER:
					ResultForInputNum = input::enter_;
					break;
				case _key_STOP:
					ResultForInputNum = input::cancel_;
					break;
				default:break;
				}
			}
		break;
		default:
		break;
	}
}

void UI::command_key()
{
	switch (k_c)
	{
	case KeyUp:
		up();
		break;
	case KeyDown:
		down();
		break;
	case KeyEnter:
		enter();
		break;
	case KeyStop:
		stop();
		break;
	case KeyDiagn:
		goto_menuDiagnostika();
		break;
	default:
		break;
	}
}


void UI::inversemenuitem()
{
	 int  y = curItem->id;
	 if (y < max_items)
	 {
		 y = y - 1;
		 gotoxy(0, y);
		 SetConsoleTextAttribute(hConsole, (WORD)((7 << 4) | 0));
		 printf("%s", curItem->text);
		 SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
	 }
}


void UI::update_menuStart(const int &i)
{
	gotoxy(0, 0);
	if (EnterMenu == true || BackMenu == true) {
		size = GetSizeMenu(*curItem);
		system("cls");
		EnterMenu = BackMenu = false;
		passOK = 0;
	}
	DrawMenu(&mStart, size);
}

void UI::update_menuAbout()
{
	gotoxy(0, 0);
	if (EnterMenu == true || BackMenu == true) {
		size = GetSizeMenu(*curItem);
		system("cls");
		EnterMenu = BackMenu = false;
	}
	DrawMenu(&mAbout, size);
}

void UI::update_menuDiagn(const int &i)
{
	gotoxy(0, 0);
	if (EnterMenu == true || BackMenu == true) {
		system("cls");
		size = GetSizeMenu(*curItem);
		menucounter = i;
		maxcount = size - 2;
		if (BackMenu == true)
		{
			if (i < 6)
				menucounter = i;
			else
				menucounter = i - 1;
		}
		EnterMenu = BackMenu = false;
	}

	DrawMenu(mDiag, size);
}

void UI::update_menuAllpar(const int &i)
{
	gotoxy(0, 0);
	if (EnterMenu == true || BackMenu == true) {
		system("cls");
		size = GetSizeMenu(*curItem);
		menucounter = i - 1;
		maxcount = size - 3;
		if (BackMenu == true)
		{
			menucounter = i - 1;
		}
		EnterMenu = BackMenu = false;
	}
	DrawMenu(mAllpar, size);
}

void UI::update_menuDebugMode(const int &i)
{
	gotoxy(0, 0);
	if (EnterMenu == true || BackMenu == true) {
		system("cls");
		size = GetSizeMenu(*curItem);
		menucounter = i - 1;
		maxcount = size - 2;
		if (BackMenu == true)
		{
			menucounter = i - 1;
		}
		EnterMenu = BackMenu = false;
	}
	DrawMenu(mDebugMode, size);
}

void UI::update_menuInputPass()
{
	if (!passOK)
	{
		gotoxy(0, 12);
		printf("Введите пароль:\n");
		printf("16384");
	}
}

int UI::GetSizeMenu(menuItem & menu_p)
{
	menuItem *menu = &menu_p;
	int x = 0;
	int l = 0;
	int i = menu[0].id;
	for (; x < max_items; x++)
	{	
		//if (menu[x].id == 0) l++;
		if (menu[x].id == txt) { return 1; }
		if (menu[x].id == endmenu) { x = (x - 1 - l) + i; return x; }
	}
	return 0;
}

void UI::up()
{
	if (curItem->up)
	{
		curItem = curItem->up;
		menucounter--;
		if (menucounter < 0) menucounter = maxcount;
	}
}

void UI::down()
{
	if (curItem->down)
	{
		curItem = curItem->down;
		menucounter++;
		if (menucounter > maxcount) menucounter = 0;
	}
}


void UI::enter()
{
	if (curItem->enter)
	{
		curItem = curItem->enter;
		EnterMenu = true;
	}
}

void UI::stop()
{
	if (curItem->stop)
	{
		curItem = curItem->stop;
		BackMenu = true;
	}
}





void UI::gotoxy(int x, int y)
{
#if(configUseX86 == 1)
	COORD coord = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#endif
}

int UI::goto_menuDiagnostika()
{
	if (curItem == &mStart)
	{
		curItem = &mDiag[0];
		EnterMenu = true;
		return 1;
	}
	return 0;
}

void UI::check_pass()
{
	if (cursor_pos > 4 || ResultForInputNum == enter_)
	{
		if (bufASCIIstr[0] == '1' && bufASCIIstr[1] == '6' && bufASCIIstr[2] == '3' && bufASCIIstr[3] == '8' && bufASCIIstr[4] == '4')
		{
			gotoxy(15, 12);
			printf(" Доступ открыт   ");
			if (menucounter == 0) curItem = &mAllpar[1];
			if (menucounter == 1) curItem = &mDiag[1];
			Sleep(500);
			passOK = 1;
		}
		else
		{
			gotoxy(15, 12);
			printf(" Нет доступа     ");
			//curItem = &mDiag[menucounter];
			Sleep(500);
			gotoxy(15, 12);
			printf("                              \n");
			//printf("                ");
			EnterMenu = 0;
		}
		ResultForInputNum = reset_;
		reset_input_buf();
	}
	if (ResultForInputNum == cancel_)
	{
		curItem = &mDiag[menucounter];
		ResultForInputNum = reset_;
		reset_input_buf();
		gotoxy(0, 12);
		printf("                              \n");
		printf("                ");
		EnterMenu = 0;
	}
}

void UI::reset_input_buf()
{
	cursor_pos = 0;
	memset(bufASCIIstr, 0, IN_BUF_SZ);
}



