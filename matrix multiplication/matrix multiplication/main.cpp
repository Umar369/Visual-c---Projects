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
	int a = 0, b = 0, c = 0, d = 0; //a,c - ������. b,d - �������
		
	cout << "\t��������� ������������ ���� ������\n\n������� ���������� ����� � �������� ������ ������� ����� ������\n ";
	cin >> a >> b;
	cout << "������� ���������� ����� � �������� ������ ������� ����� ������\n ";
	cin >> c >> d;
	if (b==c)
	{
		int **p = new int *[a];	//��������� �� ��������� ��� ������ �������
		for (int i(0); i < a; i++)		
			p[i] = new int[b];

		int **p1 = new int *[c];	//��������� �� ��������� ��� ������ �������
		for (int i(0); i < c; i++)
			p1[i] = new int[d];

		int **p2 = new int *[a];	//��������� �� ��������� ��� �������������� �������
		for (int i(0); i < a; i++)
			p2[i] = new int[d];

		cout << "������� ������ �������\n";
		for (int i(0); i < a; i++)
		{
			for (int j(0); j < b; j++)
			{
				cin >> p[i][j];
			}
		}
		

		cout << "������� ������ �������\n";
		for (int i(0); i < c; i++)
		{
			for (int j(0); j < d; j++)
			{
				cin >> p1[i][j];
			}
		}
		for (int i(0); i < a; i++) //��������� �������������� ������� (����������!)
		{
			for (int j(0); j < d; j++)
			{
				p2[i][j] = 0;
			}
		}
		for (int i(0); i < a; i++) //���������� �������������� �������
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
		cout << "������ �������:\n";
		for (int i(0); i < a; i++)
		{
			for (int j(0); j < b; j++)
			{
				cout << p[i][j] << ' ';
			}
			cout << "\n";
		}
		cout << "������ �������:\n";
		for (int i(0); i < c; i++)
		{
			for (int j(0); j < d; j++)
			{
				cout << p1[i][j] << ' ';
			}
			cout << "\n";
		}
		cout << "�������������� �������:\n";
		for (int i(0); i < a; i++)
		{
			for (int j(0); j < d; j++)
			{
				cout << p2[i][j] << ' ';
			}
			cout <<"\n";
		}
//������������ ���������� ��� ������� ������///////
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
	else cout << "������ ������� �� ����� ���� �����������!\n";
	
	cout << "������� ����� ������� ��� ������...";
	_getch();
	return 0;
}
