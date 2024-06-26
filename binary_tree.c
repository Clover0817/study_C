#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h> 
#include <stdlib.h> 
#include <memory.h> 
#define TRUE 1 
#define FALSE 0 
#define MAX_TREE_SIZE 20 

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode;

TreeNode n1 = { 15, NULL, NULL };
TreeNode n2 = { 4, &n1, NULL };
TreeNode n3 = { 16, NULL, NULL };
TreeNode n4 = { 25, NULL, NULL };
TreeNode n5 = { 15, &n3, &n4 };
TreeNode n6 = { 15, &n2, &n5 };
TreeNode* root = &n6;

TreeNode m1 = { 15, NULL, NULL };
TreeNode m2 = { 4, &n1, NULL };
TreeNode m3 = { 16, NULL, NULL };
TreeNode m7 = { 28, NULL, NULL }; 
TreeNode m4 = { 25, NULL, &m7 };
TreeNode m5 = { 15, &m3, &m4 };
TreeNode m6 = { 15, &m2, &m5 };
TreeNode* root2 = &m6;

int get_nonleaf_count(TreeNode* t)
{
	int count = 0;

	if (t == NULL)
		return 0;
	if ((t->left != NULL) || (t->right != NULL))
		count = 1 + get_nonleaf_count(t->left) + get_nonleaf_count(t->right);

	return count;
}

int get_oneleaf_count(TreeNode* t)
{
	int count = 0;
	
	if (t == NULL)
		return 0;
	if (((t->left != NULL) && (t->right == NULL)) || ((t->left == NULL) && (t->right != NULL)))
		count = 1 + get_oneleaf_count(t->left) + get_oneleaf_count(t->right);
		
	return count;
}

int get_twoleaf_count(TreeNode* t)
{
	int count = 0;

	if (t == NULL)
		return 0;
	if ((t->left != NULL) && (t->right != NULL))
		count = 1 + get_twoleaf_count(t->left) + get_twoleaf_count(t->right);
	else 
		count = get_twoleaf_count(t->left) + get_twoleaf_count(t->right);
	return count;
}

int get_max(TreeNode* node)
{
	int mx = -1, m1, m2, m3;

	if (node == NULL)
		return mx;
	if (node != NULL) {
		m1 = node->data;
		m2 = get_max(node->left);
		m3 = get_max(node->right);
		mx = max(m1, m2);
		mx = max(mx, m3);
	}
	return mx;
}

int get_min(TreeNode* node)
{
	int mn = 9999, n1, n2, n3;

	if (node == NULL)
		return  mn;
	if (node != NULL) {
		n1 = node->data;
		n2 = get_min(node->left);
		n3 = get_min(node->right);
		mn = min(n1, n2);
		mn = min(mn, n3);
	}
	return mn;
}

void node_increase(TreeNode* node)
{
	if (node != NULL) {
		node->data++;
		node_increase(node->left);
		node_increase(node->right);
	}
}

int equal(TreeNode* t1, TreeNode* t2)
{
	if ((t1 != NULL) && (t2 != NULL)) {
		if (t1->data != t2->data)
			return 0;
		equal(t1->left, t2->left);
		equal(t1->right, t2->right);
	}
	else if ((t1 != NULL && t2 == NULL) || (t1 == NULL && t2 != NULL))
		return 0;
	return 1;
}

TreeNode* copy(TreeNode* t)
{
	TreeNode* new = (TreeNode*)malloc(sizeof(TreeNode));
	if (t == NULL)
		return NULL;
	new->data = t->data;
	new->left = copy(t->left);
	new->right = copy(t->right);
	return new;
}
void preorder(TreeNode* root)
{
	if (root != NULL) {
		printf("%d ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

int main(void)
{
	TreeNode* result[MAX_TREE_SIZE];
	TreeNode* clone;
	int i, num;
	printf("가)\n");
	printf("트리 root 중 비단말노드의 개수는 %d.\n", get_nonleaf_count(root));
	printf("트리 root2 중 비단말노드의 개수는 %d.\n", get_nonleaf_count(root2));
	printf("트리 root 중 자식이 하나만 있는 노드의 개수는 %d.\n", get_oneleaf_count(root));
	printf("트리 root2 중 자식이 하나만 있는 노드의 개수는 %d.\n", get_oneleaf_count(root2));
	printf("트리 root 중 자식이 둘이 있는 노드의 개수는 %d.\n", get_twoleaf_count(root));
	printf("트리 root2 중 자식이 둘이 있는 노드의 개수는 %d.\n", get_twoleaf_count(root2));
	printf("트리 root 에서 가장 큰 수는 %d.\n", get_max(root));
	printf("트리 root2 에서 가장 큰 수는 %d.\n", get_max(root2));
	printf("트리 root 에서 가장 작은 수는 %d.\n", get_min(root));
	printf("트리 root2 에서 가장 작은 수는 %d.\n", get_min(root2));
	//printf("\n 나)\n");   -----search 함수 제외
	//num = search(root, 15, result);
	//for (i = 0; i < num; i++)
	//	printf("(0x%p, %d), ", result[i], result[i]->data);
	//printf("\n");
	printf("\n다)\n");
	preorder(root);
	node_increase(root);
	printf("\n");
	preorder(root);
	printf("\n");
	printf("%s\n", equal(root, root) ? "같다" : "다르다");
	printf("%s\n", equal(root2, root2) ? "같다" : "다르다");
	printf("%s\n", equal(root, root2) ? "같다" : "다르다");
	printf("\n라)\n");
	clone = copy(root);
	preorder(root);
	printf("\n");
	preorder(clone);
	printf("\n");
}
