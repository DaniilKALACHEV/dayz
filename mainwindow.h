#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QTableView>
#include <QPushButton>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addRecord();
    void deleteRecord();

private:
    QSqlTableModel *konrtagentModel;
    QSqlTableModel *sellModel;
    QSqlTableModel *productsModel;

    QTabWidget *tabWidget;
    QWidget *tabKonrtagent;
    QWidget *tabSell;
    QWidget *tabProducts;

    QTableView *tableViewKonrtagent;
    QTableView *tableViewSell;
    QTableView *tableViewProducts;

    QLineEdit *lineEditKonrtagentId;
    QLineEdit *lineEditKonrtagentNameOrg;
    QLineEdit *lineEditKonrtagentPhoneNumber;
    QLineEdit *lineEditKonrtagentNamePastname;

    QLineEdit *lineEditSellId;
    QLineEdit *lineEditSellIdNy;
    QLineEdit *lineEditSellDate;
    QLineEdit *lineEditSellStatus;

    QLineEdit *lineEditProductsIdNy;
    QLineEdit *lineEditProductsName;
    QLineEdit *lineEditProductsPrice;

    QPushButton *addButton;
    QPushButton *deleteButton;

    void setupUI();
};

#endif // MAINWINDOW_H
