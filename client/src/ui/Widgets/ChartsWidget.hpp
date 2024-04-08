//
// Created by VERB1807 on 4/5/2024.
//

#pragma once
#include <QChartView>
#include <ads/DockManager.h>
#include <QValueAxis>
#include <QBarSet>
#include <QBarSeries>
#include <QBarCategoryAxis>
#include <QSplineSeries>
#include <QToolTip>
#include "MenuBar.hpp"

namespace ui::ChartsWidget
{
    inline ads::CDockWidget* dockWidget = nullptr;
    inline QChartView* chartView = nullptr;
    inline QChart* chart = nullptr;
    inline QBarCategoryAxis* axisX = nullptr;
    inline QValueAxis* axisY = nullptr;

    inline void CreateWidget()
    {
        if (dockWidget) return;

        chart = new QChart();
        chart->setTitle("Showing operation: ");
        chart->setTitleBrush(ui::mainWindow->mainWindowWidget->palette().color( ui::mainWindow->mainWindowWidget->foregroundRole()));
        chartView = new QChartView(chart);

        chartView->setRenderHint(QPainter::RenderHint::Antialiasing);

//        auto axisX = new QBarCategoryAxis;
//        axisX->append(categories);
//        ui::ChartsWidget::chart->addAxis(axisX, Qt::AlignBottom);

        axisX = new QBarCategoryAxis;
        axisY = new QValueAxis();

        axisX->setLabelsColor(ui::mainWindow->mainWindowWidget->palette().color( ui::mainWindow->mainWindowWidget->foregroundRole()));
        axisY->setLabelsColor(ui::mainWindow->mainWindowWidget->palette().color( ui::mainWindow->mainWindowWidget->foregroundRole()));

        axisY->setLabelFormat("%.f us");
//        axisX->setLabelFormat("%.1f");

        chart->addAxis(axisX, Qt::AlignmentFlag::AlignBottom);
        chart->addAxis(axisY, Qt::AlignmentFlag::AlignLeft);

        chart->legend()->setAlignment(Qt::AlignmentFlag::AlignLeft);
        chart->legend()->hide();

        chartView->setContentsMargins(0, 0, 0, 0);
        chart->setContentsMargins(0, 0, 0, 0);

        chart->setBackgroundVisible(false);
        chart->setAcceptHoverEvents(true);

//        axisX->setRange(0, 10);
        axisY->setRange(0, 10);

        dockWidget = new ads::CDockWidget("Speed Efficiency Chart");
        dockWidget->setWidget(chartView);

        ui::MenuBar::menuView->addAction(dockWidget->toggleViewAction());

//        QSplineSeries* series = new QSplineSeries();
//
//        series->append(0, 5);
//        series->append(1, 8);
//        series->append(3, 3);
//        series->append(10, 0);
//        chart->addSeries(series);
//
//        series->attachAxis(axisX);
//        series->attachAxis(axisY);
//

//        QObject::connect(series, &QLineSeries::hovered, series, [](QPointF point, bool state){
//            std::cout << QString("X: %1\nY: %2").arg(point.x()).arg(point.y()).toStdString() << std::endl;
//        });

//        chartView->update();
    }
}