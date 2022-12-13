#include <iostream>   // to get std::cout
#include <cassert>    // to get assert() and static assert()
#include <iterator>   // to get iterators' tags
#include <cstddef>    // to get std::ptrdiff_t
#include <limits.h>
// #include <memory>     // to get 
#include <utility>    // to get std::pair<,>
#include <map>        // to get std::map<,>
//#define NDEBUG


// TODO: move semantics
// TODO: recode iterators with right inheretance

namespace MY_BASE {

    template <class Ty>
    void swap(Ty &a, Ty &b) {     
    // it's just a copy of std::swap() implementation
        if (*a == *b) {
            return;
        }

        Ty tmp = std::move(a);
        a = std::move(b);
        b = std::move(tmp);
    }

}




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
    using value_type      = std::pair<const Kty_, Dty_>;           // the type the TreeNode iterates over 
    using pointer         = value_type*;  
    using reference       = value_type&; 
    using const_reference = const value_type&; 



// https://stackoverflow.com/questions/74764195/why-does-the-compiler-declare-a-class-method-deleted
    TreeNode(
        const_reference             pairValue,
        usI                         height  = 0,
        TreeNode<const Kty_, Dty_> *parent  = nullptr,
        TreeNode<const Kty_, Dty_> *left    = nullptr,
        TreeNode<const Kty_, Dty_> *right   = nullptr
    ) :
        left_(left),
        parent_(parent),
        right_(right),
        pairValue_(pairValue),
        height_(height)
    {}

    TreeNode (const TreeNode *other) {
        assert(other != nullptr);

        left_       = other->left_;
        parent_     = other->parent_;
        right_      = other->right_;
        pairValue_  = other->pairValue_;
        height_     = other->height_;
    }

    TreeNode *operator = (const TreeNode *other) noexcept {
        // assert(other != nullptr);  // TODO: what is other == nullptr

        left_       = other->left_;
        parent_     = other->parent_;
        right_      = other->right_;
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
    usI getHeight() const noexcept { return height_; }



    void setLeft(TreeNode *left) noexcept { left_ = left; }
    void setParent(TreeNode *parent) noexcept { parent_ = parent; }
    void setRight(TreeNode *right) noexcept { right_ = right; }
    void setData(const Dty_ &data) noexcept { pairValue_.second = data; }
    void setValue(reference value_pair) { pairValue_ = value_pair; }
    void setHeight(const usI &height) { height_ = height; }


    // reference operator *() {} // TODO
    // pointer operator ->() {}  // TODO

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

    // bool operator > (const TreeNode *node) const noexcept {
    //     assert(this != nullptr && node != nullptr);

    //     return (pairValue_.first > node->pairValue_.first);
    // }

    // bool operator >= (const TreeNode *node) const noexcept {
    //     return (pairValue_.first > node->pairValue_.first || pairValue_.first == node->pairValue_.first);
    // }

    // bool operator < (const TreeNode *node) const noexcept {
    //     return !(this >= node);
    // }

    // bool operator <= (const TreeNode *node) const noexcept {
    //     return !(this > node);
    // }



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
// BinarySearchTree dosn't allow store values with the same keys
// TODO: make a container that allow store values with the same keys based on BinarySearchTree
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
    using Nodeptr         = TreeNode<const Kty_, Dty_>*;          // a pointer to node of BST
    using const_Nodeptr   = const Nodeptr;                      
    using reference       = value_type&;                        
    using const_reference = const value_type&;



    BinarySearchTree() { root_ = nullptr; size_ = 0; }

    BinarySearchTree(const BinarySearchTree &other) {
        root_ = other.root_;
        size_ = other.size_;
    }

    BinarySearchTree &operator = (const BinarySearchTree *other) {
        this->_CLEAR_SUBTREE(root_);

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
        using value_type         = TreeNode<const Kty_, Dty_>;
        using pointer            = value_type*;              // it_pointer = Nodeptr = TreeNode<,>* 
        using reference          = value_type&;
        using const_pointer      = const value_type*;
        using const_reference    = const value_type&;
        

    public:

        const_iterator (pointer ptr) : itt_(ptr) {}     
           

        virtual const_reference operator *() const noexcept { return *itt_; }
        
        virtual const_pointer operator ->() const noexcept { return itt_; }

    protected:

        pointer itt_;

    };

    class forward_iterator {
    public:

        // tags:
        using iterator_category  = std::forward_iterator_tag;  // read-only iterator 
        using difference_type    = std::ptrdiff_t;
        using value_type         = TreeNode<const Kty_, Dty_>;
        using pointer            = value_type*;             // it_pointer = Nodeptr 
        using reference          = value_type&;



        forward_iterator (pointer ptr) : f_itt_(ptr) {}
        
        forward_iterator (const_iterator c_itt) {
            f_itt_ = c_itt.itt_;
        }


        reference operator *() const noexcept { return *f_itt_; }
        
        pointer operator ->() const { return f_itt_; }


        forward_iterator& operator ++() { f_itt_++; return *this; }
        
        forward_iterator operator ++(int) { // why we dont return a reference? 
            forward_iterator tmp = *this;
            ++(*this);

            return tmp;
        }    

        friend bool operator == (const forward_iterator& a, const forward_iterator& b) {
            return a.f_itt_ == b.f_itt_;
        };


        friend bool operator != (const forward_iterator& a, const forward_iterator& b) {
            return a.f_itt_ != b.f_itt_; 
        };  

    private:

        pointer f_itt_;

    };

    class iterator  {
    public:

        // tags:
        using iterator_category  = std::bidirectional_iterator_tag;  // read-only iterator 
        using difference_type    = std::ptrdiff_t;
        using value_type         = TreeNode<const Kty_, Dty_>;
        using pointer            = value_type*;                     // it_pointer = Nodeptr 
        using reference          = value_type&;



        iterator (pointer ptr) : i_itt_(ptr) {}

        // iterator (const_iterator c_itt) {
        //     i_itt_ = c_itt.itt_;
        // }


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
            iterator tmp = *this;
            --(*this);

            return tmp;
        }     

        friend bool operator == (const iterator& a, const iterator& b) {
            return a.i_itt_ == b.i_itt_;
        };


        friend bool operator != (const iterator& a, const iterator& b) {
            return a.i_itt_ != b.i_itt_; 
        };  

    private:

        pointer i_itt_; 


    };
    // class reverse_iterator : public forward_iterator {
    // public:

    //     // tags:
    //     using iterator_category  = std::bidirectional_iterator_tag;  // read-only iterator 
    //     using difference_type    = std::ptrdiff_t;
    //     using value_type         = TreeNode<const Kty_, Dty_>;
    //     using pointer            = value_type*;                     // it_pointer = Nodeptr 
    //     using reference          = value_type&;

    //     using const_iterator::itt_;


    //     reverse_iterator(pointer ptr) : const_iterator::itt_(ptr) {}


    //     virtual reference operator *() const noexcept { return *itt_; }
        
    //     virtual pointer operator ->() const { return itt_; }


    //     virtual reverse_iterator& operator --() { itt_++; return *this; }
        
    //     virtual reverse_iterator operator --(int) { // why we dont return a reference? 
    //         reverse_iterator tmp = *this;
    //         ++(*this);

    //         return tmp;
    //     }

    //     virtual reverse_iterator& operator ++() { itt_--; return *this; }
        
    //     virtual reverse_iterator operator ++(int) { // why we dont return a reference? 
    //         reverse_iterator tmp = *this;
    //         --(*this);

    //         return tmp;
    //     }     
    // };
    

    const Dty_ &at (const Kty_ &key) const {}

    Dty_ &operator [] (const Kty_ &key) const {}



    iterator begin() noexcept { }
    // reverse_iterator rbegin() noexcept {}
    const_iterator cbegin() const noexcept {}

    iterator end() noexcept {}
    // reverse_iterator rend() const noexcept {}
    const_iterator cend() const noexcept {}



    virtual bool empty() const noexcept final {
        return size() == 0;
    }

    virtual size_t size() const noexcept final {
        return size_;
    }

    virtual Nodeptr getRoot() const noexcept final {
        return root_;
    }

    virtual void clear() noexcept final {
        this->_CLEAR_SUBTREE(root_);
    }



    // O(h)
    std::pair<iterator, bool> insert (const_reference value) {
        assert (size_ < SIZE_MAX );

        auto node = root_;
        auto node_parent = root_;
        auto key = value.first;
        bool key_exists = false;  // i need it to 
        bool this_right_child = false;

        while ( node != nullptr ) {
            node_parent = node;

            if ( key > node->getKey() ) {
                node = node->getRight();
                this_right_child = true;
            }
            else if ( key == node->getKey() ) {
                key_exists = true;
                break;
            }
            else {
                node = node->getLeft();
                this_right_child = false;
            }
        }

        if (key_exists != true) { // value with the same key doens't exists 
            auto nodeptrInserting = new TreeNode<const Kty_, Dty_>(
                                                                   value,
                                                                  (size_ > 0 ? node_parent->getHeight() + 1 : 1),
                                                                   node_parent
                                                                   );
            if ( size_ > 0 ) {
                (this_right_child) ? node_parent->setRight(nodeptrInserting) : node_parent->setLeft(nodeptrInserting);
            }
            else {
                root_ = nodeptrInserting;
            }
            
            
            size_++;
            return std::make_pair(iterator(nodeptrInserting), !(key_exists));
        }

        return std::make_pair(iterator(node), !(key_exists)); // value with the same key already exists
    }

    iterator insert (const_iterator pos, const_reference value) { // TODO

    }

    void insert (std::initializer_list<Dty_> ilist) {}  // TODO
    
    std::pair<iterator, bool> insert_or_assign (const key_type &key, const mapped_type &data) {} // TODO

    iterator erase (const_iterator pos) {
        
    }

    // O(h) 

    Nodeptr _ERASE_NODE (Nodeptr nodeptrErasing) { // TODO: const_iterator // 
        // case 1: no child 
        // case 2: only child
        // case 3: two children
        
        auto nodeptrReturn = _FIND_NEXT(nodeptrErasing);

        if ( nodeptrErasing->getRight() != nullptr && nodeptrErasing->getLeft() != nullptr ) { // case 3
            nodeptrReturn = _MIN(nodeptrErasing->getRight());

            _SWAP_NODES_VALUES(nodeptrReturn, nodeptrErasing);
            _DELETE_NODE_UNCHECK(nodeptrErasing);
        }
        else if (nodeptrErasing->getRight() != nullptr || nodeptrErasing->getLeft() != nullptr) { // case 2
            auto nodeptr_child = (nodeptrErasing->getRight() != nullptr ? nodeptrErasing->getRight() : nodeptrErasing->getLeft());

            _SWAP_NODES_VALUES(nodeptrErasing, nodeptr_child);
            _DELETE_NODE_UNCHECK(nodeptrErasing);

            // nodeptrReturn = 
        }
        else { // case 1
            _DELETE_NODE_UNCHECK(nodeptrErasing); 
        } 

        

        return nodeptrReturn;
    }

    // O(h * std::ptrdiff_t(first, last))
    iterator erase (const_iterator first, const_iterator last) { // [first, last) // TODO 
    }

    // O(h + cont.count(key)) ~ O(h)
    size_t erase (const key_type &key) {

        auto nodeptrErasing = _FIND(root_, key);

        if ( nodeptrErasing != nullptr ) {
            this->erase(iterator(nodeptrErasing));
            return 1;
        }

        return 0;
    }

    void swap (BinarySearchTree &other) {
        MY_BASE::swap(this->size_, other->size_);
        MY_BASE::swap(*(this->root_), *(other->root_));
    }



    size_t count (const key_type &key) const {
        return static_cast<size_t>(contains(key));
    } // return 0 or 1

protected:


    // O(h)
    void _CLEAR_SUBTREE (Nodeptr subTreeRoot) {
        if (subTreeRoot == nullptr) { // recursion stop point 
            return;
        }
        else { // recursion base
            if (subTreeRoot->getLeft() != nullptr && subTreeRoot->getRight() != nullptr) {
                delete subTreeRoot;
                subTreeRoot = nullptr;
            }
            else { // recursion step
                _CLEAR_SUBTREE(subTreeRoot->getLeft());
                _CLEAR_SUBTREE(subTreeRoot->getRight());
            }
        }

    }


    // O(1)
    void _DELETE_NODE_UNCHECK (Nodeptr node) {
        delete node;
        node = nullptr;
    } 

    // O(1); 
    void _SWAP_NODES_VALUES (Nodeptr a, Nodeptr b) {  
        // MY_BASE::swap(*a, *b);
        
        auto tmp = *a;
        a->setValue(*b);
        b->setValue(tmp);
    }



    // O(h), h - height of the tree
    Nodeptr _FIND (const Nodeptr subTreeRoot, const Kty_ &key) const noexcept {
        if ( subTreeRoot == nullptr ) {
            return nullptr;
        }
        else if ( subTreeRoot->getKey() == key ) {
            return subTreeRoot;
        }
        else if ( subTreeRoot->getKey() > key ) {
            return _FIND(subTreeRoot->getLeft(), key);
        }
        else {
            return _FIND(subTreeRoot->getRight(), key);
        }
    }

    // O(h)
    Nodeptr _MAX (const Nodeptr subTreeRoot) const noexcept {
        // assert(root_ != nullptr); // is empty tree
        
        if ( subTreeRoot == nullptr ) { return subTreeRoot; }
        
        Nodeptr result = subTreeRoot; // TODO static or dynamic
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
    Nodeptr _MIN (const Nodeptr subTreeRoot) const noexcept {
        // assert(root_ != nullptr); // is empty tree
        
        if ( subTreeRoot == nullptr ) { return subTreeRoot; }
        
        Nodeptr result = subTreeRoot;
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

    // O(h); return firts greater; equivalent _FIND_LOWER_BOUND because of container doesn't allow store
                                // value_types with the same keys
    Nodeptr _FIND_UPPER_BOUND (Nodeptr node, const key_type &key) const {
        return _FIND_LOWER_BOUND(node, key);  
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
        
        return _FIND_UPPER_BOUND(node, key);
    }
    const_iterator upper_bound (const key_type &key) const { 
        auto node = _FIND(root_, key);
        
        return _FIND_UPPER_BOUND(node, key);
    }

    void print(Nodeptr node) {

        if (node == nullptr) {
            return;
        }

        print(node->getLeft());
        std::cout << node->getData() << " ";
        print(node->getRight());
    }


protected:
    Nodeptr  root_;
    size_t   size_;
};





int main() {
    

    //TreeNode<int> node(1);
    //std::cout << node.getData();
    
    
    // std::map<int, int>;

    BinarySearchTree<int,int> bstree;
    bstree.insert( std::make_pair<int,int>(1,1) );
    bstree.insert( std::make_pair<int,int>(9,9) );  
    bstree.insert( std::make_pair<int,int>(8,8) );  
    bstree.insert( std::make_pair<int,int>(1,1) );
    bstree.insert( std::make_pair<int,int>(2,2) );
    bstree.insert( std::make_pair<int,int>(7,7) );  
    bstree.insert( std::make_pair<int,int>(3,3) );
    bstree.insert( std::make_pair<int,int>(6,6) );  
    bstree.insert( std::make_pair<int,int>(4,4) );  
    bstree.insert( std::make_pair<int,int>(10,10) );  
    bstree.insert( std::make_pair<int,int>(3,3) );
    bstree.insert( std::make_pair<int,int>(11,11) );  
    bstree.insert( std::make_pair<int,int>(5,5) );  

    bstree.print(bstree.getRoot()); 

    // bstree.erase(1);
    // bstree.erase(6);

    std::cout << '\n';
    // bstree.print(bstree.getRoot());

     
    return 0;
}




















