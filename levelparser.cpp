#include "levelparser.h"

/**
 * @brief LevelParser::LevelParser
 * @param XML путь к файду с картой
 * парсит карту
 */
LevelParser::LevelParser(QString XML)
{   
    f_XML = new QFile(XML);
    if (!f_XML->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Невозможно открыть XML-конфиг";
    }

    QVector<int>* ID = new QVector<int>;

    QXmlStreamReader xml(f_XML);

    while (!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::StartDocument)
            continue;

        if (token == QXmlStreamReader::StartElement)
        {
            if(xml.name() == "tile")
            {
                // тут он пушит найденные значения в карту
                if(ID->size() == map->mapW())
                {
                    map->getlvlID().push_back(*ID);
                    ID->clear();
                }
                ID->push_back(xml.attributes().value("gid").toInt());

                continue;
            }

            if (xml.name() == "map")
            {
                map = new Map(xml.attributes().value("width").toInt(),
                                           xml.attributes().value("height").toInt(),
                                           xml.attributes().value("tilewidth").toInt(),
                                           xml.attributes().value("tileheight").toInt());
                continue;
            }

            if(xml.name() == "tileset")continue;

            if(xml.name() == "image") continue;

            if (xml.name() == "data") continue;
            if (xml.name() == "objectgroup")
            {
                // внизу файла с картой прописана дорога
                if(xml.attributes().value("name")=="road")
                {
                    xml.readNextStartElement();
                    start = QPoint(xml.attributes().value("x").toInt()-14, xml.attributes().value("y").toInt()-14);
                    xml.readNextStartElement();
                    road = new Road(start,parseRoad(xml.attributes().value("points").toString()));
                }
            }
        }
    }

    // пушит
    map->getlvlID().push_back(*ID);
    ID->clear();

    f_XML->close();
    delete ID;
}

QPolygon& LevelParser::parseRoad(QString line)
{
    QPoint* p = new QPoint() ;
    QPolygon* pol = new QPolygon();
    int x , y;
    QStringList split1 = line.split(" ");
    for(int i = 0; i < split1.size(); ++i)
    {
        QStringList split2 = split1[i].split(",");
        x = split2.at(0).toInt()+start.x();
        y = split2.at(1).toInt()+start.y();
        p->setX(x);
        p->setY(y);
        *(pol)<<*p;
    }
    return *pol;
}

Map &LevelParser::getMap()
{
    return *map;
}

Road &LevelParser::getRoad()
{
    return *road;
}

LevelParser::~LevelParser()
{
    delete road;
    delete map;
}
