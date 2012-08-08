#include <stdlib.h>
#include <iostream>
#include "AND_gate.h"

AND_gate::AND_gate() : logic_object(){
	label="AND gate";
}

AND_gate::AND_gate(vector<logic_object*> inputs_) : logic_object(inputs_){
	label="AND gate";
}

AND_gate::AND_gate(vector<logic_object*> inputs_, string label_) : logic_object(inputs_){
	label=label_;
}

/*
The evaluate function updates the truth value of the logic_object by checking
the current inputs to itself
*/
void AND_gate::evaluate(){
	
	truth_value=true;
	
	/*
	AND_gate evaluate will search for a 0 and returns false
	if it does so. It will return true otherwise.
	*/
	
	for(int i=0; i<inputs.size(); i++){
		if(inputs[i]->is_chip()){
			chip_evaluate((Chip*)inputs[i]);
			/*
			This if statement is here to ensure that if the chip does change the truth
			value to false, the function will exit.
			*/
			if(!truth_value)
				break;
		}
		else{
			if(!(inputs[i]->value())){
				truth_value=false;
				break;
			}
		}
	}
}

/*
The chip_evaluate function exists so that the vector of booleans that the chip class's
value() function can be examined. A vector of boolean values is returned because
the And gate may be connected to multiple outputs of a chip.
*/
void AND_gate::chip_evaluate(Chip* chip){
	vector<bool> pin_values=chip->value(this);
	
	for(int i=0; i<pin_values.size();i++){
		if(!pin_values[i]){
			truth_value=false;
			break;
		}			
	}
}


void AND_gate::restructure(){
	bool prev_value=truth_value;
	
	evaluate();
	
	/*
	only call restructure on the next component if the value
	of this component has changed. Returns once output points
	to NULL (i.e. there is no next component)
	*/
	
	if(output && (prev_value!=truth_value))
		output->restructure();
}

bool AND_gate::is_chip(){
	return false;
}
