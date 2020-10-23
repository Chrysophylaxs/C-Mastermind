#include "mastermind.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int min(int a, int b) {
	return a < b ? a : b;
}

void generate_secret(struct mastermind* mastermind) {
	mastermind->secret = malloc(SECRET_LEN * sizeof(int));
	srand(time(NULL));
	for (int i = 0; i < SECRET_LEN; i++) {
		mastermind->secret[i] = rand() % 8;
	}
}

struct mastermind* mastermind_init() {
	struct mastermind* mastermind = malloc(sizeof(struct mastermind));
	mastermind->turn = 0;
	generate_secret(mastermind);
	mastermind->guesses = malloc(NUM_GUESSES * sizeof(int*));
	return mastermind;
}

struct result verify_guess(struct mastermind* mastermind) {
	int freq_secret[NUM_COLORS] = {0};
	int freq_guess[NUM_COLORS] = {0};
	int similar = 0;
	int equal = 0;
	for (int i = 0; i < SECRET_LEN; i++) {
		freq_secret[mastermind->secret[i]]++;
		freq_guess[mastermind->guesses[mastermind->turn][i]]++;
		if (mastermind->secret[i] == mastermind->guesses[mastermind->turn][i]) {
			equal++;
		}
	}

	for (int i = 0; i < NUM_COLORS; i++) {
		similar += min(freq_guess[i], freq_secret[i]);
	}

	struct result res = {similar, equal};
	return res;
}

int guess_invalid(int* guesses) {
	for (int i = 0; i < SECRET_LEN; i++) {
		if (guesses[i] < 0 || guesses[i] > 7) {
			printf("Please enter a number between 0 and 7 inclusive!\n");
			return 1;
		}
	}
	return 0;
}

void guesses_get(struct mastermind* mastermind) {
	int* guess = malloc(SECRET_LEN * sizeof(int));
	do {
		scanf("%d %d %d %d %d", guess, guess + 1, guess + 2, guess + 3, guess + 4);
	} while (guess_invalid(guess));
	mastermind->guesses[mastermind->turn] = guess;
}

void mastermind_run(struct mastermind* mastermind) {
	printf("> The secret has been generated, type your guesses as numbers 0-7 as such: ? ? ? ? ? and press enter!\n");
	for (mastermind->turn = 0; mastermind->turn < NUM_GUESSES; mastermind->turn++) {
		guesses_get(mastermind);
		struct result res = verify_guess(mastermind);
		if (res.equal == 5) {
			printf("> You guessed the correct secret code!\n");
			return;
		}
		printf("> [%d] number%s in your guess appear%s in the secret. Out of those, [%d] %s in the correct spot!\n", res.similar, res.similar == 1 ? "" : "s", res.similar == 1 ? "s" : "", res.equal, res.equal == 1 ? "is" : "are");
	}
	printf("> You did not manage to guess the secret :(, the secret was:\n");
	printf("%d %d %d %d %d\n", mastermind->secret[0], mastermind->secret[1], mastermind->secret[2], mastermind->secret[3], mastermind->secret[4]);

}

void mastermind_free(struct mastermind* mastermind) {
	for (int i = 0; i < mastermind->turn; i++) {
		free(mastermind->guesses[i]);
	}
	free(mastermind->guesses);
	free(mastermind->secret);
	free(mastermind);
}