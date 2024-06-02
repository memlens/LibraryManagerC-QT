#include "modifier.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

bool mettreAJourLivre(const QString &isbn, const QString &titre, const QString &auteur, const QString &genre, int annee) {
    QSqlQuery query;
    query.prepare("UPDATE livres2 SET titre = :titre, auteur = :auteur, genre = :genre, annee = :annee WHERE isbn = :isbn");
    query.bindValue(":titre", titre);
    query.bindValue(":auteur", auteur);
    query.bindValue(":genre", genre);
    query.bindValue(":annee", annee);
    query.bindValue(":isbn", isbn);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la mise à jour du livre : " << query.lastError().text();
        return false;
    }

    if (query.numRowsAffected() > 0) {
        return true;
    } else {
        qDebug() << "Aucun livre trouvé avec l'ISBN : " << isbn;
        return false;
    }
}

