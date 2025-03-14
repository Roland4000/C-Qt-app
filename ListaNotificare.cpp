#include "ListaNotificare.h"

void ListaNotificare::goleste_lista() {
    listaApartamente.clear();
}

void ListaNotificare::adauga_in_lista(Locatar &apartament) {
    listaApartamente.push_back(apartament);
}

int ListaNotificare::size(){
    return (int)listaApartamente.size();
}

int ListaNotificare::genereaza_lista(const int &nr_apartamente, const vector<Locatar>& lista_locatari) {
    vector<Locatar> locatari_neplasati;
    for (const auto& loc1 : lista_locatari) {
        bool situat=false;
        for (const auto& loc2: listaApartamente)
            if (loc1.get_proprietar()==loc2.get_proprietar())
                situat=true;
        if (!situat)
            locatari_neplasati.push_back(loc1);
    }
    int nr_loc=(int)locatari_neplasati.size();
    int rezultat_functie=0;
    if (nr_loc<nr_apartamente){
        rezultat_functie=1;
        for (const auto& loc : locatari_neplasati)
            listaApartamente.push_back(loc);
    }
    else{
        for (int i=0;i<nr_apartamente;i++){
            int size=(int)locatari_neplasati.size();
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, size-1);
            int randomNumber = dis(gen);
            listaApartamente.push_back(locatari_neplasati[randomNumber]);
            locatari_neplasati.erase(locatari_neplasati.begin()+randomNumber);
        }
    }
    return rezultat_functie;
}

void ListaNotificare::export_CSV(const std::string& file_path){
    std::ofstream fout = std::ofstream(file_path);
    for (const auto& apartament : listaApartamente)
        fout<<apartament.get_apartament()<<","<<apartament.get_proprietar()<<","<<apartament.get_suprafata()<<","<<apartament.get_tip()<<"\n";
    fout.close();
}
bool ListaNotificare::cautare_apartament(const int& nr_apartament){
    return any_of(listaApartamente.begin(),listaApartamente.end(),[&nr_apartament](const Locatar& a){return a.get_apartament()==nr_apartament;});
}

vector<Locatar> ListaNotificare::get_lista_notificare() {
    return listaApartamente;
}