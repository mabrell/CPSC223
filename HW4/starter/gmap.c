#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "gmap.h"

#ifndef INITIAL_SIZE
#define INITIAL_SIZE 19

#endif

/**
 * Implementation File for gmap functions
 * Author: Mason Abrell
 * Pset 4
 * Date: 11/4/2023
 */

typedef struct node_list node;


struct _gmap{
	int size; //Length of the gmap array
	int el_stored; //number of elements stored
	node **table;
	size_t key_index;
	void *(*cp)(const void *a); //Deep copy maker
	int (*comp)(const void *b, const void *c); //comparison function
	size_t (*h)(const void *d); 
	void (*f)(void *); //destroy function
};

struct node_list {
	node *next;
	char* key;
	char* value;
};

//Creates a new, bigger table, rehashes into new table, then assigns
//new table to old gmap
void gmap_embiggen(gmap* m)
{
	size_t new_size = 2 * m->size;
	node** new_table = malloc(new_size * sizeof(node*));
	for (size_t i = 0; i < new_size; i++)
	{
		new_table[i] = NULL;
	}
	bool chain_cleared = false;

	for (size_t i = 0; i < m->size; i++)
	{
		node* current_node = m->table[i];
		if (current_node != NULL)
		{		
			chain_cleared = false;
			while (chain_cleared == false)
			{
				
				node* next_node = current_node->next;
				void* key = current_node->key;
				size_t hash_value = m->h(key)%(new_size);
				if (new_table[hash_value] == NULL)
				{
					new_table[hash_value] = current_node;
					current_node->next = NULL;
				}
				else
				{
					current_node->next = new_table[hash_value];
					new_table[hash_value] = current_node;
				}
				

				current_node = next_node;
				
				if (current_node == NULL)
				{
					chain_cleared = true;
				}
			}
		}
	}
	free(m->table);
	m->size = new_size;
	m->table = new_table;
}

//Shrinks down table and rehashes(should only be done if load < 1/4)
void gmap_shrink(gmap* m)
{
	size_t new_size = (m->size/4);
	node** new_table = malloc((new_size * sizeof(node*)));
	for (size_t i = 0; i < new_size; i++)
	{
		new_table[i] = NULL;
	}
	bool chain_cleared = false;

	for (size_t i = 0; i < m->size; i++)
	{
		node* current_node = m->table[i];
		if (current_node != NULL)
		{	
			chain_cleared = false;
			while (chain_cleared == false)
			{
				
				node* next_node = current_node->next;
				void* key = current_node->key;
				size_t hash_value = m->h(key)%(new_size);
				if (new_table[hash_value] == NULL)
				{
					new_table[hash_value] = current_node;
					current_node->next = NULL;
				}
				else
				{
					current_node->next = new_table[hash_value];
					new_table[hash_value] = current_node;
				}
				

				current_node = next_node;
				
				if (current_node == NULL)
				{
					chain_cleared = true;
				}
			}
		}
	}
	free(m->table);
	m->size = new_size;
	m->table = new_table;
}


/**
 * Used for gmap_put to report an allocation error through its return value.
 */
char *gmap_error = "error"; //might need "extern as a prefix"

/**
 * Creates an empty map that uses the given hash function.
 *
 * @param cp a pointer to a function that takes a pointer to a key and returns a pointer to a deep
 * copy of that key
 * @param comp a pointer to a function that takes two keys and returns the result of comparing them,
 * with return value as for strcmp
 * @param h a pointer to a function that takes a pointer to a key and returns its hash code
 * @param f a pointer to a function that takes a pointer to a copy of a key make by cp and frees it
 * @return a pointer to the new map or NULL if it could not be created;
 * it is the caller's responsibility to destroy the map
 */
gmap *gmap_create(void *(*cp)(const void *), int (*comp)(const void *, const void *), size_t (*h)(const void *), void (*f)(void *))
{

	if (h == NULL || cp == NULL || comp == NULL || f == NULL)
    {
        // one of the required functions was missing
        return NULL;
    }

	gmap *new_gmap = malloc(sizeof(gmap));
	new_gmap->cp = cp;
	new_gmap->comp = comp;
	new_gmap->h = h;
	new_gmap->f = f;
	new_gmap->size = INITIAL_SIZE;
	new_gmap->el_stored = 0;
	new_gmap->key_index = 0;
	new_gmap->table = malloc(new_gmap->size * sizeof(node*));
	for (size_t i = 0; i < INITIAL_SIZE; i++)
	{
		new_gmap->table[i] = NULL;
	}
	return new_gmap;
}

/**
 * Returns the number of (key, value) pairs in the given map. Behavior
 * is undefined if m is NULL.
 *
 * @param m a pointer to a map, non-NULL
 * @return the size of the map pointed to by m
 */
size_t gmap_size(const gmap *m)
{
	return m->el_stored; //They actually just want the # of elements stored
}

/**
 * Adds a copy of the given key with value to this map.  If the key is
 * already present then the old value is replaced and returned.  The
 * map copies the key, so the caller retains ownership of the original
 * key and may modify it or destroy it without affecting the map.  The
 * map copies the pointer to the value, but the caller retains
 * ownership of the value. Behavior is undefined if either m or key is
 * NULL.
 *
 * @param m a pointer to a map, non-NULL
 * @param key a pointer to a key, non-NULL
 * @param value a pointer to a value
 * @return a pointer to the old value, or NULL, or a pointer to gmap_error
 */
void *gmap_put(gmap *m, const void *key, void *value)
{
	if (m == NULL || key == NULL)
    {
        return NULL;
    }
	if (m->size == m->el_stored)
	{
		gmap_embiggen(m);
	}
	size_t hash_value = (m->h(key))%(m->size);
	bool key_found = false;
	node* current_node = m->table[hash_value];
	void* target_value;
	if (current_node == NULL)
	{
		void *copy = m->cp(key);
		if (copy != NULL)
		{
			node* new_node = malloc(sizeof(node));
			new_node->key = copy;
			new_node->value = value;
			m->el_stored++;
			new_node->next = NULL;
			m->table[hash_value] = new_node;
			return NULL;
		}
		else
		{
			m->f(copy);
			return NULL;
		}
	}
	
	while (key_found == false)
	{
		if((m->comp(key, current_node->key)) == 0) //if correct key is found,
		{                                         //return the old value
			target_value = current_node->value;
			current_node->value = value;
			return target_value;
		}
		else
		{
			//node* previous_node = NULL;
			if ((current_node->next) == NULL)//Here we need to add a new node
			{
				void *copy = m->cp(key);
				if (copy != NULL)
				{
					node* new_node = malloc(sizeof(node));
					new_node->key = copy;
					new_node->value = value;
					new_node->next = NULL;
					if (current_node != NULL)
					{
						current_node->next = new_node; //Stitches prior node
					}
					m->el_stored++;
					return NULL;
				}
				else
				{
					m->f(copy);
					return NULL;
				}
			}
			//previous_node = current_node;
			current_node = current_node->next;
		}

	}
	return NULL;
}

/**
 * Removes the given key and its associated value from the given map if
 * the key is present.  The return value is NULL and there is no effect
 * on the map if the key is not present.  The copy of the key held by
 * the map is destroyed.  It is the caller's responsibility to free the
 * returned value if necessary. Behavior is undefined if either m or key
 * is NULL.
 *
 * @param m a pointer to a map, non-NULL
 * @param key a key, non-NULL
 * @return the value associated with the removed key, or NULL
 */
void *gmap_remove(gmap *m, const void *key)
{
	if (m == NULL || key == NULL)
    {
        return NULL;
    }
	if (m->el_stored < (m->size /4))
	{
		gmap_shrink(m);
	}
	
	size_t hash_value = (m->h(key))%(m->size);
	bool key_found = false;
	node* current_node = m->table[hash_value];
	node* prior_node = NULL;
	while (key_found == false)
	{
		if((m->comp(key, current_node->key)) == 0)
		{
			void* temp_value_holder = current_node->value;
			if (prior_node != NULL)
			{
				prior_node->next = current_node->next;
			}
			if (prior_node == NULL)
			{
				m->table[hash_value] = current_node->next;
			}
			m->f(current_node->key);
			free(current_node);
			m->el_stored--;
			
			return temp_value_holder;
		}
		else
		{
			if (current_node->next == NULL)
			{
				return NULL;
			}
			prior_node = current_node;
			current_node = current_node->next;
		}
	}
	return NULL;
}

/**
 * Determines if the given key is present in this map. Behavior is undefined
 * if either m or key is NULL.
 *
 * @param m a pointer to a map, non-NULL
 * @param key a pointer to a key, non-NULL
 * @return true if a key equal to the one pointed to is present in this map,
 * false otherwise
 */
bool gmap_contains_key(const gmap *m, const void *key)
{
	if (m == NULL || key == NULL)
    {
        return NULL;
    }
	size_t hash_value = (m->h(key))%(m->size);
	bool key_found = false;
	node* current_node = m->table[hash_value];
	if (current_node == NULL)
	{
		return false;
	}
	while (key_found == false)
	{
		if((m->comp(key, current_node->key)) == 0)
		{
			return true;
		}
		else
		{
			if (current_node->next == NULL)
			{
				return false;
			}
			
			current_node = current_node->next;
		}

	}
	return false;
}

/**
 * Returns the value associated with the given key in this map.
 * If the key is not present in this map then the returned value is
 * NULL.  The pointer returned is the original pointer passed to gmap_put,
 * and it remains the responsibility of whatever called gmap_put to
 * release the value it points to (no ownership transfer results from
 * gmap_get). Behavior is undefined is either m or key is NULL.
 *
 * @param m a pointer to a map, non-NULL
 * @param key a pointer to a key, non-NULL
 * @return a pointer to the assocated value, or NULL if they key is not present
 */
void *gmap_get(gmap *m, const void *key)
{
	if (m == NULL || key == NULL)
    {
        return NULL;
    }
	size_t hash_value = (m->h(key))%(m->size);
	bool key_found = false;
	node* current_node = m->table[hash_value];

	while (key_found == false)
	{
		if (current_node == NULL)
		{
			return NULL;
		}
		if((m->comp(key, current_node->key)) == 0)
		{
			return current_node->value;
		}
		else
		{
			if (current_node->next == NULL)
			{
				return NULL;
			}
			
			current_node = current_node->next;
		}
	}
	return NULL;
}

/**
 * Calls the given function for each (key, value) pair in this map, passing
 * the extra argument (arg) as well. Behavior is undefined if either m or f
 * is NULL.
 *
 * @param m a pointer to a map, non-NULL
 * @param f a pointer to a function that takes a key, a value, and an
 * extra piece of information, and does not add or remove keys from the
 * map, non-NULL
 * @param arg a pointer
 */
void gmap_for_each(gmap *m, void (*f)(const void *, void *, void *), void *arg)
{
	if (m == NULL || f == NULL)
    {
        return;
    }
	bool chain_cleared = false;
	for (size_t i = 0; i < m->size; i++)
	{
		if (m->table[i] == NULL)
		{
			chain_cleared = true;
		}
		else
		{
			chain_cleared = false;
			node* current_node = m->table[i];
			while (chain_cleared == false)
			{
				node* next_node = current_node->next;
				f(current_node->key, current_node->value, arg);
				current_node = next_node;
				if (current_node == NULL)
				{
					chain_cleared = true;
				}
			}
			
		}
		
	}
}

void add_to_array(void* key, const void** keys_array)
{
	bool open_slot_found = false;
	size_t i = 0;
	while (open_slot_found == false)
	{
		if (keys_array[i] == NULL)
		{
			open_slot_found = true;
			keys_array[i] = key;
			return;
		}
		i++;
	}
}

/**
 * Returns an array containing pointers to all of the keys in the
 * given map.  The return value is NULL if there was an error
 * allocating the array.  The map retains ownership of the keys, and
 * the pointers to them are only valid as long until they are removed
 * from the map, or until the map is destroyed, whichever comes first.
 * It is the caller's responsibility to destroy the returned array if
 * it is non-NULL. Behavior is undefined is m is NULL.
 *
 * @param m a pointer to a map, non-NULL
 * @return a pointer to an array of pointers to the keys, or NULL
 */
const void **gmap_keys(gmap *m)
{
	if (m == NULL)
	{
		return NULL;
	}
	
	const void **keys_array = malloc(m->el_stored * sizeof(void*));
	for (size_t i = 0; i < m->el_stored; i++)
	{
		keys_array[i] = NULL;
	}

	bool chain_cleared = false;
	for (size_t i = 0; i < m->size; i++)
	{
		if (m->table[i] == NULL)
		{
			chain_cleared = true;
		}
		else
		{
			chain_cleared = false;
			node* current_node = m->table[i];
			while (chain_cleared == false)
			{
				node* next_node = current_node->next;
				add_to_array(current_node->key, keys_array);
				current_node = next_node;
				if (current_node == NULL)
				{
					chain_cleared = true;
				}
			}
			
		}
		
	}
	return keys_array;

}

/**
 * Destroys the given map.  There is no effect if the given pointer is NULL.
 *
 * @param m a pointer to a map, or NULL
 */
void gmap_destroy(gmap *m)
{
	if (m->el_stored == 0)
	{
		free(m->table);
		free(m);
		return;
	}
	else
	{
		bool chain_cleared = false;
		for (size_t i = 0; i < m->size; i++)
		{
			if (m->table[i] == NULL)
			{
				chain_cleared = true;
			}
			else
			{
				chain_cleared = false;
				node* current_node = m->table[i];
				while (chain_cleared == false)
				{
					node* next_node = current_node->next;
					free(current_node->key); 
					free(current_node);
					current_node = next_node;
					if (current_node == NULL)
					{
						chain_cleared = true;
					}
				}
				
			}
			
		}
		free(m->table);
		free(m);
		return;
		
	}
}




// Destroys the node and returns the pointer to the next node (if there is no
// next node, returns NULL
node* node_destroy(node* target)
{
	free(target->key);
	free(target->value);
	node* temp_node = target->next;
	free(target->next);
	return temp_node;
}