#include "gpxparser.h"
#include <QDebug>
#include <QFile>


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
    m_file.close();
    //if (!(m_file==0)) delete m_file;
}

void GPXparser::setFileName(QString sFileName)
{
    m_GPXfile=sFileName;
    m_file.setFileName(sFileName);
    m_file.open(QFile::ReadOnly);
    //m_file=QFile(sFileName,this);
    m_XmlStreamReader=new QXmlStreamReader(&m_file);
    qDebug() << "FileName=" << sFileName;
    qDebug() << "File exist=" << QFile(sFileName).exists();
}


bool GPXparser::getNextCache(Geocache &OneCache)
{
    bool boolValid=true;

    //OneCache.clear();
    // StartElement "wpt" suchen, dieses gibt einen neuen Cache an

    bool boolFoundStartTag=false;
    while(!m_XmlStreamReader->atEnd() && !m_XmlStreamReader->hasError() && !boolFoundStartTag)
    {
        m_XmlStreamReader->readNext();
        if(m_XmlStreamReader->tokenType() == QXmlStreamReader::StartElement)
        {
            if (m_XmlStreamReader->name()=="wpt") {
               boolFoundStartTag=true;
               qDebug() << "StartTag found";
            }
        }
    }
    //
    // Prima, jetzt so lange einlesen, bis wpt-EndElement
    bool boolGotName=false;
    while(!m_XmlStreamReader->atEnd() && !m_XmlStreamReader->hasError() && boolFoundStartTag)
    {
        m_XmlStreamReader->readNext();
        //
        // Elemente ermitteln
        if(m_XmlStreamReader->tokenType() == QXmlStreamReader::StartElement)
        {
            //qDebug() << "StartElement Name=" << m_XmlStreamReader->name();

            if(m_XmlStreamReader->name() == "name")
            {
                if (!boolGotName) {
                    boolGotName=true;
                    OneCache.setCode(m_XmlStreamReader->readElementText());
                }
            }
            else if(m_XmlStreamReader->name() == "desc")
            {
                //OneCache.setDescription(m_XmlStreamReader->readElementText());
                OneCache.setName(m_XmlStreamReader->readElementText());
            }
            else if(m_XmlStreamReader->name() == "type")
            {
                QString sType=m_XmlStreamReader->readElementText();
                if (sType=="Geocache|Traditional Cache") OneCache.setType("tradi");
                else if (sType=="Geocache|Multi-cache") OneCache.setType("multi");
                else if (sType=="Geocache|Unknown Cache")  OneCache.setType("unknown");
                qDebug() << "Found type=" << m_XmlStreamReader->readElementText();
            }
            else if(m_XmlStreamReader->name()=="text")
            {
                OneCache.setText(m_XmlStreamReader->readElementText());
                qDebug() << "Text=" << m_XmlStreamReader->readElementText();
            }
            else if(m_XmlStreamReader->name()=="short_description")
            {
                OneCache.setDescription(m_XmlStreamReader->readElementText());
                //qDebug() << "long_description=" << m_XmlStreamReader->readElementText();
            }
            else if(m_XmlStreamReader->name()=="long_description")
            {
                OneCache.setLongDescription(m_XmlStreamReader->readElementText());
                //qDebug() << "long_description=" << m_XmlStreamReader->readElementText();
            }
            else
            {
                qDebug() << "StartElement Name=" << m_XmlStreamReader->name();
                //qDebug() << "Value=" << m_XmlStreamReader->readElementText();
            }
        }

        if(m_XmlStreamReader->tokenType() == QXmlStreamReader::EndElement)
        {
            //qDebug() << "EndElement Name=" << m_XmlStreamReader->name();
            if (m_XmlStreamReader->name()=="wpt") {
                qDebug() << "Cache fettich gelesen";
                boolFoundStartTag=false;
            }
        }
    }

//    while(m_XmlStreamReader->tokenType() != QXmlStreamReader::EndElement &&
//      !m_XmlStreamReader->atEnd() && !m_XmlStreamReader->hasError())
//    {
//        if (m_XmlStreamReader->atEnd()) boolValid=false;
//        if(m_XmlStreamReader->tokenType() == QXmlStreamReader::StartElement)
//        {
//            qDebug() << "StartElement Name=" << m_XmlStreamReader->name();
//            if(m_XmlStreamReader->name() == "name")
//            {
//                QString name;
//                //parseString(m_XmlStreamReader, name);
//                name=m_XmlStreamReader->readElementText();
//                OneCache.setDescription(name);
//                qDebug() << iCount << ": " << name;
//                iCount++;
//            }
//        }
//      m_XmlStreamReader->readNext();
//    }
    if (m_XmlStreamReader->atEnd()) boolValid=false;
//    qDebug() << "Token=" << m_XmlStreamReader->readNext();
//    qDebug() << m_XmlStreamReader->name().toString();
//    if (m_XmlStreamReader->atEnd()) {
//        qDebug() << "XML File am Ende";
//        boolValid=false;
//    }
//    else
//    {
//        qDebug() << "hasErrors=" << m_XmlStreamReader->hasError();
//        //qDebug()<<  m_XmlStreamReader->readNextStartElement();
//        qDebug() << "Text=" << m_XmlStreamReader->text().toString();
//        qDebug() << "Linenumber=" << m_XmlStreamReader->lineNumber();
//        qDebug() << "Nicht am Ende...";
//        qDebug()<< "isStartDocument= " << m_XmlStreamReader->isStartDocument();
//        if(m_XmlStreamReader->isStartElement()) {
//            qDebug() << "StartElement gefunden";

//        }
//        if(m_XmlStreamReader->tokenType() == QXmlStreamReader::StartElement) {
//          qDebug() << "StartElement detected";
//          if(m_XmlStreamReader->name() == "name") {
//              qDebug() << "Element \"name\" detected.";
//          }
//        }
//    }
    //}
    //qDebug() << "Jetzt sollte ich einen Eintrag aus der xml-DAtei picken...\n";
    //return MyCache;
    return boolValid;
}
