#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#include "config.h"

typedef struct {
	unsigned long long gain;
	unsigned long long score;
} Game;

int main(void) {
	char savefilepath[4096];
	strcpy(savefilepath, getenv("HOME"));
	strcat(savefilepath, "/.config/btclickersave.bin");

	initscr();
	cbreak();
	noecho();
	clear();

	printw("Attempt to load progress from save file? [Y/n]");
	char choice = getch();

	Game game;

	if (choice != 'n') {
		FILE *savefile = fopen(savefilepath, "rb");
		if (savefile != NULL) {
			fread(&game, sizeof(Game), 1, savefile);
			fclose(savefile);
		} else {
			clear();
			endwin();
			fprintf(stderr, "btclicker: Could not open save file: ~/.config/btclickersave.bin\n");
			return 1;
		}
	} else {
		game.gain = 1;
		game.score = 0;
	}

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
			printw("Attempt to save progress to save file? [Y/n]");
			char choice = getch();

			if (choice != 'n') {
				FILE *savefile = fopen(savefilepath, "wb");
				if (savefile != NULL) {
					fwrite(&game, sizeof(Game), 1, savefile);
					fclose(savefile);
				} else {
					clear();
					endwin();
					fprintf(stderr, "btclicker: Could not open save file: ~/.config/btclickersave.bin\n");
					return 1;
				}
			}

			endwin();
			running = 0;
		}
	}
	return 0;
}
