#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(560, 520);
    this->setMouseTracking(true);

    m_cursorPosition = new QLabel(this);
    m_cursorPosition->setText("position : 0 x 0");
    m_sliderPosition = new QLabel(this);
    m_sliderPosition->setText("Height : 0");
    ui->m_statusBar->addWidget(m_cursorPosition);
    ui->m_statusBar->addWidget(m_sliderPosition);

    m_mainLayout = new QHBoxLayout(this);
    m_imageMap = new QLabel(this);
    m_imageMap->setPixmap(QPixmap("C:\\map_500x500.png"));
    m_imageMap->setFixedSize(500, 500);
    m_imageMap->setMouseTracking(true);
    m_mainLayout->addWidget(m_imageMap);

    m_heightSlider = new QSlider(this);
    //m_highSlider->set
    m_heightSlider->setFixedSize(30, 480);
    m_heightSlider->setMaximum(100000);
    m_heightSlider->setMinimum(0);
    m_mainLayout->addWidget(m_heightSlider);

    setLayout(m_mainLayout);

    QObject::connect(m_heightSlider, SIGNAL(valueChanged(int)), this, SLOT(ModifyHeight(int)));

    ////////////////////////////////////////////////////////////////////////////////////////////

    windowName = "PwnAdventure3 (32-bit, PCD3D_SM5)";
    processName = "PwnAdventure3-Win32-Shipping.exe";
    dllName = "GameLogic.dll";
    lookXOffset = 0x8C;
    loogYOffset = 0x88;
    posXOffset = 0x90;
    posYOffset = 0x94;
    posZOffset = 0x98;
    velocityOffset = 0x13C;

    processHacking = new ProcessHacking(processName, windowName, dllName);
    ReadProcessMemory(processHacking->m_handleProcess, (PBYTE*)(processHacking->m_dwGameLogic + 0x00097D80), &PointerAddress, sizeof(DWORD), 0);
    ReadProcessMemory(processHacking->m_handleProcess, (PBYTE*)(PointerAddress + 0x170), &PointerAddress, sizeof(DWORD), 0);
    ReadProcessMemory(processHacking->m_handleProcess, (PBYTE*)(PointerAddress + 0x238), &PointerAddress, sizeof(DWORD), 0);
    ReadProcessMemory(processHacking->m_handleProcess, (PBYTE*)(PointerAddress + 0x27C), &PointerAddress, sizeof(DWORD), 0);
    ReadProcessMemory(processHacking->m_handleProcess, (PBYTE*)(PointerAddress + 0x74), &PointerAddress, sizeof(DWORD), 0);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
//    int minX = 150000;
//    int maxX = 100000;
//    int minY = 150000;
//    int maxY = 100000;
    int posX = (event->x() - 250) * 150000 / 250;
    int posY = (event->y() - 250) * 150000 / 250;
    QString posString = "Position : " + QString::number(posX) + " x " + QString::number(posY) + " ";

    m_cursorPosition->setText(posString);
}


// TOUT RESTE A FAIRE!
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
//    int minX = 150000;
//    int maxX = 100000;
//    int minY = 150000;
//    int maxY = 100000;
    float posX = (event->x() - 250) * 150000 / 250;
    float posY = (event->y() - 250) * 150000 / 250;
    //QDialog *box = new QDialog(this);
    //QLabel *msg = new QLabel(box);

//    ProcessHacking processHacking(processName, windowName, dllName);
//    ReadProcessMemory(processHacking->m_handleProcess, (PBYTE*)(processHacking->m_dwGameLogic + 0x00097D80), &PointerAddress, sizeof(DWORD), 0);
//    ReadProcessMemory(processHacking->m_handleProcess, (PBYTE*)(PointerAddress + 0x170), &PointerAddress, sizeof(DWORD), 0);
//    ReadProcessMemory(processHacking->m_handleProcess, (PBYTE*)(PointerAddress + 0x238), &PointerAddress, sizeof(DWORD), 0);
//    ReadProcessMemory(processHacking->m_handleProcess, (PBYTE*)(PointerAddress + 0x27C), &PointerAddress, sizeof(DWORD), 0);
//    ReadProcessMemory(processHacking->m_handleProcess, (PBYTE*)(PointerAddress + 0x74), &PointerAddress, sizeof(DWORD), 0);

    WriteProcessMemory(processHacking->m_handleProcess, (PBYTE*)(PointerAddress + posXOffset), &posX, sizeof(posX), 0);
    WriteProcessMemory(processHacking->m_handleProcess, (PBYTE*)(PointerAddress + posYOffset), &posY, sizeof(posY), 0);

//    float positionX, positionY, positionZ, velocity;
//    ReadProcessMemory(processHacking->m_handleProcess, (PBYTE*)(PointerAddress + posXOffset), &positionX, sizeof(float), 0);
//    ReadProcessMemory(processHacking->m_handleProcess, (PBYTE*)(PointerAddress + posYOffset), &positionY, sizeof(float), 0);
//    ReadProcessMemory(processHacking->m_handleProcess, (PBYTE*)(PointerAddress + posZOffset), &positionZ, sizeof(float), 0);
//    ReadProcessMemory(processHacking->m_handleProcess, (PBYTE*)(PointerAddress + velocityOffset), &velocity, sizeof(float), 0);
//    ProcessHacking ph;
//    PROCESSENTRY32 m_gameProcess;
//    ph.FindProcessName(processName, &m_gameProcess);
//    DWORD pid = m_gameProcess.th32ProcessID;

    //QString posString = QString::number(velocity) + QString(" x ") + QString::number(posY);

    //msg->setText(posString);
    //box->show();
}

void MainWindow::ModifyHeight(int height)
{
    m_sliderPosition->setText("Height : " + QString::number(height));

//    ProcessHacking processHacking(processName, windowName, dllName);
//    ReadProcessMemory(processHacking->m_handleProcess, (PBYTE*)(processHacking->m_dwGameLogic + 0x00097D80), &PointerAddress, sizeof(DWORD), 0);
//    ReadProcessMemory(processHacking->m_handleProcess, (PBYTE*)(PointerAddress + 0x170), &PointerAddress, sizeof(DWORD), 0);
//    ReadProcessMemory(processHacking->m_handleProcess, (PBYTE*)(PointerAddress + 0x238), &PointerAddress, sizeof(DWORD), 0);
//    ReadProcessMemory(processHacking->m_handleProcess, (PBYTE*)(PointerAddress + 0x27C), &PointerAddress, sizeof(DWORD), 0);
//    ReadProcessMemory(processHacking->m_handleProcess, (PBYTE*)(PointerAddress + 0x74), &PointerAddress, sizeof(DWORD), 0);

    float h = height;
    WriteProcessMemory(processHacking->m_handleProcess, (PBYTE*)(PointerAddress + posZOffset), &h, sizeof(h), 0);
}
