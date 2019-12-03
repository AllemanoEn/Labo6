/*
 -----------------------------------------------------------------------------------
 Laboratoire : 06
 Fichier     : lab6.cpp
 Auteur(s)   : Luca Zacheo, Enzo Allemano, David Darmanger
 Date        : 03/12/2019

 But         : Le but de ce laboratoire est de créer une fonction qui reçoit en entrée un nombre réel au format double, 
				et retourne une chaine de caractères au format string contenant en vaudois le montant correspondant exprimé en francs et centimes.
				Le français utilisé est celui utilisé dans le canton de Vaud, donc septante, huitante et nonante pour 70, 80 et 90.
			La fonction doit traiter correctement toutes les valeurs entre 0 francs et 999'999 francs et 99 centimes,
			en respectant les règles de la grammaire française. Cependant, n'utilisez pas les accents. Ecrivez donc zero et pas zéro.

 Remarque(s) :

 Compilateur : MinGW-g++ 6.3.0
 -----------------------------------------------------------------------------------
 */

#include <string>
#include <iostream>

using namespace std;

/**
 \brief Traduit des nombres réels en prix exprimés en vaudois
 \param[in] montant un réel compris entre 0 et 999999.99 CHF.
 \return une chaine de caractères indiquant en vaudois le prix
 en francs et centimes.
 \details Exemples:
 12.30  -> "douze francs et trente centimes"
 200.01 -> "deux cents francs et un centime"
 180    -> "cent huitante francs"
 1.80   -> "un franc et huitante centimes"
 0.20   -> "vingt centimes"
 0      -> "zéro franc"
 */
string montantEnVaudois(double dblMontant);

string TraductionEntier(string entier, int iLongueurEntier, bool bMillier);

int main()
{
    double d;

    while( cin >> d ) {
        cout << montantEnVaudois(d) << endl;
    }

    return 0;
}

/**
\brief Permet de transformer 3 chiffres en lettre
\param[in] entier int qui contient les chiffres
\param[in] iLongueurEntier int qui contient le nombre de chiffres
\param[in] bMillier bool qui permet de savoir si on travaille sur les milliers (ou les centaines et les décimales)
\return Retourne les nombres en lettres
\details Permet de "convertir" 3 chiffres en lettre. Gère les exceptions comme les "-" ou "et" entre les nombres.
*/
string TraductionEntier(int entier, int iLongueurEntier, bool bMillier){

    const string unite[] = {
            "zero",
            "un",
            "deux",
            "trois",
            "quatre",
            "cinq",
            "six",
            "sept",
            "huit",
            "neuf",
    };

    const string casSpeciaux[] = {
            "onze",
            "douze",
            "treize",
            "quatorze",
            "quinze",
            "seize",
            "dix-sept",
            "dix-huit",
            "dix-neuf"
    };

    const string dizaines[]{
            "cent",
            "dix",
            "vingt",
            "trente",
            "quarante",
            "cinquante",
            "soixante",
            "septante",
            "huitante",
            "nonante",
    };

    const int CENT = 0;

    string strResultat;

    int centaineCalcul = entier/100;
    int dizaineCalcul = (entier - (centaineCalcul*100))/10;
    int uniteCalcul = entier - (dizaineCalcul*10 + centaineCalcul*100);

    switch(iLongueurEntier)
    {
        case 3:
            if(centaineCalcul != 1 && dizaineCalcul == 0 && uniteCalcul == 0){

                if(bMillier){
                    strResultat += unite[centaineCalcul] + " " + dizaines[CENT];
                }else{
                    strResultat += unite[centaineCalcul] + " " + dizaines[CENT] + "s";
                }

                break;
            } else if (centaineCalcul == 1 && dizaineCalcul == 0 && uniteCalcul == 0){
                strResultat += dizaines[CENT];
                break;
            }else if (centaineCalcul == 1){
                strResultat += dizaines[CENT] + " ";
            }else{
                strResultat += unite[centaineCalcul] + " " + dizaines[CENT] + " ";
            }
        case 2:
            if(dizaineCalcul == 1 && uniteCalcul != 0){
                strResultat += casSpeciaux[uniteCalcul-1];
                break;
            }
            if(uniteCalcul == 0){
                strResultat += dizaines[dizaineCalcul];
                break;
            }else if(uniteCalcul == 1){
                strResultat += dizaines[dizaineCalcul] + " et ";
            }else{
                strResultat += dizaines[dizaineCalcul] + "-";
            }
        case 1:
            if(uniteCalcul == 1){
                strResultat += unite[uniteCalcul];
                break;
            }
            strResultat += unite[uniteCalcul];
            break;

        default:
            break;
    }
    return  strResultat;
}

/**
\brief permet de récupérer le nombre entré et appelle la fonction qui va convertir les nombres en lettre
\param[in] dblMontant double qui contient le montant entrée par l'utilisateur
\return Retourne la chaîne entière convertit en lettre (2.45 -> deux francs et quarante-cinq centimes)
\details Séparer le montant en millier, centaine et décimal. Cela est ensuite utilisé lors de l'appel
 à la fonction "TraductionEntier". On gère également les exeptions.
*/
string montantEnVaudois(double dblMontant){

    //Comme vu en cours, pour comparer des valeurs en float, on declare une variable qui nous permet d'arrondir en cas de décimals
    const int ARONDIE = 0.0001;
    //On garde uniquement la partie entière
    int iEntier = dblMontant;
    //On garde la partie décimals
    float fDecimal = dblMontant - iEntier;
    fDecimal += ARONDIE;
    int iDecimal = fDecimal*100;

    int iCentaine = 0, iMillier = 0;

    string strResultat;

    string strEntier = to_string(iEntier);
    string strDecimal = to_string(iDecimal);

    string strMillier;
    string strCentaine;


    if(iEntier != 0 || iDecimal == 0) {
        //On passe dans ce if, uniquement si il n'y a que des centaines
        if (strEntier.length() <= 3) {
            strResultat = TraductionEntier(iEntier, strEntier.length(), false);

        } else {
            //On passe içi si l'entier contient de centaines et des milliers

            iMillier = iEntier / 1000;
            iCentaine = iEntier - iMillier * 1000;

            strMillier = to_string(iMillier);
            strCentaine = to_string(iCentaine);

            //On passe içi uniquement si la valeur est différente de 1000
            if (iMillier != 1) {
                strResultat = TraductionEntier(iMillier, strMillier.length(), true);
            }
            strResultat += " mille ";
            if (iCentaine != 0) {
                //On passe içi si il n'y a pas de centaines
                strResultat += TraductionEntier(iCentaine, strCentaine.length(), false);
            }
        }

        if (iEntier <= 1) {
            strResultat += " franc";
        } else {
            strResultat += " francs";
        }

    }

    if(iEntier != 0 && iDecimal != 0){
        strResultat += " et ";
    }

    //Si il y a une décimal
    if(iDecimal>0.0)
    {
        strResultat += TraductionEntier(iDecimal,strDecimal.length(), false);

        //Si la décimal vaut 1 alors on affiche "centime" au lieu de "centimes"
        if(iDecimal==1)
        {
            strResultat += " centime";
        } else
        {
            strResultat += " centimes";
        }
    }

    return strResultat;
}