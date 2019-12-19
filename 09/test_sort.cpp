#include <iostream>
#include <cstdint>
#include <cstddef>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <chrono>
#include <cstdio>
#include "sort.h"

using namespace std;

void gen_test(const string &str, const string &teststr, size_t cnt) {
	ofstream fout(str, ios::binary);
	ofstream testfout(teststr, ios::binary);
	for (size_t i = 0; i < cnt; ++i) {
		uint64_t tmp = rand() + (1llu << 31) * rand();
		fout.write((char*)&tmp, sizeof(tmp));
		testfout.write((char*)&tmp, sizeof(tmp));
	}
}

int main() {
	gen_test("test.bin", "testtmp.bin", 3000000);
	thread_file_sort("test.bin", "out.bin");
	{
		ifstream fin("testtmp.bin", ios::binary);
		ifstream fout("out.bin", ios::binary);
		vector<uint64_t> v;
		uint64_t tmp;
		while (fin.read((char*)&tmp, sizeof(tmp))) {
			v.push_back(tmp);
		}
		sort(v.begin(), v.end());
		for (size_t i = 0; i < v.size(); ++i) {
			if (fout.read((char*)&tmp, sizeof(tmp))) {
				if (tmp != v[i]) {
					cout << "Error sort order" << endl;
					return 0;
				}
			} else {
				cout << "File not full!" << endl;
				return 0;
			}
		}
	}
	remove("test.bin");
	remove("testtmp.bin");
	remove("out.bin");
	cout << "OK" << endl;
	return 0;
}
