#pragma once
#include <stdlib.h>
#include <vector>
#include <list>
#include "logic_object.h"
#include "input.h"
#include "Chip.h"
using namespace std;

struct list_element{
	logic_object* obj;
	double initial_time;
	double prop_delay;
	int input_pin;
	int output_pin;
}
class circuit{
	public:
		circuit(){}
		circuit(vector<input> _inputs){
			inputs=_inputs; //Declare initial inputs
		}
		void add_element(logic_object& element);
		void add_element(input* variable);
		
		void connect_elements(logic_object* output_obj, int output_pin, logic_object* input_obj, int input_pin);
		void connect_elements(input* variable, logic_object* input_obj, int input_pin);
		
		void disconnect_elements(logic_object* output_obj, int output_pin, logic_object* input_obj, int input_pin);
		void disconnect_elements(input* variable, logic_object* input_obj, int input_pin);
		
		void remove_element(logic_object* element);
		void remove_element(input* variable);
		
		vector<bool> evaluate();
		void print_value();
		void set_output_labels(vector<string> labels);
	private:
		map<logic_object*, bool> outputs;
		vector<input*> inputs; 
		vector<bool> logic_values;
		vector<string> output_labels;
};
