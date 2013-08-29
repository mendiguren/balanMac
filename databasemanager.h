#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDateTime>
#include <QStringList>
#include <QSqlResult>
#include <QSqlQueryModel>

class DatabaseManager : public QObject
{
public:
    DatabaseManager(QObject *parent = 0);
    ~DatabaseManager();

public:
    bool openDB();
    int insertCiudad(int cp, QString ciudad, QString provincia);
    int insertCliente(QString nombre,QString apellido, QString empresa,QString email,QString telefonofijo,QString telefonocelular,QString direccion,int ciudades_cp);
    int insertBalanza(QString marca,QString modelo,int dimension);
    int insertUbicacion(QString etiqueta,int dimension);
    int insertPrestable(QString idserie,QString observaciones,int balanzas_idbalanza);
    int insertTransaccion(QString idserie,QString prioridad,QString accesorios,QString observaciones,int clientes_idcliente,int balanzas_idbalanza,QString prestables_idprestable,int ubicaciones_idubicacion,QString dateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

    int getUbicacion(int dimension);
    QStringList getCliente(int idtransaccion);
    QVector<int> getBalanzas(int idtransaccion);
    QStringList getBalanza(int idtransaccion, int idserie);
    QStringList getTransaccion(int idtransaccion);
    QSqlQueryModel* getPrestable(int idtransaccion, QWidget *parentWidget);

    //TODO add a function to set balanza as : limpia, reparada, confirmada
    bool setBalanzaAsLimpiada(int idtransaccion);


    QStringList enumPrioridad;
    QStringList enumBalanzaSize;
private:
    QSqlDatabase db;



public slots:
    void propagateUpdates();


};

#endif // DATABASEMANAGER_H
