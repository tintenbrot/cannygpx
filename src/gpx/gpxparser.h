#ifndef GPXPARSER_H
#define GPXPARSER_H

#include <QObject>
#include <QXmlStreamReader>
#include "cache.h"

class GPXparser : public QObject
{
    Q_OBJECT
public:
    explicit GPXparser(QObject *parent = 0);
    virtual ~GPXparser();
    //
    void setFileName(QString sFileName);
    void getNextCache();
signals:
    
public slots:
private:
    QString m_GPXfile;
    QXmlStreamReader *m_XmlStreamReader;
};

#endif // GPXPARSER_H
