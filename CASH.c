#include <stdio.h>
#include <stdlib.h>

typedef struct node node;
typedef struct LinkedList LinkedList;
typedef struct hash_node hash_node;
typedef struct Hash Hash;
typedef struct cash cash;

struct node{  
    int val;
    node *next;
    node *prev;
}; 

struct LinkedList {
    int size;
    int now_size;
    node *head;
    node *tail;
};

struct hash_node {
  int value;
  node *point;
};

struct Hash {
  int capacity;
  hash_node **array;
};

struct *cash Cash_list {
  LinkedList *list;
  Hash *table;
  int size_L;
  int size_T;
  
}

//LIST
node* create_node()
{
	node *new_node = (node*) malloc(sizeof(node));
	return new_node;
}

LinkedList *List(int size) {

  LinkedList *list = NULL;
  node *tmp = NULL;
  list = (LinkedList*)malloc((sizeof (LinkedList))); 
  list->size = size;
  list->our_size = 0;
  list->head = NULL;
  list->tail = NULL;

  
  return list;



}
void list_free(LinkedList **list) {
    node *tmp = (*list)->head;
    node *next = NULL;
    while (tmp) {
        next = tmp->next;
        free(tmp);
        tmp = next;
    }
    free(*list);
    (*list) = NULL;
}


void pushFront(LinkedList *list, int data) {
	node *tmp = (node*) malloc(sizeof(node));
	if (tmp == NULL) {
		exit(1);
	}
	tmp->val = data;
	tmp->next = list->head;
	tmp->prev = NULL;
	if (list->head) {
		list->head->prev = tmp;
	}
	list->head = tmp;

	if (list->tail == NULL) {
		list->tail = tmp;
	}
	list->our_size++;
}
void* popBack(LinkedList *list) {
    node *next;
    void *tmp;
    if (list->tail == NULL) {
        exit(4);
    }
 
    next = list->tail;
    list->tail = list->tail->prev;
    if (list->tail) {
        list->tail->next = NULL;
    }
    if (next == list->head) {
        list->head = NULL;
    }
    tmp = next->val;
    free(next);
 
    list->size--;
    return tmp;
}
//ФУНКЦИЯ УДАЛЕНИЯ УЗЛА ИЗ СПИСКА



//HASH



hashnode *create_node(int value, node* point) {//создаем узел в хэш-таблице
  hashnode *tmp = NULL;
  tmp = (hashnode *)malloc(sizeof(hashnode));
  tmp->value = value;
  tmp->point = point;
  return tmp;
}
Hash* delete_from_hash(Hash *hash, int k){
  (hash->array)[k]->value = 0;
  (hash->array)[k]->point = NULL;
  free((hash->array)[k]);
  (hash->array)[k] = NULL;
  return hash;
}
  
hashnode **init_array(int capacity) { //проинициализировали массив ссылки заполнили 0
  int t = 0;
  hashnode **array = NULL;
  array = (hashnode **)malloc(capacity*sizeof(hashnode*));
  for (int i = 0; i < capacity; i++) {
    (array)[i] = NULL;
  }
  return array;
 
}
Hash *create_HASH_TABLE(int size_Table) {//создали хэш-таблицу
  hashnode **array = NULL;
  Hash *our_hash = NULL;
  our_hash =(Hash*)malloc(sizeof(Hash)); 
  our_hash->capacity = size_Table;
  array = init_array(size_Table);
  our_hash->array = array; //иницилиализируем массив
  our_hash->count = 0;
  return our_hash;
}

void free_item(hashnode *node) {
  node->point = NULL;
  node->value = 0;
  free(node);
}
  
 void free_HASH(Hash *hash) {//освободили хэш-таблицу
  for (int i = 0; i < hash->capacity; i++) {
    hashnode *tmp =  hash->array[i];
    if (tmp != NULL) {
      free_item(tmp);
    }
      
  }
  free(hash->array);
  free(hash);
 
}
//Поиск элемента в хэше

int find_element_in_hash(Hash *hash, int page) { //И
  int i = 0;
  int k = -1;

  for (i = 0; i < hash->capacity; i++) {
    if ((hash->array)[i] != NULL) {
      if (((hash->array)[i]->value) == page) {
        return  i;
      
    }
  }
  }
  return -1;  
}
int search_for_empty_place_in_hash(Hash *hash) {
  int i = 0;
  hashnode **array = hash->array;
   for ( i = 0; i < hash->capacity; i++) {

    
     if ((array)[i] == 0){
        return i;
      }
    
  }
      
}
void add_value_to_hash(int page, node *list, Hash *hash, int i) {
  (hash->array)[i] = create_node(page, list);
 //убрала hashnode *
}
void hash_add(Cash *cash, int page, node* list) {
  int data = search_for_empty_place_in_hash(cash->table);
  add_value_to_hash(page, list, cash->table data);
}
void hash_delete(Cash *cash, int page);
  int data = find_element_in_hash(cash->table, page);
  delete_from_hash(cash->table, data);
}

//CASH

cash* init_cash(int size_List, int size_Table) {

  cash *o_cash = NULL;
  o_cash = (cash *)(malloc(sizeof(cash)));
  cash->size_L = size_List;
  cash->size_T = size_Table;
  cash->list = init_list(cash->size_List);
  cash->table = init_list(cash->size_Table);
  return o_cash;


}


void free_cash(cash *CASH) {
  free_list(CASH->list);
  free_table(CASH->table);
  CASH->size_L = 0;
  CASH->size_T = 0;
  free(CASH);
  CASH = NULL;
}



void push(cash* cash, int page) {
  Linkedlist* t = NULL;
  t = cash->table;
  assert(t->now_size <= t->size);
  hash_delete(cash, page); //удаляем элемент в хэшу
  if (t->now_size == t->size) {
    hash_delete(cash, cash->list->val);
    popBack(t);
    pushFront(t, page);
    hash_add(cash, page, cash->list->head) ;
  else {
    pushFront(t, page);
    hash_add(cash, page, cash->list->head) ;
  }
}
    
void exchange(cash* cash, int page, int data) {
  Linkedlist *list = NULL;
  node *point = NULL;
  node *tmp = NULL;
  list = cash->list;
  node = (list->array)[data]->point;
  if (node = NULL) {
    return;
  }
  if ( node == list->head) {
    return;
  }
  if (node == list->tail) {
    tmp = node->prev;
    tmp->next = NULL;
    list->tail = tmp;
  }
  else {
    node->prev->next = node->next;
    node->next->prev = node->prev;
  
  
  
  }
  node->next = list->head;
  list->head->prev = node;
  list->head = node;
  node->prev = NULL;
  hash_delete(cash, cash->list->val);
  hash_add(cash, page, cash->list->head) ;
}
    


void init_value_in_list(Cash* Cash, int page) {
  int data = 0;
  int result = 0;
  data = find_element_in_hash(Cash->table, page); //ЕСТЬ ЛИ ЭЛЕМЕНТ В ХЭШЕ
  if (data == -1) {
    Push(cash, page);
  }
  else {
    exchange(cash, page);
    result += 1;
  }
  return result;

}
























