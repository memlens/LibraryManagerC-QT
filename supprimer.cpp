#include "supprimer.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

bool supprimerLivre(const QString &isbn) {
    QSqlQuery query;
    query.prepare("DELETE FROM livres2 WHERE isbn = :isbn");
    query.bindValue(":isbn", isbn);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la suppression du livre : " << query.lastError().text();
        return false;
    }

    if (query.numRowsAffected() > 0) {
        return true;
    } else {
        qDebug() << "Aucun livre trouvé avec l'ISBN : " << isbn;
        return false;
    }
}

