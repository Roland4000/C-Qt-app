//
// Created by Legion user on 03.05.2024.
//

#include "GUI.h"


using std::exception;

void LocatariGUI::initGuiCmps(){
    mainLy=new QHBoxLayout;
    drLy=new QVBoxLayout;
    formLy=new QFormLayout;
    buttonUpperLy=new QHBoxLayout;
    buttonBottomLy=new QHBoxLayout;
    mapLy=new QHBoxLayout;
    tabelModel=new MyTableModel(service.extrage_Locatari());
    tabelView=new QTableView;
    tabelView->setModel(tabelModel);

    setLayout(mainLy);
    mainLy->addLayout(drLy);
    mainLy->addWidget(tabelView);
    drLy->addLayout(formLy);
    drLy->addLayout(buttonUpperLy);
    drLy->addLayout(buttonBottomLy);
    mainLy->addLayout(mapLy);

    txtNr=new QLineEdit;
    txtTip=new QLineEdit;
    txtProprietar=new QLineEdit;
    txtSurface=new QLineEdit;


    formLy->addRow("Apartment number", txtNr);
    formLy->addRow("Owner", txtProprietar);
    formLy->addRow("Surface",txtSurface);
    formLy->addRow("Type",txtTip);

    btnAdaugare=new QPushButton("&Add",this);
    btnStergere=new QPushButton("&Delete",this);
    btnModificare=new QPushButton("&Moddify",this);
    btnSortBySurface=new QPushButton("&Sort by surface",this);
    btnSortByName=new QPushButton("&Sort by name",this);
    btnSortByType=new QPushButton("&Sort by type",this);
    btnFilterByType=new QPushButton("&Filter by type",this);
    btnFilterBySurface=new QPushButton("&Filter by surface",this);
    ListaNotificare=new QPushButton("&Notification list",this);
    Undo=new QPushButton("&Undo",this);
    ListaNotificareReadOnly=new QPushButton("&Read only notification list",this);
    btnAddListaNotificare=new QPushButton("&Add notification list",this);
    btnGolireListaNotificare=new QPushButton("&Empty notification list",this);
    btnGenerareListaNotificare=new QPushButton("&Generate random notification list",this);

    buttonUpperLy->addWidget(btnAdaugare);
    buttonUpperLy->addWidget(btnStergere);
    buttonUpperLy->addWidget(btnModificare);
    buttonUpperLy->addWidget(btnSortBySurface);
    buttonUpperLy->addWidget(btnSortByName);
    buttonUpperLy->addWidget(btnSortByType);

    buttonBottomLy->addWidget(btnFilterByType);
    buttonBottomLy->addWidget(btnFilterBySurface);
    buttonBottomLy->addWidget(Undo);
    buttonBottomLy->addWidget(ListaNotificare);
    buttonBottomLy->addWidget(ListaNotificareReadOnly);

    buttonBottomLy->addWidget(btnAddListaNotificare);
    buttonBottomLy->addWidget(btnGolireListaNotificare);
    buttonBottomLy->addWidget(btnGenerareListaNotificare);

}

void LocatariGUI::connectSignalsSlots() {
    QObject::connect(btnAdaugare, &QPushButton::clicked, [&](){
        try{
            int nr=stoi(txtNr->text().toStdString());
            string proprietar=txtProprietar->text().toStdString();
            int suprafata=stoi(txtSurface->text().toStdString());
            string tip=txtTip->text().toStdString();
            try {
                service.adaugareLocatar(nr, proprietar, suprafata, tip);
            }
            catch (Error& er){
                QMessageBox::warning(this,"Error",QString::fromStdString(er.getMessage()));
            }
        }
        catch (exception&){
            QMessageBox::critical(this,"Error","Bad format!");
        }
        reloadList(service.extrage_Locatari());
    });

    QObject::connect(btnStergere,&QPushButton::clicked,[&](){
        try {
            int nr = stoi(txtNr->text().toStdString());
            try{
                service.stergereLocatar(nr);
                reloadList(service.extrage_Locatari());
            }
            catch (exception&){
                QMessageBox::warning(this,"Error","Unregistered apartment!");
            }
        }
        catch (exception&){
            QMessageBox::critical(this,"Error","Bad format!");
        }
    });

    QObject::connect(btnModificare,&QPushButton::clicked,[&](){
        try{
            int nr=stoi(txtNr->text().toStdString());
            string proprietar=txtProprietar->text().toStdString();
            int suprafata=stoi(txtSurface->text().toStdString());
            string tip=txtTip->text().toStdString();
            try {
                service.actualizareLocatar(nr, proprietar, suprafata, tip);
            }
            catch (Error& er){
                QMessageBox::warning(this,"Error",QString::fromStdString(er.getMessage()));
            }
        }
        catch (exception&){
            QMessageBox::critical(this,"Error","Bad format!");
        }
        reloadList(service.extrage_Locatari());
    });

    QObject::connect(btnSortByName,&QPushButton::clicked,[&](){reloadList(service.sorteaza_locatari_nume_service());});
    QObject::connect(btnSortBySurface,&QPushButton::clicked,[&](){reloadList(service.sorteaza_locatari_suprafata_service());});
    QObject::connect(btnSortByType,&QPushButton::clicked,[&](){reloadList(service.sorteaza_locatari_tip_suprafata_service());});
    QObject::connect(btnFilterByType,&QPushButton::clicked,[&](){
        auto gui = new FilterGUI(this,"tip");
        hide();
        gui->show();
    });
    QObject::connect(btnFilterBySurface,&QPushButton::clicked,[&](){
        auto gui = new FilterGUI(this,"sup");
        hide();
        gui->show();
    });
    QObject::connect(ListaNotificare,&QPushButton::clicked,[&](){
        auto gui = new ListaNotificareCRUDGUI(this);
        gui->show();
    });
    QObject::connect(Undo,&QPushButton::clicked,[&](){
        try {
            service.doUndo();
        }
        catch (exception&){
            QMessageBox::information(this,"Info","No more undo actions!");
        }
        reloadList(service.extrage_Locatari());
    });
    QObject::connect(ListaNotificareReadOnly,&QPushButton::clicked,[&](){
        auto gui = new ListaNotificareReadOnlyGUI(this);
        gui->show();
    });
    QObject::connect(btnAddListaNotificare,&QPushButton::clicked,[&](){
        try{
            int nr_ap=txtNr->text().toInt();
            try{
                service.adauga_lista_notificari(nr_ap);
            }
            catch (Error& er){
                if (er.getMessage()=="Apartament deja inregistrat!\n")
                    QMessageBox::warning(this,"Error","Apartment already registered!");
                else
                    QMessageBox::warning(this,"Error","Apartment does'nt exist");
            }
        }
        catch (exception&){
            QMessageBox::critical(this,"Error","Bad format");
        }
    });
    QObject::connect(btnGolireListaNotificare,&QPushButton::clicked,[&](){
            service.goleste_lista_notificari();
    });
    QObject::connect(btnGenerareListaNotificare,&QPushButton::clicked,[&](){
        try{
            int nr_ap=txtNr->text().toInt();
            int res=service.get_random_apartamente(nr_ap);
            if (res==1)
                QMessageBox::information(this,"Info","Less generated than the given number!");
        }
        catch (exception&){
            QMessageBox::critical(this,"Error","Bad format!");
        }
    });
}


void LocatariGUI::reloadList(const std::vector<Locatar>& locatari) {

    for (int index=0;index<mapButtons.size();index++){
        if (!service.extrage_frecvente()[mapButtons[index]->text().toStdString()]){
            delete mapButtons[index];
            mapButtons.erase(mapButtons.begin()+index,mapButtons.begin()+index+1);
            index--;
        }
    }

    tabelModel->setLocatar(locatari);

    for (auto& loc : locatari){
        bool exista=false;
        string tip=loc.get_tip();
        for (auto button : mapButtons){
            if (button->text().toStdString()==tip){
                exista=true;
            }
        }
        if (!exista){
            auto* btnNou = new QPushButton(QString::fromStdString(tip),this);
            mapButtons.push_back(btnNou);
            mapLy->addWidget(btnNou);
            QObject::connect(btnNou,&QPushButton::clicked, [=](){
                QMessageBox::information(this,"Info",QString::fromStdString(to_string(service.extrage_frecvente()[(btnNou->text()).toStdString()])));
            });
        }
    }



}

FilterGUI::FilterGUI(LocatariGUI* parent, const string& type) {
    mainLy=new QHBoxLayout;
    setLayout(mainLy);
    criteriu=new QFormLayout;
    okay=new QPushButton("&Okay");
    txtCriteriu=new QLineEdit;
    criteriu->addRow("&Filtru",txtCriteriu);
    mainLy->addLayout(criteriu);
    mainLy->addWidget(okay);

    if (type=="tip")
    QObject::connect(okay,&QPushButton::clicked,parent,[=](){
        string filter=txtCriteriu->text().toStdString();
        parent->reloadList(parent->service.filtreaza_locatari_tip_service(filter));
        parent->show();
        this->close();});
    else
        QObject::connect(okay,&QPushButton::clicked,parent,[=](){
            try{
                int filter=txtCriteriu->text().toInt();
                parent->reloadList(parent->service.filtreaza_locatari_sup_service(filter));
            }
            catch (exception&){
                QMessageBox::critical(this,"Error","Bad format!");
            }
            parent->show();
            this->close();
            });
}

ListaNotificareCRUDGUI::ListaNotificareCRUDGUI(LocatariGUI *parent):parent(parent){

    parent->service.addObserver(this);

    mainLy=new QHBoxLayout;
    frmLy=new QFormLayout;
    setLayout(mainLy);

    lstNotificareView=new QListView;
    lstNotificareModel=new MyQListModel(parent->service.get_lista_notificare());
    lstNotificareView->setModel(lstNotificareModel);

    mainLy->addWidget(lstNotificareView);

    buttonLy=new QHBoxLayout;
    mainLy->addLayout(frmLy);
    txtNr=new QLineEdit;
    txtPath=new QLineEdit;
    frmLy->addRow("&App number.",txtNr);
    frmLy->addRow("&Path",txtPath);
    mainLy->addLayout(buttonLy);
    revenire=new QPushButton("&Return",this);
    buttonLy->addWidget(revenire);
    eliminare=new QPushButton("&Empty",this);
    buttonLy->addWidget(eliminare);
    adaugare=new QPushButton("&Add",this);
    buttonLy->addWidget(adaugare);
    adaugareRandom=new QPushButton("&Add random",this);
    buttonLy->addWidget(adaugareRandom);
    exportBtn=new QPushButton("&Export",this);
    buttonLy->addWidget(exportBtn);

    reloadList(parent->service.get_lista_notificare());

    QObject::connect(revenire,&QPushButton::clicked,parent,[=](){
        this->close();
    });

    QObject::connect(eliminare,&QPushButton::clicked,[=](){
        parent->service.goleste_lista_notificari();
        reloadList(parent->service.get_lista_notificare());
    });

    QObject::connect(adaugare,&QPushButton::clicked,[=](){
        try{
            int nr_ap=txtNr->text().toInt();
            try{
                parent->service.adauga_lista_notificari(nr_ap);
                reloadList(parent->service.get_lista_notificare());
            }
            catch (Error& er){
                if (er.getMessage()=="Apartment already registered!\n")
                    QMessageBox::warning(this,"Error","Apartment already registered!");
                else
                    QMessageBox::warning(this,"Error","Apartment does'nt exist!");
            }
        }
        catch (exception&){
            QMessageBox::critical(this,"Error","Bad format!");
        }
    });

    QObject::connect(adaugareRandom,&QPushButton::clicked,[=](){
        try{
            int nr_ap=txtNr->text().toInt();
                int res=parent->service.get_random_apartamente(nr_ap);
                if (res==1)
                    QMessageBox::information(this,"Info","Generated less than the given number!");
                reloadList(parent->service.get_lista_notificare());
        }
        catch (exception&){
            QMessageBox::critical(this,"Error","Bad format!");
        }
    });

    QObject::connect(exportBtn,&QPushButton::clicked,[=](){
        string path=txtPath->text().toStdString();
        parent->service.export_CSV(path);
    });
}

void ListaNotificareCRUDGUI::reloadList(const vector<Locatar>& locs){
    for (const auto& loc : locs){
        qDebug()<<loc.get_tip()<<" ";
    }
    lstNotificareModel->setLocatar(locs);
}

void ListaNotificareCRUDGUI::update() {
    reloadList(parent->service.get_lista_notificare());
}

ListaNotificareReadOnlyGUI::ListaNotificareReadOnlyGUI(LocatariGUI *parent) : parent(parent){
    parent->service.addObserver(this);
}

void ListaNotificareReadOnlyGUI::update() {
    repaint();
}

void ListaNotificareReadOnlyGUI::paintEvent(QPaintEvent *ev) {
    QPainter p{this};
    srand(time(nullptr));
    for (const auto& loc : parent->service.get_lista_notificare()){
        int a=rand()%800;
        int b=rand()%800;
        int c=rand()%800;
        int d=rand()%800;
        p.drawRect(a,b,c,d);
    }
}
