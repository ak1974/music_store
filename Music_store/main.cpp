#include "mainwindow.h"

#include <QApplication>
#include <QtSql>
#include "cdebug.h"
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include <QFileDialog>

const QString DB_SQLITE_FILE_NAME = "music_store";

QString getDbPath()
{
    QString fileName = QFileDialog::getOpenFileName(0,
        ("Open sqlite 'music_store' data base"), QDir::currentPath(), "music_store" );
    return fileName;
}

static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    bool isExistDb = QFileInfo::exists(DB_SQLITE_FILE_NAME);

    if( !isExistDb )
    {
        QString dbFilePath = getDbPath();
        if(dbFilePath.isEmpty()) return false;
        db.setDatabaseName(dbFilePath);
    }
    else
    {
        db.setDatabaseName(DB_SQLITE_FILE_NAME);
    }

    if (!db.open()) {
        CDEBUG << "Cannot open database:" << db.lastError().text();
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
