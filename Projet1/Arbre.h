#pragma once
#ifndef ARBRE_H
#define ARBRE_H

#include <iostream>
#include <exception>
#include "Membre.h"

using namespace std;



template<typename T>
class Arbre
{
public: //constructeurs et destructeurs
	Arbre();
	Arbre(const Arbre& arbre);
	~Arbre();

	void inserer(const T & data, T* enfant = 0) throw(logic_error);
	void enlever(const T& data);

	bool estVide() const;
	int taille() const;
	const T& getRacine() const;

	int nbNoeuds() const;
	int nbFeuilles() const;
	int hauteur() const;
	bool appartient(const T & data) const;
	const T & fils(const T & el) const throw(logic_error);
	const T & getMembre(const char * nom, const char * prenom) const;

	//Parcours

	void parcourirPreOrdre(const T& arbreElem) const;
	void parcourirPostOrdre(const T& arbreElem) const;
	void parcourirInOrdre(const T& arbreElem) const;

	void listEyes(const char * eye, T* enfant = 0) const;
	const double ageAverage() const;

	//surcharge d'opérateurs
	const Arbre<T>& operator = (const Arbre & a);

private:
	// classe
	class Noeud {
	public:
		T data;
		Noeud* pere;
		Noeud* mere;
		Noeud(const T& data_item, Noeud* father = 0, Noeud* mother = 0) : data(data_item), pere(father), mere(mother) {}

		const Noeud& operator =(const Noeud& node) {
			element = node.data;
			pere = node.pere;
			mere = node.mere;
			return *this;
		}
	};

	void _auxInserer(Noeud * arbre, const T & data);
	void _auxEnlever(Noeud * arbre);
	typename Arbre<T>::Noeud * _auxAppartient(Noeud * arbre, const T & data) const;
	int _nbNoeuds(Noeud * arb) const;
	int _nbFeuilles(Noeud * arb) const;
	int _hauteurParcours(Noeud * arb) const;
	typename Arbre<T>::Noeud* _fils(Noeud* arb, Noeud* sArb);
	typename Arbre<T>::Noeud * _auxGetMembre(Noeud * arbre, const char * nom, const char * prenom) const;

	//parcours
	void aux_parcourirPreOrdre(Noeud * arbre) const;
	void aux_parcourirPostOrdre(Noeud * arbre) const;
	void aux_parcourirInOrdre(Noeud * arbre) const;

	void _auxListEyes(Noeud * arbre, const char * eye) const;
	int _auxAgeAverage(Noeud * arbre) const;



	Noeud* m_racine; //pointeur sur la racine de l'arbre
	int m_taille;
	//cardinalité de l'arbre
};

template<typename T>
void Arbre<T>::_auxInserer(Noeud* arbre, const T& data) throw (const logic_error)
{
	if (arbre == 0)//cas arbre vide
	{
		arbre = new Noeud(data);
		++m_taille;
	}
	else if (arbre->data > data && arbre->mere == 0){//cas <
		arbre->mere = new Noeud(data);
		++m_taille;
	}
	else if (arbre->pere == 0) {//cas >
		arbre->pere = new Noeud(data);
		++m_taille;
	}
	else {
		throw logic_error("Cet enfant a déjà un parent");
	}
}

template<typename T>
void Arbre<T>::_auxEnlever(Noeud* arbre) {
	if (arbre != 0) {
		_auxEnlever(arbre->pere);
		_auxEnlever(arbre->mere);
		delete arbre;
		--m_taille;
	}
}

template<typename T>
typename Arbre<T>::Noeud * Arbre<T>::_auxAppartient(Noeud* arbre, const T& data) const
{
	if (arbre == 0)
		return 0;
	if (arbre->data == data)
		return arbre;
	Noeud* result = _auxAppartient(arbre->pere, data);
	if (result != 0) {
		return result;
	}
	return _auxAppartient(arbre->mere, data);
}

template<typename T>
int Arbre<T>::_nbNoeuds(Noeud* arb) const
{
	if (arb == 0)
		return 0;
	return _nbNoeuds(arb->pere) + _nbNoeuds(arb->mere) + 1;
}

template<typename T>
int Arbre<T>::_nbFeuilles(Noeud* arb) const
{
	int nbG(0), nbD(0);
	if (arb != 0)
	{
		if (arb->pere == 0 && arb->mere == 0)
			return 1;
		else
		{
			if (arb->pere != 0)
				nbG = _nbFeuilles(arb->pere);
			if (arb->mere != 0)
				nbD = _nbFeuilles(arb->mere);
		}
	}
	return nbG + nbD;
}

template<typename T>
int Arbre<T>::_hauteurParcours(Noeud * arb) const
{
	if (arb == 0)
		return -1;
	int hauteurMere = _hauteurParcours(arb->mere);
	int maxHauteur = _hauteurParcours(arb->pere);
	if (hauteurMere > maxHauteur) {
		maxHauteur = hauteurMere;
	}
	return 1 + maxHauteur;
}

template<typename T>
typename Arbre<T>::Noeud* Arbre<T>::_fils(Noeud* arb, Noeud * sArb)
{
	if (arb == 0 || sArb == arb || sArb == 0) {
		return 0;
	}
	else if (arb->data > sArb->data) {	//Si on recherche l'enfant d'une mere

		if (arb->mere = sArb)
			return arb;
	}
	if (arb->pere = sArb) { //Si on recherche l'enfant d'un pere
			return arb;
	}
	Noeud* result = _fils(arb->pere, sArb);
	if (result != 0) {
		return result;
	}
	return _fils(arb->mere, sArb);
}

template<typename T>
typename Arbre<T>::Noeud* Arbre<T>::_auxGetMembre(Noeud * arbre, const char* nom, const char* prenom) const{
	if (arbre == 0)
		return 0;
	if ((strcmp(arbre->data.getNom(), nom) == 0) && (strcmp(arbre->data.getPrenom(), prenom) == 0)) {
		return arbre;
	}
	else {
		Noeud* result = _auxGetMembre(arbre->pere, nom, prenom);
		if (result != 0) {
			return result;
		}
		return _auxGetMembre(arbre->mere, nom, prenom);
	}
}


template<typename T>
void Arbre<T>::aux_parcourirPreOrdre(Noeud* arbre) const
{
	if (arbre != 0) {
		cout << " | " << arbre->data;
		aux_parcourirPreOrdre(arbre->pere);
		aux_parcourirPreOrdre(arbre->mere);
	}
}

template<typename T>
void Arbre<T>::aux_parcourirPostOrdre(Noeud* arbre) const
{
	if (arbre != 0) {
		aux_parcourirPostOrdre(arbre->pere);
		aux_parcourirPostOrdre(arbre->mere);
		cout << " | " << arbre->data;

	}
}

template<typename T>
void Arbre<T>::aux_parcourirInOrdre(Noeud* arbre) const
{
	if (arbre != 0) {
		aux_parcourirInOrdre(arbre->pere);
		cout << " | " << arbre->data;
		aux_parcourirInOrdre(arbre->mere);
	}
}

template<typename T>
void Arbre<T>::_auxListEyes(Noeud* arbre, const char * eye) const
{

	if (arbre != 0) {
		if (strcmp(arbre->data.getCouleurYeux(), eye) == 0) {
			cout << arbre->data << " | ";
		}
		_auxListEyes(arbre->pere, eye);
		_auxListEyes(arbre->mere, eye);
	}
}

template<typename T>
int Arbre<T>::_auxAgeAverage(Noeud* arbre) const {
	if (arbre == 0) {
		return 0;
	}
	else {
		double ret = _auxAgeAverage(arbre->pere) + _auxAgeAverage(arbre->mere);
		ret += arbre->data.getAge();
		return ret;
	}
}

#endif // !ARBRE_H