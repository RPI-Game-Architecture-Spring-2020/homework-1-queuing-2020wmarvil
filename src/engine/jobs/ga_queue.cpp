/*
** RPI Game Architecture Engine
**
** Portions adapted from:
** Viper Engine - Copyright (C) 2016 Velan Studios - All Rights Reserved
**
** This file is distributed under the MIT License. See LICENSE.txt.
*/

#include "ga_queue.h"

ga_queue::ga_queue(int node_count)
{
	ga_node* node = new ga_node();
	node->next = NULL;

	head = tail = new ga_node();

	count = 0;
	max_count = node_count; // unused
}

ga_queue::~ga_queue()
{
	void* value;

	bool not_empty = pop(&value);
	while (not_empty) {
		not_empty = pop(&value);
	}

	free(head);
}

void ga_queue::push(void* data)
{
	// TODO:
	// Push 'data' onto the queue in a thread-safe manner.
	// If you preallocated 'node_count' elements, and if the queue is full when
	// this function is called, you must block until another thread pops an
	// element off the queue.
	// See https://www.research.ibm.com/people/m/michael/podc-1996.pdf

	ga_node* node = new ga_node();
	node->value = data;
	node->next = NULL;

	tail_lock.lock();

	tail->next = node;
	tail = node;

	tail_lock.unlock();

	count++;
}

bool ga_queue::pop(void** data)
{
	// TODO:
	// Pop one element off the queue in a thread-safe manner and place it in
	// the memory pointed to by 'data'.
	// If the queue is empty when this function is called, return false.
	// Otherwise return true.
	// See https://www.research.ibm.com/people/m/michael/podc-1996.pdf

	head_lock.lock();

	ga_node* node = head;
	ga_node* new_head = node->next;

	if (!new_head) {
		head_lock.unlock();
		return false;
	}

	*data = new_head->value;
	head = new_head;

	head_lock.unlock();

	free(node);
	count--;

	return true;
}

int ga_queue::get_count() const
{
	return count;
}
