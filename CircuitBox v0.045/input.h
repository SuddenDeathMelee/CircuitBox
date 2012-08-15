#pragma once
#include <stdlib.h>
#include "logic_object.h"

class input: public logic_object{
	public:
		//CONSTRUCTORS
		input(){
			num_outputs=1;
		}
		input(string label_); //Give name to input
		input(string label_, bool value_); //Give name and initial truth value to input
		
		//LOGIC FUNCTIONS
		vector<list_element> switch_value(); //Change the value from 0 to 1 or 1 to 0
		bool current_value(){ //find current value of input
			return outputs[0];
		}
};