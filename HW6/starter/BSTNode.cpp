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

/*
 * TODO: The BSTNode copy constructor is incomplete. You must complete it. You
 *  may use an initializer list, or you may write a traditional constructor
 *  function, or both.
 */
BSTNode::BSTNode(const BSTNode &other){
#pragma message "TODO: Implement this function"
}

BSTNode::~BSTNode(){
#pragma message "TODO: Implement this function"
}

std::string BSTNode::to_string() const
{
    return value_string(this) + decorator_string(this);
}

const BSTNode *BSTNode::minimum_value() const
{
#pragma message "TODO: Implement this function"

    // TODO: This line is in here so that the starter code compiles.
    // Remove or modify it when implementing.
    return this;
}

const BSTNode *BSTNode::maximum_value() const
{
#pragma message "TODO: Implement this function"

    // TODO: This line is in here so that the starter code compiles.
    // Remove or modify it when implementing.
    return this;
}

const BSTNode *BSTNode::search(int value) const
{
#pragma message "TODO: Implement this function"

    // TODO: This line is in here so that the starter code compiles.
    // Remove or modify it when implementing.
    return new BSTNode();
}

BSTNode *BSTNode::insert(int value)
{
#pragma message "TODO: Implement this function"

    // TODO: Update this->height (optional)
    // TODO: Update this->{left,right}->parent (optional)

    // TODO: This line is in here so that the starter code compiles.
    // Remove or modify it when implementing.
    return this;
}

BSTNode *BSTNode::avl_insert(int value)
{
#pragma message "TODO: Implement this function"

    /********************************
     ***** BST Insertion Begins *****
     ********************************/

    // TODO: Students write code here

    /********************************
     ****** BST Insertion Ends ******
     ********************************/

    /********************************
     **** AVL Maintenance Begins ****
     ********************************/

    // TODO: Students write code here

    /********************************
     ***** AVL Maintenance Ends *****
     ********************************/

    // TODO: Update this->height (optional)
    // TODO: Update this->{left,right}->parent (optional)

    // TODO: This line is in here so that the starter code compiles.
    // Remove or modify it when implementing.
    return this;
}

BSTNode *BSTNode::rb_insert(int value)
{
#pragma message "TODO: Implement this function"

    /********************************
     ***** BST Insertion Begins *****
     ********************************/

    // TODO: Students write code here

    /********************************
     ****** BST Insertion Ends ******
     ********************************/

    /********************************
     ***** RB Maintenance Begins ****
     ********************************/

    // TODO: Students write code here

    /********************************
     ****** RB Maintenance Ends *****
     ********************************/

    // TODO: Update this->height (optional)
    // TODO: Update this->{left,right}->parent (optional)

    // TODO: This line is in here so that the starter code compiles.
    // Remove or modify it when implementing.
    return this;
}

BSTNode *BSTNode::remove(int value)
{
    // TODO: Students write code here

    // TODO: Update this->height (optional)
    // TODO: Update this->{left,right}->parent (optional)

    // TODO: This line is in here so that the starter code compiles.
    // Remove or modify it when implementing.
    return this;
}

BSTNode *BSTNode::avl_remove(int value)
{
#pragma message "TODO: Implement this function"

    /********************************
     ****** BST Removal Begins ******
     ********************************/

    // TODO: Students write code here

    /********************************
     ******* BST Removal Ends *******
     ********************************/

    /********************************
     **** AVL Maintenance Begins ****
     ********************************/

    // TODO: Students write code here

    /********************************
     ***** AVL Maintenance Ends *****
     ********************************/

    // TODO: This line is in here so that the starter code compiles.
    // Remove or modify it when implementing.
    return this;
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
#pragma message "TODO: Implement this function"

    // TODO: This line is in here so that the starter code compiles.
    // Remove or modify it when implementing.
    return -1;
}

unsigned int BSTNode::node_count() const
{
#pragma message "TODO: Implement this function"

    // TODO: This line is in here so that the starter code compiles.
    // Remove or modify it when implementing.
    return 0;
}

unsigned int BSTNode::count_total() const
{
#pragma message "TODO: Implement this function"

    // TODO: This line is in here so that the starter code compiles.
    // Remove or modify it when implementing.
    return 0;
}

const BSTNode *BSTNode::parent_in(BSTNode *root) const
{
#pragma message "TODO: Implement this function"

    // TODO: This line is in here so that the starter code compiles.
    // Remove or modify it when implementing.
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
#pragma message "TODO: Implement this function"

    // TODO: (optional) Update heights
    // TODO: (optional) Update parents

    // TODO: This line is in here so that the starter code compiles.
    // Remove or modify it when implementing.
    return this;
}

BSTNode *BSTNode::left_rotate()
{
#pragma message "TODO: Implement this function"

    // TODO: (optional) Update heights
    // TODO: (optional) Update parents

    // TODO: This line is in here so that the starter code compiles.
    // Remove or modify it when implementing.
    return this;
}

BSTNode *BSTNode::avl_balance()
{
#pragma message "TODO: Implement this function"

    // TODO: This line is in here so that the starter code compiles.
    // Remove or modify it when implementing.
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
        /*
         * There is a red-red violation somewhere in the neighborhood of this
         *  Fix it.
         */

#pragma message "TODO: Implement the rest of this function"
    }

    // TODO: This line is in here so that the starter code compiles.
    // Remove or modify it when implementing.
    return this;
}

int BSTNode::height_diff() const
{
    /*
     * This is implemented for you. Note the use of the node_height() function
     *  rather than the height property. Why do you think is it written in this
     *  way?
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
#pragma message "TODO: Implement this function"
}
