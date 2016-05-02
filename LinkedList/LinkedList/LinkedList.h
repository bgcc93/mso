#include "Node.h"

class LinkedList{
	Node* first;
	Node* last;
	int nodeNumbers;

	void DeleteNode(Node* n, Node* nB4){
		delete n;
		last = nB4;
	}

	Node* GetNodeAt(int nodeNum){
		if ( nodeNum > nodeNumbers || nodeNum < 0){
			return nullptr;
		}else{
			Node* n = first;
			for (int i = 0; i < nodeNum; i++){
				n = n->GetNext();
			}
			return n;
		}
	}

public:
	LinkedList(){
			first = nullptr;
			last = nullptr;
			nodeNumbers = 0;
	}
	
	LinkedList(double val){
		first = new Node(val);
		last = first;
		nodeNumbers = 1;
	}
	
	LinkedList(double valx, double valy){
		first = new Node(valx, valy);
		last = first;
		nodeNumbers = 1;
	}

	LinkedList(Node* n){
		first = n;
		last = first;
		first->SetNext(last);
		nodeNumbers = 1;
	}

	~LinkedList(){
		delete first;
	}

	Node* First(){return first;}
	Node* Last(){return last;}

	int LinkedList::Length(){return LinkedList::nodeNumbers;}
	
	void CreateNode(double val){
		CreateNode(val, val);
	}

	void CreateNode(double valx, double valy){
		Node* n = new Node(valx, valy);
		if(first == 0){
			first = n;
			last = 0;
			first->SetNext(0);
		}
		else if (nodeNumbers == 1) {
			first->SetNext(n);
			last = n;
		}else{
			last->SetNext(n);
			last = n;
		}
		nodeNumbers += 1;
	}

	Node* operator[](int nodeNum){ return GetNodeAt(nodeNum); }

	void DeleteNodeAt(int nodeNum){
		Node* n = GetNodeAt(nodeNum);
		Node* nB4;
		int nn = nodeNumbers - nodeNum;
		if ( nodeNum < 1 ){
			if (n > 0){
				nB4 = GetNodeAt(nodeNum - 1);
			}else{
				nB4 = 0;
			}
			DeleteNode(n, nB4);
		}
		nodeNum -= nn;
	}
	
	void DeleteFirst(){ 
		DeleteNode(first, 0);
		first = 0;
		nodeNumbers = 0;
	}

	void DeleteLast(){ 
		Node* n = GetNodeAt(nodeNumbers - 1);
		DeleteNode(last, 0);
		first = 0;
		nodeNumbers -= 1;
	}

};