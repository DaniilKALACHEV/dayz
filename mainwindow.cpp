#include "mainwindow.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTabWidget>
#include <QTableView>
#include <QSqlTableModel>
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("1cdb");
    db.setUserName("root");
    db.setPassword("usbw");
    db.setPort(3307);

    if (!db.open()) {
        qDebug() << db.lastError().text();
        return;
    }

    konrtagentModel = new QSqlTableModel(this);
    konrtagentModel->setTable("konrtagent");
    konrtagentModel->select();
    tableViewKonrtagent->setModel(konrtagentModel);
    tableViewKonrtagent->hideColumn(0);

    sellModel = new QSqlTableModel(this);
    sellModel->setTable("sell");
    sellModel->select();
    tableViewSell->setModel(sellModel);
    tableViewSell->hideColumn(0);

    productsModel = new QSqlTableModel(this);
    productsModel->setTable("products");
    productsModel->select();
    tableViewProducts->setModel(productsModel);
    tableViewProducts->hideColumn(0);

    connect(addButton, &QPushButton::clicked, this, &MainWindow::addRecord);
    connect(deleteButton, &QPushButton::clicked, this, &MainWindow::deleteRecord);
}

MainWindow::~MainWindow()
{
}

void MainWindow::addRecord()
{
    if (tabWidget->currentIndex() == 0) { // добавление записи в таблицу konrtagent
        int id_k = lineEditKonrtagentId->text().toInt();
        QString name_org = lineEditKonrtagentNameOrg->text();
        int phone_number = lineEditKonrtagentPhoneNumber->text().toInt();
        QString name_pastname = lineEditKonrtagentNamePastname->text();

        QSqlQuery query;
        query.prepare("INSERT INTO konrtagent (id_k, name_org, phone_number, name_pastname) "
                      "VALUES (:id_k, :name_org, :phone_number, :name_pastname)");
        query.bindValue(":id_k", id_k);
        query.bindValue(":name_org", name_org);
        query.bindValue(":phone_number", phone_number);
        query.bindValue(":name_pastname", name_pastname);

        if (query.exec()) {
            konrtagentModel->select();
        }
    }
    else if (tabWidget->currentIndex() == 1) { // добавление записи в таблицу sell
        int id_k = lineEditSellId->text().toInt();
        int id_ny = lineEditSellIdNy->text().toInt();
        QString date = lineEditSellDate->text();
        QString status = lineEditSellStatus->text();

        QSqlQuery query;
        query.prepare("INSERT INTO sell (id_k, id_ny, date, status) "
                      "VALUES (:id_k, :id_ny, :date, :status)");
        query.bindValue(":id_k", id_k);
        query.bindValue(":id_ny", id_ny);
        query.bindValue(":date", date);
        query.bindValue(":status", status);

        if (query.exec()) {
            sellModel->select();
        }
    }
    else if (tabWidget->currentIndex() == 2) { // добавление записи в таблицу products
        int id_ny = lineEditProductsIdNy->text().toInt();
        QString name = lineEditProductsName->text();
        int price = lineEditProductsPrice->text().toInt();

        QSqlQuery query;
        query.prepare("INSERT INTO products (id_ny, name, price) "
                      "VALUES (:id_ny, :name, :price)");
        query.bindValue(":id_ny", id_ny);
        query.bindValue(":name", name);
        query.bindValue(":price", price);

        if (query.exec()) {
            productsModel->select();
        }
    }
}

void MainWindow::deleteRecord()
{
    if (tabWidget->currentIndex() == 0) { // удаление записи из таблицы konrtagent
        QModelIndex index = tableViewKonrtagent->currentIndex();
        if (index.isValid()) {
            int id_k = konrtagentModel->data(konrtagentModel->index(index.row(), 0)).toInt();

            QSqlQuery query;
            query.prepare("DELETE FROM konrtagent WHERE id_k = :id_k");
            query.bindValue(":id_k", id_k);

            if (query.exec()) {
                konrtagentModel->select();
            }
        }
    }
    else if (tabWidget->currentIndex() == 1) { // удаление записи из таблицы sell
        QModelIndex index = tableViewSell->currentIndex();
        if (index.isValid()) {
            int id_k = sellModel->data(sellModel->index(index.row(), 0)).toInt();

            QSqlQuery query;
            query.prepare("DELETE FROM sell WHERE id_k = :id_k");
            query.bindValue(":id_k", id_k);

            if (query.exec()) {
                sellModel->select();
            }
        }
    }
    else if (tabWidget->currentIndex() == 2) { // удаление записи из таблицы products
        QModelIndex index = tableViewProducts->currentIndex();
        if (index.isValid()) {
            int id_ny = productsModel->data(productsModel->index(index.row(), 0)).toInt();

            QSqlQuery query;
            query.prepare("DELETE FROM products WHERE id_ny = :id_ny");
            query.bindValue(":id_ny", id_ny);

            if (query.exec()) {
                productsModel->select();
            }
        }
    }
}

void MainWindow::setupUI()
{
    tabWidget = new QTabWidget(this);
    tabWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    tabKonrtagent = new QWidget(tabWidget);
    tableViewKonrtagent = new QTableView(tabKonrtagent);

    lineEditKonrtagentId = new QLineEdit(tabKonrtagent);
    lineEditKonrtagentNameOrg = new QLineEdit(tabKonrtagent);
    lineEditKonrtagentPhoneNumber = new QLineEdit(tabKonrtagent);
    lineEditKonrtagentNamePastname = new QLineEdit(tabKonrtagent);

    addButton = new QPushButton("Добавить", tabKonrtagent);
    deleteButton = new QPushButton("Удалить", tabKonrtagent);

    QHBoxLayout *lineLayout1 = new QHBoxLayout;
    lineLayout1->addWidget(new QLabel("id_k", tabKonrtagent));
    lineLayout1->addWidget(lineEditKonrtagentId);

    QHBoxLayout *lineLayout2 = new QHBoxLayout;
    lineLayout2->addWidget(new QLabel("Наименование организации", tabKonrtagent));
    lineLayout2->addWidget(lineEditKonrtagentNameOrg);

    QHBoxLayout *lineLayout3 = new QHBoxLayout;
    lineLayout3->addWidget(new QLabel("Номер телефона", tabKonrtagent));
    lineLayout3->addWidget(lineEditKonrtagentPhoneNumber);

    QHBoxLayout *lineLayout4 = new QHBoxLayout;
    lineLayout4->addWidget(new QLabel("ФИО", tabKonrtagent));
    lineLayout4->addWidget(lineEditKonrtagentNamePastname);

    QVBoxLayout *formLayout = new QVBoxLayout;
    formLayout->addLayout(lineLayout1);
    formLayout->addLayout(lineLayout2);
    formLayout->addLayout(lineLayout3);
    formLayout->addLayout(lineLayout4);
    formLayout->addWidget(addButton);
    formLayout->addWidget(deleteButton);

    QGridLayout *tabKonrtagentLayout = new QGridLayout(tabKonrtagent);
    tabKonrtagentLayout->addWidget(tableViewKonrtagent, 0, 0, 1, 2);
    tabKonrtagentLayout->addLayout(formLayout, 1, 0, 1, 2);

    tabSell = new QWidget(tabWidget);
    tableViewSell = new QTableView(tabSell);

    lineEditSellId = new QLineEdit(tabSell);
    lineEditSellIdNy = new QLineEdit(tabSell);
    lineEditSellDate = new QLineEdit(tabSell);
    lineEditSellStatus = new QLineEdit(tabSell);

    addButton = new QPushButton("Добавить", tabSell);
    deleteButton = new QPushButton("Удалить", tabSell);

    QHBoxLayout *lineLayout5 = new QHBoxLayout;
    lineLayout5->addWidget(new QLabel("id_k", tabSell));
    lineLayout5->addWidget(lineEditSellId);

    QHBoxLayout *lineLayout6 = new QHBoxLayout;
    lineLayout6->addWidget(new QLabel("id_ny", tabSell));
    lineLayout6->addWidget(lineEditSellIdNy);

    QHBoxLayout *lineLayout7 = new QHBoxLayout;
    lineLayout7->addWidget(new QLabel("Дата", tabSell));
    lineLayout7->addWidget(lineEditSellDate);

    QHBoxLayout *lineLayout8 = new QHBoxLayout;
    lineLayout8->addWidget(new QLabel("Статус", tabSell));
    lineLayout8->addWidget(lineEditSellStatus);

    QVBoxLayout *formLayout2 = new QVBoxLayout;
    formLayout2->addLayout(lineLayout5);
    formLayout2->addLayout(lineLayout6);
    formLayout2->addLayout(lineLayout7);
    formLayout2->addLayout(lineLayout8);
    formLayout2->addWidget(addButton);
    formLayout2->addWidget(deleteButton);

    QGridLayout *tabSellLayout = new QGridLayout(tabSell);
    tabSellLayout->addWidget(tableViewSell, 0, 0, 1, 2);
    tabSellLayout->addLayout(formLayout2, 1, 0, 1, 2);

    tabProducts = new QWidget(tabWidget);
    tableViewProducts = new QTableView(tabProducts);

    lineEditProductsIdNy = new QLineEdit(tabProducts);
    lineEditProductsName = new QLineEdit(tabProducts);
    lineEditProductsPrice = new QLineEdit(tabProducts);

    addButton = new QPushButton("Добавить", tabProducts);
    deleteButton = new QPushButton("Удалить", tabProducts);

    QHBoxLayout *lineLayout9 = new QHBoxLayout;
    lineLayout9->addWidget(new QLabel("id_ny", tabProducts));
    lineLayout9->addWidget(lineEditProductsIdNy);

    QHBoxLayout *lineLayout10 = new QHBoxLayout;
    lineLayout10->addWidget(new QLabel("Наименование", tabProducts));
    lineLayout10->addWidget(lineEditProductsName);

    QHBoxLayout *lineLayout11 = new QHBoxLayout;
    lineLayout11->addWidget(new QLabel("Цена", tabProducts));
    lineLayout11->addWidget(lineEditProductsPrice);

    QVBoxLayout *formLayout3 = new QVBoxLayout;
    formLayout3->addLayout(lineLayout9);
    formLayout3->addLayout(lineLayout10);
    formLayout3->addLayout(lineLayout11);
    formLayout3->addWidget(addButton);
    formLayout3->addWidget(deleteButton);

    QGridLayout *tabProductsLayout = new QGridLayout(tabProducts);
    tabProductsLayout->addWidget(tableViewProducts, 0, 0, 1, 2);
    tabProductsLayout->addLayout(formLayout3, 1, 0, 1, 2);

    tabWidget->addTab(tabKonrtagent, "Контрагенты");
    tabWidget->addTab(tabSell, "Продажи");
    tabWidget->addTab(tabProducts, "Продукты");

    setCentralWidget(tabWidget);
}
