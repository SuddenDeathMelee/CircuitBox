#pragma once
#include <stdlib.h>
#include "logic_object.h"
#include "Chip.h"

class OR_gate: public logic_object{
	public:
		//CONSTRUCTORS
		OR_gate();
		OR_gate(vector<logic_object*> inputs_);
		OR_gate(vector<logic_object*> inputs_, string label_);
		//LOGIC FUNCTIONS
		void evaluate();
		void chip_evaluate(Chip* chip);
		void restructure();
		bool is_chip();
};