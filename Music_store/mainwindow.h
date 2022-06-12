#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QSplitter>
#include <QComboBox>
#include "sqlstandartitemmodel.h"
#include <QSortFilterProxyModel>
#include <QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    void initFrom();
    void fillForm();

    ~MainWindow();

    QSqlTableModel *getArtistSqlModel() const;
    QSqlTableModel *getSinglesSqlModel() const;

private:

    enum { UserIdRole = Qt::UserRole+1 };

    QSqlTableModel *m_artistSqlModel = nullptr;
    QSqlTableModel *m_singlesSqlModel = nullptr;
    QSqlQueryModel *m_releaseQueryModel = nullptr;

    SqlStandardItemModel  m_singlesSqlItemModel; // Модель с загрузкой данных через поток
    QSortFilterProxyModel m_singlesProxyModel;

    void initArtistTable();
    void initSinglesTable();
    void initAllSinglesTable();

    void setFilterArtistModel(int bandId);
    void setFilterSinglesModel(int bandId, const QString &fltName = QString());    

    void companyNameChange();

private slots:

    void bandNameChange(int id);
    void companyNameChange(int id);
    void albumNameChange(int id);

    void underConstruction();
    void setFilterSinglesModel(const QString &flt_);
    void setFilterAllSinglesModel(const QString &flt_);

    void remCurrentAlbumSingle();
    void addOneSingeToAlbum();    
    void fillAlbumTracksTable();
    void saveAlbumToDB();

    void addAlbum();
    void remAlbum();

    void decorationForm();

private:

    void tmpConnnect(); // debug only

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
