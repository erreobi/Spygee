#include "apigeeedge.h"
#include "constants.h"
#include <QtNetwork>


ApigeeEdge::ApigeeEdge(QString username,
                       QString password,
                       QString apigeeUrl,
                       QString environment,
                       QString organization)
{
    this->m_sAuthBasic = "Basic "+(username+":"+password).toLocal8Bit().toBase64();
    this->m_sApigeeUrl = apigeeUrl+"/v1/o/"+organization+"/e/"+environment;
}

void ApigeeEdge::httpCall(QString sUrl, const QObject *receiver, const char *method)
{
    QNetworkAccessManager *networkManager = new QNetworkAccessManager (this);
    connect(networkManager, &QNetworkAccessManager::finished,receiver, method);

    QUrl url = QUrl(sUrl);
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
        // ui->logTextEdit->append("Get Response ... ");
    } else {

        // ui->logTextEdit->append("TIME out Error ..."+ui->urlLineEdit->text()+" is not responding");
        m_reply->abort();

    }
}
