#include <iostream>
#include <cassert>
#include <iterator>
#include <memory>
#include <utility>
#include <xtree>
#include <map>
//#define NDEBUG
//#include <map>

using usI = unsigned short int;
// class ContainerNodeInterface {};

// template <typename Kty_, typename Ty_> class TreeNode : public ContainerNodeInterface {
template <typename Kty_, typename Ty_> class TreeNode {
public:

    TreeNode(
        const Kty_       &key,
        const Ty_        &data,
        const usI        height = 0,
        TreeNode<const Kty_, Ty_> *parent  = nullptr,
        TreeNode<const Kty_, Ty_> *right   = nullptr,
        TreeNode<const Kty_, Ty_> *left    = nullptr
    ) {
        parent_ = parent;
        right_  = right;
        left_   = left;
        key_    = key;
        data_   = data;
        height_ = height;
    }

    TreeNode (const TreeNode *other) {
        assert(other != nullptr);

        parent_ = other->parent_;
        right_  = other->right_;
        left_   = other->left_;
        key_    = other->key_;
        data_   = other->data_;
        height_ = other->height_;
    }

    TreeNode *operator = (const TreeNode *other) noexcept {
        assert(other != nullptr);

        parent_ = other->parent_;
        right_  = other->right_;
        left_   = other->left_;
        key_    = other->key_;
        data_   = other->data_;
        height_ = other->height_;

        return this;
    }

    ~TreeNode() = default;



    TreeNode *getParent() const noexcept { return parent_; }
    TreeNode *getRight() const noexcept { return right_; } 
    TreeNode *getLeft() const noexcept { return left_; }
    const Ty_ &getData() const noexcept { return data_; } 
    const Kty_ &getKey() const noexcept { return key_; }


    void setParent(TreeNode *parent) noexcept { parent_ = parent; }
    void setRight(TreeNode *right) noexcept { right_ = right; }
    void setLeft(TreeNode *left) noexcept { left_ = left; }
    void setData(const Ty_ &data) noexcept { data_ = data; }
    // TODO: ckeck the new key
    void setKey(const Kty_ &key) noexcept { key_ = key; }
    void setHeight(const usI &height) { height_ = height; }


    
    const Ty_ &operator * () const { 
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
    TreeNode<const Kty_, Ty_> *parent_;
    TreeNode<const Kty_, Ty_> *right_;
    TreeNode<const Kty_, Ty_> *left_;
    
    const Kty_                 key_;
    Ty_                        data_;

    usI                        height_;
};

// TODO: inherate from ContainerInterface
// change std::pait to my own pait class
template <class Kty_, class Ty_, class Pr_ = std::less<Kty_>,
    class Alloc_ = std::allocator<std::pair<const Kty_, Ty_>>> class BinarySearchTree {
public:

    using key_type    = typename Kty_;
    using mapped_type = typename Ty_;
    using key_compare = Pr_;
    using value_type  = typename std::pair<const Kty_, Ty_>;

    BinarySearchTree() { root_ = nullptr; size_ = 0; }

    ~BinarySearchTree() = default;
    
    // TODO: do i need change * to & in iterator and node classes?
    BinarySearchTree &operator = (const BinarySearchTree &other) {
        // delete old tree
        // root_ = other->root_;
        // size_ = other->size_;
        
        // return *this;
    }

    // TODO: 
    // need: *iterator = std::pair<const Kty_, Ty_>
    //  now: *iterator = *TreeNode<Kty_, Ty_>
    // вынести key из класса TreeNode наружу, возможно ввести класс key_compare
    // как сравнивать 
    // как сделать шаблон по умолчанию
    class iterator : public std::iterator<std::input_iterator_tag, TreeNode<const Kty_, Ty_>> {
    public:

        iterator() { iterator_ = nullptr; }
        
        iterator (iterator *other) { iterator_ = other->iterator_; }

        iterator (const TreeNode *treeNode) {
            iterator_ = treeNode;
        }

        iterator *operator = (const iterator *other) {
            iterator_ = other->iterator_;
        }

       /*explicit operator typename const_iterator() const {
            return const_cast<TreeNode<Kty_, Ty_>*>(iterator_);
        }*/

        ~iterator() = default;



        bool operator == (const iterator *other) const noexcept {
            return (iterator_ == other->iterator_);
        }

        bool operator != (const iterator *other) const noexcept {
            return (iterator_ != other->iterator_);
        }

        const Ty_ &operator * () const noexcept {
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
        TreeNode<const Kty_, Ty_> *iterator_;
        friend class BinarySearchTree::const_iterator;
    };

    class const_iterator : public std::iterator<std::input_iterator_tag, TreeNode<const Kty_, Ty_>> {
    public:
        const_iterator() {
            const_iterator_ = nullptr;
        }

        const_iterator (iterator *other) { 
            const_iterator_ = const_cast<const TreeNode<const Kty_, Ty_>*>(other->iterator_);
        }

        const_iterator (const_iterator *other) {
            const_iterator_ = other;
        }

        const_iterator (TreeNode *treeNode) {
            const_iterator_ = const_cast<const TreeNode<const Kty_, Ty_>*>(treeNode);
        }

        const_iterator (const TreeNode *treeNode) {
            const_iterator_ = treeNode;
        }

        const_iterator *operator = (const_iterator *other) {
            const_iterator_ = other->const_iterator_;
        }


        /*explicit operator iterator() const {
            return const_cast<const TreeNode<const Kty_, Ty_>*>(const_iterator_);
        }*/

        ~const_iterator() = default;

        
    protected:
        const TreeNode<const Kty_, Ty_> *const_iterator_;
        friend class BinarySearchTree::iterator;
    };
    

    const Ty_ &at (const Kty_ &key) const {}

    Ty_ &operator [] (const Kty_ &key) const {}
    Ty_ &operator [] (Kty_ &&key) const {}



    iterator begin() noexcept {}
    const_iterator begin() const noexcept {}
    const_iterator cbegin() const noexcept {}

    iterator end() noexcept {}
    const_iterator end() const noexcept {}
    const_iterator cend() const noexcept {}

    //std::map<Key, T, Compare, Allocator>::rbegin ??
    //std::map<Key, T, Compare, Allocator>::crbegin ??
    //std::map<Key, T, Compare, Allocator>::rend ??
    //std::map<Key, T, Compare, Allocator>::crend ??



    bool empty() const noexcept final {
        return size() == 0;
    }

    size_t size() const noexcept final {
        return size_;
    }



    void clear() noexcept {

    }

    std::pair<iterator, bool> insert (const Ty_ &value) {}
    std::pair<const_iterator, bool> insert (const Ty_ &value) {}
    std::pair<iterator, bool> insert (Ty_ &&value) {}
    void insert (std::initializer_list<Ty_> ilist) {}
    std::pair<iterator, bool> insert_or_assign (const Kty_ &k, const Ty_ &data) {}
    std::pair<iterator, bool> insert_or_assign (Kty_ &&k, Ty_ &&data) {}


    iterator erase(const_iterator pos) {}
    iterator erase(const_iterator first, const_iterator last) {}

    void swap(BinarySearchTree &other) {
        // поменять местами корни и размеры
    }



    size_t count(const Kty_ &x) const {} // return 0 or 1

protected:
    // O(h), h - height of the tree
    TreeNode *_FIND (const TreeNode *subTree_root, const Kty_ &key) const noexcept {
        if ( subTree_root == nullptr ) {
            return nullptr;
        }
        else if ( subTree_root->key_ == key ) {
            return subTree_root;
        }
        else if ( subTree_root->key_ > key ) {
            return _FIND(subTree_root->left_, key);
        }
        else {
            return _FIND(subTree_root->right_, key);
        }
    }
    // O(h)
    TreeNode *_MAX () const noexcept {
        assert(root_ != nullptr);
        
        if ( root_ == nullptr ) { return root_; }
        TreeNode<key_type, mapped_type> *result = new TreeNode<key_type, mapped_type>(root_);
        //auto *node_current = new TreeNode<key_type, mapped_type>(root_);
        //auto *node_current = new TreeNode(root_);
        while ( true ) {
            if ( result->getRight() == nullptr ) {
                break;
            }
            else {
                result = result->getRight();
            }
        }

        return result;
    }
    // O(h)
    TreeNode *_MIN () const noexcept {
        assert(root_ != nullptr);
        
        if ( root_ == nullptr ) { return root_; }
        TreeNode<key_type, mapped_type> *result = new TreeNode<key_type, mapped_type>(root_);
        //auto *node_current = new TreeNode<key_type, mapped_type>(root_);
        //auto *node_current = new TreeNode(root_);
        while ( true ) {
            if ( result->getLeft() == nullptr ) {
                break;
            }
            else {
                result = result->getLeft();
            }
        }

        return result;
    }

public:
    // O(h)
    iterator find (const Kty_ &key) {
        auto nodeResult = _FIND(root_, key);

        return iterator(nodeResult);
    }
    // O(h)
    const_iterator find (const Kty_ &key) const {
        auto nodeResult = _FIND(root_, key);

        return const_iterator(nodeResult);
    }

    // O(h)
    bool contains (const Kty_ &key) const {
        return (_FIND(root_, key) != nullptr);
    }

protected:
    // O(h), h - height of the tree
    // not less
    TreeNode *_FIND_LOWER_BOUND (const key_type &key) const noexcept {
        auto *result = _FIND(root_, key);

        if ( result->right != nullptr ) {
            result = result->right_;
            
            while ( true ) {
                if ( result->left_ != nullptr ) {
                    result = result->left_;
                }
                else { break; }
            }
        }
        else {
            auto result_parent = result->parent_;

            if (result_parent->left_->key_ == key_ )
        }
        
        
    }
public:
    iterator lower_bound (const key_type &key) {

    }
    const_iterator lower_bound (const key_type &key) {}

    iterator upper_bound (const key_type &key) {}
    const_iterator upper_bound (const key_type &key) {}



protected:
    TreeNode<const Kty_, Ty_> *root_;
    size_t size_;
};

























int main() {
    

    TreeNode<int, int> node(1,32);
    std::cout << node.getKey();
    
    
    std::map<int, int>;
     
    return 0;
}
