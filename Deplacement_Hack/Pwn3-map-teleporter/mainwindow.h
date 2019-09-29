#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <windows.h>
#include "processhacking.h"

#include <QMainWindow>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QDialog>
#include <QSlider>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    LPCTSTR windowName;
    LPCTSTR processName;
    LPCTSTR dllName;
    DWORD lookXOffset;
    DWORD loogYOffset;
    DWORD posXOffset;
    DWORD posYOffset;
    DWORD posZOffset;
    DWORD velocityOffset;
    DWORD PointerAddress;
    ProcessHacking *processHacking;


    Ui::MainWindow *ui;
    QLabel *m_imageMap;
    QLabel *m_cursorPosition;
    QLabel *m_sliderPosition;
    QSlider *m_heightSlider;
    QHBoxLayout *m_mainLayout;

    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);

private slots:
    void ModifyHeight(int height);
};

#endif // MAINWINDOW_H
