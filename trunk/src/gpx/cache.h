#ifndef GEOCACHE_H
#define GEOCACHE_H

#include <QObject>

class Geocache : public QObject
{
    Q_OBJECT
public:
    explicit Geocache(QObject *parent = 0);
    virtual ~Geocache();

    enum CacheType {
      Unknown, UnknownCache, MultiCache, TraditionalCache
    };

    QString name();
    QString description();
    CacheType type();
    //
    void setName(QString sValue);
    void setDescription(QString sValue);
    void setType(CacheType value);
signals:
    
public slots:

private:
    QString m_name;
    QString m_description;
    CacheType m_type;
};

#endif // GEOCACHE_H
