#include "linkedlist.h"

struct ListNode *detectCycle(struct ListNode *head)
{
	struct ListNode *slow, *fast;
	slow = fast = head;

	while (fast && fast->next && fast->next->next) {
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast) {
			while (head != slow) {
				slow = slow->next;
				head = head->next;
			}
			return head;
		}
	}
	return NULL;
}

