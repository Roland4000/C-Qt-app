//
// Created by Legion user on 24.05.2024.
//

#include "Observer.h"

void Observable::addObserver(Observer *obs) {
    observers.push_back(obs);
}

void Observable::removeObserver(Observer *obs) {
    for (int index=0;index<observers.size();index++){
        if (observers[index]==obs){
            observers.erase(observers.begin()+index,observers.begin()+index+1);
            return ;
        }
    }
}
