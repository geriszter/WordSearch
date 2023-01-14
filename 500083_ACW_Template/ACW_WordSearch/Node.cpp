#include "Node.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

using namespace std;
Node::Node() : m_ch{ '\0' }
{
}

Node::~Node()
{
    children.clear();
}
