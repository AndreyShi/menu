#include "ui.h"
#pragma warning(disable : 4996)
UI menu;

int main(){	

	while (1) {				// main cycle

		menu.actions(); // �������� �� ��������� � �������� ������
		if (_kbhit()){ // �������� �� ������� ������

			menu.kbhit = true;
			menu.k_c = _getch();  //��������� ��� ������� ������
			menu.kbhit = menu.k_c;
			menu.number_key();    //��������� ������ 
			menu.command_key();	  //��������� ������������� ������
			menu.update();        //��������� ����
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