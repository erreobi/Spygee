#ifndef APIGEEEDGE_H
#define APIGEEEDGE_H

#include <QString>
#include <QStandardItemModel>

class ApigeeEdge : public QObject
{

public:
    ApigeeEdge( QString username,
                QString password,
                QString apigeeUrl,
                QString environment,
                QString organization);


    QJsonArray getApis();


private:
    QString m_sAuthBasic;
    QString m_sApigeeUrl;

    void httpCall(QString url, const QObject *receiver, const char *method );

};

#endif // APIGEEEDGE_H
