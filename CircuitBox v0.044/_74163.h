#pragma once
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <typeinfo>
#include "Chip.h"
using namespace std;

class _74163: public Chip{
	public:
		//Constructors
		_74163(){
			num_outputs=5;
			
			int i;
			for(i=0; i<9; ++i){
				inputs[i]=NULL;
			}
		}
		_74163(vector<logic_object*> inputs_){
			num_outputs=5;
			
			if(inputs_.size()>9){
				cout<<"Too many inputs, size should be 9"<<endl;
				return;
			}
			int i;
			
			for(i=0; i<9; ++i){
				inputs[i]=NULL;
			}
			
			for(i=0; i<inputs_.size(); ++i){
				inputs[i]=inputs_[i];
			}
		}
		//Logic Functions
		void pin_to_output(logic_object* output, int pin_input, int pin_output);
		void input_to_pin(logic_object* input, int pin);
		void restructure();
		void evaluate();
		bool evaluate_pin(int pin);
		bool restructure_pin(int pin);
		vector<bool> value(logic_object* obj);
		bool value(logic_object* obj, int pin_);
		bool outputs_filled();	
		bool output_connected(int pin);	
		void print_value();
	private:
		logic_object* inputs[9];
		bool outputs[5];
		logic_object* output_objects[5];
		double prop_delay;
		double clock_prop_delay;
};