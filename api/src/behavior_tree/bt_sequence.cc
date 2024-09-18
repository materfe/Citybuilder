#include "behavior_tree/bt_sequence.h"

using namespace behavior_tree;

Status Sequence::Process()
{

	if (current_child_ < all_childrens_.size())
	{
		const Status status = all_childrens_[current_child_]->Process();

		if (status == Status::kSuccess)
		{
			current_child_++;
			if (current_child_ >= all_childrens_.size())
			{
				current_child_ = 0;
				return Status::kSuccess;
			}
			else
			{
				return Status::kRunning;
			}
		}

		return status;


	}

	return Status::kFailure;

}