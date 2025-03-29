/**
 * @file tetris_back_2.h
 * @author karstarl
 * @brief 
 * @version 0.1
 * @date 2024-07-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef TETRIS_V2
#define TETRIS_V2
#define WINDOW_WIDTH 10
#define WINDOW_HEIGHT 21
#define SPAWN_POS_X 3
#define SPAWN_POS_Y 0
#define FILE_SCORE "./game_info/highscore_list.txt"
#define BAD_ALLOC 1

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

/**
 * @brief Enum with possible user Action
 * 
 */
typedef enum {
    Start,
    Pause,
    Terminate,
    Left,
    Right,
    Up,
    Down,
    Action
} UserAction_t;

/**
 * @brief enum with all block types of tetris
 * 
 */
typedef enum block_type {L_block, I_block, T_block, square, Z_block, RL_block, RZ_block} block_type;

/**
 * @brief enum with all types of game cell state
 * 
 */
typedef enum cell_state {empty, block, active_block} cell_state;

typedef enum position {top, left, bottom, right} position;

/**
 * @brief Struct with main game info
 * 
 * @param field Main tetris map
 * @param next Don`t use in tetris but need for other games
 * @param score Contains current score
 * @param high_score Contains best score of all games
 * @param level Contains difficult of game
 * @param speed not used in tetris
 * @param pause
 */
typedef struct {
    int **field;
    int **next;
    int score;
    int high_score;
    int level;
    int speed;
    int pause;
} GameInfo_t;

/**
 * @brief Contains 2 point of Rectangle shape
 * 
 */
typedef struct {
    int x1;
    int x2;
    int y1;
    int y2;
    position pos;
} Rectangle_t;

/**
 * @brief struct with all info for game map
 * @param info contains game map, score, level, speed and highscore of game
 * @param block current active block
 * @param next_block next spawn block, when @param block get down
 * @param rect contains position of current active block
 */
typedef struct{
    GameInfo_t *info;
    block_type block;
    block_type next_block;
    Rectangle_t rect;
}GameState_t;

/**
 * @brief make action from user input
 * 
 * @param action current player action
 * @param hold contain active user hold
 */
void userInput(UserAction_t action, bool hold);

/**
 * @brief 
 * 
 * @return current game state
 */
GameInfo_t updateCurrentState();

/**
 * @brief 
 * 
 * @return initialisation tetris map
 */
void init_tetris_map(GameState_t* state);

int get_active_position(Rectangle_t* rect, bool rotate);
int get_max_active_x();
int get_min_active_x();
int get_max_active_y();
int get_min_active_y();

/**
 * @brief moves active piece in left if is no obstacle
 * @param state current game state
 */
void try_left(GameState_t* state);

/**
 * @brief moves active piece in right if is no obstacle
 * @param state current game state
 */
void try_right(GameState_t* state);

/**
 * @brief moves active piece down if is no obstacle
 * @param state current game state
 * @return 1 if impossible to move down 
 */
int try_down(GameState_t* state);

/**
 * @brief rotate active piece on 90 degrees
 * @param state current game state
 */
void rotate_block(GameState_t* state);

/**
 * @brief delete all dynamic objects
 * @param state current game state
 */
void clear_tetris(GameState_t* state);

/**
 * @brief spawn new block on tetris map
 * @param state current game state
 * @param block type of spawn block
 */
void spawn_new_block(GameState_t* state);

/**
 * @brief Get the random block object
 * 
 * @return random block
 */
block_type get_random_block();

/**
 * @brief break full lines and update game score
 * @param state current game state
 * @return 1 if is game over
 */
int get_score(GameState_t* state);

/**
 * @brief delete specified line
 * @param state current game state
 * @param line y position of line to delete
 */
void delete_line(GameState_t* state, int line);

/**
 * @brief turns all active blocks in nonactive
 * @param state current game state
 */
void active_to_block(GameState_t* state);

/**
 * @brief set new highscore, if score > highscore
 * @param state current game state
 */
void set_new_highscore(GameState_t* state);

/**
 * @brief set new level depending on points scored
 * @param state current game state
 */
void set_new_level(GameState_t* state);

/**
 * @brief set new game state or return current game state if *state == NULL
 * @param state current game state
 * @return current game state
 */
GameState_t* get_set_current_map(GameState_t* state);

/**
 * @brief chooses block state
 * @param buf where to save new block state
 * @param bt block type
 * @param pos block position
 * @param spawn_pos_x x coordinate for spawn position
 */
void choose_blstate(int** buf, block_type bt, position pos, int spawn_pos_x);

/**
 * @brief spawns new block
 * @param state current game state
 * @param spawn_pos_x x coordinate for spawn position
 */
void spawn_block(GameState_t *state, int spawn_pos_x);

/**
 * @brief safe memory allocation
 * @param size amount of memory
 * @return void pointer
 */
void* s21_malloc(const size_t size);

/**
 * @brief safe matrix memory allocation
 * @param y number of rows
 * @param x number of columns
 * @return int** pointer
 */
int** s21_malloc_matrix(const size_t y, const size_t x);

/**
 * @brief safe matrix memory release
 * @param matrix matrix pointer
 * @param r_size number of rows
 */
void free_matrix(int** matrix, int r_size);

static const int block_state[7][4][16] = \
{                       \
 /*L_block*/ {{0,0,2,0,2,2,2,0,0,0,0,0,0,0,0,0},{2,2,0,0,0,2,0,0,0,2,0,0,0,0,0,0},{2,2,2,0,2,0,0,0,0,0,0,0,0,0,0,0},{2,0,0,0,2,0,0,0,2,2,0,0,0,0,0,0}},     \
 /*I_block*/ {{0,0,0,0,2,2,2,2,0,0,0,0,0,0,0,0},{0,2,0,0,0,2,0,0,0,2,0,0,0,2,0,0},{0,0,0,0,2,2,2,2,0,0,0,0,0,0,0,0},{0,2,0,0,0,2,0,0,0,2,0,0,0,2,0,0}},                     \
 /*T_block*/ {{0,2,0,0,2,2,2,0,0,0,0,0,0,0,0,0},{0,2,0,0,2,2,0,0,0,2,0,0,0,0,0,0},{2,2,2,0,0,2,0,0,0,0,0,0,0,0,0,0},{0,2,0,0,0,2,2,0,0,2,0,0,0,0,0,0}},                     \
 /*square*/  {{0,2,2,0,0,2,2,0,0,0,0,0,0,0,0,0},{0,2,2,0,0,2,2,0,0,0,0,0,0,0,0,0},{0,2,2,0,0,2,2,0,0,0,0,0,0,0,0,0},{0,2,2,0,0,2,2,0,0,0,0,0,0,0,0,0}},                     \
 /*Z_block*/ {{2,2,0,0,0,2,2,0,0,0,0,0,0,0,0,0},{0,2,0,0,2,2,0,0,2,0,0,0,0,0,0,0},{2,2,0,0,0,2,2,0,0,0,0,0,0,0,0,0},{0,2,0,0,2,2,0,0,2,0,0,0,0,0,0,0}},                     \
 /*RL_block*/{{2,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0},{0,2,0,0,0,2,0,0,2,2,0,0,0,0,0,0},{2,2,2,0,0,0,2,0,0,0,0,0,0,0,0,0},{2,2,0,0,2,0,0,0,2,0,0,0,0,0,0,0}},                     \
 /*RZ_block*/{{0,2,2,0,2,2,0,0,0,0,0,0,0,0,0,0},{2,0,0,0,2,2,0,0,0,2,0,0,0,0,0,0},{0,2,2,0,2,2,0,0,0,0,0,0,0,0,0,0},{2,0,0,0,2,2,0,0,0,2,0,0,0,0,0,0}}                      \
};


#endif