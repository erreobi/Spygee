#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include "setupconnection.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void on_goButton_clicked();
    void onResult(QNetworkReply* reply);
    void newSettings();

private:
    Ui::MainWindow *ui;

    SetupConnection *m_qSetupDialog;

    QString m_sUsername;
    QString m_sPassword;
    QString m_sApigeeUrl;


protected:
    void showEvent(QShowEvent *ev);

private slots:
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
