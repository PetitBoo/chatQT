#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    userDB = QSqlDatabase::addDatabase("QSQLITE");
    userDB.setDatabaseName("./userDB.db");
    if(userDB.open())
    {
        qDebug("open UDB");
    }
    else
    {
        qDebug("not open");
    }
    /*messageDB = QSqlDatabase::addDatabase("QSQLITE", "secondConnect");
    messageDB.setDatabaseName("./messageDB.db");
    if(messageDB.open())
    {
        qDebug("open MDB");
    }
    else
    {
        qDebug("not open");
    }*/

    queryU =new QSqlQuery(userDB);
    queryU->exec("CREATE TABLE UserDataBase(Login TEXT, Password TEXT, Ban BOOLEAN);");
    //queryM =new QSqlQuery(messageDB);
    queryU->exec("CREATE TABLE MessageDataBase(From TEXT, To TEXT, Message TEXT);");

    modelU = new QSqlTableModel(this, userDB);
    modelU->setTable("UserDataBase");
    modelU->select();
    //modelM = new QSqlTableModel(this, userDB);
    //modelM->setTable("MessageDataBase");
    //modelM->select();

    ui->tableView->setModel(modelU);
    //ui->tableView_2->setModel(modelM);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    modelU->insertRow(modelU->rowCount());
}


void MainWindow::on_pushButton_2_clicked()
{
    modelU->removeRow(row);
    modelU->select();
}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    row = index.row();
}

