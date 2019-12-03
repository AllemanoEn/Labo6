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

string montantEnVaudois(double dblMontant){
    const int ARRONDIE = 0.0001;
    int iEntier = dblMontant;
    float fDecimal = dblMontant - iEntier;
    fDecimal += ARRONDIE;
    int iDecimal = fDecimal*100;

    int iCentaine = 0, iMillier = 0;

    string strResultat;

    string strEntier = to_string(iEntier);
    string strDecimal = to_string(iDecimal);

    string strMillier;
    string strCentaine;


    if(iEntier == 0) {

    }else {
        if (strEntier.length() <= 3) {
            strResultat = TraductionEntier(iEntier, strEntier.length(), false);

        } else {
            iMillier = iEntier / 1000;
            iCentaine = iEntier - iMillier * 1000;

            strMillier = to_string(iMillier);
            strCentaine = to_string(iCentaine);

            if (iMillier != 1) {
                strResultat = TraductionEntier(iMillier, strMillier.length(), true);
            }
            strResultat += " mille ";
            if (iCentaine != 0) { //Exeption x00'000
                strResultat += TraductionEntier(iCentaine, strCentaine.length(), false);
            }
        }

        if(iDecimal != 0){
            if (iEntier <= 1) {
                strResultat += " franc";
            } else {
                strResultat += " francs";
            }
        }

    }



    //Si il y a une décimal
    if(iDecimal>0.0)
    {
        strResultat += TraductionEntier(iDecimal,strDecimal.length(), false);
        //Si la décimal ne vaut 1 alors on affiche "centime" au lieu de "centimes"
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