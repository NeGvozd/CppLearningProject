#include "databasecontroller.h"

DatabaseController::DatabaseController()
{

}

int DatabaseController::connection()
{
    airplanDB.connection();
}

QSqlDatabase DatabaseController::return_db()
{
    return airplanDB.return_db();
}

int DatabaseController::closing()
{
    airplanDB.closing();
}
