#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>
#include <conio.h>
using namespace std;

// FCFS
void FCFS(vector<int> yeucau, int dau_doc) {
	int tong = 0;
	int hien_tai = dau_doc;
	cout << "FCFS thu tu di chuyen: " << hien_tai;
	for (int x : yeucau) {
		tong += abs(hien_tai - x);
		hien_tai = x;
		cout << " -> " << x;
	}
	cout << "\nTong khoang cach: " << tong << "\n\n";
}

// SSTF
void SSTF(vector<int> yeucau, int dau_doc) {
	int tong = 0;
	int hien_tai = dau_doc;
	vector<bool> da_dung(yeucau.size(), false);

	cout << "SSTF thu tu di chuyen: " << hien_tai;
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
		cout << " -> " << hien_tai;
	}
	cout << "\nTong khoang cach: " << tong << "\n\n";
}

// SCAN (huong ve 0)
void SCAN(vector<int> yeucau, int dau_doc, int max_cylinder) {
	int tong = 0;
	vector<int> trai, phai;

	for (int x : yeucau) {
		if (x < dau_doc) trai.push_back(x);
		else phai.push_back(x);
	}

	sort(trai.begin(), trai.end());
	sort(phai.begin(), phai.end());

	cout << "SCAN (huong ve 0) thu tu di chuyen: " << dau_doc;
	// Di ve ben trai truoc
	for (int i = (int)trai.size() - 1; i >= 0; i--) {
		tong += abs(dau_doc - trai[i]);
		dau_doc = trai[i];
		cout << " -> " << dau_doc;
	}
	// cham bien 0
	tong += dau_doc - 0;
	dau_doc = 0;
	cout << " -> " << dau_doc;

	// sau do quay sang phai
	for (int i = 0; i < (int)phai.size(); i++) {
		tong += abs(dau_doc - phai[i]);
		dau_doc = phai[i];
		cout << " -> " << dau_doc;
	}

	cout << "\nTong khoang cach: " << tong << "\n\n";
}

// C-SCAN (huong ve 0)
void CSCAN(vector<int> yeucau, int dau_doc, int max_cylinder) {
	int tong = 0;
	vector<int> trai, phai;

	for (int x : yeucau) {
		if (x < dau_doc) trai.push_back(x);
		else phai.push_back(x);
	}

	sort(trai.begin(), trai.end());
	sort(phai.begin(), phai.end());

	cout << "C-SCAN (huong ve 0) thu tu di chuyen: " << dau_doc;

	// Di ve phai truoc
	for (size_t i = 0; i < phai.size(); i++) {
		tong += abs(dau_doc - phai[i]);
		dau_doc = phai[i];
		cout << " -> " << dau_doc;
	}

	// cham bien max
	tong += abs(dau_doc - max_cylinder);
	dau_doc = max_cylinder;
	cout << " -> " << dau_doc;

	// nhay ve 0 (khong tinh khoang cach di giua)
	tong += max_cylinder;
	dau_doc = 0;
	cout << " -> " << dau_doc;

	// Di tiep ben trai
	for (size_t i = 0; i < trai.size(); i++) {
		tong += abs(dau_doc - trai[i]);
		dau_doc = trai[i];
		cout << " -> " << dau_doc;
	}

	cout << "\nTong khoang cach: " << tong << "\n\n";
}

int main() {
	int n; 
	cout << "Nhap so luong yeu cau: "; 
	cin >> n; 
	vector<int> yeucau(n); 
	cout << "Nhap cac yeu cau : "; 
	for (int i = 0; i < n; i++) cin >> yeucau[i]; 
	int dau_doc; cout << "Nhap vi tri dau doc ban dau: "; 
	cin >> dau_doc; int max_cylinder; 
	cout << "Nhap gia tri cylinder toi da cua dia: "; 
	cin >> max_cylinder; 
	cout << "\n=== KET QUA ===\n";

	FCFS(yeucau, dau_doc);
	SSTF(yeucau, dau_doc);
	SCAN(yeucau, dau_doc, max_cylinder);
	CSCAN(yeucau, dau_doc, max_cylinder);

	_getch();
	return 0;
}

