//
// Created by Legion user on 03.05.2024.
//

#ifndef QTIE_REPOSITORY_H
#define QTIE_REPOSITORY_H

#include "Domain.h"
#include <vector>
#include <utility>
#include <algorithm>
#include <fstream>
#include "Error.h"
#include <unordered_map>
using namespace std;

class AbstractRepository{
public:
    virtual void adaugareLocatar(const Locatar &Locatar) = 0;
    virtual void stergereLocatar(const int& apartament) = 0;
    virtual void actualizareLocatar(int apartament, string proprietar, int suprafata, string tip) = 0;
    virtual bool cautareApartament(const int& apartament) = 0;
    virtual vector<Locatar> extrage_Locatari() = 0;
    virtual Locatar& extrageApartament(const int& nr_apartament) = 0;
    virtual Locatar copiaza_locatar(const int& nr_apartament) = 0;
    virtual void write_ListaLocatari_to_file() = 0;
    virtual unordered_map<string,int> extrage_frecvente() = 0;
};

class Repository : public AbstractRepository {
public:
    unordered_map<string,int> extrage_frecvente() override;
    /*
     * Functia adauga un Locatar in ListaLocatari.
     * Preconditii: Locatar = un Locatar
     * Postconditii: adevarat
     */
    void adaugareLocatar(const Locatar &Locatar) override;
    /*
     * Functia sterge un Locatar din ListaLocatari.
     * Preconditii: apartament = int > 0
     * Postconditii: adevarat
     */
    void stergereLocatar(const int& apartament) override;
    /*
     * Functia actualizeaza Locatarul cu id-ul id si ii modifica pretul si cantitatea.
     * Pentru pret = -1, nu se modifica pretul, pentru cantitate =-1, nu se modifica cantitatea.
     * Preconditii:  pret = double >0 sau =-1, cantitate = int >0 sau =-1
     * Postconditii: adevarat
     */
    void actualizareLocatar(int apartament, string proprietar, int suprafata, string tip) override;
    /*
     * Functia ne returneaza adevarat sau fals daca exista un Locatar
     * cu apartamentul apartament in ListaLocatari sau nu.
     * Preconditii: apartament = int > 0
     * Postconditii: adevarat sau fals
     */
    bool cautareApartament(const int& apartament) override;
    /*
     * Functia returneaza lista de Locatari din repo.
     * Preconditii: adevarat
     * Postconditii: vector<Locatar>
     */
    vector<Locatar> extrage_Locatari() override;
    /*
     * Functia returneaza o referinta la apartamentul cu nr_apartament.
     * Preconditii: nr_apartament: int > 0
     * Postconditii: Locatar&
     */
    Locatar &extrageApartament(const int& nr_apartament) override;
    /*
     * Functia returneaza numarul de apartamente inregistrate de tipul tip.
     * Preconditii: tip = string
     *
     */
    void write_ListaLocatari_to_file() override{};
    /*
  * Functia intoarce o copie a locatarului cu nr_apartament din repo.
  * Preconditii: nr_apartament = int > 0
  * Postconditii: Locatar
  * Arunca exceptie daca nu exista un locatar cu nr_apartament dat ca parametru.
  */
    Locatar copiaza_locatar(const int& nr_apartament) override;

    Repository& operator=(Repository *obj){
        if (this!=obj){
            this->ListaLocatari.clear();
            for (const auto& locatar : obj->ListaLocatari)
                this->ListaLocatari.push_back(locatar);
        }
        return *this;
    }

    //Constructor
    Repository() = default;
    //Copy
    Repository(Repository& obj){
        *this=obj;
    }
    //Destructor
    ~Repository()=default;
protected:
    vector<Locatar> ListaLocatari;
    unordered_map<string,int> frecventa_tip;
};

class FileRepository : public Repository {
private :
    string path;
public:
    unordered_map<string,int> extrage_frecvente() override;
    /*
    * Clasa cere un string care sa reprezinte calea
    * fisierului unde se vor realiza salvarile.
    * Preconditii: path = string
    * Postconditii: adevarat
    */
    explicit FileRepository(const string& path);
    /*
     * Functia salveaza ListaLocatari in format CSV in fisierul cu pathul dat in
     * constructor.
     * Preconditii: adevarat
     * Postconditii: adevarat
     */
    void write_ListaLocatari_to_file() override;
    /*
     * Copy constructor.
     */
    FileRepository(const FileRepository& repo);
    /*
     * Destructor.
     */
    ~FileRepository()=default;
    /*
     * Default constructor.
     */
    FileRepository()=default;
    /*
     * Functia adauga un locatar in ListaLocatari si
     * actualizeaza lista in fisier.
     * Preconditii: locatar = Locatar
     * Postconditii: adevarat
     */
    void adaugareLocatar(const Locatar& locatar) override;
    /*
   * Functia sterge un Locatar din ListaLocatari si actualizeaza datele din fisier.
   * Preconditii: apartament = int > 0
   * Postconditii: adevarat
   */
    void stergereLocatar(const int& apartament) override;
    /*
     *  Functia schimba datele locatarului cu apartamentul dat ca
     *  parametru in celelalte date date prin parametrii.
     *  Preconditii: apartament = int > 0, suprafata = int > 0
     *  Postconditii: adevarat
     */
    void actualizareLocatar(int apartament, string proprietar, int suprafata, string tip) override;
    /*
    *   Functia goleste fisierul din path.
    */
    void clearFile();
private:
    /*
     *  Functia scrie in fisierul dat prin path datele din
     *  ListaLocatari.
     */
    void writeToFile();
    /*
     *  Functia citeste datele din fisierul dat prin path
     *  si le memoreaza in ListaLocatari.
     */
    void readFromFile();

    FileRepository& operator=(FileRepository *obj){
        if (this!=obj){
            this->ListaLocatari.clear();
            for (const auto& locatar : obj->extrage_Locatari())
                this->ListaLocatari.push_back(locatar);
            this->path=obj->path;
        }
        return *this;
    }
    unordered_map<string,int> frecventa_tip;
};


#endif //QTIE_REPOSITORY_H
