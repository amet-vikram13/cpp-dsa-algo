#include <iostream>
using namespace std;

struct Node
{
	int data;
	struct Node * left;
	struct Node * right;
};

bool isIdentical(struct Node * r1,struct Node * r2)
{
	if(!r1 && !r2)
		return true;
	
	else if(!r1 || !r2)
		return false;
	
	else
	{
		bool flag;
		if(r1->data==r2->data)
			flag = true;
		else
			flag = false;

		flag = flag && isIdentical(r1->left,r2->left);
		flag = flag && isIdentical(r1->right,r2->right);		

		return flag;
	}

}

bool chkMirror(struct Node * r1,struct Node * r2)
{
    if(!r1 && !r2)
        return true;
    else if(!r1 || !r2)
        return false;
    else
    {
        bool flag;
        if(r1->data==r2->data)
            flag = true;
        else
            flag = false;
        flag = flag && chkMirror(r1->left,r2->right);
        flag = flag && chkMirror(r1->right,r2->left);
        return flag;
    }
}


int main()
{
	return 0;
}