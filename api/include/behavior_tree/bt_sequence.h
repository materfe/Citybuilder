#ifndef API_BEHAVIOR_TREE_SEQUENCE_H_
#define API_BEHAVIOR_TREE_SEQUENCE_H_
#include "bt_node.h"

namespace behavior_tree
{
	class Sequence : public NodeList
	{
	public:
		~Sequence() override = default;

		Status Process() override;
		//void ResetSequence();
	};
}

#endif// API_BEHAVIOR_TREE_SEQUENCE_H_