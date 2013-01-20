#ifndef GPXVIEWER_H
#define GPXVIEWER_H

#include <QObject>
#include <QWidget>
#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"
#include "gpxmodel.h"

#ifdef Q_OS_BLACKBERRY
#include <bb/cascades/pickers/FilePicker>
#endif

class GpxViewer : public QWidget
{
    Q_OBJECT
public:
    explicit GpxViewer(QWidget *parent = 0);
    virtual ~GpxViewer();

signals:
    
public slots:
    
private:
    QSqlDatabase m_Database;
    QmlApplicationViewer *m_viewer;
    GpxModel *m_pGpxModel;
    QString m_sDatabaseFile;
#ifdef Q_OS_BLACKBERRY
    bb::cascades::pickers::FilePicker* m_filePicker;
#else
    quint32 * m_filePicker;
#endif
    QObject *m_RebuildButton;
    void createDB();
    void fillDB(QString sFileName);
private slots:
//    void slotEvalQMLSignal(int);
    void slotEvalQMLSignal(QString);
    void onFileSelected(const QStringList&);
};

#endif // GPXVIEWER_H
