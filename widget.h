#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QDebug>
#include <QMessageBox>
#include<QPoint>
#include <QMouseEvent>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QMessageBox>
#include <QPainter>
#include "weatherday.h"
#include "WeatherToPicture.h"
#include "weathertool.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QByteArray getReplyMessage( QNetworkReply *reply);
    void getCityWeather(QString cityCode);
    void parseJson(QByteArray json);
    void setLeftTop(WeatherDay *today);
    void setLeftBottom(WeatherDay *today);
    void setRightTop(WeatherDay *today,WeatherDay *yesterday,WeatherDay *day[]);
    QString airLevel(int aqi);
    void drawHighCurve();
    void drawLowCurve();

protected:
    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    Ui::Widget *ui;
    QPoint pOffset;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    WeatherDay *today;
    WeatherDay *yesterday;
    WeatherDay *day[4];
    WeatherToPicTure data;     //天气对应的图片数据字典

};
#endif // WIDGET_H
