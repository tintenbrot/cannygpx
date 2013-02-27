#include "gpxviewer.h"
#include <QDeclarativeContext>
#include <QtSql/QSqlDatabase>
#include <QDebug>
#include <QtSql/QSqlError>
#include <QModelIndex>
#include <QDir>
#include <QFile>
//#include <QFileDialog>
#include "gpx/gpxparser.h"
//#include <bb/cascades/pickers/FilePicker>


#ifdef Q_OS_BLACKBERRY
using namespace bb::cascades::pickers;
#endif

GpxViewer::GpxViewer(QWidget *parent) :
    QWidget(parent)
{
    m_pGpxModel=0;
    m_pGpxModel = new GpxModel(this);
    m_viewer= new QmlApplicationViewer();
    m_filePicker = 0;

    //m_filePicker = 0;
    m_Database = QSqlDatabase::addDatabase("QSQLITE");
    //bdb.setDatabaseName("Chinook_Sqlite.sqlite");
    qDebug() << "currentPath=" << QDir::currentPath();
    qDebug() << "homePath="<< QDir::homePath();
    m_sDatabaseFile=QDir::homePath() + QDir::separator()+"CannyGPX.sqlite";
    //m_Database.setDatabaseName("CannyGPX.sqlite");
//    QFile MyFile(m_sDatabaseFile);
//    MyFile.remove();
    //
    bool bFirstRun;
    bFirstRun=!QFile(m_sDatabaseFile).exists();

    m_Database.setDatabaseName(m_sDatabaseFile);

    //bdb.setDatabaseName("/home/daniel/maps/default.sqlitedb");
    m_Database.open();
    //
    qDebug() << "m_Database open=" << m_Database.lastError();
//    bFirstRun=true;
    if (bFirstRun) {
        createDB();
        QString sGpxFile=QDir::homePath()+"/default.gpx";
#ifdef Q_OS_BLACKBERRY
            sGpxFile=QDir::homePath() + "/app/native/assets/default.gpx";
//            QFile::copy(sGpxFile,QDir::
#endif
        fillDB(sGpxFile);
    }

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
   // m_viewer->setMainQmlFile(QLatin1String("qrc:/qml/MainWindow.qml"));
    m_viewer->setMainQmlFile(QLatin1String("qml/MainWindow.qml"));
    //
#ifdef Q_OS_BLACKBERRY
    m_viewer->showFullScreen();
#else
    m_viewer->showExpanded();
#endif
    //
    // Button Rebuild Database in C++ verknüpfeln
    //m_RebuildButton = m_viewer->findChild<QObject*>("btnRebuildDatabase");
    m_RebuildButton = (QObject *)m_viewer->rootObject();
    QObject::connect(m_RebuildButton, SIGNAL(qmlSignal(QString)), this, SLOT(slotEvalQMLSignal(QString)));
}

GpxViewer::~GpxViewer()
{
    m_Database.close();
    //if (!(m_pGpxModel==0)) delete(m_pGpxModel);
    if (!(m_viewer==0)) delete(m_viewer);
//    if (m_filePicker != 0) delete m_filePicker;
}

void GpxViewer::createDB()
{
    qDebug() << "Build database";
    m_pGpxModel->setQuery("create table geocaches \
                          (sCode varchar(7), \
                           sName varchar(32), \
                           sType varchar(16), \
                           sShortDescription varchar(30), \
                           sLongDescription varchar(4096) );", m_Database);
    qDebug() << "lastError=" << m_pGpxModel->lastError();
}

void GpxViewer::fillDB(QString sFileName)
{
    QString sInsert;
    GPXparser MyGpxParser;
    Geocache MyCache;
    MyGpxParser.setFileName(sFileName);
    while (MyGpxParser.getNextCache(MyCache)) {
        qDebug() << "fillDB: New Cache found=" << MyCache.name();
//        qDebug() << "Description=" << MyCache.description() << "\n";
        //
        sInsert="INSERT INTO geocaches VALUES ('";
        sInsert += MyCache.code() + "', '"+MyCache.name()+"', ";
        sInsert += QString("'")+MyCache.type()+"', ";
        sInsert += QString("'")+MyCache.description()+"', ";
        sInsert += QString("'")+MyCache.longdescription()+"');";
        m_pGpxModel->setQuery(sInsert, m_Database);
    }
}


void GpxViewer::slotEvalQMLSignal(QString sValue)
{
    qDebug() << "Got Signal" << sValue;
    if (sValue=="ImportGPX") {
    #ifdef Q_OS_BLACKBERRY
            //if (m_filePicker != 0) delete m_filePicker;
            QStringList filters;
            filters << "*.gpx";
            //FilePicker *filePicker = new FilePicker(FileType::Other, 0, filters, QStringList(), QStringList(),this);

            //m_filePicker = new FilePicker(FileType::Other, 0, filters, QStringList(), QStringList());
            m_filePicker = new FilePicker(this);
            m_filePicker->setType(FileType::Other);
            m_filePicker->setFilter(filters);
        //    filePicker->setType(FileType::Picture);
            m_filePicker->setTitle("Select GPX-file");
            m_filePicker->setAllowOverwrite(false);
            //filePicker->setFilter(filters);
            //filePicker->setType()
            m_filePicker->setMode(FilePickerMode::Picker);
            m_filePicker->open();
            QObject::connect(m_filePicker, SIGNAL(fileSelected(const QStringList&)), this, SLOT(onFileSelected(const QStringList&)));
    #else
            QString sFile=QDir::homePath() + QDir::separator()+"default.gpx";;
            m_Database.close();
            if (QFile(sFile).exists())
            {
                m_viewer->rootContext()->setContextProperty("GpxModel",0);
                qDebug() << "Juchu, das File existiert";
                QFile MyFile(m_sDatabaseFile);
                MyFile.remove();
                //
                m_Database.open();
                createDB();
                fillDB(sFile);
                //
                m_pGpxModel->setQuery("SELECT * FROM Geocaches", m_Database);
                m_viewer->rootContext()->setContextProperty("GpxModel",m_pGpxModel);
//                m_viewer->rootContext()->setProperty(
//                m_viewer->
            }
    #endif

        }
    if (sValue=="") {
        qDebug() << "sValue ist leer, also Anwendung beenden";
            qApp->quit();
    }
        //
}


void GpxViewer::onFileSelected(const QStringList &slList )
{
    QString sFile="";
    //sFile=QDir::homePath()+QDir::separator()+"downloads"+QDir::separator()+"default.gpx";
    qDebug() << "slList.size=" << slList.size();
    if (slList.size()>0) sFile=slList.at(0);
    if (!sFile.isEmpty()) {
        m_Database.close();
//        qDebug() << "Selected file=" << sFile;
//        qDebug() << "File exist=" << QFile(sFile).exists();
        if (QFile(sFile).exists())
        {
            qDebug() << "Juchu, das File existiert";
            QFile MyFile(m_sDatabaseFile);
            MyFile.remove();
            MyFile.flush();
            //
//            m_pGpxModel->deleteLater();
//            m_pGpxModel = new GpxModel(this);
            //
            m_Database.open(); //Builds new database-file
            createDB();
            fillDB(sFile);
            // Reset Database
//            m_viewer->deleteLater();
//            m_viewer= new QmlApplicationViewer();
            //
            m_pGpxModel->setQuery("SELECT * FROM Geocaches", m_Database);
            m_viewer->rootContext()->setContextProperty("GpxModel",m_pGpxModel);
        }
    }
}
