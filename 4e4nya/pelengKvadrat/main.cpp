#include "D:\WORK\Projects\Visual c++ Projects\Lib\Functions.h"

#include <iostream>
#include <conio.h>

using namespace std;
#define STEP 22.5;

float Fm1, Fm2;

int main()
{
	setlocale(LC_ALL, "Russian");

	Input();
	calcDev();
	calcMasDop();
	calcAndPrintTrueFaza();
	calcAndPrintPhaseAmbiguity();
	CalcPhaseRepair();
	Output();
	_getch();
	return 0;
}