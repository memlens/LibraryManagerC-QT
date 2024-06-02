#include "connection.h"

QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
bool connection_db(){
    db.setHostName("localhost");
    db.setDatabaseName("tuto1");
    db.setUserName("test");
    db.setPassword("test");

    if(!db.open()){
        qDebug() <<"Erreur : Impossible de se conneter : " << db.lastError().text();
        return false;
    }else{
        qDebug() << "Connexion effectuée avec succes !";
        return true;
    }
}


void deconnection_db(){
    if (db.isOpen()) {
        db.close();
        qDebug() << "Déconnexion effectuée avec succès !";
    } else {
        qDebug() << "La base de données n'est pas ouverte.";
    }
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
}
