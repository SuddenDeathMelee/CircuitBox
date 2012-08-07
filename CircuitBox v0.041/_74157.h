#pragma once
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <typeinfo>
#include "Chip.h"
using namespace std;

class _74157: public Chip{
	public:
		//Constructors
		_74157(){
			num_outputs=4;
			
			int i;
			for(i=0; i<10; ++i){
				inputs[i]=NULL;
			}
		}
		_74151(vector<logic_object*> inputs_){
			num_outputs=4;
			
			if(inputs_.size()>10){
				cout<<"Too many inputs, size should be 10"<<endl;
				return;
			}
			int i;
			
			for(i=0; i<10; ++i){
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
		logic_object* inputs[10];
		bool outputs[4];
		logic_object* output_objects[4];
	
};