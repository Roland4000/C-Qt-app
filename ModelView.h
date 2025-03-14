//
// Created by Legion user on 29.05.2024.
//

#ifndef QTIE_MODELVIEW_H
#define QTIE_MODELVIEW_H

#include <vector>
#include "Domain.h"
#include <QAbstractListModel>

using std::vector;

class MyQListModel : public  QAbstractListModel{
public:
    explicit MyQListModel(const vector<Locatar>& lst):lista{lst}{};
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    void setLocatar(const vector<Locatar>& lst);
private:
    vector<Locatar> lista;
};

class MyTableModel: public QAbstractTableModel {
private:
    vector<Locatar> lista;

public:
    explicit MyTableModel(const vector<Locatar>& lst):lista{lst}{};

    [[nodiscard]] int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    [[nodiscard]] int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    [[nodiscard]] QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    void setLocatar(const vector<Locatar>&lst);
};


#endif //QTIE_MODELVIEW_H
