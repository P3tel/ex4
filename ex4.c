/******
Name:Ori Bahat-Petel
ID:331753830
Assignment:ex4
*******/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_N 20
#define MAX_GRID 30
#define MAX_WORDS 100
#define MAX_WORD_LENGTH 15
#define LENG2 5
#define All_ASCII 256
typedef struct
{
    int row;
    int col;
    int length;
    char direction;
} Slot;

int task1_robot_paths();

double task2_human_pyramid(int r,int c, double weight[LENG2][LENG2]);

bool task3_parenthesis_validator(char expect);

void task4_queens_battle();
void initialize_solution(char solution[MAX_N][MAX_N], int N);
bool is_safe(int row, int col, char board[MAX_N][MAX_N], bool rows[MAX_N], bool cols[MAX_N], bool regions[All_ASCII]);
bool place_queen(int row, int col, int N, char board[MAX_N][MAX_N], char solution[MAX_N][MAX_N], bool rows[MAX_N], bool cols[MAX_N], bool regions[All_ASCII]);
bool solve(int N, char board[MAX_N][MAX_N], char solution[MAX_N][MAX_N]);
void print_solution(char solution[MAX_N][MAX_N], int N);
void read_board(int N, char board[MAX_N][MAX_N]);

void task5_crossword_generator(char grid[MAX_GRID][MAX_GRID]);
bool fill_crossword(char grid[MAX_GRID][MAX_GRID], Slot slots[MAX_WORDS], int slot_count, char words[MAX_WORDS][MAX_WORD_LENGTH + 1], bool used[MAX_WORDS], int current_slot);
bool can_place_word(char grid[MAX_GRID][MAX_GRID], Slot slot, const char word[MAX_WORD_LENGTH + 1]);
void place_word(char grid[MAX_GRID][MAX_GRID], Slot slot, const char word[MAX_WORD_LENGTH + 1]);
void remove_word(char grid[MAX_GRID][MAX_GRID], Slot slot);
void print_grid(char grid[MAX_GRID][MAX_GRID], int size);

int main()
{
    int task,RobotX1,RobotY1,result1;
    char grid[MAX_GRID][MAX_GRID];
    do
    {
        printf("Choose an option:\n"
               "1. Robot Paths\n"
               "2. The Human Pyramid\n"
               "3. Parenthesis Validation\n"
               "4. Queens Battle\n"
               "5. Crossword Generator\n"
               "6. Exit\n");
        scanf("%d", &task);
            switch (task)
            {
            case 6:
                printf("Goodbye!\n");
                break;
            case 1:
                printf("Please enter the coordinates of the robot (column, row):\n");
                scanf("%d %d",&RobotX1,&RobotY1);
                result1 = task1_robot_paths(RobotX1,RobotY1);
                printf("The total number of paths the robot can take to reach home is: %d\n",result1);
                break;
            case 2:
                double weights[LENG2][LENG2] = {0};
                printf("Please enter the weights of the cheerleaders:\n");
                printf("Please enter the weights of the cheerleaders:\n");
                for (int i = 0; i < 5; i++) 
                {
                    for (int j = 0; j <= i; j++)
                    {
                        do{
                            scanf("%lf", &weights[i][j]);
                            if(weights[i][j] < 0)
                                printf("Negative weights are not supported.\n");
                        }while (weights[i][j] < 0);
                    }
                }       

                printf("The total weight on each cheerleader is:\n");
                for (int i = 0; i < LENG2; i++) 
                {
                    for (int j = 0; j <= i; j++) 
                    {
                        printf("%.2lf ", task2_human_pyramid(i, j, weights));
                    }
                    printf("\n");
                }
                break;
            case 3:
                getchar();
                printf("Please enter a term for validation:\n");
                if(task3_parenthesis_validator('\0'))
                    printf("The parentheses are balanced correctly.\n");
                else
                    printf("The parentheses are not balanced correctly.\n");
                break;
            case 4:
                task4_queens_battle();
                break;
            case 5:
                for (int i = 0; i < MAX_GRID; i++)
                {
                    for (int j = 0; j < MAX_GRID; j++) 
                    {
                        grid[i][j] = '#';
                    }
                }       
                task5_crossword_generator(grid);
                break;
            default:
                printf("Please choose a task number from the list.\n");
                break;
            }
    } while (task != 6);
}

int task1_robot_paths(int RobotX,int RobotY)
{
    if(RobotX == 0 && RobotY == 0)
        return 1;
    if(RobotX < 0 || RobotY < 0)
        return 0;
    return task1_robot_paths(RobotX - 1,RobotY) + task1_robot_paths(RobotX,RobotY - 1);
}

double task2_human_pyramid(int r, int c, double weights[5][5])
{
    if (r >= LENG2)
        return 0;
    double leftWeight = 0.5 * task2_human_pyramid(r + 1, c, weights);
    double rightWeight = 0.5 * task2_human_pyramid(r + 1, c + 1, weights);
    return leftWeight + rightWeight + weights[r][c];
}

bool task3_parenthesis_validator(char expect)
{
    char ch;
    do {
        if (scanf("%c", &ch) != 1) 
        {
            return expect == '\0';
        }
    } while (ch == ' ');

    if (ch == '\n')
    {
        return expect == '\0';
    }
    
    if (ch == '(' || ch == '[' || ch == '{' || ch == '<')
    {
        char match = (ch == '(') ? ')' :
                     (ch == '[') ? ']' :
                     (ch == '{') ? '}' : '>';
        if (!task3_parenthesis_validator(match)) 
        {
            return false;
        }
        return task3_parenthesis_validator(expect);
    }
    if (ch == ')' || ch == ']' || ch == '}' || ch == '>') {
        return ch == expect;
    }
    return task3_parenthesis_validator(expect);
}

void task4_queens_battle()
{
    int N;
    char board[MAX_N][MAX_N];
    char solution[MAX_N][MAX_N];
    printf("Please enter the board dimensions:\n");
    scanf("%d", &N);
    read_board(N, board);
    initialize_solution(solution, N);
    if (solve(N, board, solution))
    {
        printf("Solution:\n");
        print_solution(solution, N);
    } 
    else 
    {
        printf("This puzzle cannot be solved.\n");
    }
}

void initialize_solution(char solution[MAX_N][MAX_N], int N) {
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            solution[i][j] = '*';
        }
    }
}

bool is_safe(int row, int col, char board[MAX_N][MAX_N], bool rows[MAX_N], bool cols[MAX_N], bool regions[All_ASCII])
{
    return !rows[row] && !cols[col] && !regions[(int)board[row][col]];
}

bool place_queen(int row, int col, int N, char board[MAX_N][MAX_N], char solution[MAX_N][MAX_N], bool rows[MAX_N], bool cols[MAX_N], bool regions[All_ASCII]) 
{
    if (col >= N) return true;
    if (row >= N) return false;

    if (is_safe(row, col, board, rows, cols, regions)) {
        rows[row] = cols[col] = regions[(int)board[row][col]] = true;
        solution[row][col] = 'X';

        if (place_queen(0, col + 1, N, board, solution, rows, cols, regions)) return true;

        rows[row] = cols[col] = regions[(int)board[row][col]] = false;
        solution[row][col] = '*';
    }
    return place_queen(row + 1, col, N, board, solution, rows, cols, regions);
}

bool solve(int N, char board[MAX_N][MAX_N], char solution[MAX_N][MAX_N])
{
    bool rows[MAX_N] = {false};
    bool cols[MAX_N] = {false};
    bool regions[All_ASCII] = {false};
    return place_queen(0, 0, N, board, solution, rows, cols, regions);
}

void print_solution(char solution[MAX_N][MAX_N], int N)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%c ", solution[i][j]);
        }
        printf("\n");
    }
}

void read_board(int N, char board[MAX_N][MAX_N])
{
    printf("Please enter the %d*%d puzzle board:\n", N, N);
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++) 
        {
            scanf(" %c", &board[i][j]);
        }
    }
}


void task5_crossword_generator(char grid[MAX_GRID][MAX_GRID]) 
{
    int size;
    int slot_count;
    int word_count;
    Slot slots[MAX_WORDS];
    char words[MAX_WORDS][MAX_WORD_LENGTH + 1];
    bool used[MAX_WORDS] = {false};

    printf("Please enter the dimensions of the crossword grid:\n");
    scanf("%d", &size);

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            grid[i][j] = '#';
        }
    }

    printf("Please enter the number of slots in the crossword:\n");
    scanf("%d", &slot_count);
    printf("Please enter the details for each slot (Row, Column, Length, Direction):\n");
    for (int i = 0; i < slot_count; i++) 
    {
        scanf("%d %d %d %c", &slots[i].row, &slots[i].col, &slots[i].length, &slots[i].direction);
    }

    do {
        printf("Please enter the number of words in the dictionary:\n");
        scanf("%d", &word_count);
        if (word_count < slot_count)
        {
            printf("The dictionary must contain at least %d words. Please enter a valid dictionary size:\n", slot_count);
        }
    } while (word_count < slot_count);

    printf("Please enter the words for the dictionary:\n");
    for (int i = 0; i < word_count; i++)
    {
        scanf("%s", words[i]);
    }

    if (fill_crossword(grid, slots, slot_count, words, used, 0))
    {
        printf("The filled crossword grid is:\n");
        print_grid(grid, size);
    } else {
        printf("This crossword cannot be solved.\n");
    }
}

bool fill_crossword(char grid[MAX_GRID][MAX_GRID], Slot slots[MAX_WORDS], int slot_count, char words[MAX_WORDS][MAX_WORD_LENGTH + 1], bool used[MAX_WORDS], int current_slot) 
{
    if (current_slot == slot_count) 
    {
        return true;
    }

    Slot slot = slots[current_slot];
    for (int i = 0; i < slot_count; i++) 
    { 
    if (!used[i] && strlen(words[i]) == (size_t)slot.length && can_place_word(grid, slot, words[i]))
        {
            place_word(grid, slot, words[i]);
            used[i] = true;

            if (fill_crossword(grid, slots, slot_count, words, used, current_slot + 1))
            {
                return true;
            }
            remove_word(grid, slot);
            used[i] = false;
        }
    }

    return false;
}

bool can_place_word(char grid[MAX_GRID][MAX_GRID], Slot slot, const char word[MAX_WORD_LENGTH + 1]) 
{
    int row = slot.row;
    int col = slot.col;

    for (int i = 0; i < slot.length; i++) 
    {
        char cell = grid[row][col];
        if (cell != '#' && cell != word[i]) 
        {
            return false;
        }
        if (slot.direction == 'H')
        {
            col++;
        } else {
            row++;
        }
    }

    return true;
}

void place_word(char grid[MAX_GRID][MAX_GRID], Slot slot, const char word[MAX_WORD_LENGTH + 1]) 
{
    int row = slot.row;
    int col = slot.col;

    for (int i = 0; i < slot.length; i++) 
    {
        grid[row][col] = word[i];
        if (slot.direction == 'H') 
        {
            col++;
        } 
        else 
        {
            row++;
        }
    }
}

void remove_word(char grid[MAX_GRID][MAX_GRID], Slot slot)
{
    int row = slot.row;
    int col = slot.col;

    for (int i = 0; i < slot.length; i++)
    {
        grid[row][col] = '#';
        if (slot.direction == 'H') 
        {
            col++;
        } 
        else 
        {
            row++;
        }
    }
}

void print_grid(char grid[MAX_GRID][MAX_GRID], int size)
{
    for (int i = 0; i < size; i++) 
    {
        for (int j = 0; j < size; j++)
        {
            printf("%c", grid[i][j]);
            if (j < size - 1) {
                printf(" | ");
            }
        }
        printf("\n");
    }
}
