#include "mastermind.h"
#include <stdio.h>

int main() {
	struct mastermind* mastermind =	mastermind_init();
	mastermind_run(mastermind);
	mastermind_free(mastermind);
	return 0;
}