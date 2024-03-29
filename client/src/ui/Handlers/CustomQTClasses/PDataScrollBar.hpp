//
// Created by VERB1807 on 3/27/2024.
//

#pragma once
#include <QScrollArea>
#include <QScrollBar>
#include <QWheelEvent>
#include <QKeyEvent>
#include <iostream>
#include "Handlers/OperationsBarData/OperationsBarData.h"

class PDataScrollBar: public QScrollArea
{
    Q_OBJECT
private:
    bool shiftDown = false;
    bool ctrlDown = false;

    float zoomIncrease = 0.05f;
public:
    explicit PDataScrollBar(QWidget *parent = nullptr) : QScrollArea(parent){

    };

    void wheelEvent(QWheelEvent * event) override
    {

        QPoint numPixels = event->angleDelta();
        int num = numPixels.y();

        if (ctrlDown)
            num > 0 ? ZoomIn() : ZoomOut();

        if(shiftDown && !ctrlDown)
            num > 0 ? ScrollLeft() : ScrollRight();
        else if (!ctrlDown)
            num < 0 ? ScrollDown() : ScrollUp();

        event->accept();
    }

    void keyPressEvent(QKeyEvent * event) override
    {
        if (event->key() == 16777248)
            shiftDown = true;
        else if (event->key() == 16777249)
            ctrlDown = true;
        event->accept();
    }

    void keyReleaseEvent(QKeyEvent *event) override
    {
        if (event->key() == 16777248)
            shiftDown = false;
        else if (event->key() == 16777249)
            ctrlDown = false;
        event->accept();
    }

private:
    void ScrollUp()
    {
        QScrollBar* bar = verticalScrollBar();
        if (bar->value() <= 0) return;
        bar->setValue(bar->value() - bar->pageStep()/10);
    }
    void ScrollDown()
    {
        QScrollBar* bar = verticalScrollBar();
        bar->setValue(bar->value() + bar->pageStep()/10);
    }
    void ScrollRight()
    {
        QScrollBar* bar = horizontalScrollBar();
        if (bar->value() <= 0) return;
        bar->setValue(bar->value() - bar->pageStep()/10);
    }
    void ScrollLeft()
    {
        QScrollBar* bar = horizontalScrollBar();
        bar->setValue(bar->value() + bar->pageStep()/10);
    }

    void ZoomIn(){
        ui::OperationsBarDataHandler::zoomAmount += zoomIncrease;
        ui::OperationsBarDataHandler::UpdateBarZoom();
    };
    void ZoomOut(){
        if ( ui::OperationsBarDataHandler::zoomAmount <= 0.1) return;
        ui::OperationsBarDataHandler::zoomAmount -= zoomIncrease;
        ui::OperationsBarDataHandler::UpdateBarZoom();
    };
};