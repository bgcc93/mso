class Node{
	double val;
	double val2;
	Node* nextNode;
public:
	Node::Node(){
		val = 0;
		val2 = 0;
		nextNode = 0;
	}
	Node::Node(double v){
		nextNode = 0;
		val = v;
		val2 = v;
	}
	Node::Node(double v, double v2){
		nextNode = 0;
		val = v;
		val2 = v2;
	}
	Node::~Node(){
		delete nextNode;
	}
	
	double Node::GetVal(){return Node::val;}
	double Node::GetVal2(){return Node::val2;}

	double Node::X(){return GetVal();}
	double Node::Y(){return GetVal2();}

	void Node::SetVal(double v){Node::val = v;}
	
	void Node::SetX(double v){Node::val = v;}
	void Node::SetY(double v){Node::val2 = v;}

	void SetNext(Node* n){nextNode = n;}
	Node* GetNext(){return nextNode;}
};