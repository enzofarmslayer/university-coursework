#include "list.h"
#include "stdio.h"
#include <stdlib.h>

int main()
{
    /*  This is called a sentinel node. It's not really a part of the list,
     *  it's just used to hold on to the list to be able to avoid certain
     *  special cases in the list implementation, and to make the solution
     *  slightly eaiser.
     */
	struct list_item root;
	root.value = -1;
	root.next = NULL;

	append(&root, 2);
	append(&root, 2);
	append(&root, 3);
	append(&root, 5);
	input_sorted(&root, 1);
	//clear(&root);
	print(&root);
	clear(&root);
	print(&root);

	/* Write your test cases here */
	return 0;
}
