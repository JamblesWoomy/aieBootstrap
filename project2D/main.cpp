#include "Application2D.h"
#include <vector.h>
#include <matrix.h>

int main() {
	
	// allocation
	auto app = new Application2D();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}