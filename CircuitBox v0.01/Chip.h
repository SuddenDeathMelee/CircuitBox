#pragma once
#include <list>
#include <map>
#include "logic_object.h"
using namespace std;

class Chip : public logic_object{
	public:
	//Constructors
		Chip(){}
		Chip(vector<logic_object*> inputs_);
		Chip(vector<logic_object*> inputs_, string label_);
		//Logic Functions
		void evaluate();
		virtual bool evaluate_pin(int pin){}
		virtual bool restructure_pin(int pin){}
		virtual bool output_connected(int pin){}
		virtual void input_to_pin(logic_object* input_, int pin){}
		virtual void pin_to_output(logic_object* output, int pin){}
		virtual vector<bool> value(logic_object* obj){}
		virtual void chip_evaluate(Chip* chip, int pin){}
		virtual bool outputs_filled(){}
		bool is_chip();
		int num_outputs;
	protected:
		map<logic_object*, list<int> > pins;//output pins
};