#include "tree.h"

void flatten(struct TreeNode* root) {
	struct TreeNode *temp;
	while (root){
		if (root->left) {
			temp = root->left;	
			while (temp->right) {				
				temp = temp->right;						
			}									
			temp->right = root->right;		
			root->right = root->left;
			root->left = NULL;											
		}
		root=root->right;
	}
}

