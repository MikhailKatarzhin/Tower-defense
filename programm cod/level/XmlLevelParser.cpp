#include <QDebug>
#include <QFile>
#include <QXmlStreamReader>
#include "XmlLevelParser.h"

QPolygon& parseRoad(QString line, QPoint start);

XmlLevelParser::XmlLevelParser(QString filePath)
{
    QFile* fileOfMap = new QFile(filePath);
    if (!fileOfMap->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << TAG << " can't open file " << filePath;
    }
    QVector<int>* ID = new QVector<int>;
    QXmlStreamReader xmlReader(fileOfMap);
    while (!xmlReader.atEnd() && !xmlReader.hasError())
    {
        QXmlStreamReader::TokenType token = xmlReader.readNext();
        if (token == QXmlStreamReader::StartDocument) continue;
        if (token == QXmlStreamReader::StartElement)
        {
            if(xmlReader.name() == "tile")
            {
                if(ID->size() == map->mapW())
                {
                    map->getlvlID().push_back(*ID);
                    ID->clear();
                }
                ID->push_back(xmlReader.attributes().value("gid").toInt());
                continue;
            }
            if (xmlReader.name() == "map")
            {
                map = new Map(
                            xmlReader.attributes().value("width").toInt(),
                            xmlReader.attributes().value("height").toInt(),
                            xmlReader.attributes().value("tilewidth").toInt(),
                            xmlReader.attributes().value("tileheight").toInt()
                );
                continue;
            }
            if (xmlReader.name() == "tileset") continue;
            if (xmlReader.name() == "image") continue;
            if (xmlReader.name() == "data") continue;
            if (xmlReader.name() == "objectgroup")
            {
                if(xmlReader.attributes().value("name")=="road")
                {
                    xmlReader.readNextStartElement();
                    QPoint start = QPoint(
                                xmlReader.attributes().value("x").toInt()-14,
                                xmlReader.attributes().value("y").toInt()-14
                    );
                    xmlReader.readNextStartElement();
                    road = new Road(
                                start,
                                parseRoad(
                                    xmlReader.attributes().value("points").toString(),
                                    start
                                )
                    );
                }
            }
        }
    }
    map->getlvlID().push_back(*ID);
    ID->clear();
    fileOfMap->close();
    delete ID;
    delete fileOfMap;
}

QPolygon& parseRoad(QString line, QPoint start)
{
    QPoint* p = new QPoint() ;
    QPolygon* pol = new QPolygon();
    int x , y;
    QStringList split1 = line.split(" ");
    for(int i = 0; i < split1.size(); ++i)
    {
        QStringList split2 = split1[i].split(",");
        x = split2.at(0).toInt() + start.x();
        y = split2.at(1).toInt() + start.y();
        p->setX(x);
        p->setY(y);
        *(pol)<<*p;
    }
    return *pol;
}

Map& XmlLevelParser::getMap()
{
    return *map;
}

Road& XmlLevelParser::getRoad()
{
    return *road;
}

XmlLevelParser::~XmlLevelParser()
{
    delete road;
    delete map;
}
