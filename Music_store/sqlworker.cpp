#include "sqlworker.h"
#include <QSqlField>
#include <QEventLoop>
#include "cdebug.h"
#include "QApplication"

const int MLS=1000;
const int DATAPARTS = 512;

SqlWorker::SqlWorker(QObject *parent) : QObject(parent)
{
    CDEBUG;
    flagStopProcess  = false;
}

SqlWorker::~SqlWorker(){}

void SqlWorker::setQuery(const QString &sqlStr, const QSqlDatabase &db_)
{
    m_sqlQuery = sqlStr;
    db = QSqlDatabase::cloneDatabase(db_,"abc");
}

QStringList SqlWorker::getHorizontalHeader(const QString &sql, const QSqlDatabase &db_, QString &lastErr)
{
    if(sql.simplified().isEmpty()) {

        CDEBUG << "SQL IS EMPTY!";
        return QStringList();
    }
    QString str = "SELECT * FROM (" + sql + ") LIMIT 1";
    CDEBUG << str;
    QSqlQuery qu(db_);

    if ( !qu.exec(str)) {        
        QSqlError serr = qu.lastError();
        lastErr = serr.text();
        return QStringList();
    }
    QStringList lst;

    for(int i=0; i<qu.record().count(); i++)
        lst << qu.record().fieldName(i);

    return lst;
}


void SqlWorker::process()
{
    CDEBUG << "BEGIN...";

    loadDataPatrs(m_sqlQuery);

    CDEBUG << "WORKER FINISHED. GOODBYE!";
    emit finished();
}

void SqlWorker::stopProcess()
{
    flagStopProcess = true;
    CDEBUG << "WORKER ANSVER STOP PROCESS." << VAR(flagStopProcess);
}

void SqlWorker::loadDataPatrs(const QString sql_)
{
    QTime tm; tm.start();
    CDEBUG << "BEGIN ALL LOAD...";

    emit needClearData();

    QString strSql = "SELECT * FROM (" +sql_+ ")";
    if(!qu.exec(strSql))
    {
        sqlError = qu.lastError();
        emit problems( sqlError.text() );
        return;
    }

    int iterCount=0; //, fieldCount = qu.record().count()/*, mult=1*/;

    CStandartItemRowList lstRows; // QList< one row >

    while(qu.next()) {

        ++iterCount;

        lstRows << recordToItems(qu.record());

        if( !(lstRows.count()%DATAPARTS) )
        {
            emit appendRows(lstRows);
            lstRows.clear();
        }

        if(isStopProcess()) return;        
    }

    emit appendRows(lstRows);

    CDEBUG << "...END LOAD ALL" << VAR(iterCount) << "TIME MLS:" << tm.elapsed();
}

CStandartItemRow SqlWorker::recordToItems(const QSqlRecord &rec)
{
    CStandartItemRow items;
    for(int i=0; i<rec.count(); i++)
    {
        QVariant v = rec.field(i).value();
        QStandardItem *item = new QStandardItem();
        item->setData(v,Qt::EditRole);
        item->setData(v,Qt::DisplayRole);
        items << item;
    }
    return items;
}

CStandartItemRowList SqlWorker::recordsToItemsList(const QList<QSqlRecord> &lstRec)
{
    CStandartItemRowList itemsList;

    foreach (QSqlRecord r, lstRec) {
        itemsList << recordToItems(r);
    }
    return itemsList;
}


QSqlDatabase SqlWorker::cloneDB(const QSqlDatabase &_db)
{
    return QSqlDatabase::cloneDatabase(_db,"new");
}

void SqlWorker::reconnect()
{
    db.close();
    db.open();
}

void SqlWorker::delayMls(int mls)
{
    QEventLoop loop; QTimer::singleShot(mls, &loop, SLOT(quit())); loop.exec();
}
