#include <iostream>
#include "utilesWet2.h"
#include <string>
#include <iostream>
#include <vector>
#include "hashTable.h"
using namespace std;

int main() {
    hashTable hash;
    int op, op2;
    /*AVL_Tree<Node<Customer*>> tree1;
    for (int i = 0; i < hash.getSize(); ++i) {
        Customer* cust3 = new Customer(i,i);
        Node<Customer*>* node = new Node<Customer*>(i,cust3, nullptr);
        tree1.searchAndAdd(node);
        tree1.printLevelOrder();
    }
    deleteTree(tree1.getRoot());

    for (int i = 0; i < hash.getSize(); ++i) {
        Customer* cust2 = new Customer(i,i);
        hash.Insert(cust2);
        hash.array.printArr();
    }
     */
    int Switch=0;
    while(true){
        cin >> op;
        cin >> op2;
        for (int i = 0; i < hash.getSize(); ++i) {
            hash[i].printLevelOrder();
        }
        Customer* cust= new Customer(op,op2);

        if(Switch >= 15)
            hash.Delete(op);
        else
        {
            hash.Insert(cust);
        }
        std::cout << "-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/" ;
        Switch++;
        hash.printArr();
    }
    return 5;
}
