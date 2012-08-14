#pragma once
#include <stdlib.h>
#include "logic_object.h"
#include "Chip.h"

using namespace std;

class AND_gate: public logic_object{
	public:
		//CONSTRUCTORS
		AND_gate();
		AND_gate(vector<logic_object*> inputs_);
		AND_gate(vector<logic_object*> inputs_, string label_);
		//LOGIC FUNCTIONS
		void evaluate();
		void chip_evaluate(Chip* chip);
		void restructure();
		bool is_chip();
};
