///////////////////////////////////
// basic_malloc.c
// basic test for tj_mallc
// Tom Brady is the GOAT
//   - Jielun Tan, 02/2019
///////////////////////////////////

extern void exit();
#include "tj_malloc.h"
#include <stdio.h>

typedef struct {
	int brady;
	uint16_t rings;
	bool goat;
	int gronk;
	int edelman;
}example_t;

int main() {
	example_t* pats = (example_t*)tj_malloc(sizeof(example_t));
	//printf("pts is %i\n", pats);
	//printf("what\n");
	pats->brady = 12; // as of 02/2019
	//printf("huh\n");
	pats->rings = 6;
	pats->goat = 1; // hands down the goat
	pats->gronk = 87; // tide pods
	pats->edelman = 11; // the ironman, superbowl 53 mvp
	//printf("the\n");
	//printf("%i\n", pats->edelman);
	example_t* another = (example_t*)tj_malloc(sizeof(example_t));
	//printf("pts is %i\n", another);
	tj_free(pats);
	return 0;
}
