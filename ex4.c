/**
Name:Ori Bahat-Petel
ID:331753830
Assignment:ex4
***/
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
double round_decimal(double number);

void clear_input_buffer();
int task3_parenthesis_validator(char expect);

void task4_queens_battle();
void reset_solution(char solution[MAX_N][MAX_N], int N);
bool is_safe(int row, int col, char board[MAX_N][MAX_N], bool rows[MAX_N], bool cols[MAX_N], bool regions[All_ASCII], char solution[MAX_N][MAX_N], int N);
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
    char task;
    int RobotX1,RobotY1,result1;
    char grid[MAX_GRID][MAX_GRID];
    double weights[LENG2][LENG2];
    do
    {
        printf("Choose an option:\n"
               "1. Robot Paths\n"
               "2. The Human Pyramid\n"
               "3. Parenthesis Validation\n"
               "4. Queens Battle\n"
               "5. Crossword Generator\n"
               "6. Exit\n");
        scanf("%1c", &task);
        clear_input_buffer();
            switch (task)
            {
            case '6':
                printf("Goodbye!\n");
                break;
            case '1':
                printf("Please enter the coordinates of the robot (column, row):\n");
                scanf("%d %d",&RobotX1,&RobotY1);
                result1 = task1_robot_paths(RobotX1,RobotY1);
                printf("The total number of paths the robot can take to reach home is: %d\n",result1);
                clear_input_buffer();
                break;
            case '2':
                bool notNegative = true;
                printf("Please enter the weights of the cheerleaders:\n");
                for (int i = 0; i < 5 && notNegative; i++) 
                {
                    for (int j = 0; j <= i; j++)
                    {
                            scanf("%lf", &weights[i][j]);
                            if(weights[i][j] < 0)
                            {
                                printf("Negative weights are not supported.\n");
                                notNegative = false;
                                break;
                            }
                    }
                }    
                if(!notNegative)
                {
                    clear_input_buffer();
                    break;
                }
                printf("The total weight on each cheerleader is:\n");
                for (int i = 0; i < LENG2; i++) 
                {
                    for (int j = 0; j <= i; j++) 
                    {
                        double w = task2_human_pyramid(i, j, weights);
                        printf("%.2lf ", round_decimal(w));
                    }
                    printf("\n");
                }
                clear_input_buffer();
                break;
            case '3':
                printf("Please enter a term for validation:\n");
                int ans3 = task3_parenthesis_validator('\0');
                if(ans3 == 1)
                    printf("The parentheses are balanced correctly.\n");
                else if(ans3 == 0) 
                {
                    printf("The parentheses are not balanced correctly.\n");
                    clear_input_buffer();
                }
                else
                    printf("The parentheses are not balanced correctly.\n");
                break;
            case '4':
                task4_queens_battle();
                clear_input_buffer();
                break;
            case '5':
                for (int i = 0; i < MAX_GRID; i++)
                {
                    for (int j = 0; j < MAX_GRID; j++) 
                    {
                        grid[i][j] = '#';
                    }
                }       
                task5_crossword_generator(grid);
                clear_input_buffer();
                break;
            default:
                printf("Please choose a task number from the list.\n");
                break;
            }
    } while (task != '6');
}

int task1_robot_paths(int RobotX,int RobotY)
{
    if(RobotX == 0 && RobotY == 0)
        return 1;
    if(RobotX < 0 || RobotY < 0)
        return 0;
    return task1_robot_paths(RobotX - 1,RobotY) + task1_robot_paths(RobotX,RobotY - 1);
}

double round_decimal(double number) 
{
    number *= 100;
    int intPart = (int)number;
    double decimalPart = number - intPart;
    double result = 0;
    if (decimalPart >= 0.4999999) 
    {
        result = (intPart + 1) / 100.0;
    } 
    else
    {
        result = intPart / 100.0;
    }
    return result;
}

double task2_human_pyramid(int r, int c, double weights[LENG2][LENG2])
{
    if (r == 0)
    {
        if(c == 0) 
            return weights[0][0];
        else
            return 0;
    }
    if(c < 0)
        return 0;
    double left = 0.5 * task2_human_pyramid(r - 1, c, weights);
    double right = 0.5 * task2_human_pyramid(r - 1, c -1, weights);
    return left + right + weights[r][c];
}

void clear_input_buffer()
{
    char c = getchar();
    while (c != '\n' && c != ' ')
        c = getchar();
}

int task3_parenthesis_validator(char expect)
{
    char ch;
    while (scanf("%1c", &ch) == 1) 
    { 
        if (ch == '\n') 
        {
            return expect == '\0';
        }

        if (ch == '(' || ch == '[' || ch == '{' || ch == '<') 
        {
            char match = (ch == '(') ? ')' :
                         (ch == '[') ? ']' :
                         (ch == '{') ? '}' : '>';
            if (!task3_parenthesis_validator(match)) {
                return 2;
            }
        } 
        else if (ch == ')' || ch == ']' || ch == '}' || ch == '>') 
        {
            return ch == expect;
        } 
        else 
        {
            continue;
        }
    }
    return expect == '\0';
}

void task4_queens_battle()
{
    int N;
    char board[MAX_N][MAX_N];
    char solution[MAX_N][MAX_N];
    printf("Please enter the board dimensions:\n");
    scanf("%d", &N);

    read_board(N, board);
    reset_solution(solution, N);
    
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

void reset_solution(char solution[MAX_N][MAX_N], int N) {
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            solution[i][j] = '*';
        }
    }
}

bool is_safe(int row, int col, char board[MAX_N][MAX_N], bool rows[MAX_N], bool cols[MAX_N], bool regions[All_ASCII], char solution[MAX_N][MAX_N], int N)
{
    if (rows[row] || cols[col] || regions[(int)board[row][col]])
        return false;
    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            if (dr == 0 && dc == 0) 
                continue;
            int adj_row = row + dr;
            int adj_col = col + dc;
            if (adj_row >= 0 && adj_row < N && adj_col >= 0 && adj_col < N && solution[adj_row][adj_col] == 'X')
                return false;
        }
    }

    return true;
}

bool place_queen(int row, int col, int N, char board[MAX_N][MAX_N], char solution[MAX_N][MAX_N], bool rows[MAX_N], bool cols[MAX_N], bool regions[All_ASCII]) 
{
    if (col >= N) return true;
    if (row >= N) return false;
    if (is_safe(row, col, board, rows, cols, regions, solution, N)) {
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
    printf("Please enter a %d*%d puzzle board:\n", N, N);
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
    printf("Please enter the number of words in the dictionary:\n");
    do {
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
        print_grid(grid, size);
    } else
    {
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
        printf("| ");
        for (int j = 0; j < size; j++)
        {
            printf("%c", grid[i][j]);
            if (j < size - 1) {
                printf(" | ");
            }
        }
        printf(" |\n");
    }
}
