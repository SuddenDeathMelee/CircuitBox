#include <vector>
#include <list>
#include <typeinfo>
#include "logic_object.h"
#include "circuit.h"

using namespace std;

void circuit::add_element(logic_object* element){
	outputs[element]=true;
}

void circuit::add_element(input* variable){
	inputs.push_back(variable);
}

void circuit::connect_elements(logic_object* output_obj, int output_pin, logic_object* input_obj, int input_pin){
	output_obj->pin_to_input(input_obj, output_pin, input_pin);
	if(output_obj->outputs_filled()){
		outputs[output_obj]=false;
	}
}

void circuit::connect_elements(input* variable, logic_object* input_obj, int input_pin){
	variable->pin_to_input(input_obj, 0, input_pin);
}

void circuit::disconnect_elements(logic_object* output_obj, int output_pin, logic_object* input_obj, int input_pin){
	output_obj->disconnect_pins(output_pin, input_obj, input_pin);
	
	if(output_obj->outputs_filled()){
		outputs[output_obj]=false;
	}
	else{
		outputs[output_obj]=true;
	}
}

void circuit::disconnect_elements(input* variable, logic_object* input_obj, int input_pin){
	output_obj->disconnect_pins(0, input_obj, input_pin);
}

void circuit::remove_element(logic_object* element){
	element->remove_all_inputs();
}

void circuit::remove_element(input* variable){
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
	
