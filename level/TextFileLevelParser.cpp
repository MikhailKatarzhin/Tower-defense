#include <QDebug>
#include <QFile>
#include <QRegularExpression>
#include <QTextStream>
#include "TextFileLevelParser.h"

TextFileLevelParser::TextFileLevelParser(QString filePath)
{
    QFile* fileOfMap = new QFile(filePath);
    if (!fileOfMap->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << TAG << " can't open file " << filePath;
        exit(1);
    }
    TAG = QString(TAG + "[" + filePath + "]");
    QTextStream textStream(fileOfMap);
    if (!parseParametersLine( textStream.readLine() )) exit(-1);
    qDebug() << this->getMap().mapH();
    for (int mapLine = 0; mapLine < this->getMap().mapH(); mapLine++)
    {
        if (!parseLineOfMap(textStream.readLine(), mapLine)) exit(-2);
    }
    if (QRegularExpression("^road").match(textStream.readLine()).hasMatch()) {
        if (!parseRoadLine(textStream.readLine())) exit(-3);
    } else {
        qDebug() << TAG << "road line not found.";
    }
}

Map& TextFileLevelParser::getMap()
{
    return *map;
}

Road& TextFileLevelParser::getRoad()
{
    return *road;
}

TextFileLevelParser::~TextFileLevelParser()
{
    delete road;
    delete map;
}

bool TextFileLevelParser::parseParametersLine(QString parametersLine)
{
    QStringList propertiesList = parametersLine.split(" ");
    if (4 != propertiesList.size()) {
        qDebug() << TAG
                 << " can't parse information line, wrong number of the parameters, "
                 << " right format of the parameters line is "
                 << "'width=%d height=%d tilewidth=%d tileheight=%d' in any order.";
        return false;
    }
    int width(0), height(0), tilewidth(0), tileheight(0);
    for (QString property: propertiesList)
    {
        QStringList nameValueParameter = property.split("=");
        if (2 != nameValueParameter.size()) {
            qDebug() << TAG << " wrong parameter " << property;
            return false;
        }
        bool ok;
        if ("width" == nameValueParameter[0]) {
            width = nameValueParameter[1].toInt(&ok);
            if (!ok) {
                qDebug() << " can't parse width '" << property << "'.";
                return false;
            }
        } else if ("height" == nameValueParameter[0]) {
            height = nameValueParameter[1].toInt(&ok);
            if (!ok) {
                qDebug() << " can't parse height '" << property << "'.";
                return false;
            }
        } else if ("tilewidth" == nameValueParameter[0]) {
            tilewidth = nameValueParameter[1].toInt(&ok);
            if (!ok) {
                qDebug() << " can't parse tilewidth '" << property << "'.";
                return false;
            }
        } else if ("tileheight" == nameValueParameter[0]) {
            tileheight = nameValueParameter[1].toInt(&ok);
            if (!ok) {
                qDebug() << " can't parse tileheight '" << property << "'.";
                return false;
            }
        } else {
            qDebug() << " unexpected parameter " << nameValueParameter[0];
            return false;
        }
    }
    this->map = new Map(width, height, tilewidth, tileheight);
    return true;
}

bool TextFileLevelParser::parseLineOfMap(QString mapLine, int lineNumber)
{
    bool ok;
    QVector<int> line;
    for (QChar number: mapLine)
    {
        line.push_back(QString(number).toInt(&ok));
        if (!ok) {
            qDebug() << " can't parse line #" << lineNumber
                     << ". Sumbol " << number << " not a number.";
            return false;
        }
    }
    if (line.size() != this->getMap().mapW()) {
        qDebug() << " unexpected length of the line #" << lineNumber
                 << ". Expected size is " << this->getMap().mapW()
                 << ", but actual size is " << line.size();
        return false;
    }
    this->getMap().getlvlID().push_back(line);
    return true;
}

bool TextFileLevelParser::parseRoadLine(QString roadLine)
{
    QPolygon roadPoints;
    for (QString xCommaYPoint: roadLine.split(" "))
    {
        QStringList xYPair = xCommaYPoint.split(",");
        if (2 != xYPair.size()) {
            qDebug() << " wrong format of the point " << xCommaYPoint;
            return false;
        }
        bool ok;
        int x = xYPair[0].toInt(&ok);
        if (!ok) {
            qDebug() << " 'x' (" << xCommaYPoint << ") not a number .";
            return false;
        }
        x *= this->getMap().getTileW();
        x -= this->getMap().getTileW() / 2;
        int y = xYPair[1].toInt(&ok);
        if (!ok) {
            qDebug() << " 'y' (" << xCommaYPoint << ") not a number .";
            return false;
        }
        y *= this->getMap().getTileH();
        y -= this->getMap().getTileH() / 2;
        qDebug() << x << y;
        roadPoints << QPoint(x, y);
    }
    this->road = new Road(roadPoints.at(0), roadPoints);
    return true;
}
