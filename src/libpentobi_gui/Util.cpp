//-----------------------------------------------------------------------------
/** @file libpentobi_gui/Util.cpp */
//-----------------------------------------------------------------------------

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "Util.h"

#include <QCoreApplication>

using libpentobi_base::variant_classic;
using libpentobi_base::variant_classic_2;
using libpentobi_base::variant_duo;
using libpentobi_base::variant_junior;
using libpentobi_base::variant_trigon;
using libpentobi_base::variant_trigon_2;
using libpentobi_base::variant_trigon_3;

//-----------------------------------------------------------------------------

namespace {

const QColor blue(0, 115, 207);

const QColor green(0, 192, 0);

const QColor red(230, 62, 44);

const QColor yellow(235, 205, 35);

const QColor gray(174, 167, 172);

void paintDot(QPainter& painter, QColor color, qreal x, qreal y, qreal width,
              qreal height, qreal size)
{
    painter.save();
    painter.translate(x, y);
    painter.setPen(Qt::NoPen);
    painter.setBrush(color);
    painter.drawEllipse(QPointF(0.5 * width, 0.5 * height), size, size);
    painter.restore();
}

void paintSquare(QPainter& painter, qreal x, qreal y, qreal size,
                 const QColor& rectColor, const QColor& upLeftColor,
                 const QColor& downRightColor)
{
    painter.save();
    painter.translate(x, y);
    painter.fillRect(QRectF(0, 0, size, size), rectColor);
    qreal border = 0.05 * size;
    const QPointF downRightPolygon[6] =
        {
            QPointF(border, size - border),
            QPointF(size - border, size - border),
            QPointF(size - border, border),
            QPointF(size, 0),
            QPointF(size, size),
            QPointF(0, size)
        };
    painter.setPen(Qt::NoPen);
    painter.setBrush(downRightColor);
    painter.drawPolygon(downRightPolygon, 6);
    const QPointF upLeftPolygon[6] =
        {
            QPointF(0, 0),
            QPointF(size, 0),
            QPointF(size - border, border),
            QPointF(border, border),
            QPointF(border, size - border),
            QPointF(0, size)
        };
    painter.setBrush(upLeftColor);
    painter.drawPolygon(upLeftPolygon, 6);
    painter.restore();
}

void paintTriangle(QPainter& painter, bool isUpside, qreal x, qreal y,
                   qreal width, qreal height, const QColor& color,
                   const QColor& upLeftColor, const QColor& downRightColor)
{
    painter.save();
    painter.translate(x, y);
    qreal left = -0.5 * width;
    qreal right = 1.5 * width;
    if (isUpside)
    {
        const QPointF polygon[3] =
            {
                QPointF(left, height),
                QPointF(right, height),
                QPointF(0.5 * width, 0)
            };
        painter.setPen(Qt::NoPen);
        painter.setBrush(color);
        painter.drawConvexPolygon(polygon, 3);
        qreal border = 0.08 * width;
        const QPointF downRightPolygon[6] =
            {
                QPointF(left, height),
                QPointF(right, height),
                QPointF(0.5 * width, 0),
                QPointF(0.5 * width, 2 * border),
                QPointF(right - 1.732 * border, height - border),
                QPointF(left + 1.732 * border, height - border)
            };
        painter.setBrush(downRightColor);
        painter.drawPolygon(downRightPolygon, 6);
        const QPointF upLeftPolygon[4] =
            {
                QPointF(0.5 * width, 0),
                QPointF(0.5 * width, 2 * border),
                QPointF(left + 1.732 * border, height - border),
                QPointF(left, height),
            };
        painter.setBrush(upLeftColor);
        painter.drawPolygon(upLeftPolygon, 4);
    }
    else
    {
        const QPointF polygon[3] =
            {
                QPointF(left, 0),
                QPointF(right, 0),
                QPointF(0.5 * width, height)
            };
        painter.setPen(Qt::NoPen);
        painter.setBrush(color);
        painter.drawConvexPolygon(polygon, 3);
        qreal border = 0.05 * width;
        const QPointF downRightPolygon[4] =
            {
                QPointF(0.5 * width, height),
                QPointF(0.5 * width, height - 2 * border),
                QPointF(right - 1.732 * border, border),
                QPointF(right, 0)
            };
        painter.setBrush(downRightColor);
        painter.drawPolygon(downRightPolygon, 4);
        const QPointF upLeftPolygon[6] =
            {
                QPointF(right, 0),
                QPointF(right - 1.732 * border, border),
                QPointF(left + 1.732 * border, border),
                QPointF(0.5 * width, height - 2 * border),
                QPointF(0.5 * width, height),
                QPointF(left, 0)
            };
        painter.setBrush(upLeftColor);
        painter.drawPolygon(upLeftPolygon, 6);
    }
    painter.restore();
}

void setAlphaSaturation(QColor& c, qreal alpha, qreal saturation)
{
    if (saturation != 1)
        c.setHsv(c.hue(), static_cast<int>(saturation * c.saturation()),
                 c.value());
    if (alpha != 1)
        c.setAlphaF(alpha);
}

} //namespace

//-----------------------------------------------------------------------------

string Util::convertSgfValueFromQString(const QString& value,
                                        const string& charset)
{
    QString charsetToLower = QString(charset.c_str()).trimmed().toLower();
    if (charsetToLower == "utf-8" || charsetToLower == "utf8")
        return value.toUtf8().constData();
    else if (charsetToLower == "iso-8859-1" || charsetToLower == "latin1"
             || charsetToLower.isEmpty())
        return value.toLatin1().constData();
    else
        return value.toAscii().constData();
}

QString Util::convertSgfValueToQString(const string& value,
                                       const string& charset)
{
    QString charsetToLower = QString(charset.c_str()).trimmed().toLower();
    if (charsetToLower == "utf-8" || charsetToLower == "utf8")
        return QString::fromUtf8(value.c_str());
    else if (charsetToLower == "iso-8859-1" || charsetToLower == "latin1"
             || charsetToLower.isEmpty())
        return QString::fromLatin1(value.c_str());
    else
        return QString::fromAscii(value.c_str());
}

QColor Util::getLabelColor(Variant variant, PointState s)
{
    if (s.is_empty())
        return Qt::black;
    Color c = s.to_color();
    QColor paintColor = getPaintColor(variant, c);
    if (paintColor == yellow || paintColor == green)
        return Qt::black;
    else
        return Qt::white;
}

QColor Util::getPaintColor(Variant variant, Color c)
{
    if (variant == variant_duo || variant == variant_junior)
        return c == Color(0) ? blue : green;
    else
    {
        if (c == Color(0))
            return blue;
        if (c == Color(1))
            return yellow;
        if (c == Color(2))
            return red;
        LIBBOARDGAME_ASSERT(c == Color(3));
        return green;
    }
}

QColor Util::getPaintColorEmpty()
{
    return gray;
}

QString Util::getPlayerString(Variant variant, Color c)
{
    if (variant == variant_duo || variant == variant_junior)
    {
        if (c == Color(0))
            return qApp->translate("Util", "Blue");
        if (c == Color(1))
            return qApp->translate("Util", "Green");
    }
    else if (variant == variant_classic || variant == variant_trigon)
    {
        if (c == Color(0))
            return qApp->translate("Util", "Blue");
        if (c == Color(1))
            return qApp->translate("Util", "Yellow");
        if (c == Color(2))
            return qApp->translate("Util", "Red");
        if (c == Color(3))
            return qApp->translate("Util", "Green");
    }
    else if (variant == variant_trigon_3)
    {
        if (c == Color(0))
            return qApp->translate("Util", "Blue");
        if (c == Color(1))
            return qApp->translate("Util", "Yellow");
        if (c == Color(2))
            return qApp->translate("Util", "Red");
    }
    else if (variant == variant_classic_2 || variant == variant_trigon_2)
    {
        if (c == Color(0) || c == Color(2))
            return qApp->translate("Util", "Blue/Red");
        if (c == Color(1) || c == Color(3))
            return qApp->translate("Util", "Yellow/Green");
    }
    LIBBOARDGAME_ASSERT(false);
    return "";
}

void Util::paintColorSquare(QPainter& painter, Variant variant,
                            Color c, qreal x, qreal y, qreal size,
                            qreal alpha, qreal saturation, bool flat)
{
    QColor color = getPaintColor(variant, c);
    QColor upLeftColor;
    QColor downRightColor;
    if (flat)
    {
        upLeftColor = color;
        downRightColor = color;
    }
    else
    {
        upLeftColor = color.lighter(130);
        downRightColor = color.darker(160);
    }
    setAlphaSaturation(color, alpha, saturation);
    setAlphaSaturation(upLeftColor, alpha, saturation);
    setAlphaSaturation(downRightColor, alpha, saturation);
    paintSquare(painter, x, y, size, color, upLeftColor, downRightColor);
}

void Util::paintColorTriangle(QPainter& painter, Variant variant,
                              Color c, bool isUpside, qreal x, qreal y,
                              qreal width, qreal height, qreal alpha,
                              qreal saturation, bool flat)
{
    QColor color = getPaintColor(variant, c);
    QColor upLeftColor;
    QColor downRightColor;
    if (flat)
    {
        upLeftColor = color;
        downRightColor = color;
    }
    else
    {
        upLeftColor = color.lighter(130);
        downRightColor = color.darker(160);
    }
    setAlphaSaturation(color, alpha, saturation);
    setAlphaSaturation(upLeftColor, alpha, saturation);
    setAlphaSaturation(downRightColor, alpha, saturation);
    paintTriangle(painter, isUpside, x, y, width, height, color, upLeftColor,
                  downRightColor);
}

void Util::paintEmptySquare(QPainter& painter, qreal x, qreal y, qreal size)
{
    paintSquare(painter, x, y, size, gray, gray.darker(130), gray.lighter(115));
}

void Util::paintEmptyTriangle(QPainter& painter, bool isUpside, qreal x,
                              qreal y, qreal width, qreal height)
{
    paintTriangle(painter, isUpside, x, y, width, height, gray,
                  gray.darker(130), gray.lighter(115));
}

void Util::paintEmptyTriangleStartingPoint(QPainter& painter, bool isUpside,
                                           qreal x, qreal y, qreal width,
                                           qreal height)
{
    paintEmptyTriangle(painter, isUpside, x, y, width, height);
    if (isUpside)
        y += 0.333 * height;
    height = 0.666 * height;
    paintDot(painter, gray.darker(130), x, y, width, height, 0.17 * width);
}

void Util::paintEmptySquareStartingPoint(QPainter& painter,
                                         Variant variant, Color c,
                                         qreal x, qreal y, qreal size)
{
    paintEmptySquare(painter, x, y, size);
    paintDot(painter, getPaintColor(variant, c), x, y, size, size,
             0.13 * size);
}

//-----------------------------------------------------------------------------
