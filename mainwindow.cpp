#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "setupconnection.h"
#include "constants.h"
#include <QtNetwork>
#include <QStandardItemModel>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_qSetupDialog = new SetupConnection(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete  m_qSetupDialog;
}

void MainWindow::newSettings(){

    QSettings settings;
    m_sUsername  = settings.value(Constants::USERNAME, "").toString();
    m_sPassword  = settings.value(Constants::PASSWORD, "").toString();
    m_sApigeeUrl = settings.value(Constants::APIURL,   "").toString();

    ui->urlLineEdit->setText(m_sApigeeUrl);

}

void MainWindow::showEvent( QShowEvent* event ) {
    QWidget::showEvent( event );

    QSettings settings;
    if (settings.value(Constants::USERNAME, "") == "")
    {

        m_qSetupDialog->setModal(true);
        m_qSetupDialog->show();
    }

    m_sUsername  = settings.value(Constants::USERNAME, "").toString();
    m_sPassword  = settings.value(Constants::PASSWORD, "").toString();
    m_sApigeeUrl = settings.value(Constants::APIURL,   "").toString();

    ui->urlLineEdit->setText(m_sApigeeUrl);


    ui->logTextEdit->append("Found Setting at "+settings.fileName());

}

void MainWindow::on_goButton_clicked()
{
    ui->logTextEdit->append("START ... ");

    QNetworkAccessManager *networkManager = new QNetworkAccessManager (this);
    connect(networkManager, &QNetworkAccessManager::finished,this, &MainWindow::onResult);

    QNetworkRequest request(QUrl( ui->urlLineEdit->text()));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    request.setRawHeader("Authorization", "Basic "+(m_sUsername+":"+m_sPassword).toLocal8Bit().toBase64());


    QNetworkReply* m_reply = networkManager->get(request);

    /* Set timeout */
    QTimer timer;
    timer.setSingleShot(true);

    QEventLoop loop;
    connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
    connect(m_reply, SIGNAL(finished()),&loop, SLOT(quit()));

    timer.start(Constants::TIMEOUT);
    loop.exec();


    if(timer.isActive()) {
        timer.stop();
        // ui->logTextEdit->append("Get Response ... ");
    } else {

        ui->logTextEdit->append("TIME out Error ..."+ui->urlLineEdit->text()+" is not responding");
        m_reply->abort();

    }

}

void MainWindow::onResult(QNetworkReply* reply)
{

    if (reply->error()) {

        QString reason = reply->attribute( QNetworkRequest::HttpReasonPhraseAttribute ).toString();

        ui->logTextEdit->append("Error ... reason["+reason+"]");

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

    ui->apiTreeView->setModel(model);

    ui->logTextEdit->append(strReply);

}


void MainWindow::on_pushButton_clicked()
{
    m_qSetupDialog = new SetupConnection(this);
    m_qSetupDialog->setModal(true);
    m_qSetupDialog->show();
}
