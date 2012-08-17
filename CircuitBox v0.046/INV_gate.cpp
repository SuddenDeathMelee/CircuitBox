#include <stdlib.h>
#include <iostream>
#include "INV_gate.h"

INV_gate::INV_gate() : logic_object(){
	label="INV gate";
}

INV_gate::INV_gate(vector<logic_object*> inputs_) : logic_object(inputs_){
	label="INV gate";
}

INV_gate::INV_gate(vector<logic_object*> inputs_, string label_) : logic_object(inputs_){
	label=label_;
}

void INV_gate::evaluate(){
	/*
	INV_gate evaluate inverts the value of it's input
	and stores in in value
	*/
	if(inputs[0]->is_chip()){
		
	}
	else{
		truth_value=!(inputs[0]->value());
	}
}

void INV_gate::restructure(){
	bool prev_value=truth_value;
	
	evaluate();
	
	/*
	only call restructure on the next component if the value
	of this component has changed. Returns once output points
	to NULL (i.e. there is no next component)
	*/
	
	if(output && (prev_value!=value())){
		output->restructure();
	}
}

bool INV_gate::is_chip(){
	return false;
}