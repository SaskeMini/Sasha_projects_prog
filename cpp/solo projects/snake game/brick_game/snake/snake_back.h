#include <vector>
#include "stdlib.h"

#define WIDTH 20
#define HEIGHT 10
#define SQUARE_SIZE 40

typedef enum{
    Start,
    Pause,
    Terminate,
    Left,
    Right,
    Up,
    Down,
    Action
} UserAction_t;

typedef enum{
    L,
    R,
    U,
    D
} Snake_direction;

typedef struct {
    int **field;
    int **next;
    int score;
    int high_score;
    int level;
    int speed;
    int pause;
} GameInfo_t;

typedef struct {
    std::vector<std::pair<int, int> > points;
    Snake_direction curr_direction;
    int head_h, head_w;
} Snake_info;

typedef struct {
    bool apple_in_field;
    int h, w;
} Apple_info;

namespace s21{

class Snake_model{
    private:
        GameInfo_t curr;
        Snake_info snake_body;
        int check_to_lose;
        Apple_info apple;

    public:
        GameInfo_t updateCurrentState();

        Snake_model(){
            curr.field = (int**)calloc(HEIGHT, sizeof(int*));
            curr.next = (int**)calloc(HEIGHT, sizeof(int*));
            for (int i = 0; i < HEIGHT; i++){
                curr.field[i] = (int*)calloc(WIDTH, sizeof(int));
                curr.next[i] = (int*)calloc(WIDTH, sizeof(int));
            }
            curr.score = 3;
            curr.level = 1;
            curr.speed = 250;
            curr.pause = 0;
            snake_body.curr_direction = R;
            snake_body.head_h = HEIGHT / 2;
            snake_body.head_w = 3;
            snake_body.points.push_back(std::make_pair(HEIGHT / 2, 3));
            snake_body.points.push_back(std::make_pair(HEIGHT / 2, 2));
            snake_body.points.push_back(std::make_pair(HEIGHT / 2, 1));
            check_to_lose = 1;
            apple.h = HEIGHT / 2;
            apple.w = 15;
            apple.apple_in_field = true;
        }

        ~Snake_model(){
            for (int i = 0; i < HEIGHT; i++){
                free(curr.field[i]);
                free(curr.next[i]);
            }
            free(curr.field);
            free(curr.next);
            curr.score = 0;
            curr.level = 1;
            curr.speed = 0;
            curr.pause = 0;
        }

        Snake_model(const Snake_model&other);

        Snake_model(Snake_model&& other);

        void create_next(){
            this->snake_move_head();
            curr.next[snake_body.head_h][snake_body.head_w] = 2;
            for (size_t i = 1; i < (snake_body.points).size(); i++){
                curr.next[snake_body.points[i].first][snake_body.points[i].second] = 1;
            }
            if (apple.apple_in_field){
                curr.next[apple.h][apple.w] = 3;
            }
            else{
                generate_apple();
                curr.next[apple.h][apple.w] = 3;
            }
        }

        void snake_move_head(){
            if (snake_body.curr_direction == U){
                if (snake_body.head_h - 1 >= 0){
                    snake_body.points[0].first--;
                }
                else{
                    check_to_lose = 0;
                }
            }
            else if (snake_body.curr_direction == D){
                if (snake_body.head_h + 1 < HEIGHT){
                    snake_body.points[0].first++;
                }
                else{
                    check_to_lose = 0;
                }
            }
            else if (snake_body.curr_direction == L){
                if (snake_body.head_w - 1 >= 0){
                    snake_body.points[0].second--;
                }
                else{
                    check_to_lose = 0;
                }
            }
            else if (snake_body.curr_direction == R){
                if (snake_body.head_w + 1 < WIDTH){
                    snake_body.points[0].second++;
                }
                else{
                    check_to_lose = 0;
                }
            }
            for (size_t i = 1; i < snake_body.points.size(); i++){
                if (snake_body.points[i].first == snake_body.points[0].first && snake_body.points[i].second == snake_body.points[0].second){
                    check_to_lose = 0;
                }
            }
            if (check_to_lose){
                this->apple_collision(snake_body.points[0].first, snake_body.points[0].second);
                this->snake_move_body(snake_body.head_h, snake_body.head_w);
                snake_body.head_h = snake_body.points[0].first;
                snake_body.head_w = snake_body.points[0].second;
            }
        }

        void snake_move_body(int h, int w){
            bool check = true;
            for (size_t i = 1; i < snake_body.points.size() && check; i++){
                int temp_h, temp_w;
                temp_h = snake_body.points[i].first;
                temp_w = snake_body.points[i].second;
                snake_body.points[i].first = h;
                snake_body.points[i].second = w;
                h = temp_h;
                w = temp_w;
                if (i == snake_body.points.size() - 1 && !apple.apple_in_field){
                    check = false;
                    snake_body.points.push_back(std::make_pair(h, w));
                    curr.score++;
                }
            }
        }

        void apple_collision(int h, int w){
            if (h == apple.h && w == apple.w){
                apple.apple_in_field = false;
            }
        }

        void replace_info(GameInfo_t *other, int *in_game){
          curr.level <= 10 ? curr.level = (curr.score / 5) : curr.level = 10;
          if (check_to_lose){
            this->create_next();
            for (int i = 0; i < HEIGHT; i++){
                for (int j = 0; j < WIDTH; j++){
                    other->field[i][j] = curr.next[i][j];
                    curr.next[i][j] = 0;
                }
            }
            curr.speed = 250 - 15 * curr.level;
            other->score = curr.score;
            other->speed = curr.speed;
            other->pause = curr.pause;
            other->level = curr.level;
            other->high_score = curr.high_score;
          }
          else{
              other->score = curr.score;
              other->speed = curr.speed;
              other->pause = curr.pause;
              other->level = curr.level;
              other->high_score = curr.high_score;
              *in_game = check_to_lose;
          }
        }

        void generate_apple(){
            while (!apple.apple_in_field){
                apple.h = rand() % HEIGHT;
                apple.w = rand() % WIDTH;
                if (curr.next[apple.h][apple.w] == 0){
                    apple.apple_in_field = true;
                }
            }
        }

        void work_with_user(UserAction_t new_key, GameInfo_t *other){
            if (new_key == Up && snake_body.curr_direction != D){
                snake_body.curr_direction = U;
            }
            if (new_key == Right && snake_body.curr_direction != L){
                snake_body.curr_direction = R;
            }
            if (new_key == Left && snake_body.curr_direction != R){
                snake_body.curr_direction = L;
            }
            if (new_key == Down && snake_body.curr_direction != U){
                snake_body.curr_direction = D;
            }
            if (new_key == Terminate){
                check_to_lose = 0;
            }
            if (new_key == Pause){
                curr.speed = 100000;
                other->speed = curr.speed;
            }
        }
};
}