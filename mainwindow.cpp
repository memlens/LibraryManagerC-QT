#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QTabWidget"
#include "QString"
#include "ajouter.h"
#include "rechercher.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , model(new QSqlTableModel(this))
    , model2(new QSqlQueryModel(this))
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


void MainWindow::on_pushButton_3_clicked()
{
    //rechercher dans modifier
    QString isbn = ui->lineEdit_10->text();
    if (!rechercherEtRemplirFormulaire(isbn, ui->lineEditMTitre, ui->lineEditMAuteur, ui->lineEditMGenre, ui->lineEditMAnnee, ui->lineEditMISBN)) {
        ui->statusbar->showMessage("Aucun résultat trouvé pour l'ISBN fourni.");
    } else {
        ui->statusbar->showMessage("Formulaire rempli avec les résultats de la recherche.");
    }
}

void MainWindow::on_pushButton_16_clicked()
{
    //rechercher dans supprimer
    QString isbn = ui->lineEdit_53->text();
    if (!rechercherEtRemplirFormulaire(isbn, ui->lineEditSTitre, ui->lineEditSAuteur, ui->lineEditSGenre, ui->lineEditSAnnee, ui->lineEditSISBN)) {
        ui->statusbar->showMessage("Aucun résultat trouvé pour l'ISBN fourni.");
    } else {
        ui->statusbar->showMessage("Formulaire rempli avec les résultats de la recherche.");
    }
}


void MainWindow::on_pushButton_11_clicked()
{
    //bouton de suupression de la base de donnée
    QString isbn = ui->lineEditSISBN->text();
        if (isbn.isEmpty()) {
            ui->statusbar->showMessage("Veuillez rechercher et sélectionner un livre à supprimer.");
            return;
        }

        if (supprimerLivre(isbn)) {
            ui->lineEditSTitre->clear();
            ui->lineEditSAuteur->clear();
            ui->lineEditSGenre->clear();
            ui->lineEditSAnnee->clear();
            ui->lineEditSISBN->clear();

            ui->statusbar->showMessage("Livre supprimé avec succès.");
            model->select(); // Actualiser la vue du modèle
        } else {
            ui->statusbar->showMessage("Erreur lors de la suppression du livre.");
        }
}


void MainWindow::on_pushButton_4_clicked()
{
    //modifier les éléments éléments de la base donnée
    QString isbn = ui->lineEditMISBN->text();
    QString titre = ui->lineEditMTitre->text();
    QString auteur = ui->lineEditMAuteur->text();
    QString genre = ui->lineEditMGenre->text();
    int annee = ui->lineEditMAnnee->text().toInt();

    if(isbn.isEmpty()) {
        ui->statusbar->showMessage("Veuillez rechercher et sélectionner un livre à mettre à jour.");
        return;
    }

    if(mettreAJourLivre(isbn, titre, auteur, genre, annee)) {
        ui->lineEditMTitre->clear();
        ui->lineEditMAuteur->clear();
        ui->lineEditMGenre->clear();
        ui->lineEditMAnnee->clear();
        ui->lineEditMISBN->clear();

        ui->statusbar->showMessage("Livre mis à jour avec succès.");
        model->select(); // Actualiser la vue du modèle
    } else {
        ui->statusbar->showMessage("Erreur lors de la mise à jour du livre.");
    }
}


void MainWindow::on_comboBox_activated(int index)
{
    ui->comboBox_2->addItem("ISBN");
    ui->comboBox_2->addItem("Titre");
    ui->comboBox_2->addItem("Genre");
    ui->comboBox_2->addItem("Année");
}


void MainWindow::on_pushButton_17_clicked()
{
    QString valeur = ui->lineEdit_54->text();
    QString categorie = ui->comboBox_2->currentText(); // Récupérer le critère de recherche sélectionné

    if (!rechercherParCategorie(valeur, categorie, model2)) {
        ui->statusbar->showMessage("Aucun résultat trouvé pour la recherche.");
    } else {
        ui->statusbar->showMessage("Vue mise à jour avec les résultats de la recherche.");
        ui->tableView->setModel(model2);
        ui->tableView->resizeColumnsToContents();
    }
}


void MainWindow::on_pushButton_clicked()
{
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

