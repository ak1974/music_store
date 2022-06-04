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

    ~MainWindow();

private:

    QSqlTableModel model;

    void fillComboBox(QComboBox *cbox_, const QString &sql_);


    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
