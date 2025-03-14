//
// Created by Legion user on 03.05.2024.
//

#ifndef QTIE_UNDO_H
#define QTIE_UNDO_H

#include "Service.h"
#include "Repository.h"
#include "Domain.h"
//clasa abstracta din care mostenesc pentru cele 3 undo-uri (adaugare,stergere,modificare)
class ActiuneUndo {
public:
    virtual void doUndo() = 0;
    virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
private:

    AbstractRepository& repo;
    Locatar loc;
public:
    UndoAdauga(AbstractRepository& repo, const Locatar& loc) :repo{repo},loc{loc}{}
    void doUndo() override {
        repo.stergereLocatar(loc.get_apartament());
    }
};

class UndoSterge : public ActiuneUndo {
private:
    AbstractRepository& repo;
    Locatar loc;
public:
    UndoSterge(AbstractRepository& repo,const Locatar& loc) : repo{repo},loc{loc}{}
    void doUndo() override{
        repo.adaugareLocatar(loc);
    }
};

class UndoModificare : public ActiuneUndo {
private:
    AbstractRepository& repo;
    Locatar loc;
public:
    UndoModificare(AbstractRepository& repo, Locatar& loc) : repo{repo},loc{loc}{}
    void doUndo() override{
        repo.actualizareLocatar(loc.get_apartament(),loc.get_proprietar(),loc.get_suprafata(),loc.get_tip());
    }

};


#endif //QTIE_UNDO_H
