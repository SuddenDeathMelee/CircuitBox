#include <stdlib.h>
#include <iostream>
#include "NAND_gate.h"

NAND_gate::NAND_gate() : logic_object(){
	label="NAND gate";
}
NAND_gate::NAND_gate(vector<logic_object*> inputs_) : logic_object(inputs_){
	label="NAND gate";
}
NAND_gate::NAND_gate(vector<logic_object*> inputs_, string label_) : logic_object(inputs_){
	label=label_;
}

void NAND_gate::evaluate(){
	
	truth_value=false;
	
	/*
	AND_gate evaluate will search for a 0 and returns true
	if it does so. It will return false otherwise.
	*/
	
	for(int i=0; i<inputs.size(); i++){
		if(inputs[i]->is_chip()){
			chip_evaluate((Chip*)inputs[i]);
		}
		else{
			if(!(inputs[i]->value())){
				truth_value=true;
				break;
			}
		}
	}
}

void NAND_gate::chip_evaluate(Chip* chip){
	vector<bool> pin_values=chip->value(this);
	
	for(int i=0; i<pin_values.size();i++){
		if(!pin_values[i]){
			truth_value=true;
			break;
		}			
	}
}

void NAND_gate::restructure(){
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

bool NAND_gate::is_chip(){
	return false;
}
