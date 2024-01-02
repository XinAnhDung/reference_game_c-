#include "main.h"
#include "Console.h"
#include "function.h"
using namespace std;
//trang, vị trí đang chọn, tổng mục
short STrang, SViTriChon, STongMuc;


int main() {
	resizeConsole(ConsoleWidth, ConsoleHeigth);// thay đổi kích thước cmd
	SetConsoleTitle(TEXT("Game Do Min"));//đổi title cho cmd
	LoadIconA(NULL, MAKEINTRESOURCEA(IDI_MyIcon)); // đổi icon
	veTieuDeGame();

	Cursor(false);// false: ẩn đi con trỏ chuột
	//khoitao(9, 9, 10);
	veMenuChinh(0);
	//veMenuCapDo(0);
	STrang = 1;
	XuLySuKien();
	cout << endl;
	//system("pause");
	_getch();
	return 0;
}
