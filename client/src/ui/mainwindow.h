#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ads/DockManager.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void dragEnterEvent(QDragEnterEvent *event);
    virtual void dropEvent(QDropEvent *event);

    void ImportTaskkFile(std::string filePath);

    ads::CDockManager* GetDockManager() {return m_DockManager;}
private:
    Ui::MainWindow *ui;
    ads::CDockManager* m_DockManager;

    void InitStylesheet();
};
#endif // MAINWINDOW_H
