#include "gpxviewer.h"
#include <QDeclarativeContext>
#include <QtSql/QSqlDatabase>
#include <QDebug>
#include <QtSql/QSqlError>
#include <QModelIndex>
#include <QDir>
#include "gpx/gpxparser.h"


GpxViewer::GpxViewer(QObject *parent) :
    QObject(parent)
{
    m_pGpxModel=0;
    m_pGpxModel = new GpxModel(this);
    m_viewer= new QmlApplicationViewer();

    m_Database = QSqlDatabase::addDatabase("QSQLITE");
    //bdb.setDatabaseName("Chinook_Sqlite.sqlite");
    qDebug() << "currentPath=" << QDir::currentPath();
    qDebug() << "homePath="<< QDir::homePath();
    m_sDatabaseFile=QDir::homePath() + QDir::separator()+"CannyGPX.sqlite";
    //m_Database.setDatabaseName("CannyGPX.sqlite");
    m_Database.setDatabaseName(m_sDatabaseFile);
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

    //m_viewer->setMainQmlFile(QLatin1String("qrc:/qml/CannyGPX.qml"));
    m_viewer->setMainQmlFile(QLatin1String("qrc:/qml/MainWindow.qml"));
    m_viewer->showExpanded();
    //
    // Button Rebuild Database in C++ verknüpfeln
    //m_RebuildButton = m_viewer->findChild<QObject*>("btnRebuildDatabase");
    m_RebuildButton = (QObject *)m_viewer->rootObject();
    QObject::connect(m_RebuildButton, SIGNAL(qmlSignal(int)), this, SLOT(slotEvalQMLSignal(int)));
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
    QString sInsert;
    GPXparser MyGpxParser;
    Geocache MyCache;
    MyGpxParser.setFileName("/home/daniel/Test_LDK.gpx");
    //MyGpxParser.setFileName("/home/daniel/sample.xml");
    //MyGpxParser.setFile(MyFile);
    while (MyGpxParser.getNextCache(MyCache)) {
        qDebug() << "New found Cache";
        qDebug() << "Name=" << MyCache.name();
        qDebug() << "Description=" << MyCache.description() << "\n";
        //
//        sInsert="INSERT INTO geocaches VALUES ('";
//        sInsert += MyCache.name() + "', '"+MyCache.description()+"', ";
//        sInsert += QString("%1").arg(0)+", ";
//        sInsert += QString("'")+"Kommt noch"+"', ";
//        sInsert += QString("'")+"HTML beschreibung kommt auch noch"+"');";
//        m_pGpxModel->setQuery(sInsert, m_Database);
    }
    //CacheList MyCacheList;
    //GpxFileParser MyFileParser;
    //MyFileParser.parse("/home/daniel/default.gpx");
    //GpxParser MyGPXparser;
    //MyGPXparser.
    //MyGPXparser.setFileName("/home/daniel/default.gpx");
    //GeoCache OneCache;
    //OneCache=MyGPXparser.getNextCache();
    //MyGPXparser.getNextCache();
//    qDebug() << "Fill database";
//    m_pGpxModel->setQuery("INSERT INTO geocaches \
//                          VALUES ('GC1201', \
//                                  'Als und als an der Wand lang', \
//                                 0, \
//                                  'Verdammt schwer zu finden', \
//                                  '<HTML> Hier steht ein irre langer Text als Beschreibung </HTML>');", m_Database);
}

void GpxViewer::slotEvalQMLSignal(int iValue)
{
    qDebug() << "Got Signal with value=" << iValue;
    m_Database.close();
    //
    QFile MyFile(m_sDatabaseFile);
    MyFile.remove();
    //
    m_Database.open();
    createDB();
    fillDB();


}