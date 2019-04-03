#include "pch.h"
#include "PlanszaSudoku.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Pole::Pole()
{
	this->x = 1;
	this->y = 1;
	this->znak = ' ';
	this->czyPuste = true;
}

Pole::Pole(int x, int y, char znak)
{
	this->x = x;
	this->y = y;
	this->znak = znak;
	if (znak == ' ') { this->czyPuste = true; }
	this->wartoscPola = static_cast<int>(znak);

}

Pole::~Pole() {}

Plansza::Plansza()
{
	this->rozmiarC = 13;
	this->rozmiarR = 9;
	this->taPlansza = generujPlansze(9);
}

vector<vector<Pole>> Plansza::generujPlansze(int r)
{
	vector<Pole>yTemp;
	vector<vector<Pole>>temp;
	int sektorCounter = 0;

	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < r; j++)
		{
			Pole *wskPole = nullptr;
			if (i >= 0 && i <= 2 && j >= 0 && j <= 2) { wskPole = new Pole(i, j, ' '/*(char)0-207*/);  wskPole->setSektor(0); }
			else if (i >= 3 && i <= 5 && j >= 0 && j <= 2) { wskPole = new Pole(i, j, ' '/* (char)3 - 207*/); wskPole->setSektor(3); }
			else if (i >= 6 && i <= 8 && j >= 0 && j <= 2) { wskPole = new Pole(i, j, ' '/* (char)6 - 207*/); wskPole->setSektor(6); }

			else if (i >= 0 && i <= 2 && j >= 3 && j <= 5) { wskPole = new Pole(i, j, ' '/* (char)1 - 207*/); wskPole->setSektor(1); }
			else if (i >= 3 && i <= 5 && j >= 3 && j <= 5) { wskPole = new Pole(i, j, ' '/* (char)4 - 207*/); wskPole->setSektor(4); }
			else if (i >= 6 && i <= 8 && j >= 3 && j <= 5) { wskPole = new Pole(i, j, ' '/* (char)7 - 207*/); wskPole->setSektor(7); }

			else if (i >= 0 && i <= 2 && j >= 6 && j <= 8) { wskPole = new Pole(i, j, ' '/* (char)2 - 207*/); wskPole->setSektor(2); }
			else if (i >= 3 && i <= 5 && j >= 6 && j <= 8) { wskPole = new Pole(i, j, ' '/* (char)5 - 207*/); wskPole->setSektor(5); }
			else if (i >= 6 && i <= 8 && j >= 6 && j <= 8) { wskPole = new Pole(i, j, ' '/* (char)8 - 207*/); wskPole->setSektor(8); }
			else {}

			wskPole->puste();
			yTemp.push_back(*wskPole);
		}
		temp.push_back(yTemp);
		yTemp.clear();
	}

	return temp;
}

void Plansza::wyswietl(int tryb)
{
	if (tryb == 0)
	{
		int j2 = 0;
		for (int i = 0; i < 9; i++)
		{
			j2 = 0;
			for (int j = 0; j < 9; j++)
			{
				cout << " _ " << this->akcesP(i, j2).getChar();

				cout << " _ ";

				if (j == 2 || j == 5) { cout << " | "; }
				j2++;
			}
			if (i == 2 || i == 5) { cout << endl; }
			cout << endl;

		}
	}

	else if (tryb == 1)
	{
		int prawdopodobienstwo = 0;
		int j2 = 0;
		for (int i = 0; i < 9; i++)
		{
			j2 = 0;
			for (int j = 0; j < 9; j++)
			{
				prawdopodobienstwo = rand() % 100;
				if (prawdopodobienstwo >= 66) { cout << " _ " << this->akcesP(i, j2).getChar(); }
				else { cout << " _  "; }
				cout << " _ ";

				if (j == 2 || j == 5) { cout << " | "; }
				j2++;
			}
			if (i == 2 || i == 5) { cout << endl; }
			cout << endl;

		}
	}
}

void Plansza::PlanszaU(int x, int y, char znak)
{
	this->taPlansza[x][y].setChar(znak);
	this->taPlansza[x][y].pelne();
}

char Plansza::PlanszaU(int x, int y)
{
	return taPlansza[x][y].getChar();
}

int Plansza::PlanszaW(int x, int y)
{
	return taPlansza[x][y].wartoscPola;
}

int Plansza::los(int zakres)
{
	int k;
	k = rand() % zakres;
	k += 1;
	return k;
}