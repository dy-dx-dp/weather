#ifndef WEATHERDAY_H
#define WEATHERDAY_H

#include <QObject>

class WeatherDay :QObject
{
    Q_OBJECT
public:
    WeatherDay();

public:
    QString dateTime;
    QString city;
    QString shidu;
    double  pm25;
    double pm10;
    QString quality;
    QString wendu;
    QString ganmao;
    QString high;//最高温
    QString low;//最低温
    QString fx;//风类型
    QString fl;//风力等级
    QString type;//天气类型
    QString week;//星期日期
    QString ymd;//年月日
    int aqi;  //空气质量指数
};

#endif // WEATHERDAY_H
