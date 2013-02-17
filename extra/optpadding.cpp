/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

/*
 This program calculate the optimum position to fields in a C/C++ structure
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <map>

#define INF 1<<20

using namespace std;

size_t _get_padding_ext(size_t offset, size_t align)
{
	return (align - (offset % align)) % align;
}

map<int, int> pi;
map<int, int> mojo;

int solution = INF;
int fsolution = INF;
int vsolution[100];
int temp[100];

void doit(bool* mark, int* align, int* offset, int* sizes, int ini, int size)
{
	size_t padding = 0;

	if (ini == size) {
		if (ini == 0) {
			offset[ini] = 0;
		} else {
			padding = _get_padding_ext(offset[ini-1] + align[ini - 1], align[ini - 1]);
			offset[ini] = padding + offset[ini-1] + align[ini - 1];
		}

		if (solution == INF) fsolution = offset[ini];

		if (offset[ini] < solution) {
			solution = offset[ini];
			for (int i = 0; i < size; ++i) {
				vsolution[i] = temp[i];
			}
		}

		return;
	}

	for (int i = 0; i < size; ++i)
		if (mark[i]){
			mark[i] = false;

			temp[ini] = i;
			align[ini] = sizes[i];

			if (ini == 0) {
				offset[ini] = 0;
			} else {
				padding = _get_padding_ext(offset[ini-1] + align[ini - 1], align[ini - 1]);
				offset[ini] = padding + offset[ini-1] + align[ini - 1];
			}

			if (offset[ini] < solution) {
				mojo[ini] = offset[ini];
				doit(mark, align, offset, sizes, ini+1, size);
			}

			mark[i] = true;
		}
}

//4 8 4 8 8 4
//4 4 8 8 8 4
class T {
	int l1;
	double l2;
	int l3;
	double l4;
	double l5;
	int l6;
};

class T2 {
	int l1;
	int l2;
	double l3;
	double l4;
	double l5;
	int l6;
};

int main()
{
	int sizes[100];
	int n;

	cout << "N fields: ";
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cout << "Size field " << i << ":\n";

		cin >> sizes[i];
	}

	bool mark[100];
	int align[100];
	int offset[100];

	for (int i = 0; i < n; ++i) {
		mark[i] = true;
		align[i] = 0;
		offset[i] = 0;
	}

	doit(mark, align, offset, sizes, 0, n);

	cout << "original size: " << fsolution << "\n";
	cout << "solution: " << solution << "\n";
	for (int i = 0; i < n; ++i) {
		cout << " " << sizes[vsolution[i]];
	}
	cout << "\n";

	cout << "-----------------------" << "\n";
	cout << "T: " << sizeof(T) << "\n";
	cout << "T2: " << sizeof(T2) << "\n";

	cout << "int: " << sizeof(int) << "\n";
	cout << "double: " << sizeof(double) << "\n";
	return 0;
}

