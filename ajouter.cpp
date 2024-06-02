// ajouter.cpp
#include "ajouter.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>

bool ajouterLivre(const QString &titre, const QString &auteur, const QString &genre, int annee, const QString &isbn) {
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Erreur : La base de données n'est pas ouverte.";
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO livres2 (titre, auteur, genre, annee, isbn) VALUES (:titre, :auteur, :genre, :annee, :isbn)");
    query.bindValue(":titre", titre);
    query.bindValue(":auteur", auteur);
    query.bindValue(":genre", genre);
    query.bindValue(":annee", annee);
    query.bindValue(":isbn", isbn);

    if (!query.exec()) {
        qDebug() << "Erreur : Impossible d'ajouter le livre : " << query.lastError().text();
        return false;
    }

    qDebug() << "Livre ajouté avec succès !";
    return true;
}
