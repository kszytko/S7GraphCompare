#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QFile"
#include <QDebug>
#include <QString>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFile file("C:\\Users\\QTSWISS\\Desktop\\CrossReferencesViewer\\New folder\\FB451.GR7");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream data(&file);
    QString text = data.readAll();
    file.close();

    graph = parser.parseData(text);

    graph->makeReferences();
    graph->printReferences();
}

MainWindow::~MainWindow()
{
    delete ui;
}

