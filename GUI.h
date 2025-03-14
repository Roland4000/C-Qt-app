//
// Created by Legion user on 03.05.2024.
//

#ifndef QTIE_GUI_H
#define QTIE_GUI_H
#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include "Domain.h"
#include "Service.h"
#include <exception>
#include <QMessageBox>
#include "Observer.h"
#include <QPainter>
#include <QPaintEvent>
#include <cstdlib>
#include <time.h>
#include "ModelView.h"
#include <QListView>
#include <QTableView>


class LocatariGUI : public QWidget, public Observer {
private:
    Service& service;
    MyTableModel* tabelModel;
    QTableView* tabelView;
    QHBoxLayout* mainLy;
    QHBoxLayout* buttonUpperLy;
    QHBoxLayout* buttonBottomLy;
    QHBoxLayout* mapLy;
    QVBoxLayout* drLy;
    QPushButton* btnAdaugare;
    QPushButton* btnStergere;
    QPushButton* btnModificare;
    QPushButton* btnSortBySurface;
    QPushButton* btnSortByName;
    QPushButton* btnSortByType;
    QPushButton* btnFilterByType;
    QPushButton* btnFilterBySurface;
    QPushButton* Undo;
    QPushButton* ListaNotificare;
    QPushButton* ListaNotificareReadOnly;
    QPushButton* btnAddListaNotificare;
    QPushButton* btnGolireListaNotificare;
    QPushButton* btnGenerareListaNotificare;
    vector<QPushButton *> mapButtons;
    QFormLayout* formLy;
    QLineEdit* txtNr;
    QLineEdit* txtProprietar;
    QLineEdit* txtSurface;
    QLineEdit* txtTip;
    void initGuiCmps();
    void connectSignalsSlots();
    void reloadList(const std::vector<Locatar>& locatari);
    void update () override{};
public:
    LocatariGUI(Service& srv) : service{srv}{
        srv.addObserver(this);
        initGuiCmps();
        connectSignalsSlots();
        reloadList(service.extrage_Locatari());
    }
    friend class FilterGUI;
    friend class ListaNotificareCRUDGUI;
    friend class ListaNotificareReadOnlyGUI;
    ~LocatariGUI() override{
        service.removeObserver(this);
    }
};

class FilterGUI : public QWidget{
private:
    QHBoxLayout* mainLy;
    QFormLayout* criteriu;
    QLineEdit* txtCriteriu;
    QPushButton* okay;
public:
    FilterGUI(LocatariGUI* parent, const string& type);
};

class ListaNotificareCRUDGUI : public QWidget, public Observer{
private:
    QHBoxLayout* mainLy;
    MyQListModel* lstNotificareModel;
    QListView* lstNotificareView;
    LocatariGUI* parent;
    QHBoxLayout* buttonLy;
    QPushButton* revenire;
    QPushButton* eliminare;
    QPushButton* adaugare;
    QPushButton* adaugareRandom;
    QPushButton* exportBtn;
    QLineEdit* txtNr;
    QLineEdit* txtPath;
    QFormLayout* frmLy;

    void reloadList(const vector<Locatar>& locs);
    void update() override;
public:
    explicit ListaNotificareCRUDGUI(LocatariGUI* parent);
    ~ListaNotificareCRUDGUI() override{
        parent->service.removeObserver(this);
    }
};

class ListaNotificareReadOnlyGUI : public QWidget, public Observer{
private:
    LocatariGUI* parent;
    void update() override;
public:
    void paintEvent(QPaintEvent* ev) override;
    explicit ListaNotificareReadOnlyGUI(LocatariGUI* parent);
    ~ListaNotificareReadOnlyGUI() override{
        parent->service.removeObserver(this);
    }
};

#endif //QTIE_GUI_H
