// ConsoleApplication7.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<iomanip>
using namespace std;
int input(char n[][20], int p[], int s[])
{
	int i, num = 0;
	 while(num <= 0 || num >= 100)
	{
		cout << "please input n=";
		cin >> num;
	}
	cout << endl;
	for (i = 0; i < num; i++)
	{
		cout << "input " << i + 1 << "th goods:" << endl;
		cout << "   name:";
		cin >> n[i];
		cout << "   price:";
		cin >> p[i];
		cout << "   stock:";
		cin >> s[i];
	}
	cout << endl << "input finish" << endl << endl;
	return num;
}
void show(int num, char n[][20], int p[], int s[])
{
	int i;
	cout << "        goods" << endl;
	cout << "-------------------" << endl;
	cout << "  name   |  price  |  stock  " << endl;
	cout << "---------------------" << endl;
	if (num != 0)
		for (i = 0; i < num; i++)
		{
			cout << setw(20) << n[i] << "  ";
			cout << setw(7) << p[i] << "  ";
			cout << setw(7) << s[i] << endl;

		}
	else
		cout << endl << "non!!!" << endl << endl;
	cout << "-------------------------" << endl;
}
int menu()
{
	int choice = 0;
	cout << endl<< endl << endl;
	cout << "      menu" << endl;
	cout << "---------------------------" << endl;
	cout << "1.input goods" << endl;
	cout << "2.show goods" << endl;
	cout << "0.exit" << endl;
	cout << "------------------------------" << endl;
	cout << "your choice:";
	cin >> choice;
	cout << endl << endl << endl;
	return choice;
}
int main()
{
	int n = 0, choice = 0;
	int price[100], stock[100];
	char name[100][20];
	while ((choice = menu()) != 0)
	{
		switch (choice)
		{
		case 1:
			n = input(name, price, stock);
			break;
		case2:
			show(n, name, price, stock);
			break;
		}
	}
    return 0;
}

