#ifndef DEBUG_H
# define DEBUG_H

typedef struct { int ROT, RROT, PUSH, SWAP; } t_debug;
t_debug libreta = (t_debug) {
	.ROT = 0,
		.RROT = 0,
		.PUSH = 0,
		.SWAP = 0
};
void reset(void) {
	t_debug libreta = (t_debug) {
		.ROT = 0,
			.RROT = 0,
			.PUSH = 0,
			.SWAP = 0
	};
}

# endif
