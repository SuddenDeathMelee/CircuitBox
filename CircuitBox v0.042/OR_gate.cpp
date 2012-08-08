#include <stdlib.h>
#include <iostream>
#include "OR_gate.h"

OR_gate::OR_gate() : logic_object(){
	label="OR gate";
}
OR_gate::OR_gate(vector<logic_object*> inputs_) : logic_object(inputs_){
	label="OR gate";
}
OR_gate::OR_gate(vector<logic_object*> inputs_, string label_) : logic_object(inputs_){
	label=label_;
}

void OR_gate::evaluate(){
	
	truth_value=false;
	
	/*
	OR_gate searches through its inputs until it finds a 1,
	then returns true. Otherwise, it returns false.
	*/
	
	for(int i=0; i<inputs.size(); i++){
		if(inputs[i]->is_chip()){
			chip_evaluate((Chip*)inputs[i]);
		}
		else{
			if((inputs[i]->value())){
				truth_value=true;
				break;
			}
		}
	}
}

void OR_gate::chip_evaluate(Chip* chip){
	vector<bool> pin_values=chip->value(this);
	
	for(int i=0; i<pin_values.size();i++){
		if(pin_values[i]){
			truth_value=true;
			break;
		}			
	}
}

void OR_gate::restructure(){
	bool prev_value=truth_value;
	
	evaluate();

	/*
	only call restructure on the next component if the value
	of this component has changed. Returns once output points
	to NULL (i.e. there is no next component)
	*/
	
	if(output && (prev_value!=truth_value)){
		output->restructure();
	}
}

bool OR_gate::is_chip(){
	return false;
}
