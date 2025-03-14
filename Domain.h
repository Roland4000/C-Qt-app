//
// Created by Legion user on 03.05.2024.
//

#ifndef QTIE_DOMAIN_H
#define QTIE_DOMAIN_H

#include <ostream>
#include <string>

using namespace std;

class Locatar {
public:
    Locatar();
    Locatar(int apartament, std::string &nume_proprietar, int suprafata, std::string &tip);
    Locatar(const Locatar &obj);
    [[nodiscard]]int get_apartament() const;
    [[nodiscard]]std::string get_proprietar() const;
    [[nodiscard]]int get_suprafata() const;
    [[nodiscard]]std::string get_tip() const;
    void set_apartament(const int &apartament1);
    void set_proprietar(std::string &proprietar1);
    void set_suprafata(const int &suprafata1);
    void set_tip(std::string &tip1);
    Locatar& operator=(Locatar *obj){
        if (this!=obj){
            proprietar=obj->proprietar;
            apartament=obj->apartament;
            suprafata=obj->suprafata;
            tip=obj->tip;
        }
        return *this;
    }

    friend ostream& operator<<(ostream& os,const Locatar& loc);

private:
    int apartament;
    std:: string proprietar;
    int suprafata;
    std::string tip;

};




#endif //QTIE_DOMAIN_H
