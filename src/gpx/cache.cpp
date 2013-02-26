#include "cache.h"

Geocache::Geocache(QObject *parent) :
    QObject(parent)
{
    m_name="";
    m_type="";
    m_description="";
    m_code="";
}


Geocache::~Geocache()
{

}

QString Geocache::code()
{
    return m_code;
}

QString Geocache::name()
{
    return m_name;
}

QString Geocache::description()
{
    return m_description;
}

QString Geocache::type()
{
    return m_type;
}

QString Geocache::text()
{
    return m_text;
}

QString Geocache::longdescription()
{
    return m_longdescription;
}

void Geocache::setCode(QString sValue)
{
    m_code=sValue;
}

void Geocache::setName(QString sValue)
{
    m_name=sValue;
}


void Geocache::setDescription(QString sValue)
{
    m_description=reformatSQLstring(sValue);
}

void Geocache::setType(QString sValue)
{
    m_type=sValue;
}

void Geocache::setText(QString sValue)
{
    m_text=sValue;
}

void Geocache::setLongDescription(QString sValue)
{
    m_longdescription=reformatSQLstring(sValue);
}

QString Geocache::reformatSQLstring(QString sValue)
{
    return sValue.replace("'","");
}
