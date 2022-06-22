#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QUdpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QUdpSocket *udpSocket;

private slots:
    void on_openBt_clicked();
    void readyRead_slot();

    void on_sendBt_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
