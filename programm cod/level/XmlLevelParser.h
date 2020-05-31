#pragma once
#include <QString>
#include "ILevelParser.h"

/**
 * @brief The XmlLevelParser class
 * This is the realisation of the interface ILeveLParser.
 * This class can parse *.tmx files.
 * WARNING: road in this file writed by pixel, not cell.
 * In TextFileLevelParser this problem was solved.
 * Example: :/res/maps/map.tmx
 */
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
