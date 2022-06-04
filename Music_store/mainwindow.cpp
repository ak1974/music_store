#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cdebug.h"
#include <QCommonStyle>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Music store");

    initFrom();
}

void MainWindow::initFrom()
{
    CDEBUG;
    model.setTable("band");
    model.select();
    model.setEditStrategy(QSqlTableModel::OnFieldChange);

    // tab1 ---------

//    QCommonStyle style;
//    ui->tbAddBand->setIcon(style.standardIcon(QStyle::SP_DriveCDIcon));
//    ui->tbDelBand->setIcon(style.standardIcon(QStyle::SP_DialogCloseButton));

//    ui->tableView->setModel(&model);
//    ui->tableView->show();
//    ui->tableView->selectAll();

    // tab2 -----------


    ui->splitter->setCollapsible(0,false);


    // tab3 -----------

    ui->leYear->setPlaceholderText("Год в формате YYYY");
    // ui->leYear->setValidator();
    ui->pbReport1->setToolTip("Лидеры продаж по количеству дисков.");
    ui->pbReport2->setToolTip("Лидеры продаж по объёму прибыли.");

}




MainWindow::~MainWindow()
{
    delete ui;
}

