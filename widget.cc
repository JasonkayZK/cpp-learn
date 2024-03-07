#include "widget.h"
#include "ui_Widget.h"
#include <QMessageBox>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);

  client = new QMqttClient;
  client->setHostname("127.0.0.1");
  client->setPort(1883);
  client->setUsername("test");
  client->setPassword("test");

  connect(ui->connectButton, &QPushButton::clicked, this, &Widget::onConnectButtonClicked);
  connect(ui->subButton, &QPushButton::clicked, this, &Widget::onSubButtonClicked);
  connect(ui->pubButton, &QPushButton::clicked, this, &Widget::onPubButtonClicked);
  connect(client, &QMqttClient::connected, this, &Widget::connectSuccess);
}

Widget::~Widget() {
  delete ui;
}

void Widget::connectSuccess() {
  QMessageBox::information(this, "连接提示", "连接成功！");

  // 收到消息处理
  connect(client, &QMqttClient::messageReceived, [=](const QByteArray &message, const QMqttTopicName &topic) {
    QString str = topic.name() + ": " + QString(message);
    ui->textEdit->setText(str);
  });

  // 断开连接处理
  connect(client, &QMqttClient::disconnected, [this]() {
    QMessageBox::warning(this, "连接提示", "服务器断开！");
  });
}

void Widget::onConnectButtonClicked() {
  qDebug() << "连接服务器！";
  client->connectToHost();
}

void Widget::onSubButtonClicked() {
  auto topicName = ui->subTopicEdit->text();
  qDebug() << "订阅了Topic：" << topicName;
  client->subscribe(topicName);
}

void Widget::onPubButtonClicked() {
  QByteArray msg;
  msg.append(ui->msgEdit->text().toUtf8());

  client->publish(ui->pubTopicEdit->text(), msg);
}
