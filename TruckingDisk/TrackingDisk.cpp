#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>
#include <conio.h>
using namespace std;

double FCFS(vector<int> yeucau, int dau_doc) {
	int tong = 0;
	int hien_tai = dau_doc;
	cout << "FCFS thu tu di chuyen: " << hien_tai;
	for (int x : yeucau) {
		tong += abs(hien_tai - x);
		hien_tai = x;
		cout << " -> " << x;
	}
	double khoang_cach_trung_binh = (double)tong / yeucau.size();
	cout << "\nTong khoang cach: " << tong << " | Khoang cach trung binh: " << khoang_cach_trung_binh << "\n\n";
	return khoang_cach_trung_binh;
}


double SSTF(vector<int> yeucau, int dau_doc) {
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
	double khoang_cach_trung_binh = (double)tong / yeucau.size();
	cout << "\nTong khoang cach: " << tong << " | Khoang cach trung binh: " << khoang_cach_trung_binh << "\n\n";
	return khoang_cach_trung_binh;
}


double SCAN(vector<int> yeucau, int dau_doc, int max_cylinder) {
	int tong = 0;
	vector<int> trai, phai;

	for (int x : yeucau) {
		if (x < dau_doc) trai.push_back(x);
		else phai.push_back(x);
	}

	sort(trai.begin(), trai.end());
	sort(phai.begin(), phai.end());

	cout << "SCAN (huong ve 0) thu tu di chuyen: " << dau_doc;
	
	for (int i = (int)trai.size() - 1; i >= 0; i--) {
		tong += abs(dau_doc - trai[i]);
		dau_doc = trai[i];
		cout << " -> " << dau_doc;
	}
	
	tong += dau_doc - 0;
	dau_doc = 0;
	cout << " -> " << dau_doc;

	
	for (int i = 0; i < (int)phai.size(); i++) {
		tong += abs(dau_doc - phai[i]);
		dau_doc = phai[i];
		cout << " -> " << dau_doc;
	}

	double khoang_cach_trung_binh = (double)tong / yeucau.size();
	cout << "\nTong khoang cach: " << tong << " | Khoang cach trung binh: " << khoang_cach_trung_binh << "\n\n";
	return khoang_cach_trung_binh;
}


double CSCAN(vector<int> yeucau, int dau_doc, int max_cylinder) {
	int tong = 0;
	vector<int> trai, phai;

	for (int x : yeucau) {
		if (x < dau_doc) trai.push_back(x);
		else phai.push_back(x);
	}

	sort(trai.begin(), trai.end());
	sort(phai.begin(), phai.end());

	cout << "C-SCAN (huong ve 0) thu tu di chuyen: " << dau_doc;

	
	for (size_t i = 0; i < phai.size(); i++) {
		tong += abs(dau_doc - phai[i]);
		dau_doc = phai[i];
		cout << " -> " << dau_doc;
	}

	
	tong += abs(dau_doc - max_cylinder);
	dau_doc = max_cylinder;
	cout << " -> " << dau_doc;

	
	tong += max_cylinder;
	dau_doc = 0;
	cout << " -> " << dau_doc;

	
	for (size_t i = 0; i < trai.size(); i++) {
		tong += abs(dau_doc - trai[i]);
		dau_doc = trai[i];
		cout << " -> " << dau_doc;
	}

	double khoang_cach_trung_binh = (double)tong / yeucau.size();
	cout << "\nTong khoang cach: " << tong << " | Khoang cach trung binh: " << khoang_cach_trung_binh << "\n\n";
	return khoang_cach_trung_binh;
}

int main() {
	int n;
	cout << "Nhap so luong yeu cau: ";
	cin >> n;
	vector<int> yeucau(n);
	cout << "Nhap cac yeu cau : ";
	for (int i = 0; i < n; i++) cin >> yeucau[i];
	int dau_doc; cout << "Nhap vi tri dau doc ban dau: ";
	cin >> dau_doc;
	int max_cylinder;
	cout << "Nhap gia tri cylinder toi da cua dia: ";
	cin >> max_cylinder;
	cout << "\n=== KET QUA ===\n";

	
	double fcfs_kc = FCFS(yeucau, dau_doc);
	double sstf_kc = SSTF(yeucau, dau_doc);
	double scan_kc = SCAN(yeucau, dau_doc, max_cylinder);
	double cscan_kc = CSCAN(yeucau, dau_doc, max_cylinder);

	
	double min_kc = min({ fcfs_kc, sstf_kc, scan_kc, cscan_kc });
	cout << "\n=== KET LUAN ===\n";
	if (min_kc == fcfs_kc) cout << "FCFS la thuat toan toi uu nhat.\n";
	else if (min_kc == sstf_kc) cout << "SSTF la thuat toan toi uu nhat.\n";
	else if (min_kc == scan_kc) cout << "SCAN (huong ve 0) la thuat toan toi uu nhat.\n";
	else cout << "C-SCAN (huong ve 0) la thuat toan toi uu nhat.\n";

	_getch();
	return 0;
}
