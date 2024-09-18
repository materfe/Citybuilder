#ifndef API_BEHAVIOR_TREE_SELECTOR_H_
#define API_BEHAVIOR_TREE_SELECTOR_H_
#include "bt_node.h"


namespace behavior_tree
{
	class Selector : public NodeList
	{
	public:
		Status Process() override;
		~Selector() override = default;
	};

}

#endif //API_BEHAVIOR_TREE_SELECTOR_H_