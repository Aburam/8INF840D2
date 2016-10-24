#pragma once
#ifndef MEMBRE_H
#define MEMBRE_H

#include <iostream>
#include <string>

using namespace std;

class Membre
{
public:
	Membre(char* prenom, char* nom, char genre, char* couleurYeux, char* dateNaissance, char* dateDeces = nullptr );
	~Membre();

	const char* getNom() const;
	const char* getPrenom() const;
	const char getGenre() const;
	const char* getCouleurYeux() const;
	const char* getDateNaissance() const;
	const char * getDateDeces() const;
	const int getAge() const;

	//surcharge d'opérateurs
	bool operator> (const Membre & a);
	bool operator== (const Membre & a);


private :
	char* m_nom;
	char* m_prenom;
	char m_genre;
	char* m_couleurYeux;
	char* m_dateNaissance;
	char* m_dateDeces;

};

std::ostream& operator<<(std::ostream& os, Membre const& membre);


#endif // !MEMBRE_H