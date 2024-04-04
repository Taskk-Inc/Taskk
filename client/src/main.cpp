#include <QApplication>
#include "ui/ui.hpp"
#include "mainwindow.h"
#include "Handlers/OperationsBarData/OperationsBarData.h"

void init()
{
}

int main(int argc, char * argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    init();

    ui::OperationsBarDataHandler::UpdateBarZoom();

    return a.exec();
}

