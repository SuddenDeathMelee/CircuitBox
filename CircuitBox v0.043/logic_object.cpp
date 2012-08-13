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
void logic_object::pin_to_output(logic_object* log_obj, int pin_input, int pin_output){
	//Create a new pin and store the pin to which it is connected and the value which it holds
	pin connected_pin;
	connected_pin.input=pin_input;
	connected_pin.obj=log_obj;
	
	pin_map[pin_output].push_back(connected_pin);
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

/*
change_value is used to replace one logic_object* in inputs with another.
*/
void logic_object::change_value(logic_object& new_input, int index){
	inputs[index]=(&new_input);
}

void logic_object::print_value(){
	if(truth_value)
		cout<<"Value of "<<label<<" is: 1"<<endl;
	else
		cout<<"Value of "<<label<<" is: 0"<<endl;
}
