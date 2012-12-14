#include "cache.h"

Geocache::Geocache(QObject *parent) :
    QObject(parent)
{
    m_name="GC1234";
    m_type=TraditionalCache;
    m_description="Ein Wurstencache";
}


Geocache::~Geocache()
{

}

QString Geocache::name()
{
    return m_name;
}

QString Geocache::description()
{
    return m_description;
}

Geocache::CacheType Geocache::type()
{
    return m_type;
}

void Geocache::setName(QString sValue)
{
    m_name=sValue;
}


void Geocache::setDescription(QString sValue)
{
    m_description=sValue;
}

void Geocache::setType(Geocache::CacheType value)
{
    m_type=value;
}
