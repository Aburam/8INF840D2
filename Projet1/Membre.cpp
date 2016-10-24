#include "Membre.h"
#include <iostream>
#include <time.h>
#include <sstream>
#include <stdio.h>
#define timegm _mkgmtime






Membre::Membre(char * prenom, char * nom, char genre, char * couleurYeux, char * dateNaissance, char * dateDeces)
{
	m_prenom = prenom;
	m_nom = nom;
	m_genre = genre;
	m_couleurYeux = couleurYeux;
	m_dateNaissance = dateNaissance;
	m_dateDeces = dateDeces;
}

Membre::~Membre()
{
}

const char * Membre::getNom() const
{
	return m_nom;
}

const char * Membre::getPrenom() const
{
	return m_prenom;
}

const char Membre::getGenre() const
{
	return m_genre;
}

const char * Membre::getCouleurYeux() const
{
	return m_couleurYeux;
}

const char * Membre::getDateNaissance() const
{
	return m_dateNaissance;
}

const char * Membre::getDateDeces() const
{
	return m_dateDeces;
}

const int Membre::getAge() const
{
	int t1, t2;

	struct tm tmdate;
	memset(&tmdate, 0, sizeof(struct tm)); // *****

	tmdate.tm_mday = atoi(&m_dateNaissance[0]);
	tmdate.tm_mon = atoi(&m_dateNaissance[3]) - 1;
	tmdate.tm_year = atoi(&m_dateNaissance[6]) - 1900;
	
	t1 = tmdate.tm_year;

	if (m_dateDeces != 0) {
		tmdate.tm_mday = atoi(&m_dateDeces[0]);
		tmdate.tm_mon = atoi(&m_dateDeces[3]) - 1;
		tmdate.tm_year = atoi(&m_dateDeces[6]) - 1900;
	}
	else {
		time_t today = time(0);
		localtime_s(&tmdate, &today);
	}
	t2 = tmdate.tm_year;
	return t2-t1;
}

std::ostream & operator<<(std::ostream & os, Membre const & membre)
{

	os << membre.getPrenom() << " " << membre.getNom() << " (" << membre.getCouleurYeux() << ", "
		<< membre.getDateNaissance();
	if (membre.getDateDeces() != 0) {
		os << ", " << membre.getDateDeces();
	}
	os << ")";
	return os;
}

bool Membre::operator==(const Membre & a)
{
	if (m_nom == a.getNom() && m_prenom == a.getPrenom() && m_couleurYeux == a.getCouleurYeux() && m_dateNaissance == a.getDateNaissance() && m_genre == a.getGenre())
		return true;
	return false;
}

bool Membre::operator>(const Membre & a)
{
	return (a. getGenre() == 'F') ? true : false;
}
