#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
class Node
{
public:

	//Node(const char c);
	Node();
	~Node();


	Node* SetChild(const int pos) const;
	void SetChar(const char ch);
	void AddChild(Node* n);
	char GetChar() const;

	Node& operator=(const Node&) =delete;//Parasoft Error
	Node(Node&) = delete;//Parasoft error

private:
	char m_ch;
	vector<Node*> children;
};

inline void Node::AddChild(Node* n)
{
	children.push_back(n);
}

inline Node* Node::SetChild(const int pos) const
{
	return children[pos];
}

inline char Node::GetChar() const
{
	return m_ch;
}


inline void Node::SetChar(const char ch)
{
	m_ch = ch;
}
