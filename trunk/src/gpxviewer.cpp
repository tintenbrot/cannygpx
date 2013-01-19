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
   // m_viewer->setMainQmlFile(QLatin1String("qrc:/qml/MainWindow.qml"));
    m_viewer->setMainQmlFile(QLatin1String("qml/MainWindow.qml"));
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
    if (m_filePicker != 0) delete m_filePicker;
}

void GpxViewer::createDB()
{
    qDebug() << "Build database";
    m_pGpxModel->setQuery("create table geocaches \
                          (sCode varchar(7), \
                           sName varchar(32), \
                           sType varchar(16), \
                           sShortDescription varchar(30), \
                           sLongDescription varchar(1024) );", m_Database);
    qDebug() << "lastError=" << m_pGpxModel->lastError();
}

void GpxViewer::fillDB(QString sFileName)
{
    QString sInsert;
    GPXparser MyGpxParser;
    Geocache MyCache;
    MyGpxParser.setFileName(sFileName);
    //MyGpxParser.setFileName("/home/daniel/Test_LDK.gpx");
    //MyGpxParser.setFileName("/home/daniel/20121201_LDK.gpx");
    //MyGpxParser.setFile(MyFile);
    while (MyGpxParser.getNextCache(MyCache)) {
        qDebug() << "New found Cache";
        qDebug() << "Name=" << MyCache.name();
        qDebug() << "Description=" << MyCache.description() << "\n";
        //
        sInsert="INSERT INTO geocaches VALUES ('";
        sInsert += MyCache.code() + "', '"+MyCache.name()+"', ";
        //sInsert += QString("%1").arg((int)MyCache.type())+", ";
        sInsert += QString("'")+MyCache.type()+"', ";
        sInsert += QString("'")+MyCache.description()+"', ";
        sInsert += QString("'")+MyCache.longdescription()+"');";
        m_pGpxModel->setQuery(sInsert, m_Database);
    }
}

void GpxViewer::slotEvalQMLSignal(int iValue)
{
    qDebug() << "Got Signal with value=" << iValue;
    if (iValue==0) {
#ifdef Q_OS_BLACKBERRY
        //if (m_filePicker != 0) delete m_filePicker;
        QStringList filters;
        filters << "*.gpx";
        //FilePicker *filePicker = new FilePicker(FileType::Other, 0, filters, QStringList(), QStringList(),this);
        m_filePicker = new FilePicker(FileType::Other, 0, filters, QStringList(), QStringList());
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
            m_viewer->rootContext()->setContextProperty("GpxModel",m_pGpxModel);
        }
#endif
    }
    if (iValue==1)
        qApp->quit();
    //
}

void GpxViewer::onFileSelected(const QStringList &slList )
{
    QString sFile;
    //sFile=QDir::homePath()+QDir::separator()+"downloads"+QDir::separator()+"default.gpx";
    sFile=slList[0];
    if (m_filePicker != 0) delete m_filePicker;
    //QString sFile = filePicker->selectedFiles[0];
    m_Database.close();
//     "/home/daniel/Test_LDK.gpx"
//    QString sFile= QFileDialog::getOpenFileName(this, "Open Image", QDir::homePath(), "Gpx Files (*.gpx)");
    qDebug() << "Selected file=" << sFile;
    qDebug() << "File exist=" << QFile(sFile).exists();
    if (QFile(sFile).exists())
    {
        //m_viewer->rootContext()->setContextProperty("GpxModel",0);
        qDebug() << "Juchu, das File existiert";
        QFile MyFile(m_sDatabaseFile);
        MyFile.remove();
        //
        m_Database.open();
        createDB();
        fillDB(sFile);
        // Reset Database
        //m_viewer->rootContext()->setContextProperty("GpxModel",m_pGpxModel);
    }
}
