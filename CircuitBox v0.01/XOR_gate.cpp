#include <stdlib.h>
#include <iostream>
#include "XOR_gate.h"

XOR_gate::XOR_gate() : logic_object(){
	label="XOR gate";
}
XOR_gate::XOR_gate(vector<logic_object*> inputs_) : logic_object(inputs_){
	label="XOR gate";
}
XOR_gate::XOR_gate(vector<logic_object*> inputs_, string label_) : logic_object(inputs_){
	label=label_;
}

void XOR_gate::evaluate(){
	truth_value=false;
	
	/*
	XOR_gate evaluate will count how many inputs
	ave a value of 1. It will return true only if
	there is 1 input whose value is true and false
	otherwise
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
	if(num_true_values==1){
		truth_value=true;
	}
}

void XOR_gate::chip_evaluate(Chip* chip){
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
	if(num_true_values==1){
		truth_value=true;
	}
}

void XOR_gate::restructure(){
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

bool XOR_gate::is_chip(){
	return false;
}