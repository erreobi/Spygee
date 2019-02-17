#include "setupconnection.h"
#include "ui_setupconnection.h"
#include "constants.h"


SetupConnection::SetupConnection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetupConnection)
{
    ui->setupUi(this);

    ui->urlApigeeUrlLineEdit-> setText(m_oSettings.value(Constants::APIURL,   "").toString());
    ui->usernameLineEdit->     setText(m_oSettings.value(Constants::USERNAME, "").toString());
    ui->passwordLineEdit->     setText(m_oSettings.value(Constants::PASSWORD, "").toString());
    ui->organizzationLineEdit->setText(m_oSettings.value(Constants::ORG,      "").toString());
    ui->environmentLineEdit->  setText(m_oSettings.value(Constants::ENV,      "").toString());

    connect(this, SIGNAL(finished(int)), parent, SLOT(newSettings()));
}

SetupConnection::~SetupConnection()
{
    delete ui;
}

void SetupConnection::on_buttonSaveButton_clicked(QAbstractButton *button)
{
    m_oSettings.setValue(Constants::PASSWORD,ui->passwordLineEdit->text());
    m_oSettings.setValue(Constants::USERNAME,ui->usernameLineEdit->text());
    m_oSettings.setValue(Constants::ORG,ui->organizzationLineEdit->text());
    m_oSettings.setValue(Constants::ENV,ui->environmentLineEdit->text());
    m_oSettings.setValue(Constants::APIURL,  ui->urlApigeeUrlLineEdit->text());
}

void SetupConnection::on_pushClearButton_clicked()
{
    m_oSettings.setValue(Constants::PASSWORD, "");
    m_oSettings.setValue(Constants::USERNAME, "");
    m_oSettings.setValue(Constants::APIURL,   "");
    m_oSettings.setValue(Constants::ENV,      "");
    m_oSettings.setValue(Constants::APIURL,   "");

    ui->urlApigeeUrlLineEdit-> setText(m_oSettings.value(Constants::APIURL,   "").toString());
    ui->usernameLineEdit->     setText(m_oSettings.value(Constants::USERNAME, "").toString());
    ui->passwordLineEdit->     setText(m_oSettings.value(Constants::PASSWORD, "").toString());
    ui->organizzationLineEdit->setText(m_oSettings.value(Constants::ORG,      "").toString());
    ui->environmentLineEdit->  setText(m_oSettings.value(Constants::ENV,      "").toString());

    m_oSettings.clear();
}
