#ifndef XMLLEVELPARSER_H
#define XMLLEVELPARSER_H

#include <QString>
#include "ILevelParser.h"

class XmlLevelParser: public ILevelParser
{
public:
    XmlLevelParser(QString filePath);
    ~XmlLevelParser();
    Map& getMap() override;
    Road& getRoad() override;
private:
    QString TAG = "XmlLevelParser";
    Map* map;
    Road* road;
};

#endif // XMLLEVELPARSER_H
