#ifndef CHARTTOOLTIP_HPP
#define CHARTTOOLTIP_HPP

#include <QGraphicsItem>
#include <QPainter>
#include <QString>

class ChartTooltip : public QGraphicsItem {
public:
    ChartTooltip(QGraphicsItem* parent = nullptr) : QGraphicsItem(parent) {}

    void setText(const QString& text) {
        tooltipText = text;
        update();
    }

    QRectF boundingRect() const override {
        return QRectF(0, 0, 150, 50);
    }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override {
        painter->setBrush(Qt::white);
        painter->setPen(Qt::black);
        painter->drawRect(boundingRect());
        painter->drawText(boundingRect(), Qt::AlignCenter, tooltipText);
    }

private:
    QString tooltipText;
};

#endif // CHARTTOOLTIP_HPP
