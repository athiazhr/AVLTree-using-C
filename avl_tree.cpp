#include<stdio.h>
#include<stdlib.h>

// AVL Tree
// b. Write a program to insert, delete and print datas from AVL Tree insertion in C Program

struct node{
	int nomor;
	int height;
	node *left, *right;
};

int max(int x, int y){
	return(x > y) ? x : y;
}

int get_height(struct node* Node){
	if(!Node)
		return 0;
	return Node->height;
}

int getbalanceFact(struct node* Node){
	if(!Node)
		return 0;
	return get_height(Node->left) - get_height(Node->right);
}

struct node* createNode(int nomor){
	struct node* node_new=(struct node*)malloc(sizeof(struct node));
	node_new->nomor = nomor;
	node_new->left = NULL;
	node_new->right = NULL;
	node_new->height = 1;
	return node_new;
}

node *rightRotate(node *Node){
	node *left = Node->left;
	node *leftRight = left->right;
	
	left->right = Node;
	Node->left = leftRight;
	
	Node->height = max(get_height(Node->left), get_height(Node->right)) + 1;
	left->height = max(get_height(left->left), get_height(left->right)) + 1;
	
	return left;
}

node *leftRotate( node *Node){
	node *right = Node->right;
	node *rightLeft = right->left;
	
	right->left = Node;
	Node->right = rightLeft;
	
	Node->height = max(get_height(Node->right), get_height(Node->left)) + 1;
	right->height = max(get_height(right->right), get_height(right->left)) + 1;
	
	return right;
}

node* insertion(struct node* Node, int nomor){
	if(!Node)
		return createNode(nomor);
		
	if(nomor < Node->nomor)
		Node->left = insertion(Node->left,nomor);
	else if(nomor > Node->nomor)
		Node->right = insertion(Node->right,nomor);
	else
		return Node;
	
	Node->height = 1 + max(get_height(Node->left), get_height(Node->right));
	int balanceFactor = getbalanceFact(Node);	
	
	if(balanceFactor > 1 && nomor < Node->left->nomor)
		return rightRotate(Node);
	if(balanceFactor < -1 && nomor > Node->right->nomor)
		return leftRotate(Node);
	if(balanceFactor > 1 && nomor > Node->left->nomor){
		Node->left = leftRotate(Node->left);
		return rightRotate(Node);
	}
	if(balanceFactor < -1 && nomor < Node->right->nomor){
		Node->right = rightRotate(Node->right);
		return leftRotate(Node);
	}
	return Node;	
}

node* minimum_value(struct node* Node){
	struct node* current = Node;
	while(current->left != NULL)
		current = current->left;
	return current;
}

node* delete_node(struct node* Node, int nomor){
	if(!Node){
		printf("Data not found\n");
		return Node;
	}
		
		
	if(nomor < Node->nomor)
		Node->left = delete_node(Node->left,nomor);
	else if(nomor > Node->nomor)
		Node->right = delete_node(Node->right,nomor);
	else{
		if((Node->left == NULL) || (Node->right == NULL)){
			struct node* temp = Node->left ? Node->left : Node->right;
	
			if(temp == NULL){
				temp = Node;
				Node = NULL;
			}else
				*Node = *temp;
				
			free(temp);	
			printf("Data found\n");
			printf("Value %d was deleted\n", nomor);
		}else{
			struct node* temp = minimum_value(Node->right);
			Node->nomor = temp->nomor;
			Node->right = delete_node(Node->right,temp->nomor);
		}
	}
	if(Node == NULL)
		return Node;
	
	Node->height = 1 + max(get_height(Node->left), get_height(Node->right));
	int balanceFactor = getbalanceFact(Node);	
	
	if(balanceFactor > 1 && getbalanceFact(Node->left) >= 0)
		return rightRotate(Node);
	if(balanceFactor > 1 && getbalanceFact(Node->left) < 0){
		Node->left = leftRotate(Node->left);
		return rightRotate(Node);
	}
	if(balanceFactor < -1 && getbalanceFact(Node->right) <= 0)
		return leftRotate(Node);
	
	if(balanceFactor < -1 && getbalanceFact(Node->right) > 0){

		Node->right = rightRotate(Node->right);
		return leftRotate(Node);
	}
	return Node;	
}

void preOrder(struct node* Node){
	if(Node != NULL){
		printf("%d ", Node->nomor);
		preOrder(Node->left);
		preOrder(Node->right);
	}
}

void inOrder(struct node* Node){
	if(Node != NULL){
		inOrder(Node->left);
		printf("%d ", Node->nomor);
		inOrder(Node->right);
	}
}

void postOrder(struct node* Node){
	if(Node != NULL){
		postOrder(Node->left);
		postOrder(Node->right);
		printf("%d ", Node->nomor);
	}
}

int main(){
	struct node* Node = NULL;
	int opt, nomor;
	
	while(1){
		printf("1. Insertion\n");
		printf("2. Deletion\n");
		printf("3. Traversal\n");
		printf("4. Exit\n");
		printf("Choose: ");
		scanf("%d", &opt);
		
		switch(opt){
			case 1:
				printf("Insert: ");
				scanf("%d", &nomor);
				Node = insertion(Node,nomor);
				break;
			case 2:
				printf("Delete: ");
				scanf("%d", &nomor);
				Node = delete_node(Node,nomor);
				break;
			case 3:
				printf("Preorder: ");
				preOrder(Node);
				printf("\n");
				printf("Inorder: ");
				inOrder(Node);
				printf("\n");
				printf("Postorder: ");
				postOrder(Node);
				printf("\n");
				break;
			case 4:
				printf("Thank you\n");
				exit(0);
			default:
				printf("Invalid choice!\n");
		}
	}
	
	return 0;
}
