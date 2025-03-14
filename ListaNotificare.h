//
// Created by Legion user on 03.05.2024.
//

#ifndef QTIE_LISTANOTIFICARE_H
#define QTIE_LISTANOTIFICARE_H

#include "Domain.h"
#include <vector>
#include <random>
#include <string>
#include <fstream>
#include <algorithm>

using std::vector;

class ListaNotificare {
private:
    vector<Locatar> listaApartamente;
public:
    ListaNotificare()=default;
    /*
     * Functia goleste listaApartamente.
     * Preconditii: adevarat.
     * Postconditii: adevarat.
     */
    void goleste_lista();
    /*
     * Functia adauga in lista un nou apartament.
     * Preconditii: apartament=Locatar&
     * Postconditii: adevarat
     */
    void adauga_in_lista(Locatar &apartament);
    /*
     * Functia populeaza lista de notificari cu nr_apartamente apartamente
     * extrase aleator din lista_locatari care nu se afla deja in lista de notificari.
     * Preconditii: nr_apartamente=int > 0, lista_locatari=vector<Locatar>
     * Postconditii: 0 daca operatia s-a efectuat corect, 1 daca nu au existat suficiente
     * apartamente ramase
     */
    int genereaza_lista(const int& nr_apartamente, const vector<Locatar>& lista_locatari);
    /*
     * Functia salveaza datele din lista de notificari in format CSV.
     * Preconditii: file_path = string
     * Postconditii: adevarat
     */
    void export_CSV(const std::string& file_path);
    /*
     * Functia returneaza o copie a listei de apartamente.
     * Preconditii: adevarat
     * Postconditii: vector<Locatar>
     */
    //vector<Locatar> extrage_listaNotificari();
    /*
     * Functia returneaza numarul de elemente al lui listaApartamente.
     * Preconditii: adevarat
     * Postconditii: int > 0
     */
    int size();
    /*
     * Functia returneaza true/false daca exista un apartament in listaApartamente
     * cu numarul de apartament dat ca parametru.
     * Preconditii: nr_apartament = int > 0
     * Postconditii: true daca exista, false daca nu exista
     */
    bool cautare_apartament(const int& nr_apartament);
    /*
     * Functia returneaza lista de notificare.
     * Preconditii: adevarat
     * Postconditii: vector<Locatar>
     */
    vector<Locatar> get_lista_notificare();
};




#endif //QTIE_LISTANOTIFICARE_H
