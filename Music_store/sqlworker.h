#ifndef SQLWORKER_H
#define SQLWORKER_H

#include <QObject>
#include <QString>
#include <QTimer>
#include <QStandardItem>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDateTime>

typedef QList<QStandardItem *> CStandartItemRow;
typedef QList<CStandartItemRow> CStandartItemRowList;

class SqlWorker : public QObject
{
    Q_OBJECT
public:
    explicit SqlWorker(QObject *parent = 0);
    ~SqlWorker();

    void setQuery(const QString &sqlStr, const QSqlDatabase &db_);

    QSqlError lastError(){ return sqlError; }
    static QStringList getHorizontalHeader(const QString &sql, const QSqlDatabase &db_, QString& lastErr);

public slots:
    void process();    // Основной процесс потока
    void stopProcess();// Остановить всё

signals:
    void finished();    
    void appendRow (CStandartItemRow row);
    void appendRows(CStandartItemRowList rowLst);

    void needClearData();
    void problems(const QString &str);

private:
    bool flagStopProcess; // Всё остановить и завершить работу
    bool isStopProcess(){ return flagStopProcess; }
    void delayMls(int mls);

    QSqlDatabase db;  //коннект подключения
    QSqlQuery qu;     // рабочий запрос
    QString m_sqlQuery; // строка запроса
    QString m_connectionName;
    QSqlError sqlError; // Последняя ошибка выполнения запроса

    void loadDataPatrs(const QString sql_); // загрузка всех данных в модель показом по частям

    CStandartItemRow recordToItems(const QSqlRecord &rec);
    CStandartItemRowList recordsToItemsList(const QList<QSqlRecord> &lstRec);

    QSqlDatabase cloneDB(const QSqlDatabase &_db);
    void reconnect();
};

#endif // SQLWORKER_H
