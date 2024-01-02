#pragma once
#include<iostream>
#include<string.h>
#include <ctime>
#include <Windows.h>
#include "resource.h"
#pragma comment(lib, "winmm.lib")
#define AmThanh(filename) (PlaySound(MAKEINTRESOURCE(filename), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC));

#define ConsoleWidth 80
#define ConsoleHeigth 35
// phím x và z
#define ClickTrai 0x5A
#define ClickPhai 0x58
struct CauTrucBang{
	short SDong = 0, SCot = 0, SSoBom = 0, SSoODaMo = 0, SSoCo = 0;// o là các ô trong bảng
};
struct CauTrucO {
	bool BCoBom = false;
	bool BDaMo = false;
	bool BCamCo = false;
	short SBomLanCan = 0;
};
//trang, vị trí đang chọn, tổng mục
extern short STrang, SViTriChon, STongMuc;
