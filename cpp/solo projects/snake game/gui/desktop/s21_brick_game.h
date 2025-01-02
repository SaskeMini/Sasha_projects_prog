#ifndef S21_BRICK_GAME_H
#define S21_BRICK_GAME_H

#include <iostream>
#include <string.h>
#include "../../brick_game/snake/snake_back.h"
#include <QWidget>
#include <QKeyEvent>
#include <QTimerEvent>
#include <QPainter>
#include <QDebug>
#include <QMessageBox>

#define WIDTH 20
#define HEIGHT 10
#define SQUARE_SIZE 40

namespace s21{

    class Snake_controller {
        private:
            UserAction_t curr;
        public:
            Snake_controller(){
                curr = Right;
            };

            ~Snake_controller() = default;

            Snake_controller(const Snake_controller&other);

            Snake_controller(Snake_controller&& other);

            UserAction_t return_current_key(){
                return curr;
            }

            void keyPressEvent(QKeyEvent* event){
                switch(event->key()){
                    case Qt::Key_Up:
                        curr = Up;
                        break;
                    case Qt::Key_Down:
                        curr = Down;
                        break;
                    case Qt::Key_Right:
                        curr = Right;
                        break;
                    case Qt::Key_Left:
                        curr = Left;
                        break;
                    case Qt::Key_Escape:
                        curr = Terminate;
                        break; // Выход
                    case Qt::Key_Space:
                        curr = Pause;
                        break; // Пауза
                    default:
                        break;
                }
            }
    };

    class Snake_view : public QWidget{
        private:
            int timer;
            GameInfo_t curr;
            Snake_model model;
            Snake_controller control;
            int in_game;

        public:
            Snake_view() {
                curr.field = (int**)calloc(HEIGHT, sizeof(int*));
                for (int i = 0; i < HEIGHT; i++){
                    curr.field[i] = (int*)calloc(WIDTH, sizeof(int));
                }
                curr.score = 0;
                curr.level = 1;
                curr.speed = 250;
                curr.pause = 0;
                in_game = 1;
                this->setWindowTitle("Snake_game");
                resize(SQUARE_SIZE * WIDTH, SQUARE_SIZE * HEIGHT);
                timer = startTimer(curr.speed);
            };

            ~Snake_view() = default;

            Snake_view(const Snake_view& other);

            Snake_view(Snake_view&& other);

            void timerEvent(QTimerEvent *event){
                Q_UNUSED(event);
                this->update();
                this->repaint();
                if (in_game == 0){
                    this->game_over();
                }
            };

            void keyPressEvent(QKeyEvent *event){
                Q_UNUSED(event);
                control.keyPressEvent(event);
                model.work_with_user(control.return_current_key(), &curr);
            };

            void game_over(){
                QMessageBox msgt;
                if (curr.score == HEIGHT * WIDTH){
                    msgt.setText("You win!");
                }
                else{
                    msgt.setText("Game over! Your score");
                }
                msgt.exec();
            }

            void paintEvent(QPaintEvent* event){
                Q_UNUSED(event);
                draw_field();
            };

            void draw_field(){
                if (in_game == 1){
                    QPainter qp(this);
                    for (int i = 0; i < HEIGHT; i++){
                       for (int j = 0; j < WIDTH; j++){
                           if (curr.field[i][j] == 0){
                               qp.setBrush((QBrush(Qt::white, Qt::SolidPattern)));
                               qp.drawRect(40 * j, 40 * i, SQUARE_SIZE, SQUARE_SIZE);
                           }
                           else if (curr.field[i][j] == 1){
                               qp.setBrush((QBrush(Qt::green, Qt::SolidPattern)));
                               qp.drawRect(40 * j, 40 * i, SQUARE_SIZE, SQUARE_SIZE);
                           }
                           else if (curr.field[i][j] == 3){
                               qp.setBrush((QBrush(Qt::red, Qt::SolidPattern)));
                               qp.drawRect(40 * j, 40 * i, SQUARE_SIZE, SQUARE_SIZE);
                           }
                           else{
                               qp.setBrush((QBrush(Qt::darkGreen, Qt::SolidPattern)));
                               qp.drawRect(40 * j, 40 * i, SQUARE_SIZE, SQUARE_SIZE);
                           }
                       }
                    }
                }
            };

            void update(){
                model.replace_info(&curr, &in_game);
                if (in_game == 0){
                    killTimer(timer);
                }
                else{
                    killTimer(timer);
                    timer = startTimer(curr.speed);
                }
            }
    };
}

#endif // S21_BRICK_GAME_H
