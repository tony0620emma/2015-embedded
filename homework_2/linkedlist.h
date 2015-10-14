#ifndef __LINKEDLIST_H
#define __LINKEDLIST_H

#include <string.h>
#include <stdlib.h>

struct ListNode {
	int val;
	struct ListNode *next;
};

/* 
 * create test linked-lists 
 * format :
 * 1,2,3,4,5 => 1->2->3->4->5->null 
 */
struct ListNode *test_case_creater(char *s)
{
	char *token;
	struct ListNode *head = NULL, *cur, *temp;
	token = strtok(s, ",");
	if (!token)
		return head;
	head = malloc(sizeof(struct ListNode));
	head->val = atoi(token);
	cur = head;

	while ((token = strtok(s, ","))) {
		temp = malloc(sizeof(struct ListNode));
		temp->val = atoi(token);
		cur->next = temp;
		cur = temp;
	}
	cur->next = NULL;
	return head;
}

#endif
