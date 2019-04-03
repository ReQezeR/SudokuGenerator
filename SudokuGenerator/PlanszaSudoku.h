#pragma once
#include "pch.h"
#include <iostream> 
#include <string>
#include <vector>

using namespace std;

class Pole
{
private:
	int x, y;//wspolrzedne pola
	char znak;//znak pola
	int sektor;//sektor pola
	bool czyPuste;//flaga

public:
	int wartoscPola;
	Pole();
	Pole(int x, int y, char znak);
	~Pole();

	char getChar()const { return znak; }//Getter: znak
	void setChar(char z) { this->znak = z; this->wartoscPola = static_cast<int>(z); }//Setter: znak
	void setSektor(int s) { this->sektor = s; }//Setter: sektor
	int getSektor() { return this->sektor; }
	int getX()const { return x; }//Getter: x
	int getY()const { return y; }//Getter: y
	void puste() { this->czyPuste = true; }//Setter: czyPuste(tak)
	void pelne() { this->czyPuste = false; }//Setter: czyPuste(nie)
	bool statusP() { return czyPuste; }
};





class Plansza : private Pole
{
private:
	string nazwa;//nazwa planszy
	int rozmiarC;//rozmiar plus krawedzie
	int rozmiarR;//rozmiar planszy
	vector<vector<Pole>>Rozwiazanie;//plansza z rozwiazaniem
public:
	vector<vector<Pole>>taPlansza;//plansza
	//Konstruktor / Destruktor
	Plansza();
	~Plansza() {}

	//Settery i Gettery
	string getNazwa()const { return nazwa; }//Getter: nazwa
	int getRC()const { return rozmiarC; }//Getter: rozmiarC(alkowity)
	int getR()const { return rozmiarR; }//Getter: rozmiar R(oboczy)
	void setN(string n) { this->nazwa = n; }//Setter: nazwa

	//Metody
	vector<vector<Pole>>generujPlansze(int r);
	//Pole startPoint() { int x, y; x = los(rozmiarR); y = los(rozmiarR); taPlansza[x][y].setChar('D'); return taPlansza[x][y]; }
	void PlanszaU(int x, int y, char znak);
	char PlanszaU(int x, int y);
	int PlanszaW(int x, int y);
	int PlanszaSektor(int x, int y)
	{
		return taPlansza[x][y].getSektor();
	}

	Pole akcesP(int x, int y) { return taPlansza[x][y]; }
	void wyswietl(int tryb);

	int los(int zakres);
};

