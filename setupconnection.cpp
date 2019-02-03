#include "setupconnection.h"
#include "ui_setupconnection.h"
#include "constants.h"


SetupConnection::SetupConnection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetupConnection)
{
    ui->setupUi(this);

    ui->urlApigeeUrlLineEdit->setText(m_oSettings.value(Constants::APIURL,  "").toString());
    ui->usernameLineEdit->    setText(m_oSettings.value(Constants::USERNAME,"").toString());
    ui->passwordLineEdit->    setText(m_oSettings.value(Constants::PASSWORD,"").toString());

    connect(this, SIGNAL(finished(int)), parent, SLOT(newSettings()));
}

SetupConnection::~SetupConnection()
{
    delete ui;
}

void SetupConnection::on_buttonBox_clicked(QAbstractButton *button)
{
    m_oSettings.setValue(Constants::PASSWORD,ui->passwordLineEdit->text());
    m_oSettings.setValue(Constants::USERNAME,ui->usernameLineEdit->text());
    m_oSettings.setValue(Constants::APIURL,  ui->urlApigeeUrlLineEdit->text());
}

void SetupConnection::on_pushButton_clicked()
{
    m_oSettings.setValue(Constants::PASSWORD, "");
    m_oSettings.setValue(Constants::USERNAME, "");
    m_oSettings.setValue(Constants::APIURL,  "");

    ui->urlApigeeUrlLineEdit->setText(m_oSettings.value(Constants::APIURL,  "").toString());
    ui->usernameLineEdit->    setText(m_oSettings.value(Constants::USERNAME,"").toString());
    ui->passwordLineEdit->    setText(m_oSettings.value(Constants::PASSWORD,"").toString());

    m_oSettings.clear();
}
