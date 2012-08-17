#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>
#include "logic_object.h"

/*
pin_to_output stores a logic_object* in output_objects; a pin from this chip is connected to
another logic_object. This function ensures that a new pin object is stored in 
the pins data structure so that this object can know which elements are connected to which
pins
*/
void logic_object::pin_to_input(logic_object* log_obj, int pin_input, int pin_output){
	//Create a new pin and store the pin to which it is connected and the value which it holds
	pin connected_pin;
	connected_pin.input=pin_input;
	connected_pin.obj=log_obj;
	
	list<pin> pins=pin_map[pin_output];
	list<pin>::iterator pins_itr=pins.begin();
	while(pins_itr!=pins.end()){
		if(pins_itr->obj==log_obj){
			if(pins_itr->input==pin_input){
				return;
			}
		}
		pins_itr++;
	}
	pin_map[pin_output].push_back(connected_pin);
	connected_outputs++;
}

vector<list_element> logic_object::update(int input_pin, bool input_value, int output_pin, double intial_time){
	inputs[input_pin]=input_value;
	evaluate_pin(output_pin);
	
	list<pin> pins=pin_map[output_pin];
	list<pin>::iterator pins_itr=pins.begin();
	
	vector<list_element> temp;
	while(pins_itr!=pins.end()){
		pins_itr->obj->edit_element(temp, pins_itr->input, initial_time);
		pins_itr++;
	}
	return temp;
}

void logic_object::edit_element(vector<list_element>& elements, int input, double init_time){
	int input_pin=element.input;
	map<int, double> pin_to_prop_delay= prop_delay_map[input];
	for(int i=0; i<num_outputs; i++){
		list_element temp_element;
		if(pin_to_prop_delay[i]==0){
			continue;
		}
		else{
			temp_element.obj=this;
			temp_element.input_pin=input;
			temp_element.output_pin=i;
			temp_element.initial_time=initial_time;
			temp_element.prop_delay=pin_to_prop_delay[i];
		}
		elements.push_back(temp_element);
	}
}

void logic_object::disconnect_pins(int output_pin, logic_object* input_obj, int input_pin){
	list<pin>::iterator list itr= (pin_map[output_pin]).begin();
	
	int input_count=0;
	while(list_itr!= (pin_map[output_pin].end()) ){
		input_count++;
		if(list_itr->obj==input_obj){
			if(list_itr->input==input_pin){
				list_itr=(pin_map[output_pin]).erase(list_itr);
				continue;
			}
		}
		list_itr++;
	}
	if(input_count==1){
		input_obj->remove_input(this);
	}
}

void logic_object::disconnect_element(logic_object* input_obj){
	for(int i=0; i<num_outputs; i++){
		list<pin>::iterator list_itr= (pin_map[i]).begin();
		while(list_itr!= (pin_map[i]).end() ){
			if(list_itr==input_obj){
				list_itr=(pin_map[i]).erase(list_itr);
				continue;
			}
			list_itr++;
		}
	}
}

void logic_object::remove_input(logic_object* obj){
	list<logic_object*>::iterator list_itr=object_inputs.begin();
	
	while(list_itr!=object_inputs.end()){
		if(list_itr==obj){
			object_inputs.erase(list_itr);
			break;
		}
		list_itr++;
	}
}

void logic_object::remove_all_inputs(){
	list<logic_object*>::iterator list_itr=object_inputs.begin();
	
	while(list_itr!=object_inputs.end()){
		list_itr->disconnect_element(this);
	}
}

void logic_object::print_value(){
	if(truth_value)
		cout<<"Value of "<<label<<" is: 1"<<endl;
	else
		cout<<"Value of "<<label<<" is: 0"<<endl;
}
