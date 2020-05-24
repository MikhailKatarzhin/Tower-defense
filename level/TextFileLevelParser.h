#ifndef TEXTFILELEVELPARSER_H
#define TEXTFILELEVELPARSER_H

#include <QString>
#include "ILevelParser.h"

/**
 * @brief The TextFileLevelParser class
 * This is the realisation of the interface ILeveLParser.
 * This class can parse just text files.
 * Road in this files writed by cell.
 * Example: :/res/maps/map.
 */
class TextFileLevelParser: public ILevelParser
{
public:
    TextFileLevelParser(QString filePath);
    ~TextFileLevelParser();
    Map& getMap() override;
    Road& getRoad() override;
private:
    QString TAG = "TextFileLevelParser";
    Map* map;
    Road* road;

    bool parseParametersLine(QString parametersLine);
    bool parseLineOfMap(QString mapLine, int lineNumber);
    bool parseRoadLine(QString roadLine);
};

#endif // TEXTFILELEVELPARSER_H
