#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QThread>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class ChatGLM; // 假设ChatGLM已经在另一个头文件中定义

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void displayMessage(const QString &message);
    void on_chatglm_pushButton_clicked();

private:
    Ui::Widget *ui;
    ChatGLM *chatGLM;
    //QTimer *displayTimer;
};

#endif // WIDGET_H
