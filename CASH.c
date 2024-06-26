#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node node;
typedef struct LinkedList LinkedList;
typedef struct hashnode hashnode;
typedef struct Hash Hash;
typedef struct cash cash;

struct node
{
	int val;
	node * next;
	node * prev;
};

struct LinkedList
{
	int size;
	int now_size;
	node * head;
	node * tail;
};

struct hashnode
{
	int value;
	node * point;
};

struct Hash
{
	int capacity;
	hashnode **array;
};

struct cash
{
	LinkedList * list;
	Hash * table;
	int size_L;
	int size_T;

};

//LIST
node* create_node();
LinkedList* List(int size);
void list_free(LinkedList **list);
void pushFront(LinkedList *list, int data);
void popBack(LinkedList *list);
//HASH
hashnode* create_node_h(int value, node *point);
Hash* delete_from_hash(Hash *hash, int k);
hashnode **init_array(int capacity);
Hash* create_HASH_TABLE(int size_Table);
void free_item(hashnode *node);
void free_HASH(Hash *hash);
int find_element_in_hash(Hash *hash, int page);
int search_for_empty_place_in_hash(Hash *hash);
void add_value_to_hash(int page, node *list, Hash *hash, int i);
void hash_add(cash *cash, int page, node *list);
void hash_delete(cash *cash, int page);
//CASH
cash* init_cash(int size_List, int size_Table);
void free_cash(cash *CASH);
void push(cash *cash, int page);
void exchange(cash *cash, int data);
//
int init_value_in_list(cash *Cash, int page);
int print(cash *cash, int *array, int size);

//LIST
node* create_node()
{
	node *new_node = (node*) malloc(sizeof(node));
	return new_node;
}

LinkedList* List(int size)
{
	LinkedList *list = NULL;
	list = (LinkedList*) malloc((sizeof(LinkedList)));
	list->size = size;
	list->now_size = 0;
	list->head = NULL;
	list->tail = NULL;

	return list;

}

void list_free(LinkedList **list)
{
	node *tmp = (*list)->head;
	node *next = NULL;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}

	free(*list);
	(*list) = NULL;
}

void pushFront(LinkedList *list, int data)
{
	node *tmp = (node*) malloc(sizeof(node));
	if (tmp == NULL)
	{
		exit(1);
	}

	tmp->val = data;
	tmp->next = list->head;
	tmp->prev = NULL;
	if (list->head)
	{
		list->head->prev = tmp;
	}

	list->head = tmp;

	if (list->tail == NULL)
	{
		list->tail = tmp;
	}

	list->now_size++;
}

void popBack(LinkedList *list)
{
	node * next;
	if (list->tail == NULL)
	{
		exit(4);
	}

	next = list->tail;
	list->tail = list->tail->prev;
	if (list->tail)
	{
		list->tail->next = NULL;
	}

	if (next == list->head)
	{
		list->head = NULL;
	}

	free(next);

	list->now_size--;

}

//HASH

hashnode* create_node_h(int value, node *point)
{
	hashnode *tmp = NULL;
	tmp = (hashnode*) malloc(sizeof(hashnode));
	tmp->value = value;
	tmp->point = point;
	return tmp;
}

Hash* delete_from_hash(Hash *hash, int k)
{
	(hash->array)[k]->value = 0;
	(hash->array)[k]->point = NULL;
	free((hash->array)[k]);
	(hash->array)[k] = NULL;
	return hash;
}

hashnode **init_array(int capacity)
{
	hashnode **array = NULL;
	array = (hashnode **) malloc(capacity* sizeof(hashnode*));
	for (int i = 0; i < capacity; i++)
	{
		(array)[i] = NULL;
	}

	return array;

}

Hash* create_HASH_TABLE(int size_Table)
{
	hashnode **array = NULL;
	Hash *our_hash = NULL;
	our_hash = (Hash*) malloc(sizeof(Hash));
	our_hash->capacity = size_Table;
	array = init_array(size_Table);
	our_hash->array = array;

	return our_hash;
}

void free_item(hashnode *node)
{
	node->point = NULL;
	node->value = 0;
	free(node);
}

void free_HASH(Hash *hash)
{
	for (int i = 0; i < hash->capacity; i++)
	{
		hashnode *tmp = hash->array[i];
		if (tmp != NULL)
		{
			free_item(tmp);
		}
	}

	free(hash->array);
	free(hash);

}

int find_element_in_hash(Hash *hash, int page)
{
	//ÃÂ
	int i = 0;

	for (i = 0; i < hash->capacity; i++)
	{
		if ((hash->array)[i] != NULL)
		{
			if (((hash->array)[i]->value) == page)
			{
				return i;
			}
		}
	}

	return -1;
}

int search_for_empty_place_in_hash(Hash *hash)
{
	int i = 0;
	hashnode **array = hash->array;
	for (i = 0; i < hash->capacity; i++)
	{
		if ((array)[i] == 0)
		{
			return i;
		}
	}

	return 0;
}

void add_value_to_hash(int page, node *list, Hash *hash, int i)
{
	(hash->array)[i] = create_node_h(page, list);

}

void hash_add(cash *cash, int page, node *list)
{
	int data = search_for_empty_place_in_hash(cash->table);
	add_value_to_hash(page, list, cash->table, data);
}

void hash_delete(cash *cash, int page)
{
	int data = find_element_in_hash(cash->table, page);
	delete_from_hash(cash->table, data);
}

//CASH

cash* init_cash(int size_List, int size_Table)
{
	cash *o_cash = NULL;
	o_cash = (cash*)(malloc(sizeof(cash)));
	o_cash->size_L = size_List;
	o_cash->size_T = size_Table;
	o_cash->list = List(o_cash->size_L);
	o_cash->table = create_HASH_TABLE(o_cash->size_T);
	return o_cash;

}

void free_cash(cash *CASH)
{
	list_free(&(CASH->list));
	free_HASH(CASH->table);
	CASH->size_L = 0;
	CASH->size_T = 0;
	free(CASH);
	CASH = NULL;
}

void push(cash *cash, int page)
{
	LinkedList *t = NULL;
	t = cash->list;
	assert(t->now_size <= t->size);

	if (t->now_size == t->size)
	{
		hash_delete(cash, cash->list->tail->val);
		popBack(t);
		pushFront(t, page);
		hash_add(cash, page, cash->list->head);
	}
	else
	{
		pushFront(t, page);
		hash_add(cash, page, cash->list->head);
	}
}

void exchange(cash *cash, int data)
{
	int value = 0;
	LinkedList *list = NULL;
	node *k = NULL;

	node *node = NULL;
	list = cash->list;

	node = (cash->table->array)[data]->point;
	value = (cash->table->array)[data]->value;
	if (node == NULL)
	{
		return;
	}

	if (node == list->head)
	{
		return;
	}

	if (node == list->tail)
	{
		k = node->prev;
		k->next = NULL;
		list->tail = k;
	}
	else
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}

	node->next = list->head;
	list->head->prev = node;
	list->head = node;
	node->prev = NULL;

}

int init_value_in_list(cash *Cash, int page)
{
	int data = 0;
	int result = 0;
	data = find_element_in_hash(Cash->table, page);
	if (data == -1)
	{
		push(Cash, page);
	}
	else
	{
		exchange(Cash, data);
		result = 1;
	}

	return result;

}

void print_list(LinkedList *t)
{
	//print_list_for 
	if (t)
	{
		node *tmp = NULL;
		tmp = t->head;
		while (tmp)
		{
			printf("%d", tmp->val);
			tmp = tmp->next;
		}
	}
}

int main()
{
	int result = 0;
	int data = 0;
	int i = 0;
	int a = 0;
	int b = 0;
	int *arr = NULL;
	cash *cash = NULL;
	scanf("%d", &a);
	scanf("%d", &b);
	cash = init_cash(a, b);
	arr = (int*) malloc(b* sizeof(int));
	for (i = 0; i < b; i++)
	{
		scanf("%d", &arr[i]);
	}

	result = print(cash, arr, b);

	printf("%d", result);
	free_cash(cash);
	free(arr);
	arr = NULL;

}

int print(cash *cash, int *array, int size)
{
	int i = 0;
	int result = 0;
	for (i = 0; i < size; i++)
	{
		result += init_value_in_list(cash, array[i]);
	}

	return result;
}
