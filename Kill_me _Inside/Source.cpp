#include<iostream>
#include"Edit.h"
int main() {
	Game g;
	Editor e(&g);
	e.map();
	g.main_loop();
	return 0;
}