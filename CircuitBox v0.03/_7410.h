#pragma once
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <typeinfo>
#include "Chip.h"
using namespace std;

class _7410: public Chip{
	public:
		//Constructors
		_7410(){
			num_outputs=3;
			
			int i;
			for(i=0; i<6; ++i){
				inputs[i]=NULL;
			}
		}
		_7410(vector<logic_object*> inputs_){
			num_outputs=3;
			
			if(inputs_.size()>6){
				cout<<"Too many inputs, size should be 8"<<e6dl;
				return;
			}
			int i;
			
			for(i=0; i<6; ++i){
				inputs[i]=NULL;
			}
			
			for(i=0; i<inputs_.size(); ++i){
				inputs[i]=inputs_[i];
			}
		}
		//Logic Functions
		void pin_to_output(logic_object* output, int pin_input, int pin_output);
		void input_to_pin(logic_object* input, int pin);
		void evaluate();
		void restructure();
		bool evaluate_pin(int pin);
		bool restructure_pin(int pin);		
		bool outputs_filled();
		vector<bool> value(logic_object* obj);
		bool value(logic_object* obj, int pin_);
		bool output_connected(int pin);
		void print_value();
	private:
		logic_object* inputs[6];
		bool outputs[3];
		logic_object* output_objects[3];
	
};