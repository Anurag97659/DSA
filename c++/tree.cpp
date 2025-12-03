#include <iostream>
#include <queue>
using namespace std;
#include <iomanip>

class Node{
    public:
    int data;
    Node* left;
    Node* right;
    Node(int data){
        this->data = data;
        left = NULL;
        right = NULL;
    }
    void height(){
        int l=0,r=0;
        while(left!=NULL){
            left = left->left;
            l++;
        }
        while(right!=NULL){
            right = right->right;
            r++;
        }
        int h = max(l,r);
        cout<<h;
    } 
     void printTree(int space = 0, int levelGap = 5) {
        if (!this) return;
        space += levelGap;
        if (right) right->printTree(space, levelGap);
        cout << endl;
        cout << setw(space) << data << endl;
        if (left) left->printTree(space, levelGap);
    }
};

void breathFirstSearch(Node* root){
    if(root==NULL) return;
    queue<Node*> q;
    q.push(root);
    while(!q.empty()){
        Node* curr = q.front();
        q.pop();
        cout<<curr->data<<" ";
        if(curr->left!=NULL) q.push(curr->left);
        if(curr->right!=NULL) q.push(curr->right);

    }

}
void depthFirstSearch(Node* root){
    if(root==NULL) return;
    cout<<root->data<<" ";
    depthFirstSearch(root->left);
    depthFirstSearch(root->right);
}
int main(){
     Node* n1 = new Node(1);
     n1->left = new Node(2);
     n1->right = new Node(3);
     n1->left->left = new Node(4);
     n1->left->right = new Node(5);
     n1->right->left = new Node(6);
     n1->right->right = new Node(7);
     n1->printTree();
     cout<<"Height of tree is: ";
    // n1->height();
    cout<<endl<<"Breath First Search: ";
    breathFirstSearch(n1);
    cout<<endl<<"Depth First Search: ";
    depthFirstSearch(n1);
    

}