#include<iostream>
#include<string>
#include<fstream>
#include"04_NguyenQuocHuy_N19DCAT037.h"

#define MEAN_MAX 5// số nghĩa
#define BOX_SEARCH 55// chiều rộng khung tìm kiếm
#define SHOW_MAX 14// số từ xuất tối da tù vị trí pos xuống

using namespace std;
// cấu trúc dữ liệu
struct Example {
	string info;
	Example* pNext;
};
struct Vocabulary 
{
	string word, mean[5], type;
	Example* first;
};
struct List
{
	Vocabulary data;
	List* Next;
	List* Prev;
};
struct Group {
	List* pHead;
	List* pTail;
};
// các hàm vẽ khung giao diện
void Box(int x, int y, int w, int h) {
	SetColor(11);
	for (int ix = x; ix <= x + w; ix++) {
		gotoXY(ix, y);
		cout << char(196);
		gotoXY(ix, y + h);
		cout << char(196);
	}
	for (int iy = y; iy <= y + h; iy++) {
		gotoXY(x, iy);
		cout << char(179);
		gotoXY(x + w, iy);
		cout << char(179);
	}
	gotoXY(x, y); cout << char(218);
	gotoXY(x + w, y); cout << char(191);
	gotoXY(x, y + h); cout << char(192);
	gotoXY(x + w, y + h); cout << char(217);
}
void BoxChucNang(int x, int y, int w, int h, int sl) {
	SetColor(11);
	for (int i = 0; i < sl; i++) {
		Box(x, y + (i * h), w, h);
		if (i != 0) {
			gotoXY(x, y + (i * h)); cout << char(195);
			gotoXY(x + w, y + (i * h)); cout << char(180);
		}
	}
}
void BoxName() {
	Box(5, 1, 20, 6);
	gotoXY(7, 3); cout << "Nguyen_Quoc_Huy";
	gotoXY(7, 4); cout << "N19DCAT037";
}
void Box_1() {
	/*BoxChucNang(5, 5, 20, 6, 4);
	gotoXY(7, 7); cout << "Nguyen_Quoc_Huy";
	gotoXY(7, 8); cout << "N19DCAT037";*/
	BoxName();
	BoxChucNang(5, 7, 20, 5, 4);
	gotoXY(7, 9); cout << "    Enter";
	gotoXY(7, 10); cout << "Xem nghia cua tu";
	gotoXY(7, 14); cout << "    Tab";
	gotoXY(7, 15); cout << "Them tu moi";
	gotoXY(7, 19); cout << "    Space";
	gotoXY(7, 20); cout << "Xoa toan bo tu dien";
	gotoXY(7, 24); cout << "    Esc";
	gotoXY(7, 25); cout << "Thoat chuong trinh";
}
void Box_2() {
	BoxChucNang(5, 1, 20, 6, 4);
	gotoXY(7, 3); cout << "Nguyen_Quoc_Huy";
	gotoXY(7, 4); cout << "N19DCAT037";
	gotoXY(7, 9); cout << "Backspace";
	gotoXY(7, 10); cout << "Xoa tu nay";
	gotoXY(7, 15); cout << "  Tab";
	gotoXY(7, 16); cout << "Sua tu nay";
	gotoXY(7, 21); cout << "  Esc";
	gotoXY(7, 22); cout << "Ve man hinh chinh ";
}
void Box_3() {
	BoxName();
	BoxChucNang(5, 1, 20, 24, 1);
	gotoXY(7, 15); cout << "  Enter";
	gotoXY(7, 16); cout << "Ve man hinh chinh";
}
void Box_4() {
	BoxName();
	BoxChucNang(5, 7, 20, 9, 2);
	Box(25, 7, 60, 18);
	gotoXY(11, 11); cout << "  Y";
	gotoXY(11, 12); cout << "DE XOA";
	gotoXY(11, 20); cout << "  N";
	gotoXY(11, 21); cout << "DE Huy";
}
void Title() {
	Box(25, 1, 60, 6);
	gotoXY(25, 1); cout << char(194);
	Box(30, 2, 50, 4);
	gotoXY(49, 4); cout << "04_DISTIONARY";
	//Box(25, 11, 60, 18);
}
void Corner() {
	gotoXY(5, 7); cout << char(195);
	gotoXY(25, 7); cout << char(197);
	gotoXY(25, 13); cout << char(180);
	gotoXY(25, 19); cout << char(180);
	gotoXY(25, 25); cout << char(193);
	gotoXY(85, 7); cout << char(180);
}
void Corner_Home() {
	gotoXY(5, 7); cout << char(195);
	gotoXY(25, 7); cout << char(197);
	gotoXY(25, 12); cout << char(180);
	gotoXY(25, 17); cout << char(180);
	gotoXY(25, 22); cout << char(180);
	gotoXY(25, 27); cout << char(193);
	gotoXY(85, 7); cout << char(180);
}
void Corner_1() {
	gotoXY(5, 7); cout << char(195);

	gotoXY(25, 1); cout << char(194);
	gotoXY(25, 7); cout << char(197);
	gotoXY(85, 7); cout << char(180);
}
//* global variables */
int book(string);
bool change_data = false;
string Sofware_Name = "De_4: DICTIONARY";
List* Detached(string);

void InsertLastDictionary(Group*& dis, List* p) {
	int i = book(p->data.word); // xác định từ cần thêm thuộc tập nào
	//trường hợp từ điển chưa có từ
	if (dis[i].pHead == NULL) {
		dis[i].pHead = dis[i].pTail = p;
	}// từ điển đã có từ
	else {
		dis[i].pTail->Next = p; // tạo liên kết giữa node cuối cùng vs node cần thêm
		p->Prev = dis[i].pTail;// tạo liên kết giữa node cần thêm vs node cuối
		dis[i].pTail = p;// cập nhật lại node cuối cùng là node vừa thêm vào
	}
}

void InsertfirstExample(Example*& first, string example) {
	//tao 1 node trung gian ben heap
	Example* p = new Example();// cấp phát ô nhớ
	p->info = example; // gán ví dụ vào
	p->pNext = NULL;
	// trường hợp danh sách chưa có từ nào
	if (first == NULL) {
		first = p;
	}// đã có vd
	else {
		p->pNext = first;
		first = p;
	}
}

int book(string p) {
	if (p[0] < 123 && p[0]>96) { // đoạn (96,123) là mã ASCII bảng chữ cái từ a-z 
		// => có 26 tập từ , vd chữ a=97
		return p[0] - 97;// sẽ trả về tập từ 0 là tập đầu tiên
	}
	return -1;
}

void LoadFile(Group*& dis) {
	ifstream filein;
	filein.open("words.txt", ios_base::in);
	string line;
	// mở tập tin kiểm tra tập tin có tồn tại hayy không
	if (filein.is_open()) {
		while (getline(filein, line)) {
			if (line == "") {// nếu không có kí tự thì chuyển xuống cuối vong lặp
				continue;
			}
			List* p = Detached(line);// Cấp phát Node p lưu trữ các dữ liệu đã phân tách
			InsertLastDictionary(dis, p); // thêm node p vào cuối danh sách
		}
		filein.close();// đóng file
	}
}

void WriteFile(Group* dis) {
	ofstream fileout("words.txt");
	if (fileout.is_open()) {

		for (int i = 0; i < 26; i++) {
			List* p = dis[i].pHead;
			if (p == NULL) continue;
			while (p != NULL) {
				fileout << p->data.word << "/";
				fileout << p->data.type << "/";

				for (int i = 0; i < MEAN_MAX; i++) {
					if (p->data.mean[i] == "") break;
					fileout << p->data.mean[i] << ";";
				}
				fileout << "/";

				Example* ex = p->data.first;
				while (ex != NULL) {
					fileout << ex->info << ";";
					ex = ex->pNext;
				}
				fileout << "/\n";
				p = p->Next;
			}
		}

		fileout.close();
	}
}

List* Detached(string line) {
	List* p = new List(); // cấp phát node p để lưu trữ dữ liệu
	int i = 0, pos; // i là các kí tự, pos dùng để xác định vị trí của mảng nghĩa
	string word = "";// dùng để lưu trữ từ khi được tách ra khỏi chuỗi 
	// tách từ
	while (line[i] != '/')// dùng vòng lặp while để tách kiên tục cho đến khi gặp kí tự /
	{
		word += line[i++];// gắn hết các kí tự đã tách ra vào Word.
		// sau đó tăng i lên 1 đơn vị để kiểm tra xem i có phải dấu /
	}
	i++;// bỏ qua kí tự dấu / để thực hiện tách tiếp
	p->data.word = word;// gán từ đã tách vào node p vs thuộc tính word
	//tách loại từ
	string tyle = "";// 
	while (line[i] != '/')
	{
		tyle += line[i++];
	}
	i++;
	p->data.type = tyle;
	//tách mean
	string mean = ""; pos = 0;
	while (line[i] != '/') {// tương tự như ở trên 
		mean += line[i];
		i++;
		if (line[i] == ';') {// ở đây có thể có nhiều ví dụ mỗi ví dụ cách nhau ;
			p->data.mean[pos++] = mean;
			mean = "";
			i++;
		}
	}
	i++;
	// tách ví dụ :
	p->data.first = NULL;
	string example = "";
	while (line[i] != '/') {
		example += line[i++];
		if (line[i] == ';') {
			InsertfirstExample(p->data.first, example);
			example = "";
			i++;
		}
	}
	return p;
}

void DisplayWord(List* p) { 
	system("cls");// xóa hết màn hình
	// các hàm để xử lí đồ họa
	Box_2();
	Title();
	Box(25, 7, 60, 18);
	Corner();
	gotoXY(27, 9);
	// in ra cac chi tiet cua tu
	cout << "Tu :    " << p->data.word;// xuất từ
	gotoXY(27, 11);
	cout << "Loai :  " << p->data.type;// xuất loại
	int m = 13;
	for (int i = 0; i < MEAN_MAX; i++) {// lặp cho đến khi xuất hết nghĩa

		if (p->data.mean[i] == "") break;
		gotoXY(27, m); cout << "Nghia " << i + 1 << " : ";// xuất nghĩa
		cout << p->data.mean[i] << "; ";
		m++;
	}
	int n = 19;
	int j = 0;
	Example* v = p->data.first;// cấp phát v quản lí vi dụ node p
	while (v != NULL) {
		gotoXY(27, n); cout << "Vi du " << j + 1 << " : ";
		cout << v->info;// xuất ví dụ
		v = v->pNext;// truyển đến ví dụ tiếp theo 
		n++;
		j++;
	}
}

bool Compare(string input, List* p) {
	string vol = p->data.word;
	for (int i = 0; i < input.size(); i++) {
		if (input[i] != vol[i]) {
			return false;
		}
	}
	return true;
}

List* Search(Group* dis, string input) {
	int index = book(input);
	List* p = dis[index].pHead; // có ph
	while (p != NULL) {
		if (Compare(input, p)) {
			return p;
		}
		p = p->Next;
	}
	return NULL;
}

List* PrintWordList(Group* dis, string input, int pos) {
	List* volnow = NULL; // từ đc highlight trong màn hình
	// nếu khung tìm kiếm không có giá trị in hết các từ ra
	int index = -1; // như đã biết có 26 tập từ từ 0-25;
	if (input != "") {// nếu người dùng nhập vào từ
		index = book(input);// kiểm tra xem từ đó thuộc tập từ nào
	}
	int count = 0;
	int k = 11;// vị trí trục y để làm đồ họa
	for (int i = 0; i < 26; i++) {
		if (dis[i].pHead == NULL)continue;//tập từ điển không có từ nào
		List* p = dis[i].pHead;// cấp phat node p là node dàu danh sách
		if (index != -1) {// người dùng nhập
			p = Search(dis, input); // tìm thấy thì gán từ tìm đc = p ngược lại =NULL
		}

		while (true) {

			while (pos > 0 && p != NULL) {
				pos--;// cập nhật lại số lượng từ của tập khi sử dụng các phím arrow
				p = p->Next;// gán p = từ tiếp theo
			}
			if (p == NULL) break;// kết thúc vòng lặp
			if (count == 0) {// vị trí từ đầu tiên 
				volnow = p;// 
				SetColor(4);// to màu từ đầu tiên = mã màu 4 (đỏ)
			}
			else {

				SetColor(11);//các từ phía sau màu xanh nhạt
			}


			gotoXY(26, k + 1); cout << " " << p->data.word << " ";//xuất tư
			for (int j = 0; j < BOX_SEARCH - p->data.word.size(); j++) {// lấp đầy các kí tự trông
				cout << " ";
			}
			count++; // vị trí từ kế tiếp
			p = p->Next;// chuyển p đến node tiếp theo
			k++;
			if (p == NULL) break; // kết thúc vòng lặp

		}
		if (index != -1) break; // cập nhật lại tập từ để xuất các tập tiếp theo
		if (count >= SHOW_MAX) break;// > hơn số lượng từ được xuất thì ngừng việc xuất

	}
	SetColor(11);
	return volnow;// trả về  từ đc hiển thị đầu tiên
}

List* HomeScreen(Group* dis, string input, int pos) {
	system("cls");

	Box_1();
	Title();
	Box(25, 7, 60, 20);
	Corner_Home();

	//vẽ ô tìm kiếm

	gotoXY(26, 9);
	cout << char(218);
	for (int i = 0; i < BOX_SEARCH; i++) {
		cout << char(196);
	}
	cout << char(191) << endl;
	gotoXY(26, 10);
	cout << char(179) << input;
	for (int i = 0; i < BOX_SEARCH - input.size(); i++) {
		cout << char(255);
	}
	cout << char(179);
	cout << endl;
	gotoXY(26, 11);
	cout << char(192);
	for (int i = 0; i < BOX_SEARCH; i++) {
		cout << char(196);
	}
	cout << char(217);
	// xuất danh dách từ 
	List* volnow = PrintWordList(dis, input, pos); // từ đầu tiên to đỏ
	gotoXY(27 + input.size(), 10);// dịch chuyển con trỏ chỉ vị về đầu ô tìm kiếm
	return volnow;// trả về từ đầu tiên danh sách 
}

int WordCount(Group* dis) {// dếm sô lượng các từ co trong từ điển
	int count = 0;
	for (int i = 0; i < 26; i++) {// duyệt qua tất cả tập từ
		if (dis[i].pHead == NULL)continue;
		List* p = dis[i].pHead;// node p là node đầu danh sách
		while (p != NULL) {
			count++;// cập nhật số lượng từ
			p = p->Next;// dịch chuyển đến node tiếp theo
		}
	}
	return count;// trả về số lượng từ
}

void DeleteWord(Group*& dis, List*& p) {
	system("cls");
	Box_4();
	Title();
	Corner_1();
	gotoXY(30, 14);
	cout << "Ban co chac muon xoa tu nay: " << p->data.word << "'y/n?";
	char c = _getch();
	if (c != 'y') {
		return;
	}
	int index = book(p->data.word);
	List* head = dis[index].pHead;// khai báo 1 node quản lí đầu danh sách
	List* tail = dis[index].pTail;// khai báo 1 node quản lí cuối dành sách
	// nếu node đầu và cuối bằng nhau và node dầu có data = với dât cần xóa
	if (head == tail && head->data.word == p->data.word) {
		head = tail = NULL;// cắt đứt liên kết tới node dầu đó
	}
	else if (head->data.word == p->data.word) {// chỉ có node đầu bằng
		if (head->Next == NULL) {
			head = tail = NULL;
		}
		head = head->Next;// cập nhật node dầu tiên là node tiếp theo danh sách
		head->Prev = NULL;// cắt liên kết vs node trước nó
	}
	else if (tail->data.word == p->data.word) {// node cần xóa là node cuối cùng
		tail = tail->Prev;// cập nhật node cuối là node phía trước node p
		tail->Next = NULL;// cắt đứt liên kết vs node p
	}
	else {// p nằm ở vị trí bất kì trong danh sách
		List* q = head; // tạo node q quản lí node đầu danh sách
		do
		{
			q = q->Next; // chuyển q đén node tiếp theo
			if (q->data.word == p->data.word) { // nếu node q có da ta = với p
				List* r = q->Prev; // tạo node r giữ node phía trước q, ở dây cũn là p
				List* s = q->Next;//tạo node s giữ node phía sau q, ở dây cũng là p
				q->Prev = NULL;// cắt đứt liên kết giữa q vs node phía trước
				q->Next = NULL;// cắt đứt liên kết giữ q vs node phía sau
				q = NULL;// gán q = rỗng
				delete q; // giải phóng q (thu hồi ô nhớ)
				r->Next = s; // nối lại liên kết tới node phía sau
				s->Prev = r;// nôi lại liên kết giũa node phía sau vs phía trước
				break;
			}
		} while (true);
	}
	p = NULL;
	delete p;// giải phòng p
	dis[index].pHead = head; // cập nhật lại node đầu danh sách
	dis[index].pTail = tail;// cập ngật lại node cuối dánh sách
	change_data = true;
}

void DeleteListWord(Group*& dis) {
	system("cls");
	Box_4();
	Title();
	Corner_1();
	gotoXY(30, 14);
	cout << "Ban co chac muon xoa het tu 'y/n?";
	char c = _getch();
	if (c != 'y') {
		return;
	}
	bool kt = true;
	// duyệt tất các các tập từ điển 
	for (int i = 0; i < 26; i++) {
		List* p = dis[i].pHead;// cấp phát node p quản lí đầu danh sách mỗi tập

		while (p != NULL) { // duyệt hết tập từ 
			int index = book(p->data.word);
			List* head = dis[index].pHead;
			List* tail = dis[index].pTail;
			if (head == tail && head->data.word == p->data.word) {// có 1 phần tử 
				head = tail = NULL;
			}
			else if (head->data.word == p->data.word) {// phần tử dầu = từ xóa
				if (head->Next == NULL) {//có 1 node 
					head = tail = NULL; // cắt đứt hết liên kết
				}
				head = head->Next;// gắn phần tử đầu tiên = node tiếp theo
				head->Prev = NULL;// cắt liên kết với node phía trước
			}
			else if (tail->data.word == p->data.word) {// node cuối bằng
				tail = tail->Prev;// cập nhật node cuối là node phái trước
				tail->Next = NULL;// cắt liên kết node p
			}
			p = p->Next;
			dis[index].pHead = head;// cập nhật lại node đầu danh sách
			dis[index].pTail = tail;// cập nhật lại node cuối danh sách
			change_data = true;// xác đẹnh xem dữ liệu có thay dổi hay ko
		}

	}
}

void WordCorrection(List*& p) {
	// xử lí đồ họa
	system("cls");
	Box_3();
	Title();
	Box(25, 7, 60, 18);
	Corner_1();
	// khai báo chuổi từ = rỗng
	string tu = "";
	int k = 9;
	gotoXY(27, k);
	cout << "Sua tu(" << p->data.word << "):  ";// xuất ra từ người dùng muốn sửa để đối chiếu
	getline(cin, tu);// cho người dung nhập vào từ sửa vào
	if (tu == "")return;// nếu người dùng ko nhạp gì hiểu là ko muốn sửa và kết thúc hàm
	p->data.word = tu;// cập nhật lại từ 
	// tương tự cho đến khi hết các thuộc tính của từ
	string temp = "";
	gotoXY(27, ++k);
	cout << "Sua loai tu(" << p->data.type << "):  ";
	getline(cin, temp);
	if (temp == "")return;
	p->data.type = temp;
	for (int i = 0; i < MEAN_MAX; i++) {
		temp = "";
		gotoXY(27, ++k);
		cout << "Sua Nghia " << i + 1 << "(" << p->data.mean[i] << "): ";
		getline(cin, temp);
		if (temp == "")break;
		p->data.mean[i] = temp;
		
	}
	Example* ex = p->data.first;
	int count = 0;
	if (ex == NULL) {
		// trường hợp từ không có ví dụ
		while (true) {
			gotoXY(27, k);
			cout << "Them vi du " << ++count << ": ";
			getline(cin, temp);
			if (temp == "")break;
			InsertfirstExample(p->data.first, temp);
			k++;
		};
	}
	else {
		// trường hợp đã có ít nhât 1 ví dụ trong danh sách
		while (ex != NULL) {
			gotoXY(27, k);
			cout << "Sua vi du " << ++count << "(" << ex->info << "): ";
			getline(cin, temp);
			if (temp == "")break;
			ex->info = temp;
			ex = ex->pNext;
			k++;
		}
	}
	change_data = true;
}

void InsertNewWord(Group*& dis) {
	system("cls");
	Title();
	Box_3();
	Box(25, 7, 60, 18);
	Corner_1();
	List* p = new List();// cấp phát node 
	string temp = "";
	gotoXY(27, 9);
	cout << "Nhap tu: ";
	getline(cin, temp);
	if (temp == "")return;// nếu từ cần thêm ko có kí tự nào kết thúc hàm luôn
	else {
		p->data.word = temp; // truyền dữ liệu vào p tới thuộc tính word
	}
	gotoXY(27, 10);
	cout << "Nhap loai tu: ";
	getline(cin, temp);
	p->data.type = temp;
	int k = 11;
	for (int i = 0; i < MEAN_MAX; i++) {
		temp = "";
		gotoXY(27, k);
		cout << "Nhap nghia " << i + 1 << ": ";
		getline(cin, temp);
		if (temp == "")break;
		p->data.mean[i] = temp;
		k++;
	}
	int count = 0;
	while (true) {
		temp = "";
		gotoXY(27, k);
		cout << "Nhap vi du " << ++count << ": ";
		getline(cin, temp);
		if (temp == "")break;
		InsertfirstExample(p->data.first, temp);
		k++;
	};
	InsertLastDictionary(dis, p);
	change_data = true;
}

void ControlCenter(Group*& dis) {
	DisableResizeWindow();
	
	List* volnow = NULL;
	string input = "";// Nội dung hiện tại ô input
	int keycode = 0;
	int pos = 0; // vị trí từ hiện tại(Thanh sáng)
	int wordcount = WordCount(dis);// đém số lượng từ có trong từ điển
	while (true) {
		volnow = HomeScreen(dis, input, pos); //vẽ toàn bộ giao diện 
		keycode = _getch();// dừng chương trình để nhập dữ liệu vào
		switch (keycode) {
		case 8: //backspace
			input = input.substr(0, input.size() - 1);//xóa ký tự cuói
			break;

		case 9: //Tab
			InsertNewWord(dis);
			break;
		case 32:
			DeleteListWord(dis);
			break;
		case 13: //Enter
			DisplayWord(volnow);
			int k;
			do
			{
				k = _getch();
				if (k == 8) {
					DeleteWord(dis, volnow);
					input = "", pos = 0;
					break;
				}
				if (k == 9) {
					WordCorrection(volnow);
					input = ""; pos = 0;
					break;
				}
				if (k == 27) {
					input = "";
					pos = 0;
					break;
				}
			} while (true);
			break;
		case 27: //ESC
			gotoXY(30, 27);
			if (change_data == true) {
				WriteFile(dis);
				cout << "Du lieu thay doi!!! Tien hanh ghi file..." << endl;
			}
			exit(EXIT_SUCCESS);//thoat ct
			break;
		case 224: {
			int arrow = _getch();
			if (arrow == 72) { pos--; }//up
			if (arrow == 80) { pos++; }//down
			if (arrow < 0) pos = 0;
			if (pos > wordcount - 1) pos = wordcount - 1;
			break;
		}
		default:
			if (keycode >= 97 && keycode <= 122) {
				input += char(keycode);
			}
		}
	};
}

int main() {
	/*Menu_1();
	Title();
	Corner();*/
	SetWindowSize(90, 29);
	ShowScrollbar(0);
	Group* distionary = new Group[26];
	for (int i = 0; i < 26; i++) {
		distionary[i].pHead = NULL;
		distionary[i].pTail = NULL;
	}
	LoadFile(distionary);
	ControlCenter(distionary);
	
	return 0;
}