#define MAX 78 /* from '.' to lower alphabeta in ASCII */
/* make a struct */
struct TreeNode{
	int n;
	struct TreeNode *next[MAX];
};

/* create a struct and initialize */
struct TreeNode *create(){
	int i;
	struct TreeNode *p; 
	p = (struct TreeNode *)alloc(sizeof(struct TreeNode *)*MAX);
	p->n = 1;
	for (i = 0; i < MAX; i++)
		p->next[i]=NULL;
	return p;
}

/* insert a string into the tree */
void insert(struct TreeNode *root, char *s){
	int i = 0;
	struct TreeNode *p = root;
	struct TreeccNode *temp = NULL;
	int length = strlen(s);
	for(; i < length; i++){
        	if(p->next[s[i] - '.'] == NULL)
			p->next[s[i] - '.'] =create();
                else
			p->next[s[i] - '.']->n++;
		p = p->next[s[i] - '.'];
	}
}

/* search the string in the tree */
int search(struct TreeNode *root, char *s){
	if (root ==NULL)
		return 0;
	struct TreeNode *p = root;
	int i = 0;
	int length = strlen(s);
	for(; i < length; i++){
        	if(p->next[s[i] - '.'] == NULL) 
			return 0;
        	p = p->next[s[i] - '.'];
	}
	return p->n;
}

/* delete a struct TreeNode */
void delete(struct TreeNode *root){
	int i;
	for(i = 0; i < MAX; i++){
		if(root->next[i] != NULL)
			delete(root->next[i]);
	}
	free(root);
}
