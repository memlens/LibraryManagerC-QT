#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QTabWidget"
#include "QString"
#include "ajouter.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , model(new QSqlTableModel(this))
{
    ui->setupUi(this);

    // Appeler la fonction de connexion à la base de données
    if (!connection_db()) {
        exit(1);  // Arrêter l'application si la connexion échoue
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    deconnection_db();
}


void MainWindow::on_AjouterBouton_clicked()
{
    QString titre = ui->lineEditATitre->text();
    QString auteur = ui->lineEditAAuteur->text();
    QString genre = ui->lineEditAGenre->text();
    int annee = ui->lineEditAAnnee->text().toInt();
    QString isbn = ui->lineEditAISBN->text();

    if(ajouterLivre(titre, auteur, genre, annee, isbn)){
        ui->lineEditATitre->clear();
        ui->lineEditAAuteur->clear();
        ui->lineEditAGenre->clear();
        ui->lineEditAAnnee->clear();
        ui->lineEditAISBN->clear();

        ui->statusbar->showMessage("Livre ajouté avec succès !");
    }else {
        ui->statusbar->showMessage("Impossible d'ajouter le livre !");
    }
}


void MainWindow::on_tabWidget_currentChanged(int index)
{
    if(ui->tabWidget->widget(index) == ui->tabLivres){
        model->setTable("livres2");
         model->select();

         // Définissez les en-têtes des colonnes (optionnel)
         model->setHeaderData(0, Qt::Horizontal, tr("ID"));
         model->setHeaderData(1, Qt::Horizontal, tr("Titre"));
         model->setHeaderData(2, Qt::Horizontal, tr("Auteur"));
         model->setHeaderData(3, Qt::Horizontal, tr("Genre"));
         model->setHeaderData(4, Qt::Horizontal, tr("Année"));
         model->setHeaderData(5, Qt::Horizontal, tr("ISBN"));

         ui->tableView->setModel(model);
         ui->tableView->resizeColumnsToContents();
    }
}

