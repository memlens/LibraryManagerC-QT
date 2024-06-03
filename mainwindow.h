#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include "connection.h"
#include "rechercher.h"
#include "supprimer.h"
#include "modifier.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_AjouterBouton_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_pushButton_3_clicked();


    void on_pushButton_16_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_4_clicked();

    void on_comboBox_activated(int index);

    void on_pushButton_17_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QSqlTableModel *model;
    QSqlQueryModel *model2;
};
#endif // MAINWINDOW_H
