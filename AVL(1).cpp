#include<iostream>
#include<stdlib.h>
using namespace std;
template <class g>
class BST
{
	struct node
	{
		g data;
		node* left;
		node* right;
		int height;
	};
	node* root;
	void makempty(node* t)
	{
		if(t==NULL)
		return ;
		makempty(t->left);
		makempty(t->right);
		delete t;
	}
	node* insert(g x,node* t)
	{
		if(t==NULL)
		{
			t=new node;
			t->data=x;
			t->height=0;
			t->left=t->right=NULL;
		}
		else if(x<t->data)
		{
			t->left=insert(x,t->left);
			if((height(t->left)-height(t->right))==2)
			{
				if(x<t->left->data)
					t=singlerightrotate(t);
				else
					t=doublerightrotate(t); 
			}
		}
		else if(x>t->data)
		{
			t->right=insert(x,t->right);
			if((height(t->right)-height(t->left))==2)
			{
				if(x>t->right->data)
					t=singleleftrotate(t);
				else
					t=doubleleftrotate(t);
			}
		}
		t->height=max(height(t->left),height(t->right))+1;
		return t;
	}
	node* singlerightrotate(node* t)
	{
		node* u=t->left;
		t->left=u->right;
		u->right=t;
		t->height=max(height(t->left),height(t->right))+1;
		u->height=max(height(u->left),t->height);
		return u;
	}
	node* singleleftrotate(node* t)
	{
		node* u=t->right;
		t->right=u->left;
		u->left=t;
		t->height=max(height(t->left),height(t->right))+1;
		u->height=max(height(t->right),t->height)+1;
	}
	node* doubleleftrotate(node* t)
	{
		t->right=singlerightrotate(t->right);
		return singleleftrotate(t);
	}
	node* doublerighttrotate(node* t)
	{
		t->left=singleleftrotate(t->left);
		return singlerightrotate(t);
	}
	node* findmin(node* t)
	{
		if(t==NULL)
			return NULL;
		else if(t->left==NULL)
			return t;
		else
			findmin(t->left);
	}
	node* findmax(node* t)
	{
		if(t==NULL)
			return NULL;
		else if(t->right==NULL)
			return t;
		else
			findmax(t->right);
	}
	node* remove(g x,node* t)
	{
		node* temp;
		if(t==NULL)
		return NULL;
		else if(x<t->data)
		t->left=remove(x,t->left);
		else if(x>t->data)
		t->right=remove(x,t->right);
		
		else if(t->left && t->right)
		{
			temp=findmin(t->right);
			t->data=temp->data;
			t->right=remove(t->data,t->right);
		}
		else 
		{
			temp=t;
			if(t->left==NULL)
				t=t->right;
			else if(t->right==NULL)
				t=t->left;
			delete temp;
		}
		if(t==NULL)
		return t;
		t->height=max(height(t->left),height(t->right))+1;
		if(height(t->left)-height(t->right)==2)
		{
			if(height(t->left->left)-height(t->left->right)==1)
			t=singleleftrotate(t);
			else
			t=doubleleftrotate(t);
		}
		else if(height(t->right)-height(t->left)==2)
		{
			if(height(t->right->right)-height(t->right->left)==1)
			t=singlerightrotate(t);
			else
			t=doublerightrotate(t);
		}
		return t;
	}a
	void print(node* root,int level=0)
	{
		if(root==NULL)
		return;
		print(root->right,level+1);
		cout<<endl;
		for(int i=0;i<level;i++)
		cout<<"\t";
		cout<<root->data<<endl;
		print(root->left,level+1);
	}
	int height(node* t)
	{
		return (t==NULL?-1:t->height);
	}
	int getbalance(node* t)
	{
		if(t==NULL)
		return 0;
		else
		return (height(t->left)-height(t->right));	
	}
	void search(g x,node* t)
	{
		if(t==NULL)
			{
				cout<<"Element not found\n";
				return ;
			}
		else if(t->data==x)
		{
			cout<<"Element found\n";
			return ;
		}
		else if(x<t->data)
		{
			return search(x,t->left);
		}
		else
		return search(x,t->right);
	}
	void inorder(node* t)
	{
		if(t==NULL)
		return ;
		inorder(t->left);
		cout<<t->data<<" ";
		inorder(t->right);
	}
	public:
		BST()
		{
			root=NULL;
		}
		void insert(g x)
		{
			root=insert(x,root);
		}
		void remove(g x)
		{
			root=remove(x,root);
		}
		void search(g x)
		{
			search(x,root);
		}
		void print()
		{
			print(root,0);
		}
		void display()
		{
			inorder(root);
			cout<<endl;
		}
};
int main()
{
	BST <int> t;
	int val;
	int ch,n;
	while(true)
	{
		cout<<"1.Create\n2.Insert\n3.Delete\n4.Search\n5.Inorder\n6.Print\n";
		cin>>ch;
		switch(ch)
		{
			case 1:
				cout<<"Enter number of values:";
				cin>>n;
				for(int i=0;i<n;i++)
				{
					cout<<"\nEnter values:";
					cin>>val;
					t.insert(val);
				}
				printf("The AVL tree after creating:");
				t.display();
				break;
			case 2:
				cout<<"Enter value";
				cin>>val;
				t.insert(val);
				printf("The AVL tree after inserting:");
				t.display();
				break;
			case 3:
				cout<<"Enter ele to be deleted:";
				cin>>val;
				t.remove(val);
				printf("The AVL tree after deleting:");
				t.display();
				break;				
			case 4:
				cout<<"Enter ele to be searched:";
				cin>>val;
				t.search(val);
				break;
			case 5:
				t.display();
				break;
			case 6:
				t.print();
				break;
			default:
				break;
		}	
	}
}
