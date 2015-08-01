#include <iostream>
#include <conio.h>
#include <cstring>
#include <cctype>

using std::cout;
using std::cin;
using std::endl;

int main()
{
	setlocale(LC_ALL, "Russian");
	int a = 0, b = 0, c = 0, d = 0; //a,c - строки. b,d - столбцы
		
	cout << "\tПрограмма перемножения двух матриц\n\nВведите количество строк и столбцов первой матрицы через пробел\n ";
	cin >> a >> b;
	cout << "Введите количество строк и столбцов второй матрицы через пробел\n ";
	cin >> c >> d;
	if (b==c)
	{
		int **p = new int *[a];	//указатель на указатель для первой матрицы
		for (int i(0); i < a; i++)		
			p[i] = new int[b];

		int **p1 = new int *[c];	//указатель на указатель для второй матрицы
		for (int i(0); i < c; i++)
			p1[i] = new int[d];

		int **p2 = new int *[a];	//указатель на указатель для результирующей матрицы
		for (int i(0); i < a; i++)
			p2[i] = new int[d];

		cout << "Введите первую матрицу\n";
		for (int i(0); i < a; i++)
		{
			for (int j(0); j < b; j++)
			{
				cin >> p[i][j];
			}
		}
		

		cout << "Введите вторую матрицу\n";
		for (int i(0); i < c; i++)
		{
			for (int j(0); j < d; j++)
			{
				cin >> p1[i][j];
			}
		}
		for (int i(0); i < a; i++) //обнуление результирующей матрицы (необходимо!)
		{
			for (int j(0); j < d; j++)
			{
				p2[i][j] = 0;
			}
		}
		for (int i(0); i < a; i++) //вычисление результирующей матрицы
		{
			for (int j(0); j < d; j++)
			{
				for (int k(0); k < b; k++)
				{
					p2[i][j] += p[i][k] * p1[k][j];
				}
			}
		}
		system("cls");
		cout << "Первая матрица:\n";
		for (int i(0); i < a; i++)
		{
			for (int j(0); j < b; j++)
			{
				cout << p[i][j] << ' ';
			}
			cout << "\n";
		}
		cout << "Вторая матрица:\n";
		for (int i(0); i < c; i++)
		{
			for (int j(0); j < d; j++)
			{
				cout << p1[i][j] << ' ';
			}
			cout << "\n";
		}
		cout << "Результирующая матрица:\n";
		for (int i(0); i < a; i++)
		{
			for (int j(0); j < d; j++)
			{
				cout << p2[i][j] << ' ';
			}
			cout <<"\n";
		}
//освобождение выделенной под массивы памяти///////
		for (int i(0); i < a; i++)				///
			delete[] p[i];						///
		delete[] p;								///
												///
		for (int i(0); i < c; i++)				///
			delete[] p1[i];						///
		delete[] p1;							///
												///
		for (int i(0); i < a; i++)				///
			delete[] p2[i];						///
		delete[] p2;							///
///////////////////////////////////////////////////
	}
	else cout << "Данные матрицы не могут быть перемножены!\n";
	
	cout << "Нажмите любую клавишу для выхода...";
	_getch();
	return 0;
}
