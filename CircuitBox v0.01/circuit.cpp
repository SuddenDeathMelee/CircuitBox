#include <vector>
#include <list>
#include <typeinfo>
#include "logic_object.h"
#include "circuit.h"

using namespace std;

void circuit::add_element(logic_object& element, vector<input>& variables){
	for(int i=0; i<variables.size(); ++i){
		variables[i].add_output(&element);
		element.add_inputs(variables[i]);
	}
	element.evaluate();//update truth value of element
	
	outputs.push_back(&element);//component is considered an output of the circuit at this point
}

void circuit::add_element(Chip& chip, input& input, int pin){
	chip.input_to_pin(&input, pin);
	chip.evaluate();
	
	if(!chip.outputs_filled() && !is_output(&chip)){
		outputs.push_back(&chip);
	}
	if(chip.outputs_filled()){
		remove_chip(&chip);
	}
}

void circuit::add_element(logic_object& element, vector<logic_object*> elements){
	for(int i=0; i<elements.size(); ++i){
		list<logic_object*>::iterator output_itr;
		for(output_itr=outputs.begin(); output_itr!=outputs.end(); ){
			if((elements[i])==*output_itr){ //if one of the elements was an output of the circuit, it no longer is
				output_itr=outputs.erase(output_itr); //remove as circuit output
			}
			else
				output_itr++;
		}
	}
	for(int j=0; j<elements.size(); ++j){
		(*elements[j]).add_output(&element);
		element.add_inputs(*(elements[j]));//Add inputs to new component
	}
	element.evaluate();//update truth value of elements
	outputs.push_back(&element);
}

void circuit::add_element(logic_object& element, vector<logic_object*> elements, vector<input>& variables){
	for(int i=0; i<variables.size(); ++i){
		variables[i].add_output(&element);
		element.add_inputs(variables[i]); //Add variables as inputs of element-
	}
	for(int i=0; i<elements.size(); ++i){
		list<logic_object*>::iterator output_itr;
		for(output_itr=outputs.begin(); output_itr!=outputs.end(); ){
			if((elements[i])==*output_itr){ //if one of the elements was an output of the circuit, it no longer is
				output_itr=outputs.erase(output_itr); //remove as circuit output
			}
			else
				output_itr++;
		}
	}
	for(int j=0; j<elements.size(); ++j){
		(*elements[j]).add_output(&element);
		element.add_inputs(*(elements[j])); //Add inputs to new component
	}
	element.evaluate();//update truth value of elements
	outputs.push_back(&element);
}

bool circuit::is_output(logic_object* obj){
	list<logic_object*>::iterator output_itr;
	for(output_itr=outputs.begin(); output_itr!=outputs.end(); ){
		if(obj==*output_itr){ //if one of the elements was an output of the circuit, it no longer is
			return true;
		}
		else
			output_itr++;
	}
	return false;
}

void circuit::remove_chip(logic_object* obj){
	list<logic_object*>::iterator output_itr;
	for(output_itr=outputs.begin(); output_itr!=outputs.end(); ){
		if(obj==*output_itr){ //if one of the elements was an output of the circuit, it no longer is
			output_itr=outputs.erase(output_itr); //remove as circuit output
		}
		else
			output_itr++;
	}	
}

vector<bool> circuit::evaluate(){
	vector<bool> new_values;
	list<logic_object*>::iterator itr;
	
	for(itr=outputs.begin(); itr!=outputs.end();++itr){
		if((*itr)->is_chip())
			evaluate_chip(new_values, (Chip*)(*itr));
		else{
			(*itr)->evaluate();
			new_values.push_back((*itr)->value());
		}
	}
	logic_values=new_values;
	return new_values;
}

void circuit::evaluate_chip(vector<bool>& values, Chip* chip){
	for(int i=0; i<chip->num_outputs; i++){
		if(chip->output_connected(i)){
			values.push_back(chip->evaluate_pin(i));
		}
	}
}
void circuit::print_value(){
	for(int i=0; i<logic_values.size();++i){
		if(logic_values[i])
			cout<<"The truth value of "<<output_labels[i]<<" is "<<1<<endl;
		else
			cout<<"The truth value of "<<output_labels[i]<<" is "<<0<<endl;
	}
}
void circuit::set_output_labels(vector<string> labels){
	output_labels=labels;
}
	
