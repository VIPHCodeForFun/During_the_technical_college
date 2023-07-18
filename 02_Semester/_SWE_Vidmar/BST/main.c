/*////////////////////////////////////////////////////////////////////////////
#Author:    Philipp Vidmar            
#Semester:  2/2021                                       
#Programm:  C  
#README:
BST 
einfügen 
löschen
traversieren 
    inorder 
    preorder
    postorder
        10
      /    \
     6      15
    / \     / \
  3    7   12   20
///////////////////////////////////////////////////////////////////////////*/

#include <stdio.h>  // io
#include <stdlib.h> // malloc calloc

struct bst_node
{
    int value;
    struct bst_node *p_left;
    struct bst_node *p_right;
};

struct bst_node *create_node(int element);
struct bst_node *new_node(struct bst_node *p_root, int element);
void trv_inorder(struct bst_node *p_root);
struct bst_node *bst_search(struct bst_node *p_root, int search);
struct bst_node *bst_delete(struct bst_node *p_root, int item);

int main(int argc, char *argv[])
{
    printf("yeaaa BST is so geil.\n");

    struct bst_node *p_root = NULL;

    int temp = atoi(argv[1]);

    p_root = new_node(p_root, 10);
    new_node(p_root, 6);
    new_node(p_root, 15);
    new_node(p_root, 7);
    new_node(p_root, 3);
    trv_inorder(p_root);
    if (argc == 2)
    {
        if (bst_search(p_root, temp) == NULL)
        {
            printf("\nnix gefunden mann !\n");
        }
        else
        {
            printf("\nsearch %d\n", bst_search(p_root, temp)->value);
        }
    }
    bst_delete(p_root, 10);

    trv_inorder(p_root);
    return 0;
}
struct bst_node *create_node(int element)
{
    struct bst_node *p_new_node = malloc(sizeof(struct bst_node));
    if (p_new_node == NULL)
    {
        return NULL;
    }
    p_new_node->value = element;
    p_new_node->p_left = NULL;
    p_new_node->p_right = NULL;
    return p_new_node;
}

struct bst_node *new_node(struct bst_node *p_root, int element)
{
    //Es gibt keinen Baum wir legen root an
    if (p_root == NULL)
    {
        return create_node(element);
    }
    //element ist gleich
    else if (p_root->value == element)
    {
        return p_root;
    }
    //nach links gehn (kleiner)
    else if (p_root->value > element)
    {
        p_root->p_left = new_node(p_root->p_left, element);
        return p_root;
    }
    //rechts einfügen
    else if (p_root->value < element)
    {
        p_root->p_right = new_node(p_root->p_right, element);
        return p_root;
    }
    return p_root;
}
void trv_inorder(struct bst_node *p_root)
{
    if (p_root == NULL)
    {
        return;
    }
    trv_inorder(p_root->p_left);
    printf("-[%d]", p_root->value);
    trv_inorder(p_root->p_right);
    return;
}
struct bst_node *bst_search(struct bst_node *p_root, int search)
{
    struct bst_node *p_temp = NULL;
    if (p_root == NULL)
    {
        return NULL;
    }
    else if (p_root->value == search)
    {
        return p_root;
    }
    else if (p_root->value > search)
    {
        p_temp = bst_search(p_root->p_left, search);
    }
    else if (p_root->value < search)
    {
        p_temp = bst_search(p_root->p_right, search);
    }
    return p_temp;
}
struct bst_node *bst_delete(struct bst_node *p_root, int item)
{
    // nichts gefunden
    if (p_root == NULL)
    {
        return NULL;
    }
    //item ist größer geh nach rechts
    else if (p_root->value < item)
    {
        p_root->p_right = bst_delete(p_root->p_right, item);
    }
    //item ist kleiner geh nach links
    else if (p_root->value > item)
    {
        p_root->p_left = bst_delete(p_root->p_left, item);
    }
    //item wurde gefunden und kann exikutiert werden
    else if (p_root->value == item)
    {
        //kein Kind einfach löschen und NUll zurück geben.
        if (p_root->p_left == NULL && p_root->p_right == NULL)
        {
            free(p_root);
            return NULL;
        }
        //ein Kind lösche den speicher und gib die addresse des rechten knotens zurück
        else if (p_root->p_left == NULL && p_root->p_right != NULL)
        {
            struct bst_node *p_temp = p_root->p_right;
            free(p_root);
            return p_temp;
        }
        //ein Kind Links lösche den knoten und gib die addresse des rechten knotens zurück
        else if (p_root->p_left != NULL && p_root->p_right == NULL)
        {
            struct bst_node *p_temp = p_root->p_left;
            free(p_root);
            return p_temp;
        }
        //zwei kinder
        else
        {
            //1 im rechten baum das kleinse element finden und wert speichern
            struct bst_node *p_temp = p_root->p_right;
            while (p_temp->p_left != NULL)
            {
                p_temp = p_temp->p_left;
            }
            int save = p_temp->value;
            //2 kleinses element löschen mit bst_del -> 0 oder 1 kind
            bst_delete(p_root, save);
            //3 wert umschreiben
            p_root->value = save;
            //4 Addresse normal returnen
        }
    }
    return p_root;
}