#include "behavior_tree/bt_selector.h"

#include <iostream>

using namespace behavior_tree;

Status Selector::Process()
{
	if (current_child_ < all_childrens_.size())
	{
		const Status status = all_childrens_[current_child_]->Process();

		if (status == Status::kFailure)
		{
			std::cout << "Next leaf !\n";

			current_child_++;
			if (current_child_ >= all_childrens_.size())
			{
				return Status::kFailure;
			}
		}

		return status;


	}

	return Status::kFailure;
}