//
// Created by VERB1807 on 4/5/2024.
//

#pragma once

#include <QSplineSeries>
#include <QBarSeries>

struct OperationBar;

namespace ui::EfficiencyChartHandler
{
    inline QSplineSeries* series = nullptr;
    inline QBarSeries* barSeries = nullptr;

    void CreateSeries(std::map<int, int> seriesData);
    void InitSeries(OperationBar data, int hLayoutIndex);

    void Clear();
}
