#ifndef CONNECTION_H
#define CONNECTION_H
#include "QSqlDatabase"
#include "QDebug"
#include "QSqlError"

bool connection_db();

void deconnection_db();
#endif // CONNECTION_H
