#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork>
#include <QStandardItemModel>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_goButton_clicked()
{
    ui->logTextEdit->append("START ... ");

    QNetworkAccessManager *networkManager = new QNetworkAccessManager (this);
    connect(networkManager, &QNetworkAccessManager::finished,
            this, &MainWindow::onResult);

    QNetworkRequest request(QUrl( ui->urlLineEdit->text()));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    networkManager->get(request);

}

void MainWindow::onResult(QNetworkReply* reply)
{

    if (reply->error()) {
        ui->logTextEdit->append("Error ... ");

        QString reason = reply->attribute( QNetworkRequest::HttpReasonPhraseAttribute ).toString();

        ui->logTextEdit->append(reason);

        return;
    }


    /* parse Json */
    QStringList propertyNames;
    QStringList propertyKeys;
    QString strReply = (QString)reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
    QJsonArray jsonArray = jsonResponse.array();

    /* Buil QTree */
    QStandardItemModel *model = new QStandardItemModel() ;
    QStandardItem *rootNode =  model->invisibleRootItem();
    rootNode->setText("API List");

    foreach (const QJsonValue & value, jsonArray) {
        rootNode->appendRow(new QStandardItem(value.toString()));
    }

//    connect(selectionModel, SIGNAL(selectionChanged (const QItemSelection &, const QItemSelection &)),
//               this, SLOT(selectionChangedSlot(const QItemSelection &, const QItemSelection &)));

    ui->apiTreeView->setModel(model);

    ui->logTextEdit->append(strReply);

}

