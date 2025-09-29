#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>
#include <conio.h>
#include <fstream>
#include <iomanip>
#include <string>   // chắc chắn có std::string
#include <cstdio>   // sprintf_s
using namespace std;

// Hàm chuyển int sang string cho VS 2013
string intToString(int n) {
	char buf[20];
	sprintf_s(buf, "%d", n); // dùng sprintf_s cho VS2013
	return string(buf);
}

// Cấu trúc lưu kết quả mỗi thuật toán
struct KetQua {
	string ten_thuat_toan;
	int tong;
	double trung_binh;
	string thu_tu;
};

// Thuật toán FCFS
KetQua FCFS(vector<int> yeucau, int dau_doc) {
	int tong = 0;
	int hien_tai = dau_doc;
	string thu_tu = intToString(hien_tai);

	for (int x : yeucau) {
		tong += abs(hien_tai - x);
		hien_tai = x;
		thu_tu += " -> " + intToString(x);
	}

	double trung_binh = (double)tong / yeucau.size();
	return{ "FCFS", tong, trung_binh, thu_tu };
}

// Thuật toán SSTF
KetQua SSTF(vector<int> yeucau, int dau_doc) {
	int tong = 0;
	int hien_tai = dau_doc;
	vector<bool> da_dung(yeucau.size(), false);
	string thu_tu = intToString(hien_tai);

	for (size_t i = 0; i < yeucau.size(); i++) {
		int gan_nhat = -1;
		int kc_min = INT_MAX;
		for (size_t j = 0; j < yeucau.size(); j++) {
			if (!da_dung[j]) {
				int kc = abs(hien_tai - yeucau[j]);
				if (kc < kc_min) {
					kc_min = kc;
					gan_nhat = j;
				}
			}
		}
		da_dung[gan_nhat] = true;
		tong += abs(hien_tai - yeucau[gan_nhat]);
		hien_tai = yeucau[gan_nhat];
		thu_tu += " -> " + intToString(hien_tai);
	}

	double trung_binh = (double)tong / yeucau.size();
	return{ "SSTF", tong, trung_binh, thu_tu };
}

// Thuật toán SCAN
KetQua SCAN(vector<int> yeucau, int dau_doc, int max_cylinder) {
	int tong = 0;
	vector<int> trai, phai;
	string thu_tu = intToString(dau_doc);

	for (int x : yeucau) {
		if (x < dau_doc) trai.push_back(x);
		else phai.push_back(x);
	}

	sort(trai.begin(), trai.end());
	sort(phai.begin(), phai.end());

	for (int i = (int)trai.size() - 1; i >= 0; i--) {
		tong += abs(dau_doc - trai[i]);
		dau_doc = trai[i];
		thu_tu += " -> " + intToString(dau_doc);
	}

	tong += dau_doc - 0;
	dau_doc = 0;
	thu_tu += " -> 0";

	for (int i = 0; i < (int)phai.size(); i++) {
		tong += abs(dau_doc - phai[i]);
		dau_doc = phai[i];
		thu_tu += " -> " + intToString(dau_doc);
	}

	double trung_binh = (double)tong / yeucau.size();
	return{ "SCAN", tong, trung_binh, thu_tu };
}

// Thuật toán C-SCAN
KetQua CSCAN(vector<int> yeucau, int dau_doc, int max_cylinder) {
	int tong = 0;
	vector<int> trai, phai;
	string thu_tu = intToString(dau_doc);

	for (int x : yeucau) {
		if (x < dau_doc) trai.push_back(x);
		else phai.push_back(x);
	}

	sort(trai.begin(), trai.end());
	sort(phai.begin(), phai.end());

	for (size_t i = 0; i < phai.size(); i++) {
		tong += abs(dau_doc - phai[i]);
		dau_doc = phai[i];
		thu_tu += " -> " + intToString(dau_doc);
	}

	tong += abs(dau_doc - max_cylinder);
	dau_doc = max_cylinder;
	thu_tu += " -> " + intToString(max_cylinder);

	tong += max_cylinder;
	dau_doc = 0;
	thu_tu += " -> 0";

	for (size_t i = 0; i < trai.size(); i++) {
		tong += abs(dau_doc - trai[i]);
		dau_doc = trai[i];
		thu_tu += " -> " + intToString(dau_doc);
	}

	double trung_binh = (double)tong / yeucau.size();
	return{ "C-SCAN", tong, trung_binh, thu_tu };
}

int main() {
	ifstream fin("input.txt");
	if (!fin) {
		cerr << "Khong the mo file input.txt\n";
		return 1;
	}

	int n;
	fin >> n;
	vector<int> yeucau(n);
	for (int i = 0; i < n; i++) fin >> yeucau[i];
	int dau_doc; fin >> dau_doc;
	int max_cylinder; fin >> max_cylinder;
	fin.close();

	// Hiển thị dữ liệu đầu vào
	cout << left << setw(25) << "So luong yeu cau" << ": " << n << "\n";
	cout << left << setw(25) << "Danh sach yeu cau" << ": ";
	for (int x : yeucau) cout << x << " ";
	cout << "\n";
	cout << left << setw(25) << "Vi tri dau doc" << ": " << dau_doc << "\n";
	cout << left << setw(25) << "Cylinder toi da" << ": " << max_cylinder << "\n\n";

	// Tính kết quả
	vector<KetQua> ds;
	ds.push_back(FCFS(yeucau, dau_doc));
	ds.push_back(SSTF(yeucau, dau_doc));
	ds.push_back(SCAN(yeucau, dau_doc, max_cylinder));
	ds.push_back(CSCAN(yeucau, dau_doc, max_cylinder));

	// Hiển thị bảng kết quả
	cout << left << setw(12) << "Thuat toan"
		<< setw(15) << "Tong kc"
		<< setw(20) << "Khoang cach TB"
		<< "Thu tu di chuyen\n";
	cout << string(70, '-') << "\n";

	for (auto &kq : ds) {
		cout << left << setw(12) << kq.ten_thuat_toan
			<< setw(15) << kq.tong
			<< setw(20) << fixed << setprecision(2) << kq.trung_binh
			<< kq.thu_tu.c_str() << "\n"; // dùng .c_str() để cout nhận dạng
	}

	// Tìm thuật toán tối ưu
	double min_kc = ds[0].trung_binh;
	string toan_toan_toi_uu = ds[0].ten_thuat_toan;
	for (auto &kq : ds) {
		if (kq.trung_binh < min_kc) {
			min_kc = kq.trung_binh;
			toan_toan_toi_uu = kq.ten_thuat_toan;
		}
	}

	cout << "\n=== KET LUAN ===\n";
	cout << toan_toan_toi_uu << " la thuat toan toi uu nhat.\n";

	system("pause"); // giữ cửa sổ console

	return 0;
}
