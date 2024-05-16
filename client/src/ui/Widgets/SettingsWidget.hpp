//
// Created by VERB1807 on 4/8/2024.
//

#pragma once
#include <ads/DockManager.h>
#include <QCheckBox>
#include "../ui_mainwindow.h"
#include "mainwindow.h"
#include "Handlers/SettingsHandler/SettingsHandler.hpp"
//#include "MenuBar.hpp"

namespace ui::SettingsWidget
{
    inline ads::CDockWidget* dockWidget = nullptr;
    inline QHBoxLayout* mainLayout = nullptr;
    inline QVBoxLayout* leftHorizontalLayout = nullptr;
    inline QSpacerItem* leftSpacerItem = nullptr;
    inline QVBoxLayout* rightHorizontalLayout = nullptr;
    inline QSpacerItem* rightSpacerItem = nullptr;

    inline QString currentlyShowing = "";

    void InitLeftButtons();
    void ShowParameters();

    inline void CreateWidget() {
        if (dockWidget) return;

        QWidget *scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("Content");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 779, 349));

        mainLayout = new QHBoxLayout(scrollAreaWidgetContents);
        mainLayout->setSpacing(10);
        mainLayout->setObjectName("verticalLayout");
//        verticalLayout->setContentsMargins(0, 0, 0, 0);

        leftHorizontalLayout = new QVBoxLayout();
        leftHorizontalLayout->setSpacing(2);
        leftHorizontalLayout->setObjectName("sad");
//        leftHorizontalLayout->setContentsMargins(0, 0, 0, 0);

        leftSpacerItem = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);
        leftHorizontalLayout->addItem(leftSpacerItem);

        mainLayout->addLayout(leftHorizontalLayout);

        rightHorizontalLayout = new QVBoxLayout();
        rightHorizontalLayout->setSpacing(2);
        rightHorizontalLayout->setObjectName("sad");
//        rightHorizontalLayout->setContentsMargins(0, 0, 0, 0);

        rightSpacerItem = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);
        rightHorizontalLayout->addItem(rightSpacerItem);

        mainLayout->addLayout(rightHorizontalLayout);

        InitLeftButtons();

        dockWidget = new ads::CDockWidget("Settings");
        dockWidget->setWidget(scrollAreaWidgetContents);

        mainLayout->setStretch(0, 30);
        mainLayout->setStretch(1, 70);

        ShowParameters();
    }

    inline void Clear()
    {
        rightHorizontalLayout->removeItem(rightSpacerItem);

        for (int i = 0; i < rightHorizontalLayout->count(); ++i)
        {
            QWidget *widget = rightHorizontalLayout->itemAt(i)->widget();
            if (widget != NULL)
                widget->setVisible(false);
        }

        rightHorizontalLayout->addItem(rightSpacerItem);
    }

    inline void InitLeftButtons()
    {
        QPushButton* paramsButton = new QPushButton("Parameters");

        QObject::connect(paramsButton, QPushButton::clicked, paramsButton, [](){
            if (currentlyShowing == "params") return;
            ShowParameters();
        });

        leftHorizontalLayout->addWidget(paramsButton);

        leftHorizontalLayout->removeItem(leftSpacerItem);
        leftHorizontalLayout->addItem(leftSpacerItem);
    }

    inline struct {
        QCheckBox* msCheckbox = nullptr;
        QCheckBox* usCheckbox = nullptr;
        QCheckBox* sCheckbox = nullptr;
    } Parameters;

    inline void SetDisplayTime(QString displayText, int divider, QCheckBox* checkBox)
    {
        if (not checkBox->isChecked()) {checkBox->setChecked(true); return; }
        if (ui::SettingsHandler::timeDisplayText == displayText) return;

        Parameters.sCheckbox->setChecked(false);
        Parameters.msCheckbox->setChecked(false);
        Parameters.usCheckbox->setChecked(false);
        checkBox->setChecked(true);

        ui::SettingsHandler::timeDisplayText = displayText;
        ui::SettingsHandler::timeDisplayDivider = divider;
        ui::SettingsHandler::TimeDisplayChanged();
    }

    inline void ShowParameters()
    {
        currentlyShowing = "params";
        Clear();

        QHBoxLayout* layout = new QHBoxLayout();

        QLabel* label = new QLabel("Display time: ");
        layout->addWidget(label);

        QCheckBox* msCheckbox = new QCheckBox("ms");
        msCheckbox->setChecked(true);
        layout->addWidget(msCheckbox);
        Parameters.msCheckbox = msCheckbox;
        msCheckbox->setEnabled(false);

        QCheckBox* usCheckbox = new QCheckBox("μs");
        usCheckbox->setChecked(false);
        layout->addWidget(usCheckbox);
        Parameters.usCheckbox = usCheckbox;
        usCheckbox->setEnabled(false);

        QCheckBox* sCheckbox = new QCheckBox("s");
        sCheckbox->setChecked(false);
        layout->addWidget(sCheckbox);
        Parameters.sCheckbox = sCheckbox;
        sCheckbox->setEnabled(false);

        QObject::connect(sCheckbox, QCheckBox::clicked, sCheckbox, [](){ SetDisplayTime("s", 1000000, Parameters.sCheckbox);});
        QObject::connect(usCheckbox, QCheckBox::clicked, usCheckbox, [](){ SetDisplayTime("μs", 1, Parameters.usCheckbox);});
        QObject::connect(msCheckbox, QCheckBox::clicked, msCheckbox, [](){ SetDisplayTime("ms", 1000, Parameters.msCheckbox);});

        rightHorizontalLayout->addLayout(layout);

        rightHorizontalLayout->removeItem(rightSpacerItem);
        rightHorizontalLayout->addItem(rightSpacerItem);
    }
}