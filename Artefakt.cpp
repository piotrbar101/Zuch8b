#include <iostream> 
using namespace std;
#include "Artefakt.h"

// klasa Artefakt

Artefakt::Artefakt(string nazwa, string opis, typ_artefaktu typ, int modyfikator)
	: Przedmiot{nazwa, opis}, modyfikator{modyfikator}, typ{typ}
{
}

int Artefakt::wykorzystaj_artefakt() const
{
	return modyfikator;
}

void Artefakt::info(ostream& out) const
{
	Przedmiot::info(out);
	out << " Modyfikator ";
	switch (typ)
	{
	case typ_artefaktu::MODYFIKUJACY_ATAK:
		out << "ataku";
		break;
	case typ_artefaktu::MODYFIKUJACY_OCHRONE:
		out << "obrony";
		break;
	}
	out << ": " << modyfikator;
}
