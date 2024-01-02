#include "main.h"
#include "function.h"
#include "Console.h"

CauTrucBang CTBang;
CauTrucO** CTO;
//vị trí con trỏ hiện tại
COORD CViTriConTro;
//sử dụng phím
bool BSuDungPhim = false;
//tọa độ x, y ve bang
short SToaDoX;
short SToaDoY;
// cập nhật trạng thái đang chơi game
bool BTrangThaiChoiGame = false;
bool thongKeCo();
//trang, vị trí đang chọn, tổng mục
//short STrang, SViTriChon, STongMuc;

void taoMangHaiChieuDong() {
	CTO = new CauTrucO * [CTBang.SDong];
	for (int i = 0;i < CTBang.SDong;i++) {
		CTO[i] = new CauTrucO[CTBang.SCot];
	}
}
void xoaMangHaiChieuDong() {
	for (int i = 0;i < CTBang.SDong;i++) {
		delete[] CTO[i];
	}
	delete[] CTO;
}
//hàm lưu tọa độ
void luuToaDoBang() {
	SToaDoX = ((ConsoleWidth / 2) - (CTBang.SDong));
	SToaDoY = (((ConsoleHeigth - 6) - CTBang.SCot) / 2) + 6;
}

void khoitao(short SDong, short SCot, short SSoBom) {
	CTBang.SDong = SDong;
	CTBang.SCot = SCot;
	CTBang.SSoBom = SSoBom;
	CTBang.SSoODaMo = 0; // số ô đã mở
	CTBang.SSoCo = 0; // số cờ đã cắm
	//ktao
	taoMangHaiChieuDong();
	TaoBomNgauNhien();	
	//lưu lại tọa độ bảng
	luuToaDoBang();
	CViTriConTro = { 0, 0 };
	BTrangThaiChoiGame = true;
	veBang();
	veTrangThaiChoiGame(1, 0, 0);
}
//thay đổi giá trị tọa độ của x và y trong ô vuông
short toaDoX(short SX) {
	return (SX * 2) + SToaDoX;
}
short toaDoY(short SY) {
	return SY + SToaDoY;
}
//hàm vẽ ô
void veO(short SX, short SY, short SKieu) {
	switch (SKieu) {
		case 0: // Rỗng thì màu xanh lá
			Tao_mau_cho_o(toaDoX(SX), toaDoY(SY), 0, 10, "  ");
			break;
		case 1:	//Xanh dương	// Từ 1 đến 8 thì ô có màu trắng
			Tao_mau_cho_o(toaDoX(SX), toaDoY(SY), 9, 15, "1 ");
			break;
		case 2: // Xanh lá
			Tao_mau_cho_o(toaDoX(SX), toaDoY(SY), 2, 15, "2 ");
			break;
		case 3: //  Đỏ
			Tao_mau_cho_o(toaDoX(SX), toaDoY(SY), 12, 15, "3 ");
			break;
		case 4: // Xanh dương đậm
			Tao_mau_cho_o(toaDoX(SX), toaDoY(SY), 1, 15, "4 ");
			break;
		case 5: // Đỏ đậm
			Tao_mau_cho_o(toaDoX(SX), toaDoY(SY), 4, 15, "5 ");
			break;
		case 6: // Cyan đậm
			Tao_mau_cho_o(toaDoX(SX), toaDoY(SY), 3, 15, "6 ");
			break;
		case 7: // Đen
			Tao_mau_cho_o(toaDoX(SX), toaDoY(SY), 0, 15, "7 ");
			break;
		case 8: // Xanh lá
			Tao_mau_cho_o(toaDoX(SX), toaDoY(SY), 13, 15, "8 ");
			break;
		case 9: // Bom nền đỏ chữ đen
			Tao_mau_cho_o(toaDoX(SX), toaDoY(SY), 0, 12, "B ");
			break;
		case 10: // Ô chẵn
			Tao_mau_cho_o(toaDoX(SX), toaDoY(SY), 0, 8, "  ");
			break;
		case 11: // Ô lẽ
			Tao_mau_cho_o(toaDoX(SX), toaDoY(SY), 0, 7, "  ");
			break;
		case 12: // Theo dõi con trỏ
			Tao_mau_cho_o(toaDoX(SX), toaDoY(SY), 0, 13, " ");
			break;
		case 13: // Cấm cờ
			Tao_mau_cho_o(toaDoX(SX), toaDoY(SY), 12, 14, "P ");
			break;
		case 14: // Cấm cờ không có bom-> Cấm cờ sai
			Tao_mau_cho_o(toaDoX(SX), toaDoY(SY), 15, 6, "Px");
			break;
		case 15: // Cấm cờ có bom-> Cấm đúng
			Tao_mau_cho_o(toaDoX(SX), toaDoY(SY), 12, 14, "B ");
			break;
	}
}
void veBang() {
	for (int i = 0;i < CTBang.SDong;i++) {
		for (int j = 0;j < CTBang.SCot;j++) {
			if (CTO[i][j].BCamCo) {
				veO(j, i, 13);
			}
			else if (CTO[i][j].SBomLanCan) {// có bom
				veO(j, i, CTO[i][j].SBomLanCan);
			}
			else if (CTO[i][j].BDaMo) { // ô rõng
				veO(j, i, 0);
			}
			else if ((i + j) % 2 == 0) {
				// vẽ ô chẳn
				veO(j, i, 10);
			}
			else {
				//vẽ ô lẽ	
				veO(j, i, 11);
			}
			if (BSuDungPhim) {
				veO(CViTriConTro.X, CViTriConTro.Y, 12);
			}
		}
	}
}
// tạo bom ngẫu nhiê
void TaoBomNgauNhien() {
	short SSoBom = CTBang.SSoBom;
	short SI, SJ; //vị trí dòng và cột để tạo bom
	//ktao ngẫu nhiên bom
	srand(time(NULL));
	// kiểm tra số lượng bom vẫn còn thì thực hiện
	while (SSoBom) {
		/*Công thức ran dom trong khoảng x, y:
			rand()%(y-x+1) + x;
			Ở đây ta muốn random bom từ hàng 0->8: rand()%(8-0+1)+0=rand()%9=rand()%CTBang.SDong;
		*/
		SI = rand() % CTBang.SDong;
		SJ = rand() % CTBang.SCot;
		// kiểm tra tại ô i, j đó có bom hay không, true: có bom
		if (CTO[SI][SJ].BCoBom) {
			continue;
		}
		CTO[SI][SJ].BCoBom = true;
		--SSoBom;
	}
}
// xuất bom ngẫu nhiên
void XuatBomNgauNhien() {
	for (int i = 0;i < CTBang.SDong;i++) {
		for (int j = 0;j < CTBang.SCot;j++) {
			std::cout << CTO[i][j].BCoBom << " ";
		}
		std::cout << std::endl;
	}
}
//xử lý các phím z và x
void clickPhai(short SX, short SY) { // cắm cờ
	if (!CTO[SX][SY].BDaMo) // kiểm tra ô đó có mở chưa hay không
	{
		if (CTO[SX][SY].BCamCo) { // ô đó chưa mở-> cho phép đánh dấu or hủy dấu đánh cờ
			CTO[SX][SY].BCamCo = false;
			CTBang.SSoCo--;
		}
		else {
			CTO[SX][SY].BCamCo = true;
			CTBang.SSoCo++;
		}	
		AmThanh(IDR_WAVE3);
	}
	veBang();	
	deleteRow(4, 1);
	veTrangThaiChoiGame(1, 0, 0);
}
// xử lý sau khi mở ô an toàn
short demBomLanCan(short SX, short SY) {
	short SDem = 0;
	// bom lân cận 1 ô trung tâm thì có 8 ô
	for (int i = SX - 1;i <= SX + 1;i++) {
		for (int j = SY - 1;j <= SY + 1;j++) {
			//xét trường hợp vị trí k hợp lệ
			if (i < 0 || i >= CTBang.SDong || j < 0 || j >= CTBang.SCot) continue;
			//xét trường hợp có bom hay không. CÓ thì tăng đếm bom lên 1 đơn vị
			if (CTO[i][j].BCoBom) SDem++;
		}
	}
	return SDem;
}
//xử lý mở ô
void moO(short SX, short SY) {
	if (!CTO[SX][SY].BDaMo && !CTO[SX][SY].BCamCo) {
		CTO[SX][SY].BDaMo = true;// đánh dấu mở ô
		if (CTO[SX][SY].BCoBom) {
			// nếu có bom thì thua
			thua();
		}
		else {
			CTBang.SSoODaMo++;
			short SSoBomLanCan = demBomLanCan(SX, SY);
			if (SSoBomLanCan) {// có bom lân cận
				CTO[SX][SY].SBomLanCan = SSoBomLanCan;
			} 
			else { // ô rỗng
				//duyệt các ô lân cận và gọi đệ quy
				for (int i = SX - 1;i <= SX + 1;i++) {
					for (int j = SY - 1;j <= SY + 1;j++) {
						//xét trường hợp vị trí k hợp lệ
						if (i < 0 || i >= CTBang.SDong || j < 0 || j >= CTBang.SCot) continue;
						// gọi lại đệ quy
						moO(i, j);
					}
				}
			}
		}
	}
}
void clickTrai(short SX, short SY) {
	if (!CTO[SX][SY].BDaMo && !CTO[SX][SY].BCamCo) {
		// nếu ô đó chưa mở và chưa cắm cờ thì ta mở
		moO(SX, SY);
		if (BTrangThaiChoiGame) {
			veBang();
			if (thongKeCo()) {
				thang();
			}
			else {
				AmThanh(IDR_WAVE3);
			}
		}
	}
}
/*Xử lý menu
* 1.Trang menu chính
* 2.Menu chọn cấp độ
* 3.Trang chơi game
* 4.Trang thua
* 5.Trang thắng
* 6.Trang lưu game
*/

//xử lý phím
void XuLyPhim(KEY_EVENT_RECORD key) {
	if (key.bKeyDown) { // có nhấn phím
		switch (key.wVirtualKeyCode)
		{
		case VK_UP: //mũi tên lên
			//std::cout << "len" << std::endl;
			switch (STrang) {
				case 1: //Menu chính
					if (STongMuc == 4) {
						if (SViTriChon == 0) {
							SViTriChon = STongMuc - 1;
						}
						else SViTriChon -= 1;
						veMenuChinh(SViTriChon);
					}
					break;
				case 2: // Menu chọn cấp độ
					if (STongMuc == 4) {
						if (SViTriChon == 0) {
							SViTriChon = STongMuc - 1;
						}
						else SViTriChon -= 1;
						veMenuCapDo(SViTriChon);
					}
					break;
				case 3: //TRang chơi game
					if (BTrangThaiChoiGame) {
						BSuDungPhim = true;
						CViTriConTro.Y = (CViTriConTro.Y == 0 ? CTBang.SDong - 1 : CViTriConTro.Y - 1);
						veBang();
					}
					break;
				case 4: // trang thua
					veTrangThaiChoiGame(3, 3, (SViTriChon == 0 ? 1 : 0));
					break;
				case 5: // trang thắng
					veTrangThaiChoiGame(2, 2, (SViTriChon == 0 ? 1 : 0));
					break;
			}
			break;
		case VK_DOWN: // mũi tên xuống
			//std::cout << "xuong" << std::endl;
			switch (STrang) {
			case 1: //Menu chính
				if (STongMuc == 4) {
					if (SViTriChon == STongMuc - 1) {
						SViTriChon = 0;
					}
					else SViTriChon += 1;
					veMenuChinh(SViTriChon);
				}
				break;
			case 2: // Menu chọn cấp độ
				if (STongMuc == 4) {
					if (SViTriChon == STongMuc - 1) {
						SViTriChon = 0;
					}
					else SViTriChon += 1;
					veMenuCapDo(SViTriChon);
				}
				break;
			case 3: //TRang chơi game
				if (BTrangThaiChoiGame) {
					BSuDungPhim = true;
					CViTriConTro.Y = (CViTriConTro.Y == CTBang.SDong - 1 ? 0 : CViTriConTro.Y + 1);
					veBang();
				}
				break;
			case 4: // trang thua
				veTrangThaiChoiGame(3, 3, (SViTriChon == 0 ? 1 : 0));
				break;
			case 5: // trang thắng
				veTrangThaiChoiGame(2, 2, (SViTriChon == 0 ? 1 : 0));
				break;
			}
			break;
		case VK_LEFT: // mũi tên trái
			//std::cout << "trai" << std::endl;
			BSuDungPhim = true;
			CViTriConTro.X = (CViTriConTro.X == 0 ? CTBang.SCot - 1 : CViTriConTro.X - 1);
			veBang();
			break;
		case VK_RIGHT: // mũi tên phải
			//std::cout << "phải" << std::endl;
			BSuDungPhim = true;
			CViTriConTro.X = (CViTriConTro.X == CTBang.SCot - 1 ? 0 : CViTriConTro.X + 1);
			veBang();
			break;
		case VK_RETURN: // phím enter
			//std::cout << "enter" << std::endl;
			switch (STrang) {
			case 1: //Menu chính
				if (SViTriChon == 0) {
					STrang = 2;
					deleteRow(4, 5);
					veMenuCapDo(0);
				}
				else if (SViTriChon == 1) { // trang bảng điểm

				}
				else if (SViTriChon == 2) { //trang thông tin

				}
				else {
					exit(0);
				}
				break;
			case 2: // Menu chọn cấp độ
				if (SViTriChon == 0) { // mức độ dễ 9*9 và 10 bom
					STrang = 3;
					deleteRow(4, 10);
					khoitao(9, 9, 10);
				}
				else if (SViTriChon == 1) { // mức độ trung bình 16*16 và 40 bom
					STrang = 3;
					deleteRow(4, 10);
					khoitao(16, 16, 40);
				}
				else if (SViTriChon == 2) { // mức độ khó 24*24 và 90 bom
					STrang = 3;
					deleteRow(4, 10);
					khoitao(24, 24, 99);
				}
				else {
					STrang = 1; // cập nhật lại menu chính
					deleteRow(4, 10);
					veMenuChinh(0);
				}
				break;				
			case 4: // trang thua
				if (SViTriChon == 1) {
					STrang = 1;
					deleteRow(3, ConsoleHeigth - 3);
					veMenuChinh(0);
				}
				else {
					STrang = 3; // trang chơi game
					deleteRow(3, ConsoleHeigth - 3);
					khoitao(CTBang.SDong, CTBang.SCot, CTBang.SSoBom);
				}
				break;
			case 5: // trang thắng
				break;
			case 6: // trang lưu
				if (SViTriChon == 1) {
					STrang = 1; // trở về menu chính
					deleteRow(3, ConsoleHeigth - 3);
					veMenuChinh(0);
				}
				else {
					// lưu game, xử lý file
				}
				break;
			}
			break;
		case VK_ESCAPE: //phím esc
			//std::cout << "esc" << std::endl;
			switch (STrang) {
			case 1: //Menu chính
				exit(0);
				break;
			case 2: // Menu chọn cấp độ
				STrang = 1;
				deleteRow(4, 10);
				veMenuChinh(0);
				break;
			case 3: //trạng thái đang chơi mà thoát
				STrang = 6;
				veTrangThaiChoiGame(1, 1, 0);
				break;
			case 4: // trang thua
			case 5: // trang thắng
				STrang = 2;
				deleteRow(3, ConsoleHeigth - 3);
				veMenuCapDo(0);
				break;
			}
			break;
		case ClickTrai: // phím z: mở ô
			//std::cout << "z" << std::endl;
			clickTrai(CViTriConTro.Y, CViTriConTro.X);
			break;
		case ClickPhai: // phím x: cắm cờ
			//std::cout << "x" << std::endl;
			clickPhai(CViTriConTro.Y, CViTriConTro.X);
			break;
		}
	}
}
// xử lý sự kiện
void XuLySuKien() {
	while (true) {
		DWORD DWNumberOffEvents = 0; // lưu lại sự kiện hiện tại
		DWORD DWNumberOffEventsRead = 0;//Lưu lại số lượng sự kiện đã được lọc
		HANDLE HConsoleInput = GetStdHandle(STD_INPUT_HANDLE);// thiết bị đầu vào
		GetNumberOfConsoleInputEvents(HConsoleInput, &DWNumberOffEvents); //đặt sự kiện vào đầu của giao diện cho biến DWNumherOffEvents
		if (DWNumberOffEvents) {
			INPUT_RECORD* IREventBuffer = new INPUT_RECORD[DWNumberOffEvents]; // tạo con trỏ IREventBuffer
			ReadConsoleInput(HConsoleInput, IREventBuffer, DWNumberOffEvents, &DWNumberOffEventsRead);
			// chạy vòng lặp để đọc sự kiện
			for (int i = 0;i < DWNumberOffEvents;i++) {
				if (IREventBuffer[i].EventType == KEY_EVENT) { // nếu là sự kiện phím
					XuLyPhim(IREventBuffer[i].Event.KeyEvent);
				}
				/*else if (IREventBuffer[i].EventType == MOUSE_EVENT) {

				}*/
			}
		}
	}
}
//design
void veTieuDeGame() {
	short i;
	for (i = 0;i < ConsoleWidth;i++) {
		printf("%c", 45);
	}
	Tao_mau_cho_o((ConsoleWidth / 2) - 7, 1, 5, 0, "Game Do Min\n");
	setColor(7);
	for (i = 0;i < ConsoleWidth;i++) {
		printf("%c", 45);
	}
}
void veTrangThaiChoiGame(short STrangThai, short SCheDo, short SIndex) {
	// cập nhật index
	SViTriChon = SIndex;
	STongMuc = 2;
	Tao_mau_cho_o(1, 3, 15, 0, "Ban do: "); std::cout << CTBang.SDong << " * " << CTBang.SCot;
	Tao_mau_cho_o(1, 4, 15, 0, "So bom: "); std::cout << (CTBang.SSoBom - CTBang.SSoCo >=0 ? CTBang.SSoBom - CTBang.SSoCo : 0);
	// vẽ menu thắng thua
	std::string STRTextMenuChedo;
	if (SCheDo == 1) {
		STRTextMenuChedo = " LUU LAI ";
		Tao_mau_cho_o((ConsoleWidth / 2) - (STRTextMenuChedo.length() / 2), 3, 15, (SIndex == 0) ? 2 : 0, STRTextMenuChedo);
	}
	if (SCheDo == 2) {
		STRTextMenuChedo = " LUU TEN ";
		Tao_mau_cho_o((ConsoleWidth / 2) - (STRTextMenuChedo.length() / 2), 3, 15, (SIndex == 0) ? 2 : 0, STRTextMenuChedo);
	}
	if (SCheDo == 3) {
		STRTextMenuChedo = " CHOI LAI ";
		Tao_mau_cho_o((ConsoleWidth / 2) - (STRTextMenuChedo.length() / 2), 3, 15, (SIndex == 0) ? 2 : 0, STRTextMenuChedo);
	}
	if (SCheDo >= 1) {
		STRTextMenuChedo = " THOAT ";
		Tao_mau_cho_o((ConsoleWidth / 2) - (STRTextMenuChedo.length() / 2), 4, 15, (SIndex == 1) ? 2 : 0, STRTextMenuChedo);
	}
	
	// vẽ text trạng thái
	if (STrangThai == 1) { // đang chơi 
		Tao_mau_cho_o(ConsoleWidth - 22, 4, 15, 0, "Trang Thai: "); std::cout << "Dang choi";
	}
	if (STrangThai == 2) { // thắng 
		Tao_mau_cho_o(ConsoleWidth - 22, 4, 14, 0, "Trang Thai: "); std::cout << "Thang";
	}
	if (STrangThai == 3) { // thua 
		Tao_mau_cho_o(ConsoleWidth - 22, 4, 12, 0, "Trang Thai: "); std::cout << "Thua";
	}
	std::cout << std::endl;
	setColor(7);
	for (short i = 0;i < ConsoleWidth;i++) {
		printf("%c", 45);
	}
}
//thống kê số cờ
bool thongKeCo() {
	if (CTBang.SSoODaMo + CTBang.SSoBom == (CTBang.SDong * CTBang.SCot)) {
		return true;
	}
	return false;
}
// xét điều kiện thắng thua
void thang() {
	BTrangThaiChoiGame = false;
	xoaMangHaiChieuDong(); // giải phóng bộ nhớ
	STrang = 5;
	deleteRow(4, 1);
	veTrangThaiChoiGame(2, 2, 0); // cập nhật trạng thái thắng
	AmThanh(IDR_WAVE4);
}
void thua() {
	// hiện bom ẩn và kiểm tra cấm cờ đúng hay sai
	for (int i = 0;i < CTBang.SDong;i++) {
		for (int j = 0;j < CTBang.SCot;j++) {
			if (CTO[i][j].BCamCo) { // có cắm cờ
				if (CTO[i][j].BCoBom) { // có bom
					veO(j, i, 15);
				}
				else {
					veO(j, i, 14);
				}
			}
			else { // không cắm cờ
				if (CTO[i][j].BCoBom) { //có bom-> hiện bom
					veO(j, i, 9); // hiện bom ẩn
				}
			}
		}
	}
	BTrangThaiChoiGame = false;
	xoaMangHaiChieuDong(); // giải phóng bộ nhớ
	STrang = 4;
	deleteRow(4, 1);
	veTrangThaiChoiGame(3, 3, 0); // cập nhật trạng thái thua
	AmThanh(IDR_WAVE2);
}
void veMenuChinh(short SIndex) {
	// cập nhật lại vị trí đang chọn và tổng mục menu
	SViTriChon = SIndex;
	STongMuc = 4;
	// vẽ menu
	std::string STRTextMenuChinh = " GAME MOI ";
	Tao_mau_cho_o((ConsoleWidth / 2) - (STRTextMenuChinh.length() / 2), 7, 15, (SIndex == 0) ? 2 : 0, STRTextMenuChinh);
	STRTextMenuChinh = " BANG DIEM ";
	Tao_mau_cho_o((ConsoleWidth / 2) - (STRTextMenuChinh.length() / 2), 8, 15, (SIndex == 1) ? 2 : 0, STRTextMenuChinh);
	STRTextMenuChinh = " THONG TIN ";
	Tao_mau_cho_o((ConsoleWidth / 2) - (STRTextMenuChinh.length() / 2), 9, 15, (SIndex == 2) ? 2 : 0, STRTextMenuChinh);
	STRTextMenuChinh = " THOAT ";
	Tao_mau_cho_o((ConsoleWidth / 2) - (STRTextMenuChinh.length() / 2), 10, 15, (SIndex == 3) ? 2 : 0, STRTextMenuChinh);
	//cách ép kiểu cho hàm setcolor
	/*const char* STRTextMenuChinh = " GAME MOI ";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTextMenuChinh) / 2), 7, 15, (SIndex == 0) ? 2 : 0, (char*)STRTextMenuChinh);*/
}
void veMenuCapDo(short SIndex) {
	// cập nhật lại vị trí đang chọn và tổng mục menu
	SViTriChon = SIndex;
	STongMuc = 4;
	std::string STRTextMenuChinh = " CHON CAP DO ";
	Tao_mau_cho_o((ConsoleWidth / 2) - (STRTextMenuChinh.length() / 2), 4, 1, 0, STRTextMenuChinh);
	// vẽ menu
	STRTextMenuChinh = " DE (9 * 9 VA 10 BOM) ";
	Tao_mau_cho_o((ConsoleWidth / 2) - (STRTextMenuChinh.length() / 2), 7, 15, (SIndex == 0) ? 2 : 0, STRTextMenuChinh);
	STRTextMenuChinh = " TRUNG BINH (16 * 16 VA 40 BOM) ";
	Tao_mau_cho_o((ConsoleWidth / 2) - (STRTextMenuChinh.length() / 2), 8, 15, (SIndex == 1) ? 2 : 0, STRTextMenuChinh);
	STRTextMenuChinh = " KHO (24 *24 VA 99 BOM) ";
	Tao_mau_cho_o((ConsoleWidth / 2) - (STRTextMenuChinh.length() / 2), 9, 15, (SIndex == 2) ? 2 : 0, STRTextMenuChinh);
	STRTextMenuChinh = " QUAY LAI ";
	Tao_mau_cho_o((ConsoleWidth / 2) - (STRTextMenuChinh.length() / 2), 10, 15, (SIndex == 3) ? 2 : 0, STRTextMenuChinh);
}