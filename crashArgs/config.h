#ifndef CONFIG_H
#define CONFIG_H

class QString;

static QString tpl = "import QtQuick 2.0\n"
        "\n"
        "Text {\n"
        "   %1\n"
        "}";

class Config
{
public:
    Config();

    enum WeightType {
        WT_Light,
        WT_Normal,
        WT_DemiBold,
        WT_Bold,
        WT_Black
    };

    enum StyleType {
        ST_Normal,
        ST_Outline,
        ST_Raised,
        ST_Sunken
    };

    enum WrapMode {
        WM_NoWrap,
        WM_WordWrap,
        WM_ManualWrap,
        WM_WrapAnywhere,
        WM_WrapAtWordBoundaryOrAnywhere
    };

    enum ElideType {
        ET_None,
        ET_Left,
        ET_Middle,
        ET_Right
    };

    void setWidth(int w);
    void setHeight(int h);
    void setPixelSize(int size);
    void setColor(QString c);
    void setWrapMode(WrapMode mode);
    void setBox(int w, int h);
//    void setWindow(int w, int h);
    void setClip(bool b);
    void setElide(ElideType elide);
    void setMaxLine(int max);
    void setText(QString txt);

    QString GetQML();
private:
    QString width;
    QString height;
    QString pixel;
    QString color;
    QString wrap;
    QString box;
//    QString window;
    QString clip;
    QString elide;
    QString maxline;
    QString text;

    QString innerQml;
};

#endif // CONFIG_H
