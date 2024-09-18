#ifndef API_BEHAVIOR_TREE_TREE_H_
#define API_BEHAVIOR_TREE_TREE_H_

#include <memory>

#include "bt_leaf.h"
#include "bt_node.h"
#include "bt_selector.h"
#include "bt_sequence.h"

namespace behavior_tree
{
	class Tree
	{
		std::unique_ptr<Node> root_ = nullptr;

	public:

		void Tick() const;
		void AttachNode(std::unique_ptr<Selector>& node);
		void AttachNode(std::unique_ptr<Leaf>& node);
		void AttachNode(std::unique_ptr<Sequence>& node);


	};
}
#endif//API_BEHAVIOR_TREE_TREE_H_