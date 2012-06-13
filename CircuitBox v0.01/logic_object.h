#pragma once
#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

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
		virtual void evaluate(){}//examines input values to determine output value
		virtual void chip_evaluate(){};
		virtual void restructure(){}//reevaluates component and calls on output to reevaluate it's value
		void add_output(logic_object* new_output); //sets output variable
		void add_inputs(logic_object& new_input); //Adds inputs to element
		void change_value(logic_object& new_input, int index); //replace an input for another one
		virtual bool value(); //returns the logic value of the component
		virtual bool is_chip(){}	
			
		//GRAPHICAL FUNCTIONS
		void set_dimensions_location(int x, int y, unsigned int w, unsigned int h);//set size of logic object's image
		bool in_range(int min_x, int max_x, int min_y, int max_y); //Checks to see if component is in range of miouse click
		
		//OTHER
		virtual void print_value(); //print the values of inputs and outputs
		
		//VARIABLES
		string label; //label of logic component
		logic_object* output; //pointer to the logic component to which the output is connected
		
	protected:
		bool truth_value; //stores the logic value of the component
		vector<logic_object*> inputs;//stores the inputs of the logic component
		int location_x, location_y; //location in pixels
		unsigned int width;
		unsigned int height;
		unsigned int texture_id; //holds the value it's texture
};