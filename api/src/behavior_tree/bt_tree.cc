#include "behavior_tree/bt_tree.h"

#include <iostream>


using namespace behavior_tree;

void Tree::Tick() const
{

	if (root_ != nullptr)
	{
		Status status = root_->Process();
	}

	/*switch (status) {
	case Status::kRunning:
		break;
	case Status::kFailure:
		break;
	case Status::kSuccess:
		break;
	default:
		std::cout << "Whaaaaaat ?????" << std::endl;
		break;
	}*/

}

void Tree::AttachNode(std::unique_ptr<Selector>& node)
{
	root_ = std::move(node);
}

void Tree::AttachNode(std::unique_ptr<Leaf>& node)
{
	root_ = std::move(node);
}

void Tree::AttachNode(std::unique_ptr<Sequence>& node)
{
	root_ = std::move(node);
}
