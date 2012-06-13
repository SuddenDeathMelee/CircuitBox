#pragma once
#include <stdlib.h>
#include <vector>
#include <list>
#include "logic_object.h"
#include "input.h"
#include "Chip.h"
using namespace std;

class circuit{
	public:
		circuit(vector<input> _inputs){
			inputs=_inputs; //Declare initial inputs
		}
		void add_element(logic_object& element, vector<input>& variables);//Add stand-alone element- not connected to any other components
		void add_element(Chip& chip, input& input, int pin);
		void add_element(Chip& chip, logic_object* obj, int pin);
		void add_element(logic_object& element, vector<logic_object*> elements);//Add an element whose inputs are the outputs of other elements
		void add_element(logic_object& element, vector<logic_object*> elements, vector<input>& variables);//Add an element whose inputs are a combination of components and variables
		vector<bool> evaluate();
		bool is_output(logic_object* obj);
		void remove_chip(logic_object* obj);
		void evaluate_chip(vector<bool>& values, Chip* chip);
		void print_value();
		void set_output_labels(vector<string> labels);
	private:
		vector<input> inputs; 
		list<logic_object*> outputs;
		vector<bool> logic_values;
		vector<string> output_labels;
};