#ifndef APIGEEEDGE_H
#define APIGEEEDGE_H

#include <QString>
#include <QtNetwork>
#include <QStandardItemModel>

class ApigeeEdge : public QObject
{

    Q_OBJECT

public:
    ApigeeEdge( QString username,
                QString password,
                QString apigeeUrl,
                QString environment,
                QString organization);


    //It is useful to inform what is the APIGEE url that it will use
    QString getApigeeUrl();

    //It is usefull to reset the URL
    void setApigeeEdge( QString username,
                        QString password,
                        QString apigeeUrl,
                        QString environment,
                        QString organization);

    //Returns all the Apis
    void getApis();



public slots:
    void onResultGetApis(QNetworkReply* reply);

signals:
    void resultGetApi(QJsonDocument resultJson);
    void apigeeHttpError(QString error);

private:
    QString m_sAuthBasic;
    QString m_sApigeeUrl;



};


#endif // APIGEEEDGE_H
