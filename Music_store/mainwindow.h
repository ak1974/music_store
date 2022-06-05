#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QSplitter>
#include <QComboBox>

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

    void fillComboBox(QComboBox *cbox_, const QString &sql_);
    void fillArtistTable();
    void fillSinglesTable();

    void setFilterArtistModel(int bandId);
    void setFilterSinglesModel(int bandId, const QString &fltName = QString());


private slots:

    void bandNameChange(int id);
    void companyNameChange(int id);

    void underConstruction();
    void setFilterSinglesModel(const QString &flt);

private:


    void tmpConnnect(); // debug only


    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
