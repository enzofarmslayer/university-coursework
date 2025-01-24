#include "list.h"
#include "stdio.h"
#include <stdlib.h>

int main()
{
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
