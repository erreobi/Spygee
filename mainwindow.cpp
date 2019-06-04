#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "setupconnection.h"
#include "constants.h"
#include "apigeeedge.h"
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
    delete apigeeEdge;
}

void MainWindow::newSettings(){

    QSettings settings;

    this->apigeeEdge->setApigeeEdge(settings.value(Constants::USERNAME,   "").toString(),
                                    settings.value(Constants::PASSWORD, "").toString(),
                                    settings.value(Constants::APIURL, "").toString(),
                                    settings.value(Constants::ORG,      "").toString(),
                                    settings.value(Constants::ENV,      "").toString());

    ui->urlLineEdit->setText("APIGEE URL: " + this->apigeeEdge->getApigeeUrl());

}

void MainWindow::showEvent( QShowEvent* event ) {
    QWidget::showEvent( event );

    QSettings settings;
    if (settings.value(Constants::USERNAME, "") == "")
    {

        m_qSetupDialog->setModal(true);
        m_qSetupDialog->show();
    }else{
         ui->logTextEdit->append("Found Setting at "+settings.fileName());

         if (!apigeeEdge)
         {
            delete apigeeEdge;
         }

         apigeeEdge = new ApigeeEdge(settings.value(Constants::USERNAME, "").toString(),
                                        settings.value(Constants::PASSWORD, "").toString(),
                                        settings.value(Constants::APIURL, "").toString(),
                                        settings.value(Constants::ENV, "").toString(),
                                        settings.value(Constants::ORG, "").toString());

         ui->urlLineEdit->setText("APIGEE URL: "+apigeeEdge->getApigeeUrl());
    }

}

void MainWindow::on_goButton_clicked()
{
    ui->logTextEdit->append("START ... ");

    apigeeEdge->getApis();
    connect(apigeeEdge, SIGNAL(resultGetApi(QJsonDocument)), this, SLOT(getApiSlot(QJsonDocument)));

}

void MainWindow::getApiSlot(QJsonDocument jsonResponse)
{
   // QJsonObject jsonObjAPIList = jsonResponse.object();
    QJsonArray jsonArray = jsonResponse.array();

    /* Buil QTree */
    QStandardItemModel *model = new QStandardItemModel() ;
    QStandardItem *rootNode =  model->invisibleRootItem();
    rootNode->setText("API List");


    foreach (const QJsonValue & value, jsonArray) {

        QJsonObject singleApigJsonObj = value.toObject();
        rootNode->appendRow(new QStandardItem(value.toString()));

        ui->logTextEdit->append(value.toString());

    }

    ui->apiTreeView->setModel(model);

    //ui->logTextEdit->append(strReply);

}


void MainWindow::on_pushButton_clicked()
{
    m_qSetupDialog->setModal(true);
    m_qSetupDialog->show();
}
