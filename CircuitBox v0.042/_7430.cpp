#include "_7430.h"

/*
pin_to_output stores a logic_object* in output_objects; a pin from this chip is connected to
another logic_object. This function ensures that a new pin object is stored in 
the pins data structure so that this object can know which elements are connected to which
pins
*/
void _7430::pin_to_output(logic_object* output, int pin_input, int pin_output){
	output_objects[pin]=output;
	pin connected_pin;
	connected_pin.output_pin=pin_output;
	connected_pin.value=output[pin_input];
	pins[output].push_back(connected_pin);
}

/*
input_to_pin stores a logic_object* in the inputs array so this class
can read its input values
*/
void _7430::input_to_pin(logic_object* input, int pin){
	inputs[pin]=input;
}

/*
Calculates the values in each output pin of the chip
*/
void _7430::evaluate(){
	evaluate_pin(0);
}

/*
The restructure function updates each output pin's truth value. If any output's value has changed,
then the logic_object to which they are connected is updated.
*/
void _7430::restructure(){
	vector<bool> output_changed;
	
	for(int i=0; i<1; ++i)
		output_changed.push_back(restructure_pin(i));
	
	for(int i=0; i<1; i++){
		if(output_changed[i])
			output_objects[i]->restructure();
	}
}

/*
evaluate_pin determines and updates the value of a pin on the chip.
*/
bool _7430::evaluate_pin(int pin){
	outputs[pin]=false;

	for(int i=0; i<8; i++){
		if(inputs[i]!=NULL){
			if(inputs[i]->is_chip()){
				bool value=inputs[i]->value(this, 3*pin+i);
				if(!value){
					outputs[pin]=true;
					return outputs[pin];
				}
			}
			else{
				bool value=inputs[i]->value();
				if(!value){
					outputs[pin]=true;
					return outputs[pin];
				}
			}	
		}			
	}
	return outputs[pin];
}

/*
restructure_pin only updates the value of a single pin. If its value changes, then the logic_object
to which it is connected will be updated.
*/
bool _7430::restructure_pin(int pin){
	bool prev_value=outputs[pin];
	evaluate_pin(pin);
	
	if(output_objects[pin] && prev_value!=outputs[pin])
		return true;
	return false;
}

/*
The value(logic_object* obj) function returns a vector containing containing all of the
boolean values from the all the pins in this chip that are connected to obj.
*/
vector<bool> _7430::value(logic_object* obj){
	vector<bool> pin_values;
	list<pin> pin_numbers= pins[obj];
	list<pin>::iterator pin_itr= pin_numbers.begin();
	
	while(pin_itr!=pin_numbers.end()){
		int pin_value=pin_itr->value;
		pin_values.push_back(outputs[pin_value]);
		pin_itr++;
	}
	return pin_values;
}

/*
The value(logic_object* obj, int pin_) function returns the boolean value of the pin
that is connected to pin_ of obj. This is done by finding the list of pins that are connected
to obj, and then searching through that list to find the pin that is connected to pin_.
*/ 
bool _7430::value(logic_object* obj, int pin_){
	int value;
	list<pin> pin_numbers= pins[obj];
	list<pin>::iterator pin_itr= pin_numbers.begin();
	
	while(pin_itr!=pin_numbers.end()){
		if(pin_itr->output_pin==pin_){
			return pin_itr->value;
		}
	}
	return 0;
}

/*
outputs_filled returns true if every output pin of the chip is connected to a logic_object, and it
returns false otherwise.
*/
bool _7430::outputs_filled(){
	if(pins.size()==num_outputs)
		return true;
	return false;
}

/*
output_connected returns true if the output number pin is connected
to a logic_object.
*/
bool _7430::output_connected(int pin){
	if(output_objects[pin])
		return true;
	else
		return false;
}

/*
print_value prints out the value of each output pin.
*/
void _7430::print_value(){
	for(int i=0; i<1; ++i){
		cout<<"Value of pin "<<i<<" is: "<<outputs[i]<<endl;
	}
}