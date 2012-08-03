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

void circuit::restructure(){
	std::list<list_element> update_list=initialize_list();
	
	list<list_element>::iterator list_itr=update_list.begin();
	while(list_itr!=update_list.end()){
		vector<logic_object*> output_elements = list_itr->obj->restructure(list_itr->prev);
		sort_elements(output_elements,update_list);
		list_itr++;
	}	
}

list<list_element> circuit::initialize_list(){
	list<list_element> update_list;
	
	for(int i=0; i<inputs.size(); i++){
		logic_object* temp_obj= inputs[i]->output;
		list_element A;
		A.obj=temp_obj;
		A.prev=NULL;
		A.prop_delay=temp_obj.propogation_delay;
		A.initial_time=0;
		
		list<list_element>::iterator list_itr=update_list.begin();
		if(update_list.size()==0){
			update_list.push_back(A);
		}
		else{
			while(list_itr!=update_list.end()){
				if(list_itr->prop_delay>A.prop_delay)
					update_list.insert(list_itr,A);
				list_itr++;
			}
		}
	}
	return update_list;
}

void circuit::sort_elements(vector<logic_objects> new_objects, logic_object* current_element, list<list_element> & update_list, double time){
	
	for(int i=0; i<new_objects.size(); i++){
		logic_object* temp_obj= new_objects[i]->output;
		list_element A;
		A.obj=temp_obj;
		A.prev=current_element;
		A.prop_delay=temp_obj.propogation_delay;
		A.initial_time=time;
		
		list<list_element>::iterator list_itr=update_list.begin();
		if(update_list.size()==0){
			update_list.push_back(A);
		}
		else{
			while(list_itr!=update_list.end()){
				double temp_time= (list_itr->prop_delay) + (list_itr->initial_time);
				double A_time= A.prop_delay + A.initial_time;
				if(temp_time>A_time)
					update_list.insert(list_itr,A);
				list_itr++;
			}
		}
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
	
