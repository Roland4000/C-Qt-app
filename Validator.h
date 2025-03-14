//
// Created by Legion user on 03.05.2024.
//

#ifndef QTIE_VALIDATOR_H
#define QTIE_VALIDATOR_H


#include <string>
#include <exception>
#include "Error.h"
using namespace std;

class Validator {
public:
    /*
     * Functia valideaza datele pentru crearea unui produs.
     * Preconditii:
     *              tip = string != ""
     *              producator = string != ""
     *              model = string != ""
     *              pret = double > 0
     *              cantitate = int > 0
     * Postconditii: adevarat daca datele sunt valide
     * Arunca exceptie daca exista erori.
     */
    static bool valideazaLocatar(int apartament,const string &proprietar,int suprafata,const string &tip);
};


#endif //QTIE_VALIDATOR_H
