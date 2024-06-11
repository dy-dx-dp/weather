#include "weathertool.h"

QMap<QString, QString> WeatherTool::cityMap;

WeatherTool::WeatherTool()
{
    initCityMap();
}

QString WeatherTool::getCityCode(QString cityName)
{
    return cityMap.value(cityName);
}

void WeatherTool::initCityMap()
{
    QFile file(":/res/citycode.json");
    if(!file.open(QIODevice::ReadOnly)){
        qDebug()<<"读取文件失败！";
        return;
    }

    QByteArray json = file.readAll();
    QJsonDocument jsdoc = QJsonDocument::fromJson(json);
    if(jsdoc.isNull()){
        qDebug()<<"读取文件失败！";
        return;
    }

    //文件里面的cityName和cityName作为键值对插入QMap
    QJsonArray cityArray = jsdoc.array();
    for(int i = 0;i<cityArray.count();i++){
        QJsonObject city = cityArray[i].toObject();
        cityMap.insert(city["cityName"].toString(),city["cityCode"].toString());
    }
}
