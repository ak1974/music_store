#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cdebug.h"
#include <QCommonStyle>
#include <QDateTime>
#include "sqlhelper.h"
#include <QSqlQuery>
#include <QCompleter>

const int INVALID_ID = -1;

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

    QCommonStyle style;
    ui->tbClearFilterTrack->setIcon(style.standardIcon(QStyle::SP_LineEditClearButton));
    ui->tbClearFilterTrack->setToolTip(tr("Очистить фильтр"));
    ui->leFilter->setPlaceholderText("track filter...");

    ui->cbBandName->setToolTip(tr("Список музыкальных групп"));
    ui->tbAddBand->setToolTip(tr("Создать новую группу"));
    ui->tbDelBand->setToolTip(tr("Удалить группу"));
    ui->tbAddArtist->setToolTip(tr("Добавить участника в группу"));
    ui->tbDelArtist->setToolTip(tr("Удалить участника из группы"));
    ui->tbAddSingl->setToolTip(tr("Добавить композицию/песню"));
    ui->tbDelSingl->setToolTip(tr("Удалить композицию"));

//    ui->tableView->setModel(&model);
//    ui->tableView->show();
//    ui->tableView->selectAll();

    // tab2 -----------

    ui->splitter->setCollapsible(0,false);// QStyle::SP_DialogSaveButton

    ui->tbClearFilter2->setIcon(style.standardIcon(QStyle::SP_LineEditClearButton));
    ui->tbAddTrack->setIcon(style.standardIcon(QStyle::SP_MediaSeekBackward));
    ui->tbRemTrack->setIcon(style.standardIcon(QStyle::SP_MediaSeekForward));
    ui->tbRemCurrentTrack->setIcon(style.standardIcon(QStyle::SP_DialogCloseButton));
    ui->tbBreakAlbum->setIcon(style.standardIcon(QStyle::SP_BrowserReload));
    ui->tbSaveAlbum->setIcon(style.standardIcon(QStyle::SP_DialogSaveButton));

    ui->leFilterTab2->setPlaceholderText("track filter...");

    ui->cBoxCompany->setToolTip(tr("Список компаний-производителей"));
    ui->cBoxAlbum->setToolTip(tr("Список альбомов, выпущенных компанией"));
    ui->leSeller->setToolTip(tr("Оптовый поставщик альбома"));
    ui->tbAddTrack->setToolTip(tr("Добавить трек к альбому"));
    ui->tbRemTrack->setToolTip(tr("Удалить трек из альбома"));
    ui->tbRemCurrentTrack->setToolTip(tr("Удалить текущий трек из альбома"));
    ui->tbAddRelease->setToolTip(tr("Добавить релиз альбома"));
    ui->tbRemRelease->setToolTip(tr("Удалить релиз альбома"));
    ui->tbBreakAlbum->setToolTip(tr("Отменить все изменения альбома"));
    ui->tbSaveAlbum->setToolTip(tr("Сохранить изменения в базу"));
    ui->tbClearFilter2->setToolTip(tr("Очистить фильтр"));

    // tab3 -----------

    ui->leYear->setPlaceholderText("Отчетный год в формате YYYY");
    ui->leYear->setValidator( new QIntValidator(0, 9999, this) );
    ui->pbReport1->setToolTip(tr("Лидеры продаж по количеству дисков."));
    ui->pbReport2->setToolTip(tr("Лидеры продаж по объёму прибыли."));
    ui->tbAdd2store->setToolTip(tr("Добавить диски на склад..."));
    ui->tbDel2store->setToolTip(tr("Удалить диски со склада..."));
    ui->pbApply->setToolTip(tr("Сохранить запись"));

    fillComboBox( ui->cbBandName, SQLHELPER::sqlAllBandNameAndId );
}



void MainWindow::fillComboBox(QComboBox *cbox_, const QString &sql_)
{
    if( !cbox_ || sql_.simplified().isEmpty()) return;

    cbox_->clear();

    QStringList complLst;
    QSqlQuery qu(sql_);

    if( qu.exec() )
    {
        while (qu.next())
        {
            int id = qu.value("id").toInt();
            QString name = qu.value("name").toString();
            CDEBUG << id << name;
            cbox_->addItem(name,id);
            complLst << name;
        }
    }

    QCompleter* cmpl = new QCompleter(complLst,this);
    cmpl->setCaseSensitivity(Qt::CaseInsensitive);
    cmpl->setCompletionMode(QCompleter::PopupCompletion);
    //cmpl->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    cbox_->setCompleter(cmpl);
}


MainWindow::~MainWindow()
{
    delete ui;
}


