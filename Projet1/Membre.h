#pragma once
#ifndef MEMBRE_H
#define MEMBRE_H

#include <iostream>
#include <string>

using namespace std;

/*
* Cette classe réprésente une personne avec son nom, son prénom, son genre, la couleur de ses yeux, sa date de naissance et eventuellement sa date de déces
*/
class Membre
{
public:
	// constructeur
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

	/*
	* return vrai si l'élément a est de genre 'F', return faux dans le cas contraire
	*/
	bool operator> (const Membre & a);
	bool operator== (const Membre & a);


private :
	char* m_nom;
	char* m_prenom;
	char m_genre; //'F' pour féminin, soit 'M' pour masculin 
	char* m_couleurYeux;
	char* m_dateNaissance;
	char* m_dateDeces; // équivaut à 0 si le membre n'est pas décédé

};

/*
 * Surcharge d'opérateur : permet d'imprimer à l'écran les caractéristiques du membre en question
 */
std::ostream& operator<<(std::ostream& os, Membre const& membre);


#endif // !MEMBRE_H