#include "mainwindow.h"

#include <QApplication>
#include <QtSql>
#include "cdebug.h"


static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("music_store");

    if (!db.open()) {
        CDEBUG << "Cannot open database:" << db.lastError();
        return false;
    } else {
        CDEBUG << db.userName() << db.hostName() << db.password();
    }
    return true;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (!createConnection()) {
            return -1;
    }

    MainWindow w;
    w.show();
    return a.exec();
}
