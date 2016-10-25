#pragma once
#ifndef ARBRE_H
#define ARBRE_H

#include <iostream>
#include <exception>
#include "Membre.h"

using namespace std;


//Structure d'arbre binaire adaptée pour la généalogie veticale
template<typename T>
class Arbre
{
public:
	//constructeurs et destructeurs
	Arbre();
	Arbre(const Arbre& arbre);
	~Arbre();

	/**
	 * @param data : element à rajouter dans l'arbre
	 * @param enfant : represente le noeud dans l'arbre auquel va se racorder le nouvel element en tant que fils gauche ou fils droit
	 */
	void inserer(const T & data, T* enfant = 0) throw(logic_error);

	/**
	 * @param data : element à enlever dans l'arbre, tout ses successeurs seront aussi enlevés
	 */
	void enlever(const T& data);

	/**
	 * @return true si la taille de l'arbre = 0 
	 */
	bool estVide() const;

	/**
	 * @return la taille de l'arbre
	 */
	int taille() const;

	/**
	 * @return l'element du premier noeud de l'arbre
	 */
	const T& getRacine() const;

	/**
	 * @return le nombre total de noeud
	 */
	int nbNoeuds() const;

	/**
	 * @return le nombre total de feuilles au sein de l'arbre
	 */
	int nbFeuilles() const;

	/**
	 * @return le niveau de l'arbre, return 0 si une racine seulement est présente, return 1 s'il y a au plus les parents de la racine et ainsi de suite
	 */
	int hauteur() const;

	/**
	 * @param data: l'élément à rechercher au sein de l'arbre
	 * @return true si l'element data est retrouvé au sein de l'arbre
	 */
	bool appartient(const T & data) const;

	/**
	 * @param el: l'élément représentant le père ou la mère de l'élement recherché
	 * @return l'element retrouvé au dessus du noeud de l'élement el
	 */
	const T & fils(const T & el) const throw(logic_error);

	/**
	 * @param nom : le nom du membre recherché
	 * @param prenom : le prenom du membre recherché
	 * @return un objet de la classe Membre présent dans l'arbre et représentant le membre recherché
	 */
	const T & getMembre(const char * nom, const char * prenom) const;

	//Parcours


	void parcourirPreOrdre(const T& arbreElem) const;
	void parcourirPostOrdre(const T& arbreElem) const;
	void parcourirInOrdre(const T& arbreElem) const;

	/**
	 * @param eye : correspond au filtre de la recherche des elements dans l'arbre ayant l'attribut couleurYeux correspondant
	 * @param enfant :  represente le noeud dans l'arbre auquel on va commencer la rechercher, si il est équivalent à NULL alors on part de la racine
	 */
	void listEyes(const char * eye, T* enfant = 0) const;

	/**
	 * Calcule la moyenne d'age des elements de l'arbre
	 * @return la valeur représentant la moyenne d'age
	 */
	const double ageAverage() const;

	//surcharge d'opérateurs
	const Arbre<T>& operator = (const Arbre & a);

private:
	// classe interne définissant les noeuds de l'arbre
	class Noeud {
	public:
		
		T data; //l'élément associé au noeud
		Noeud* pere; //représente en réalité le fils gauche d'un noeud au sein d'un arbre binaire, ici c'est le père pour la coherence de l'arbre genealogique
		Noeud* mere; //représente en réalité le fils droit d'un noeud au sein d'un arbre binaire, ici c'est la mère pour la coherence de l'arbre genealogique
		//constructeur du noeud
		Noeud(const T& data_item, Noeud* father = 0, Noeud* mother = 0) : data(data_item), pere(father), mere(mother) {}

		//surcharge d'opérateurs
		const Noeud& operator =(const Noeud& node) {
			element = node.data;
			pere = node.pere;
			mere = node.mere;
			return *this;
		}
	};



	/**
	 * permet d'insérer un nouveau noeud à  partir d'un autre
	 * @see inserer()
	 */
	void _auxInserer(Noeud * arbre, const T & data);

	/*
	 * fonction recursive, supprime tout les noeud successeurs de celui passé en parametre, puis supprime ce dernier aussi
	 * @see enlever()
	 */
	void _auxEnlever(Noeud * arbre);

	/*
	 *  fonction recursive récupérant le noeud contenant l'élément passé en parametre
	 *  @see appartient()
	 */
	typename Arbre<T>::Noeud * _auxAppartient(Noeud * arbre, const T & data) const;
	
	/*
	 * fonction recursive
	 * @see nbNoeud()
	 */
	int _nbNoeuds(Noeud * arb) const;

	/*
	 * fonction recursive
	 * @see nbFeuilles()
	 */
	int _nbFeuilles(Noeud * arb) const;

   /*
	* fonction recursive
	* @see hauteur()
	*/
	int _hauteurParcours(Noeud * arb) const;
	typename Arbre<T>::Noeud* _fils(Noeud* arb, Noeud* sArb);
	typename Arbre<T>::Noeud * _auxGetMembre(Noeud * arbre, const char * nom, const char * prenom) const;

	//parcours
	/*
	 * Fonction récursive associée au parcours prefixe d'un arbre
	 * @see parcourirPreOrdre
	 */
	void aux_parcourirPreOrdre(Noeud * arbre) const;

    /*
	 * Fonction récursive associée au parcours postfixe d'un arbre
	 * @see parcourirPostOrdre
	 */
	void aux_parcourirPostOrdre(Noeud * arbre) const;
	
	/*
	 * Fonction récursive associée au parcours enfixe d'un arbre
	 * @see parcourirInOrdre
	 */
	void aux_parcourirInOrdre(Noeud * arbre) const;

	/*
	 * fonction récursive affichant les elements sucessifs du noeud possédant un attribut couleurYeux dont la valeur est égale à eye
	 * @see listEyes
	 */
	void _auxListEyes(Noeud * arbre, const char * eye) const;

	/*
	 * fonction recursive sommant l'age total des éléments contenu dans les noeuds successeurs de celui passé en paramètre
	 * @see ageAverage
	 */
	int _auxAgeAverage(Noeud * arbre) const;



	Noeud* m_racine; //pointeur sur la racine de l'arbre
	int m_taille; //cardinalité de l'arbre
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