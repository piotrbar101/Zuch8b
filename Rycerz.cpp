#include <iostream> 
using namespace std;
#include "Rycerz.h"
#include "Przedmiot.h"
#include "Bron.h"
#include "Zbroja.h"
#include "Artefakt.h"
#include "Zdolnosc.h"

// klasa Rycerz


Rycerz::Rycerz(string imie, int punktyZycia, int zrecznosc, int sila, int poziom)
	: Postac(imie, punktyZycia, zrecznosc, sila, poziom)
{
	zdolnosci = new (nothrow) Zdolnosc*[liczba_zdolnosci];
	zdolnosci[0] = new Zdolnosc_Specjalna("Perfekcyjne ostrzenie broni", "dodatkwe 2 obrazenia", 2);
	zdolnosci[1] = new Zdolnosc_Uzdrawiajaca("Opatrywanie ran", "leczy 4 obrazenia", 4);

	for (int i = 0; i < wielkosc_ekwipunku; i++)
		ekwipunek[i] = nullptr;
	ekwipunek[0] = new Bron("Miecz", "doskonaly miecz", 5);
	ekwipunek[1] = new Przedmiot("Butelka", "butelka z woda pitna");
	ekwipunek[2] = new Bron("Sztylet", "sztylet krotki", 1);
	ekwipunek[3] = new Zbroja("Kolczuga", "klasyczna kolczuga", 3);
}

void Rycerz::info(ostream& out) const
{
	Postac::info(out);
	cout << "Modyfikator obrazen: " << modyfikator_obrazen << endl;
	cout << "Zdolnosci: " << endl;
	for (int i = 0; i < liczba_zdolnosci; i++)
		out << *zdolnosci[i];
	cout << "Ekwipunek: " << endl;
	for (int i = 0; i < wielkosc_ekwipunku; i++)
	{
		if (ekwipunek[i])
			out << i + 1 << ". " << *ekwipunek[i];
		else
			out << i + 1 << ". " << "pusto" << endl;
	}
}

Rycerz::~Rycerz()
{
	for (int i = 0; i < wielkosc_ekwipunku; i++)
		delete ekwipunek[i];

	for (int i = 0; i < liczba_zdolnosci; i++)
		delete zdolnosci[i];

	delete[] zdolnosci;
}

void Rycerz::przygotowanie()
{
	for (int i = 0; i < liczba_zdolnosci; i++)
	{
		zdolnosci[i]->dostepnosc = true;
		Zdolnosc_Specjalna* sp = dynamic_cast<Zdolnosc_Specjalna*>(zdolnosci[i]);
		if (sp)
			modyfikator_obrazen += sp->wykorzystaj_zdolnosc();
	}

	for (int i = 0; i < wielkosc_ekwipunku; i++)
	{
		Bron* b = dynamic_cast<Bron*>(ekwipunek[i]);
		Zbroja* z = dynamic_cast<Zbroja*>(ekwipunek[i]);
		Artefakt* a = dynamic_cast<Artefakt*>(ekwipunek[i]);
		if(!bron_w_reku && b)
		{
			bron_w_reku = b;
			ekwipunek[i] = nullptr;
		}
		else if(!zbroja_na_ciele && z)
		{
			zbroja_na_ciele = z;
			poziom_ochrony += z->wykorzystaj_ochrone();
			ekwipunek[i] = nullptr;
		}
		else if(!artefakt && a)
		{
			artefakt = a;
			switch (a->jaki_typ_artefaktu())
			{
			case Artefakt::typ_artefaktu::MODYFIKUJACY_ATAK:
				sila_ataku += a->wykorzystaj_artefakt();
				break;
			case Artefakt::typ_artefaktu::MODYFIKUJACY_OCHRONE:
				poziom_ochrony += a->wykorzystaj_artefakt();
				break;
			}
			ekwipunek[i] = nullptr;
		}
	}
}

int Rycerz::czy_dostepna_specjalna() const
{
	for (int i = 0; i < liczba_zdolnosci; i++)
		if (typeid(*zdolnosci[i]) == typeid(Zdolnosc_Specjalna) && zdolnosci[i]->dostepnosc)
			return i;
	return -1;
}

int Rycerz::czy_dostepna_uzdrawiajaca() const
{
	for (int i = 0; i < liczba_zdolnosci; i++)
		if (typeid(*zdolnosci[i]) == typeid(Zdolnosc_Uzdrawiajaca) && zdolnosci[i]->dostepnosc)
			return i;
	return -1;
}


int Rycerz::wykonaj_atak(int poziom_ochrony_przeciwnika)
{
	int uzdrawiajaca = czy_dostepna_uzdrawiajaca();
	if (punktyZycia < 10 && uzdrawiajaca != -1)
		punktyZycia += zdolnosci[uzdrawiajaca]->wykorzystaj_zdolnosc();
	else
	{
		int atak = Postac::wykonaj_atak(poziom_ochrony_przeciwnika);
		if (atak > 0)
			return atak + modyfikator_obrazen;
	}

	return 0;
}

