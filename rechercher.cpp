#include "rechercher.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>


bool rechercherEtRemplirFormulaire(const QString &isbn, QLineEdit *titre, QLineEdit *auteur, QLineEdit *genre, QLineEdit *annee, QLineEdit *isbnField) {
    QSqlQuery query;
    query.prepare("SELECT titre, auteur, genre, annee, isbn FROM livres2 WHERE isbn = :isbn");
    query.bindValue(":isbn", isbn);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête de recherche : " << query.lastError().text();
        return false;
    }

    if (query.next()) {
        QSqlRecord record = query.record();
        titre->setText(record.value("titre").toString());
        auteur->setText(record.value("auteur").toString());
        genre->setText(record.value("genre").toString());
        annee->setText(record.value("annee").toString());
        isbnField->setText(record.value("isbn").toString());
        return true;
    } else {
        qDebug() << "Aucun résultat trouvé pour l'ISBN : " << isbn;
        return false;
    }
}



bool rechercherParCategorie(const QString &valeur, const QString &categorie, QSqlQueryModel *model) {
    QSqlQuery query;
    QString queryString = QString("SELECT * FROM livres2 WHERE %1 = :valeur").arg(categorie);
    query.prepare(queryString);
    query.bindValue(":valeur", valeur);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la recherche du livre : " << query.lastError().text();
        return false;
    }

    model->setQuery(query);

    if (model->lastError().isValid()) {
        qDebug() << "Erreur lors de la mise à jour de la vue : " << model->lastError().text();
        return false;
    }

    if (model->rowCount() > 0) {
        return true;
    } else {
        qDebug() << "Aucun livre trouvé avec " << categorie << " : " << valeur;
        return false;
    }
}
