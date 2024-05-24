#ifndef CHATGLM_H
#define CHATGLM_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

class ChatGLM : public QObject
{
    Q_OBJECT
public:
    explicit ChatGLM(QObject *parent = nullptr);
    virtual ~ChatGLM();

    // 设置API密钥、API URL的槽函数声明
    void setApiKey(const QString &apiKey);
    void setApiUrl(const QString &apiUrl);

    // 同步方法，直接调用Widget的displayMessage方法
        //void displayMessage(const QString &message);
signals:
    // 定义messageReceived信号
    void messageReceived(const QString &message);

public slots:
    // 发送消息的槽函数声明
    void sendMessage(const QString &message);
    // 网络回复完成的槽函数声明
    void onReplyFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager *manager;
    QString apiKey;
    QString apiUrl;
};

#endif // CHATGLM_H
