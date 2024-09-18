#ifndef API_BEHAVIOR_TREE_NODE_H_
#define API_BEHAVIOR_TREE_NODE_H_
#include <vector>

namespace behavior_tree
{
	//enum -> state of node
	enum class Status
	{
		kRunning,
		kSuccess,
		kFailure
	};


	class Node
	{
	public:
		virtual ~Node() = default;
		//function that does something depending on the node's task and return a status
		virtual Status Process() = 0;
	};


	class NodeList : public Node
	{
	protected:
		std::vector<Node*> all_childrens_;
		size_t current_child_;

	public:
		NodeList();
		~NodeList() override
		{
			for (auto& ptr : all_childrens_)
			{
				ptr = nullptr;
			}
		}

		void AddAChildren(Node* node);
	};
}

#endif //API_BEHAVIOR_TREE_NODE_H_