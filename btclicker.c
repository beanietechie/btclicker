#include <stdio.h>
//#include <stdlib.h>
#include <ncurses.h>

#include "config.h"

typedef struct {
	unsigned long long gain;
	unsigned long long score;
} Game;

int main(void) {
	Game game;
	game.score = 0;
	game.gain = 1;

	initscr();
	cbreak();
	noecho();
	
	char running = 1;
	while (running) {
		char choice;
		const unsigned long long upgradecost = getupgradecost(game.gain);
		
		clear();
		printw("Score: %lld\nScore per click: %lld\n", game.score, game.gain);
		printw("\n(Enter): Click\n(u): Upgrade score per click (Cost: %lld)\n(q): Quit\n", upgradecost);

		choice = getch();

		if (choice == '\n') {
			game.score += game.gain;
		} else if (choice == 'u' && game.score >= upgradecost) {
			game.score -= upgradecost;
			game.gain++;
		} else if (choice == 'q') {
			clear();
			endwin();
			running = 0;
		}
	}
	return 0;
}
