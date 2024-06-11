#ifndef WEATHERTOOL_H
#define WEATHERTOOL_H

#include<QMap>
#include<QFile>
#include<QJsonDocument>
#include<QJsonArray>
#include<QJsonObject>



class WeatherTool
{
public:
    WeatherTool();
    static QString getCityCode(QString cityName);

private:
    static QMap<QString ,QString> cityMap;
    static void initCityMap();
};

#endif // WEATHERTOOL_H
