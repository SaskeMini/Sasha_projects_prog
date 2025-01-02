#include <QtWidgets/QApplication>

#include "../../gui/desktop/s21_brick_game.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    s21::Snake_view snake;
    snake.show();
    return app.exec();
}
