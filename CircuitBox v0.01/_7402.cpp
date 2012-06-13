#include "_7402.h"

void _7402::pin_to_output(logic_object* output, int pin){
	output_objects[pin]=output;
	pins[output].push_back(pin);
}

void _7402::input_to_pin(logic_object* input, int pin){
	inputs[pin]=input;
}

void _7402::evaluate(){
	for(int i=0; i<4; i++)
		evaluate(i);
}

void _7402::restructure(){
	vector<bool> output_changed;
	
	for(int i=0; i<4; ++i)
		output_changed.push_back(restructure(i));
	
	for(int i=0; i<4; i++){
		if(output_changed[i])
			output_objects[i]->restructure();
	}
}

bool _7402::evaluate(int pin){
	outputs[pin]=true;
	logic_object* pin_1= inputs[pin+pin];
	logic_object* pin_2= inputs[pin+pin+1];
	if(pin_1 && pin_1->is_chip()){
		chip_evaluate((Chip*)pin_1, pin);
	}
	if(pin_2 && pin_2->is_chip()){
		chip_evaluate((Chip*)pin_2, pin);
	}
	if((pin_1 && pin_2) && (pin_1->value() || pin_2->value()))
		outputs[pin]=false;

	return outputs[pin];
}

bool _7402::restructure(int pin){
	bool prev_value=outputs[pin];
	evaluate(pin);
	
	if(output_objects[pin] && prev_value!=outputs[pin])
		return true;
	return false;
}

void _7402::chip_evaluate(Chip* chip, int pin){
	vector<bool> pin_values=chip->value(this);
	
	for(int i=0; i<pin_values.size();i++){
		if(pin_values[i]){
			outputs[pin]=false;
			break;
		}			
	}
}

vector<bool> _7402::value(logic_object* obj){
	vector<bool> pin_values;
	list<int> pin_numbers= pins[obj];
	list<int>::iterator pin_itr= pin_numbers.begin();
	
	while(pin_itr!=pin_numbers.end()){
		int pin=*pin_itr;
		pin_values.push_back(outputs[pin]);
		pin_itr++;
	}
	return pin_values;
}

bool _7402::outputs_filled(){
	if(pins.size()==num_outputs)
		return true;
	return false;
}

bool _7402::output_connected(int pin){
	if(output_objects[pin])
		return true;
	else
		return false;
}

void _7402::print_value(){
	for(int i=0; i<4; ++i){
		cout<<"Value of pin "<<i<<" is: "<<outputs[i]<<endl;
	}
}