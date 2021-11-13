#ifndef RBT_HPP
#define RBT_HPP

#include "../Vector.hpp"
#include <algorithm>
#include <memory>

namespace ft
{
	enum COLOR {BLACK, RED};

	template<typename value_type>
	struct Node
	{
		value_type	data;
		Node		*parent;
		Node		*left;
		Node		*right;
		COLOR		color;

		Node() : parent(nullptr), left(nullptr), right(nullptr), color(BLACK) {}
		Node (value_type v) : data(v), parent(nullptr), left(nullptr), right(nullptr), color(BLACK) {}
		~Node() {}
	};

	template<class Container, class Allocator = std::allocator<Node<typename Container::value_type> > >
	class RBTree
	{
		public :
			typedef typename Container::value_type									value_type;
			typedef typename Container::key_type									key_type;
			typedef typename Container::mapped_type									mapped_type;
			typedef typename Allocator::template rebind<Node<value_type> >::other	allocator_type;
			typedef Node<value_type>												Node;
			typedef Node*															Node_ptr;
			typedef typename Container::key_compare									key_compare;
			typedef typename Container::size_type									size_type;

		private:
			Node_ptr				root;
			Node_ptr				TNULL;
			key_compare				comp;
			allocator_type			allocator;
			size_type 				size;


			void initialize_NULL_node (Node_ptr node, Node_ptr parent)
			{
				node->data = value_type();
				node->parent = parent;
				node->left = nullptr;
				node->right = nullptr;
				node->color = BLACK;
			}

			void pre_order_helper(Node_ptr node)
			{
				if (node != TNULL)
				{
					std::cout << node->data.first << " ";
					pre_order_helper(node->left);
					pre_order_helper(node->right);
				}
			}

			void in_order_helper(Node_ptr node)
			{
				if (node != TNULL)
				{
					in_order_helper(node->left);
					std::cout << node->data.first << " ";
					in_order_helper(node->right);
				}
			}

			void post_order_helper(Node_ptr node)
			{
				if (node != TNULL)
				{
					post_order_helper(node->left);
					post_order_helper(node->right);
					std::cout << node->data.first << " ";
				}
			}

			Node_ptr search_tree_helper(Node_ptr node, key_type key)
			{
				if (node == TNULL || (!comp(key, node->data.first) && !comp(node->data.first, key)))
					return (node);
				if (comp(key, node->data.first))
					return search_tree_helper(node->left, key);
				return search_tree_helper(node->right, key);
			}
			//fix the rb tree that has been modified by the delete operation
			void fix_delete(Node_ptr x)
			{
				Node_ptr s;
				
				while (x != root && x->color == 0)
				{
					if (x == x->parent->left)
					{
						s = x->parent->right;
						//case : x's sibling s is red
						if (s->color == RED)
						{
							s->color = BLACK;
							x->parent->color = RED;
							left_rotate(x->parent);
							s = x->parent->right;
						}

						//case : x's sibling s is black and both of s's children are black
						if (s->left->color == BLACK && s->right->color == BLACK)
						{
							s->color = RED;
							x = x->parent;
						}
						else
						{
							//case : x's sibling s is black, s's left child is red and s's right child is black
							if (s->right->color == BLACK)
							{
								s->left->color = BLACK;
								s->color = RED;
								right_rotate(s);
								s = x->parent->right;
							}

							//case : x's sibling s is black and s's right child is red
							s->color = x->parent->color;
							x->parent->color = BLACK;
							s->right->color = BLACK;
							left_rotate(x->parent);
							x = root;
						}

					}
					else
					{
						s = x->parent->left;

						//case : x's sibling s is red
						if (s->color == RED)
						{
							s->color = BLACK;
							x->parent->color = RED;
							right_rotate(x->parent);
							s = x->parent->left;
						}

						//case : x's sibling s is black and both of s's children are black
						if (s->left->color == BLACK && s->right->color == BLACK)
						{
							s->color = RED;
							x = x->parent;
						}
						else
						{
							//case : x's sibling s is black, s's left child is red and s's right child is black
							if (s->left->color == BLACK)
							{
								s->right->color = BLACK;
								s->color = RED;
								left_rotate(s);
								s = x->parent->left;
							}
							//case : x's sibling s is black and s's right child is red
							s->color = x->parent->color;
							x->parent->color = BLACK;
							s->left->color = BLACK;
							right_rotate(x->parent);
							x = root;
						}
					}
				}
				x->color = BLACK;
			}

			void rb_transplant(Node_ptr u, Node_ptr v)
			{
				if (u->parent == nullptr)
					root = v;
				else if (u == u->parent->left)
					u->parent->left = v;
				else
					u->parent->right = v;
				v->parent = u->parent;
			}

			void delete_node_helper(Node_ptr node, key_type key)
			{
				//find node containing key
				Node_ptr z = TNULL;
				Node_ptr x;
				Node_ptr y;

				while (node != TNULL)
				{
					if ((!comp(key, node->data.first) && !comp(node->data.first, key)))
					{
						z = node;
					}
					if (comp(node->data.first, key)|| (!comp(key, node->data.first) && !comp(node->data.first, key)))
						node = node->right;
					else
						node = node->left;
				}

				if (z == TNULL)
				{
					std::cout << "Couldn't find the key inside the binary tree" << std::endl;
					return ;
				}
				
				size--;
				y = z;
				COLOR y_original_color = y->color;
				if (z->left == TNULL)
				{
					x = z->right;
					rb_transplant(z, z->right);
				}
				else if (z->right == TNULL)
				{
					x = z->left;
					rb_transplant(z, z->left);
				}
				else
				{
					y = minimum(z->right);
					y_original_color = y->color;
					x = y->right;
					if (y->parent == z)
						x->parent = y;
					else
					{
						rb_transplant(y, y->right);
						y->right = z->right;
						y->right->parent = y;
					}
					rb_transplant(z, y);
					y->left = z->left;
					y->left->parent = y;
					y->color = z->color;
				}
			
				allocator.destroy(z);
				allocator.deallocate(z, 1);
				if (y_original_color == BLACK)
					fix_delete(x);
			}

			void fix_insert(Node_ptr k)
			{
				Node_ptr u;
				while (k->parent->color == RED)
				{
					if (k->parent == k->parent->parent->right)
					{
						u = k->parent->parent->left; //uncle
						
						//case 1
						if (u->color == RED)
						{
							u->color = BLACK;
							k->parent->color = BLACK;
							k->parent->parent->color = RED;
							k = k->parent->parent;
						}
						else
						{
							//case 2.1
							if (k == k->parent->left)
							{
								k = k->parent;
								right_rotate(k);
							}
							else
							{
								//case 2.2
								k->parent->color = BLACK;
								k->parent->parent->color = RED;
								left_rotate(k->parent->parent);
							}
						}
					}
					else
					{
						u = k->parent->parent->right; //uncle
						//mirror case 1
						if (u->color == RED)
						{
							u->color = BLACK;
							k->parent->color = BLACK;
							k->parent->parent->color = RED;
							k = k->parent->parent;
						}
						else
						{
							//mirror case 2.1
							if (k == k->parent->right)
							{
								k = k->parent;
								left_rotate(k);
							}
							else
							{	
								k->parent->color = BLACK;
								k->parent->parent->color = RED;
								right_rotate(k->parent->parent);
							}
						}
					}
					if (k == root)
						break;
				}
				root->color = BLACK;
			}

			void print_helper(Node_ptr root, std::string indent, bool last)
			{
				if (root != TNULL)
				{
					std::cout << indent;
					if (last)
					{
						std::cout << "R----";
						indent += "     ";
					}
					else
					{
						std::cout << "L----";
						indent += "|    ";
					}
					std::string s_color = root->color ? "RED" : "BLACK";
					std::cout << root->data.first << "(" << s_color << ")" << std::endl;
					print_helper(root->left, indent, false);
					print_helper(root->right, indent, true);
				}
			}

			//compares two nodes to see if they're equal with the comp function
			bool is_equal(Node_ptr a, Node_ptr b)
			{
				return (!comp(a->data.first, b->data.first) && !comp(b->data.first, a->data.first));
			}

 
		
		public :
			
			RBTree(allocator_type alloc = allocator_type()) : allocator(alloc)
			{
				TNULL = allocator.allocate(1);
				TNULL->parent = nullptr;
				TNULL->left = nullptr;
				TNULL->right = nullptr;
				TNULL->color = BLACK;
				root = TNULL;
				size = 0;
			}
			
			RBTree(RBTree const &cpy) : comp(cpy.comp)
			{
				TNULL = allocator.allocate(1);
				TNULL->parent = nullptr;
				TNULL->left = nullptr;
				TNULL->right = nullptr;
				TNULL->color = BLACK;
				root = TNULL;
				allocator = cpy.allocator;
				*this = cpy;
			}

			void copy_tree_helper(Node_ptr node, RBTree const &rbt)
			{
				if (node == rbt.TNULL)
					return ;
				copy_tree_helper(node->left, rbt);
				copy_tree_helper(node->right, rbt);
				if (node != rbt.TNULL)
					this->insert(ft::make_pair<key_type, mapped_type>(node->data.first, node->data.second));
			}

			RBTree &operator=(RBTree const &cpy)
			{
				root = clear(root);
				copy_tree_helper(cpy.root, cpy);
				allocator = cpy.allocator;
				return (*this);
			}

			Node_ptr clear(Node_ptr t)
			{
				return (clear_helper(t));
			}

			~RBTree()
			{
				clear(root);
			}

			void set_root(Node_ptr t)
			{
				root = t;
			}

			Node_ptr clear_helper(Node_ptr node)
			{
				if (node == TNULL)
				{
					this->size = 0;
					return TNULL;
				}
				clear_helper(node->left);
				clear_helper(node->right);
				allocator.destroy(node);
				allocator.deallocate(node, 1);
				return (TNULL);
			}

			void pre_order(void)
			{
				pre_order_helper(this->root);
			}

			void in_order(void)
			{
				in_order_helper(this->root);
			}

			void post_order(void)
			{
				post_order_helper(this->root);
			}

			Node_ptr search_tree(const key_type &k)
			{
				return search_tree_helper(this->root, k);
			}

			Node_ptr minimum(Node_ptr node)
			{
				if (node == TNULL)
					return (node);
				while (node->left != TNULL)
					node = node->left;
				return (node);
			}

			Node_ptr maximum(Node_ptr node)
			{
				if (node == TNULL || node == nullptr)
					return (node);
				while (node->right != TNULL)
					node = node->right;
				return (node);
			}

			Node_ptr predecessor(Node_ptr x)
			{
				if (x == maximum(root) + 1)
					return maximum(root);
				if (x == minimum(root))
					return (minimum(root) - 1);
				if (x->left != TNULL)
					return maximum(x->left);
				Node_ptr y = x->parent;
				while (y != get_root() && y != TNULL && x == y->left)
				{
					x = y;
					y = y->parent;
				}
				return (y);
			}

			Node_ptr successor(Node_ptr x)
			{
				if (x == maximum(root))
					return (x + 1);
				if (x == minimum(root) - 1)
					return minimum(root);
				if (x->right != TNULL)
					return minimum(x->right);
				Node_ptr y = x->parent;
				while (y != TNULL && x == y->right)
				{
					x = y;
					y = y->parent;
				}
				return (y);
			}

			const Node_ptr successor(Node_ptr x) const
			{
				if (x == maximum(root))
					return (x + 1);
				if (x == minimum(root) - 1)
					return minimum(root);
				if (x == TNULL)
					return (TNULL);
				if (x->right != TNULL)
					return minimum(x->right);
				Node_ptr y = x->parent;
				while (y != TNULL && x == y->right)
				{
					x = y;
					y = y->parent;
				}
				return (y);
			}

			void left_rotate(Node_ptr x)
			{
				Node_ptr y = x->right;
				x->right = y->left;
				if (y->left != TNULL)
					y->left->parent = x;
				y->parent = x->parent;
				if (x->parent == nullptr)
					this->root = y;
				else if (x == x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;
				y->left = x;
				x->parent = y;
			}

			void right_rotate(Node_ptr x)
			{
				Node_ptr y = x->left;
				x->left = y->right;
				if (y->right != TNULL)
					y->right->parent = x;
				y->parent = x->parent;
				if (x->parent == nullptr)
					this->root = y;
				else if (x == x->parent->right)
					x->parent->right = y;
				else
					x->parent->left = y;
				y->right = x;
				x->parent = y;
			}

			//Insert in appropriate position then fix the tree
			void insert(value_type key)
			{
				Node_ptr node = allocator.allocate(1);
				allocator.construct(node, key);
				node->parent = nullptr;
				node->left = TNULL;
				node->right = TNULL;
				node->color = RED; //new node must be red

				Node_ptr y = nullptr;
				Node_ptr x = this->root;

				while (x != TNULL)
				{
					y = x;
					if (is_equal(node, x))
						return ;
					if (comp(node->data.first, x->data.first))
						x = x->left;
					else
						x = x->right;
				}
				node->parent = y;
				if (y == nullptr)
					root = node;
				else if (comp(node->data.first, y->data.first))
					y->left = node;
				else
					y->right = node;

				size++;
				if (node->parent == nullptr)
				{
					node->color = BLACK;
					return ;
				}

				if (node->parent->parent == nullptr)
					return ;
				fix_insert(node);
			}

			Node_ptr get_root(void)
			{
				return (this->root);
			}

			const Node_ptr get_root(void) const
			{
				return (this->root);
			}

			void delete_node(key_type key)
			{
				delete_node_helper(this->root, key);
			}

			void pretty_print(void)
			{
				if (root)
					print_helper(this->root, "", true);
			}

			Node_ptr get_nullnode(void)
			{
				return TNULL;
			}
			

			size_type get_size(void)
			{
				return (size);
			}
			size_type get_size(void) const
			{
				return (size);
			}
	};
}

#endif