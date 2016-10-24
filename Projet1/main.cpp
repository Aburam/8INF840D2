
#include "Membre.h"
#include "Arbre.cpp"

void addMember(Arbre<Membre>* arb) {
	char* nom = new char[19];
	char* prenom = new char[19];
	char* couleurYeux = new char[9];
	char* dateNaissance = new char[9];
	char genre = 0;
	char* reponsePrenom = new char[19];
	char* reponseNom = new char[19];

	cout << "Bonjour, quel est le nom de la personne à rajouter ?" << endl;
	cin >> nom;
	cout << "Quel est son prenom" << endl;
	cin >> prenom;
	cout << "Quel est son genre (M/F) ?" << endl;
	cin >> genre;
	cout << "Quelle est la couleur de ses yeux" << endl;
	cin >> couleurYeux;
	cout << "Quelle est sa date de naissance (jj/mm/yyyy)" << endl;
	cin >> dateNaissance;

	Membre newMember(prenom, nom, genre, couleurYeux, dateNaissance);

	

	cout << "De quelle personne est-il le parent ? (Prenom, Nom)";
	cin >> reponsePrenom >> reponseNom;
	Membre childMember = arb->getMembre(reponseNom, reponsePrenom);
	try {
		arb->inserer(newMember, &childMember);
	}
	catch (exception& e) {
		cout << e.what() << endl;
	}
	
}

void calculate(const Arbre<Membre>* arb) {
	char reponse = 0;
	cout << " Que voulez-vous calculer ?" << endl;
	cout << " 1) taille" << endl;
	cout << " 2) hauteur" << endl;
	cout << " 3) Nombre de feuilles" << endl;
	cout << " 4) Nombre de noeuds" << endl;
	cin >> reponse;

	switch (reponse) {
		case '1':
			cout << "Taille : " << arb->taille() << endl;
			break;
		case '2':
			cout << "Hauteur : " << arb->hauteur() << endl;
			break;
		case '3':
			cout << "Nombre de feuilles : " << arb->nbFeuilles() << endl;
			break;
		case '4':
			cout << "Nombre de noeuds : " << arb->nbNoeuds() << endl;
	}
}

void listEyes(const Arbre<Membre>* arb) {
	char* couleurYeux = new char[10];
	cout << "Entrez une couleur d'yeux : " << endl;
	cin >> couleurYeux;
	arb->listEyes(couleurYeux);
	delete couleurYeux;
}

void listEyesFrom(const Arbre<Membre> * arb) {
	char* nom = new char[20];
	char* prenom = new char[20];
	char* couleurYeux = new char[10];

	cout << "A partir de quelle personne voulez-vous lister les ancetres qui ont les memes yeux (Prenom Nom)" << endl;
	cin >> prenom >> nom;
	cout << "Entrez une couleur d'yeux : " << endl;
	cin >> couleurYeux;

	Membre membre = arb->getMembre(nom, prenom);
	arb->listEyes(couleurYeux, &membre);

	delete nom, prenom, couleurYeux;

}

void calculateAge(const Arbre<Membre> * arb) {
	double ageAverage = arb->ageAverage();
	cout << "age moyen de l'arbre : " << ageAverage << endl;
}

void listGenealogicFrom(const Arbre<Membre> * arb) {
	char* nom = new char[20];
	char* prenom = new char[20];
	char parcours = 0;

	cout << "Quel parcours voulez-vous effectuer ?" << endl;
	cout << "1) Parcours pre-fixe" << endl;
	cout << "2) Parcours post-fixe" << endl;
	cout << "3) Parcours in-fixe" << endl;
	cin >> parcours;

	cout << "A partir de quelle personne voulez-vous lister les ancetres (prenom nom)" << endl;
	cin >> prenom >> nom;
	const Membre& membre = arb->getMembre(nom, prenom);

	switch (parcours) {
		case '1':
			arb->parcourirPreOrdre(membre);
			break;
		case '2':
			arb->parcourirPostOrdre(membre);
			break;
		case '3':
			arb->parcourirInOrdre(membre);
	}

	delete nom, prenom;


}

int main() {
	

	Arbre<Membre>* arb = new Arbre<Membre>();
	
	try {



		Membre moi("Jean", "Durand", 'M', "bleu", "25/12/1994");
		arb->inserer(moi);
		Membre pere("Martin", "Durand", 'M', "bleu", "06/01/1968");
		arb->inserer(pere, &moi);
		Membre mere("Charlotte", "Vaubert", 'F', "marron", "27/06/1970");
		Membre gpere1("Gerard", "Durand", 'M', "bleu", "01/01/1937");
		Membre gmere2("Louise", "Maillet", 'F', "marron", "01/08/1935");
		Membre gpere2("Jacob", "Vaubert", 'M', "marron", "31/12/1937");
		arb->inserer(mere, &moi);
		arb->inserer(gmere2, &mere);
		arb->inserer(gpere1, &pere);
		arb->inserer(gpere2, &mere);
		cout << "Parcours pre-ordre : ";
		arb->parcourirPreOrdre(arb->getRacine());
		cout << "Parcours post-ordre : ";
		arb->parcourirPostOrdre(arb->getRacine());
		cout << "Parcours in-ordre : ";
		arb->parcourirInOrdre(arb->getRacine());
	}
	catch (exception& e) {
		cout << e.what() << endl;
	}
	//addMember(arb);


	char reponse = 0;
	while(reponse != '7') {
		cout << "\nOperations possibles : " << endl;
		cout << "1) Ajouter un nouveau membre" << endl;
		cout << "2) Calculer la taille de l'arbre genealogique" << endl;
		cout << "3) Pour une couleur d'yeux entree par l'utilisateur, lister les personnes ayant cette couleur" << endl;
		cout << "4) Pour une couleur d'yeux entree par l'utilisateur, permet de lister tous les ancetres (ainsi que lui-meme) qui ont la meme couleur" << endl;
		cout << "5) Calculer la moyenne d'age" << endl;
		cout << "6) Lister les ancetres d'une personne" << endl;
		cout << "7) Quitter le programme" << endl;
		cin >> reponse;

		try {
			switch (reponse) {
			case '1':

			case '2':
				calculate(arb);
				break;
			case '3':
				listEyes(arb);
				break;
			case '4':
				listEyesFrom(arb);
				break;
			case '5':
				calculateAge(arb);
				break;
			case '6':
				listGenealogicFrom(arb);
				break;
			}
		}
		catch(exception& e) {
			cout << e.what() << endl;
		}
	}

	delete arb;



	return EXIT_SUCCESS;
}