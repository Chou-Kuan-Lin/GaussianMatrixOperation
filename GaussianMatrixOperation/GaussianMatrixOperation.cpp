#include "pch.h"
#include <vector>
#include <iostream>

using namespace std;

void showMatrix(int n, vector<float> matrix)
{
	printf("==========\n");
	for (int a = 0; a < n; a++)
	{
		for (int b = 0; b < n; b++)
		{
			printf("%f ", matrix[a*n+b]);
		}
		printf("\n");
	}
	printf("==========\n");
}

//高斯約當法
void main()
{
	//矩陣大小(Feature數量)
	int n = 3;

	//矩陣宣告、定值
	vector <float> matrix;
	vector <float> unit;
	
	for (int a = 0; a < n; a++)
	{
		for (int b = 0;b < n;b++)
		{
			if (a == b)
				unit.push_back(1);
			else
				unit.push_back(0);
		}
	}
	matrix.push_back(2);
	matrix.push_back(2);
	matrix.push_back(2);
	matrix.push_back(2);
	matrix.push_back(3);
	matrix.push_back(4);
	matrix.push_back(4);
	matrix.push_back(5);
	matrix.push_back(7);

	printf("-----The Original Matrix-----\n");
	showMatrix(n, matrix);
	//printf("UNIT");
	showMatrix(n, unit);
	printf("-----The Original Matrix-----\n");
	
	//高斯列運算
	//上三角矩陣
	float times = 0;
	float minus = 0;
	for (int a = 0; a < n; a++)	//列數
	{
		//使i*i之前項為0
		for (int b = 0;b < a;b++)	//為1的行數
		{
			minus = matrix[a*n + b] / matrix[b*n + b];
			//printf("minus=%f\n", minus);
			for (int c = 0;c < n;c++)	//行數
			{
				//printf("a=%i,b=%i,c=%i\n", a, b, c);
				matrix[a*n + c] -= minus * matrix[b*n + c];
				unit[a*n + c] -= minus * unit[b*n + c];
				//showMatrix(n, matrix);
			}
		}

		//使i*i為1
		times = matrix[a*n + a];
		for (int d = 0; d < n; d++)	//行數
		{
			matrix[a*n + d] /= times;
			unit[a*n + d] /= times;
			//showMatrix(n, matrix);
		}
	}

	//printf("---------------------------------------------------------------------------\n");
	//showMatrix(n, matrix);
	//showMatrix(n, unit);
	//printf("---------------------------------------------------------------------------\n");

	//下三角矩陣
	for (int a = n - 1;a >= 0; a--)	//為1的列數
	{		
		//使i*i之後項為0
		for (int c = a - 1;c >= 0;c--)	//列數
		{
			minus = matrix[c*n + a] / matrix[a*n + a];
			for (int d = 0;d < n;d++)	//行數
			{
				//printf("a=%i,c=%i,d=%i\n", a, c, d);
				matrix[c*n + d] -= minus * matrix[a*n + d];
				unit[c*n + d] -= minus * unit[a*n + d];
				//showMatrix(n, matrix);
			}
		}
	}

	bool check = false;	//確認是否為單元矩陣
	for (int a = 0;a < n;a++)	//行數
		for (int b = 0;b < n; b++)	//列數
			if (matrix[a*n + b] != matrix[a*n + b] || matrix[a*n + b] != 0)	//#nan(ind) or not 0
				if (a == b && matrix[a*n + b] != 1)	//i*i=1
					check = true;

	if (check == true)
		printf("Can't not compute.");
	else
	{
		printf("-----The Final Matrix-----\n");
		showMatrix(n, matrix);
		showMatrix(n, unit);
		printf("-----The Final Matrix-----\n");
	}

	system("pause");
}