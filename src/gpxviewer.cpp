#include "gpxviewer.h"
#include <QDeclarativeContext>
#include <QtSql/QSqlDatabase>
#include <QDebug>
#include <QtSql/QSqlError>
#include <QModelIndex>
#include <QDir>

GpxViewer::GpxViewer(QObject *parent) :
    QObject(parent)
{
    m_pGpxModel=0;
    m_pGpxModel = new GpxModel(this);
    m_viewer= new QmlApplicationViewer();

    m_Database = QSqlDatabase::addDatabase("QSQLITE");
    //bdb.setDatabaseName("Chinook_Sqlite.sqlite");
    qDebug() << "currentPAth=" << QDir::currentPath();
    qDebug() << "homePath="<< QDir::homePath();
    QString sDatabaseFile=QDir::homePath() + QDir::separator()+"CannyGPX.sqlite";
    //m_Database.setDatabaseName("CannyGPX.sqlite");
    m_Database.setDatabaseName(sDatabaseFile);
    //bdb.setDatabaseName("/home/daniel/maps/default.sqlitedb");
    m_Database.open();
    qDebug() << "m_Database open=" << m_Database.lastError();

    //createDB();
    //fillDB();
    m_pGpxModel->setQuery("SELECT * FROM Geocaches", m_Database);
    //m_pGpxModel->setQuery("SELECT * FROM artist", bdb);

    //

    //
    // Kann ich schrieben?
//    QModelIndex MyIndex;
//    MyIndex=m_pGpxModel->index(0,0,MyIndex);
//    m_pGpxModel->setData(MyIndex,"Hurz",Qt::EditRole);

    m_viewer->setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    //viewer.setMainQmlFile(QLatin1String("qml/test03/main.qml"));
    //viewer.setMainQmlFile(QLatin1String("qml/test03/dynamiclist.qml"));
    m_viewer->rootContext()->setContextProperty("GpxModel",m_pGpxModel);

    m_viewer->setMainQmlFile(QLatin1String("qrc:/qml/cannygpx.qml"));
    m_viewer->showExpanded();
}

GpxViewer::~GpxViewer()
{
    m_Database.close();
    if (!(m_pGpxModel==0)) delete(m_pGpxModel);
    if (!(m_viewer==0)) delete(m_viewer);
}

void GpxViewer::createDB()
{
    qDebug() << "Build database";
    m_pGpxModel->setQuery("create table geocaches \
                          (sID varchar(7), \
                           sName varchar(32), \
                           iType number(3), \
                           sShortDescription varchar(30), \
                           sLongDescription varchar(1024) );", m_Database);
    qDebug() << "lastError=" << m_pGpxModel->lastError();
}

void GpxViewer::fillDB()
{
    qDebug() << "Fill database";
    m_pGpxModel->setQuery("INSERT INTO geocaches \
                          VALUES ('GC123A', \
                                  'Als und als an der Wand lang', \
                                  0, \
                                  'Verdammt schwer zu finden', \
                                  '<HTML> Hier steht ein irre langer Text als Beschreibung </HTML>');", m_Database);
}
