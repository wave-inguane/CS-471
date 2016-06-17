#include <stdio.h>
#include <assert.h>
#include "queue.h"

// Print out the index and the value of each element.
bool show_one(queue_element* elem, queue_function_args* args) {
  printf("Item %d == %d\n", *(int*) args, *(int*) elem);
  *(int*) args = *(int*) args + 1;
  return true;
}

int compare_elem(queue_element* e1, queue_element* e2){

		int i1 = *( int *) e1;
		int i2 = *( int *) e2;
		if (i1 < i2)
				return -1;
		if (i1 > i2)
				return 1;
		return 0;
	
}

int main(int argc, char* argv[]) {

		int index, array[] = { 9, 7, 4, 10, 1, 6, 1, 0 };
	  int len = sizeof(array)/sizeof(array[0]);

		queue* q = queue_create();
		assert(q != NULL);
		assert(queue_is_empty(q));
		assert(queue_size(q) == 0 );

	/*populate the queue*/
	for(index = 0; index < len; index++)
			queue_append(q, &array[index]);
		
	assert(!queue_is_empty(q));
	assert(queue_size(q) == 8 );

	index = 0;
	queue_apply(q, show_one, &index); 
	printf("\n");

	/************************************/
	printf("Reversed \n");
	queue_reverse(q);
	assert(!queue_is_empty(q));
	assert(queue_size(q) == 8 );

	index = 0;
	queue_apply(q, show_one, &index);//Wave Test
	printf("\n");

	/***********************************/
	printf("Sorted \n");
	queue_sort(q , &compare_elem);
	assert(!queue_is_empty(q));
	assert(queue_size(q) == 8 );

	index = 0;
	queue_apply(q, show_one, &index); 
	printf("\n");
  

  return 0;
}
