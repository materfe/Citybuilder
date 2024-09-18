#include "behavior_tree/bt_node.h"

using namespace behavior_tree;

NodeList::NodeList()
{
	current_child_ = 0;
}

void NodeList::AddAChildren(Node* node)
{
	//controls of the node ??? if needed

	all_childrens_.emplace_back(node);
	node = nullptr;
}
