#include <iostream>
#include <cassert>
#include <iterator>
#include <utility>
//#define NDEBUG
//#include <map>

using usI = unsigned short int;
// class ContainerNodeInterface {};

// template <typename Dt, typename K> class TreeNode : public ContainerNodeInterface {
template <typename Dt, typename K> class TreeNode {
public:

    TreeNode(
        const Dt        &data,
        const K         &key,
        const usI        height = 0,
        TreeNode<Dt, K> *parent  = nullptr,
        TreeNode<Dt, K> *right   = nullptr,
        TreeNode<Dt, K> *left    = nullptr
    ) {
        parent_ = parent;
        right_  = right;
        left_   = left;
        data_   = data;
        key_    = key;
        height_ = height;
    }

    TreeNode (const TreeNode *other) {
        assert(other != nullptr);

        parent_ = other->parent_;
        right_  = other->right_;
        left_   = other->left_;
        data_   = other->data_;
        key_    = other->key_;
        height_ = other->height_;
    }

    TreeNode *operator = (const TreeNode *other) {
        assert(other != nullptr);

        parent_ = other->parent_;
        right_  = other->right_;
        left_   = other->left_;
        data_   = other->data_;
        key_    = other->key_;
        height_ = other->height_;

        return this;
    }

    ~TreeNode() = default;



    TreeNode *getParent() const noexcept { return parent_; }
    TreeNode *getRight() const noexcept { return right_; } 
    TreeNode *getLeft() const noexcept { return left_; }
    const Dt &getData() const noexcept { return data_; } 
    const K &getKey() const noexcept { return key_; }


    void setParent(TreeNode parent) noexcept { parent_ = parent; }
    void setRight(TreeNode right) noexcept { right_ = right; }
    void setLeft(TreeNode left) noexcept { left_ = left; }
    void setData(const Dt &data) noexcept { data_ = data; }
    void setKey(const K &key) noexcept { key_ = key; }
    void setHeight(const usI &height) { height_ = height; }


    
    const Dt &operator * () const { 
        assert(this != nullptr);

        return data_;
    }

    bool operator == (const TreeNode *node) const noexcept {
        if ( this == nullptr && node == nullptr ) {
            return true;
        }
        else if ( this == nullptr || node == nullptr ) {
            return false;
        }


        return (key_ == node->key_ && data_ == node->key_);
    }

    bool operator != (const TreeNode *node) const noexcept {
        return !(this == node);
    }

    bool operator > (const TreeNode *node) const noexcept {
        assert(this != nullptr && node != nullptr);

        return (key_ > node->key_);
    }

    bool operator >= (const TreeNode *node) const noexcept {
        return (key_ > node->key_ || key_ == node->key_);
    }

    bool operator < (const TreeNode *node) const noexcept {
        return !(this >= node);
    }

    bool operator <= (const TreeNode *node) const noexcept {
        return !(this > node);
    }




protected:
    TreeNode<Dt, K> *parent_;
    TreeNode<Dt, K> *right_;
    TreeNode<Dt, K> *left_;
    
    Dt               data_;
    K                key_;

    usI              height_;
};

// TODO: inherate from ContainerInterface
template <typename Dt, typename K> class BinarySearchTree {
public:

    //using value_type = typename std::pair<Dt, K>;

    BinarySearchTree() { root_ = nullptr; }

    ~BinarySearchTree() = default;
    
    // TODO: dont i need change * to & in iterator and node classes?
    BinarySearchTree &operator = (const BinarySearchTree &other) {}


    class iterator : public std::iterator<std::input_iterator_tag, TreeNode<Dt, K>> {
    public:

        iterator() { iterator_ = nullptr; }
        
        iterator(iterator *other) { iterator_ = other->iterator_; }

       /*explicit operator typename const_iterator() const {
            return const_cast<TreeNode<Dt, K>*>(iterator_);
        }*/

        ~iterator() = default;



        bool operator == (const iterator *other) const noexcept {
            return (iterator_ == other->iterator_);
        }

        bool operator != (const iterator *other) const noexcept {
            return (iterator_ != other->iterator_);
        }

        const Dt &operator * () const noexcept {
            assert(this != nullptr);
            
            return *iterator_;
        }

        // TODO: k-statistic
        iterator *operator ++ () {
            //static_assert(this != nullptr, "iterator is nullptr");
            assert(this != nullptr);

            iterator_ = iterator_->right_;
            return iterator;
        }
        //iterator *operator++ (int) {}
        //iterator *operator-- () {}
        //iterator *operator-- (int) {}

    protected:
        TreeNode<Dt, K> *iterator_;
        friend class BinarySearchTree::const_iterator;
    };

    class const_iterator : public std::iterator<std::input_iterator_tag, TreeNode<Dt, K>> {
    public:
        const_iterator() {
            const_iterator_ = nullptr;
        }

        const_iterator (iterator *other) { 
            const_iterator_ = const_cast<const TreeNode<Dt, K>*>(other->iterator_);
        }

        explicit operator iterator() const {
            return const_cast<const TreeNode<Dt, K>*>(const_iterator_);
        }

        const_iterator (const_iterator *other) {
            const_iterator_ = other;
        }
        ~const_iterator() = default;

        
    protected:
        const TreeNode<Dt, K> *const_iterator_;
        friend class BinarySearchTree::iterator;
    };
    

    const Dt &at (const K &key) const {}

    Dt &operator [] (const K &key) const {}
    Dt &operator [] (K &&key) const {}



    iterator begin() const noexcept {}
    const_iterator begin() const noexcept {}
    const_iterator cbegin() const noexcept {}

    iterator end() const noexcept {}
    const_iterator end() const noexcept {}
    const_iterator cend() const noexcept {}

    //std::map<Key, T, Compare, Allocator>::rbegin ??
    //std::map<Key, T, Compare, Allocator>::crbegin ??
    //std::map<Key, T, Compare, Allocator>::rend ??
    //std::map<Key, T, Compare, Allocator>::crend ??



    bool empty() const noexcept {}

    size_t size() const noexcept {}



    void clear() noexcept {}

    std::pair<iterator, bool> insert(const Dt &value) {}
    std::pair<const_iterator, bool> insert(const Dt &value) {}
    std::pair<iterator, bool> insert(Dt &&value) {}
    void insert(std::initializer_list<Dt> ilist) {}
    std::pair<iterator, bool> insert_or_assign(const K &k, const Dt &data) {}
    std::pair<iterator, bool> insert_or_assign(K &&k, Dt &&data) {}


    iterator erase(const_iterator pos) {}
    iterator erase(const_iterator first, const_iterator last) {}

    void swap(BinarySearchTree &other) {}



    size_t count(const K &x) const {} // return 0 or 1

    iterator find(const K &key) const {}
    const_iterator find(const K &key) const{}


    bool contains(const K &key) const {}
protected:
    TreeNode<Dt, K> root_;
};

























int main() {
    

    TreeNode<int, int> node(1,32);
    std::cout << node.getKey();

     
    return 0;
}
