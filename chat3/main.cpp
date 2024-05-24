#include "widget.h"

#include <QApplication>
#include <QSslSocket>
//#include <QSsl>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    /*编译时有链接静态库，但是我没有动态库，所以最终不支持SSL
     * 缺少SSL相关动态库
     *
    // 获取编译时 SSL 静态库的版本号和字符串
        long buildVersionNumber = QSslSocket::sslLibraryBuildVersionNumber();
        QString buildVersionString = QSslSocket::sslLibraryBuildVersionString();

        // 获取运行时 SSL 库的版本号和字符串
        long versionNumber = QSslSocket::sslLibraryVersionNumber();
        QString versionString = QSslSocket::sslLibraryVersionString();

        // 输出版本信息
        qDebug() << "Compiled with SSL Static Library Version:" << buildVersionNumber << buildVersionString;
        qDebug() << "Running with SSL Library Version:" << versionNumber << versionString;
    // 检查 Qt 是否支持 SSL
        if (QSslSocket::supportsSsl()) {
            qDebug() << "Qt supports SSL.";
        } else {
            qDebug() << "Qt does not support SSL.";
        }
        */
    return a.exec();
}
