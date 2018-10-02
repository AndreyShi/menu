#pragma once
#define configUseX86           1


#define max_items 20
#define KeyUp    72    
#define KeyDown  80    
#define KeyLeft  75   
#define KeyRight 77   
#define KeyEnter 13  

//#define KeyHand  115
#define KeyDiagn 100
#define KeyRef 102
#define KeyStop  27 
#define KeyStart 115

#define _key_0  48
#define _key_1  49
#define _key_2  50
#define _key_3  51
#define _key_4  52
#define _key_5  53
#define _key_6  54
#define _key_7  55
#define _key_8  56
#define _key_9  57
#define _key_POINT 46
#define _key_C   8

#define Entermenu 1


#define txt     9999
#define title   9998
#define end     -1


enum menu_e {
	start       = 0,
	diagnostika = 1,
	debugmode   = 2,
	allpar      = 3
};



const char sDiag[][23]  = { {" Общие параметры"},
							{" Параметры осей"},
							{" Смещения координат"},
							{" Коррекция"},
							{" Измерения"},
							{" Настройки"},
							{" Режим обмена с ПК"},
							{" Режим отладки"},
							{" О программе"}};

const char sAllpar[][29] = { {" ОБЩИЕ ПАРАМЕТРЫ"},
							 {" Оси-Измерительные каналы"},
							 {" Оси-экран"},
							 {" СБРОС ПАРАМЕТРОВ"},
							 {" СБРОС СМЕЩЕНИЙ"},
							 {" СБРОС"} };
const char line[]  = { "---------------------------------------" };

const char sDebugMode[][19] = { {" РЕЖИМ ОТЛАДКИ"},
								{" Датчики"},
								{" Питание и батарея"},
								{" Время"},
								{" Входы"} };