#pragma once

/*
** RPI Game Architecture Engine
**
** Portions adapted from:
** Viper Engine - Copyright (C) 2016 Velan Studios - All Rights Reserved
**
** This file is distributed under the MIT License. See LICENSE.txt.
*/

/*
** Thread-safe queue.
** https://www.research.ibm.com/people/m/michael/podc-1996.pdf
*/

#include <mutex>
#include <thread>

class ga_queue
{
public:
	struct ga_node {
		void* value;
		ga_node* next;
	};

	ga_queue(int node_count);
	~ga_queue();

	void push(void* data);
	bool pop(void** data);

	int get_count() const;
private:
	ga_node* head;
	ga_node* tail;
	std::mutex head_lock;
	std::mutex tail_lock;
	int count, max_count;
};
