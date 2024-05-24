#include "widget.h"
#include "ui_widget.h"
#include "chatglm.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , chatGLM(new ChatGLM(this)) // 初始化chatGLM对象
    //, displayTimer(new QTimer(this)) // 初始化displayTimer
{
    ui->setupUi(this);

    connect(ui->chatglm_pushButton, &QPushButton::clicked, this, &Widget::on_chatglm_pushButton_clicked);
    connect(chatGLM, &ChatGLM::messageReceived, this, &Widget::displayMessage);
    /*
    connect(ui->chatglm_pushButton, &QPushButton::clicked, this, [this]() { onChatglmPushButtonClicked(); });
    connect(chatGLM, &ChatGLM::messageReceived, this, [this](const QString &message) { displayMessage(message); });
    */

    // 设置API密钥和URL
    chatGLM->setApiKey("2a9f04e946ce43c06cb6e3cb67840771.eklVXZsyStEexS5E");
    chatGLM->setApiUrl("http://open.bigmodel.cn/api/paas/v4/chat/completions");
}

Widget::~Widget()
{
    delete ui;
    //delete displayTimer;
}

void Widget::on_chatglm_pushButton_clicked()
{
    QString message = ui->chatglm_lineEdit->text();
    chatGLM->sendMessage(message);
    ui->chatglm_lineEdit->clear();
}

void Widget::displayMessage(const QString &message)
{
    /*
    QString currentMessage = ui->chatglm_textEdit->toPlainText();
        for (int i = 0; i < message.length(); ++i) {
            currentMessage += message[i];
            ui->chatglm_textEdit->setPlainText(currentMessage);
            QCoreApplication::processEvents(); // 确保界面更新
            QThread::msleep(100); // 休眠100毫秒
        }
        */


     //逐个字符显示消息
    QTimer *timer = new QTimer(this);
    int index = 0;
    QString currentMessage;

    connect(timer, &QTimer::timeout, [this, message, timer, &index, &currentMessage]() {
        if (index < message.length()) {
            currentMessage += message[index];
            ui->chatglm_textEdit->setPlainText(currentMessage);
            index++;
        } else {
            timer->stop();
            delete timer;
        }
    });

    timer->start(100); // Display one character every 100 milliseconds

    //整个消息直接输出
    /*
    ui->chatglm_textEdit->append(message);
    */
    /*
    int delay = 100; // 每个字符显示的延迟（毫秒）

        // 使用QTimer显示消息的每个字符
        displayTimer->setInterval(delay);
        connect(displayTimer, &QTimer::timeout, [this, message] {
            static int index = 0;
            if (index < message.length()) {
                ui->chatglm_textEdit->setPlainText(ui->chatglm_textEdit->toPlainText() + message[index]);
                index++;
            } else {
                displayTimer->stop();
                index = 0; // 重置索引
            }
        });

        displayTimer->start(); // 开始显示消息
        */
}


