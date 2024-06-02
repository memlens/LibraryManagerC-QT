#ifndef MODIFIER_H
#define MODIFIER_H

#include <QString>
#include <QSqlDatabase>

bool mettreAJourLivre(const QString &isbn, const QString &titre, const QString &auteur, const QString &genre, int annee);

#endif // MODIFIER_H
