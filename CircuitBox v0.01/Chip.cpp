#include <list>
#include "Chip.h"
using namespace std;

void Chip::evaluate(){
	for(int i=0; i<4; i++)
		evaluate_pin(i);
}

bool Chip::is_chip(){
	return true;
}