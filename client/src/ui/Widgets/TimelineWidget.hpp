//
// Created by VERB1807 on 4/3/2024.
//

#pragma once
#include <ads/DockManager.h>
#include <QVBoxLayout>
#include "QTClasses/PDataScrollBar.hpp"
#include "MenuBar.hpp"

namespace ui::TimelineWidget
{
    inline ads::CDockWidget* dockWidget = nullptr;
    inline QVBoxLayout* verticalLayout = nullptr;
    inline QSpacerItem* verticalSpacer = nullptr;

    inline void CreateWidget(){
        if (dockWidget != nullptr)
            return;
        dockWidget = new ads::CDockWidget("Timeline");

        PDataScrollBar* infoScrollArea = new PDataScrollBar();
        infoScrollArea->setObjectName("infoScrollArea");
        infoScrollArea->setStyleSheet(QString::fromUtf8(""));
        infoScrollArea->setLineWidth(0);
        infoScrollArea->setWidgetResizable(true);
        infoScrollArea->setAlignment(Qt::AlignRight|Qt::AlignTop|Qt::AlignTrailing);
        infoScrollArea->setStyleSheet(
                "QScrollBar:vertical {background: rgb(50, 104, 191); width: 5px;border-style: solid;} "
                "QScrollBar::handle:vertical {background-color: rgb(54, 54, 54); border: 0px}"
                "QScrollBar::sub-page:vertical {background: rgb(30, 30, 30);}"
                "QScrollBar::add-page:vertical {background: rgb(30, 30, 30);}"
                "QScrollBar::sub-page:horizontal {background: rgb(30, 30, 30);}"
                "QScrollBar::add-page:horizontal {background: rgb(30, 30, 30);}"
                "QScrollBar:horizontal {background: rgb(50, 104, 191); height: 5px;border-style: solid;}"
                "QScrollBar::handle:horizontal {background-color: rgb(54, 54, 54); border: 0px}"
                );
        infoScrollArea->setFrameShape(QFrame::NoFrame);

        QWidget* scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1110, 370));

        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);
        verticalLayout->addItem(verticalSpacer);

        infoScrollArea->setWidget(scrollAreaWidgetContents);
        dockWidget->setWidget(infoScrollArea);

        ui::MenuBar::menuView->addAction(dockWidget->toggleViewAction());
    };
}