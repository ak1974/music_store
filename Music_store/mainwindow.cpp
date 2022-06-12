#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cdebug.h"
#include <QCommonStyle>
#include <QDateTime>
#include "sqlhelper.h"
#include <QSqlQuery>
#include <QCompleter>
#include <QMessageBox>
#include <QInputDialog>

const int INVALID_ID = -1;
const int TRACKS_NAME_COLUMN    = 0;
const int TRACKS_ALBUM_COLUMN   = 1;
const int TRACKS_BAND_ID_COLUMN = 2;
const int TRACKS_MATRIX_COLUMN  = 3;
const int TRACKS_SINGLE_COLUMN  = 4;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Music store");

    tmpConnnect(); // until construction only

    initFrom();
    fillForm();
}

void MainWindow::initFrom()
{
    CDEBUG;
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

    // tab2 -----------

    ui->splitter->setCollapsible(0,false);    

    ui->tbClearFilter2->setIcon(style.standardIcon(QStyle::SP_LineEditClearButton));
    ui->tbAddTrack->setIcon(style.standardIcon(QStyle::SP_MediaSeekBackward));
    ui->tbRemTrack->setIcon(style.standardIcon(QStyle::SP_MediaSeekForward));
    ui->tbRemTrack->hide();
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
    ui->tbSaveAlbum->setToolTip(tr("Сохранить изменения в базу..."));
    ui->tbClearFilter2->setToolTip(tr("Очистить фильтр"));
    ui->tbAddAlbum->setToolTip(tr("Добавить новый альбом"));
    ui->tbRemAlbum->setToolTip(tr("Удалить текущий альбом..."));

    // tab3 -----------

    ui->leYear->setPlaceholderText(tr("Отчетный год в формате YYYY"));
    ui->leYear->setValidator( new QIntValidator(0, 9999, this) );
    ui->leYear->setToolTip(tr("Отчетный год в формате YYYY"));
    ui->pbReport1->setToolTip(tr("Лидеры продаж по количеству дисков."));
    ui->pbReport2->setToolTip(tr("Лидеры продаж по объёму прибыли."));
    ui->tbAdd2store->setToolTip(tr("Добавить диски на склад..."));
    ui->tbDel2store->setToolTip(tr("Удалить диски со склада..."));
    ui->pbApply->setToolTip(tr("Сохранить запись"));
}

void MainWindow::fillForm()
{
    initArtistTable();
    initSinglesTable();
    initAllSinglesTable();

    try
    {
        fillComboBox( ui->cbBandName, SQLHELPER::sqlAllBandNameAndId);
        fillComboBox( ui->cBoxCompany, SQLHELPER::sqlAllCompanyNameAndId);
    }
    catch (QString err)
    {
        QMessageBox::information(this, this->windowTitle(), err);
    }
    connect(ui->cbBandName, SIGNAL(currentIndexChanged(int)), this, SLOT(bandNameChange(int)), Qt::UniqueConnection);
    emit ui->cbBandName->currentIndexChanged(0);

    connect(ui->cBoxCompany, SIGNAL(currentIndexChanged(int)), this, SLOT(companyNameChange(int)), Qt::UniqueConnection);
    emit ui->cBoxCompany->currentIndexChanged(0);

    connect(ui->tbClearFilterTrack, SIGNAL(clicked(bool)), ui->leFilter, SLOT(clear()), Qt::UniqueConnection );
    connect(ui->leFilter, SIGNAL(textChanged(QString)), this, SLOT(setFilterSinglesModel(QString)));

    connect(ui->cBoxAlbum, SIGNAL(currentIndexChanged(int)), this, SLOT(albumNameChange(int)), Qt::UniqueConnection);

    connect(ui->tbClearFilter2, SIGNAL(clicked(bool)), ui->leFilterTab2, SLOT(clear()), Qt::UniqueConnection );
    connect(ui->leFilterTab2, SIGNAL(textChanged(QString)), this, SLOT(setFilterAllSinglesModel(QString)));

    connect(ui->tableWidgetTracks, SIGNAL(clicked(QModelIndex)), this, SLOT(decorationForm()));
    connect(ui->tvAllTracks, SIGNAL(clicked(QModelIndex)), this, SLOT(decorationForm()));

    ui->tbRemCurrentTrack->setEnabled(false);
    ui->tbAddTrack->setEnabled(false);

    connect(ui->tbRemCurrentTrack, SIGNAL(clicked(bool)), this, SLOT(remCurrentAlbumSingle()) );
    connect(ui->tbAddTrack, SIGNAL(clicked(bool)), this, SLOT(addOneSingeToAlbum()) );
    connect(ui->tbSaveAlbum, SIGNAL(clicked(bool)), this, SLOT(saveAlbumToDB()));
    connect(ui->tbBreakAlbum, SIGNAL(clicked(bool)), this, SLOT(fillAlbumTracksTable()));

    connect(ui->tbAddAlbum, SIGNAL(clicked(bool)), this, SLOT(addAlbum()));
    connect(ui->tbRemAlbum, SIGNAL(clicked(bool)), this, SLOT(remAlbum()));
}

void MainWindow::initArtistTable()
{
    if( getArtistSqlModel() ) return;

    m_artistSqlModel = new QSqlTableModel(this);
    m_artistSqlModel->setTable(SQLHELPER::sqlArtistRoleView);
    m_artistSqlModel->select();
    m_artistSqlModel->setHeaderData(0, Qt::Horizontal, tr("Роль"));
    m_artistSqlModel->setHeaderData(1, Qt::Horizontal, tr("Имя"));

    ui->tvArtist->setModel( getArtistSqlModel());
    ui->tvArtist->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tvArtist->hideColumn(TRACKS_BAND_ID_COLUMN);
    ui->tvArtist->horizontalHeader()->setStretchLastSection(true);
    ui->tvArtist->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_artistSqlModel->select();
}

void MainWindow::initSinglesTable()
{
    if( getSinglesSqlModel() ) return;

    m_singlesSqlModel = new QSqlTableModel(this);
    m_singlesSqlModel->setTable(SQLHELPER::sqlSinglesAlbumView);
    m_singlesSqlModel->select();
    m_singlesSqlModel->setHeaderData(0, Qt::Horizontal, tr("Композиция"));
    m_singlesSqlModel->setHeaderData(1, Qt::Horizontal, tr("Альбом"));

    ui->tvSingles->setModel( getSinglesSqlModel() );
    ui->tvSingles->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tvSingles->hideColumn(TRACKS_BAND_ID_COLUMN);
    ui->tvSingles->hideColumn(TRACKS_MATRIX_COLUMN);
    ui->tvSingles->hideColumn(TRACKS_SINGLE_COLUMN);
    ui->tvSingles->horizontalHeader()->setStretchLastSection(true);
    ui->tvSingles->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_singlesSqlModel->select();
}

void MainWindow::initAllSinglesTable()
{
    m_singlesSqlItemModel.setTable(SQLHELPER::sqlSinglesAlbumView);
    m_singlesSqlItemModel.select();
    m_singlesSqlItemModel.setHeaderData(0, Qt::Horizontal, tr("Композиция"));
    m_singlesSqlItemModel.setHeaderData(1, Qt::Horizontal, tr("Альбом"));

    m_singlesProxyModel.setSourceModel(&m_singlesSqlItemModel);

    ui->tvAllTracks->setModel(&m_singlesProxyModel);
    ui->tvAllTracks->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tvAllTracks->setSelectionMode(QAbstractItemView::SingleSelection);
//  ui->tvAllTracks->hideColumn(TRACKS_ALBUM_COLUMN);
    ui->tvAllTracks->hideColumn(TRACKS_BAND_ID_COLUMN);
    ui->tvAllTracks->hideColumn(TRACKS_MATRIX_COLUMN);
    ui->tvAllTracks->hideColumn(TRACKS_SINGLE_COLUMN);
    ui->tvAllTracks->horizontalHeader()->setStretchLastSection(true);
    ui->tvAllTracks->setEditTriggers(QAbstractItemView::NoEditTriggers);
}


void MainWindow::setFilterArtistModel(int bandId)
{
    if( getArtistSqlModel() )
        getArtistSqlModel()->setFilter(QString("b_id = %1").arg(bandId));
}

void MainWindow::setFilterSinglesModel(int bandId, const QString &fltName)
{
    if( !getSinglesSqlModel() ) return;
    QString flt = QString("b_id = %1 and name like '%%2%'").arg(bandId).arg(fltName);
    getSinglesSqlModel()->setFilter(flt);
}


void MainWindow::setFilterAllSinglesModel(const QString &flt_)
{
    m_singlesProxyModel.setFilterFixedString(flt_);
    emit decorationForm();
}

void MainWindow::remCurrentAlbumSingle()
{
    CDEBUG;
    ui->tableWidgetTracks->removeRow(ui->tableWidgetTracks->currentRow());
}

void MainWindow::addOneSingeToAlbum()
{
    QModelIndex mi = ui->tvAllTracks->currentIndex();
    ui->tvAllTracks->showColumn(TRACKS_MATRIX_COLUMN);
    ui->tvAllTracks->showColumn(TRACKS_SINGLE_COLUMN);
    ui->tvAllTracks->showColumn(TRACKS_BAND_ID_COLUMN);
    ui->tvAllTracks->selectRow(mi.row());
    QModelIndexList miList = ui->tvAllTracks->selectionModel()->selectedIndexes();
    ui->tvAllTracks->hideColumn(TRACKS_MATRIX_COLUMN);
    ui->tvAllTracks->hideColumn(TRACKS_SINGLE_COLUMN);
    ui->tvAllTracks->hideColumn(TRACKS_BAND_ID_COLUMN);

    QList<int> colums({TRACKS_NAME_COLUMN,TRACKS_MATRIX_COLUMN,TRACKS_SINGLE_COLUMN,TRACKS_BAND_ID_COLUMN});
    const int row = ui->tableWidgetTracks->rowCount();
    ui->tableWidgetTracks->insertRow(row);

    int twCol=0;
    for(auto col:colums)
        ui->tableWidgetTracks->setItem(row, twCol++, new QTableWidgetItem(miList.value(col).data().toString()));
}

void MainWindow::decorationForm()
{
    int TABALBUM=1;
    //CDEBUG << ui->tabWidget->currentIndex();
    if( ui->tabWidget->currentIndex() == TABALBUM )
    {
        ui->tbRemCurrentTrack->setEnabled( ui->tableWidgetTracks->selectedItems().count());
        ui->tbAddTrack->setEnabled( ui->tvAllTracks->selectionModel()->selectedRows().count());
    }
}

void MainWindow::setFilterSinglesModel(const QString &flt_)
{
    int bandId = ui->cbBandName->currentData(UserIdRole).toInt();
    setFilterSinglesModel(bandId,flt_);
}

void MainWindow::bandNameChange(int id)
{
    ui->lbBandInfo->setText( ui->cbBandName->itemData(id, Qt::UserRole).toString() );
    int bandId = ui->cbBandName->itemData(id, UserIdRole).toInt();

    setFilterArtistModel(bandId);
    setFilterSinglesModel(bandId, ui->leFilter->text().simplified());
}

void MainWindow::companyNameChange(int id)
{
    ui->cBoxCompany->setToolTip(ui->cBoxCompany->itemData(id, Qt::UserRole).toString());
    int idComp = ui->cBoxCompany->itemData(id, UserIdRole).toInt();
    CDEBUG << idComp;
    fillComboBox( ui->cBoxAlbum, SQLHELPER::sqlAllAlbumNameForCompany.arg(idComp), false);
    emit ui->cBoxAlbum->setCurrentIndex(ui->cBoxAlbum->count()-1);
    albumNameChange( ui->cBoxAlbum->currentIndex() );
}

void MainWindow::companyNameChange()
{
    int id = ui->cBoxCompany->currentIndex();
    CDEBUG << id;
    companyNameChange(id);
}


void MainWindow::albumNameChange(int id)
{    
    int matrixId = ui->cBoxAlbum->itemData(id, UserIdRole).toInt();

    // Seller
    QString err;
    QVariant val = selectValue(SQLHELPER::sqlSellerByMatrixId.arg(matrixId), err);
    if( !err.isEmpty())
    {
        CDEBUG << err;
        return;
    }
    ui->leSeller->setText( val.toString() );

    // Date release
    QString sql = SQLHELPER::sqlReleaseDateByMatrixId.arg(matrixId);
    if( !m_releaseQueryModel )
    {
        m_releaseQueryModel = new QSqlQueryModel(this);
        ui->tvDateRelease->setModel(m_releaseQueryModel);
        ui->tvDateRelease->horizontalHeader()->setStretchLastSection(true);
    }
    m_releaseQueryModel->setQuery( sql );

    // Album tracks
    fillAlbumTracksTable();

    emit decorationForm();
}

void MainWindow::fillAlbumTracksTable()
{
    int matrixId = ui->cBoxAlbum->currentData(UserIdRole).toInt();
    try
    {
        fillTableWidgetFromDB(*ui->tableWidgetTracks, SQLHELPER::sqlSinglesByMatrixId.arg(matrixId));
    }
    catch (QString err)
    {
        QMessageBox::information(this, this->windowTitle(), err);
        return;
    }
    int NAME=0, AM_ID=1, S_ID=2, B_ID=3;
    ui->tableWidgetTracks->horizontalHeaderItem(NAME)->setData(Qt::DisplayRole, QVariant("Композиция"));
    ui->tableWidgetTracks->hideColumn(AM_ID);
    ui->tableWidgetTracks->hideColumn(S_ID);
    ui->tableWidgetTracks->hideColumn(B_ID);
    ui->tableWidgetTracks->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetTracks->setSelectionMode(QAbstractItemView::SingleSelection);

    emit decorationForm();
}

void MainWindow::saveAlbumToDB()
{
    int matrixId = ui->cBoxAlbum->currentData(UserIdRole).toInt();
    auto reply = QMessageBox::question(this, ui->tbSaveAlbum->toolTip(),
                                       "Сохранить альбом '"
                                       + ui->cBoxAlbum->currentText()
                                       + "' в базу данных?\nЭта операция необратима.",
                                       QMessageBox::Yes|QMessageBox::No);
    if (reply != QMessageBox::Yes) return;

    QString sql = SQLHELPER::sqlDeleteSinglesToAlbum.arg(matrixId);

    try {
        execWithException(sql);
    }
    catch (QString err) {
        QMessageBox::information(this, this->windowTitle(), err);
        return;
    }
    const int S_ID=2, B_ID=3;

    QStringList sqlValues;
    QString valMask = "(%1,%2,%3)";

    for(int row=0; row < ui->tableWidgetTracks->rowCount(); ++row )
    {

        QString sid = ui->tableWidgetTracks->item(row,S_ID)->text();
        QString bid = ui->tableWidgetTracks->item(row,B_ID)->text();
        sqlValues << valMask.arg(matrixId).arg(sid).arg(bid);
    }

    sql = SQLHELPER::sqlInsertSinglesToAlbum + sqlValues.join(",");

    try {
        execWithException(sql);
    }
    catch (QString err) {
        QMessageBox::information(this, this->windowTitle(), err);
        return;
    }
}

void MainWindow::addAlbum()
{
    int idComp = ui->cBoxCompany->currentData(UserIdRole).toInt();
    bool ok;
    QString text = QInputDialog::getText(this,
                                 QString::fromUtf8("Добавить новый альбом"),
                                 QString::fromUtf8("Введите название нового альбома:"),
                                 QLineEdit::Normal,
                                 "Самый лучший диск", &ok);
    if(!ok) return;
    if(text.simplified().isEmpty())
    {
        QMessageBox::information(this, this->windowTitle(), "Название альбома не может быть пустым.");
        return;
    }
    QString err;
    QVariant val = selectValue(SQLHELPER::sqlSelectMaxMatrixId, err);
    const int BEGIN_ID = 100000000;
    int am_id = val.isValid() ? val.toInt()+1 : BEGIN_ID;

    QString sql = SQLHELPER::sqlInsertAlbumToMatrix.arg(am_id).arg(text).arg(idComp);
//    CDEBUG << sql;
    try {
        execWithException(sql);
    }
    catch (QString err) {
        QMessageBox::information(this, this->windowTitle(), err);
        return;
    }
    companyNameChange();
}

void MainWindow::remAlbum()
{
    auto reply = QMessageBox::question(this, ui->tbSaveAlbum->toolTip(),
                                       "Удалить альбом '"
                                       + ui->cBoxAlbum->currentText()
                                       + "' из базы данных?\nЭта операция необратима.",
                                       QMessageBox::Yes|QMessageBox::No);
    if (reply != QMessageBox::Yes) return;

    int matrixId = ui->cBoxAlbum->currentData(UserIdRole).toInt();
    QString sql = SQLHELPER::sqlDeleteMatrix.arg(matrixId);

    try {
        execWithException(sql);
    }
    catch (QString err) {
        QMessageBox::information(this, this->windowTitle(), err);
        return;
    }
    companyNameChange();
}

void MainWindow::underConstruction()
{
    QMessageBox::information(this, this->windowTitle(),"Function under construction.");
}

QSqlTableModel *MainWindow::getArtistSqlModel() const
{
    return m_artistSqlModel;
}

QSqlTableModel *MainWindow::getSinglesSqlModel() const
{
    return m_singlesSqlModel;
}

void MainWindow::tmpConnnect()
{
    // QAbstractButton::clicked()

    QList<QAbstractButton*> abLst;
    abLst << ui->tbDelArtist << ui->tbAddArtist << ui->tbAddSingl << ui->tbDelSingl
          << ui->tbAddRelease << ui->tbRemRelease
          << ui->tbRemTrack << ui->tbAdd2store << ui->tbDel2store
          << ui->pbApply << ui->pbReport2 << ui->pbReport1 << ui->tbAddBand << ui->tbDelBand;

    foreach (auto ab, abLst) {
        connect(ab, SIGNAL(clicked(bool)), this, SLOT( underConstruction()), Qt::UniqueConnection);
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}



