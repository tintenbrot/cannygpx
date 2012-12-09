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
    QString m_sDatabaseFile;

    QObject *m_RebuildButton;
    void createDB();
    void fillDB();
private slots:
    void slotEvalQMLSignal(int);
};

#endif // GPXVIEWER_H
