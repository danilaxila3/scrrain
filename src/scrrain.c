#include <locale.h>
#include <ncurses/ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[]) {
  char *message = NULL;
  int lightnings = 0;

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-m") == 0) {
      message = argv[i + 1];
    }

    if (strcmp(argv[i], "-l") == 0) {
      lightnings = 1;
    }
  }

  srand(time(0));
  setlocale(LC_ALL, "");

  initscr();
  keypad(stdscr, 1);
  noecho();
  curs_set(0);
  timeout(0);
  start_color();

  init_pair(1, COLOR_BLUE, COLOR_BLACK);
  init_pair(2, COLOR_BLACK, COLOR_BLACK);
  init_pair(3, COLOR_BLACK, COLOR_WHITE);

  int running = 1;
  int positions[75][2];
  int lightning_time = 0;

  for (int i = 0; i < 75; i++) {
    positions[i][0] = -rand() % LINES;
    positions[i][1] = rand() % COLS;
  }

  while (running) {
    clear();
    lightning_time -= 1;

    if (lightnings && rand() % 500 == 0) {
      lightning_time = 100;
    }

    for (int i = 0; i < 75; i++) {
      if (i > 50) {
        positions[i][0] += 2;
      } else {
        positions[i][0] += 1;
      }

      if (positions[i][0] > LINES) {
        positions[i][0] = -10;
        positions[i][1] = rand() % COLS;
      }

      if (i > 50) {
        if (rand() % 2 == 0) {
          attron(COLOR_PAIR(1));
        }
      } else {
        attron(COLOR_PAIR(2));

        if (rand() % 2 == 0) {
          attron(A_BOLD);
        }
      }

      for (int j = 0; j < 10; j++) {
        mvprintw(positions[i][0] + j, positions[i][1], "│");
      }

      attroff(COLOR_PAIR(1));
      attroff(COLOR_PAIR(2));
      attroff(A_BOLD);
    }

    if (message != NULL) {
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < (int)strlen(message) + 4; j++) {
          mvprintw(LINES / 2 + i - 1, COLS / 2 - strlen(message) / 2 + j - 2,
                   " ");
        }
      }

      mvprintw(LINES / 2, COLS / 2 - strlen(message) / 2, "%s", message);
    }

    if (lightning_time > 0 && rand() % 5 == 0) {
      attron(COLOR_PAIR(3));
      
      for (int i = 0; i < LINES; i++) {
        for (int j = 0; j < COLS; j++) {
          mvprintw(i, j, " ");
        }
      }

      attroff(COLOR_PAIR(3));
    }

    usleep(1000);

    int input = getch();

    if (input == 'q') {
      running = 0;
    }
  }

  endwin();

  return 0;
}
