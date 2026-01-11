#include <stdio.h>
#include <unistd.h>

#define COLS 100
#define ROWS 40
#define CELLS (COLS*ROWS)
#define ALIVE '0'
#define DEAD '.'

int cell_to_index(int x, int y) {
    if (x < 0) { 
        x = (-x) % COLS;
        x = COLS - x;
    } 
    if (y < 0) { 
        y = (-y) % ROWS;
        y = ROWS - y;
    }

    if (x >= COLS) x = x % COLS;
    if (y >= ROWS) y = y % ROWS;
    
    return y * COLS + x; 
}
void set_cell(char *grid, int x, int y, char state) {
    grid[cell_to_index(x, y)] = state;
}

char get_cell(char *grid, int x, int y) {
    return grid[cell_to_index(x, y)];
}

void print_grid(char *grid, int gen, int pop) {
    printf("\x1b[3J\x1b[H\x1b[2J");
    printf("[generation: %d] - [population: %d]\n", gen, pop);
    for (int y=0; y < ROWS; y++) {
        for (int x=0; x < COLS; x++) {
            printf("%c", get_cell(grid, x, y));
        }
        printf("\n");
    }
}

void set_grid(char *grid, char state) {
    for (int y=0; y < ROWS; y++) {
        for (int x=0; x < COLS; x++) {
            set_cell(grid, x, y, state);
        }
    }

}

int count_living_neighbours(char *grid, int x, int y) {
    return 
       (get_cell(grid, x-1, y-1) == ALIVE) +  
       (get_cell(grid, x, y-1) == ALIVE) +  
       (get_cell(grid, x+1, y-1) == ALIVE) +  
       (get_cell(grid, x-1, y) == ALIVE) +  
       (get_cell(grid, x+1, y) == ALIVE) +  
       (get_cell(grid, x-1, y+1) == ALIVE) +  
       (get_cell(grid, x, y+1) == ALIVE) +  
       (get_cell(grid, x+1, y+1) == ALIVE); 
}

int set_new_state(char *old_grid, char *new_grid) {
    int state_changed = 0;
    for (int y=0; y < ROWS; y++) {
        for (int x=0; x < COLS; x++) {
            int n_alive = count_living_neighbours(old_grid, x, y);
            char new_state = DEAD;
            char old_state = get_cell(old_grid, x, y);

            if (get_cell(old_grid, x, y) == ALIVE) {
                // alive cell
                if (n_alive == 2 || n_alive == 3) {
                    new_state = ALIVE;
                }
            } else {
                // dead cell
                if (n_alive == 3) {
                    new_state = ALIVE; 
                }            
            }
            
            if (new_state != old_state) state_changed = 1;
            set_cell(new_grid, x, y, new_state);
        }
    }

    return state_changed;
}


int get_population(char *grid) {
    int pop = 0;
    for (int y=0; y < ROWS; y++) {
        for (int x=0; x < COLS; x++) {
            if (get_cell(grid, x, y) == ALIVE) pop++;
        }
    }

    return pop;
}

void sleep_ms(int milliseconds){
    #ifdef WIN32
        Sleep(milliseconds);
    #elif _POSIX_C_SOURCE >= 199309L
        struct timespec ts;
        ts.tv_sec = milliseconds / 1000;
        ts.tv_nsec = (milliseconds % 1000) * 1000000;
        nanosleep(&ts, NULL);
    #else
        usleep(milliseconds * 1000);
    #endif
}

int main(void) {
    int gen = 1;
    int pop = 0;
    int is_stable = 0;

    char new_grid[CELLS];
    char old_grid[CELLS];
    char *old = old_grid;
    char *new = new_grid;

    set_grid(old_grid, DEAD);
    set_grid(new_grid, DEAD);
    

    set_cell(old_grid, 25, 8, ALIVE);
    set_cell(old_grid, 24, 8, ALIVE);

    set_cell(old_grid, 25, 9, ALIVE);
    set_cell(old_grid, 26, 9, ALIVE);
    set_cell(old_grid, 27, 9, ALIVE);
    set_cell(old_grid, 28, 9, ALIVE);

    set_cell(old_grid, 25, 7, ALIVE);
    set_cell(old_grid, 25, 7, ALIVE);
    set_cell(old_grid, 23, 10, ALIVE);
    set_cell(old_grid, 24, 10, ALIVE);
    set_cell(old_grid, 25, 10, ALIVE);
    set_cell(old_grid, 26, 10, ALIVE);
    set_cell(old_grid, 27, 10, ALIVE);
  
    
    pop = get_population(old_grid);
    print_grid(old_grid, gen, pop);
    sleep_ms(1000);    
    
    while (1) {
        is_stable = set_new_state(old, new);
        if (is_stable == 0) break;
        
        pop = get_population(new_grid);
        gen++;
        print_grid(new_grid, gen, pop);
        sleep_ms(100);

        char *tmp = old;
        old = new;
        new = tmp;
    }
    
    return 0;
}
























