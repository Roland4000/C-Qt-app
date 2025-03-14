//
// Created by Legion user on 03.05.2024.
//

#ifndef QTIE_SERVICE_H
#define QTIE_SERVICE_H


#include "Repository.h"
#include "Validator.h"
#include "Domain.h"
#include "Error.h"
#include <algorithm>
#include "ListaNotificare.h"
#include <unordered_map>
#include "Undo.h"
#include <memory>
#include "Observer.h"

using namespace std;

class Service : public Observable{
public:
    Service(AbstractRepository& repo,ListaNotificare &listaNotificare);
    /*
     * Functia creeaza un Locatar cu datele transmise ca parametrii, il valideaza si
     * adauga daca nu exista deja un Locatar cu acelasi id.
     * Preconditii: apartament = int > 0
     *              tip = string != ""
     *              producator = string != ""
     *              model = string != ""
     *              pret = double > 0
     *              cantitate = int > 0
     * Postconditii: adevarat
     * Arunca exceptie daca id se afla deja in lista sau datele sunt invalide.
     */
    void adaugareLocatar(int apartament, string &proprietar, int suprafata, string &tip);
    /*
     * Functia cauta un id in lista de Locatare si sterge Locatarul cu id-ul respectiv daca il gaseste.
     * Preconditii: id = int > 0
     * Postconditii: adevarat
     * Arunca exceptie daca nu exista un Locatar cu id-ul respectiv.
     */
    void stergereLocatar(const int& apartament);
    /*
     * Functia actualizeaza un Locatar cu date noi daca sunt valide.
     * Preconditii: id = int > 0
     *              pret = double > 0 sau =-1
     *              cantitate = int > 0 sau =-1
     * Postconditii: adevarat
     * Arunca exceptie daca datele sunt invalide sau nu exista Locatar in lista cu id-ul id
     */
    void actualizareLocatar(int apartament, string &proprietar, int suprafata, string &tip);
    /*
     * Functia returneaza un vector cu Locatarele din repo.
     * Preconditii: adevarat
     * Postconditii: vector<Locatar>
     */
    vector<Locatar> extrage_Locatari();
    /*
* Functia returneaza o lista cu tipul tip.
* Preconditii: adevarat
* Postconditii: vector<Locatar>
*/
    vector<Locatar> filtreaza_locatari_tip_service(string& tip);
    /*
     * Functia returneaza o lista cu apartamentele cu suprafata <sup.
     * Preconditii: sup = int > 0
     * Postconditii: vector<Locatar>
     */
    vector<Locatar> filtreaza_locatari_sup_service(const int& sup);
    /*
     * Functia returneaza lista sortata dupa numele proprietarilor
     * Preconditii: adevarat
     * Postconditii: vector<Locatar>
     */
    vector<Locatar> sorteaza_locatari_nume_service();
    /*
    * Functia returneaza lista sortata dupa suprafata
    * Preconditii: adevarat
    * Postconditii: vector<Locatar>
    */
    vector<Locatar> sorteaza_locatari_suprafata_service();
    /*
    * Functia returneaza lista sortata dupa tip si suprafata
    * Preconditii: adevarat
    * Postconditii: vector<Locatar>
    */
    vector<Locatar> sorteaza_locatari_tip_suprafata_service();
    /*
     * Functia goleste lista de notificari
     * Preconditii: adevarat
     * Postconditii: adevarat
     */
    void goleste_lista_notificari();
    /*
     * Functia adauga un apartament din repo dupa nr_apartament in lista de utilizatori
     * Precodntii: nr_apartament=int>0
     * Postconditii: adevarat
     * Arunca exceptie daca nu exista apartament cu nr_apartament
     */
    void adauga_lista_notificari(const int& nr_apartament);
    /*
     * Functia retunreaza numarul de elemente din ListaNotificare.
     * Preconditii: adevarat
     * Postconditii: int > 0
     */
    int get_size_lista_notificari();
    /*
     * Functia adauga in listaNotificare nr_apartamente apartamente
     * alese aleator din repo care nu se afla deja in listaNotificare
     * sau cate exista si nu sunt in listaNotificare daca nr_apartamente
     * este un numar prea mare.
     * Preconditii: nr_apartamente : int > 0
     * Postconditii: 0 daca operatia s-a efectuat corect, 1 in caz contrar
     */
    int get_random_apartamente(const int& nr_apartamente);
    /*
     * Functia salveaza lista de notificari in fisierul dat prin file_path
     * in format CSV.
     * Preconditii: file_path = string
     * Postconditii: adevarat
     */
    void export_CSV(const std::string& file_path);
    /*
     * Functia intoarce frecventa_tip.
     * Preconditii: adevarat
     * Postconditii: unordered_map<string,int>
     */
    unordered_map<string,int> extrage_frecvente();
    /*
     * Functia scrie ListaLocatari in fisierul dat in constructor.
     * Preconditii: adevarat
     * Postconditii: adevarat
     */
    void write_ListaLocatari_to_file();
    /*
     * Functia realizeaza undo pentru ultima operatie.
     * Preconditii: adevarat
     * Postconditii: adevarat
     * Arunca exceptie daca UndoActions este gol.
     */
    void doUndo();
    /*
     * Functia returneaza locatarul cu nr_ap din repo.
     * Preconditii: nr_ap >= 1
     * Postconditii: Locatar
     * Arunca exceptie daca nu exista un locatar cu nr_ap
     */
    Locatar extrage_Locatar(const int& nr_ap);
    /*
     * Functia returneaza lista de notificare.
     * Preconditii: adevarat
     * Postconditii: vector<Locatar>
     */
    vector<Locatar> get_lista_notificare();
    //destructor
    ~Service();
private:
    vector<ActiuneUndo*> UndoActions;
    AbstractRepository& repo;
    ListaNotificare listaNotificare;
};


#endif //QTIE_SERVICE_H
