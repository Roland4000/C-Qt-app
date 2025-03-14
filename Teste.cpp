#include "Teste.h"
#include <iostream>
using namespace std;
void Teste::run_all_tests() {
    test_creaza_locatar();
    test_adaugare_stergere_Locatar_repo();
    test_actualizare_Locatar_repo();
    test_validare_Locatar();
    test_cautareID();
    test_adaugare_stergere_Locatar_service();
    test_actualizare_Locatar_service();
    test_eroare();
    test_copiere_VD();
    test_constructor_copiere_locatar();
    test_filtrare_locatari_tip_service();
    test_filtrare_locatari_sup_service();
    test_sortare_locatari_nume_service();
    test_sortare_locatari_suprafata_service();
    test_sortare_locatari_tip_suprafata_service();
    test_lista_notificare_adaugare_golire();
    test_generare_lista_random();
    test_export_CSV();
    test_extrage_frecvente();
    test_Undo();
    test_export_ListaLocatari();
    test_copiere_afisare_stergere_modificare_filelocatar();
}

void Teste::test_creaza_locatar() {
    int apartament=22;
    string proprietar="Ion";
    int suprafata=100;
    string tip="Da";
    Locatar locatar=Locatar(apartament,proprietar,suprafata,tip);
    assert(locatar.get_apartament()==apartament);
    assert(locatar.get_tip()==tip);
    assert(locatar.get_proprietar()==proprietar);
    assert(locatar.get_suprafata()==suprafata);

    string proprietar1="M";
    string tip1="Nu";
    locatar.set_tip(tip1);
    locatar.set_apartament(1);
    locatar.set_proprietar(proprietar1);
    locatar.set_suprafata(12);

    assert(locatar.get_apartament()==1);
    assert(locatar.get_tip()==tip1);
    assert(locatar.get_proprietar()==proprietar1);
    assert(locatar.get_suprafata()==12);

}

void Teste::test_adaugare_stergere_Locatar_repo(){
    int apartament=22;
    string proprietar="Ion";
    int suprafata=100;
    string tip="Da";
    Locatar locatar=Locatar(apartament,proprietar,suprafata,tip);
    assert(locatar.get_apartament()==apartament);
    assert(locatar.get_tip()==tip);
    assert(locatar.get_proprietar()==proprietar);
    assert(locatar.get_suprafata()==suprafata);

    Repository repo=Repository();
    repo.adaugareLocatar(locatar);
    vector<Locatar> Locatari=repo.extrage_Locatari();
    assert(Locatari.size()==1);
    assert(Locatari[0].get_tip()==tip);
    assert(Locatari[0].get_apartament()==apartament);
    assert(Locatari[0].get_proprietar()==proprietar);
    assert(Locatari[0].get_suprafata()==suprafata);
    repo.stergereLocatar(22);
    vector<Locatar> Locatari2=repo.extrage_Locatari();

    assert(Locatari2.empty());
}

void Teste::test_actualizare_Locatar_repo(){
    int apartament=22;
    string proprietar="Ion";
    int suprafata=100;
    string tip="Da";
    Locatar locatar=Locatar(apartament,proprietar,suprafata,tip);

    string proprietar1="M";
    string tip1="Nu";
    Locatar locatar1=Locatar(23,proprietar1,200,tip1);
    Repository repo=Repository();
    repo.adaugareLocatar(locatar);
    repo.adaugareLocatar(locatar1);
    repo.actualizareLocatar(23,"Gigel",120,"Kl");
    vector<Locatar> Locatari=repo.extrage_Locatari();
    assert(Locatari[1].get_suprafata()==120);
}

void Teste::test_validare_Locatar() {
    int apartament=22;
    string proprietar="Ion";
    string tip="duplex";
    int suprafata=100;
    assert(Validator::valideazaLocatar(apartament,proprietar,suprafata,tip)==true);
    try{
        Validator::valideazaLocatar(-1,"",-2,"");
        assert(false);
    }
    catch(Error& er){
        assert(er.getMessage()=="Apartament <=0\nTip vid!\nProprietar vid!\nSuprafata <=0!\n");
    }
}

void Teste::test_cautareID() {
    int apartament=22;
    string proprietar="Marcel";
    int suprafata=200;
    string tip="duplex";
    Locatar locatar=Locatar(apartament,proprietar,suprafata,tip);

    string proprietar1="Ion";
    string tip1="igen";

    Locatar Locatar1=Locatar(24,proprietar1,220,tip1);
    Repository repo=Repository();
    repo.adaugareLocatar(locatar);
    repo.adaugareLocatar(Locatar1);
    assert(repo.cautareApartament(24)==true);
    assert(repo.cautareApartament(4)==false);
}

void Teste::test_adaugare_stergere_Locatar_service(){
    Repository repo=Repository();
    ListaNotificare listaNotificare;
    Service service=Service(repo,listaNotificare);

    int apartament=22;
    string proprietar="Marcel";
    int suprafata=200;
    string tip="duplex";

    service.adaugareLocatar(apartament,proprietar,suprafata,tip);
    vector<Locatar> Locatare=service.extrage_Locatari();
    assert(Locatare.size()==1);
    assert(Locatare[0].get_suprafata()==suprafata);

    int apartament1=23;
    string proprietar1="Marceli";
    int suprafata1=2002;
    string tip1="dup";
    service.adaugareLocatar(apartament1,proprietar1,suprafata1,tip1);
    try {
        service.adaugareLocatar(apartament1, proprietar1, suprafata1, tip1);
    }
    catch(Error& er){
        assert(true);
    }
    try {
        service.stergereLocatar(6);
        assert(false);
    }
    catch(Error& er){
        assert(true);
    }
    service.stergereLocatar(22);
    vector<Locatar> Locatare1=service.extrage_Locatari();
    assert(Locatare1.size()==1);
}

void Teste::test_actualizare_Locatar_service(){
    Repository repo;
    string proprietar0="An";
    string tip0="su[";
    ListaNotificare listaNotificare;
    Service service=Service(repo,listaNotificare);
    try{
        service.actualizareLocatar(15,proprietar0,2020,tip0);
        assert(false);
    }
    catch(Error& er){
        assert(true);
    }

    int apartament=22;
    string proprietar="Marcel";
    int suprafata=200;
    string tip="duplex";
    string proprietar1="Ion";
    string tip1="sup";
    service.adaugareLocatar(apartament,proprietar,suprafata,tip);
    service.actualizareLocatar(22,proprietar1,202,tip1);
    vector<Locatar> locatari=service.extrage_Locatari();
    assert(locatari[0].get_suprafata()==202);
    assert(locatari[0].get_proprietar()=="Ion");
}

void Teste::test_eroare() {
    Error er= Error("Eroare de sistem");
    assert("Eroare de sistem"==er.getMessage());
}

void Teste::test_copiere_VD() {
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    vector<int> v2=v;
    assert(v2[0]==v[0]);
}


void Teste::test_constructor_copiere_locatar() {
    Locatar l = Locatar();
    string m="M";
    string d="D";
    Locatar l1(23,m,23,d);
    Locatar l2 = l1;
    assert(l2.get_suprafata()==l1.get_suprafata());
}

void Teste::test_filtrare_locatari_tip_service(){
    Repository repo=Repository();
    ListaNotificare listaNotificare;
    Service service=Service(repo,listaNotificare);

    int apartament=22;
    string proprietar="Marcel";
    int suprafata=200;
    string tip="duplex";

    service.adaugareLocatar(apartament,proprietar,suprafata,tip);
    vector<Locatar> locatari=service.filtreaza_locatari_tip_service(tip);
    assert(locatari.size()==1);
}

void Teste::test_filtrare_locatari_sup_service(){
    Repository repo=Repository();
    ListaNotificare listaNotificare;
    Service service=Service(repo,listaNotificare);

    int apartament=22;
    string proprietar="Marcel";
    int suprafata=200;
    string tip="duplex";

    service.adaugareLocatar(apartament,proprietar,suprafata,tip);
    vector<Locatar> locatari=service.filtreaza_locatari_sup_service(220);
    assert(locatari.size()==1);
}

void Teste::test_sortare_locatari_nume_service(){
    Repository repo=Repository();
    ListaNotificare listaNotificare;
    Service service=Service(repo,listaNotificare);


    int apartament=22;
    string proprietar="Marcel";
    int suprafata=200;
    string tip="duplex";


    int apartament1=23;
    string proprietar1="Costi";
    int suprafata1=200;
    string tip1="duplex";

    service.adaugareLocatar(apartament,proprietar,suprafata,tip);
    service.adaugareLocatar(apartament1,proprietar1,suprafata1,tip1);
    vector<Locatar> locatari=service.sorteaza_locatari_nume_service();
    assert(locatari[0].get_proprietar()=="Costi");
    assert(locatari[1].get_proprietar()=="Marcel");
}
void Teste::test_sortare_locatari_suprafata_service(){
    Repository repo=Repository();
    ListaNotificare listaNotificare;
    Service service=Service(repo,listaNotificare);

    int apartament=22;
    string proprietar="Marcel";
    int suprafata=200;
    string tip="duplex";

    int apartament1=23;
    string proprietar1="Costi";
    int suprafata1=120;
    string tip1="duplex";

    service.adaugareLocatar(apartament,proprietar,suprafata,tip);
    service.adaugareLocatar(apartament1,proprietar1,suprafata1,tip1);
    vector<Locatar> locatari=service.sorteaza_locatari_suprafata_service();
    assert(locatari[0].get_proprietar()=="Costi");
    assert(locatari[1].get_proprietar()=="Marcel");
}
void Teste::test_sortare_locatari_tip_suprafata_service(){
    Repository repo=Repository();
    ListaNotificare listaNotificare;
    Service service=Service(repo,listaNotificare);

    int apartament2=22;
    string proprietar2="Ion";
    int suprafata2=120;
    string tip2="t";

    int apartament=23;
    string proprietar="Marcel";
    int suprafata=200;
    string tip="duplex";

    int apartament1=24;
    string proprietar1="Costi";
    int suprafata1=120;
    string tip1="duplex";

    service.adaugareLocatar(apartament2,proprietar2,suprafata2,tip2);
    service.adaugareLocatar(apartament,proprietar,suprafata,tip);
    service.adaugareLocatar(apartament1,proprietar1,suprafata1,tip1);
    vector<Locatar> locatari=service.sorteaza_locatari_tip_suprafata_service();
    assert(locatari[0].get_proprietar()=="Costi");
    assert(locatari[1].get_proprietar()=="Marcel");
    assert(locatari[2].get_proprietar()=="Ion");
}

void Teste::test_lista_notificare_adaugare_golire() {
    Repository repo = Repository();
    ListaNotificare listaNotificare = ListaNotificare();
    Service service = Service(repo, listaNotificare);
    int apartament = 5;
    int suprafata = 120;
    string nume = "Marcel";
    string tip = "duplex";
    service.adaugareLocatar(apartament, nume, suprafata, tip);
    try {
        service.adauga_lista_notificari(6);
        assert(false);
    }
    catch (Error &) {
        assert(true);
    }
    service.adauga_lista_notificari(5);
    try {
        service.adauga_lista_notificari(5);
        assert(false);
    }
    catch (Error &) {
        assert(true);
    }
    assert(service.get_size_lista_notificari() == 1);
    service.goleste_lista_notificari();
    assert(service.get_size_lista_notificari() == 0);
}

void Teste::test_generare_lista_random(){
    Repository repo = Repository();
    ListaNotificare listaNotificare = ListaNotificare();
    Service service = Service(repo, listaNotificare);

    int apartament = 5;
    int suprafata = 120;
    string nume = "Marcel";
    string tip = "duplex";
    service.adaugareLocatar(apartament, nume, suprafata, tip);

    int ap1=10;
    int sup1=150;
    string nume1="Mike";
    string tip1="da";
    service.adaugareLocatar(ap1,nume1,sup1,tip1);

    int ap2=15;
    int sup2=200;
    string nume2="Abel";
    string tip2="nu";
    service.adaugareLocatar(ap2,nume2,sup2,tip2);

    assert(service.get_random_apartamente(2)==0);

    vector<Locatar> listaNotificari=service.extrage_Locatari();
    assert(service.get_size_lista_notificari()==2);

    assert(service.get_random_apartamente(5)==1);
    assert(service.get_size_lista_notificari()==3);
    assert(service.get_size_lista_notificari()==3);

}
void Teste::test_export_CSV(){
    string path=R"(E:\Folders\UBB An 1 sem 2\LAB 8 OOP\testCSV.txt)";
    Repository repo = Repository();
    ListaNotificare listaNotificare = ListaNotificare();
    Service service = Service(repo, listaNotificare);

    int apartament = 5;
    int suprafata = 120;
    string nume = "Marcel";
    string tip = "duplex";
    service.adaugareLocatar(apartament, nume, suprafata, tip);

    int ap1=10;
    int sup1=150;
    string nume1="Mike";
    string tip1="da";
    service.adaugareLocatar(ap1,nume1,sup1,tip1);

    int ap2=15;
    int sup2=200;
    string nume2="Abel";
    string tip2="nu";
    service.adaugareLocatar(ap2,nume2,sup2,tip2);

    assert(service.get_random_apartamente(2)==0);

    vector<Locatar> listaNotificari=service.extrage_Locatari();
    assert(service.get_size_lista_notificari()==2);

    assert(service.get_random_apartamente(5)==1);
    assert(service.get_size_lista_notificari()==3);
    assert(service.get_size_lista_notificari()==3);

    service.export_CSV(path);
}

void Teste::test_extrage_frecvente(){
    Repository repo = Repository();
    ListaNotificare listaNotificare = ListaNotificare();
    Service service = Service(repo, listaNotificare);

    int apartament = 5;
    int suprafata = 120;
    string nume = "Marcel";
    string tip = "duplex";
    service.adaugareLocatar(apartament, nume, suprafata, tip);

    int ap1=10;
    int sup1=150;
    string nume1="Mike";
    string tip1="da";
    service.adaugareLocatar(ap1,nume1,sup1,tip1);

    int ap2=15;
    int sup2=200;
    string nume2="Abel";
    string tip2="da";
    service.adaugareLocatar(ap2,nume2,sup2,tip2);

    unordered_map<string,int> frecv=service.extrage_frecvente();
    assert(frecv["da"]==2);
    assert(frecv["duplex"]==1);
}

void Teste::test_Undo() {
    Repository repo = Repository();
    ListaNotificare listaNotificare = ListaNotificare();
    Service service = Service(repo, listaNotificare);

    int apartament = 5;
    int suprafata = 120;
    string nume = "Marcel";
    string tip = "duplex";
    try {
        service.doUndo();
        assert(false);
    }
    catch (Error&){
        assert(true);
    }

    service.adaugareLocatar(apartament, nume, suprafata, tip);

    service.doUndo();

    assert(service.extrage_Locatari().empty());

    service.adaugareLocatar(apartament, nume, suprafata, tip);
    service.stergereLocatar(5);
    service.doUndo();

    assert(service.extrage_Locatari().size()==1);

    string nume2="Ion";
    service.actualizareLocatar(5,nume2,suprafata,tip);
    assert(service.extrage_Locatari()[0].get_proprietar()=="Ion");

    service.doUndo();

    assert(service.extrage_Locatari()[0].get_proprietar()=="Marcel");
}

void Teste::test_export_ListaLocatari(){
    FileRepository repo = FileRepository(R"(E:\Folders\UBB An 1 sem 2\LAB 8 OOP\testexportListaLocatari.txt)");
    repo.clearFile();
    ListaNotificare listaNotificare = ListaNotificare();
    Service service = Service(repo, listaNotificare);

    int apartament = 5;
    int suprafata = 120;
    string nume = "Marcel";
    string tip = "duplex";
    service.adaugareLocatar(apartament, nume, suprafata, tip);
    service.write_ListaLocatari_to_file();
    FileRepository repo2 = repo;

}

void Teste::test_copiere_afisare_stergere_modificare_filelocatar(){
    int apartament = 5;
    int suprafata = 120;
    string nume = "Marcel";
    string tip = "duplex";
    Locatar loc = Locatar(apartament,nume,suprafata,tip);
    FileRepository repo = FileRepository(
            R"(E:\Folders\UBB An 1 sem 2\LAB 8 OOP\copiereAfisareLocatarTest.txt)");
    repo.clearFile();
    repo.adaugareLocatar(loc);
    try{
        repo.copiaza_locatar(22);
        assert(false);
    }
    catch (Error&){
        assert(true);
    }
    repo.write_ListaLocatari_to_file();
    try {
        repo.extrageApartament(28);
        assert(false);
    }
    catch(Error&){
        assert(true);
    }
    string nume2="Mirel";
    Locatar loc2=Locatar(9,nume2,200,tip);
    repo.adaugareLocatar(loc2);
    repo.actualizareLocatar(9,nume2,200,tip);
    assert(repo.extrage_Locatari()[1].get_proprietar()=="Mirel");
    repo.stergereLocatar(5);
    repo.stergereLocatar(9);
    assert(repo.extrage_Locatari().empty());
}