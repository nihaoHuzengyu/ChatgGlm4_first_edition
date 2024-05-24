#include "chatglm.h"

ChatGLM::ChatGLM(QObject *parent)
    : QObject(parent)
    , manager(new QNetworkAccessManager(this))
{
    // 连接网络请求完成信号和槽
        connect(manager, &QNetworkAccessManager::finished, this, &ChatGLM::onReplyFinished);
}
ChatGLM::~ChatGLM(){
    delete manager;
}
void ChatGLM::sendMessage(const QString &message)
{
    QNetworkRequest request(apiUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", ("Bearer " + apiKey).toUtf8());

    QString prompt = "User: " + message + "\nAI:";
    QJsonObject data;
    data["prompt"] = prompt;
    data["max_tokens"] = 50;
    data["n"] = 1;
    data["stop"] = "\n";
    data["temperature"] = 0.5;

    QJsonDocument doc(data);
    QByteArray payload = doc.toJson();

    // 使用异步网络请求发送 POST 请求
    manager->post(request, payload);
}


/*
void ChatGLM::sendMessage(const QString &message)
{
    QNetworkRequest request(apiUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", ("Bearer " + apiKey).toUtf8());

    QString prompt = "User: " + message + "\nAI:";
    QJsonObject data;
    data["prompt"] = prompt;
    data["max_tokens"] = 50;
    data["n"] = 1;
    data["stop"] = "\n";
    data["temperature"] = 0.5;

    QJsonDocument doc(data);
    QByteArray payload = doc.toJson();

    // 使用异步网络请求发送 POST 请求
    manager->post(request, payload, [this](QNetworkReply *reply) {
        if (reply->error() != QNetworkReply::NoError) {
            // 处理错误
            qDebug() << "Network error:" << reply->errorString();
            return;
        }

        QByteArray response = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(response);
        QJsonObject obj = doc.object();
        QJsonArray choices = obj["choices"].toArray();
        if (choices.isEmpty()) {
            // 处理空响应
            qDebug() << "Empty response";
            return;
        }

    QString aiMessage = "AI:" + choices[0].toObject()["text"].toString().trimmed();
    emit messageReceived(aiMessage);
});
}
*/
void ChatGLM::setApiKey(const QString &newApiKey)
{
    apiKey = newApiKey;
}

void ChatGLM::setApiUrl(const QString &newApiUrl)
{
    apiUrl = newApiUrl;
}

void ChatGLM::onReplyFinished(QNetworkReply *reply)
{
    if (!reply)
        return;

    if (reply->error() != QNetworkReply::NoError) {
        // Handle error
        return;
    }

    QByteArray response = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(response);
    QJsonObject obj = doc.object();
    QJsonArray choices = obj["choices"].toArray();
    if (choices.isEmpty()) {
        // Handle empty response
        return;
    }

    QString aiMessage = "AI:" + choices[0].toObject()["text"].toString().trimmed();
    emit messageReceived(aiMessage);
    // 直接调用Widget的displayMessage方法
    //displayMessage("AI:" + aiMessage);
}

