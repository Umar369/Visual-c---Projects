#include <cmath>
#include <fstream>
#include "Functions.h"
#include <iostream>
#include <conio.h>
#include <stdlib.h>

using namespace std;
using std::cout;
using std::cin;
using std::endl;
using std::system;
#define PI 3.14159265359
#define RAD 57.295779513
#define SPEED 300.0 // Скорость света в вакууме
#define R 1.6
#define FULLTERN 360 // Полный оборот
#define NUMBER 16 // Количество вибраторов

int countDop = NULL;
double frequency;
int betta;
int tetta;
double TrueFaza[NUMBER];
double PhaseAmbiguity[NUMBER];
double PhaseRepair[NUMBER];
double *DemoMasA = new double[countDop];
double *DemoMasB = new double[countDop];
int *vector = new int[countDop];
double MasOtnosheniya[6][6];
double dev, devia;
int temp = NULL;

void Input()
{
	cout << "\tВведите частоту в диапазоне 100 - 400 МГц\n";
	cin >> frequency;
	cout << "\tВведите угол прихода\n";
	cin >> betta;
	cout << "\tВведите угол пеленга\n";
	cin >> tetta;
}

void calcDev()
{
	double lyambda;
	lyambda = SPEED / (double)frequency;
	dev = 2.0 * PI * R / lyambda * cos((double)betta*PI / FULLTERN / 2) * RAD;
	cout << "\tДевиация = " << dev << "\n"<< endl;
}

void calcMasDop()
{
	if (dev <= FULLTERN)
	{
		countDop = 2; // {0, 1}
		for (int i = 0; i < countDop; i++)
		{
			vector[i] = i;
			//cout << "vector= " << vector[i] << " ";
		}
	}
	else if ((dev > FULLTERN) && (dev <= 2 * FULLTERN))
	{
		countDop = 4; // {-1, 0, 1, 2}
		for (int i = 0; i < countDop; i++)
		{
			vector[i] = i-1;
			//cout << "vector= " << vector[i] << " ";
		}
	}
	else if ((dev > 2 * FULLTERN) && (dev <= 3 * FULLTERN))
	{
		countDop = 6; // {-2, -1, 0, 1, 2, 3}
		for (int i = 0; i < countDop; i++)
		{
			vector[i] = i-2;
			//cout << "vector= " << vector[i] << " ";
		}
	}
	//cout << "countDop= " << countDop;
	DemoMasA = new double[countDop];
	DemoMasB = new double[countDop];
}
void calcAndPrintTrueFaza()
{
	cout << "\tИстинные фазы\n";
	for (int k = 0; k < NUMBER; k++)
	{
		TrueFaza[k] = (dev * cos(2.0 * PI * k / NUMBER - tetta*PI / 180.0));
		cout << k << ") " << TrueFaza[k] << " ";
	}
	cout << endl << endl;
}

void calcAndPrintPhaseAmbiguity()
{
	cout << "\tФазы с неоднозначностью\n";
	for (int k = 0; k < NUMBER; k++)
	{
		if (((TrueFaza[k] < 0) && (TrueFaza[k] > -0.001)) || ((TrueFaza[k] > 0) && (TrueFaza[k] < 0.001)))
		{
			PhaseAmbiguity[k] = 0;
		}
		else if ((TrueFaza[k] >= 0.001) && (TrueFaza[k] < FULLTERN)) // 0 ... FULLTERN
		{
			PhaseAmbiguity[k] = TrueFaza[k];
		}
		else if ((TrueFaza[k] > FULLTERN) && (TrueFaza[k] < 2 * FULLTERN)) // 361 ... 2 * FULLTERN
		{
			PhaseAmbiguity[k] = TrueFaza[k] - FULLTERN;
		}
		else if (TrueFaza[k] > 2 * FULLTERN) // 721 ... 
		{
			PhaseAmbiguity[k] = TrueFaza[k] - 2 * FULLTERN;
		}
		else if ((TrueFaza[k] < -0.001) && (TrueFaza[k] > -FULLTERN)) // ... 0
		{
			PhaseAmbiguity[k] = FULLTERN + TrueFaza[k];
		}
		else if ((TrueFaza[k] < -FULLTERN) && (TrueFaza[k] > -2 * FULLTERN)) // -2 * FULLTERN ... -361
		{
			PhaseAmbiguity[k] = 2 * FULLTERN + TrueFaza[k];
		}
		else if (TrueFaza[k] < 2 * FULLTERN) // ... -721 
		{
			PhaseAmbiguity[k] = 3 * FULLTERN + TrueFaza[k];
		}

		cout << k <<") "<<PhaseAmbiguity[k] <<" ";
	}
	cout << endl << endl;
}

void CalcPhaseRepair()
{
	cout << "\tВосстановленные фазы\n";
	int cmin, dmin;
	cmin = dmin = 0;
	double min = 0;
	/* формирование промежуточных массивов для одной пары вибраторов,
	элементы которых являются 36 возможных вариантов */
	for (int a = 0; a < 12; a++)
	{
		for (int b = 0; b < countDop; b++)
		{
			DemoMasA[b] = PhaseAmbiguity[a] - vector[b] * FULLTERN;
			DemoMasB[b] = PhaseAmbiguity[a + 4] - vector[b] * FULLTERN;
			//cout << DemoMasA[b] << "  \t" << DemoMasB[b] << "\n";
		}
		//cout << "\n";
		for (int c = 0; c < 6; c++)
		{
			for (int d = 0; d < 6; d++)
			{
				devia = sqrt(pow(DemoMasA[d], 2) + pow(DemoMasB[c], 2));
				//cout << devia << " ";
				MasOtnosheniya[c][d] = abs(devia / dev - 1);
				min = MasOtnosheniya[0][0];
				//cout << MasOtnosheniya[c][d] << " ";
			}
			//cout << "\n";
		}
		for (int c = 0; c < 6; c++)
		{
			for (int d = 0; d < 6; d++)
			{
				if (MasOtnosheniya[c][d] <= min)
				{
					min = MasOtnosheniya[c][d];
					cmin = c;
					dmin = d;
				}
			}
		}
		for (int c = 0; c < 6; c++)
		{
			for (int d = 0; d < 6; d++)
			{
				if (MasOtnosheniya[c][d] == min)
				{
					temp++;
				}
			}
		}
		if (temp >= 1)
		{
			PhaseRepair[a] = DemoMasA[dmin];
			PhaseRepair[a + 4] = DemoMasB[cmin];
		}
		else
		{
			cout << endl << "ATTENTION ! " << endl;
		}
			//cout << "\nc= " << cmin << "d= " << dmin << "\n\n" << "temp = " << temp<<"\n";
			temp = 0;
			//cout << "****************************************"<< endl;
		//cout << PhaseRepair[a] << " " << PhaseRepair[a + 4] << "\n\n";
	}
	for (int f = 0; f < NUMBER; f++)
	{
		cout << f << ") " << PhaseRepair[f] << " ";
	}
}

void Output()
{
	ofstream fout("Output.txt"); // создаём объект класса ofstream для записи и связываем его с файлом cppstudio.txt
	fout << "\tfrequency " << frequency << " betta " << betta << " dev " << dev << " tetta " << tetta << "\n\n";
	for (int k = 0; k < NUMBER; k++)
	{
		fout << k << ") " << TrueFaza[k] << "\t" << PhaseAmbiguity[k] << "\t" << PhaseRepair[k] << "\n";
	}
	fout.close(); // закрываем файл
}
