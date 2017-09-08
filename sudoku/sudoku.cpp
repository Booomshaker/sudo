// sudoku.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <random>
#include <string.h>
using namespace std;
int arr[9][9] = { 0 };
int temp[9] = { 0 };
string para, num_str;
class Judge {
public:
	bool formatJudge() {
		if (para != "-c")
			return false;
		for (int k = 0; k < num_str.length(); k++) {
			if (num_str[k] >= '9' || num_str[k] <= '0')
				return false;
		}
		return true;
	}

};
class todoSudoku {
public:
	bool numJudge(int i, int j, int num) {
		for (int k = 0; k < i; k++)
			if (arr[k][j] == num)
				return false;
		for (int k = 0; k < j; k++)
			if (arr[i][k] == num)
				return false;
		int count = i % 3 * 3 + j % 3;
		while (count--)
			if (!(arr[i - i % 3 + count / 3][j - j % 3 + count % 3] - num))
				return false;
		return true;
	}
	bool fill(int y, int x, int* p) {
		if (y > 8)
			return true;
		if (numJudge(y, x, *p)) {
			arr[y][x] = *p;
			if (fill(y + (x + 1) / 9, (x + 1) % 9, temp))
				return true;
		}
		arr[y][x] = 0;
		if (p - temp >= 8)
			return false;
		if (fill(y, x, p + 1))
			return true;
	}
	void shuf(int *t) {
		for (int i = 0; i < 9; i++)
			*(t + i) = i + 1;
		random_shuffle(t, t + 9);
	}
	void shuf_first(int *t) {
		for (int i = 0; i < 9; i++)
			*(t + i) = i + 1;
		random_shuffle(t, t + 9);
		int num = 0;
		for (int i = 0; i < 9; i++) {
			if (*(t + i) == 3) {
				num = i;
				break;
			}
		}
		*(t + num) = *t;
		*t = 3;
	}
	void outPut(bool isRight) {
		ofstream outfile;
		outfile.open("myfile.txt");
		if (isRight) {
			int cnt = atoi(num_str.c_str());
			for (int k = 0; k < cnt; k++) {
				shuf(temp);
				shuf_first(arr[0]);
				fill(1, 0, temp);
				for (int i = 0; i < 9; i++) {
					for (int j : arr[i])
						outfile << j << " ";
					outfile << endl;
				}
				memset(temp, 0, sizeof(temp));
				memset(arr, 0, sizeof(arr));
				outfile << endl;
			}
		}
		else {
			outfile << "Format Wrong!" << endl;
		}
		outfile.close();
	}
};



int main(int argc, char ** argv) {
	srand((unsigned)time(0));
	Judge ju;
	todoSudoku to;
	para = argv[argc - 2];
	num_str = argv[argc - 1];
	bool isRight = ju.formatJudge();
	to.outPut(isRight);
	return 0;
}