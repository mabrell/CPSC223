/*
 * Filename: BSTNode.cpp
 * Contains: Implementation of Nodes for CPSC223
 * Part of: Homework assignment "Trees" for CPSC 223
 * Author: Mason Abrell
 */

#include "BSTNode.h"
#include <cassert>
#include <algorithm>
#include <string>

/**
 * A pseudo-assert macro that immediately returns from the enclosing function
 *  if e is false.
 */
#define ABORT_UNLESS(e) \
    if (!(e))           \
    {                   \
        return;         \
    }

/**
 * This function is implemented for you, for your convenience.
 *
 * Input: Node node - the node to decorate
 * Returns: the decorator to print with this node using its to_string function.
 *      The decorator is either nothing, '*', 'r', or 'R' (computed as node is
 *      BLACK with count <=1, BLACK with count >1, RED with count =1, or RED
 *      with count >1).
 */
std::string decorator_string(const BSTNode *node)
{
    std::string dec = "";
    if (node && node->node_height() >= 0)
    {
        if (node->color == BSTNode::Color::RED)
        {
            if (node->count > 1)
            {
                dec = "R";
            }
            else
            {
                dec = "r";
            }
        }
        else
        {
            if (node->count > 1)
            {
                dec = "*";
            }
        }
    }
    return dec;
}

/**
 * This function is implemented for you, for your convenience.
 *
 * Input: Node node - the node to get the value label for
 * Returns: node's data as a string, or empty_string if node is an empty tree.
 */
std::string value_string(const BSTNode *node)
{
    std::string value = "";
    if (node && node->node_height() >= 0)
    {
        value = std::to_string(node->data);
    }
    return value;
}

/**
 * This function is implemented for you, for your conveninence.
 *
 * Input: Node a
 *        Node b
 * Returns: N/A
 * Does: Swaps the colors of Nodes a and b.
 * Assumes: a and b are both non-null
 */
void swap_colors(BSTNode *a, BSTNode *b)
{
    BSTNode::Color t = a->color;
    a->color = b->color;
    b->color = t;
}

/**
 * This function is implemented for you, for your convenience.
 *
 * It is implemented in two different ways (one of them commented out):
 *    - The commented-out version makes explicit that LEFT is the opposite of
 *      RIGHT, and that ROOT has no opposite
 *    - The uncommented version uses the fact that enum values in C++ are given
 *      integer values in increasing order starting at 0 and can be implicitly
 *      converted into an int. Since the Direction enum is defined in order
 *      LEFT, ROOT, RIGHT, the values are LEFT=0, ROOT=1, RIGHT=2.
 * Both exhibit constant time and space complexity so are asymptotically
 *  equivalent.
 *
 * Input: Direction dir
 * Returns: the opposite of dir, or ROOT if dir is ROOT.
 */
BSTNode::Direction opposite_direction(BSTNode::Direction dir)
{
    // BSTNode::Direction opp = dir;
    // if (dir == BSTNode::Direction::LEFT)
    // {
    //     opp = BSTNode::Direction::RIGHT;
    // }
    // else if (dir == BSTNode::Direction::RIGHT)
    // {
    //     opp = BSTNode::Direction::LEFT;
    // }
    // return opp;
    return BSTNode::Direction(BSTNode::Direction::RIGHT - dir);
}

/*
 * These BSTNode constructors use intializer lists. They are complete and you
 *  may not modify them.
 *
 * More info here: https://en.cppreference.com/w/cpp/language/constructor
 */
BSTNode::BSTNode() : count(0), height(-1), color(BLACK),
                     left(nullptr), right(nullptr), parent(nullptr) {}
BSTNode::BSTNode(int data)
    : data(data), count(1), height(0), color(BLACK),
      left(new BSTNode()), right(new BSTNode()), parent(nullptr) {}


void BSTNode::make_empty() //Here we empty out the node's pointers and data
{
	if ((left != nullptr))
	{
		delete(left); //Note: When called in the destructor, these are recursive
	}
	if (right != nullptr)
	{
		delete(right);
	}
	if(parent != nullptr)
	{
		if (this == parent->left)
		{
			parent->left = nullptr;
		}
		if (this == parent->right) 
		{
			parent->right = nullptr;
		}
	}
	
	this->left = nullptr;
	this->right = nullptr;
	this->parent = nullptr;
	this->color = BLACK;
	this->count = 0;
	this->data = 0;
}

/*
 * TODO: The BSTNode copy constructor is incomplete. You must complete it. You
 *  may use an initializer list, or you may write a traditional constructor
 *  function, or both.
 */
BSTNode::BSTNode(const BSTNode &other)
{

	this->data = other.data; //Here, each static value is initialized
	this->count = other.count;
	this->height = other.height;
	this->color = other.color;
	this->parent = nullptr;
	if (!other.left->is_empty()) //Here, nodes are recursively copied
	{
		BSTNode* left_node = new BSTNode(*other.left);
		left_node->parent = this;
		this->left = left_node;
	}
	else
	{
		BSTNode* baby_left = new BSTNode();
		baby_left->parent = this;
		this->left = baby_left;
	}
	if (!other.right->is_empty())
	{
		BSTNode* right_node = new BSTNode(*other.right);
		right_node->parent = this;
		this->right = right_node;
	}
	else
	{
		BSTNode* baby_right = new BSTNode();
		baby_right->parent = this;
		this->right = baby_right;
	}

}

BSTNode::~BSTNode()
{
	if ((parent == nullptr) && (left == nullptr) && (right ==nullptr))
	{
		return; //Protects already-dead nodes from getting double-freed
	}
	else
	{
		this->make_empty();
	}
	
}

std::string BSTNode::to_string() const
{
    return value_string(this) + decorator_string(this);
}

const BSTNode *BSTNode::minimum_value() const
{
	bool value_found = false;
	const BSTNode* tempvalue;
	tempvalue = this;
	while (value_found == false)
	{
		if (tempvalue->left->is_empty())  
		//Iterates under assumption of BST invariance
		{
			value_found = true;
			return tempvalue;
		}
		else
		{
			tempvalue = tempvalue->left;
		}
	}
    return this;
}

const BSTNode *BSTNode::maximum_value() const
{
	bool value_found = false;
	const BSTNode* tempvalue;
	tempvalue = this;
	while (value_found == false)
	{
		if (tempvalue->right->is_empty())
		{
			value_found = true;
			return tempvalue;
		}
		else
		{
			tempvalue = tempvalue->right;
		}
	}
    return this;
}

const BSTNode *BSTNode::search(int value) const
{
	if (this->data == value)
	{
		return this;
	}
	bool value_found = false;
	int total_nodes = this->node_count();
	const BSTNode* tempvalue;
	tempvalue = this;
	while (value_found == false)
	{		
		bool shifted_down = false;
		if (tempvalue->height == -1)
		{
			return tempvalue;
		}
		if (tempvalue->data == value)
		{
			return tempvalue;
		}
		if ((tempvalue->data > value) && (shifted_down == false))
		{
			if (tempvalue->left->is_empty())
			{
				return tempvalue->left;
			}
			else
			{
				tempvalue = tempvalue->left;
				shifted_down = true;
			}
		}

		if ((tempvalue->data < value) && (shifted_down == false))
		{
			if (tempvalue->right->is_empty())
			{
				return tempvalue->right;
			}
			else
			{
				tempvalue = tempvalue->right;
				shifted_down = true;
			}
		}
		total_nodes--; 
		//Notes when full tree has been searched, returns an empty node if so
		if (total_nodes < 0)
		{
			return new BSTNode();
		}
		
	}
	
    return new BSTNode();
}

BSTNode *BSTNode::insert(int value)
{
	int left_height;
	int right_height;

	if (this->is_empty()) //For if this is the first node in the tree
	{
		this->data = value;
		this->count++;
		BSTNode* left_baby = new BSTNode(); //creating baby nodes for root
		BSTNode* right_baby = new BSTNode();
		this->right = right_baby;
		this->left = left_baby;
		this->height = 0;
		return this;
	}
	
	if (this->data == value) //Adds one to count for duplicate vlues
	{
		this->count++;
		return this;
	}
	BSTNode* novel = new BSTNode(value);
	if (this->data > value)
	{
		if (this->left->is_empty())
		{
			delete(this->left);
			this->set_child(LEFT, novel);
		}
		else
		{
			delete(novel);
			this->left = this->left->insert(value);
		}
	}

	if (this->data < value)
	{
		if (this->right->is_empty())
		{
			delete(this->right);
			this->set_child(RIGHT, novel);
		}
		else
		{
			delete(novel);
			this->right = this->right->insert(value);
		}
	}
	//Here we calculate the height of the current node and set it:
	left_height = this->left->height;
	right_height = this->right->height;
	if(left_height >= right_height)
	{
		this->height = left_height + 1;
	}
	if (left_height < right_height)
	{
		this->height = right_height + 1;
	}
    return this;
}

BSTNode *BSTNode::avl_insert(int value) //Quite simple, functionality in balance
{

    /********************************
     ***** BST Insertion Begins *****
     ********************************/

    this->insert(value);

    /********************************
     ****** BST Insertion Ends ******
     ********************************/

    /********************************
     **** AVL Maintenance Begins ****
     ********************************/

    BSTNode* temp = this->avl_balance();

    /********************************
     ***** AVL Maintenance Ends *****
     ********************************/
    return temp;
}

BSTNode *BSTNode::rb_insert(int value)
{

    /********************************
     ***** BST Insertion Begins *****
     ********************************/
	bool duplicate = false;
	const BSTNode* target = this->search(value);
	if (!target->is_empty())
	{
		duplicate = true;
	}
    this->insert(value);
	
	if (duplicate) //returns and skips all correcting stuff if a duplicate
	{
		return this;
	}

	target = this->search(value);
	
	//Here I sneakily get around the const by going to the parent and back down

	if ((target->parent != nullptr))
	{
		if (target->parent->left == target)
		{
			BSTNode* sneaky_temp = target->parent;
			sneaky_temp->left->color = RED;
		}
		if (target->parent->right == target)
		{
			BSTNode* sneaky_temp = target->parent;
			sneaky_temp->right->color = RED;
		}
	}
	
    /********************************
     ****** BST Insertion Ends ******
     ********************************/

    /********************************
     ***** RB Maintenance Begins ****
     ********************************/

	
	if (target->parent != nullptr)
	{
		if(target->parent->color == RED) //check for red-red violation
		{
			if(target->parent->parent != nullptr)
			{
				target->parent->parent->rb_eliminate_red_red_violation();
			}
		}
	}

    /********************************
     ****** RB Maintenance Ends *****
     ********************************/
	
	BSTNode* height_temp = target->parent;
	while (height_temp != nullptr)
		{
			height_temp->make_locally_consistent();
			height_temp = height_temp->parent;
		}
    return this;
}

BSTNode *BSTNode::remove(int value)
{
	BSTNode* target = (BSTNode*) this->search(value);	
	if (target->is_empty())
	{
		return target;
	}
	
	//Takes care of the case in which there is multiplicity at a node
	if (target->count != 1)
	{
		target->count = target->count - 1;
		return this;
	}
	int target_direction = 0;
	if (target->parent != nullptr)
	{
		//Here, -1 means left, 1 means right, 0 means no parent
		if (target->parent->left ==  target)
		{
			target_direction = -1;
		}
		if (target->parent->right == target)
		{
			target_direction = 1;
		}	
	}
	
	//This denotes the state of the children, with child count being 3 if
	//the only child is on the left, child_count = 1, if the only child is on
	//the right, child_count = 2, and if it has two children then
	//child_count = 3
	int child_count = 0;
	if (!target->left->is_empty())
	{
		child_count = child_count + 1;
	}
	if (!target->right->is_empty())
	{
		child_count = child_count + 2;
	}

	//This takes care of cases where the target is a leaf
	if ((target->right->is_empty()) && (target->left->is_empty()))
	{
		delete(target->right);
		if (target_direction != 0)
		{
			if (target_direction == -1)
			{
				target->parent->left = target->left;
				target->left->parent = target->parent;
			}
			if (target_direction == 1)
			{
				target->parent->right = target->left;
				target->left->parent = target->parent;
			}
		}
		target->parent = nullptr;
		target->right = nullptr;
		BSTNode* height_temp = target->left;
		target->left = nullptr;
		while (height_temp->parent != nullptr) //Ensures heights are correct
		{
			height_temp->make_locally_consistent();
			height_temp = height_temp->parent;
		}
		height_temp->make_locally_consistent();
		delete(target);
		this->parent = nullptr;
		return this;
	}
	
	//Takes care of the one left child case
	if (child_count == 1)
	{
		
		target->left->parent = target->parent;
		delete(target->right);
		if (target_direction == -1)
		{
			target->parent->left = target->left; ///It might be that the left should be 
			
		}
		if (target_direction == 1)
		{
			target->parent->right = target->left; //It might be that the right should be target->parent.right

		}
		if (target_direction == 0)
		{
			BSTNode* temp = target->left;
			target->right = nullptr;
			BSTNode* height_temp = target->left;
			target->left = nullptr;
			while (height_temp->parent != nullptr)
			{
				height_temp->make_locally_consistent();
				height_temp = height_temp->parent;
			}
			height_temp->make_locally_consistent();
			target->parent = nullptr;
			delete(target);
			return temp;
		}
		target->right = nullptr;
		target->left = nullptr;
		target->parent = nullptr;
		delete(target);

		return this;
	}
	
	//Takes care of the one right child case
	if (child_count == 2)
	{
		target->right->parent = target->parent;
		delete(target->left);

		if (target_direction == -1)
		{
			target->parent->left = target->right;
		}
		if (target_direction == 1)
		{
			target->parent->right = target->right;
		}
		if (target_direction == 0)
		{
			BSTNode* temp = target->right;
			
			target->right = nullptr;
			BSTNode* height_temp = target->left;
			target->left = nullptr;
			while (height_temp->parent != nullptr)
			{
				height_temp->make_locally_consistent();
				height_temp = height_temp->parent;
			}
			height_temp->make_locally_consistent();
			target->parent = nullptr;
			delete(target);
			return temp;
		}
		target->parent = nullptr;
		target->right = nullptr;
		BSTNode* height_temp = target->left;
		target->left = nullptr;
		while (height_temp->parent != nullptr)
		{
			height_temp->make_locally_consistent();
			height_temp = height_temp->parent;
		}
		height_temp->make_locally_consistent();
		delete(target);
		this->parent = nullptr;
		return this;
	}
	

	//Takes care of the two children case
	if (child_count == 3)
	{
		BSTNode* successor = (BSTNode*) target->right->minimum_value();
		//Here we have to snip out the successor and putting it up top
		//There are two cases for the successor: it has one left child, or it
		//is a leaf. So, we check for case, then if/else
		if (target->parent == nullptr)
		{
			target->data = successor->data;
			target->count = successor->count;
			successor->count = 1;
			target->right->remove(successor->data);
			target->parent = nullptr;
			return target;
		}
		
		bool successor_has_child = false;
		//Find and record parent side:
		int successor_parent_side = 0; //-1 means parent's left, 1 means right
		if (successor == successor->parent->left)
		{
			successor_parent_side = -1;
		}
		if (successor == successor->parent->right)
		{
			successor_parent_side = 1;
		}

		if (!successor->right->is_empty()) //Checks if the successor has child
		{
			successor_has_child = true; 
		}
		if (successor_has_child) //If there exists a child
		{
			if (successor_parent_side == -1)
			{
				delete(successor->left);
				successor->right->parent = successor->parent;
				successor->parent->left = successor->right;
			}
			if (successor_parent_side == 1)
			{
				delete(successor->left);
				successor->right->parent = successor->parent;
				successor->parent->right = successor->right;
			}
		}
		
		if (!successor_has_child)
		{
			if (successor_parent_side == -1)
			{
				successor->parent->left = successor->right;//MIGHT HAVE TO DELETE THE BABY NODES HERE
				delete(successor->left);
			}
			if (successor_parent_side == 1)
			{
				successor->parent->right = successor->right;//MIGHT HAVE TO DELETE THE BABY NODES HERE
				delete(successor->left);
			}
		
		}

		BSTNode* height_temp; //Sets up variables for height correction
		if (successor_has_child)
		{
			height_temp = successor->right;
		}
		else
		{
			height_temp = successor->parent;
		}
		successor->parent = target->parent;
		if (target_direction == -1)
		{
			target->parent->left = successor;
		}
		
		if (target_direction == 1)
		{
			target->parent->right = successor;
		}
		
		target->left->parent = successor;
		target->right->parent = successor;
		successor->left = target->left;
		successor->right = target->right;
		target->parent = nullptr;
		target->left = nullptr;
		target->right = nullptr;
		while (height_temp->parent != nullptr)
		{
			height_temp->make_locally_consistent();
			height_temp = height_temp->parent;
		}
		height_temp->make_locally_consistent();
		delete(target);
		if (this->height > successor->height)
		{
			return this;
		}
		return successor;
	}
	
   
    return this;
}

BSTNode *BSTNode::avl_remove(int value)
{

    /********************************
     ****** BST Removal Begins ******
     ********************************/

    this->remove(value);

    /********************************
     ******* BST Removal Ends *******
     ********************************/

    /********************************
     **** AVL Maintenance Begins ****
     ********************************/

    BSTNode* temp = this->avl_balance();

    /********************************
     ***** AVL Maintenance Ends *****
     ********************************/

    return temp;
}

BSTNode *BSTNode::rb_remove(int value)
{
    // This is implemented for you.
    BHVNeighborhood nb(this, ROOT);
    BSTNode *root = this->rb_remove_helper(value, nb);
    nb.fix_blackheight_imbalance();
    return root;
}

int BSTNode::node_height() const
{
	return this->height;
}

unsigned int BSTNode::node_count() const
{
	int total_count = 0; //Total count in the tree started at the node
	if (this->is_empty())
	{
		return 0;
	}

	int left_count = this->left->node_count();
	int right_count = this->right->node_count();

	total_count = left_count + right_count + 1;
    return total_count;
}

unsigned int BSTNode::count_total() const
{
	int total_count = 0; //Total count in the tree started at the node
	if (this->is_empty())
	{
		return 0;
	}

	int left_count = this->left->count_total();
	int right_count = this->right->count_total();

	total_count = left_count + right_count + this->count;
    return total_count;
}

const BSTNode *BSTNode::parent_in(BSTNode *root) const
{
	int value = root->data;
	BSTNode* target = (BSTNode*) this->search(value);
	return target->parent;	
    return nullptr;
}

bool BSTNode::is_empty() const
{
    bool empty_by_count = this->count == 0;
    bool empty_by_height = this->height == -1;
    bool empty_by_children = !this->left && !this->right;

    // Assert some invariants about binary search trees
    assert(!this->left == !this->right);
    assert(empty_by_count == empty_by_height);
    assert(empty_by_height == empty_by_children);

    // Return any of the equivalent checks
    return empty_by_count;
}

BSTNode *BSTNode::child(Direction dir) const
{
    BSTNode *child = nullptr;
    if (dir == LEFT)
    {
        child = this->left;
    }
    else if (dir == RIGHT)
    {
        child = this->right;
    }
    return child;
}

void BSTNode::set_child(Direction dir, BSTNode *child)
{
    if (dir != ROOT)
    {
        if (dir == LEFT)
        {
            this->left = child;
        }
        else if (dir == RIGHT)
        {
            this->right = child;
        }
        child->parent = this;
    }
    else
    {
        assert(false);
    }
}

/*************************
 * BEGIN PRIVATE SECTION *
 *************************/

BSTNode::RRVNeighborhood::RRVNeighborhood(BSTNode *root)
    : g{root}, p{nullptr}, x{nullptr}, y{nullptr}, shape{SHAPE_NONE}
{
    // Stop if g is RED or too short
    ABORT_UNLESS((this->g->color == BLACK) &&
                 (this->g->node_height() > 1));

    if (this->g->left->color == BLACK)
    {
        // If there is a red-red violation, it's to the right
        this->y = this->g->left;
        this->p = this->g->right;

        // Stop if g has two BLACK children
        ABORT_UNLESS(this->p->color == RED);

        if (this->p->left->color == RED)
        {
            this->shape = RL;
            this->x = this->p->left;
        }
        else
        {
            // Stop if there is no red-red violation
            ABORT_UNLESS(this->p->right->color == RED);

            this->shape = RR;
            this->x = this->p->right;
        }
    }
    else if (this->g->right->color == BLACK)
    {
        // If there is a red-red violation, it's to the left
        this->y = this->g->right;
        this->p = this->g->left;

        if (this->p->left->color == RED)
        {
            this->shape = Shape::LL;
            this->x = this->p->left;
        }
        else
        {
            // Stop if there is no red-red violation
            ABORT_UNLESS(p->right->color == RED);

            this->shape = LR;
            this->x = this->p->right;
        }
    }
    else
    {
        // Both children of g are RED. Find the red-red violation
        BSTNode *lc = this->g->left;
        BSTNode *llc = lc->left;
        BSTNode *lrc = lc->right;
        BSTNode *rc = this->g->right;
        BSTNode *rlc = rc->left;
        BSTNode *rrc = rc->right;

        if (llc && llc->color == RED)
        {
            this->shape = LL;
            this->p = lc;
            this->x = llc;
            this->y = rc;
        }

        if (lrc && lrc->color == RED)
        {
            // Stop if there are multiple red-red violations
            ABORT_UNLESS(this->shape == SHAPE_NONE);

            this->shape = LR;
            this->p = lc;
            this->x = lrc;
            this->y = rc;
        }

        if (rlc && rlc->color == RED)
        {
            // Stop if there are multiple red-red violations
            ABORT_UNLESS(this->shape == Shape::SHAPE_NONE);

            this->shape = Shape::RL;
            this->p = rc;
            this->x = rlc;
            this->y = lc;
        }

        if (rrc && rrc->color == RED)
        {
            // Stop if there are multiple red-red violations
            ABORT_UNLESS(this->shape == SHAPE_NONE);

            this->shape = RR;
            this->p = rc;
            this->x = rrc;
            this->y = lc;
        }

        // Stop if there is no red-red violation
        ABORT_UNLESS(this->shape != SHAPE_NONE);
    }
}

BSTNode::BHVNeighborhood::BHVNeighborhood(BSTNode *n, Direction dir)
    : n{n}, p{nullptr}, s{nullptr}, c{nullptr}, d{nullptr},
      del_case{CASE_NONE}, dir{dir}
{
    ABORT_UNLESS(this->n && !this->n->is_empty() &&
                 this->n->color == BLACK);

    this->p = this->n->parent;

    if (!this->p)
    {
        this->del_case = CASE_1;
        assert(dir == ROOT);
        this->dir = ROOT;
    }
    else
    {
        assert(!this->p->is_empty());
        assert(this->dir != ROOT);

        this->s = this->p->child(opposite_direction(dir));
        this->c = this->s->child(dir);
        this->d = this->s->child(opposite_direction(dir));

        if (this->p->color == BLACK &&
            this->s->color == BLACK &&
            this->c && this->c->color == BLACK &&
            this->d && this->d->color == BLACK)
        {
            this->del_case = CASE_2;
        }
        else if (this->p->color == BLACK &&
                 this->s->color == RED)
        {
            assert(this->c && this->c->color == BLACK &&
                   this->d && this->d->color == BLACK);

            this->del_case = CASE_3;
        }
        else if (this->p->color == RED &&
                 this->s->color == BLACK &&
                 this->c->color == BLACK &&
                 this->d->color == BLACK)
        {
            this->del_case = CASE_4;
        }
        else if (this->s->color == BLACK &&
                 this->c->color == RED &&
                 this->d->color == BLACK)
        {
            this->del_case = CASE_5;
        }
        else if (this->s->color == BLACK &&
                 this->d->color == RED)
        {
            this->del_case = CASE_6;
        }
        else
        {
            this->del_case = CASE_NONE;
        }
    }
}

void BSTNode::BHVNeighborhood::fix_blackheight_imbalance()
{
    /*
     * This is implemented for you. Study it carefully so you understand what
     *  is going on when a node is deleted from a Red-Black Tree.
     */
    BSTNode::BHVNeighborhood nb = *this;
    while (nb.p)
    {
        BSTNode::Direction pdir = ROOT;
        if (nb.p->parent)
        {
            if (nb.p == nb.p->parent->left)
            {
                pdir = LEFT;
            }
            else if (nb.p == nb.p->parent->right)
            {
                pdir = RIGHT;
            }
            else
            {
                // Should never happen: nb.p is non-null.
                assert(false);
            }
        }
        BSTNode *grandparent = nb.p->parent;

        switch (nb.del_case)
        {
        case CASE_2:
            nb.s->color = RED;
            nb.n = nb.p;
            nb = BSTNode::BHVNeighborhood(nb.n->parent, nb.dir);
            break;
        case CASE_3:
            nb.s = nb.p->dir_rotate(nb.dir);
            if (pdir != ROOT)
            {
                grandparent->set_child(pdir, nb.s);
            }
            swap_colors(nb.p, nb.s);
            nb = BSTNode::BHVNeighborhood(nb.p, nb.dir);
            assert(nb.del_case >= CASE_4);
            break;
        case CASE_4:
            swap_colors(nb.p, nb.s);
            return;
        case CASE_5:
            nb.p->set_child(opposite_direction(nb.dir),
                            nb.s->dir_rotate(opposite_direction(nb.dir)));
            swap_colors(nb.c, nb.s);
            nb = BSTNode::BHVNeighborhood(nb.p, nb.dir);
            assert(nb.del_case == CASE_6);
            break;
        case CASE_6:
            nb.s = nb.p->dir_rotate(nb.dir);
            if (pdir != ROOT)
            {
                grandparent->set_child(pdir, nb.s);
            }
            swap_colors(nb.p, nb.s);
            nb.d->color = BLACK;
            return;
        default:
            // CASE_NONE or CASE_1 (should never happen; nb.p is non-null)
            assert(false);
            break;
        }
    }
}

BSTNode *BSTNode::rb_remove_helper(int value, BHVNeighborhood &nb)
{
    // This is implemented for you
    BSTNode *root = this;
    if (root->height >= 0)
    {
        if (value < root->data)
        {
            nb.dir = LEFT;
            root->left = root->left->rb_remove_helper(value, nb);
        }
        else if (value > root->data)
        {
            nb.dir = RIGHT;
            root->right = root->right->rb_remove_helper(value, nb);
        }
        else
        {
            // We found the value. Remove it.
            if (root->count > 1)
            {
                root->count--;
            }
            else
            {
                if (root->left->is_empty() &&
                    root->right->is_empty())
                {
                    // root has no children. We may have to do extra work.

                    // Get its neighborhood
                    nb = BHVNeighborhood(this, nb.dir);

                    // Delete it
                    delete this;
                    root = new BSTNode();
                }
                else if (!root->left->is_empty() &&
                         root->right->is_empty())
                {
                    // this has one (left) child. Promote this's child
                    this->left->color = root->color;
                    root = this->left;
                    this->left = nullptr;
                    delete this;
                }
                else if (root->left->is_empty() &&
                         !root->right->is_empty())
                {
                    // this has one (right) child. Promote this's child
                    this->right->color = root->color;
                    root = this->right;
                    this->right = nullptr;
                    delete this;
                }
                else
                {
                    /*
                     * this has two children.
                     *
                     * Find the successor to use as a replacement, then remove it
                     * entirely from this's right subtree. This requires setting
                     * the replacement's count to 1 so that the node is entirely
                     * removed rather than simply having its count decremented.
                     * Removal is the only place a const-to-non-const cast should
                     * appear in your solution.
                     *
                     * TODO: (optional) Rewrite this section of code to eliminate
                     *  the const-to-non-const cast.
                     */

                    BSTNode *replacement = (BSTNode *)root->right->minimum_value();
                    root->data = replacement->data;
                    root->count = replacement->count;
                    replacement->count = 1;
                    nb.dir = RIGHT;
                    root->right = root->right->rb_remove_helper(replacement->data, nb);
                }
            }
        }
    }

    root->make_locally_consistent();

    return root;
}

BSTNode *BSTNode::dir_rotate(Direction dir)
{
    // This is implemented for you.
    BSTNode *root = this;
    if (dir == LEFT)
    {
        root = root->left_rotate();
    }
    else if (dir == RIGHT)
    {
        root = root->right_rotate();
    }
    return root;
}

BSTNode *BSTNode::right_rotate()
{
	if (this->left->is_empty())
	{
		return this; //I know they assume its not but double check, trust no one
	} //-_-

	this->left->parent = this->parent;
	if (this->parent != nullptr)
	{
		if (this->parent->left == this)
		{
			this->parent->left = this->left;
		}
		if (this->parent->right == this)
		{
			this->parent->right = this->left;
		}
	}
	
	
	this->parent = this->left;
	this->left = this->parent->right;
	this->parent->right = this;
	
	this->left->make_locally_consistent();
	this->make_locally_consistent();
	this->parent->make_locally_consistent();
	

	BSTNode* height_fix_temp = this->parent;

	while (!(height_fix_temp->parent == nullptr))
	{
		height_fix_temp = height_fix_temp->parent;
		height_fix_temp->make_locally_consistent();		
	}
	
	return this->parent;
}

BSTNode *BSTNode::left_rotate()
{
	if (this->right->is_empty())
	{
		return this; //I know they assume its not but double check
	}
	
	this->right->parent = this->parent;

	if (this->parent != nullptr)
	{
		if (this->parent->left == this)
		{
			this->parent->left = this->right;
		}
		if (this->parent->right == this)
		{
			this->parent->right = this->right;
		}
	}
	
	


	this->parent = this->right;
	this->right = this->parent->left;
	this->parent->left = this;
	
	this->right->make_locally_consistent();
	this->make_locally_consistent();
	this->parent->make_locally_consistent();
	

	BSTNode* height_fix_temp = this->parent;

	while (!(height_fix_temp->parent == nullptr))
	{
		height_fix_temp = height_fix_temp->parent;
		height_fix_temp->make_locally_consistent();		
	}
	
	return this->parent;
}

BSTNode *BSTNode::avl_balance()
{
	if (!is_balanced())
	{
		if (left->is_balanced() && right->is_balanced())
		{
			if (left->height > right->height)//Denotes LL or LR
			{
				if (left->left->height > left->right->height) //Denotes LL
				{
					return this->right_rotate();
				}
				else if (left->left->height < left->right->height) //Denotes LR
				{
					this->left->left_rotate();
					return this->right_rotate();
				}	
				else
				{
					return this->right_rotate();
				}
			}
			else //Denotes RR or RL
			{
				if (right->right->height > right->left->height) //Denotes RR
				{
					return this->left_rotate();
				}
				else if (right->right->height < right->left->height)
				{
					this->right->right_rotate();
					return this->left_rotate();
				}
				else
				{
					return this->left_rotate();
				}
				
			}
		}
		

	}
	if (!this->right->is_empty())
	{
		this->right = this->right->avl_balance();
	}
	if (!this->left->is_empty())
	{
		this->left = this->left->avl_balance();
	}
	
    return this;
}

BSTNode *BSTNode::rb_eliminate_red_red_violation()
{
    /*
     * Get this's neighborhood (children + grandchildren), which might have
     *  shape NONE if this is BLACK or this.height <= 1 or there is no red-red
     *  violation in the neighborhood of this.
     */
    RRVNeighborhood nb(this);

    if (nb.shape != SHAPE_NONE)
    {
		if (nb.y->color == RED) //If uncle is red
		{
			swap_colors(nb.p, nb.g); //all cases are the same
			nb.y->color = BLACK;
			return this;
		}
		
		if (nb.y->color == BLACK) //If uncle is black
		{
			if (nb.shape == LL)
			{
				swap_colors(nb.p, nb.g);
				nb.g->right_rotate();	
			}

			if (nb.shape == LR)
			{
				swap_colors(nb.x, nb.g);
				nb.p->left_rotate();
				nb.g->right_rotate();				
			}

			if (nb.shape == RL)
			{
				swap_colors(nb.x, nb.g);
				nb.p->right_rotate();
				nb.g->left_rotate();				
			}

			if (nb.shape == RR)
			{
				swap_colors(nb.p, nb.g);
				nb.g->left_rotate();
			}

			return nb.y;

		}
    }

    return this;
}

int BSTNode::height_diff() const
{
    /*
     * This is implemented for you. Note the use of the node_height() function
     *  rather than the height property. Why do you think is it written in this
     *  way? -So that it re-calculates heights?
     */
    int diff = 0;
    if (!this->is_empty())
    {
        diff = this->right->node_height() - this->left->node_height();
    }

    return diff;
}

void BSTNode::make_locally_consistent()
{
	if (this->is_empty())
	{
		this->height = -1;
		return;
	}
	this->right->parent = this;
	this->left->parent = this;
	int left_height = this->left->height;
	int right_height = this->right->height;
	if(left_height >= right_height)
	{
		this->height = left_height + 1;
	}
	if (left_height < right_height)
	{
		this->height = right_height + 1;
	}
	return;	
}

bool BSTNode::is_balanced()
{

	if (this->is_empty())//Returns empty nodes as balanced
	{
		return true;
	}
	
	int left_height = this->left->height;
	int right_height = this->right->height;

	if (abs(left_height - right_height) > 1)
	{
		return false;
	}

	return true;
}