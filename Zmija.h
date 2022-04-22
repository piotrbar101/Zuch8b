#pragma once
#include <iostream> 
#include <string>
using namespace std;

class Zmija
{	
protected:
	int punktyZycia = 8;
	int sila_ataku = 3;
	int poziom_ochrony = 3;

public:
	virtual ~Zmija() {};
	bool czyZyje() const { return punktyZycia > 0; }
	int jaki_poziom_ochrony() const { return poziom_ochrony; }

	virtual int wykonaj_atak(int poziom_ochrony_przeciwnika) const = 0;
	void przyjmij_atak(int obrazenia);

	virtual void info(ostream&) const = 0;
	friend ostream& operator<<(ostream&, const Zmija&);
};

class Zmija_Zwyczjna : public Zmija
{
protected:
	virtual int ugryzienie() const;
public:
	int wykonaj_atak(int poziom_ochrony_przeciwnika) const;
	void info(ostream&) const;
};

class Zmija_Jadowita : public Zmija_Zwyczjna
{
	static int ile_zmij;
	const int numer_zmiji;
protected:
	int ugryzienie() const override;
	int zatrucie() const;
public:
	Zmija_Jadowita();
	int wykonaj_atak(int poziom_ochrony_przeciwnika) const;
	void info(ostream&) const;

};