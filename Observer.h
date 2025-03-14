//
// Created by Legion user on 24.05.2024.
//

#ifndef QTIE_OBSERVER_H
#define QTIE_OBSERVER_H

#include <vector>
using std::vector;

class Observer{
public:
    virtual void update() = 0;
};

class Observable{
private:
    vector<Observer*> observers;
public:
    void addObserver(Observer* obs);
    void removeObserver(Observer* obs);
protected:
    void notify(){
        for (auto obs : observers){
            obs->update();
        }
    }
};


#endif //QTIE_OBSERVER_H
