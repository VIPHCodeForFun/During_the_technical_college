#ifndef BIN_TREE_H_
#define BIN_TREE_H_

struct node
{ // 'val' can be any type, even another pointer!//
    int value;
    struct node *p_left;
    struct node *p_right;
};

struct node *new_root(int item);
//first node (root)
struct node *insert_node(struct node *p_root, int item);
//insert a node to root_node
struct node *search(struct node *p_root, int item);
//serach for an item in the tree return is Ptr
struct node *successor_max(struct node *p_root);
//searc the biggest element in the tree
struct node *successor_low(struct node *p_root);
//searc the lowest element in the tree
struct node *delete_node(struct node *p_root, int item);
//delets the node with the Value of item
void print_inorder(struct node *p_root);
//Inorder [left - root - right]
void print_preorder(struct node *p_root);
//preorder [root - left - right]
void print_postorder(struct node *p_root);
//postorder [left - right - root]

#endif /* BIN_TREE_H_ */