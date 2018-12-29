#include "ui.h"
#pragma warning(disable : 4996)
UI menu;

int main(){	

	while (1) {				// main cycle

		menu.actions(); // действия не связанные с нажатием кнопок
		if (_kbhit()){ // действия по нажатию кнопки

			menu.kbhit = true;
			menu.k_c = _getch();  //считываем код нажатой кнопки
			menu.kbhit = menu.k_c;
			menu.number_key();    //обработка кнопок 
			menu.command_key();	  //обработка навигационных кнопок
			menu.update();        //отрисовка меню
		}
	}
}

DWORD WINAPI Timer(LPVOID lparam){

	UI *pMenu = static_cast<UI*>(lparam);

	while (1){
		Sleep(LIR_RTC_TICK);
		pMenu->count++;
	}
}