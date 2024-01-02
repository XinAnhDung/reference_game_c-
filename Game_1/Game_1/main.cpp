#include<iostream>
#include "mylib.h"
#define MAX_LEN 100
using namespace std;
int sl = 4;// chiều dài rắn mặc định
int ToaDoX[MAX_LEN], ToaDoY[MAX_LEN]; // khai báo mảng chứa tọa độ
void VeTuongTop();
void VeTuongRight();
void VeTuongBottom();
void VeTuongLeft();
void VeWall();
void ktaoRan(int ToaDoX[], int ToaDoY[]);
void VeRan(int ToaDoX[], int ToaDoY[]);
void XuLyRan(int ToaDoX[], int ToaDoY[], int x, int y, int& xItem, int& yItem);
void them(int a[], int x);
void xoa(int a[], int vt);
void xoaDuLieuCu(int ToaDoX[], int ToaDoY[]);
bool SnakeChamTail(int ToaDoX[], int ToaDoY[]);
bool SnakeChamTuong(int x, int y);
void CreateItem(int& xItem, int& yItem);
bool CheckRanDeQua(int xItem, int yItem);
bool CheckQuaBiAn(int xItem, int yItem, int x, int y);

int main()
{
	bool GameOver = false;
	VeWall();
	ktaoRan(ToaDoX, ToaDoY);
	VeRan(ToaDoX, ToaDoY);
	////////////////////////
	srand(time(NULL));
	int xItem = 0, yItem = 0;
	//tạo quả
	CreateItem(xItem, yItem);
	//ktao vị trí mặc định
	int x = 50, y = 13;
	int check = 2;
	while (GameOver == false) {
		//backspace
		xoaDuLieuCu(ToaDoX, ToaDoY);
		// điều khiển
		if (_kbhit() == true) {
			char kt = _getch();
			if (kt == -32) {
				kt = _getch();
				// 72: lên; 80: đi xuống; 75: sang trái; 77: sang phải
				if (kt == 72 && check != 0) {
					check = 1;
				}
				else if (kt == 80 && check != 1) {
					check = 0;
				}
				else if (kt == 77 && check != 3) {
					check = 2;
				}
				else if (kt == 75 && check != 2) {
					check = 3;
				}
			}
		}
		//0: đi xuống; 1: đi lên; 2:qua phải; 3: qua trái
		if (check == 0) {
			//đi xuống
			y++;
		}
		else if (check == 1) {
			//đi lên
			y--;
		}
		else if (check == 2) {
			//qua phải
			x++;
		}
		else if (check == 3) {
			//qua trái
			x--;
		}
		XuLyRan(ToaDoX, ToaDoY, x, y, xItem, yItem);
		// kiểm tra rắn chạm
		GameOver = SnakeChamTail(ToaDoX, ToaDoY) || SnakeChamTuong(ToaDoX[0], ToaDoY[0]);
		Sleep(150);
	}
	_getch();
	//system("pause"); // lệnh này dùng để tắt câu lệnh hiển thị ra màn hình khi kết thúc chương trình
	return 0;
}
void VeTuongTop() {
	int x = 10, y = 1;
	while (x <= 100) {
		gotoXY(x, y);
		cout << "+";
		x++;
	}
}
void VeTuongBottom() {
	int x = 10, y = 26;
	while (x <= 100) {
		gotoXY(x, y);
		cout << "+";
		x++;
	}
}
void VeTuongLeft() {
	int x = 10, y = 1;
	while (y <= 26) {
		gotoXY(x, y);
		cout << "+";
		y++;
	}
}
void VeTuongRight() {
	int x = 100, y = 1;
	while (y <= 26) {
		gotoXY(x, y);
		cout << "+";
		y++;
	}
}
void VeWall() {
	SetColor(11);
	VeTuongTop();
	VeTuongBottom();
	VeTuongRight();
	VeTuongLeft();
	SetColor(7);
}
// ktao cho ran
void ktaoRan(int ToaDoX[], int ToaDoY[]) {
	int x = 50, y = 13;// mặc định vị trí ở giữa màn hình
	for (int i = 0;i < sl;i++) {
		ToaDoX[i] = x;
		ToaDoY[i] = y;
		x--;
	}
}
void VeRan(int ToaDoX[], int ToaDoY[]) {
	for (int i = 0;i < sl;i++) {
		gotoXY(ToaDoX[i], ToaDoY[i]);
		if (i == 0) {
			cout << "0";
		}
		else {
			cout << "o";
		}
	}
}
void xoaDuLieuCu(int ToaDoX[], int ToaDoY[]) {
	//đè lên vị trí cũ
	for (int i = 0;i < sl;i++) {
		gotoXY(ToaDoX[i], ToaDoY[i]);
		cout << " ";
	}
}
void XuLyRan(int ToaDoX[], int ToaDoY[], int x, int y, int& xItem, int& yItem) {
	// b1: thêm tọa độ mới vào đầu mảng/ mặc định sau mỗi lần lặp rắn đều dài thêm 1 đơn vị
	them(ToaDoX, x);
	them(ToaDoY, y);
	// nếu quả bị ăn thì cho đuôi dài ra, còn k thì thực hiện xóa như bt
	if (CheckQuaBiAn(xItem, yItem, ToaDoX[0], ToaDoY[0]) == false) {
		// b2: xóa tọa độ cuối mảng
		xoa(ToaDoX, sl - 1);
		xoa(ToaDoY, sl - 1);
	}
	else {
		CreateItem(xItem, yItem);
	}
	//b3: vẽ rắn
	VeRan(ToaDoX, ToaDoY);
}
void them(int a[], int x) {
	for (int i = sl;i > 0;i--) {
		a[i] = a[i - 1];
	}
	a[0] = x;
	sl++;
}
void xoa(int a[], int vt) {
	//đè lên vị trí cũ
	for (int i = vt;i < sl;i++) {
		a[i] = a[i + 1];
	}
	sl--;
}
//kiểm tra chạm tường của rắn
bool SnakeChamTuong(int x, int y) {
	// rắn chạm tường trên
	if (y == 1 && (x >= 10 && x <= 100)) {
		return true;
	}
	// chạm tường dưới
	else if (y == 26 && (x >= 10 && x <= 100)) {
		return true;
	}
	// chạm tường trái
	else if (x == 10 && (y >= 1 && y <= 26)) {
		return true;
	}
	// chạm tường phải
	else if (x == 100 && (y >= 1 && y <= 26)) {
		return true;
	}
	return false;
}
bool SnakeChamTail(int ToaDoX[], int ToaDoY[]) {
	for (int i = 1;i < sl;i++) {
		if (ToaDoX[0] == ToaDoX[i] && ToaDoY[0] == ToaDoY[i]) {
			return true;
		}
	}
	return false;
}
//tạo quả
void CreateItem(int& xItem, int& yItem) {
	// thực hiện kiểm tra tọa độ quả được tạo có trùng với rắn hay không, không trùng mới được tạo
	do {
		xItem = rand() % (99 - 11 + 1) + 11;
		yItem = rand() % (25 - 2 + 1) + 2;
	} while (CheckRanDeQua(xItem, yItem));
	//k trùng thì di chuyển và in ra
	//tạo màu cho quả
	int i = rand() % (15 - 1 + 1) + 1;
	SetColor(i);
	gotoXY(xItem, yItem);
	cout << "$";
	SetColor(7);
}
//kiểm tra rắn có đè lên quả hay không
bool CheckRanDeQua(int xItem, int yItem) {
	for (int i = 0;i < sl;i++) {
		if (ToaDoX[i] == xItem && ToaDoY[i] == yItem) {
			return true; // đã bị đè
		}
	}
	return false;
}
bool CheckQuaBiAn(int xItem, int yItem, int x, int y) {
	if (xItem == x && yItem == y) {
		return true; // quả đã bị ăn
	}
	return false;
}