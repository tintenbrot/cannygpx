#include "gpxmodel.h"
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlField>
#include <QDebug>

GpxModel::GpxModel(QObject *parent) :
    QSqlQueryModel(parent)
{
//    QHash<int, QByteArray> roles;
//    roles[DisplayRole] = "title";   // Role f�r die Bildunterschrift
//    roles[DecorationRole] = "decoration"; // Role f�r die Anfrage nach einem Pixmap, das aus der ThumbnailRole (String) erzeugt wird
    //roles[ThumbnailRole] = "thumbnail";  // Role f�r die Erzeugung des Bildnamens im QML-File (Eigentlich nur Zeilennummer mit header)
//    roles[ThumbnailRole] = "picture";  // Role f�r die Erzeugung des Bildnamens im QML-File (Eigentlich nur Zeilennummer mit header)
//    roles[DetailsRole]="detailedDescription";
//    roles[SummaryRole]="summaryDescription";

    //    roles[ExamNumberRole] = "examNumber"; //Role f�r die Untersuchungsnummer
//    roles[ExamEyeRole] = "eye"; //Role f�r die Untersuchungsnummer
//    setRoleNames(roles);
    m_uiTypeIndex=0;
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
        if (roleNames[Qt::UserRole+i+1] == "iType") {
            m_uiTypeIndex=i;
            qDebug() << "Found=" << i;
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
        if (columnIdx == m_uiTypeIndex)
        {
            switch(retVariant.toInt())
            {
            case 0:
                retVariant = QString("Icons/traditional.svg");
                break;
            case 1:
                retVariant = QString("Icons/multi.svg");
                break;
            case 2:
                retVariant = QString("Icons/mystery.svg");
                break;
            }

            qDebug() << "Wurst=" << retVariant.toInt();
        }
        qDebug() << "Data=" << retVariant;
    }
    return retVariant;
}
