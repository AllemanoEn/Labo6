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

int main()
{
    double d;

    while( cin >> d ) {
        cout << montantEnVaudois(d) << endl;
    }

    return 0;
}

string montantEnVaudois(double dblMontant){

    string casSpeciaux[] = {
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
        "dix",
        "onze",
        "douze",
        "treize",
        "quatorze",
        "quinze",
        "seize",
        "dix-sept",
        "dix-huit",
        "dix-neuf",
        "vingt"
    };

    string strMontant = to_string(dblMontant);
    string strEntier, strDecimal;
    bool bPoint=false;

    for (int i = 0; i < strMontant.length()-1 ; ++i) {

        if(strMontant[i] == '.'){
            bPoint= true;
            continue; //Permet de ne pas mettre le "." dans la chaîne strDecimal
        }

        if(bPoint){
            //On ajoute les deux premier chiffre après la virgule et on sort de la boucle
            strDecimal += strMontant[i];
            strDecimal += strMontant[i+1];
            break;
        } else{
            strEntier += strMontant[i];
        }
    }
}