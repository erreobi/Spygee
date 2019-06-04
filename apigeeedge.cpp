#include "apigeeedge.h"
#include "constants.h"
#include <QtNetwork>


ApigeeEdge::ApigeeEdge(QString username,
                       QString password,
                       QString apigeeUrl,
                       QString environment,
                       QString organization)
{
    this->setApigeeEdge(username,
                        password,
                        apigeeUrl,
                        environment,
                        organization);
}

void ApigeeEdge::setApigeeEdge( QString username,
                    QString password,
                    QString apigeeUrl,
                    QString environment,
                    QString organization)
{
    this->m_sAuthBasic = "Basic "+(username+":"+password).toLocal8Bit().toBase64();
    this->m_sApigeeUrl = apigeeUrl+"/v1/o/"+organization+"/e/"+environment;
}



QString ApigeeEdge::getApigeeUrl(){
    return this->m_sApigeeUrl;
}

void ApigeeEdge::getApis()
{
    QNetworkAccessManager *networkManager = new QNetworkAccessManager (this);
    connect(networkManager, &QNetworkAccessManager::finished,this, &ApigeeEdge::onResultGetApis);

    QString getApigURL=""+m_sApigeeUrl+"/apis";

    QUrl url = QUrl(getApigURL);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    request.setRawHeader("Ahorization", this->m_sAuthBasic.toLocal8Bit());


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
    } else {
        emit apigeeHttpError("TIME out Error ..."+getApigURL+" is not responding");
        // ui->logTextEdit->append("TIME out Error ..."+ui->urlLineEdit->text()+" is not responding");
        m_reply->abort();

    }

}

void ApigeeEdge::onResultGetApis(QNetworkReply* reply)
{

    if (reply->error()) {

        QString reason = reply->attribute( QNetworkRequest::HttpReasonPhraseAttribute ).toString();

        emit apigeeHttpError("Http Error: "+reason);

        return;
    }

    /* parse Json */
    QStringList propertyNames;
    QStringList propertyKeys;
    QString strReply = (QString) reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());

    emit resultGetApi (jsonResponse);

}
