/*////////////////////////////////////////////////////////////////////////////
#Author:    Philipp Vidmar            
#Semester:  2/2021                                       
#Programm:  C  
#README:                                                                     
SWE2 LaborBinäre Suchbäume (Binary-Search-Tree „BST“)WS 2018/19Aufgabe 1 (Einfügen und Suchen)
Binäre Suchbäume sind eine weitere wichtige Datenstruktur in der Computerwissenschaft.
Im Gegensatz zu verketteten Listen, welche wirexplizit sortieren mussten, ist die Ordnung eine inhärente Eigenschaft vonbinären Bäumen.
Alle Werte der linken Kinder eines Knotens sind striktkleiner  als  im  Knoten  selbst, und strikt größer für  alle  rechten.  
DasKonzept ist direkt verwandt mit der binären Suche (binary search). Außerdemsind sie ebenfalls eine dynamische Datenstruktur. 
Sie ermöglichen es, neue Elemente an beliebiger Stelle einzufügen oder zu entfernen, ohne dasvorhandene Elemente verschoben werden müssen. 
Darin liegt auch ihr Vorteilgegenüber dynamischen   Arrays. 
Anwendung finden Bäume als Teil größererDatenstrukturen wie etwa Datenbanken oder ganze Dateisysteme.
Schreiben Sie eine eigene Implementierung eines BST, welcher aus  nur einer Datenstruktur für einen Knoten und zugehöriger Funktionen besteht.
Verwenden Sie folgende Protoypen in ihrer binary_tree.h Header-Datei:
struct node {// 'val' can be any type, even another pointer!//
int val;
struct node *left;
struct node *right;
};
struct node *new_node(int item);
struct node *search(struct node *root, int val);
void print_inorder(struct node *root);
void print_preorder(struct node *root);
void print_postorder(struct node *root);
struct node *insert(struct node *root, int val);
Diese Funktionen sind in der Datei binary_tree.c zu implementieren.Durch den sich selbst wiederholenden Aufbau von BSTs bietet es sich an, rekursive Implementierungen für einige Funktionen zu wählen.Implementieren sie insert(), print_inorder() und search() jeweils rekursiv.überlegen Sie genau, was die einzelnen Funktionen ausführen müssen, um das Testprogramm auf der letzten Seite lauffähig zu machen(kommentieren sie delete_node() zum testen von Aufgabe 1 aus)

Aufgabe 2 (Löschen von Knoten)
Für das Löschen von Knoten müssen wir etwas mehr Fallunterscheidungen treffen.
Implementieren Sie die Funktion struct node* successor( struct node* node);
welche das in der Reihenfolge nächstgrössere Element im Baum zurückgibt.
Diese dient wiederum als interne Hilfsfunktion für die Funktion
struct node* delete_node( struct node* root, int key);
delete_node() soll den Knoten mit dem entsprechend key-Wert löschen und
freigeben und die Verknüpfungen korrekt neu setzen. Beide Funktionen solle ebenfalls rekursiv implementiert werden.
Erweitern Sie also ihre Header-Datei um die entsprechenden Prototypen und kommentieren Sie den entsprechenden Zeilen zum Testen der Funktionen in
der main() wieder ein.

Aufgabe 3 (Mehrfach vorkommende Werte) [optional] 
Erweitern Sie ihr Programm so, dass auch mehrfach vorkommende Werte in dem Baum gespeichert Werden können.
Anstatt der naiven Lösung, bei der mehrfach vorkommende einfach in entweder den linken oder rechten Teilbaum
einsortiert werden, sollen Sie allerdings eine verkettete Liste pro Knoten verwenden.
Die Verwendung einer verketteten Liste erlaubt es uns, unsere bestehende 
Implementierung mit nur wenigen Veränderungen beizubehalten. Sie dürfen
Ihre Implementierung der verketteten Liste aus dem letzten Übungsblatt anpassen und verwenden.
Jeder Knoten im Baum soll eine eigene verkettete Liste aufbauen, wobei die
Elemente der Liste jeweils alle den gleichen Wert wie der jeweilige Knoten des Baums haben.
Für einfache Integer-Werte ist dies natürlich etwas komplexer als es sein muss 
(man könnte auch einen einfachen Zähler verwenden). 
Sollen jedoch ganze Datenstrukturen anhand eines Schlüssels einsortiert werden, ist dies ein sehr guter Ansatz.
Für diesen integrierten Anwendungsfall können Sie auf die Nutzung der Header Datenstruktur verzichten.
Neue Elemente werden beim einsortieren in den Baum einfach immer am Anfang der einfach verketteten Liste eingefügt.
Tipp: Genau genommen kann man sogar die Node-Datenstruktur als Listenelement missbrauchen, 
da sie den gleichen Inhalt haben (left/right   bzw. next/prev sind lediglich beliebige Namen).

///////////////////////////////////////////////////////////////////////////*/

#include <stdio.h>
#include <stdlib.h>
#include "bin_tree.h"

int main()
{
    /* example tree
                  50
               /     \
              30      70
             /  \    /  \
            20  40  60   80 
    */
    struct node *p_bst = new_root(50); //create head of tree
    insert_node(p_bst, 30);            // insert to three
    insert_node(p_bst, 40);            // the row dosent matter
    insert_node(p_bst, 70);
    insert_node(p_bst, 30);
    insert_node(p_bst, 60);
    insert_node(p_bst, 80);
    insert_node(p_bst, 20);
    printf("Inorder [links - knoten - rechts]\n");
    print_inorder(p_bst);
    printf("\n");
    printf("preorder [knoten - links - rechts]\n");
    print_preorder(p_bst);
    printf("\n");
    printf("postorder [links - rechts - knoten]\n");
    print_postorder(p_bst);
    printf("\n");
    search(p_bst, 20);
    printf("\n\n");

    printf("Inorder [links - knoten - rechts]\n");
    print_inorder(p_bst);
    printf("\n");
    delete_node(p_bst, 40); //Fall1 kein Kind
    printf("Inorder [links - knoten - rechts]\n");
    print_inorder(p_bst);
    printf("\n");
    delete_node(p_bst, 30); //Fall2 ein Kind
    printf("Inorder [links - knoten - rechts]\n");
    print_inorder(p_bst);
    printf("\n");
    delete_node(p_bst, 70); //Fall3 zwei Kinder
    printf("Inorder [links - knoten - rechts]\n");
    print_inorder(p_bst);
    printf("\n");
    printf("Inorder [links - knoten - rechts]\n");
    print_inorder(p_bst);
    printf("\n");
    return 0;
}
struct node *new_root(int item)
{
    struct node *p_new_node = malloc(sizeof(struct node));
    if (p_new_node == NULL)
    {
        printf("ErroR Malloc");
        return NULL;
    }
    p_new_node->value = item;
    p_new_node->p_left = NULL;
    p_new_node->p_right = NULL;
    return p_new_node; //return Adress from new node
}
struct node *insert_node(struct node *p_root, int item)
{
    if (p_root == NULL) // create new node return address
    {
        return new_root(item); //this is the termination condition
    }
    else if (item > p_root->value) //go right and return p_root
    {
        p_root->p_right = insert_node(p_root->p_right, item);
    }
    else if (item < p_root->value) // go left and return p_root
    {
        p_root->p_left = insert_node(p_root->p_left, item);
    }
    return p_root;
}
struct node *search(struct node *p_root, int item) // noch nicht kontrolliert
{
    if (item == p_root->value) //
    {
        printf("[%d] Value Found\n", item);
        return p_root;
    }
    else if (item < p_root->value && p_root->p_left != NULL)
    {
        return search(p_root->p_left, item);
    }
    else if (item > p_root->value && p_root->p_right != NULL)
    {
        return search(p_root->p_right, item);
    }
    else
    {
        printf("[%d] Value NOT Found\n", item);
        return NULL;
    }
}
struct node *successor_max(struct node *p_root)
{
    struct node *p_temp = p_root;
    while (p_temp == NULL)
    {
        p_temp = p_temp->p_right;
    }
    return p_temp;
}
struct node *successor_low(struct node *p_root)
{
    struct node *p_temp = p_root;
    while (p_temp == NULL)
    {
        p_temp = p_temp->p_left;
    }
    return p_temp;
}

struct node *delete_node(struct node *p_root, int item)
{
    //search for note
    if (p_root == NULL) //return NULL;
    {
        printf("[%d] Value NOT Found\n", item);
        return p_root;
    }
    else if (item < p_root->value) //go left
    {
        p_root->p_left = delete_node(p_root->p_left, item);
    }
    else if (item > p_root->value) // go right
    {
        p_root->p_right = delete_node(p_root->p_right, item);
    }
    else if (item == p_root->value) //Found Item
    {
        // only root
        if (p_root->p_left == NULL && p_root->p_right == NULL)
        {
            free(p_root); //delete note an return NULL;
            return NULL;
        }
        // root with one child
        else if (p_root->p_left == NULL && p_root->p_right != NULL)
        {
            struct node *p_temp = p_root; //save p_root position
            p_root = p_root->p_right;     //new position for p_root->right
            free(p_temp);                 //delete node
            //return p_root;              //return new position
        }
        else if (p_root->p_right == NULL && p_root->p_left != NULL)
        {
            struct node *p_temp = p_root; //save p_root position
            p_root = p_root->p_left;      //new position for p_root->left
            free(p_temp);                 //delete node
            //return p_root;              //return new position
        }
        // root wit two child
        else
        {
            //find lowest in right sup tree
            struct node *p_temp = successor_low(p_root->p_right);
            int save = 0;
            /*while (p_temp == NULL)
            {
                p_temp = p_temp->p_left; // p-temp = address from lowest in right sup tree
            }*/
            //save Item from lowest
            save = p_temp->value;
            //delete lowest Item
            delete_node(p_root, p_temp->value);
            //replace from data from root with save_lowest
            p_root->value = save;
            //return p_root;
        }
    }
    return p_root;
}
void print_inorder(struct node *p_root) // noch nicht kontrolliert
{
    //left - root - right
    if (p_root != NULL)
    {
        print_inorder(p_root->p_left);  //go left
        printf("[%d]-", p_root->value); //print root value
        print_inorder(p_root->p_right); //go right
    }
    return;
}
void print_preorder(struct node *p_root)
{
    //root - left - right
    if (p_root != NULL)
    {
        printf("[%d]-", p_root->value);  //print root value
        print_preorder(p_root->p_left);  //go left
        print_preorder(p_root->p_right); // go right
    }
    return;
}
void print_postorder(struct node *p_root)
{
    //left - right - root
    if (p_root != NULL)
    {
        print_postorder(p_root->p_left);  //goleft
        print_postorder(p_root->p_right); //go right
        printf("[%d]-", p_root->value);   //print root value
    }
    return;
}