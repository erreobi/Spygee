#ifndef SETUPCONNECTION_H
#define SETUPCONNECTION_H

#include <QDialog>
#include <QAbstractButton>
#include <QSettings>

namespace Ui {
class SetupConnection;
}

class SetupConnection : public QDialog
{
    Q_OBJECT

public:
    explicit SetupConnection(QWidget *parent = nullptr);
    ~SetupConnection();

public slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private slots:
    void on_pushButton_clicked();

private:
    Ui::SetupConnection *ui;

    QSettings m_oSettings;
};

#endif // SETUPCONNECTION_H
