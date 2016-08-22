/* Implements queue abstract data type. */
/*http://courses.cs.washington.edu/courses/cse451/15wi/projects/project0.html */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/* Each link in the queue stores a queue_element and
 * a pointer to the next link in the queue. */
typedef struct _queue_link {
  queue_element* elem;//same as void* elem
  struct _queue_link* next;//next link
} queue_link;

/* This is the actual implementation of the queue struct that
 * is declared in queue.h. */
struct _queue {
  queue_link* head;
};

queue* queue_create() {
  queue* q = ( queue*) malloc(sizeof(queue));
	if ( !q){
			 fputs("malloc failed in  queue_create() \n",stdout);
			return NULL;
	}	
  q->head = NULL;
  return q;
}

/* Private ** */
static queue_link* queue_new_element(queue_element* e) {
  queue_link* ql = (queue_link*) malloc(sizeof(queue_link));

  ql->elem = e;
  ql->next = NULL;

  return ql;
}

void queue_append(queue* q, queue_element* e) 
{ 
	assert(q != NULL);

	//If e is the first element 
	if (q->head==NULL){
 	 	 q->head = queue_new_element(e);
		 return;
	}
	else
	{
		// Find the last link in the queue.
		queue_link* cur;
		for (cur = q->head; cur->next ; cur = cur->next);

 		// Append the new link.
		cur->next= queue_new_element(e);
	}
}

bool queue_remove(queue* q, queue_element** elem_ptr) {
  queue_link* old_head;

  assert(q != NULL);
  assert(elem_ptr != NULL);
  if (queue_is_empty(q)) {
    return false;
  }

  *elem_ptr = q->head->elem;
  old_head = q->head;
  //q->head = q->head->next;   //commenetd by Wave
	q->head = old_head->next; //Wave 
		free(old_head);
	 	return true;
}

bool queue_is_empty(queue* q) {
  assert(q != NULL);
  return q->head == NULL;
}

/* private */
static bool queue_count_one(queue_element* elem, queue_function_args* args) {
  size_t* count = (size_t*) args;
  *count = *count + 1;
  return true;
}

size_t queue_size(queue* q) {
  size_t count = 0;
  queue_apply(q, queue_count_one, &count);
  return count;
}

bool queue_apply(queue* q, queue_function qf, queue_function_args* args) {
  assert(q != NULL && qf != NULL);

  if (queue_is_empty(q))
    return false;

  for (queue_link* cur = q->head; cur; cur = cur->next) {
    if (!qf(cur->elem, args))
      break;
  }

  return true;
}


void queue_reverse(queue* q){
  			assert(q != NULL);

		if(queue_is_empty(q) || queue_size(q)==1){
		// Nothing to reverse
		// A queue size of 1 also has nothing to reverse,
	
    return;
  }	
 queue_link* cur = q->head;
 q->head = NULL;
 queue_link* next_elem;

// Treat new_head as a stack and push the queue onto it
 for(; cur != NULL; cur = next_elem){
     next_elem = cur->next;
 
  	cur->next = q->head;
     q->head = cur;
   }
	}

void queue_sort(queue* q, queue_compare qc){
	
		assert(q != NULL);

		size_t qs = queue_size(q);
		if(qs < 2)
				return;

		bool swapped;
		do{
			queue_link* cur = q->head;
			swapped = false;

			while(cur->next){
					int result = qc(cur->elem, cur->next->elem);

					if(result > 0){
						queue_element* temp;
						temp = cur->elem;
						cur->elem = cur->next->elem;
						cur->next->elem = temp;
						swapped = true;
					}
					cur = cur->next;
			}
		}while(swapped);
}

void queue_destroy(queue* q){
	queue_link* cur;
	queue_link* next;
	if(q){
		cur = q->head;
		while(cur){
			next = cur->next;
			free(cur);
			cur = next;
		}
		free(q);
		}
}

