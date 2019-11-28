#include <string>
#include <iostream>

using namespace std;

string montantEnVaudois(double montant);

int main()
{
    double d;
    
    while( cin >> d ) {
        cout << montantEnVaudois(d) << endl;
    }
    
    return 0;
}