#ifndef XMLLEVELPARSER_H
#define XMLLEVELPARSER_H

#include <QString>
#include "ILevelParser.h"

class XmlLevelParser: public ILevelParser
{
public:
    XmlLevelParser(QString);
    ~XmlLevelParser();
    Map& getMap() override;
    Road& getRoad() override;
private:
    QString TAG = "XmlLevelParser";
//    QFile* f_XML;
    Map* map;
    Road* road;
//    QPoint start;
//    QPolygon& parseRoad(QString);
//    void parseTile(QString);
};

#endif // XMLLEVELPARSER_H
