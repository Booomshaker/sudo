// sudoku.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <random>
#include <string>
#include <string.h>
using namespace std;
int arr[9][9] = { 0 };
int temp[9] = { 0 };
ofstream outfile;
string para, num_str;
class Judge {
public:
	bool formatJudge() {   //判断命令行输入的参数格式是否正确
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
	bool numJudge(int i, int j, int num) {     //判断填入数字是否符合数独原则
		for (int k = 0; k < i; k++)      //列判断
			if (arr[k][j] == num)
				return false;
		for (int k = 0; k < j; k++)      //行判断
			if (arr[i][k] == num)
				return false;
		int count = i % 3 * 3 + j % 3;
		while (count--)                  //块判断
			if (!(arr[i - i % 3 + count / 3][j - j % 3 + count % 3] - num))
				return false;
		return true;
	}
	bool fill(int y, int x, int* p) {      //回溯法填入数字
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
	void shuf(int *t) {           //生成一行随机数组
		for (int i = 0; i < 9; i++)
			*(t + i) = i + 1;
		random_shuffle(t, t + 9);
	}
	void shuf_first(int *t) {     //生成第一行随机数 包含要求：首行首列数字固定
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
	void toPrint () {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++)
				cout << arr[i][j] << " ";
			cout << endl;
		}
	}
	void outPut(bool isRight) {         //生成并输出数独终盘
		if (isRight) {						//若输入格式正确 则输出数独终盘
			int cnt = atoi(num_str.c_str());
			for (int k = 0; k < cnt; k++) {
				shuf(temp);
				shuf_first(arr[0]);
				fill(1, 0, temp);
				toPrint(); 
				memset(temp, 0, sizeof(temp));
				memset(arr, 0, sizeof(arr));
				cout << endl;
			}
		}
		else {								//若输入格式错误 则报错
			cout << "Format Wrong!!!" << endl;
		}
	}
};



int main(int argc, char ** argv) {
	srand((unsigned)time(0));
	freopen("myfile.txt", "w", stdout);
	Judge ju;
	todoSudoku to;
	para = argv[argc - 2];
	num_str = argv[argc - 1];
	bool isRight = ju.formatJudge();
	to.outPut(isRight);
	return 0;
}
