#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

typedef struct {
	unsigned long long score;
	unsigned long long gain;
} Game;

int main(void) {
	Game game;
	game.score = 0;
	game.gain = 1;

	initscr();
	cbreak();
	noecho();
	
	while (1) {
		char choice;
		unsigned long long upgradecost = game.gain * game.gain * game.gain * 5;
		
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
			exit(0);
		}
	}
	return 0;
}
