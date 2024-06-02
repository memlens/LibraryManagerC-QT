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
