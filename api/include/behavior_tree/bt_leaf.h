#ifndef API_BEHAVIOR_TREE_LEAF_H_
#define API_BEHAVIOR_TREE_LEAF_H_
#include <functional>

#include "bt_node.h"

namespace behavior_tree
{
	class Leaf final : public NodeList
	{
	private:
		//call_back_thing
		std::function<Status()> leaf_action_;

	public:

		Leaf(const std::function<Status()>& func): leaf_action_(func){}

		Status Process() override;
		~Leaf() override = default;
	};
}

#endif //API_BEHAVIOR_TREE_LEAF_H_