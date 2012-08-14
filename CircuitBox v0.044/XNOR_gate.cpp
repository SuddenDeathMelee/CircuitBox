#include <stdlib.h>
#include <iostream>
#include "XNOR_gate.h"

XNOR_gate::XNOR_gate() : logic_object(){
	label="XNOR gate";
}
XNOR_gate::XNOR_gate(vector<logic_object*> inputs_) : logic_object(inputs_){
	label="XNOR gate";
}
XNOR_gate::XNOR_gate(vector<logic_object*> inputs_, string label_) : logic_object(inputs_){
	label=label_;
}
void XNOR_gate::evaluate(){
	
	truth_value=false;
	
	/*
	XNOR_gate evaluate will search for all inputs whose value is
	true. If it finds more than one, it returns true. If there are
	no inputs whose value is true, the function also returns true.
	*/
	
	int num_true_values=0;
	for(int i=0; i<inputs.size(); i++){
		if(inputs[i]->is_chip()){
			chip_evaluate((Chip*)inputs[i]);
		}
		else{
			if((inputs[i]->value())){
				num_true_values++;
				if(num_true_values>1){
					truth_value=false;
					break;
				}
			}
		}
	}
	if(num_true_values==0){
		truth_value=true;
	}
}

void XNOR_gate::chip_evaluate(Chip* chip){
	vector<bool> pin_values=chip->value(this);
	
	int num_true_values=0;
	for(int i=0; i<pin_values.size();i++){
		if(pin_values[i]){
			num_true_values++;
			if(num_true_values>1){
				truth_value=false;
				break;
			}
		}			
	}
	if(num_true_values==0){
		truth_value=true;
	}
}

void XNOR_gate::restructure(){
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

bool XNOR_gate::is_chip(){
	return false;
}
