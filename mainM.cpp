#include "menu.h"

#pragma warning(disable : 4996)

int main()
{
	setlocale(LC_ALL, "Russian");
	CMenu m;
	m.initmenu_static();

	m.curItem = &m.mStart;
	m.gotoxy(0, 15);
	printf("äëÿ âõîäà â ìåíş íàæìèòå d ");
	while (1) // main cycle
	{
		if (_kbhit())
		{
			m.kbhit = true;
			m.k_c = _getch();
			switch (m.k_c)
			{
			case KeyUp:
				m.menu_UP();
				break;
			case KeyDown:
				m.menu_DOWN();
				break;
			case KeyLeft:
				printf("KeyLeft\n");
				break;
			case KeyRight:
				printf("KeyRight\n");
				break;
			case KeyEnter:
				m.menu_ENTER();
				break;
			case KeyStop:
				m.menu_STOP();
				break;
			case KeyDiagn:
				m.goto_menuDiagnostika();
				break;
			default:
				break;
			}
			if (m.kbhit == true)
			{
				//m.updatemenu();
				m.updatemenu_simple();
				m.inversemenuitem();
				m.kbhit = false;

				m.gotoxy(0, 15);
				printf("size_menu:%d  maxcount:%d  menucounter:%d\n",m.size,m.maxcount, m.menucounter);
				printf("k_c : %d\n", m.k_c);
				printf("ÑÒÎÏ - esc\nÏÓÑÊ - s\nÄÈÀÃÍÎÑÒÈÊÀ - d\n");
			}
		}
	}
}
