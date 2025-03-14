#include "Service.h"

Service::Service(AbstractRepository& repo, ListaNotificare &listaNotificare) : repo(repo){
    this->listaNotificare=listaNotificare;
}

void Service::adaugareLocatar(const int apartament, string &proprietar, const int suprafata, string &tip) {
    if (Validator::valideazaLocatar(apartament,proprietar,suprafata,tip)) {
        if (!repo.cautareApartament(apartament)) {
            Locatar locatar = Locatar(apartament,proprietar,suprafata,tip);
            repo.adaugareLocatar(locatar);
            UndoActions.push_back(new UndoAdauga (repo, locatar));
        }
        else {
            string ex = "Apartament deja existent!\n";
            throw Error(ex);
        }
    }
}

void Service::stergereLocatar(const int& apartament) {
    if (!repo.cautareApartament(apartament)){
        string ex="Apartament inexistent!\n";
        throw Error(ex);
    }
    UndoActions.push_back(new UndoSterge(repo, repo.copiaza_locatar(apartament)));
    repo.stergereLocatar(apartament);
}

void Service::actualizareLocatar(const int apartament, string &proprietar, const int suprafata, string &tip) {
    if (!repo.cautareApartament(apartament)){
        string ex{"Apartament inexistent!\n"};
        throw Error(ex);
    }
    UndoActions.push_back(new UndoModificare(repo,repo.extrageApartament(apartament)));
    repo.actualizareLocatar(apartament,proprietar,suprafata, tip);
}

vector<Locatar> Service::extrage_Locatari(){
    return repo.extrage_Locatari();
}

vector<Locatar> Service::filtreaza_locatari_tip_service(string &tip){
    vector<Locatar> lista_extrasa=repo.extrage_Locatari();
    vector<Locatar> lista_filtrata;
    copy_if(lista_extrasa.begin(), lista_extrasa.end(), back_inserter(lista_filtrata),  [&tip](Locatar &locatar)->bool{
        return locatar.get_tip()==tip;});
    return lista_filtrata;
}

vector<Locatar> Service::filtreaza_locatari_sup_service(const int& sup){
    vector<Locatar> lista_extrasa=repo.extrage_Locatari();
    vector<Locatar> lista_filtrata;
    copy_if(lista_extrasa.begin(), lista_extrasa.end(), back_inserter(lista_filtrata),  [&sup](Locatar &locatar)->bool{
        return locatar.get_suprafata()<=sup;});
    return lista_filtrata;
}

vector<Locatar> Service::sorteaza_locatari_nume_service(){
    vector<Locatar> lista_sortata=repo.extrage_Locatari();
    sort(lista_sortata.begin(),lista_sortata.end(),
         [](const Locatar &a, const Locatar&b)->bool{return a.get_proprietar()<b.get_proprietar();});
    return lista_sortata;}

vector<Locatar> Service::sorteaza_locatari_suprafata_service(){
    vector<Locatar> lista_sortata=repo.extrage_Locatari();
    sort(lista_sortata.begin(),lista_sortata.end(),
         [](const Locatar &a, const Locatar&b)->bool{return a.get_suprafata()<b.get_suprafata();});
    return lista_sortata;}

vector<Locatar> Service::sorteaza_locatari_tip_suprafata_service(){
    vector<Locatar> lista_sortata=repo.extrage_Locatari();
    sort(lista_sortata.begin(),lista_sortata.end(),
         [](const Locatar &a, const Locatar&b)->bool{if (a.get_tip()==b.get_tip()){return a.get_suprafata()<b.get_suprafata();} return a.get_tip()<b.get_tip();});
    return lista_sortata;}

void Service::goleste_lista_notificari(){
    listaNotificare.goleste_lista();
    notify();
}

void Service::adauga_lista_notificari(const int& nr_apartament){
    if (repo.cautareApartament(nr_apartament)) {
        if (listaNotificare.cautare_apartament(nr_apartament))
            throw Error("Apartament deja inregistrat!\n");
        Locatar &apartament = repo.extrageApartament(nr_apartament);
        listaNotificare.adauga_in_lista(apartament);
        notify();
    }
    else
        throw Error("Apartamentul nu este inregistrat!\n");
}

int Service::get_size_lista_notificari(){
    return listaNotificare.size();
}

int Service::get_random_apartamente(const int& nr_apartamente){
    int res=listaNotificare.genereaza_lista(nr_apartamente,repo.extrage_Locatari());
    notify();
    return res;
}

void Service::export_CSV(const std::string& file_path){
    listaNotificare.export_CSV(file_path);
}

unordered_map<string,int> Service::extrage_frecvente(){
    return repo.extrage_frecvente();
}

void Service::write_ListaLocatari_to_file(){
    repo.write_ListaLocatari_to_file();
}

void Service::doUndo() {
    if (UndoActions.empty())
        throw Error("Nu exista operatii la care sa dau undo!\n");
    auto pointer=UndoActions.back();
    UndoActions.back()->doUndo();
    delete pointer;
    UndoActions.pop_back();
}

Locatar Service::extrage_Locatar(const int& nr_ap){
    auto lst = extrage_Locatari();
    for (const auto& loc : lst){
        if (loc.get_apartament()==nr_ap)
            return loc;
    }
    throw (Error("Nu exista locatarul!"));
}

vector<Locatar> Service::get_lista_notificare(){
    return listaNotificare.get_lista_notificare();
}

Service::~Service(){
    for (auto pointer : UndoActions)
        delete pointer;
    UndoActions.clear();
}