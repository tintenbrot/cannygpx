#ifndef GPXMODEL_H
#define GPXMODEL_H

//#include <QAbstractListModel>
#include <QtSql/QSqlQueryModel>

class GpxModel : public QSqlQueryModel
{
    Q_OBJECT
    void generateRoleNames();

public:
    explicit GpxModel(QObject *parent = 0);
    virtual ~GpxModel();
    void setQuery(const QString &query, const QSqlDatabase &db = QSqlDatabase());
    void setQuery(const QSqlQuery &query);

//    virtual int rowCount(const QModelIndex & parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

//    enum GpxModelRoles {
//        DisplayRole = Qt::DisplayRole,
//        DecorationRole= Qt::DecorationRole,
//        ThumbnailRole = Qt::UserRole + 1,
//        DetailsRole = Qt::UserRole + 2,
//        SummaryRole = Qt::UserRole + 3
//    };

signals:
    
public slots:

private:
    quint16 m_uiTypeIndex;
};

#endif // GPXMODEL_H
