#include "menu.h"

#pragma warning(disable : 4996)

int main()
{
	setlocale(LC_ALL, "Russian");
	CMenu m;
	m.initmenu_static();
	m.curItem = &m.mStart;
	printf("to enter the menu Diagnostika, press: d ");

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
				m.menu_LEFT();
				break;
			case KeyRight:
				m.menu_RIGHT();
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
			m.menu_actions();
		}

		m.switch_stream();
	}
}
