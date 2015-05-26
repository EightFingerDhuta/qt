#include <QString>

#include "config.h"

Config::Config()
    : width("width: 800\n")
    , height("height: 480\n")
    , pixel("")
    , color("")
    , wrap("")
    , box("")
//    , window("")
    , clip("")
    , elide("")
    , maxline("")
    , innerQml("")
    , text("")
{
}

void Config::setWidth(int w)
{
    width = QString("width: %1\n").arg(w);
}

void Config::setHeight(int h)
{
    height = QString("height: %1\n").arg(h);
}

void Config::setPixelSize(int size)
{
    pixel = QString("font.pixelSize: %1\n").arg(size);
}

void Config::setColor(QString c)
{
    color = QString("color: \"%1\"\n").arg(c);
}

void Config::setWrapMode(Config::WrapMode mode)
{
    switch (mode) {
    case Config::WM_NoWrap:
        wrap = QString("\twrapMode: %1\n").arg("Text.NoWrap");
        break;
    case Config::WM_WordWrap:
        wrap = QString("\twrapMode: %1\n").arg("Text.WordWrap");
        break;
    case Config::WM_ManualWrap:
        wrap = QString("\twrapMode: %1\n").arg("Text.ManualWrap");
        break;
    case Config::WM_WrapAnywhere:
        wrap = QString("\twrapMode: %1\n").arg("Text.WrapAnywhere");
        break;
    case Config::WM_WrapAtWordBoundaryOrAnywhere:
        wrap = QString("\twrapMode: %1\n").arg("Text.WrapAtWordBoundaryOrAnywhere");
        break;
    default:
        wrap = QString("\twrapMode: %1\n").arg("Text.NoWrap");
        break;
    }
}

void Config::setClip(bool b)
{
    QString tmp = b ? "true" : "false";
    clip = QString("clip: %1\n").arg(tmp);
}

void Config::setElide(Config::ElideType e)
{
    switch (e) {
    case Config::ET_None:
        elide = QString("\telide: %1\n").arg("Text.ElideNone");
        break;
    case Config::ET_Left:
        elide = QString("\telide: %1\n").arg("Text.ElideLeft");
        break;
    case Config::ET_Middle:
        elide = QString("\telide: %1\n").arg("Text.ElideMiddle");
        break;
    case Config::ET_Right:
        elide = QString("\telide: %1\n").arg("Text.ElideRight");
        break;
    default:
        elide = QString("\telide: %1\n").arg("Text.ElideNone");
        break;
    }
}

void Config::setMaxLine(int max)
{
    maxline = QString("maximumLineCount: %1\n").arg(max);
}

void Config::setText(QString txt)
{
    text = QString("text: \"%1\"\n").arg(txt);
}

void Config::setBox(int w, int h)
{
    box = QString("width: %1; height: %2\n").arg(w).arg(h);
}

QString Config::GetQML()
{
    innerQml = width + height + pixel + color + text + wrap + box + clip + elide + maxline;
    return QString(tpl).arg(innerQml);
}
