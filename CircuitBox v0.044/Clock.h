class Clock{
	public:
		Clock(){}
		Clock(double p){
			value=0;
			period=p;
		}
		void update(){
			if(value){
				for(int i=0; i<negative_edge_triggered.size(); i++)
					negative_edge_triggered[i]->evaluate();
				value=0;
			}
			else{
				for(int i=0; i<positive_edge_triggered.size(); i++)
					positive_edge_triggered[i]->evaluate();
				value=1;
			}
			
		}
		void connect(logic_object* obj, bool trigger){
			if(trigger)
				positive_edge_triggered.push_back(obj);
			else
				negative_edge_triggered.push_back(obj);
		}
	private:
		double period; //stored as seconds/cycle
		vector<logic_object*> positive_edge_triggered;
		vector<logic_object*> negative_edge_triggered;
		bool value;
}