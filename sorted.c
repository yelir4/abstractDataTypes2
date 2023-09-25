#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<stdbool.h>
#include "set.h"
// import necessary libraries and include the set header file

// coen 12 lab 2, sorted.c
// 10/06/21

typedef struct set SET;

struct set {
	int count; // number of elements
	int length; // max number of elements
	char **data; // pointer to array of words
};

/*	*createSet function
 *	@param maxElts length of set
 *	user will not pass in more words than maxElts
 *	@return pointer to new set of length maxElts
 *	@notation all cases O(1)
 */
SET *createSet(int maxElts) {
	SET *sp;
	sp = malloc(sizeof(struct set));
	assert(sp != NULL);
	sp->count = 0;
	sp->length = maxElts;
	sp->data = malloc(sizeof(char*)*maxElts);
	assert(sp->data != NULL);
	return sp;
}

/*	destroySet function
 *	@param *sp pointer of set to be 'destroyed'
 *	deallocates all memory used by sp, in reverse order
 *	starting with individual words, then the pointer
 *	to the words, and finally the set itself
 *	@notation all cases O(n) due to for loop
 */
void destroySet(SET *sp) {
	int i;
	assert(sp != NULL);
	for(i=0; i<sp->count; i++)
		free(sp->data[i]);
	free(sp->data);
	free(sp);
}

/* 	numElements function
 *	@param *sp pointer to set
 *	@return number of elements in sp
 *	@notation all cases O(1)
 */ 
int numElements(SET *sp) {
	assert(sp != NULL);
	return sp->count;
}

/*	search function
 *	@param *sp pointer to set
 *	@param *target pointer to word to search for in sp
 *	@param *found pointer to boolean, declare true if target found, false otherwise
 *	@return index of mid if found, lo otherwise
 *	@notation all cases O(log(n)) due to binary search
 */
static int search(SET *sp, char *target, bool *found) {
	assert(sp != NULL);
	assert(target != NULL);
	assert(found != NULL);
	int lo, hi, mid, diff;
	lo = 0;
	hi = sp->count-1;

	while(lo<=hi) {
		mid = (lo+hi)/2;
		diff = strcmp(target, sp->data[mid]);
		if(diff<0) // word is not to the right, change high bound
			hi = mid-1;
		else if(diff>0) // word not to the left, change low bound
			lo = mid+1;
		else { // diff == 0, target must be mid
			*found = true;
			return mid;
		}
	} // end of while loop
	*found = false;
	return lo;

}

/*	addElement function
 *	@param *sp pointer to set
 *	@param *elt pointer to word to add to sp
 *	adds elt to sp in sorted order if search returns found false
 *	@notation all cases O(n) due to for loop
 */
void addElement(SET *sp, char *elt) {
	int locn;
	bool found;
	assert(sp != NULL);
	assert(elt != NULL);
	locn = search(sp, elt, &found);
	
	// if not found, shift elements with for loop, insert elt, increment count
	if(!found) {
		int i;
		for(i=sp->count; i>locn; i--) {
			sp->data[i] = sp->data[i-1];
		}
		sp->data[locn] = strdup(elt);
		sp->count++;
	}
}

/*	removeElement function
 *	@param *sp pointer to set
 *	@param *elt pointer to word to remove from sp
 *	removes elt from sp if search returns found true
 *	@notation all cases O(n) due to for loop
 */
void removeElement(SET *sp, char *elt) {
	int locn;
	bool found;
	assert(sp != NULL);
	assert(elt != NULL);
	locn = search(sp, elt, &found);

	// if found, free memory, shift elements with for loop, decrement count
	if(found) {
		free(sp->data[locn]);
		int i;
		for(i=locn; i<sp->count-1; i++) {
			sp->data[i] = sp->data[i+1];
		}
		sp->count--;
	}
}

/*	*findElement function
 *	@param *sp pointer to set
 *	@param *elt pointer to word to return if found in sp
 *	@return pointer to copy of elt if found, null otherwise
 *	@notation all cases O(log(n)) due to search
 */
char *findElement(SET *sp, char *elt) {
	int locn;
	bool found;
	assert(sp != NULL);
	assert(elt != NULL);
	locn = search(sp, elt, &found);
	if(found) {
		return strdup(sp->data[locn]);
	}
	return NULL;
}

/*	**getElements function
 *	@param *sp pointer to set
 *	@return pointer to array of words in sp
 *	@notation all cases O(n) due to memcpy
 */
char **getElements(SET *sp) {
	assert(sp != NULL);
	char **copy;
	copy = malloc(sizeof(char*)*sp->count);
	memcpy(copy, sp->data, sizeof(char*)*sp->count);
	assert(copy != NULL);
	return copy;
}
