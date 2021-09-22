#include <chrono>
#include <ctime>
#include <curses.h>
#include <iostream>
#include <stdlib.h>
#include <thread>
using namespace std;

const int ROWS = 48;
const int COLUMNS = 160;
const char DEAD_SPACE = ' ';
const char LIVE_SPACE = '*';

void InitializeCurses() {
  initscr();
  cbreak();
  noecho();
  clear();
}

void PrintExitInstructions() {
  mvaddstr(ROWS + 1, 0, "Press ctrl+c to quit ");
  refresh();
}

void PrintRow(string row_to_print, int row) {
  mvaddstr(row, 0, row_to_print.c_str());
  refresh();
  this_thread::sleep_for(chrono::milliseconds(1));
}

void Initialize (char life[ROWS][COLUMNS]) {
  for(int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      life[i][j] = DEAD_SPACE;
    }
  }
}

void Glider(char life[ROWS][COLUMNS]) {
  life [10][40] = LIVE_SPACE;
  life [9][40] = LIVE_SPACE;
  life [10][39] = LIVE_SPACE;
  life [8][39] = LIVE_SPACE;
  life [10][38] = LIVE_SPACE;
}

void Spaceship (char life[ROWS][COLUMNS]) {
  life [20][40] = LIVE_SPACE;
  life [18][40] = LIVE_SPACE;
  life [17][41] = LIVE_SPACE;
  life [17][42] = LIVE_SPACE;
  life [17][43] = LIVE_SPACE;
  life [17][44] = LIVE_SPACE;
  life [18][44] = LIVE_SPACE;
  life [19][44] = LIVE_SPACE;
  life [20][43] = LIVE_SPACE;
}

void PrintLife (char life[ROWS][COLUMNS]) {
  for (int i = 0; i < ROWS; i++ ) {
    string row_to_print = "";
    for (int j = 0; j < COLUMNS; j++) {
      row_to_print += life[i][j];
    }
    PrintRow(row_to_print, i);
  }
}

int NeighborCounter(char life[ROWS][COLUMNS], int i, int j) {
  int neighbor_counter = 0;
  int top = i-1;
  if (i == 0) {
    top = ROWS-1;
  }
  int right = j+1;
  if (j == COLUMNS-1) {
    right = 0;
  }
  int bottom = i+1;
  if (i == ROWS-1) {
    bottom = 0;
  }
  int left = j-1;
  if (j == 0) {
    left = COLUMNS-1;
  }

  if (life[top][j] == LIVE_SPACE) {             // top
    neighbor_counter++;
  }
  if (life[top][right] == LIVE_SPACE) {         // top_right
    neighbor_counter++;
  }
  if (life[i][right] == LIVE_SPACE) {           // right
    neighbor_counter++;
  }
  if (life[bottom][right] == LIVE_SPACE) {      // bottom right
    neighbor_counter++;
  }
  if (life[bottom][j] == LIVE_SPACE) {          // bottom
    neighbor_counter++;
  }
  if (life[bottom][left] == LIVE_SPACE) {       // bottom left
    neighbor_counter++;
  }
  if (life[i][left] == LIVE_SPACE) {            /// left
    neighbor_counter++;
  }
  if (life[top][left] == LIVE_SPACE) {          // top left
    neighbor_counter++;
  }
return neighbor_counter;
}

void Transfer(char copy_life [ROWS][COLUMNS], char life [ROWS][COLUMNS]) {
  for(int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      copy_life[i][j] = life[i][j];
    }
  }
}

void ApplyRules(char copy_life[ROWS][COLUMNS], char life[ROWS][COLUMNS]) {
  for(int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      int neighbors = NeighborCounter(copy_life, i ,j);
      if (copy_life[i][j] == LIVE_SPACE){
        if (neighbors < 2) {
          life [i][j] = DEAD_SPACE;
        }
        else if (neighbors == 2 || neighbors == 3) {
          life [i][j] = LIVE_SPACE;
        }
        else if (neighbors > 3) {
          life[i][j] = DEAD_SPACE;
        }
      }
      else if (copy_life[i][j] == DEAD_SPACE) {
        if (neighbors == 3) {
          life[i][j] = LIVE_SPACE;
        }
      }
    }
  }
}

int main(int argc, char* argv[]) {
  InitializeCurses();
  char copy_life [ROWS][COLUMNS];
  char life [ROWS][COLUMNS];
  Initialize(life);
  Glider(life);
  PrintExitInstructions();

  while (true) {
    PrintLife(life);
    Transfer(copy_life, life);
    ApplyRules (copy_life, life);
  }
  endwin();
  return 0;
}