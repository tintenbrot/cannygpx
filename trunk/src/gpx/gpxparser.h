#ifndef GPXPARSER_H
#define GPXPARSER_H

#include <QObject>
#include <QXmlStreamReader>
#include <QFile>
#include "cache.h"

class GPXparser : public QObject
{
    Q_OBJECT
public:
    explicit GPXparser(QObject *parent = 0);
    //explicit GPXparser(QIODevice &file);
    virtual ~GPXparser();
    //
    void setFileName(QString sFileName);
    //void setFile(QIODevice &ioFile);
    bool getNextCache(Geocache &OneCache);

signals:
    
public slots:
private:
    QString m_GPXfile;
    QXmlStreamReader *m_XmlStreamReader;
    QFile m_file;
};

#endif // GPXPARSER_H
