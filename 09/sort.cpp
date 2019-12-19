#include "sort.h"

#include <fstream>
#include <algorithm>
#include <queue>
#include <string>
#include <cstdio>
#include <vector>
#include <mutex>
#include <thread>


enum { SIZE = 4 * 1024 * 1024 / sizeof(uint64_t) - 100};

using namespace std;

void chunk_sort(ifstream &fin, mutex &f_mutex, size_t &fnum, mutex &n_mutex) {
    uint64_t *arr = new uint64_t[SIZE]();
    size_t top;
    while (true) {
        for (top = 0; top < SIZE; top++) {
            unique_lock<mutex> unique(f_mutex);
            if (!fin.read((char *) &arr[top], sizeof(arr[top]))) {
                break;
            }
        }
		if (top == 0) {
		    delete[] arr;
        	return;
 	    }
	    size_t tmp_fnum;
	    {
	        lock_guard<mutex> guard(n_mutex);
			tmp_fnum = fnum++;
	    }
	    sort(arr, arr + top);
	    ofstream fout("sort_" + to_string(tmp_fnum) + ".bin", ios::binary);
		fout.write((char *) arr, top * sizeof(arr[0]));
    }
}

void thread_file_sort(const string &ifn, const string &ofn) {
    ifstream fin(ifn, ios::binary);
    mutex m1, m2;
    size_t num = 0;
    thread t1(chunk_sort, ref(fin), ref(m1), ref(num), ref(m2));
    thread t2(chunk_sort, ref(fin), ref(m1), ref(num), ref(m2));
    t1.join();
    t2.join();
    priority_queue< pair<uint64_t, size_t>, vector< pair<uint64_t, size_t> >, std::greater< pair<uint64_t, size_t> > > q;
    vector<ifstream> f_vec;
    for (int i = 0; i < num; i++) {
        f_vec.emplace_back("sort_" + to_string(i) + ".bin", ios::binary);
    }
    for (int i = 0; i < num; i++) {
        int64_t cur;
        f_vec[i].read((char *) &cur, sizeof(cur));
        q.push({cur, i});
    }
    ofstream fout(ofn, ios::binary);
    while (!q.empty()) {
        fout.write((char *) &q.top(), sizeof(q.top().first));
        int64_t cur;
        if (f_vec[q.top().second].read((char *) &cur, sizeof(cur))) {
            q.push({cur, q.top().second});
        }
        q.pop();
    }
    for (size_t i = 0; i < num; i++) {
        f_vec[i].close();
        remove(("sort_" + to_string(i) + ".bin").c_str());
    }
}
