#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);  //设置无边框
    ui->btn_search->setStyleSheet(R"(
        QPushButton { border: none; background-color: transparent; }
        QPushButton:hover { background-color: rgba(169, 169, 169, 50) }
        QPushButton:pressed { background-color: rgba(255, 255, 255, 100); border-style: outset; }
    )");
    getCityWeather("101010100");
    connect(reply,&QNetworkReply::finished,this,[=](){
        QByteArray json  = this->getReplyMessage(reply);  //取得json格式的天气数据
        //QString utf8String = QString::fromUtf8(json);
        //qDebug()<<utf8String;
        parseJson(json);
        reply->deleteLater();    //释放内存
        manager->deleteLater();  //释放内存
        setLeftTop(today);
        setLeftBottom(today);
        setRightTop(today, yesterday, day);
    });

    WeatherTool weathertool;
    connect(ui->btn_search,&QPushButton::clicked,this,[=](){
        QString cityName = ui->lineEdit_city->text();
        QString cityCode = WeatherTool::getCityCode(cityName);
        getCityWeather(cityCode);
        qDebug()<<cityCode<<"*********************";
        connect(reply,&QNetworkReply::finished,this,[=](){
            QByteArray json  = this->getReplyMessage(reply);  //取得json格式的天气数据
            //QString utf8String = QString::fromUtf8(json);
            //qDebug()<<utf8String;
            parseJson(json);
            reply->deleteLater();    //释放内存
            manager->deleteLater();  //释放内存
            setLeftTop(today);
            setLeftBottom(today);
            setRightTop(today, yesterday, day);
        });

    });
}

Widget::~Widget()
{
    delete ui;
}


QByteArray Widget::getReplyMessage( QNetworkReply *reply)
{
    //响应状态码
    int status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    qDebug()<<"operation:"<<reply->operation();     //请求方式
    qDebug()<<"状态码:"<<status_code;          //状态码
    qDebug()<<"url:"<<reply->url();
    qDebug()<<"raw header:"<<reply->rawHeaderList();  //header

    if(reply->error()!=QNetworkReply::NoError || status_code!=200){
        QMessageBox::warning(this,"响应信息","获取信息失败！");
        return NULL;
    }
    else{
        QByteArray data = reply->readAll();
        return data;
    }
}

void Widget::getCityWeather(QString cityCode)
{
    // Create a QNetworkAccessManager object
    manager = new QNetworkAccessManager(this);

    // Create a QUrl object with the URL you want to send the GET request to
    QString URL = "http://t.weather.itboy.net/api/weather/city/"+cityCode;
    QUrl url(URL);   //获取天气信息

    // Create a QNetworkRequest object with the URL
    QNetworkRequest request(url);

    // Send the GET request using the QNetworkAccessManager
    reply = manager->get(request);
    qDebug()<<"发送http请求............."<<URL<<reply;
}

void Widget::parseJson(QByteArray json)
{
    QJsonDocument jsdoc = QJsonDocument::fromJson(json);

    //检查是否为空
    if(jsdoc.isNull()){
        QMessageBox::warning(this,"解析信息","数据为空解析信息失败！");
        return;
    }

    //检查是否为json对象
    if(!jsdoc.isObject()){
        return;
    }

    QJsonObject rootObj = jsdoc.object();
    QJsonObject cityinfoObj = rootObj["cityInfo"].toObject();
    QJsonObject dataObj = rootObj["data"].toObject();
    QJsonArray forecastObj = dataObj["forecast"].toArray();
    QJsonObject yesterdayObj = dataObj["yesterday"].toObject();

    today = new WeatherDay;
    yesterday = new WeatherDay;
    today->dateTime = rootObj["time"].toString();
    today->city = cityinfoObj["city"].toString();
    today->shidu = dataObj["shidu"].toString();
    today->pm25 = dataObj["pm25"].toDouble();
    today->pm10 = dataObj["pm10"].toDouble();
    today->quality = dataObj["quality"].toString();
    today->wendu = dataObj["wendu"].toString();
    today->ganmao = dataObj["ganmao"].toString();
    today->high = forecastObj[0].toObject()["high"].toString();
    today->low = forecastObj[0].toObject()["low"].toString();
    today->fx = forecastObj[0].toObject()["fx"].toString();
    today->fl = forecastObj[0].toObject()["fl"].toString();
    today->type = forecastObj[0].toObject()["type"].toString();
    today->week = forecastObj[0].toObject()["week"].toString();
    today->ymd = forecastObj[0].toObject()["ymd"].toString();
    today->aqi = forecastObj[0].toObject()["aqi"].toInt();
    yesterday->high = yesterdayObj["high"].toString();
    yesterday->low = yesterdayObj["low"].toString();
    yesterday->fx = yesterdayObj["fx"].toString();
    yesterday->fl = yesterdayObj["fl"].toString();
    yesterday->type = yesterdayObj["type"].toString();
    yesterday->week = yesterdayObj["week"].toString();
    yesterday->ymd = yesterdayObj["ymd"].toString();
    yesterday->aqi = yesterdayObj["aqi"].toInt();
    for(int i = 1 ; i<5; i++){
        WeatherDay *days = new WeatherDay;
        day[i-1] = days;
        day[i-1]->high = forecastObj[i].toObject()["high"].toString();
        day[i-1]->low = forecastObj[i].toObject()["low"].toString();
        day[i-1]->fx = forecastObj[i].toObject()["fx"].toString();
        day[i-1]->fl = forecastObj[i].toObject()["fl"].toString();
        day[i-1]->type = forecastObj[i].toObject()["type"].toString();
        day[i-1]->week = forecastObj[i].toObject()["week"].toString();
        day[i-1]->ymd = forecastObj[i].toObject()["ymd"].toString();
        day[i-1]->aqi = forecastObj[i].toObject()["aqi"].toInt();
    }
}

void Widget::setLeftTop(WeatherDay *today)
{
    QString path = data.weatherImageMap[today->type];    //天气类型是key，返回图片的路径
    QPixmap pix(path);
    ui->label_weather->setPixmap(pix);
    ui->label_city->setText(today->city);
    ui->label_temperature->setText(today->wendu);
    ui->label_temDiff->setText(today->low+"-"+today->high);
    ui->label_type->setText(today->type);
}

void Widget::setLeftBottom(WeatherDay *today)
{
    ui->label_wind->setText(today->fx);
    ui->label_windLevel->setText(today->fl);
    ui->label_PM->setText(QString::number(today->pm25));
    ui->label_humidity->setText(today->shidu);
    ui->label_airLevel->setText(today->quality);
}

void Widget::setRightTop(WeatherDay *today, WeatherDay *yesterday, WeatherDay *day[])
{
    //取yyyy-mm-dd格式的最后四位字符
    ui->label_date1->setText(yesterday->ymd.right(4));
    ui->label_date2->setText(today->ymd.right(4));
    ui->label_date3->setText(day[0]->ymd.right(4));
    ui->label_date4->setText(day[1]->ymd.right(4));
    ui->label_date5->setText(day[2]->ymd.right(4));
    ui->label_date6->setText(day[3]->ymd.right(4));

    //换天气图片
    ui->label_day1_weather->setPixmap(QPixmap(data.weatherImageMap[yesterday->type]));
    ui->label_day2_weather->setPixmap(QPixmap(data.weatherImageMap[today->type]));
    ui->label_day3_weather->setPixmap(QPixmap(data.weatherImageMap[day[0]->type]));
    ui->label_day4_weather->setPixmap(QPixmap(data.weatherImageMap[day[1]->type]));
    ui->label_day5_weather->setPixmap(QPixmap(data.weatherImageMap[day[2]->type]));
    ui->label_day6_weather->setPixmap(QPixmap(data.weatherImageMap[day[3]->type]));

    //换天气类型
    ui->label_weather1->setText(yesterday->type);
    ui->label_weather2->setText(today->type);
    ui->label_weather3->setText(day[0]->type);
    ui->label_weather4->setText(day[1]->type);
    ui->label_weather5->setText(day[2]->type);
    ui->label_weather6->setText(day[3]->type);

    //换空气质量
    ui->label_air1->setText(airLevel(yesterday->aqi));
    ui->label_air2->setText(airLevel(today->aqi));
    ui->label_air3->setText(airLevel(day[0]->aqi));
    ui->label_air4->setText(airLevel(day[1]->aqi));
    ui->label_air5->setText(airLevel(day[2]->aqi));
    ui->label_air6->setText(airLevel(day[3]->aqi));
}

QString Widget::airLevel(int aqi)  //空气质量转换
{
    int res = (aqi-1)/50;
    switch(res){
        case 0:{return "优"; break;}
        case 1:{return "良好"; break;}
        case 2:{return "轻度污染"; break;}
        case 3:{return "中度污染"; break;}
        case 4:{return "重度污染"; break;}
        case 5:{return "重度污染"; break;}
        default:{return "严重污染"; break;}
    }
}

void Widget::mousePressEvent(QMouseEvent *e)
{
    pOffset = e->globalPos() - this->pos();
}

void Widget::mouseMoveEvent(QMouseEvent *e)
{
    move(e->globalPos()-pOffset);
}

