//
// Created by Legion user on 03.05.2024.
//

#ifndef QTIE_TESTE_H
#define QTIE_TESTE_H

#include <string>
#include "Domain.h"
#include "Repository.h"
#include "Validator.h"
#include "Service.h"
#include "Error.h"
#include <cassert>
#include "ListaNotificare.h"

class Teste {
public:
    static void run_all_tests();

private:
    static void test_creaza_locatar();
    static void test_adaugare_stergere_Locatar_repo();
    static void test_actualizare_Locatar_repo();
    static void test_validare_Locatar();
    static void test_cautareID();
    static void test_adaugare_stergere_Locatar_service();
    static void test_actualizare_Locatar_service();
    static void test_eroare();
    static void test_copiere_VD();
    static void test_constructor_copiere_locatar();
    static void test_filtrare_locatari_tip_service();
    static void test_filtrare_locatari_sup_service();
    static void test_sortare_locatari_nume_service();
    static void test_sortare_locatari_suprafata_service();
    static void test_sortare_locatari_tip_suprafata_service();
    static void test_lista_notificare_adaugare_golire();
    static void test_generare_lista_random();
    static void test_export_CSV();
    static void test_extrage_frecvente();
    static void test_Undo();
    static void test_export_ListaLocatari();
    static void test_copiere_afisare_stergere_modificare_filelocatar();
};


#endif //QTIE_TESTE_H
