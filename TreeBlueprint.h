#ifndef TREEBLUEPRINT_H
#define TREEBLUEPRINT_H

#include <memory>

template <class T>
class TreeBlueprint {

	template <class IterType>
	class TreeIterator;

public:
	// type definitions:
	using value_type = T;
	using iterator = TreeIterator<value_type>;
	using const_iterator = TreeIterator<const value_type>;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;


private:

	// tree node definition;
	class TreeNode {
	private:
		value_type data;
		/*IMPLEMENT ME!!*/
	public:
		value_type& access_value() const { return this->data; }
	};

	std::unique_ptr<TreeNode> root = nullptr;
	size_t _size = 0;

	template <class IterType>
	class TreeIterator {

	public:
		// iterator traits:
		using difference_type = std::ptrdiff_t;
		using value_type = IterType;
		using pointer = value_type *;
		using reference = value_type &;
		using iterator_category = std::bidirectional_iterator_tag;
		using node_pointer = TreeNode*;


	private:

		node_pointer root_iter;
		node_pointer iter;

	public:

		// iterator constructors:
		TreeIterator() : iter(node_pointer()), root_iter(node_pointer()) { }
		explicit TreeIterator(const std::unique_ptr<TreeNode>& i, const std::unique_ptr<TreeNode>& root_i)
			: iter(i.get()), root_iter(root_i.get()) { }
		TreeIterator(const TreeIterator& other) : iter(other.iter), root_iter(other.root_iter) { }

		// iterator access:
		node_pointer get_iter() const { return this->iter; }

		// iterator operator overloads:
		TreeIterator& operator=(const TreeIterator& other) {
			this->iter = other.iter;
			return *this;
		}
		reference operator*() const { return iter->access_value(); }
		pointer operator->() const { return &(operator*()); }
		TreeIterator& operator++() { /*IMPLEMENT ME!!*/ return *this; }		
		TreeIterator operator++(int) {
			TreeIterator copy(*this);
			operator++();
			return copy;
		}
		TreeIterator& operator--() { /*IMPLEMENT ME!!*/ return *this; }
		TreeIterator operator--(int) {
			TreeIterator copy(*this);
			operator--();
			return copy;
			;
		}

		// iterator comparison operators:
		friend bool operator==(const TreeIterator& lhs, const TreeIterator& rhs) {
			return (lhs.iter == rhs.iter);
		}
		friend bool operator!=(const TreeIterator& lhs, const TreeIterator& rhs) {
			return !operator==(lhs, rhs);
		}
	};


	//---------------------------------------------------------------------------------------------------------

public:

	// constructors:
	//explicit TreeBlueprint(const Compare& comp = Compare()); // default constructor (custom compare)
	explicit TreeBlueprint() { } // default constructor
	template <class InputIterator>
	TreeBlueprint(InputIterator first, InputIterator last); // iterator constructor
	TreeBlueprint(const TreeBlueprint&); // copy constructor
	TreeBlueprint(TreeBlueprint&&); // move constructor
	//TreeBlueprint(initializer_list<value_type>, const Compare & = Compare()); // initializer_list constructor


	// destructor:
	~TreeBlueprint();


	// assignment operators:
	TreeBlueprint& operator=(const TreeBlueprint& other); // copy assignment
	TreeBlueprint& operator=(TreeBlueprint&& x); // move assignment
	//TreeBlueprint& operator=(initializer_list<value_type>); // initializer_list assignment


	// iterators:
	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;

	reverse_iterator rbegin();
	const_reverse_iterator rbegin() const;
	reverse_iterator rend();
	const_reverse_iterator rend() const;

	const_iterator cbegin();
	const_iterator cend();
	const_reverse_iterator crbegin() const;
	const_reverse_iterator crend() const;


	// capacity:
	bool empty() const; // to check if tree is empty
	size_t size() const; // return number of elements in the tree
	size_t height() const; // return the height of the tree


	// root access:
	TreeNode* get_root() const; // to access root of the tree


	// emplacement:
	template <class...	 Args>
	std::pair<iterator, bool> emplace(Args&& ... args); // construct and insert an element
	template <class... Args>
	iterator emplace_at(const_iterator position, Args&& ... args); // construct and insert an element in a specified location

	// insertion:
	std::pair<iterator, bool> insert(const value_type& x); // insert value into tree
	std::pair<iterator, bool> insert_at(const value_type& x, const value_type& parent); // insert value into tree in a specified location (parent)
	iterator insert_at(const_iterator position, const value_type& x); // insert value into tree in a specified location (iterator)
	template <class InputIterator>
	void insert(InputIterator first, InputIterator last); // iterator insertion
	//void insert(initializer_list<value_type>); // initializer_list insertion

	// erasure:
	iterator erase(const_iterator position); // erase iterator location (and subtree?)
	size_t erase(const value_type& x); // erase value location (and subtree?)
	iterator erase(const_iterator first, const_iterator last); // erase between iterators
	void swap(TreeBlueprint& second); // swap this tree with second tree
	void clear(); // clear tree


	// operations:
	iterator find(const value_type& value); // to find the first occurrence of value using iterator (return this->end() if no luck)
	const_iterator find(const value_type& value) const; // const version of find
	size_t count(const value_type& value) const; // to check number of specific elements in tree
	bool has(const value_type& value); // check if element in tree (using this->find())

};


// comparison operator overloads:
template <class T>
bool operator==(const TreeBlueprint<T>& lhs, const TreeBlueprint<T>& rhs);

template <class T>
bool operator!=(const TreeBlueprint<T>& lhs, const TreeBlueprint<T>& rhs);

template <class T>
bool operator<(const TreeBlueprint<T>& lhs, const TreeBlueprint<T>& rhs);

template <class T>
bool operator<=(const TreeBlueprint<T>& lhs, const TreeBlueprint<T>& rhs);

template <class T>
bool operator>(const TreeBlueprint<T>& lhs, const TreeBlueprint<T>& rhs);

template <class T>
bool operator>=(const TreeBlueprint<T>& lhs, const TreeBlueprint<T>& rhs);


// swap overload:
template <class T>
void swap(TreeBlueprint<T>& lhs, TreeBlueprint<T>& rhs);


// outputstream overload:
template <class T>
std::ostream& operator<<(std::ostream& os, const TreeBlueprint<T>& tree);

#include "TreeBlueprint.tpp"

#endif