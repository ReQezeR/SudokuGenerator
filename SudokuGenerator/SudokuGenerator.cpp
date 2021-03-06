// TEST 010 Sudoku.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include "PlanszaSudoku.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <conio.h>
#include <ctime>
#include <vector>
#include <list>

using namespace std;

//========================================================================================================================================================================================
void DL_generuj(vector<vector<int>>&temp, int r)
{
	vector<int> t_X;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			t_X.push_back(j + r);
		}
		temp.push_back(t_X);
		t_X.clear();
	}
}

void DL_wyswietl(const vector<vector<int>>temp)
{
	for (auto i : temp)
	{
		for (auto j : i)
		{
			if (j == 0) { /*cout << " " <<" "<< " ";*/ }
			else { cout << " " << j << " "; }
		}
		cout << endl;
	}
	cout << endl;
}

void LP_usun(vector<int>&temp, int liczba_do_usuniecia)
{
	for (int i = 0; i < temp.size(); i++)
	{
		if (temp[i] == liczba_do_usuniecia)
		{
			temp[i] = 0;
		}
	}
}

bool LP_czy_jest(const vector<int>temp, const int szukana)
{
	bool czyJest = false;
	for (int i = 0; i < temp.size(); i++)
	{
		if (temp[i] == szukana) { czyJest = true; }
	}
	return czyJest;
}

//========================================================================================================================================================================================

void wypelnij_sektor(Plansza*temp, int sektor, vector<vector<int>>&dostepne_liczby, vector<vector<int>>&liczby_Pionowo, vector<vector<int>>&liczby_Poziomo, bool& czyWszystkie)
{
	int DL_pozycja = 0;
	int liczba = 0;
	int licznik = 0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (temp->PlanszaSektor(i, j) == sektor)
			{
				while (true)
				{
					DL_pozycja = rand() % dostepne_liczby[sektor].size();
					liczba = dostepne_liczby[sektor][DL_pozycja];
					if (LP_czy_jest(liczby_Pionowo[j], liczba + 1) == true && LP_czy_jest(liczby_Poziomo[i], liczba + 1) == true) { break; }
					else if (licznik > 100) { liczba = -45; czyWszystkie = false; break; }
					licznik++;
				}
				dostepne_liczby[sektor].erase(dostepne_liczby[sektor].begin() + DL_pozycja);
				LP_usun(liczby_Pionowo[j], liczba + 1);
				LP_usun(liczby_Poziomo[i], liczba + 1);

				temp->PlanszaU(i, j, (char)liczba - 207);

			}
		}
	}
	if (czyWszystkie != false) { czyWszystkie = true; }
}


void wyczysc_sektor(Plansza*temp, int sektor, vector<vector<int>>&dostepne_liczby, vector<vector<int>>&liczby_Pionowo, vector<vector<int>>&liczby_Poziomo)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (temp->PlanszaSektor(i, j) == sektor)
			{
				dostepne_liczby[sektor].push_back(temp->akcesP(i, j).getChar() - 49);
				liczby_Pionowo[j].push_back(temp->akcesP(i, j).getChar() - 49);
				liczby_Poziomo[i].push_back(temp->akcesP(i, j).getChar() - 49);
				temp->PlanszaU(i, j, (char)1 - 207);
			}
		}
	}

}

//========================================================================================================================================================================================

void wypelnij_drugim_sposobem(Plansza*temp, bool &czyWszystkie)
{
	int liczba = 0;
	vector<vector<int>>dostepne_liczby;
	DL_generuj(dostepne_liczby, 0);

	vector<vector<int>>liczby_Pionowo;
	DL_generuj(liczby_Pionowo, 1);

	vector<vector<int>>liczby_Poziomo;
	DL_generuj(liczby_Poziomo, 1);

	//DL_wyswietl(dostepne_liczby);
	//DL_wyswietl(liczby_Pionowo);

	int r = temp->taPlansza.size();
	int DL_pozycja = 0;

	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < r; j++)
		{
			if (temp->PlanszaSektor(i, j) == 0)
			{
				DL_pozycja = rand() % dostepne_liczby[0].size();
				liczba = dostepne_liczby[0][DL_pozycja];
				dostepne_liczby[0].erase(dostepne_liczby[0].begin() + DL_pozycja);
				LP_usun(liczby_Pionowo[j], liczba + 1);
				LP_usun(liczby_Poziomo[i], liczba + 1);

				temp->PlanszaU(i, j, (char)liczba - 207);
			}//przekatna 0

			else if (temp->PlanszaSektor(i, j) == 4)
			{
				DL_pozycja = rand() % dostepne_liczby[4].size();
				liczba = dostepne_liczby[4][DL_pozycja];
				dostepne_liczby[4].erase(dostepne_liczby[4].begin() + DL_pozycja);
				LP_usun(liczby_Pionowo[j], liczba + 1);
				LP_usun(liczby_Poziomo[i], liczba + 1);

				temp->PlanszaU(i, j, (char)liczba - 207);
			}//przekatna 4

			else if (temp->PlanszaSektor(i, j) == 8)
			{
				DL_pozycja = rand() % dostepne_liczby[8].size();
				liczba = dostepne_liczby[8][DL_pozycja];
				dostepne_liczby[8].erase(dostepne_liczby[8].begin() + DL_pozycja);
				LP_usun(liczby_Pionowo[j], liczba + 1);
				LP_usun(liczby_Poziomo[i], liczba + 1);
				temp->PlanszaU(i, j, (char)liczba - 207);

			}//przekatna 8
		}
	}
	bool sukces[7];

	wypelnij_sektor(temp, 2, dostepne_liczby, liczby_Pionowo, liczby_Poziomo, sukces[1]);
	wypelnij_sektor(temp, 1, dostepne_liczby, liczby_Pionowo, liczby_Poziomo, sukces[0]);
	wypelnij_sektor(temp, 6, dostepne_liczby, liczby_Pionowo, liczby_Poziomo, sukces[5]);
	wypelnij_sektor(temp, 3, dostepne_liczby, liczby_Pionowo, liczby_Poziomo, sukces[2]);
	wypelnij_sektor(temp, 5, dostepne_liczby, liczby_Pionowo, liczby_Poziomo, sukces[4]);
	wypelnij_sektor(temp, 7, dostepne_liczby, liczby_Pionowo, liczby_Poziomo, sukces[6]);

	for (int i = 0; i < 7; i++)
	{
		if (sukces[i] == false)
		{
			wyczysc_sektor(temp, i + 1, dostepne_liczby, liczby_Pionowo, liczby_Poziomo);
			wypelnij_sektor(temp, i + 1, dostepne_liczby, liczby_Pionowo, liczby_Poziomo, sukces[i]);
		}
	}
	czyWszystkie = true;
	for (int i = 0; i < 7; i++)
	{
		if (sukces[i] == false) { czyWszystkie = false; break; }
	}

	//DL_wyswietl(dostepne_liczby);
	//DL_wyswietl(liczby_Pionowo);
}

//========================================================================================================================================================================================
int main()
{
	srand(time(NULL));
	int licznik = 0;
	bool czyWszystkie = false;
	Plansza *S2;
	while (true)
	{
		S2 = new Plansza();
		while (true)
		{
			wypelnij_drugim_sposobem(S2, czyWszystkie);
			
			if (licznik == 1) { cout << "." << endl; }
			else if (licznik == 2) { cout << ".." << endl; }
			else if (licznik == 3) { cout << "..." << endl; }
			else if (licznik == 5) { cout << "....." << endl; }
			else if (licznik == 7) { cout << "........" << endl; }
			else if (licznik == 10) { cout << "............" << endl; licznik = 0; }
			licznik++;
			if (czyWszystkie == true) { break; }
		}
		cout << " Wygenerowano pomyslnie !" << endl;
		S2->wyswietl(1);// 1 losowo zakryte pola
		cout << endl << endl;

		getchar();
		S2->wyswietl(0);// 0 pelne rozwiazanie
		getchar();
		delete(S2);
		system("cls");
	}
	
	return 0;
}
