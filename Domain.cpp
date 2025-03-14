#include "Domain.h"

Locatar::Locatar() {
    suprafata=apartament=0;
}
Locatar::Locatar(int apartament, std::string &nume_proprietar, int suprafata, std::string &tip){
    this->apartament=apartament;
    this->proprietar=nume_proprietar;
    this->suprafata=suprafata;
    this->tip=tip;
}

Locatar::Locatar(const Locatar &obj){
    this->suprafata=obj.suprafata;
    this->apartament=obj.apartament;
    this->tip=obj.tip;
    this->proprietar=obj.proprietar;
}

int Locatar::get_apartament() const{
    return this->apartament;
}
std::string Locatar::get_proprietar() const{
    return this->proprietar;
}
std::string Locatar::get_tip() const{
    return this->tip;
}
int Locatar::get_suprafata() const{
    return this->suprafata;
}

void Locatar::set_tip(std::string &tip1){
    this->tip=tip1;
}
void Locatar::set_apartament(const int &apartament1){
    this->apartament=apartament1;
}
void Locatar::set_proprietar(std::string &proprietar1){
    this->proprietar=proprietar1;
}
void Locatar::set_suprafata (const int &suprafata1){
    this->suprafata=suprafata1;
}

ostream& operator <<(ostream& os, const Locatar& loc){
    os<<loc.get_apartament()<<" "<<loc.get_proprietar()<<" "<<loc.get_suprafata()<<" "<<loc.get_tip();
    return os;
}