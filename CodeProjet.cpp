#include <iostream>
#include <string>
#include <math.h>
#include <limits>
using namespace std;

string tableau_dizaine[] = { "vingt", "trente", "quarante", "cinquante", "soixante", "quatre vingt" };
string tableau_onze[] = { "dix", "onze", "douze", "treize", "quatorze", "quinze", "seize", "dix sept", "dix huit", "dix neuf" };
string tableau_unite[] = { "un", "deux", "trois", "quatre", "cinq", "six", "sept", "huit", "neuf" };

//Rappel : val -> passage par valeur et adr -> passage par adresse

/*
    FP3 : saisieNombreEtVerification() 
    Auteur : Justin FERDINAND
    Date : 21/11/2021
    Valeur Ajoutée : Ce service permet à l’utilisateur de saisir un nombre et de vérifier que le nombre saisi soit bien compris entre 0.01 et 999 999 999, 99.
    Input : -----
    Output : réel sommeSaisie
*/
double saisieNombreEtVerification() { // Saisie de la somme la somme
    string message = "\nSomme saisie invalide, veuillez retaper dans le bon format votre somme : ";
    double sommeSaisie;
    cout << "\nSaisissez une somme comprise entre 1 centime et 1 milliard d'euros - 1 centime : ";
    while ( !(cin >> sommeSaisie) || sommeSaisie < 0.01 || sommeSaisie >= 1000000000 ) {
        if (cin.eof()) return false; // si des touches par defaut pour stopper sous windows sont saisies le prog se stop
        else
            if (cin.fail()) { // condition qui véfirie si l'erreur de typage s'est produite
                cout << message << endl; // envoie du message d'erreur
                cin.clear(); // on vide le contenu de cin 
                cin.ignore( numeric_limits<streamsize>::max(), '\n'); // supprime la ligne erronée
            } else cout << message << endl; // envoie le message d'erreur
    } return sommeSaisie;
}

/*
    FP1 : decomposeNombreInitial()
    Auteur : Justin FERDINAND
    Date : 21/11/2021
    Valeur Ajoutée : Ce service permet de décomposer le nombre initial dans un tableau d’entiers de 4 cases qui représente les millions, milliers, unités et centimes.
    Input : val réel nombre, adr entier tableauDecompose[4]
    Output : -----
*/
void decomposeNombreInitial(double nombre, int TableauDecompose[4]) { // décompose la somme donnée en un tableau de 4 cases
    // Par soucis de manipulation de grand nombre on découpe ce dernier en 2
    int partie_million_millier = nombre / 1000;
    double inter = ((nombre - (partie_million_millier * 1000)) * 100) + 0.1; // le + 0.1 évite la suppression du 1 par arrondissement
    int partie_centaine_centime = (int)(inter);

    for(int indiceActuel = 0; indiceActuel < 4; indiceActuel++) TableauDecompose[indiceActuel] = 0; // On initialise à 0 les valeurs du tableau

    // On remplace ces valeurs par la partie correspondante
    TableauDecompose[0] = (partie_million_millier / 1000); // million
    TableauDecompose[1] = (partie_million_millier % 1000); // millier

    TableauDecompose[2] = (partie_centaine_centime / 100); // centaine dizaine unite
    
    // centime + gestion du centime perdu dans la décomposition en 2 parties
    TableauDecompose[3] = (partie_centaine_centime % 100);
}

/*
    FS2.1 : redecompose() 
    Auteur : Justin FERDINAND
    Date : 21/11/2021
    Valeur Ajoutée : Ce service permet de décomposer chaque case du tableau issu de FP1 en un sous tableau de 3 cases comme suit : centaine – dizaine – unité.
    Input : val entier nombre, adr entier TableauRedecompose
    Output : -----
*/
void redecompose(int nombre, int TableauRedecompose[3]) { // redécompose chaque case en un tableau de 3 cases
    TableauRedecompose[2] = nombre % 10; //unite
    TableauRedecompose[1] = (nombre / 10) % 10; // dizaine
    TableauRedecompose[0] = floor(nombre / 100); // centaine -> ici floor() récupère la partie décimale uniquement
}

/*
    FT2.2.1 : traitementCasEt() 
    Auteur : Baptiste RISSE
    Date : 21/11/2021
    Valeur Ajoutée : Ce service permet de traiter les nombre composé de « et » comme « vingt et un » ou « soixante et un »… Il renvoie le résultat sous forme de string.
    Input : adr tableau d'entier nombre[3]
    Output : val chaine dizaine_lettre
*/
string traitementCasEt(int nombre[3]) { // traitement des cas "Et" -> vintg et un / soixante et un ...
    string dizaineEnLettre;
    for (int indiceActuel = 0; indiceActuel < 6; indiceActuel++) {
        if (nombre[1] - 2 == indiceActuel) {
            dizaineEnLettre = tableau_dizaine[indiceActuel];
            if (nombre[2] == 1) dizaineEnLettre += " et";            
        }
    }
    if (nombre[1] == 7) {
        dizaineEnLettre = tableau_dizaine[4];
        if (nombre[2] == 1) dizaineEnLettre += " et";
    }

    return dizaineEnLettre;
}

/*
    FT2.2.2 : traitementCasDix()
    Auteur : Baptiste RISSE
    Date : 21/11/2021
    Valeur Ajoutée : Ce service permet de gérer les cas où le nombre écrit fini par « dix » comme « soixante dix » et « quatre vingt dix » … Il renvoie le résultat sous forme de string.
    Input : vale entier dizaine
    Output : val chaine dizaine_lettre
*/
string traitementCasDix(int dizaine) { // traitement des cas "Dix" -> quatre vingt dix / soixante dix
    string dizaineEnLettre;
    if (dizaine == 1) dizaineEnLettre = "";
    else
        if (dizaine == 0) dizaineEnLettre = "";
        else
            if (dizaine == 8 || dizaine == 9) dizaineEnLettre = tableau_dizaine[5];
    
    return dizaineEnLettre;
}

/*
    FS2.2 : gestionDizaineUnite()
    Auteur : Baptiste RISSE
    Date : 21/11/2021
    Valeur Ajoutée : Ce service permet de traduire les dizaines et unités en toute lettre dans un tableau de string de 2 cases.
    Input : Adr entier nombre[3], adr chaine dizaine_unite_lettre[2]
    Output : -----
*/
void gestionDizaineUnite(int nombre[3], string dizaine_unite_lettre[2]) { // traduction d'un nombre 2 digit en toute lettre -> 21 : vingt et un via un tableau à 2 cases
    if (nombre[1] >= 2 && nombre[1] <= 7) 
        dizaine_unite_lettre[0] = traitementCasEt(nombre);
    else
        if (nombre[1] == 0 || nombre[1] == 8 || nombre[1] == 9)
            dizaine_unite_lettre[0] = traitementCasDix(nombre[1]);

    if (nombre[1] == 1 || nombre[1] == 7 || nombre[1] == 9) {
        for (int indiceActuel = 0; indiceActuel < 10; indiceActuel++) {
            if (nombre[2] == indiceActuel)
                dizaine_unite_lettre[1] = tableau_onze[indiceActuel];
        }
    } else {
        if ((nombre[1] == 0 || nombre[1] >= 2) && (nombre[1] <= 6 || nombre[1] == 8)) {
            for (int indiceActuel = 0; indiceActuel < 9; indiceActuel++) {
                if (nombre[2] - 1 == indiceActuel)
                    dizaine_unite_lettre[1] = tableau_unite[indiceActuel];
            }
        }
    }
}

/*
    FS2.3 : gestionCentaine()
    Auteur : Baptiste RISSE
    Date : 21/11/2021
    Valeur Ajoutée : Ce service permet de traduire le chiffre des centaines en toute lettre et renvoie le résultat au type string.
    Input : val entier centaine
    Output : val chaine centaine_lettre
*/
string gestionCentaine(int centaine) { // tradcution d'un nombre 1 digit en toute lettre -> 200 : deux cent (la gestion du 's' se fait ultèrieurement)
    string centaineEnLettre;
    for (int indiceActuel = 0; indiceActuel < 9; indiceActuel++) {
        if (centaine - 1 == indiceActuel) {
            if (centaine == 1)
                centaineEnLettre = "cent";
            else
                centaineEnLettre = tableau_unite[indiceActuel] + " cent";
        }
    }
    return centaineEnLettre;
}

/*
    FS2.4 : concatenationSommeDigitee()
    Auteur : Maël RHUIN
    Date : 21/11/2021
    Valeur Ajoutée : Ce service permet de concaténer les strings de FS2.2 avec celles de FS2.3 tout en gérant le pluriel selon les contraintes posées. Elle renvoie le résultat sous forme d’un string.
    Input : val chaine sommeDigitLettre[3], val entier sommeEntier[3]
    Output : chaine sommeDigitDeSortie
*/
string concatenationSommeDigitee(string sommeDigitLettre[3], int sommeEntier[3]) { // concaténation des 2 traitements précédent et implémentation du pluriel
    //Gestion Pluriel
    if ((sommeEntier[0] > 1) && (sommeEntier[1] == 0 && sommeEntier[2] == 0)) // pluriel de cent
        sommeDigitLettre[0] += "s";

    if (sommeEntier[1] == 8 && sommeEntier[2] == 0) // pluriel de vingt
        sommeDigitLettre[1] += "s";
    //Concaténation
    string sommeDigitDeSortie = "";
    for (int indiceActuel = 0; indiceActuel < 3; indiceActuel++) if (sommeDigitLettre[indiceActuel].length() > 0) sommeDigitDeSortie += sommeDigitLettre[indiceActuel] + " "; //concaténation des traitements après gestion du pluriel
    return sommeDigitDeSortie;
}

/*
    FP2 : traiteNombreDecompose() 
    Auteur : Baptiste RISSE
    Date : 21/11/2021
    Valeur Ajoutée : Ce service permet de traiter le nombre saisi de l’utilisateur une fois que celui-ci a été décomposé. Il retranscrit en toute lettre les valeurs du tableau passé en paramètre dans un tableau de string à 4 cases.
    Input : adr entier TableauSommeDecompose[4],adr chaine TableauSommeTraitee[4]
    Output : -----
*/
void traiteNombreDecompose(int TableauSommeDecompose[4], string TableauSommeTraitee[4]) { // Implémentation de toute les FS de FP2
    for (int indiceActuel = 0; indiceActuel < 4; indiceActuel++) {
        int TableauRedecomposeInter[3];
        redecompose(TableauSommeDecompose[indiceActuel], TableauRedecomposeInter);

        string TableauTraiteeInter[3];
        TableauTraiteeInter[0] = gestionCentaine(TableauRedecomposeInter[0]);
        
        string TableauGestionDizaineUnite[2];
        gestionDizaineUnite(TableauRedecomposeInter, TableauGestionDizaineUnite);

        TableauTraiteeInter[1] = TableauGestionDizaineUnite[0];
        TableauTraiteeInter[2] = TableauGestionDizaineUnite[1];

        string SommeTraiteeDigitee = concatenationSommeDigitee(TableauTraiteeInter, TableauRedecomposeInter);
        TableauSommeTraitee[indiceActuel] = SommeTraiteeDigitee;
    }
}

/*
    FS4.1 : ajoutMajuscule()
    Auteur : Maël Rhuin
    Date : 21/11/2021
    Valeur Ajoutée : Ce service permet d’ajouter une majuscule en début de proposition.
    Input : adr chaine TableauSommeEnLettre[4]
    Output : adr entier TableauInitial[4]
*/
void ajoutMajuscule(string TableauSommeEnLettre[4], int TableauInitial[4]) { // Implémentation d'une majuscule en début de proposition
    // Trouver la case pour la majuscule
    int indiceMajuscule = 0;

    for (int indiceActuel = 0; indiceActuel < 4; indiceActuel++) {
        if (TableauInitial[indiceActuel] > 0) break;
        indiceMajuscule++;
    }

    // Attribution de la majuscule
    string inter = TableauSommeEnLettre[indiceMajuscule];
    inter[0] = toupper(inter[0]);

    TableauSommeEnLettre[indiceMajuscule] = inter;
}

/*
    FP4 : afficheNombre() (ici affichage)
    Auteur : Maël RHUIN
    Date : 21/11/2021
    Valeur Ajoutée : Ce service permet d’afficher le nombre en toute lettre saisie par l’utilisateur après une re manipulation du tableau de string de FP2.
    Input : Adr chaine TableauSommeEnLettre[4], Adr entier TableauInitial[4], val entier sommeInitial
    Output : -----
*/
void affichage(string TableauSommeEnLettre[4], int TableauInitial[4], double sommeInitial) { // Affiche après une concaténation finale la somme en toute lettre
    // Ajout Majuscule
    ajoutMajuscule(TableauSommeEnLettre, TableauInitial);
    // Concaténation Finale
    string sommeFinalEnTouteLettre = "";
    if (TableauSommeEnLettre[0].length() > 0) { // gestion des millions
        sommeFinalEnTouteLettre += TableauSommeEnLettre[0] + ((TableauInitial[0] > 1) ? "millions" : "million") + " ";
        if ((TableauInitial[1] == 0) && (TableauInitial[2] == 0)) // seule la case million dans la partie entière est remplie 
            sommeFinalEnTouteLettre += "d'"; // danbs les cas où c'est un million [d']euros
    }

    if (TableauSommeEnLettre[1].length() > 0) // gestion des milliers
        sommeFinalEnTouteLettre += TableauSommeEnLettre[1] + "mille" + " ";

    if (TableauSommeEnLettre[2].length() > 0) // gestion des centaines dizaines unités
        sommeFinalEnTouteLettre += TableauSommeEnLettre[2];

    if (sommeInitial >= 1) { // gestion du mot euro(s) ou centime d'euro + ajout du point en fin de proposition
        sommeFinalEnTouteLettre += (sommeInitial == 1) ? "euro" : "euros";

        if (TableauSommeEnLettre[3].length() > 0)
            sommeFinalEnTouteLettre += " et " +  TableauSommeEnLettre[3] + ((TableauInitial[3] > 1) ? "centimes." : "centime.");
        
        else sommeFinalEnTouteLettre += ".";
    }

    if (sommeInitial < 1 && TableauSommeEnLettre[3].length() > 0) 
        sommeFinalEnTouteLettre += TableauSommeEnLettre[3] + ((TableauInitial[3] > 1) ? "centimes d'euro." : "centime d'euro.");

    cout << "\nSomme retranscrite : " << sommeFinalEnTouteLettre << endl; // Affichage à l'écran de la concaténation finale
}

// Utilisation et implémentation des fonctions pour répondre au sujet
int main() {
    bool boucleProgramme = true;

    while(boucleProgramme) { // Tant que l'utilisateur n'a pas fermé le programme celui-ci continue
        cout << "\n ============ Nouvelle Execution ============" << endl;

        double sommeUtilisateur = saisieNombreEtVerification(); // On demande une somme à l'utilisateur

        int TableauSommeADecompose[4];
        decomposeNombreInitial(sommeUtilisateur, TableauSommeADecompose); // On décompose la somme donnée en un tableau [ million millier centaine centime ]

        string TableauSommeDigiteeTraitee[4];
        traiteNombreDecompose(TableauSommeADecompose, TableauSommeDigiteeTraitee); // On traduit chaque case ce tableau en toute lettre

        affichage(TableauSommeDigiteeTraitee, TableauSommeADecompose, sommeUtilisateur); // On affiche après concaténation la somme en toute lettre

        cout << "\n============ Fin Execution ============" << endl;
    }

    system("pause");
    return 0;
}