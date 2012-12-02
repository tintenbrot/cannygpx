#ifndef GPXVIEWER_H
#define GPXVIEWER_H

#include <QObject>
#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"
#include "gpxmodel.h"

class GpxViewer : public QObject
{
    Q_OBJECT
public:
    explicit GpxViewer(QObject *parent = 0);
    virtual ~GpxViewer();

signals:
    
public slots:
    
private:
    QSqlDatabase m_Database;
    QmlApplicationViewer *m_viewer;
    GpxModel *m_pGpxModel;

    void createDB();
    void fillDB();
};

#endif // GPXVIEWER_H
