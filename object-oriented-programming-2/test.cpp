#include <memory>
#include <iostream>

using sptr = std::shared_ptr<int>;
using wptr = std::weak_ptr<int>;
class Node {
	public:
		Node(int value = 0) {
			_value = value;
			_sucessor = nullptr;
			_predecessor = nullptr;
		}
		~Node() = default;

		void SetSucessor(wptr sucessor) {
			_sucessor = sucessor;
		}
		void SetPredecessor(sptr predecessor) {
			_predecessor = predecessor;
		}
	private:
		int _value;
		std::shared_ptr<int> _sucessor;
		std::shared_ptr<int> _predecessor;
		/* что если сделать предыдущий элемент как std::weak_ptr<int> */
}

int main() {

	int a = 1;
	std::unique_ptr<int> uptr1 = std::make_unique<int>(a);
	std::unique_ptr<int> uptr2 = std::make_unique<int>(32432);

	/* A --> B */
	Node A(123); Node B(456);



	std::cout << *uptr1;

	return 0;
}
