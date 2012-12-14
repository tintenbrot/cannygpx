#include "gpxparser.h"
#include <QDebug>


GPXparser::GPXparser(QObject *parent) :
    QObject(parent)
{
    m_GPXfile="";
    m_XmlStreamReader=0;
}

GPXparser::~GPXparser()
{
    if (!(m_XmlStreamReader==0)) {
        delete m_XmlStreamReader;
    }
}

void GPXparser::setFileName(QString sFileName)
{
    m_GPXfile=sFileName;
    m_XmlStreamReader=new QXmlStreamReader(sFileName);
}

void GPXparser::getNextCache()
{
    //Geocache MyCache;
    //
    qDebug() << "Jetzt sollte ich einen Eintrag aus der xml-DAtei picken...\n";
    //return MyCache;
}
