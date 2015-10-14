#include "linkedlist.h"

struct ListNode *reverseBetween(struct ListNode *head, int m, int n)
{
	if (head == NULL || head->next == NULL || m == n)
		return head;
	struct ListNode *start, *end, *cur = head, *temp1 = NULL, *temp2 = NULL;
	int i = 1;

	for (i = 1; i < m - 1; i++) 
		cur = cur->next;

	if (m > 1) {
		start = cur;
		cur = cur->next;
	} else {
		i--;
	}
	end = cur;
	for (; i < n; i++) {
		temp1 = cur->next;
		cur->next = temp2;
		temp2 = cur;
		cur = temp1;
	}
	if (m > 1) {
		start->next = temp2;
		end->next = temp1;
		return head;
	} else {
		end->next = temp1;
		return temp2;
	}	
}

