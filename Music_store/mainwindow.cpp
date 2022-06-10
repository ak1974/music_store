#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cdebug.h"
#include <QCommonStyle>
#include <QDateTime>
#include "sqlhelper.h"
#include <QSqlQuery>
#include <QCompleter>
#include <QMessageBox>

const int INVALID_ID = -1;
const int BAND_ID_COLUMN = 2;

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
    fillArtistTable();
    fillSinglesTable();

    fillComboBox( ui->cbBandName, SQLHELPER::sqlAllBandNameAndId );
    connect(ui->cbBandName, SIGNAL(currentIndexChanged(int)), this, SLOT(bandNameChange(int)), Qt::UniqueConnection);
    emit ui->cbBandName->currentIndexChanged(0);

    fillComboBox( ui->cBoxCompany, SQLHELPER::sqlAllCompanyNameAndId );
    connect(ui->cBoxCompany, SIGNAL(currentIndexChanged(int)), this, SLOT(companyNameChange(int)), Qt::UniqueConnection);
    emit ui->cBoxCompany->currentIndexChanged(0);

    connect(ui->tbClearFilterTrack, SIGNAL(clicked(bool)), ui->leFilter, SLOT(clear()), Qt::UniqueConnection );
    connect(ui->leFilter, SIGNAL(textChanged(QString)), this, SLOT(setFilterSinglesModel(QString)));

    connect(ui->cBoxAlbum, SIGNAL(currentIndexChanged(int)), this, SLOT(albumNameChange(int)), Qt::UniqueConnection);

    //
    // QSqlQueryModel qm;
    // qm.setQuery();
    // qm.findChildren
    // QSqlTableModel tm;




}



void MainWindow::fillComboBox(QComboBox *cbox_, const QString &sql_, bool addCompleter)
{
    if( !cbox_ || sql_.simplified().isEmpty()) return;

    cbox_->clear();

    QStringList complLst;
    QSqlQuery qu(sql_);

    if( qu.exec() )
    {
        while (qu.next())
        {
            int idTable  = qu.value(SQLHELPER::IDTAG).toInt();
            QString name = qu.value(SQLHELPER::DISPLAYTAG).toString();
            QString info = qu.value(SQLHELPER::INFOTAG).toString();
            CDEBUG << idTable << name << info;
            cbox_->addItem(name,info);
            cbox_->setItemData(cbox_->count()-1, idTable, UserIdRole );
            complLst << name;
        }
    }
    if( !addCompleter ) return;

    QCompleter* cmpl = new QCompleter(complLst,this);
    cmpl->setCaseSensitivity(Qt::CaseInsensitive);
    cmpl->setCompletionMode(QCompleter::PopupCompletion);
    //cmpl->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    cbox_->setCompleter(cmpl);
}

void MainWindow::fillArtistTable()
{
    if( getArtistSqlModel() ) return;

    m_artistSqlModel = new QSqlTableModel(this);
    m_artistSqlModel->setTable(SQLHELPER::sqlArtistRoleView);
    m_artistSqlModel->select();
    m_artistSqlModel->setHeaderData(0, Qt::Horizontal, tr("Роль"));
    m_artistSqlModel->setHeaderData(1, Qt::Horizontal, tr("Имя"));

    ui->tvArtist->setModel( getArtistSqlModel());
    ui->tvArtist->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tvArtist->hideColumn(BAND_ID_COLUMN);
    ui->tvArtist->horizontalHeader()->setStretchLastSection(true);
    ui->tvArtist->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_artistSqlModel->select();
}

void MainWindow::fillSinglesTable()
{
    if( getSinglesSqlModel() ) return;

    m_singlesSqlModel = new QSqlTableModel(this);
    m_singlesSqlModel->setTable(SQLHELPER::sqlSinglesAlbumView);
    m_singlesSqlModel->select();
    m_singlesSqlModel->setHeaderData(0, Qt::Horizontal, tr("Композиция"));
    m_singlesSqlModel->setHeaderData(1, Qt::Horizontal, tr("Альбом"));

    ui->tvSingles->setModel( getSinglesSqlModel() );
    ui->tvSingles->setSelectionBehavior(QAbstractItemView::SelectRows);
    const int MATRIX_COLUMN = 3;
    ui->tvSingles->hideColumn(BAND_ID_COLUMN);
    ui->tvSingles->hideColumn(MATRIX_COLUMN);
    ui->tvSingles->horizontalHeader()->setStretchLastSection(true);
    ui->tvSingles->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_singlesSqlModel->select();
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
    CDEBUG << flt;
    getSinglesSqlModel()->setFilter(flt);
}

void MainWindow::setFilterSinglesModel(const QString &flt)
{
    int bandId = ui->cbBandName->currentData(UserIdRole).toInt();
    setFilterSinglesModel(bandId,flt);
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

    fillComboBox( ui->cBoxAlbum, SQLHELPER::sqlAllAlbumNameForCompany.arg(idComp), false);
    albumNameChange( ui->cBoxAlbum->currentIndex() );
}

void MainWindow::albumNameChange(int id)
{
    int matrixId = ui->cBoxAlbum->itemData(id, UserIdRole).toInt();
    QString err;
    QVariant val = selectValue(SQLHELPER::sqlSellerByMatrixId.arg(matrixId), err);
    //CDEBUG << matrixId << val << err << id;
    if( !err.isEmpty())
    {
        CDEBUG << err;
        return;
    }

    ui->leSeller->setText( val.toString() );
    QString sql = SQLHELPER::sqlReleaseDateByMatrixId.arg(matrixId);

    if( !m_releaseQueryModel )
    {
        m_releaseQueryModel = new QSqlQueryModel(this);
        ui->tvDateRelease->setModel(m_releaseQueryModel);
        ui->tvDateRelease->horizontalHeader()->setStretchLastSection(true);
        //ui->tvDateRelease->setHorizontalHeader();
        //m_releaseQueryModel->setHeaderData()
    }

    m_releaseQueryModel->setQuery( sql );
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
          << ui->tbAddRelease << ui->tbRemRelease << ui->tbBreakAlbum << ui->tbSaveAlbum
          << ui->tbAddTrack << ui->tbRemTrack << ui->tbRemCurrentTrack << ui->tbAdd2store << ui->tbDel2store
          << ui->pbApply << ui->pbReport2 << ui->pbReport1 << ui->tbAddBand << ui->tbDelBand;

    foreach (auto ab, abLst) {
        connect(ab, SIGNAL(clicked(bool)), this, SLOT( underConstruction()), Qt::UniqueConnection);
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}



