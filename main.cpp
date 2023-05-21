#include <QCoreApplication>
#include <QtSql>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("1cdb");
    db.setUserName("root");
    db.setPassword("usbw");
    db.setPort(3307);

    if (!db.open()) {
        qDebug() << db.lastError().text();
        return 1;
    }

    // дальнейший код программы

    return a.exec();
}
