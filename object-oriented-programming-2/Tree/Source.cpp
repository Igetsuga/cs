#include <iostream>   // to get std::cout
#include <cassert>    // to get assert() and static assert()
#include <iterator>   // to get iterators' tags
#include <cstddef>    // to get std::ptrdiff_t
#include <memory>     // to get 
#include <utility>    // to get std::pair<,>
// #include <xtree>
#include <map>        // to get std::map<,>
//#define NDEBUG


// TODO: move semantics
// TODO: recode iterators with right inheretance


// class ContainerNodeInterface {};


// ****************************************************************************
// ********************************* TreeNode *********************************
// ****************************************************************************

// template <typename Kty_, typename Dty_> class TreeNode : public ContainerNodeInterface {
template <typename Kty_, typename Dty_>
class TreeNode {
public:

    // tags:
    using usI             = unsigned short int;                    // just to get code more readable
    using value_type      = typename std::pair<const Kty_, Dty_>;  // the type the TreeNode iterates over 
    using pointer         = value_type*;  
    using reference       = value_type&; 
    using const_reference = const value_type&; 



    TreeNode(
        reference                  &pairValue,
        usI                         height  = 0,
        TreeNode<const Kty_, Dty_> *left    = nullptr,
        TreeNode<const Kty_, Dty_> *parent  = nullptr,
        TreeNode<const Kty_, Dty_> *right   = nullptr
    ) {
        left_   = left;
        parent_ = parent;
        right_  = right;
        pairValue_  = pairValue;
        height_ = height;
    }

    TreeNode (const TreeNode *other) {
        assert(other != nullptr);

        parent_ = other->parent_;
        right_  = other->right_;
        left_   = other->left_;
        pairValue_  = other->pairValue_;
        height_ = other->height_;
    }

    TreeNode *operator = (const TreeNode *other) noexcept {
        assert(other != nullptr);

        parent_     = other->parent_;
        right_      = other->right_;
        left_       = other->left_;
        pairValue_  = other->pairValue_;
        height_     = other->height_;

        return this;
    }

    ~TreeNode() = default;



    TreeNode *getLeft() const noexcept { return left_; }
    TreeNode *getParent() const noexcept { return parent_; }
    TreeNode *getRight() const noexcept { return right_; } 
    const Dty_ &getData() const noexcept { return pairValue_.second; } 
    const Kty_ &getKey() const noexcept { return pairValue_.first; }


    void setLeft(TreeNode *left) noexcept { left_ = left; }
    void setParent(TreeNode *parent) noexcept { parent_ = parent; }
    void setRight(TreeNode *right) noexcept { right_ = right; }
    void setData(const Dty_ &data) noexcept { pairValue_.second = data; }
    void setHeight(const usI &height) { height_ = height; }
    void setValue(reference value_pair) { pairValue_ = value_pair; }

private:
    void setKey (const Kty_ &key) noexcept { pairValue_.first = key; }

public:
    
    reference operator * () const { 
        assert(this != nullptr);

        return pairValue_;
    }

    bool operator == (const TreeNode *node) const noexcept {
        if ( this == nullptr && node == nullptr ) {
            return true;
        }
        else if ( this == nullptr || node == nullptr ) {
            return false;
        }


        return (pairValue_.first == node->pairValue_.first && pairValue_.second == node->pairValue_.second);
    }

    bool operator != (const TreeNode *node) const noexcept {
        return !(this == node);
    }

    bool operator > (const TreeNode *node) const noexcept {
        assert(this != nullptr && node != nullptr);

        return (pairValue_.first > node->pairValue_.first);
    }

    bool operator >= (const TreeNode *node) const noexcept {
        return (pairValue_.first > node->pairValue_.first || pairValue_.first == node->pairValue_.first);
    }

    bool operator < (const TreeNode *node) const noexcept {
        return !(this >= node);
    }

    bool operator <= (const TreeNode *node) const noexcept {
        return !(this > node);
    }



protected:
    TreeNode<const Kty_, Dty_> *left_;
    TreeNode<const Kty_, Dty_> *parent_;
    TreeNode<const Kty_, Dty_> *right_;
    
    value_type                  pairValue_;
    usI                         height_;
};


// ****************************************************************************
// ***************************** BinarySearchTree *****************************
// ****************************************************************************


// TODO: inherate from ContainerInterface
// TODO: change std::pait to my own pait class
template <
    class Kty_,
    class Dty_, 
    class Pr_ = std::less<Kty_>,
    class Alloc_ = std::allocator<std::pair<const Kty_, Dty_>>
>
class BinarySearchTree {
public:
    
    // tags:
    using value_type      = typename std::pair<const Kty_, Dty_>; // a type that BST store
    using key_type        = Kty_;
    using mapped_type     = Dty_;
    using Nodeptr         = TreeNode<Kty_, Dty_>*;                // a pointer to node of BST
    using reference       = value_type&;    
    using const_Nodeptr   = const TreeNode<Kty_, Dty_>*;                      
    using const_reference = const value_type&;



    BinarySearchTree() { root_ = nullptr; size_ = 0; }

    BinarySearchTree(const BinarySearchTree &other) {
        root_ = other.root_;
        size_ = other.size_;
    }

    BinarySearchTree &operator = (const BinarySearchTree *other) {
        // this->clear;

        root_ = other->root_;
        size_ = other->size_;

        return *this;
    }

    ~BinarySearchTree() = default;
    


    class const_iterator {
    private:

        // tags:
        using iterator_category  = std::input_iterator_tag;  // read-only iterator 
        using difference_type    = std::ptrdiff_t;
        using value_type         = TreeNode<Kty_, Dty_>;
        using pointer            = value_type*;              // it_pointer = const Nodeptr 
        using reference          = value_type&;
        using const_pointer      = const value_type*;
        using const_reference    = const value_type&;
        


        const_iterator(pointer ptr) : itt_(ptr) {}        


        const_reference operator *() const noexcept { return const_cast<const_reference>(*itt_); }
        
        const_pointer operator ->() const noexcept { return const_cast<const_pointer>(itt_); }

    private:

        pointer itt_;

    };

    class forward_iterator {
    public:

        // tags:
        using iterator_category  = std::forward_iterator_tag;  // read-only iterator 
        using difference_type    = std::ptrdiff_t;
        using value_type         = TreeNode<Kty_, Dty_>;
        using pointer            = value_type*;             // it_pointer = Nodeptr 
        using reference          = value_type&;



        forward_iterator(pointer ptr) : f_itt_(ptr) {}


        reference operator *() const noexcept { return *f_itt_; }
        
        pointer operator ->() const { return f_itt_; }


        forward_iterator& operator ++() { f_itt_++; return *this; }
        
        forward_iterator operator ++(int) { // why we dont return a reference? 
            auto tmp = *this;
            ++(*this);

            return tmp;
        }    

        friend bool operator == (const forward_iterator& a, const forward_iterator& b) {
            return a.m_ptr == b.m_ptr;
        };


        friend bool operator != (const forward_iterator& a, const forward_iterator& b) {
            return a.m_ptr != b.m_ptr; 
        };  

    private:

        pointer f_itt_;

    };

    class iterator {
    public:

        // tags:
        using iterator_category  = std::bidirectional_iterator_tag;  // read-only iterator 
        using difference_type    = std::ptrdiff_t;
        using value_type         = TreeNode<Kty_, Dty_>;
        using pointer            = value_type*;                     // it_pointer = Nodeptr 
        using reference          = value_type&;



        iterator(pointer ptr) : i_itt_(ptr) {}


        reference operator *() const noexcept { return *i_itt_; }
        
        pointer operator ->() const { return i_itt_; }


        iterator& operator ++() { i_itt_++; return *this; }
        
        iterator operator ++(int) { // why we dont return a reference? 
            auto tmp = *this;
            ++(*this);

            return tmp;
        }

        iterator& operator --() { i_itt_--; return *this; }
        
        iterator operator --(int) { // why we dont return a reference? 
            auto tmp = *this;
            --(*this);

            return tmp;
        }     

        friend bool operator == (const iterator& a, const iterator& b) {
            return a.m_ptr == b.m_ptr;
        };


        friend bool operator != (const iterator& a, const iterator& b) {
            return a.m_ptr != b.m_ptr; 
        };  

    private:

        pointer i_itt_;

    };

    class reverse_iterator {
    public:

        // tags:
        using iterator_category  = std::bidirectional_iterator_tag;  // read-only iterator 
        using difference_type    = std::ptrdiff_t;
        using value_type         = TreeNode<Kty_, Dty_>;
        using pointer            = value_type*;                     // it_pointer = Nodeptr 
        using reference          = value_type&;



        reverse_iterator(pointer ptr) : r_itt_(ptr) {}


        reference operator *() const noexcept { return *r_itt_; }
        
        pointer operator ->() const { return r_itt_; }


        reverse_iterator& operator --() { r_itt_++; return *this; }
        
        reverse_iterator operator --(int) { // why we dont return a reference? 
            auto tmp = *this;
            ++(*this);

            return tmp;
        }

        reverse_iterator& operator ++() { r_itt_--; return *this; }
        
        reverse_iterator operator ++(int) { // why we dont return a reference? 
            auto tmp = *this;
            --(*this);

            return tmp;
        }     

        friend bool operator == (const reverse_iterator& a, const reverse_iterator& b) {
            return a.m_ptr == b.m_ptr;
        }; 


        friend bool operator != (const reverse_iterator& a, const reverse_iterator& b) {
            return a.m_ptr != b.m_ptr; 
        };  

    private:

        pointer r_itt_;

    };
    

    const Dty_ &at (const Kty_ &key) const {}

    Dty_ &operator [] (const Kty_ &key) const {}



    iterator begin() noexcept { }
    reverse_iterator rbegin() noexcept {}
    const_iterator cbegin() const noexcept {}

    iterator end() noexcept {}
    reverse_iterator rend() const noexcept {}
    const_iterator cend() const noexcept {}



    virtual bool empty() const noexcept final {
        return size() == 0;
    }

    virtual size_t size() const noexcept final {
        return size_;
    }



    void clear() noexcept {

    }

    std::pair<iterator, bool> insert (const Dty_ &value) {}
    std::pair<const_iterator, bool> insert (const Dty_ &value) {}
    std::pair<iterator, bool> insert (Dty_ &&value) {}
    void insert (std::initializer_list<Dty_> ilist) {}
    std::pair<iterator, bool> insert_or_assign (const Kty_ &k, const Dty_ &data) {}
    std::pair<iterator, bool> insert_or_assign (Kty_ &&k, Dty_ &&data) {}


    iterator erase(const_iterator pos) {}
    iterator erase(const_iterator first, const_iterator last) {}

    void swap(BinarySearchTree &other) {
        // поменять местами корни и размеры
    }



    size_t count(const key_type &key) const {
        return contains(key);
    } // return 0 or 1

protected:

    // O(h), h - height of the tree
    Nodeptr _FIND (const Nodeptr subTree_root, const Kty_ &key) const noexcept {
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
    Nodeptr _MAX () const noexcept {
        // assert(root_ != nullptr); // is empty tree
        
        if ( root_ == nullptr ) { return root_; }
        
        Nodeptr result = new Nodeptr(root_);
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
    Nodeptr _MIN () const noexcept {
        // assert(root_ != nullptr); // is empty tree
        
        if ( root_ == nullptr ) { return root_; }
        
        Nodeptr result = new Nodeptr(root_);
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
    iterator find (const key_type &key) {
        return iterator(_FIND(root_, key));
    }

    // O(h)
    const_iterator find (const key_type &key) const {
        return const_iterator(_FIND(root_, key));
    }

    // O(h)
    bool contains (const key_type &key) const {
        return (_FIND(root_, key) != nullptr);
    }

protected:

    // O(h), h - height of the tree; not less; the key of found node mustn't equals kye 
    Nodeptr _FIND_LOWER_BOUND (Nodeptr node, const key_type &key) const { 
       
        assert(node != nullptr);   // is value with that key exists

        if ( node->right != nullptr ) 
        {
            node = node->right_;
            
            while ( true )
            {
                if ( node->left_ != nullptr ) {
                    node = node->left_;
                }
                else { break; } 
            }

            return node; 
        } 
        else if (node == _MAX()) { return node->parent_; }
        else {

            auto parent_node = node->parent_;

            if (node == parent_node->left_) // node is MIN in subTree
            {
                return parent_node->right_;
            }
            else {                          // node is MAX in subTree
                return node->parent_->parent_; 
            }
        }
        
        return this->end();
    }

    // O(nh); return firts greater;
    // DOESNT WORK
    Nodeptr _FIND_UPPER_BOUND (Nodeptr node, const key_type &key) const {
     
        auto nodeLB = _FIND_LOWER_BOUND(node, key);
        
        if ( nodeLB != nullptr && nodeLB->pairValue_->firts == key ) {
            return _FIND_UPPER_BOUND(nodeLB, key);
        }

        return nodeLB;    
    }
public:
    
    iterator lower_bound (const key_type &key) {
        auto node = _FIND(root_, key);
        
        return _FIND_LOWER_BOUND(node, key);
    }

    const_iterator lower_bound (const key_type &key) const {
        auto node = _FIND(root_, key);
        
        return _FIND_LOWER_BOUND(node, key);
    }

    iterator upper_bound (const key_type &key) {
        auto node = _FIND(root_, key);
        
        return _FIND_UPPER_BOUND(key);
    }
    const_iterator upper_bound (const key_type &key) const { 
        auto node = _FIND(root_, key);
        
        return _FIND_UPPER_BOUND(key);
    }



protected:
    Nodeptr* root_;
    size_t size_;
};

























int main() {
    

    //TreeNode<int> node(1);
    //std::cout << node.getData();
    
    
    std::map<int, int>;
     
    return 0;
}
