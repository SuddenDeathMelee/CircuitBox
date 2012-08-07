#include "input.h"

input::input(string label_) : logic_object(){
	label=label_;
}
input::input(string label_, bool value_) :logic_object(value_){
	label=label_;
	truth_value=value_;
}
void input::switch_value(){
	truth_value=!(truth_value);
	output->restructure();
}
bool input::is_chip(){
	return false;
}
