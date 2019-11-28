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

string TraductionEntier(string entier);

int main()
{
    double d;

    while( cin >> d ) {
        cout << montantEnVaudois(d) << endl;
    }

    return 0;
}

string TraductionEntier(int entier, int iLongueurEntier){

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
       "cinqante",
       "soixante",
       "septante",
       "huitante",
       "nonante",
   };

   const int CENT = 0;

    string strResultat = "";

    int centaineCalcul = entier/100;
    int dizaineCalcul = (entier - (centaineCalcul*100))/10;
    int uniteCalcul = entier - (dizaineCalcul*10 + centaineCalcul*100);

    switch(iLongueurEntier)
    {
        case 3:
            if(centaineCalcul != 1){
                strResultat += unite[centaineCalcul] + " " + dizaines[CENT] + " ";
            }else{
                strResultat += dizaines[CENT] + " ";
            }
        case 2:
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

string montantEnVaudois(double dblMontant){

    int iEntier = dblMontant;
    float fDecimal = dblMontant - iEntier;
    int iDecimal = fDecimal*100;

    string strEntier = to_string(iEntier);
    string strDecimal = to_string(iDecimal);


    return TraductionEntier(iEntier,strEntier.length());

}