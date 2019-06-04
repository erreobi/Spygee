#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include "setupconnection.h"
#include "apigeeedge.h"

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
    void getApiSlot(QJsonDocument document);
    void newSettings();

private:
    Ui::MainWindow *ui;

    SetupConnection *m_qSetupDialog;
    ApigeeEdge *apigeeEdge;

protected:
    void showEvent(QShowEvent *ev);

private slots:
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
