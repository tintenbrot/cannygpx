#include "gpxmodel.h"
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlField>
#include <QDebug>

GpxModel::GpxModel(QObject *parent) :
    QSqlQueryModel(parent)
{
    m_uiTypeIndex=0;
    m_uiNameIndex=0;
}

GpxModel::~GpxModel()
{
}

void GpxModel::setQuery(const QString &query, const QSqlDatabase &db)
{
    QSqlQueryModel::setQuery(query,db);
    generateRoleNames();
}

void GpxModel::setQuery(const QSqlQuery & query)
{
    QSqlQueryModel::setQuery(query);
    generateRoleNames();
}

void GpxModel::generateRoleNames()
{
    QHash<int, QByteArray> roleNames;
    roleNames.clear();
    for( int i = 0; i < record().count(); i++) {
        roleNames[Qt::UserRole + i + 1] = record().fieldName(i).toAscii();
        if (roleNames[Qt::UserRole+i+1] == "sType") {
            m_uiTypeIndex=i;
            qDebug() << "Found=" << i;
        }
        if (roleNames[Qt::UserRole+i+1] == "sName") {
            m_uiNameIndex = i;
        }
        qDebug() << "Rolename[" << i << "]=" << roleNames[Qt::UserRole+i+1];
    }
    setRoleNames(roleNames);
}

QVariant GpxModel::data(const QModelIndex &index, int role) const
{
    QVariant retVariant = QSqlQueryModel::data(index, role);
    if(role < Qt::UserRole)
    {
        retVariant  = QSqlQueryModel::data(index, role);
    }
    else
    {
        int columnIdx = role - Qt::UserRole - 1;
        QModelIndex modelIndex = this->index(index.row(), columnIdx);
        retVariant = QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
        if  (columnIdx==m_uiTypeIndex)
        {
            qDebug() << "Got Type Request: " << retVariant.toString();

            if (retVariant.toString()=="tradi") retVariant = QString("Icons/traditional.svg");
            else if (retVariant.toString()=="multi") retVariant = QString("Icons/multi.svg");
            else if (retVariant.toString()=="unknown") retVariant = QString("Icons/mystery.svg");
            else if (retVariant.toString()=="earthcache") retVariant = QString("Icons/earthcache.svg");
            else if (retVariant.toString()=="event") retVariant = QString("Icons/event.svg");
            else if (retVariant.toString()=="whereigo") retVariant = QString("Icons/whereigo.svg");
            else if (retVariant.toString()=="letterbox") retVariant = QString("Icons/letterbox.svg");
            else if (retVariant.toString()=="mega") retVariant = QString("Icons/mega.svg");
            else if (retVariant.toString()=="webcam") retVariant = QString("Icons/webcam.svg");
            else if (retVariant.toString()=="locationless") retVariant = QString("Icons/locationless.svg");
        }
        qDebug() << "Data=" << retVariant;
    }
    return retVariant;
}
