#pragma once
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <typeinfo>
#include "Chip.h"
using namespace std;

class _74151: public Chip{
	public:
		//Constructors
		_74151(){
			num_outputs=2;
			
			int i;
			for(i=0; i<12; ++i){
				inputs[i]=NULL;
			}
		}
		_74151(vector<logic_object*> inputs_){
			num_outputs=2;
			
			if(inputs_.size()>12){
				cout<<"Too many inputs, size should be 12"<<endl;
				return;
			}
			int i;
			
			for(i=0; i<12; ++i){
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
		logic_object* inputs[12];
		bool outputs[2];
		logic_object* output_objects[2];
	
};