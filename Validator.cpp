#include "Validator.h"

bool Validator::valideazaLocatar(const int apartament, const string &proprietar, const int suprafata,const string &tip) {
    string erori;
    if (apartament<=0)
        erori+="Apartament <=0\n";
    if (tip.empty())
        erori+="Tip vid!\n";
    if (proprietar.empty())
        erori+="Proprietar vid!\n";
    if (suprafata<=0)
        erori+="Suprafata <=0!\n";
    if (erori.empty())
        return true;
    throw Error(erori);
}