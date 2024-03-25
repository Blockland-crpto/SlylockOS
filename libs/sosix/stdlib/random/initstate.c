#include <stdlib.h>

char *initstate(unsigned seed, char *state, size_t size) {
	// Calculate the number of integers needed to fill the state array
	size_t num_integers = size / sizeof(int);

	// Initialize the state array
	state[0] = seed & 0xFF;
	state[1] = (seed >> 8) & 0xFF;
	state[2] = (seed >> 16) & 0xFF;
	state[3] = (seed >> 24) & 0xFF;

	for (size_t i = 4; i < num_integers; i++) {
		// Generate pseudo-random values for the state array
		state[i] = (state[i - 4] + state[i - 3] + state[i - 2] + state[i - 1]) & 0xFF;
	}

	return state;
}
