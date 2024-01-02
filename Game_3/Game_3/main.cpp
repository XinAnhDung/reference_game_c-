#include "mylib.h"
#include<iostream>
#include<string.h>
#define sl_ground 90
using namespace std;
int h = 5;// chiều cao dino
int xDino = 25, yDino = 17;
int xDat = 5, yDat = yDino + h + 2;//tăng chiều cao đất để xử lý đất
char ground[3][sl_ground + 1];
int jump = 14; bool kt_jump = false;
string dino[6] = {
"           e-e ",
"         /(\\_/)",
".___.---' /`-' ",
" `-._.  )/,,   ",
"     //        ",
"    ^^         ",
};
string tree[5] = {
	"+++",
	"+++",
	"+++",
	" + ",
	" + ",
};
string space = "               ";
string die = "            x-x";
void play();
void draw_dino(int x, int y);
void tao_dat(int i);
void khoi_tao_mat_dat();
void draw_mat_dat();
void di_chuyen_mat_dat();
void draw_tree(int x);	
void clear_tree(int x);
bool kt_cham(int xtree, int x, int y);
void xoa(int a[], int& n, int vt);
void di_chuyen_tree(int t[], int& nt);
bool game_over(int x, int y, int t[], int nt);
void draw_wall();
int main() {
	srand(time(NULL));
	ShowCur(0);
	play();
	_getch();
}
void play() {
	int score = 0;
	//-----setup------//
	draw_wall();
	int t[100]; int nt = 0; int cnt = 0;
	draw_dino(xDino, yDino);
	khoi_tao_mat_dat();
	draw_mat_dat();
	//-----play------//
	int x = xDino, y = yDino;
	int check = 2; // 0:đi xuống, 1: đi lên, 2: đứng im
	while (true) {

		gotoXY(50, 1);
		cout << "Score: " << score++;
		if (cnt == 0) {
			t[nt++] = 92;
			cnt = rand() % (65 - 35 + 1) + 35;
		}
		//---xóa dữ liệu màn hình-----//
		if (check != 2) {
			draw_dino(x, y);
		}
		// vẽ xóa dữ liệu cũ
		//draw_tree(xTree);
		//clear_tree(xTree);
		// kiếm tra chạm
		/*if (kt_cham(xTree, x, y)) {
			gotoXY(x, y);
			cout << die;
			break;
		}
		xTree--;*/
		di_chuyen_mat_dat();
		//----điều khiển---------//
		if (_kbhit()) {
			char c = _getch();
				if (c == -32) {
					c = _getch();
					if (c == 72 && check == 2) {
						check = 1; kt_jump = true;
					}
				}
		}
		//-------di chuyển-------
		if (check == 1) {
			gotoXY(x, y + h+1);
			cout << space;
			y--;
		}
		else if (check == 0) {
			gotoXY(x, y-1);
			cout << space;
			y++;
		}
		//-----xóa thừa-----
		if (check == 2) {
			gotoXY(x, y - 1);
			cout << space;
		}
		di_chuyen_tree(t, nt);
		if (game_over(x, y, t, nt)) {
			break;
		}
		//------kiểm tra biên-----
		if (y == yDino - jump) {
			check = 0;
		}
		else if (y == yDino) {
			draw_dino(x, y);
			check = 2; kt_jump = false;
		}
		//----speed---//
		Sleep(20);
		cnt--;
	}
}
void draw_dino(int x, int y) {
	for (int i = 0;i < 6;i++) {
		gotoXY(x, y);
		cout << dino[i];
		y++;
	}
}
void tao_dat(int i) {
	int v = rand() % (15 - 1 + 1) + 1; //[1,15]
	switch (v) {
	case 1:
		ground[1][i] = '.'; ground[2][i] = ' '; break;
	case 2:
		ground[1][i] = '-'; ground[2][i] = ' '; break;
	case 3:
		ground[1][i] = '`'; ground[2][i] = ' '; break;
	case 4:
		ground[1][i] = 248; ground[2][i] = ' '; break;
	case 5:
		ground[1][i] = ' '; ground[2][i] = '.'; break;
	case 6:
		ground[1][i] = ' '; ground[2][i] = '-'; break;
	case 7:
		ground[1][i] = ' '; ground[2][i] = '`'; break;
	default:
		ground[1][i] = ' '; ground[2][i] = ' '; break;
	}
}
void khoi_tao_mat_dat() {
	for (int i = 0;i < sl_ground;i++) {
		ground[0][i] = '_';
		//lấy ra hàm tào đường
		tao_dat(i);
	}
	ground[0][sl_ground] = '\0';
	ground[1][sl_ground] = '\0';
	ground[2][sl_ground] = '\0';
}
void draw_mat_dat() {
	/*if (kt_jump == false) {
		ground[0][xDino + 4 - xDat] = '^';
		ground[0][xDino + 5 - xDat] = '^';
	}
	else {
		ground[0][xDino + 4 - xDat] = '_';
		ground[0][xDino + 5 - xDat] = '_';
	}*/
	for (int i = 0;i < 3;i++) {
		gotoXY(xDat, yDat + i);
		cout << ground[i];
	}
}
void di_chuyen_mat_dat() {
	//dời
	for (int i = 0;i < sl_ground - 1;i++) {
		ground[1][i] = ground[1][i + 1];
		ground[2][i] = ground[2][i + 1];
	}
	// chèn
	tao_dat(sl_ground - 1);
	//vẽ
	draw_mat_dat();
}
// vẽ cây
void draw_tree(int x) {
	int y = yDat - 5 - 1;
	for (int i = 0;i < 5;i++) {
		gotoXY(x, y + i);
		cout << tree[i];
	}
}
void clear_tree(int x) {
	int y = yDat - 5 - 1;
	for (int i = 0;i < 5;i++) {
		gotoXY(x + 3, y + i);
		cout << " ";
	}
}
// kiểm tra va chạm
bool kt_cham(int xtree, int x, int y) {
	int xchan_trai = x, xchan_phai = x + 15;
	int ychan = y + 5;
	//----kt cây---//
	int xtree_max = xtree + 2;
	int ytree = yDat - 5;
	int ytree_max = yDat;
	// fix vùng va chạm
	xchan_trai += 2;
	xchan_phai -= 6;
	if ((xchan_phai >= xtree && xchan_phai <= xtree_max) ||(xchan_trai >= xtree && xchan_trai <= xtree_max)) {
		if (ychan >= ytree && ychan <= ytree_max) {
			return true;
		}
	}
	return false;
}
//
void xoa(int a[], int &n, int vt) {
	for (int i = vt;i < n - 1;i++) {
		a[i] = a[i + 1];
	}
	n--;
}
void di_chuyen_tree(int t[], int &nt) {
	if (t[0] == xDat) {
		xoa(t, nt, 0);
		clear_tree(xDat);
		clear_tree(xDat-1);
		clear_tree(xDat-2);
	}
	for (int i = 0;i < nt;i++) {
		draw_tree(t[i]);
		clear_tree(t[i]);
		t[i]--;
	}
}
bool game_over(int x, int y, int t[], int nt) {
	for (int i = 0;i < nt;i++) {
		if (kt_cham(t[i], x, y)) {
			gotoXY(x, y);
			cout << die;
			return true;
		}
	}
	return false;
}
void draw_wall() {
	for (int y = 1;y <= yDat+3;y++) {
		gotoXY(xDat - 1, y); cout << "=";
		gotoXY(xDat + sl_ground + 1, y); cout << "=";
	}
	for (int x = xDat;x <= xDat + sl_ground + 1;x++) {
		gotoXY(x, 1); cout << "=";
		gotoXY(x+1, yDat+3); cout << "=";
	}
}