#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include "set.h"
// import necessary libraries and include the set header file

// coen 12 lab 2, unsorted.c
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
 *	@return index of target if found, -1 otherwise
 *	@notation all cases O(n) due to for loop
 */
static int search(SET *sp, char *target) {
	int i;
	assert(sp!=NULL);
	assert(target!=NULL);
	for(i=0; i<sp->count; i++) {
		// compare word in set to word passed in
		if(strcmp(sp->data[i], target)==0)
			return i;
	}
	return -1;
}

/*	addElement function
 *	@param *sp pointer to set
 *	@param *elt pointer to word to add to sp
 *	adds elt to end of sp if search returns -1 (not found in set)
 *	@notation all cases O(n) due to search
 */
void addElement(SET *sp, char *elt) {
	int i;
	assert(sp != NULL);
	assert(elt != NULL);
	if((i=search(sp, elt)) == -1) {
		sp->data[sp->count] = strdup(elt);
		sp->count++;
	}
}

/*	removeElement function
 *	@param *sp pointer to set
 *	@param *elt pointer to word to remove from sp
 *	removes elt from sp if valid index returned (found in set)
 *	@notation all cases O(n) due to search
 */
void removeElement(SET *sp, char *elt) {
	int i;
	assert(sp != NULL);
	assert(elt != NULL);
	if((i=search(sp, elt)) != -1) {
		free(sp->data[i]);
		sp->count--;
		sp->data[i] = sp->data[sp->count];
	}
}

/*	*findElement function
 *	@param *sp pointer to set
 *	@param *elt pointer to word to return if found in sp
 *	@return pointer to copy of elt if found, null otherwise
 *	@notation all cases O(n) due to search
 */
char *findElement(SET *sp, char *elt) {
	int i;
	assert(sp != NULL);
	assert(elt != NULL);
	if((i=search(sp, elt) != -1))
		return strdup(sp->data[i]);
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
