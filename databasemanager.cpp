#include "databasemanager.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlResult>
#include <QDateTime>
#include <QSqlRecord>

DatabaseManager::DatabaseManager(QObject *parent) :
    QObject(parent)
{
    openDB();
    enumPrioridad << "Alta" << "Normal" << "Baja";
    enumBalanzaSize << "Chica" << "Mediana" << "Grande" << "Vascula"; //Importante que esten ordenadas de menor a mayor
}

DatabaseManager::~DatabaseManager()
{
    qDebug() << "Closing database";
    db.close();
}

bool DatabaseManager::openDB()
{



    //Connects to the database
    db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("ai");
    db.setDatabaseName("balanMac");


    if(!db.open())
    {
        QMessageBox::critical(0,"Database Error",db.lastError().text());
        return false;
    }
    return true;
}

int DatabaseManager::insertCiudad(int cp, QString ciudad, QString provincia)
{
    if(!db.open()){  QMessageBox::critical(0,"Database Error",db.lastError().text()); return -2; }


    QSqlQuery preQuery;
    preQuery.exec(QString("SELECT * FROM ciudades  WHERE cp = '%1';"
                          ).arg(cp));

    if(preQuery.next())
    {
        //There is a record in the table with this same information
        qDebug() << "Ciudad already exist";
        return preQuery.value(0).toInt();

    }



    QSqlQuery query;
    bool ret = query.exec(QString("INSERT INTO ciudades (cp, ciudad, provincia) VALUES('%1','%2','%3');").arg(cp).arg(ciudad).arg(provincia));
    if(ret)
    {
        return cp;
    }
    else
    {
        qDebug() << query.lastError().text();
        return -1;
    }


}

int DatabaseManager::insertCliente(QString nombre, QString apellido, QString empresa, QString email, QString telefonofijo, QString telefonocelular,QString direccion, int ciudades_cp)
{
    if(!db.open()){  QMessageBox::critical(0,"Database Error",db.lastError().text()); return -2; }

    QSqlQuery preQuery;
    preQuery.exec(QString("SELECT idcliente FROM clientes  WHERE nombre = '%1' AND apellido = '%2' AND empresa = '%3' AND email = '%4' AND telefonofijo = '%5' AND telefonocelular = '%6' AND direccion = '%7' AND ciudades_cp = '%8' LIMIT 1;"
                          ).arg(nombre).arg(apellido).arg(empresa).arg(email).arg(telefonofijo).arg(telefonocelular).arg(direccion).arg(ciudades_cp));

    if(preQuery.next())
    {
        //There is a record in the table with this same information
        qDebug() << "Client already exist";
        return preQuery.value(0).toInt();

    }

    QSqlQuery query;
    bool ret = query.exec(QString("INSERT INTO clientes (nombre, apellido, empresa, email, telefonofijo, telefonocelular, direccion, ciudades_cp) VALUES('%1','%2','%3','%4','%5','%6','%7','%8');"
                                              ).arg(nombre).arg(apellido).arg(empresa).arg(email).arg(telefonofijo).arg(telefonocelular).arg(direccion).arg(ciudades_cp));
    if(ret)
    {
        return query.lastInsertId().toInt();
    }
    else
    {
        qDebug() << query.lastError().text();
        return -1;
    }
}

int DatabaseManager::insertBalanza(QString marca, QString modelo, int dimension)
{
    if(!db.open()){  QMessageBox::critical(0,"Database Error",db.lastError().text()); return -2;}

    QSqlQuery preQuery;
    preQuery.exec(QString("SELECT idbalanza FROM balanzas WHERE marca = '%1' AND modelo = '%2' AND dimension = '%3' LIMIT 1;"
                          ).arg(marca).arg(modelo).arg(enumBalanzaSize.at(dimension)));

    if(preQuery.next())
    {
        //There is a record in the table with this same information
        qDebug() << "Balanza already exist";
        return preQuery.value(0).toInt();
    }
    QSqlQuery query;

    bool ret = query.exec(QString("INSERT INTO balanzas (marca, modelo, dimension) VALUES('%1','%2','%3');"
                                              ).arg(marca).arg(modelo).arg(enumBalanzaSize.at(dimension)));
    if(ret)
    {
        return query.lastInsertId().toInt();
    }
    else
    {
        qDebug() << query.lastError().text();
        return -1;
    }
}

int DatabaseManager::insertUbicacion(QString etiqueta, int dimension)
{
    if(!db.open()){  QMessageBox::critical(0,"Database Error",db.lastError().text()); return -2;}

    QSqlQuery preQuery;
    preQuery.exec(QString("SELECT idubicacion FROM ubicaciones WHERE etiqueta = '%1' AND dimension = '%2' LIMIT 1;"
                          ).arg(etiqueta).arg(enumBalanzaSize.at(dimension)));

    if(preQuery.next())
    {
        //There is a record in the table with this same information
        qDebug() << "Ubicacion already exist";
        return preQuery.value(0).toInt();
    }
    QSqlQuery query;

    bool ret = query.exec(QString("INSERT INTO ubicaciones (etiqueta, dimension) VALUES('%1','%2');"
                                              ).arg(etiqueta).arg(dimension));
    if(ret)
    {
        return query.lastInsertId().toInt();
    }
    else
    {
        qDebug() << query.lastError().text();
        return -1;
    }
}

int DatabaseManager::insertPrestable(QString idserie, QString observaciones, int balanzas_idbalanza)
{
    if(!db.open()){  QMessageBox::critical(0,"Database Error",db.lastError().text()); return -2;}

    QSqlQuery preQuery;
    preQuery.exec(QString("SELECT idprestable FROM prestables WHERE idserie = '%1' AND observaciones = '%2' AND balanzas_idbalanza = '%3' LIMIT 1;"
                          ).arg(idserie).arg(observaciones).arg(balanzas_idbalanza));

    if(preQuery.next())
    {
        //There is a record in the table with this same information
        qDebug() << "Prestable already exist";
        return preQuery.value(0).toInt();
    }
    QSqlQuery query;

    bool ret = query.exec(QString("INSERT INTO prestables (idserie, observaciones, balanzas_idbalanza) VALUES('%1','%2','%3');"
                                              ).arg(idserie).arg(observaciones).arg(balanzas_idbalanza));
    if(ret)
    {
        return query.lastInsertId().toInt();
    }
    else
    {
        qDebug() << query.lastError().text();
        return -1;
    }
}

int DatabaseManager::insertTransaccion(QString idserie,QString prioridad, QString accesorios, QString observaciones, int clientes_idcliente, int balanzas_idbalanza, QString prestables_idprestable, int ubicaciones_idubicacion, QString dateTime)
{
    if(!db.open()){  QMessageBox::critical(0,"Database Error",db.lastError().text()); return -2; }

    QSqlQuery preQuery;
    preQuery.exec(QString("SELECT idtransaccion FROM transacciones WHERE idserie = '%1' AND clientes_idcliente = '%2' AND balanzas_idbalanza = '%3' AND fecha_retirada IS NULL LIMIT 1;"
                          ).arg(idserie).arg(clientes_idcliente).arg(balanzas_idbalanza));
    if(preQuery.next())
    {
        //There is a record in the table with this same information
        qDebug() << "Transaction already exist";
        return preQuery.value(0).toInt();

    }

    QSqlQuery query;
    bool ret = query.exec(QString("INSERT INTO transacciones (idserie, prioridad, accesorios, observaciones, clientes_idcliente, balanzas_idbalanza, prestables_idprestable, ubicaciones_idubicacion, fecha_ingresada) VALUES('%1','%2','%3','%4','%5','%6',%7,'%8','%9');"
                                              ).arg(idserie).arg(prioridad).arg(accesorios).arg(observaciones).arg(clientes_idcliente).arg(balanzas_idbalanza).arg(prestables_idprestable).arg(ubicaciones_idubicacion).arg(dateTime));


    if(ret)
    {
        return query.lastInsertId().toInt();
    }
    else
    {
        qDebug() << query.lastError().text();
        qDebug() << query.lastQuery();
        return -1;
    }

}

int DatabaseManager::getUbicacion(int dimension)
{
    if(!db.open()){  QMessageBox::critical(0,"Database Error",db.lastError().text()); return -2; }

    for(int tryDimension = dimension ; tryDimension < enumBalanzaSize.size() ; ++tryDimension)
    {
        QSqlQuery query;
        bool ret = query.exec(QString("SELECT * FROM balanMac.ubicaciones WHERE NOT EXISTS(SELECT * FROM balanMac.transacciones WHERE balanMac.transacciones.ubicaciones_idubicacion = balanMac.ubicaciones.idubicacion  AND balanMac.transacciones.fecha_retirada IS NULL)  AND dimension = '%1' LIMIT 1;"
                    ).arg(enumBalanzaSize.at(tryDimension)));

        if(ret && query.next())
        {
            return query.value(0).toInt();
        }
    }

    qDebug() << "No hay ninguna ubicacion disponible que sea lo suficientemente grande";

    return -1;


}

QStringList DatabaseManager::getCliente(int idtransaccion)
{
    QStringList row;

    if(!db.open()){  QMessageBox::critical(0,"Database Error",db.lastError().text()); return row; }

    QSqlQuery preQuery;
    preQuery.exec(QString("SELECT * FROM transacciones WHERE idtransaccion = '%1' LIMIT 1;"
                          ).arg(idtransaccion));
    if(!preQuery.next())
    {
        //There is a record in the table with this same information
        qDebug() << "Transaction does not exist";
        return row;
    }

    QSqlQuery query;
    bool ret = query.exec(QString("select   idcliente, nombre, apellido, empresa,email , telefonofijo, telefonocelular, ciudad, provincia, cp, direccion from clientes right join ciudades ON clientes.ciudades_cp = ciudades.cp where idcliente = (select clientes_idcliente from transacciones where idtransaccion = '%1');"
                                              ).arg(idtransaccion));
    //Query model:

    if(ret)
    {
        query.next();
        QSqlRecord rec = query.record();

        for(int i = 0; i < rec.count() ; i++)
        {
            if(rec.value(i).toString() == "0")
            {
                row << "";
            }
            else row << rec.value(i).toString();
        }
        return row;
    }
    else
    {
        qDebug() << query.lastError().text();
        qDebug() << query.lastQuery();
        return row;
    }


}

QVector<int> DatabaseManager::getBalanzas(int idtransaccion)
{
    QVector<int> result;

    if(!db.open()){  QMessageBox::critical(0,"Database Error",db.lastError().text()); return result; }


    QSqlQuery preQuery;
    preQuery.exec(QString("SELECT * FROM transacciones WHERE idtransaccion = '%1' LIMIT 1;"
                          ).arg(idtransaccion));
    if(!preQuery.next())
    {
        //There is a record in the table with this same information
        qDebug() << "Transaction does not exist";
        return result;

    }

    QSqlQuery query;
    bool ret = query.exec(QString("SELECT idtransaccion FROM transacciones  WHERE (precio IS NOT NULL AND  clientes_idcliente = (select clientes_idcliente from transacciones where idtransaccion = '%1')  AND fecha_ingresada = (select fecha_ingresada from transacciones where idtransaccion = '%1'))"
                                              ).arg(idtransaccion));
    //Query model:

    if(ret)
    {
        while (query.next())
        {
            QSqlRecord rec = query.record();
            result.append(rec.value(0).toInt());

        }

        qDebug() << result;
        return result;
    }
    else
    {
        qDebug() << query.lastError().text();
        qDebug() << query.lastQuery();
        return result;
    }
}

QStringList DatabaseManager::getTransaccion(int idtransaccion)
{
    QStringList row;

    if(!db.open()){  QMessageBox::critical(0,"Database Error",db.lastError().text()); return row; }

    QSqlQuery preQuery;
    preQuery.exec(QString("SELECT * FROM transacciones WHERE idtransaccion = '%1' LIMIT 1;"
                          ).arg(idtransaccion));
    if(!preQuery.next())
    {
        //There is a record in the table with this same information
        qDebug() << "Transaction does not exist";
        return row;
    }

    QSqlQuery query;
    bool ret = query.exec(QString("SELECT precio, marca,modelo, prioridad , observaciones, accesorios, prestables_idprestable FROM transacciones right join balanzas on transacciones.balanzas_idbalanza = balanzas.idbalanza; WHERE idtransaccion = '%1';"
                                              ).arg(idtransaccion));
    //Query model:

    if(ret)
    {
        query.next();
        QSqlRecord rec = query.record();

        for(int i = 0; i < rec.count() ; i++)
        {
            if(rec.value(i).toString() == "0")
            {
                row << "";
            }
            else row << rec.value(i).toString();
        }
        return row;
    }
    else
    {
        qDebug() << query.lastError().text();
        qDebug() << query.lastQuery();
        return row;
    }
}

QSqlQueryModel *DatabaseManager::getPrestable(int idtransaccion,QWidget* parentWidget)
{
    QSqlQueryModel *model = new QSqlQueryModel(parentWidget);

    if(!db.open()){  QMessageBox::critical(0,"Database Error",db.lastError().text()); return model; }

    QSqlQuery preQuery;
    preQuery.exec(QString("SELECT * FROM transacciones WHERE idtransaccion = '%1' LIMIT 1;"
                          ).arg(idtransaccion));
    if(!preQuery.next())
    {
        //There is a record in the table with this same information
        qDebug() << "Transaction does not exist";
        return model;
    }

//TODO what the hell is going on here?
   model->setQuery(QString("SELECT marca,modelo,observaciones,idserie,dimension FROM prestables right join balanzas on prestables.balanzas_idbalanza = balanzas.idbalanza where idprestable = (select transacciones.prestables_idprestable from transacciones where idtransaccion = '2');"));
// model->setQuery(QString("SELECT * FROM transacciones;"));




bool ret = true;
    if(ret)
    {
        qDebug() << "Row count" << model->rowCount();

        return model;
    }
    else
    {
        qDebug() << model->lastError().text();
        return model;
    }
}

bool DatabaseManager::setBalanzaAsLimpiada(int idtransaccion)
{
    if(!db.open()){  QMessageBox::critical(0,"Database Error",db.lastError().text()); return -2; }

    QSqlQuery preQuery;
    preQuery.exec(QString("SELECT * FROM transacciones WHERE idtransaccion = '%1' LIMIT 1;"
                          ).arg(idtransaccion));
    if(!preQuery.next())
    {
        //There is a record in the table with this same information
        qDebug() << "Transaction does not exist";
        return false;

    }

    QSqlQuery query;
    bool ret = query.exec(QString("UPDATE transacciones SET fecha_limpiada= '%1' WHERE idtransaccion='%2';"
                                              ).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(idtransaccion));
    //Query model:

    if(ret)
    {
        return true;
    }
    else
    {
        qDebug() << query.lastError().text();
        qDebug() << query.lastQuery();
        return false;
    }
}

void DatabaseManager::propagateUpdates()
{
    qDebug() << "Emiting update table signal";
}

