#include <iostream> 
using namespace std;
#include "Zmija.h"

int Zmija_Jadowita::ile_zmij = 0;

// Klasa Zmija

void Zmija::przyjmij_atak(int obrazenia)
{
	punktyZycia -= obrazenia;
}

ostream& operator<<(ostream& out, const Zmija& p)
{
	p.info(out);
	return out;
}

// Klasa Zmija_Zwyczjna

int Zmija_Zwyczjna::wykonaj_atak(int poziom_ochrony_przeciwnika) const
{
	if (sila_ataku > poziom_ochrony_przeciwnika)
		return ugryzienie();

	return 0;
}

void Zmija_Zwyczjna::info(ostream& out) const
{
	out << "Zmija Zwyczajna - poziom ochrony: " << poziom_ochrony << " punkty zycia: " << punktyZycia << '\n';
}

int Zmija_Zwyczjna::ugryzienie() const
{
	return 3;
}



// Klasa Zmija_Jadowita

Zmija_Jadowita::Zmija_Jadowita()
	: numer_zmiji{ ++ile_zmij }
{
	punktyZycia = 2 * punktyZycia;
	sila_ataku = 2 * sila_ataku;
	poziom_ochrony = 2 * poziom_ochrony;
}


int Zmija_Jadowita::wykonaj_atak(int poziom_ochrony_przeciwnika) const
{
	if (numer_zmiji % 2 == 0)
		return zatrucie();

	return Zmija_Zwyczjna::wykonaj_atak(poziom_ochrony_przeciwnika);
}

void Zmija_Jadowita::info(ostream& out) const
{
	out << "Zmija Jadowita - poziom ochrony: " << poziom_ochrony << " punkty zycia: " << punktyZycia << '\n';
}

int Zmija_Jadowita::ugryzienie() const
{
	return Zmija_Zwyczjna::ugryzienie()+2;
}

int Zmija_Jadowita::zatrucie() const
{
	return 2*ugryzienie();
}
