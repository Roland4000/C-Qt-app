//
// Created by Legion user on 29.05.2024.
//

#include "ModelView.h"

int MyTableModel::rowCount(const QModelIndex &parent) const {
    return lista.size();
}

int MyTableModel::columnCount(const QModelIndex &parent) const {
    return 4;
}

QVariant MyTableModel::data(const QModelIndex &index, int role) const {
    if (role==Qt::DisplayRole){
        const auto& locatar = lista[index.row()];
        switch (index.column()) {

            case 0: return QString::number(locatar.get_apartament());
            case 1: return QString::fromStdString(locatar.get_proprietar());
            case 2: return QString::number(locatar.get_suprafata());
            case 3: return QString::fromStdString(locatar.get_tip());
            default: return QVariant{};
        }
    }
    return {};
}

void MyTableModel::setLocatar(const vector<Locatar> &lst) {
    emit layoutAboutToBeChanged();
    this->lista = lst;
    emit layoutChanged();
}

int MyQListModel::rowCount(const QModelIndex &parent) const {
    return lista.size();
}

QVariant MyQListModel::data(const QModelIndex &index, int role) const {
    if (role==Qt::DisplayRole){
        const auto& locatar = lista[index.row()];
        return QString::number(locatar.get_apartament())+" "+
        QString::fromStdString(locatar.get_proprietar())+" "+
        QString::number(locatar.get_suprafata())+" "+
        QString::fromStdString(locatar.get_tip());
    }
    return {};
}

void MyQListModel::setLocatar(const vector<Locatar>& lst) {
    emit layoutAboutToBeChanged();
    this->lista = lst;
    emit layoutChanged();
}
