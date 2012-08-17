#include "input.h"

input::input(string label_) : logic_object(){
	num_outputs=1;
	label=label_;
}
input::input(string label_, bool value_) :logic_object(value_){
	num_outputs=1;
	label=label_;
	outputs[0]=value_;
}
void input::switch_value(){
	outputs[0]=!(outputs[0]);
	
	list<pin> pins=pin_map[output_pin];
	list<pin>::iterator pins_itr=pins.begin();
	
	vector<list_element> temp;
	while(pins_itr!=pins.end()){
		pins_itr->obj->edit_element(temp, pins_itr->input, initial_time);
		pins_itr++;
	}
	return temp;
}
