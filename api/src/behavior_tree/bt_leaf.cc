#include "behavior_tree/bt_leaf.h"

using namespace behavior_tree;

Status Leaf::Process()
{

	if (leaf_action_ != nullptr)
	{
		return leaf_action_();
	}
	else
	{
		return Status::kFailure;
	}
}