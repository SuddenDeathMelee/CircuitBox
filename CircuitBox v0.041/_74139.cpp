#include "_74139.h"

/*
pin_to_output stores a logic_object* in output_objects; a pin from this chip is connected to
another logic_object. This function ensures that a new pin object is stored in 
the pins data structure so that this object can know which elements are connected to which pins
*/
void _74139::pin_to_output(logic_object* output, int pin_input, int pin_output){
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
void _74139::input_to_pin(logic_object* input, int pin){
	inputs[pin]=input;
}

/*
Calculates the values in each output pin of the chip
*/
void _74139::evaluate(){
	
	for(int i=0;i<8;i++){
		outputs[i]=1;
	}
	
	if(!g1_enabled()){
		break;
	}
	
	else{
		int pin=0;
		for(int i=1;i<3;++i){
			if(inputs[i]->is_chip()){
				pin+=(inputs[i]->value(this,i))*i;
			}
			else{
				pin+=(inputs[i]->value())*i;
			}
		}
		outputs[pin]=0;
	}
	
	if(!g2_enabled()){
		break;
	}
	else{
		int pin=0;
		for(int i=4;i<6;++i){
			if(inputs[i]->is_chip()){
				pin+=(inputs[i]->value(this,i))*(i-3);
			}
			else{
				pin+=(inputs[i]->value())*(i-3);
			}
		}
		outputs[pin]=0;
	}	
}

/*
The 74x139 has two enable inputs: G1 and G2, represented by the 0th and 1st elements in the inputs
array, respectively.
*/
bool _74139::g1_enabled(){
	if(inputs[0]){
		if(inputs[0]->is_chip()){
			if(!(inputs[0]->value(this, 0)))
				return false;
			else
				return true;
		}
		else
			if(!(inputs[0]->value()))
				return false;
			else
				return true;
	}	
	else
		return false;
}

bool _74139::g2_enabled(){
	if(inputs[3]){
		if(inputs[3]->is_chip()){
			if(!(inputs[3]->value(this, 3)))
				return false;
			else return true;
		}
		else
			if(!(inputs[3]->value()))
				return false;
			else
				return true;
	}
	else
		return false;
}

/*
The restructure function updates each output pin's truth value. If any output's value has changed,
then the logic_object to which they are connected is updated.
*/
void _74139::restructure(){
	vector<bool> prev_output;
	
	
	for(int i=0; i<8; ++i)
		prev_output.push_back(outputs[i]);
	
	evaluate();
	
	for(int i=0; i<8; i++){
		if(prev_output!=outputs[i])
			output_objects[i]->restructure();
	}
}

/*
evaluate_pin determines and updates the value of a pin on the chip.
*/
bool _74139::evaluate_pin(int pin){
	evaluate();
	return outputs[pin];
}

/*
restructure_pin only updates the value of a single pin. If its value changes, then the logic_object
to which it is connected will be updated.
*/
bool _74139::restructure_pin(int pin){
	bool prev_output=outputs[pin];
	evaluate();
	if(prev_output!=outputs[pin])
		output_objects[pin]->restructure();
}

/*
The value(logic_object* obj) function returns a vector containing containing all of the
boolean values from the all the pins in this chip that are connected to obj.
*/
vector<bool> _74139::value(logic_object* obj){
	vector<bool>x pin_values;
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
bool _74139::value(logic_object* obj, int pin_){
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
bool _74139::outputs_filled(){
	if(pins.size()==num_outputs)
		return true;
	return false;
}

/*
output_connected returns true if the output number pin is connected
to a logic_object.
*/
bool _7139::output_connected(int pin){
	if(output_objects[pin])
		return true;
	else
		return false;
}

/*
print_value prints out the value of each output pin.
*/
void _7139::print_value(){
	for(int i=0; i<6; ++i){
		cout<<"Value of pin "<<i<<" is: "<<outputs[i]<<endl;
	}
}