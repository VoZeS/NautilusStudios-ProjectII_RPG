#ifndef __LIST_H__
#define __LIST_H__

#include "Defs.h"

// Contains items from double linked list
template<class tdata>
struct ListItem
{
	tdata data;
	ListItem<tdata>* next;
	ListItem<tdata>* prev;

	inline ListItem(const tdata& _data)
	{
		data = _data;
		next = prev = NULL;
	}

	~ListItem()
	{}
};

// Manages a double linked list
template<class tdata>
class List
{

public:

	ListItem<tdata>* start;
	ListItem<tdata>* end;

private:

	unsigned int size;

public:

	// Constructor
	inline List()
	{
		start = end = NULL;
		size = 0;
	}

	// Destructor
	~List()
	{
		Clear();
	}

	// Get Size
	unsigned int Count() const
	{
		return size;
	}

	// Add new item
	ListItem<tdata>* Add(const tdata& item)
	{
		ListItem<tdata>* dataItem;
		dataItem = new ListItem<tdata>(item);

		if(start == NULL)
		{
			start = end = dataItem;
		}
		else
		{
			dataItem->prev = end;
			end->next = dataItem;
			end = dataItem;
		}

		++size;
		return(dataItem);
	}

	// Deletes an item from the list
	bool Del(ListItem<tdata>* item)
	{
		if(item == NULL)
		{
			return (false);
		}

		// Now reconstruct the list
		if(item->prev != NULL)
		{
			item->prev->next = item->next;

			if(item->next != NULL)
			{
				item->next->prev = item->prev;
			}
			else
			{
				end = item->prev;
			}
		}
		else
		{
			if(item->next)
			{
				item->next->prev = NULL;
				start = item->next;
			}
			else
			{
				start = end = NULL;
			}
		}

		RELEASE(item);
		--size;
		return(true);
	}

	// Destroy and free all mem
	void Clear()
	{
		ListItem<tdata>* p_data;
		ListItem<tdata>* p_next;
		p_data = start;

		while(p_data != NULL)
		{
			p_next = p_data->next;
			RELEASE(p_data);
			p_data = p_next;
		}

		start = end = NULL;
		size = 0;
	}

	// Read/write operator access directly to a position in the list
	tdata& operator [](const unsigned int index)
	{
		long pos;
		ListItem<tdata>* p_item;
		pos = 0;
		p_item = start;

		while(p_item != NULL)
		{
			if(pos == index)
			{
				break;
			}

			++pos;
			p_item = p_item->next;
		}

		return(p_item->data);
	}

	/**
	* const read operator access directly to a position in the list
	*/
	const tdata& operator [](const unsigned int index) const
	{
		long				  pos;
		ListItem<tdata>*   p_item;
		pos = 0;
		p_item = start;

		while(p_item != NULL)
		{
			if(pos == index)
			{
				break;
			}

			++pos;
			p_item = p_item->next;
		}

		ASSERT(p_item);

		return(p_item->data);
	}

	/**
	* const read operator access directly to a position in the list
	*/
	const List<tdata>& operator +=(const List<tdata>& other_list)
	{
		ListItem<tdata>*   p_item = other_list.start;

		while(p_item != NULL)
		{
			add(p_item->data);
			p_item = p_item->next;
		}

		return(*this);
	}

	/**
	* const access to a node in a position in the list
	*/
	const ListItem<tdata>* At(unsigned int index) const
	{
		long				  pos = 0;
		ListItem<tdata>*   p_item = start;

		while(p_item != NULL)
		{
			if(pos++ == index)
				break;

			p_item = p_item->next;
		}

		return p_item;
	}

	/**
	* access to a node in a position in the list
	*/
	ListItem<tdata>* At(unsigned int index)
	{
		long				  pos = 0;
		ListItem<tdata>*   p_item = start;

		while(p_item != NULL)
		{
			if(pos++ == index)
				break;

			p_item = p_item->next;
		}

		return p_item;
	}

	// Sort
	int BubbleSort()
	{
		int ret = 0;
		bool swapped = true;

		while(swapped)
		{
			swapped = false;
			ListItem<tdata>* tmp = start;

			while(tmp != NULL && tmp->next != NULL)
			{
				++ret;
				if(tmp->data > tmp->next->data)
				{
					SWAP(tmp->data, tmp->next->data);
					swapped = true;
				}

				tmp = tmp->next;
			}
		}

		return ret;
	}

	/**
	* returns the first apperance of data as index (-1 if not found)
	*/
	int Find(const tdata& data)
	{
		ListItem<tdata>* tmp = start;
		int index = 0;

		while(tmp != NULL)
		{
			if(tmp->data == data)
				return(index);

			++index;
			tmp = tmp->next;
		}
		return (-1);
	}

	void InsertAfter(uint position, const List<tdata>& list)
	{
		ListItem<tdata>* p_my_list = At(position);
		ListItem<tdata>* p_other_list = list.start;

		while(p_other_list != NULL)
		{
			ListItem<tdata>* p_new_item = new ListItem<tdata>(p_other_list->data);

			p_new_item->next = (p_my_list) ? p_my_list->next : NULL;

			if(p_new_item->next != NULL)
				p_new_item->next->prev = p_new_item;
			else
				end = p_new_item;

			p_new_item->prev = p_my_list;

			if(p_new_item->prev != NULL)
				p_new_item->prev->next = p_new_item;
			else
				start = p_new_item;

			p_my_list = p_new_item;
			p_other_list = p_other_list->next;
		}
	}
};
#endif // LIST_H__