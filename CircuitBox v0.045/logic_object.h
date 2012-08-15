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
			connected_outputs=0;
		}		
		//LOGIC FUNCTIONS
		virtual void evaluate_pin(){}//examines input values to determine output value
		vector<list_element> update(int input_pin, bool input_value, int output_pin, double initial_time);
		void edit_element(vector<list_element>& elements, int input, double init_time);
		void pin_to_input(logic_object* output, int pin_input, int pin_output);
		void disconnect_pins(int output_pin, logic_object* input_obj, int input_pin);
		void disconnect_element(logic_object* obj);
		void remove_input(logic_object* obj);
		void remove_all_inputs();
		//connect_input();
		//void disconnect_pin();
		//double propogation_delay(int pin);
		
		//OTHER
		virtual void print_value(); //print the values of inputs and outputs
		
		//VARIABLES
		string label; //label of logic component
		
	protected:
		vector<bool> inputs;//stores the values at the inputs of the logic_object
		vector<bool> outputs;//stores the values at the outputs of the logic_object
		list<logic_object*> object_inputs;
		map<int, list<pin> > pin_map; //stores the what pins on other logic_objects each output pin is connected to
		map<int, map<int, double> > prop_delay_map;
		int connected_outputs;
		int num_outputs; //the number of outputs a logic_object has
		double propogation_delay;
};