#pragma once
#ifndef MEMBRE_H
#define MEMBRE_H

#include <iostream>
#include <string>

using namespace std;

/*
* Cette classe r�pr�sente une personne avec son nom, son pr�nom, son genre, la couleur de ses yeux, sa date de naissance et eventuellement sa date de d�ces
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

	//surcharge d'op�rateurs

	/*
	* return vrai si l'�l�ment a est de genre 'F', return faux dans le cas contraire
	*/
	bool operator> (const Membre & a);
	bool operator== (const Membre & a);


private :
	char* m_nom;
	char* m_prenom;
	char m_genre; //'F' pour f�minin, soit 'M' pour masculin 
	char* m_couleurYeux;
	char* m_dateNaissance;
	char* m_dateDeces; // �quivaut � 0 si le membre n'est pas d�c�d�

};

/*
 * Surcharge d'op�rateur : permet d'imprimer � l'�cran les caract�ristiques du membre en question
 */
std::ostream& operator<<(std::ostream& os, Membre const& membre);


#endif // !MEMBRE_H