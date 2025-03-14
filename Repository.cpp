#include "Repository.h"



void Repository::adaugareLocatar(const Locatar &locatar){
    frecventa_tip[locatar.get_tip()]++;
    ListaLocatari.push_back(locatar);
}

void Repository::stergereLocatar(const int &apartament) {
    for (int i=0;i<ListaLocatari.size();i++){
        if (ListaLocatari[i].get_apartament()==apartament)
        {
            frecventa_tip[ListaLocatari[i].get_tip()]--;
            ListaLocatari.erase(ListaLocatari.begin()+i);
            return;
        }
    }
}

void Repository::actualizareLocatar(const int apartament, string proprietar, const int suprafata, string tip){
    int it=0;
    while (it<ListaLocatari.size()&&ListaLocatari[it].get_apartament()!=apartament)
        it++;
    frecventa_tip[ListaLocatari[it].get_tip()]--;
    ListaLocatari[it].set_suprafata(suprafata);
    ListaLocatari[it].set_proprietar(proprietar);
    ListaLocatari[it].set_tip(tip);
    ListaLocatari[it].set_apartament(apartament);
    frecventa_tip[ListaLocatari[it].get_tip()]++;
}

bool Repository::cautareApartament(const int& apartament) {
    return any_of(ListaLocatari.begin(),ListaLocatari.end(),[&apartament](const Locatar& a){return a.get_apartament()==apartament;});

}

vector<Locatar> Repository::extrage_Locatari(){
    return ListaLocatari;
}

Locatar& Repository::extrageApartament(const int& nr_apartament){
    for (int i=0;i<ListaLocatari.size();i++)
        if (nr_apartament==ListaLocatari[i].get_apartament())
            return ListaLocatari[i];
    throw Error("Apartament inexistent!");
}

FileRepository::FileRepository(const std::string &path) {
    this->path=path;
    readFromFile();
    for (const auto& loc : ListaLocatari)
        frecventa_tip[loc.get_tip()]++;
}

void FileRepository::write_ListaLocatari_to_file() {
    std::ofstream f2 (path);
    for (const auto& loc : ListaLocatari)
        f2<<loc<<'\n';
    f2.close();
}

FileRepository::FileRepository (const FileRepository& repo) : Repository((Repository &) repo) {
    this->path=repo.path;
    for (const auto &loc : repo.ListaLocatari){
        ListaLocatari.push_back(loc);
    }
}

Locatar Repository::copiaza_locatar(const int& nr_apartament){
    auto loc=find_if(ListaLocatari.begin(),ListaLocatari.end(),[&nr_apartament](Locatar& loc){return loc.get_apartament()==nr_apartament;});
    if (loc!=ListaLocatari.end())
        return *loc;
    throw Error("Locatar inexistent!\n");
}

unordered_map<string, int> Repository::extrage_frecvente() {
    return frecventa_tip;
}

void FileRepository::adaugareLocatar(const Locatar& locatar){
    ListaLocatari.push_back(locatar);
    frecventa_tip[locatar.get_tip()]++;
    writeToFile();
}

void FileRepository::stergereLocatar(const int& apartament){
    for (int i=0;i<ListaLocatari.size();i++){
        if (ListaLocatari[i].get_apartament()==apartament)
        {
            frecventa_tip[ListaLocatari[i].get_tip()]--;
            ListaLocatari.erase(ListaLocatari.begin()+i);
            writeToFile();
            return;
        }
    }
}

void FileRepository::actualizareLocatar(int apartament, string proprietar, int suprafata, string tip){
    int it=0;
    while (it<ListaLocatari.size()&&ListaLocatari[it].get_apartament()!=apartament)
        it++;
    frecventa_tip[ListaLocatari[it].get_tip()]--;
    ListaLocatari[it].set_suprafata(suprafata);
    ListaLocatari[it].set_proprietar(proprietar);
    ListaLocatari[it].set_tip(tip);
    ListaLocatari[it].set_apartament(apartament);
    frecventa_tip[ListaLocatari[it].get_tip()]++;
    writeToFile();
}

void FileRepository::writeToFile() {
    ofstream f2 (path);
    for (const auto& loc : ListaLocatari)
        f2<<loc<<"\n";
    f2.close();
}

void FileRepository::readFromFile() {
    ListaLocatari.clear();
    ifstream f (path);
    int apartament;
    string nume;
    int suprafata;
    string tip;
    while (f>>apartament>>nume>>suprafata>>tip){
        int ap=apartament;
        string num=nume;
        int sup=suprafata;
        string ti=tip;
        Locatar loc = Locatar(ap,num,sup,ti);
        ListaLocatari.push_back(loc);
    }
    f.close();
}

void FileRepository::clearFile() {
    ofstream f2 (path);
    f2<<"";
    ListaLocatari.clear();
    f2.close();
}

unordered_map<string, int> FileRepository::extrage_frecvente() {
    return frecventa_tip;
}
