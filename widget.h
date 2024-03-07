//
// Created by jasonkay on 2024/3/7.
//

#ifndef CPP_LEARN_WIDGET_H_
#define CPP_LEARN_WIDGET_H_

#include <QWidget>
#include <QtMqtt/qmqttclient.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget {
 Q_OBJECT

 public:
  explicit Widget(QWidget *parent = nullptr);
  ~Widget() override;

 private:
  Ui::Widget *ui;

  QMqttClient *client;

 private slots:
  void onConnectButtonClicked();

  void onSubButtonClicked();

  void onPubButtonClicked();

  void connectSuccess();

};

#endif //CPP_LEARN_WIDGET_H_
