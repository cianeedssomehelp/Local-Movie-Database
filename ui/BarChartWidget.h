#pragma once
#include <QWidget>
#include <QPainter>
#include <map>
#include <string>
#include <vector>

#ifndef BARCHARTWIDGET_H
#define BARCHARTWIDGET_H



class BarChartWidget : public QWidget {
    Q_OBJECT

private:
    std::map<std::string, int> genreData;

public:
    explicit BarChartWidget(const std::map<std::string, int>& data, QWidget* parent = nullptr)
        : QWidget(parent), genreData(data) {}

protected:
    void paintEvent(QPaintEvent* event) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        int width = this->width();
        int height = this->height();
        int leftPadding = 60;
        int bottomPadding = 40;
        int topPadding = 30;
        int rightPadding = 20;
        int chartWidth = width - leftPadding - rightPadding;
        int chartHeight = height - topPadding - bottomPadding;

        painter.setPen(Qt::black);
        painter.drawLine(leftPadding, topPadding, leftPadding, height - bottomPadding);
        painter.drawLine(leftPadding, height - bottomPadding, width - rightPadding, height - bottomPadding);

        int maxValue = 0;
        for (const auto& pair : genreData)
            if (pair.second > maxValue) maxValue = pair.second;

        int n = genreData.size();
        int barSpace = chartWidth / n;
        int barWidth = barSpace * 2 / 3;

        int i = 0;
        for (const auto& pair : genreData) {
            int barHeight = (maxValue > 0) ? static_cast<int>((double)pair.second / maxValue * chartHeight) : 0;
            int x = leftPadding + i * barSpace + (barSpace - barWidth) / 2;
            int y = height - bottomPadding - barHeight;

            painter.setBrush(Qt::blue);
            painter.drawRect(x, y, barWidth, barHeight);

            painter.setPen(Qt::black);
            painter.drawText(x + barWidth / 2 - 10, y - 5, QString::number(pair.second));

            QRect textRect(x, height - bottomPadding + 5, barWidth, 20);
            painter.drawText(textRect, Qt::AlignCenter, QString::fromStdString(pair.first));

            ++i;
        }

        int ticks = 5;
        for (int t = 0; t <= ticks; ++t) {
            int y = topPadding + chartHeight - t * chartHeight / ticks;
            int value = maxValue * t / ticks;
            painter.drawLine(leftPadding - 5, y, leftPadding, y);
            painter.drawText(5, y + 5, QString::number(value));
        }
    }
};
#endif //BARCHARTWIDGET_H
