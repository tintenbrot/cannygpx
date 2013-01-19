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
        }
        else if (columnIdx>2) {
                retVariant=QString("");
        }
//        else if (columnIdx==m_uiNameIndex) {
//            modelIndex = this->index(index.row(), Qt::UserRole+2);
//            QString sName=QSqlQueryModel::data(modelIndex, Qt::DisplayRole).toString();
//            modelIndex = this->index(index.row(), Qt::UserRole+1);
//            sName += QString("\n")+QSqlQueryModel::data(modelIndex, Qt::DisplayRole).toString();
//            retVariant=sName;
//        }
//        if (columnIdx == m_uiTypeIndex)
//        {
//            switch(retVariant.toInt())
//            {
//            case 0:
//                retVariant = QString("Icons/traditional.svg");
//                break;
//            case 1:
//                retVariant = QString("Icons/multi.svg");
//                break;
//            case 2:
//                retVariant = QString("Icons/mystery.svg");
//                break;
//            }

//            qDebug() << "Wurst=" << retVariant.toInt();
//        }
        qDebug() << "Data=" << retVariant;
    }
    return retVariant;
}
