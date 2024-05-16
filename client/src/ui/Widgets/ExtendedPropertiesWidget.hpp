//
// Created by VERB1807 on 4/3/2024.
//

#pragma once
#include <ads/DockManager.h>
#include <QScrollArea>
#include "../ui_mainwindow.h"
#include "mainwindow.h"
#include "MenuBar.hpp"

namespace ui::ExtendedPropertiesWidget
{
    inline ads::CDockWidget* dockWidget = nullptr;
    inline QScrollArea* scrollArea = nullptr;
    inline QVBoxLayout* verticalLayout = nullptr;
    inline QSpacerItem* verticalSpacer = nullptr;

    inline void CreateWidget()
    {
        if (dockWidget) return;

        scrollArea = new QScrollArea();
        scrollArea->setGeometry(QRect(9, 9, 781, 351));
        scrollArea->setStyleSheet(QString::fromUtf8(""));
        scrollArea->setLineWidth(0);
        scrollArea->setWidgetResizable(true);
        scrollArea->setAlignment(Qt::AlignRight|Qt::AlignTop|Qt::AlignTrailing);
        scrollArea->setStyleSheet(
                "QScrollBar:vertical {background: rgb(50, 104, 191); width: 5px;border-style: solid;} "
                "QScrollBar::handle:vertical {background-color: rgb(54, 54, 54); border: 0px}"
                "QScrollBar::sub-page:vertical {background: rgb(30, 30, 30);}"
                "QScrollBar::add-page:vertical {background: rgb(30, 30, 30);}"
                "QScrollBar::sub-page:horizontal {background: rgb(30, 30, 30);}"
                "QScrollBar::add-page:horizontal {background: rgb(30, 30, 30);}"
                "QScrollBar:horizontal {background: rgb(50, 104, 191); height: 5px;border-style: solid;}"
                "QScrollBar::handle:horizontal {background-color: rgb(54, 54, 54); border: 0px}"
        );
        scrollArea->setFrameShape(QFrame::NoFrame);

        QWidget* scrollAreaWidgetContents= new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 779, 349));

        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName("verticalLayout_4");
        verticalLayout->setContentsMargins(10, 5, 10, 5);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        dockWidget = new ads::CDockWidget("Properties");
        dockWidget->setWidget(scrollArea);

        ui::MenuBar::menuView->addAction(dockWidget->toggleViewAction());
    }
}