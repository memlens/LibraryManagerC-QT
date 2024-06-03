#ifndef RECHERCHER_H
#define RECHERCHER_H


#include <QString>
#include <QLineEdit>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QComboBox>

bool rechercherParCategorie(const QString &valeur, const QString &categorie, QSqlQueryModel *model);

bool rechercherEtRemplirFormulaire(const QString &isbn, QLineEdit *titre, QLineEdit *auteur, QLineEdit *genre, QLineEdit *annee, QLineEdit *isbnField);


#endif // RECHERCHER_H
