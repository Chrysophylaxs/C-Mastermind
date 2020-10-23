#ifndef MASTERMIND
#define MASTERMIND

#define SECRET_LEN 5
#define NUM_COLORS 8
#define NUM_GUESSES 10

struct mastermind {
	int* secret;
	int** guesses;
	int turn;
};

struct result {
	int similar;
	int equal;
};

struct mastermind* mastermind_init();
void mastermind_run(struct mastermind* mastermind);
void mastermind_free(struct mastermind* mastermind);

#endif