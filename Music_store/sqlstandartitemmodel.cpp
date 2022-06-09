#include "sqlstandartitemmodel.h"
#include "cdebug.h"

SqlStandardItemModel::SqlStandardItemModel(QObject *parent) : QStandardItemModel(parent)
{
    CDEBUG;
    initModel();
}

SqlStandardItemModel::SqlStandardItemModel(const QSqlDatabase &sqb_,
                                           const QString &_query,
                                           QObject *parent)
    : dbase(QSqlDatabase::cloneDatabase( sqb_, "model" )),
      m_queryText(_query),
    QStandardItemModel(parent)
{    
    bool isDbOpen = dbase.open();
    CDEBUG << VAR(isDbOpen);
    initModel();
}

SqlStandardItemModel::~SqlStandardItemModel()
{
    emit stopProcess();
    modelDisconnect();
    clear();
}

void SqlStandardItemModel::setQuery(const QString &_query)
{
    m_queryText = _query;

    if( isParamInit() )
        selectHorizontalHeader();
}

void SqlStandardItemModel::initModel()
{
    qRegisterMetaType< CStandartItemRow >("CStandartItemRow");
    qRegisterMetaType< CStandartItemRowList >("CStandartItemRowList");
}

void SqlStandardItemModel::selectHorizontalHeader()
{
//  CDEBUG << query() << dataBase().connectionName();
    QString err;
    QStringList lst = SqlWorker::getHorizontalHeader(query(), dataBase(), err);

    if(lst.isEmpty()){
        CDEBUG << err;
        return;
    }

    this->setHorizontalHeaderLabels(lst);
}

QSqlError SqlStandardItemModel::lastError() const
{
    return sqlError;
}

void SqlStandardItemModel::select()
{
    if( horizontalHeaderLabels().isEmpty() ){
        selectHorizontalHeader();
    }

    sqlWorker = new SqlWorker();
    sqlWorker->setQuery(query(), dataBase() );

    QThread *thread = new QThread;
    sqlWorker->moveToThread(thread);

    connect(thread,SIGNAL(started()), sqlWorker, SLOT(process()));
    connect(sqlWorker, SIGNAL(finished()), thread,SLOT(quit()) );
    connect(this,SIGNAL(stopProcess()), sqlWorker, SLOT(stopProcess()), Qt::DirectConnection);
    connect(sqlWorker, SIGNAL(finished()), sqlWorker,SLOT(deleteLater()) );
    connect(thread,SIGNAL(finished()), thread, SLOT(deleteLater()));

    fullConnect();

    thread->start();
}

void SqlStandardItemModel::blockUpdateSignals(bool bl)
{
    sqlWorker->blockSignals(bl);
}

void SqlStandardItemModel::fullConnect()
{
    connect(sqlWorker, SIGNAL(problems(QString)), this, SIGNAL(errorModel(QString)) );

    // Добавить строки в конец (Обычно, при полном переселекте)
    connect(sqlWorker, SIGNAL(needClearData()), this, SLOT(smartClear()));
    connect(sqlWorker, SIGNAL(appendRow(CStandartItemRow)), this, SLOT(appendItems(CStandartItemRow)));
    connect(sqlWorker, SIGNAL(appendRows(CStandartItemRowList)), this, SLOT(appendItemsList(CStandartItemRowList)));
}

void SqlStandardItemModel::modelDisconnect()
{
    CDEBUG;
    disconnect(this, SLOT(smartClear()));
    disconnect(this, SLOT(appendItems(CStandartItemRow)));
    disconnect(this, SLOT(appendItemsList(CStandartItemRowList)));
}

void SqlStandardItemModel::stopAppendItems()
{
    disconnect(this, SLOT(appendItems(CStandartItemRow)));
    disconnect(this, SLOT(appendItemsList(CStandartItemRowList)));
}

void SqlStandardItemModel::startAppendItems()
{
    connect(sqlWorker, SIGNAL(appendRow(CStandartItemRow)), this,
                         SLOT(appendItems(CStandartItemRow)), Qt::BlockingQueuedConnection);

    connect(sqlWorker, SIGNAL(appendRows(CStandartItemRowList)), this,
                        SLOT(appendItemsList(CStandartItemRowList)), Qt::BlockingQueuedConnection);
}

bool SqlStandardItemModel::isParamInit()
{
    return !query().simplified().isEmpty();
}

void SqlStandardItemModel::reset()
{
    emit stopProcess();
    modelDisconnect();
    smartClear();
}

QStringList SqlStandardItemModel::horizontalHeaderLabels()
{
    QStringList lst;
    if(this->columnCount()==0) return lst;

    for(int i=0; i < this->columnCount(); ++i)
    {
        QStandardItem *si = this->horizontalHeaderItem(i);
        if(!si) continue;
        lst << si->data(Qt::DisplayRole).toString();
    }
    return lst;
}

void SqlStandardItemModel::smartClear()
{
    int rowCount = this->rowCount();
    CDEBUG << VAR(rowCount);
    removeRows(0,rowCount);
}

void SqlStandardItemModel::appendItems(CStandartItemRow row)
{
    appendRow(row);
}

void SqlStandardItemModel::appendItemsList(CStandartItemRowList rowList)
{    
    for (auto items : rowList)
            appendRow(items);
}

void SqlStandardItemModel::showItems(const CStandartItemRow &lst)
{
    CDEBUG << VAR(lst.count());
    int i=1;
    foreach (QStandardItem *si, lst) {
        CDEBUG << i++ << si->data(Qt::DisplayRole).toString();
    }
}

