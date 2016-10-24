#include "Arbre.h"

template<typename T>
Arbre<T>::Arbre()
{
	m_racine = 0;
	m_taille = 0;
}

template<typename T>
Arbre<T>::Arbre(const Arbre & arbre)
{
	m_racine = arbre.getRacine();
	m_taille = arbre.taille();
}

template<typename T>
Arbre<T>::~Arbre()
{
	if (!estVide()) {
		_auxEnlever(m_racine);
	}
}

template<typename T>
void Arbre<T>::inserer(const T & data, T* enfant = 0) throw(std::logic_error)
{
	if (appartient(data) == 1) {
		throw logic_error("existant: ce membre a déjà été ajouté à l'arbre");
	}
	else if (estVide()==1) {
		m_racine = new Noeud(data);
		++m_taille;
	}
	else {
		Noeud* noeudEnf = _auxAppartient(m_racine, *enfant);

		if (noeudEnf != 0) {
			_auxInserer(noeudEnf, data);
		}
		else {
			throw logic_error("renseignements nécessaire : on ne connait pas le fils");
		}
	}
	
	
}

template<typename T>
void Arbre<T>::enlever(const T & data)
{
	Noeud* noeudEnf = _auxAppartient(m_racine, data);
	if (noeudEnf != 0) {
		_auxEnlever(noeudEnf);
	}
	else
		throw logic_error("Enlever: l'element nest pas présent au sein de l'arbre!");
}

template<typename T>
bool Arbre<T>::estVide() const
{
	return (m_taille == 0) ? true : false;
}

template<typename T>
int Arbre<T>::taille() const
{
	return m_taille;
}

template<typename T>
int Arbre<T>::nbNoeuds() const
{
	return _nbNoeuds(m_racine);
}



template<typename T>
int Arbre<T>::nbFeuilles() const
{
	return _nbFeuilles(m_racine);
}

template<typename T>
int Arbre<T>::hauteur() const throw(std::logic_error)
{
	if (m_taille == 0)
		throw logic_error("hauteur: l'arbre est vide!\n");
	return _hauteurParcours(m_racine);
}

template<typename T>
bool Arbre<T>::appartient(const T &data) const
{
	return _auxAppartient(m_racine, data) != 0;
}

template<typename T>
const T& Arbre<T>::fils(const T& el) const throw(std::logic_error)
{
	Noeud* noeudDeEl = _auxAppartient(m_racine, el);
	Noeud* filsDeEl = _fils(m_racine, noeudDeEl);
	if (filsDeEl == 0) {
		throw logic_error("fils: le fils n'existe pas\n")
	}
	return filsDeEl->data;
}

template<typename T>
const T& Arbre<T>::getMembre(const char* nom, const char* prenom) const {
	if (estVide() == 0) {
		Noeud* elemMembre = _auxGetMembre(m_racine,nom, prenom);
		if (elemMembre != 0) {
			return elemMembre->data;
		}
	}
	throw logic_error("getMembre: ce membre n'est pas présent au sein de l'arbre\n");
}

template<typename T>
void Arbre<T>::parcourirPreOrdre(const T& arbreElem) const
{
	Noeud* arbre = _auxAppartient(m_racine, arbreElem);

	if (arbre != 0) {
		cout << arbre->data;
		aux_parcourirPreOrdre(arbre->pere);
		aux_parcourirPreOrdre(arbre->mere);
		cout <<"\n";
	}
}


template<typename T>
void Arbre<T>::parcourirInOrdre(const T& arbreElem) const
{
	Noeud* arbre = _auxAppartient(m_racine, arbreElem);

	if (arbre != 0) {
		aux_parcourirInOrdre(arbre->pere);
		cout << " | " << arbre->data;
		aux_parcourirInOrdre(arbre->mere);
		cout << "\n";
	}
}

template<typename T>
void Arbre<T>::listEyes(const char * eye, T * enfant = 0) const
{
	if (estVide() == 1 || enfant == 0) {
		_auxListEyes(m_racine, eye);
	}
	else {
		Noeud* noeudEnf = _auxAppartient(m_racine, *enfant);
		if (noeudEnf != 0)
			_auxListEyes(noeudEnf, eye);
		else
			cout << "cette Personne n'existe pas au sein de l'arbre";
	}
	cout << "\n";
}

template<typename T>
void Arbre<T>::parcourirPostOrdre(const T& arbreElem) const
{
	cout << arbreElem;
	Noeud* arbre = _auxAppartient(m_racine, arbreElem);

	if (arbre != 0) {
		aux_parcourirPostOrdre(arbre->pere);
		aux_parcourirPostOrdre(arbre->mere);
		cout << " | " << arbre->data << endl;
	}
}

template<typename T>
const double Arbre<T>::ageAverage() const
{
	if (estVide() == 1) {
		return 0;
	}
	return _auxAgeAverage(m_racine) / m_taille;
}



template<typename T>
const Arbre<T>& Arbre<T>::operator=(const Arbre & a)
{
	this->m_racine = a.getRacine();
	this->taille = a.getTaille();
}

template<typename T>
const T& Arbre<T>::getRacine() const
{
	return m_racine->data;
}





