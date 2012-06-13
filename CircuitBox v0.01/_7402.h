#pragma once
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <typeinfo>
#include "Chip.h"
using namespace std;

class _7402: public Chip{
	public:
		//Constructors
		_7402(){
			num_outputs=4;
			
			int i;
			for(i=0; i<8; ++i){
				inputs[i]=NULL;
			}
		}
		_7402(vector<logic_object*> inputs_){
			num_outputs=4;
			
			if(inputs_.size()>8){
				cout<<"Too many inputs, size should be 8"<<endl;
				return;
			}
			int i;
			
			for(i=0; i<8; ++i){
				inputs[i]=NULL;
			}
			
			for(i=0; i<inputs_.size(); ++i){
				inputs[i]=inputs_[i];
			}
		}
		//Logic Functions
		void pin_to_output(logic_object* output, int pin);
		void input_to_pin(logic_object* input, int pin);
		void evaluate();
		void chip_evaluate(Chip* obj, int pin);
		void restructure();
		bool evaluate(int pin);
		bool restructure(int pin);		
		bool outputs_filled();
		vector<bool> value(logic_object* obj);
		bool output_connected(int pin);
		void print_value();
	private:
		logic_object* inputs[8];
		bool outputs[4];
		logic_object* output_objects[4];
	
};