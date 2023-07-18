//3. (20) Baum-Summe (rekursiv, inorder)
//------------------------------------------------------------------
/*
Schreiben Sie die Funktion int preorder_sum(NODE_PTR) die 
die Summe der in den Blättern und Knoten eines binären Baumes gespeicherten
int-Werten berechnet indem sie den Baum rekursiv preorder traversiert.
typedef struct node
{
struct node *left; 
struct node *right; 
int value;
}NODE;

typedef NODE* NODE_PTR;
*/
typedef struct node
{
    struct node *left;
    struct node *right;
    int value;
} NODE;

typedef NODE *NODE_PTR;

#include <stdio.h>
#include <stdlib.h>

NODE *new_node(int data);
NODE *input(NODE *p_root, int val);
void preO(NODE *p_root);
int preO_sum(NODE *p_root);

int main()
{
    NODE *p_root = NULL;
    p_root = input(p_root, 40);
    input(p_root, 35);
    input(p_root, 20);
    input(p_root, 5);
    input(p_root, 30);
    input(p_root, 100);
    preO(p_root);
    printf(" Summe = %d ", preO_sum(p_root));
    return 0;
}
NODE *new_node(int data)
{
    NODE *p_temp = malloc(sizeof(NODE));
    p_temp->left = NULL;
    p_temp->right = NULL;
    p_temp->value = data;
    return p_temp;
}
//inO = links Knoten Rechts
//preO = Knoten links rechts
//postO = linbks rechts Knoten
NODE *input(NODE *p_root, int val)
{

    if (p_root == NULL)
    {
        return new_node(val);
    }
    if (val == p_root->value)
    {
        return p_root;
    }
    if (val < p_root->value)
    {
        p_root->left = input(p_root->left, val);
        return p_root;
    }
    if (val > p_root->value)
    {
        p_root->right = input(p_root->right, val);
        return p_root;
    }
}
void preO(NODE *p_root)
{
    if (p_root == NULL)
    {
        return;
    }
    printf("-%d", p_root->value);
    preO(p_root->left);
    preO(p_root->right);
    return;
}
int preO_sum(NODE *p_root)
{
    if (p_root == NULL)
    {
        return 0;
    }
    int sum = p_root->value;
    sum = sum + preO_sum(p_root->left);
    sum = sum + preO_sum(p_root->right);
    return sum;
}