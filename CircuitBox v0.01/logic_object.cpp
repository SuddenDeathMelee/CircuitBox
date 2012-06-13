#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>
#include "logic_object.h"

void logic_object::add_output(logic_object* new_output){
	output=new_output;
}

void logic_object::add_inputs(logic_object& new_input){
	inputs.push_back(&new_input);
}

void logic_object::change_value(logic_object& new_input, int index){
	inputs[index]=(&new_input);
}

void logic_object::print_value(){
	if(truth_value)
		cout<<"Value of "<<label<< " is: 1"<<endl;
	else
		cout<<"Value of "<<label<<" is: 0"<<endl;
}

bool logic_object::value(){
	return truth_value;
}
	
void logic_object::set_dimensions_location(int x, int y, unsigned int w, unsigned int h){
	location_x=x;
	location_y=y;
	width=w;
	height=h;
}

bool logic_object::in_range(int min_x, int max_x, int min_y, int max_y){
	if(((location_x>min_x && location_x<max_x) || ((location_x+width)>min_x && (location_x+width)<min_x)) &&
		((location_y>min_y && location_y<max_y) || ((location_y+height)>min_y && (location_y+height)<min_y))){
		return true;
	}
	else
		return false;
}
