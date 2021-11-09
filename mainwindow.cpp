#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    info = new SysInfo(this);
    ui->comboBox->addItems(info->getPartitionList());
    setPartitionData(ui->comboBox->currentText());
    connect(ui->comboBox, &QComboBox::currentTextChanged, this, &MainWindow::setPartitionData);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setPartitionData(QString path)
{
    PartitionData* data = info->getPartitionData(path);
    ui->filesystemType->setText(data->filesystemType);
    ui->partitionName->setText(data->partitionName);
    ui->occupiedSize->setText(QString::number(data->occupiedSize) + " Гб");
    ui->freeSize->setText(QString::number(data->freeSize) + " Гб");
    ui->totalSize->setText(QString::number(data->totalSize) + " Гб");
}

