#ifndef WEATHERTOPICTURE_H
#define WEATHERTOPICTURE_H

#endif // WEATHERTOPICTURE_H
#include <QString>
#include <QMap>

typedef struct WeatherToPicTure{
    QMap<QString, QString> weatherImageMap = {
        {"暴雪", ":/type/res/type/BaoXue.png"},
        {"暴雨", ":/type/res/type/BaoYu.png"},
        {"暴雨到大暴雨", ":/type/res/type/BaoYuDaoDaBaoYu.png"},
        {"大暴雨", ":/type/res/type/DaBaoYu.png"},
        {"大暴雨到特大暴雨", ":/type/res/type/DaBaoYuDaoTeDaBaoYu.png"},
        {"大到暴雪", ":/type/res/type/DaDaoBaoXue.png"},
        {"大到暴雨", ":/type/res/type/DaDaoBaoYu.png"},
        {"大雪", ":/type/res/type/DaXue.png"},
        {"大雨", ":/type/res/type/DaYu.png"},
        {"东雨", ":/type/res/type/DongYu.png"},
        {"多云", ":/type/res/type/DuoYun.png"},
        {"浮尘", ":/type/res/type/FuChen.png"},
        {"雷阵雨", ":/type/res/type/LeiZhenYu.png"},
        {"雷阵雨伴有冰雹", ":/type/res/type/LeiZhenYuBanYouBingBao.png"},
        {"霾", ":/type/res/type/Mai.png"},
         {"强沙尘暴", ":/type/res/type/QiangShaChenBao.png"},
         {"晴", ":/type/res/type/Qing.png"},
          {"沙尘暴", ":/type/res/type/ShaChenBao.png"},
          {"特大暴雨", ":/type/res/type/TeDaBaoYu.png"},
          {"undefined", ":/type/res/type/undefined.png"},
          {"雾", ":/type/res/type/Wu.png"},
           {"小到中雪", ":/type/res/type/XiaoDaoZhongXue.png"},
           {"小到中雨", ":/type/res/type/XiaoDaoZhongYu.png"},
           {"小雪", ":/type/res/type/XiaoXue.png"},
           {"小雨", ":/type/res/type/XiaoYu.png"},
           {"雪", ":/type/res/type/Xue.png"},
            {"扬沙", ":/type/res/type/YangSha.png"},
            {"阴", ":/type/res/type/Yin.png"},
             {"雨夹雪", ":/type/res/type/YuJiaXue.png"},
             {"阵雪", ":/type/res/type/ZhenXue.png"},
             {"阵雨", ":/type/res/type/ZhenYu.png"},
             {"中到大雪", ":/type/res/type/ZhongDaoDaXue.png"},
             {"中到大雨", ":/type/res/type/ZhongDaoDaYu.png"},
             {"中雨", ":/type/res/type/ZhongYu.png"}
    };
}WeatherToPicTure;
