#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
#include <QMainWindow>
#include <QSettings>

#include "main.h"
// #include <QGifImage>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QImage>
#include <QImageWriter>
#include <QPainter>
#include <QTimer>

#include "gif_lib.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace s21 {
class View : public QMainWindow {
  Q_OBJECT

 public:
  explicit View(QWidget *parent = nullptr);
  ~View();

 private slots:
  void on_pushButton_7_clicked();
  void on_pushButton_8_clicked();
  void on_pushButton_9_clicked();
  void on_pushButton_10_clicked();
  void on_pushButton_11_clicked();
  void on_pushButton_12_clicked();
  void on_pushButton_13_clicked();
  void on_pushButton_14_clicked();
  void on_pushButton_save_image_clicked();
  void on_pushButton_gif_clicked();
  void on_horizontalSlider_actionTriggered(int action);
  void on_horizontalSlider_2_actionTriggered(int action);
  void on_horizontalSlider_3_actionTriggered(int action);
  void on_horizontalSlider_4_actionTriggered(int action);
  void on_horizontalSlider_5_actionTriggered(int action);
  void on_horizontalSlider_6_actionTriggered(int action);
  void on_horizontalSlider_7_actionTriggered(int action);
  void on_horizontalSlider_8_actionTriggered(int action);
  void on_horizontalSlider_9_actionTriggered(int action);
  void RecordGif();

 private:
  Ui::View *ui;
  QSettings *settings;
  TestQt win;
  int x_value, y_value, z_value, scale_value, x_rotate_value, y_rotate_value,
      z_rotate_value;

  GifFileType *gif;
  QTimer *timer;

  std::vector<QImage> frames_;  // Хранение кадров
  QTimer *timer_ = nullptr;
  int frame_count_ = 0;  // Количество записанных кадров
  int max_frames_ = 50;
};
}  // namespace s21
#endif  // MAINWINDOW_H
