#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>
#include "logic_object.h"

/*
add_output is used to let the logic_object know what element is reading its
truth value. The output variable is used in restructure() to let the element
know that the truth value has been changed.
*/
void logic_object::add_output(logic_object* new_output){
	output=new_output;
}

/*
add_inputs pushes a new logic_object* onto the inputs vector. The inputs
vector is used in evaluate() to read in the input truth values.
add_inputs is only used in circuit.cpp which makes sure that the same input
isn't added multiple times.
*/
void logic_object::add_inputs(logic_object& new_input){
	inputs.push_back(&new_input);
}

/*
change_value is used to replace one logic_object* in inputs with another.
*/
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
