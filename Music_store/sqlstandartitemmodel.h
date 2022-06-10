#ifndef SQLSTANDARTITEMMODEL_H
#define SQLSTANDARTITEMMODEL_H

/*
 *  Модель с загрузкой данных через поток.
 *  Обычно здесь-же реализуется фоновое обновление данных,
 *  если требуется постоянная актуализация записей с базой. // прим. автора :)
 */


#include <QStandardItemModel>
#include "sqlstandartitemmodel.h"
#include "sqlworker.h"
#include <QThread>
#include <QMutex>

class SqlStandardItemModel : public QStandardItemModel
{
    Q_OBJECT
public:
    SqlStandardItemModel(QObject *parent = 0);

    // Создать и получить заголовок
    SqlStandardItemModel(const QSqlDatabase &sqb_,  const QString &_query = QString(),
                              QObject *parent = 0);
    ~SqlStandardItemModel();

    QSqlError lastError() const;
    QString query() const { return m_queryText; }

    // Задать условия и получить заголовок
    void setQuery(const QString &_query);

public slots:   
    void select(); // запустить получение данных из базы
    void blockUpdateSignals(bool bl); // приостановить/продолжить обновление данных

    // Для вьюшки
signals:    
    void errorModel(const QString &errText);

    // Для потока
signals:
    void stopProcess(); // Остановка всех операци и удаление потока

private slots:
    // Для потока
    void smartClear(); // Почистить перед приёмом новых данных
    void appendItems(CStandartItemRow row);  // Для полного переселекта
    void appendItemsList(CStandartItemRowList rowList); // Для полного переселекта

private:
    SqlWorker *sqlWorker = nullptr;

    void initModel();

    void selectHorizontalHeader();
    void fullConnect();
    void modelDisconnect();
    void stopAppendItems();
    void startAppendItems();

    QStringList horizontalHeaderLabels();    
    void reset();  // Сбросить всё и очистить модель, завершить потоки    
    bool isParamInit();

    void showItems(const CStandartItemRow &lst); // debug opnly

private:
    QString m_queryText;    // Рабочий запрос

    QSqlDatabase dbase;
    const QSqlDatabase &dataBase(){
        return dbase;
    }
    QSqlError sqlError;
};

#endif // SQLSTANDARTITEMMODEL_H
