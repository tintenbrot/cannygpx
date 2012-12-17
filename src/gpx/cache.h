#ifndef GEOCACHE_H
#define GEOCACHE_H

#include <QObject>

class Geocache : public QObject
{
    Q_OBJECT
public:
    explicit Geocache(QObject *parent = 0);
    virtual ~Geocache();
    QString code();
    QString name();
    QString description();
    QString type();
    QString text();
    QString longdescription();
    //
    void setCode(QString sValue);
    void setName(QString sValue);
    void setDescription(QString sValue);
    void setType(QString sValue);
    void setText(QString sValue);
    void setLongDescription(QString sValue);
signals:
    
public slots:

private:
    QString m_code;
    QString m_name;
    QString m_type;
    QString m_text;
    QString m_description;
    QString m_longdescription;
};

#endif // GEOCACHE_H
