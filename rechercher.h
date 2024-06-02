#ifndef RECHERCHER_H
#define RECHERCHER_H


#include <QString>
#include <QLineEdit>
#include <QSqlDatabase>

bool rechercherEtRemplirFormulaire(const QString &isbn, QLineEdit *titre, QLineEdit *auteur, QLineEdit *genre, QLineEdit *annee, QLineEdit *isbnField);


#endif // RECHERCHER_H
