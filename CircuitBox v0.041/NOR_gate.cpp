#include <stdlib.h>
#include <iostream>
#include "NOR_gate.h"

NOR_gate::NOR_gate() : logic_object(){
	label="NOR gate";
}
NOR_gate::NOR_gate(vector<logic_object*> inputs_) : logic_object(inputs_){
	label="NOR gate";
}
NOR_gate::NOR_gate(vector<logic_object*> inputs_, string label_) : logic_object(inputs_){
	label=label_;
}

void NOR_gate::evaluate(){
	
	truth_value=true;
	
	/*
	NOR_gate evaluate will search for a 1 and returns false
	if it does so. It will return true otherwise.
	*/
	
	for(int i=0; i<inputs.size(); i++){
		if(inputs[i]->is_chip()){
			chip_evaluate((Chip*)inputs[i]);
		}
		else{
			if((inputs[i]->value())){
				truth_value=false;
				break;
			}
		}
	}
}

void NOR_gate::chip_evaluate(Chip* chip){
	vector<bool> pin_values=chip->value(this);
	
	for(int i=0; i<pin_values.size();i++){
		if(pin_values[i]){
			truth_value=false;
			break;
		}			
	}
}

void NOR_gate::restructure(){
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

bool NOR_gate::is_chip(){
	return false;
}
