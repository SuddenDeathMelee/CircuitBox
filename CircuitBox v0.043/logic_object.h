#pragma once
#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

struct pin{
	int input;
	logic_object* obj;
};

class logic_object{
	public:
		//CONSTRUCTORS
		logic_object(){
			output=NULL;
		}
		logic_object(vector<logic_object*> inputs_){
			inputs=inputs_;
			output=NULL;
		}
		logic_object(bool value_){
			truth_value=value_;
			output=NULL;
		}
		
		//LOGIC FUNCTIONS
		virtual void evaluate_pin(){}//examines input values to determine output value
		vector<list_element> update(int input_pin, bool input_value, int output_pin, double initial_time);
		void edit_element(vector<list_element>& elements, int input, double init_time);
		void pin_to_output(logic_object* output, int pin_input, int pin_output);
		//void disconnect_pin();
		//double propogation_delay(int pin);
		
		//OTHER
		virtual void print_value(); //print the values of inputs and outputs
		
		//VARIABLES
		string label; //label of logic component
		
	protected:
		vector<bool> inputs;//stores the values at the inputs of the logic_object
		vector<bool> outputs;//stores the values at the outputs of the logic_object
		map<int, list<pin> > pin_map; //stores the what pins on other logic_objects each output pin is connected to
		map<int, map<int, double> > prop_delay_map;
		int num_outputs; //the number of outputs a logic_object has
		double propogation_delay;
};