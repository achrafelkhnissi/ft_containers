#ifndef FT_CONTAINERS_RED_BLACK_TREE_HPP
#define FT_CONTAINERS_RED_BLACK_TREE_HPP

#include <iostream>
#include "iterator_traits.hpp"

namespace ft
{
    enum color {RED, BLACK};
    enum side {LEFT, RIGHT};

    template< class T, class Compare, class Allocator = std::allocator<T> >
    class red_black_tree
    {
    private:
        struct rbt_node;
        typedef rbt_node* _node;

    public:
        typedef T value_type;
        typedef Compare key_compare;
        typedef Allocator allocator_type;
        typedef std::allocator<rbt_node> node_allocator; // todo: which allocator to use?
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef typename allocator_type::difference_type difference_type;
        typedef typename allocator_type::size_type size_type;

        typedef tree_iterator<value_type, _node> iterator;
        typedef tree_iterator<const value_type, _node> const_iterator;
        typedef tree_reverse_iterator<value_type, _node> reverse_iterator;
        typedef tree_reverse_iterator<const value_type, _node> const_reverse_iterator;

        template<class, class, class, class> friend class map;


    private:
        struct rbt_node
        {
            bool is_nil;
//            bool is_root;
//            bool is_left;
            value_type value; // pointer?
            value_type* value_ptr;
//            pointer data;
            color color;

            _node parent;
            _node left;
            _node right;
            _node prev;
            _node next;

            _node grandparent() const { return parent->parent; }
            _node sibling() const { return (this == parent->left) ? parent->right : parent->left; }
            _node uncle() const { return parent->sibling(); }
            side side() const { return (this == parent->left) ? LEFT : RIGHT; }
            bool is_leaf() const { return (left->is_nil && right->is_nil); }
            bool is_left() const { return (this == parent->left); }
            bool is_right() const { return (this == parent->right); }
            bool has_left() const { return !left->is_nil; }
            bool has_right() const { return !right->is_nil; }
            bool has_both() const { return has_left() && has_right(); }
            bool has_one() const { return has_left() || has_right(); }
            bool has_no() const { return !has_left() && !has_right(); }
            bool is_root() const { return parent->is_nil; }
            bool is_red() const { return color == RED; }
            bool is_black() const { return color == BLACK; }

            _node successor() const {
                _node _tmp_ = this;
                _node _parent_ = _tmp_->parent;
                if (_tmp_->has_right()) {
                    _tmp_ = _tmp_->right;
                    while (!_tmp_->has_left())
                        _tmp_ = _tmp_->left;
                    return _tmp_;
                } else {
                    _parent_ = _tmp_->parent;
                    while (!_tmp_->is_root() && _tmp_->is_right()) {
                        _tmp_ = _parent_;
                        _parent_ = _parent_->parent;
                    }
                }
                return _parent_;
            }

            _node predecessor() const {
                _node _tmp_ = this;
                _node _parent_;
                if (_tmp_->has_left()) {
                    _tmp_ = _tmp_->left;
                    while (!_tmp_->has_right())
                        _tmp_ = _tmp_->right;
                    return _tmp_;
                } else {
                    _parent_ = _tmp_->parent;
                    while (!_tmp_->is_root() && _tmp_->is_left()) {
                        _tmp_ = _parent_;
                        _parent_ = _parent_->parent;
                    }
                }
                return _parent_;
            }

        }; /* struct rbt_node */

    private:
        _node  NIL;

        _node  _root;
        size_type _size;
        node_allocator  _allocator;
        allocator_type _value_allocator;

        key_compare _comp;

        template<class, class, class, class> friend class tree_iterator;


    public:

        explicit red_black_tree(const key_compare& cmp) : _comp(cmp) {
            NIL = _allocator.allocate(1);
            _allocator.construct(NIL, rbt_node());
            NIL->value = _value_allocator.allocate(1); // todo: value or value_ptr?
            _value_allocator.construct(NIL->value, value_type());
            NIL->is_nil = true;
            NIL->color = BLACK;
            NIL->parent = nullptr;
            NIL->left = nullptr;
            NIL->right = nullptr;
            NIL->prev = nullptr;
            NIL->next = nullptr;
            _root = NIL;
        }

        explicit red_black_tree(const key_compare& comp = key_compare(),
                                const allocator_type& alloc = allocator_type())
                : _root(NIL), _size(0), _allocator(), _value_allocator(alloc), _comp(comp)
        {
            NIL = _allocator.allocate(1);
            _allocator.construct(NIL, rbt_node());
            NIL->value = _value_allocator.allocate(1); // todo: value or value_ptr?
            NIL->is_nil = true;
            NIL->color = BLACK;
            NIL->parent = nullptr;
            NIL->left = nullptr;
            NIL->right = nullptr;
            NIL->prev = nullptr;
            _root = NIL;
        }

        ~red_black_tree() {
//            clear(); // todo: fix
            _allocator.destroy(NIL);
            _allocator.deallocate(NIL, 1);
        }

        _node new_node(const value_type& value) { // todo: check if you need const here
            _node node = _allocator.allocate(1);
            _allocator.construct(node, rbt_node());
            node->value = _value_allocator.allocate(1);
            _value_allocator.construct(node->value, value);
            node->is_nil = false;
            node->color = RED;
            node->parent = NIL;
            node->left = NIL;
            node->right = NIL;
            node->prev = nullptr;
            node->next = nullptr;
            return node;
        }

        red_black_tree(const red_black_tree& other) {
            *this = other;
        }

        red_black_tree& operator=(const red_black_tree& other) {
            if (this != &other) {
//                clear(); // todo: fix
                _comp = other._comp;
                _allocator = other._allocator;
                _value_allocator = other._value_allocator;
                _root = copy_tree(other._root); // todo: fix
            }
            return *this;
        }

        // todo: check if it works
        _node copy_tree(_node node) {
            if (node->is_nil)
                return NIL;
            _node new_node = _allocator.allocate(1);
            _allocator.construct(new_node, rbt_node());
            new_node->value = _value_allocator.allocate(1);
            _value_allocator.construct(new_node->value, node->value);
            new_node->is_nil = false;
            new_node->color = node->color;
            new_node->parent = copy_tree(node->parent);
            new_node->left = copy_tree(node->left);
            new_node->right = copy_tree(node->right);
            new_node->prev = copy_tree(node->prev);
            new_node->next = copy_tree(node->next);
            return new_node;
        }

        _node min(_node node) const {
            while (node && node != NIL && node->left && node->left != NIL)
                node = node->left;
            return node;
        }

        _node max(_node node) const {
            while (node && node != NIL && node->right && node->right != NIL)
                node = node->right;
            return node;
        }

        _node find(const value_type& key) const {
            _node node = _root;
            while (node && node != NIL) {
                if (_comp(key, node->value.first))
                    node = node->left;
                else if (_comp(node->value.first, key))
                    node = node->right;
                else
                    return node;
            }
            return NIL;
        }

        _node lower_bound(const value_type& key) const {
            _node node = _root;
            _node lower_bound = NIL;
            while (node && node != NIL) {
                if (_comp(key, node->value.first)) {
                    lower_bound = node;
                    node = node->left;
                } else if (_comp(node->value.first, key))
                    node = node->right;
                else
                    return node;
            }
            return lower_bound;
        }

        _node upper_bound(const value_type& key) const {
            _node node = _root;
            _node upper_bound = NIL;
            while (node && node != NIL) {
                if (_comp(key, node->value.first))
                    node = node->left;
                else if (_comp(node->value.first, key)) {
                    upper_bound = node;
                    node = node->right;
                } else
                    return node;
            }
            return upper_bound;
        }

        std::pair<_node, _node> equal_range(const value_type& key) const {
            return std::make_pair(lower_bound(key), upper_bound(key));
        }

        size_type count(const value_type& key) const {
            return (find(key) != NIL);
        }

        _node successor(_node node) const {
            if (node->right && node->right != NIL)
                return min(node->right);
            _node parent = node->parent;
            while (parent && parent != NIL && node->side() == RIGHT) {
                node = parent;
                parent = parent->parent;
            }
//            return parent;
            return (parent == nullptr) ? NIL : parent;
        }

        _node predecessor(_node node) const {
            if (node->left && node->left != NIL)
                return max(node->left);
            _node parent = node->parent;
            while (parent && parent != NIL && node->side() == LEFT) {
                node = parent;
                parent = parent->parent;
            }
//            return parent;
            return (parent == nullptr) ? NIL : parent;
        }

     // TODO: update prev and next of each inserted node
		void insert(const value_type& key) {
			_node z = newNode(key);
			_node x = _root;
			_node y = NIL;
			while ( x != NIL) {        // descend until reaching a leaf
				y = x;
                if ( _comp(*(z->key),  *(x->key)) == true ) {
                    x = x->left;
                } else {
                    x = x->right;
                }
			}
			z->parent = y;                  // found the location - insert z with parent y
			if ( y == NIL) {
				_root = z;                   // Tree was empty.

			} else if ( _comp(*(z->key), *(y->key) ) ) {
				y->left = z;
			} else {
				y->right = z;
			}
            z->next = successor(z);
            z->prev = predecessor(z);

            z->next->prev = z; // successor(z)->prev = z
            z->prev->next = z; // predeccessor(z)->next = z;
            NIL->prev = max(_root);
            NIL->next = nullptr;
			_size++;
            /*
             * From page: 195
             *  z->left = NIL;
             *  z->right = NIL;
             *  z->color = RED;
             */
            insert_fixup(z);
		}

        	/*
		 * @disc: "The overall strategy for deleting a node z from a binary search tree T has three basic cases:"
		 *      * “If z has no left child, then as in part (a) of the figure, replace z by its right child,
		 *      which may or may not be NIL. When z’s right child is NIL, this case deals with the situation in which z
		 *      has no children. When z’s right child is non-NIL, this case handles the situation in which z has just
		 *      one child, which is its right child”
		 *      * “Otherwise, if z has just one child, then that child is a left child. replace z by its left child.”
		 *      * “Otherwise, z has both a left and a right child. Find z’s successor y, which lies in z’s right
		 *      subtree and has no left child. Splice node y out of its current location and replace z by y in the tree.
		 *      How to do so depend on whether y is z’s right child:”
		 *              * “If y is z’s right child, then replace z by y, leaving y’s right child alone.”
		 *              * “Otherwise, y lies within z’s right subtree but is not z’s right child. In this case,
		 *              first replace y by its own right child, and then replace z by y.”
		 */

        // TODO: update prev and next after deleting a node
		void delete_node( const value_type& key ) {
            _node z = this->search(key);                           // Node to be deleted TODO: check with a node that doesn't exist
            _node y = z;
            _node x = NIL;

            if (z != NIL){
                z->prev->next = x->next;
                z->next->prev = x->prev;
            }
            enum color yOriginalColor = y->color;

            /*
             * “handle the case in which node z has no left child”
             */
            if (z->left == NIL) {
                x = z->right;
                x->parent = z->parent;
                _transplant(z, z->right);              // replace z by its right child
            } else if (z->right == NIL) {
                /*
                 * “handle the case in which z has a left child but no right child ”
                 */
                x = z->left;
                x->parent = z->parent;
                _transplant(z, z->left);               // replace z by its left child
            /*
             * “handle the case in which z has a left child but no right child ”
             */
            }else {
				/*
				 * “finds node y, which is the successor of z. Because z has a nonempty right subtree,
				 * its successor must be the node in that subtree with the smallest key”
				 */
				y = this->min(z->right);             // y is z's successor
                yOriginalColor = y->color;
                x = y->right;
                x->parent = y->parent; // TODO: later on remove this an uncomment line 399-400-401
				/*
				 * “replace y as a child of its parent by y’s right child and make z’s right child
				 * become y’s right child instead.”
				 */
				if ( y != z->right ) {                          // is y farther down the tree?
					_transplant(y, y->right);        // replace y by its right child
					y->right = z->right;                    // z's right child becomes-
					y->right->parent = y;               // -y's right child
//                    x->parent = y->parent;
				} //else
                   // x->parent = y; //

				/*
				 * “replace z as a child of its parent by y and replace y’s left child by z’s left child. ”
				 */
				_transplant(z, y);                       // replace z by its successor y
				y->left = z->left;                              // and give z's left child to y
				y->left->parent = y;                            // which had no left child.
                y->color = z->color;
			}

            _value_allocator.destroy(z->key);
            _value_allocator.deallocate(z->key, 1);
			_allocator.destroy(z);
			_allocator.deallocate(z, 1);
			z = nullptr;

            NIL->prev = max(_root);
            NIL->next = nullptr;
			_size--;

            if ( yOriginalColor == BLACK )                      // If any red-black violations occurred,
                delete_fixup(x);                                //      correct them.
		}

        const_iterator search(const value_type& key) const {
            _node node = find(key);
            return (node == NIL) ? NIL : const_iterator(node);
        }

        void clear() {
            if (_root->is_nil)
                return;
            clear_tree(_root);
            _root = NIL;
            _size = 0;
        }

        void clear_tree(_node node) {
            if (node->left != NIL)
                clear_tree(node->left);
            if (node->right != NIL)
                clear_tree(node->right);
            _value_allocator.destroy(node->key);
            _value_allocator.deallocate(node->key, 1);
            _allocator.destroy(node);
            _allocator.deallocate(node, 1);
        }

        void print_tree() const {
            if (_root)
                _print_tree_helper(_root, "", true);
        }

        void _print_tree_helper(_node node, std::string indent, bool last) const {
            if (node != NIL) {
                std::cout << indent;
                if (last) {
                    std::cout << "R----";
                    indent += "     ";
                } else {
                    std::cout << "L----";
                    indent += "|    ";
                }
                std::string sColor = node->color == RED ? "RED" : "BLACK";
                std::cout << node->key << "(" << sColor << ")" << std::endl;
                _print_tree_helper(node->left, indent, false);
                _print_tree_helper(node->right, indent, true);
            }
        }

        iterator begin() { return iterator(min(_root)); }
        const_iterator begin() const { return const_iterator(min(_root)); }
        const_iterator cbegin() const { return const_iterator(min(_root)); }

        iterator end() { return iterator(NIL); }
        const_iterator end() const { return const_iterator(NIL); }
        const_iterator cend() const { return const_iterator(NIL); }


    private:

        void insert_fixup(_node z) {
            _node y = z->uncle();

            // case 1: z's uncle is red
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->grandparent()->color = RED;
                z = z->grandparent();
            } else {
                if (z->side() != z->parent->side()) {
                    z = z->parent;
                    z->side() == LEFT ? left_rotate(z) : right_rotate(z);
                }

                z->parent->color = BLACK;
                z->grandparent()->color = RED;
                z->grandparent()->side() == LEFT ? right_rotate(z->grandparent()) : left_rotate(z->grandparent());
            }
            _root->color = BLACK;
        }

        void delete_fixup(_node x) {
            while (x != _root && x->color == BLACK) {
                if (x->side() == LEFT) {
                    _node w = x->sibling();
                    if (w->color == RED) {
                        w->color = BLACK;
                        x->parent->color = RED;
                        left_rotate(x->parent);
                        w = x->sibling(); // aka x->parent->right
                    }
                    if (w->left->color == BLACK && w->right->color == BLACK) {
                        w->color = RED;
                        x = x->parent;
                    } else {
                        if (w->right->color == BLACK) {
                            w->left->color = BLACK;
                            w->color = RED;
                            right_rotate(w);
                            w = x->parent->right;
                        }
                        w->color = x->parent->color;
                        x->parent->color = BLACK;
                        w->right->color = BLACK;
                        left_rotate(x->parent);
                        x = _root;
                    }
                } else {
                    _node w = x->parent->left;
                    if (w->color == RED) {
                        w->color = BLACK;
                        x->parent->color = RED;
                        right_rotate(x->parent);
                        w = x->parent->left;
                    }
                    if (w->right->color == BLACK && w->left->color == BLACK) {
                        w->color = RED;
                        x = x->parent;
                    } else {
                        if (w->left->color == BLACK) {
                            w->right->color = BLACK;
                            w->color = RED;
                            left_rotate(w);
                            w = x->parent->left;
                        }
                        w->color = x->parent->color;
                        x->parent->color = BLACK;
                        w->left->color = BLACK;
                        right_rotate(x->parent);
                        x = _root;
                    }
                }
            }
            x->color = BLACK;
        }

        void in_order(const _node root) const {
            if (root != NIL) {
                in_order(root->left);
                std::cout << "Key: " << root->key << " " << std::endl;
                in_order(root->right);
            }
        }

        void _transplant(_node& u, _node& v) {
            if (u->parent == NIL)
                _root = v;
            else if (u->side() == LEFT)
                u->parent->left = v;
            else
                u->parent->right = v;
            if (v != NIL) // todo: why
                v->parent = u->parent;
        }

        void left_rotate( const _node& x ) {
             /*
             *      x.p
             *       |
             *       x
             *      | \
             *    x.l  y
             *        | \
             *      y.l  y.r
             *
             */
             _node y = x->right;
             x->right = y->left;
             if ( y->left != NIL )
                y->left->parent = x;
             y->parent = x->parent;
             if (x->parent == NIL)
                _root = y;
             else if (x->position() == LEFT)
                x->parent->left = y;
             else
                x->parent->right = y;
             y->left = x;
             x->parent = y;
        }

        void right_rotate( const _node& y ) {
            /*
            *        y.p
            *         |
            *         y
            *        | \
            *       x   y.r
            *      | \
            *    x.l  x.r
            *
            */
            _node x = y->left;
            y->left = x->right;
            if (x->right != NIL)
                x->right->parent = y;
            x->parent = y->parent;
            if (y->parent == NIL)
                _root = x;
            else if (y->position() == RIGHT)
                y->parent->right = x;
            else
                y->parent->left = x;
            x->right = y;
            y->parent = x;
        }

        void _printHelper(const _node& root, std::string indent, bool last) {
          if ( root != NIL ) { std::cout << indent;
            if ( last ) { std::cout<<"R----> "; indent += "     "; }
            else { std::cout<<"L----> "; indent += "|      "; }

            std::string sColor = root->color == RED ?": 🔴 ":": ⚫ ";
            std::cout<< root->key->first << " - " << root->key->second << sColor <<std::endl;
            _printHelper(root->left, indent, false);
            _printHelper(root->right, indent, true);
          }
        }

    }; /* class red_black_tree */

} /* namespace ft */

#endif //FT_CONTAINERS_RED_BLACK_TREE_HPP
