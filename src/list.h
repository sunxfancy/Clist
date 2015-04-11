/* 
* @Author: sxf
* @Date:   2015-04-10 14:08:41
* @Last Modified by:   sxf
* @Last Modified time: 2015-04-11 19:48:47
*/


#ifndef LIST_H
#define LIST_H

/**
 * @brief 内存分配宏
 */
#ifndef MALLOC
#define MALLOC(type, obj) type* obj = (type*)malloc(sizeof(type))
#endif

/**
 * @brief 确定当前成员变量,在结构体中偏移量的宏
 */
#ifndef offsetof
#define offsetof(type, member) ((size_t) &((type*)0)->member)
#endif

/**
 * @brief 根据成员变量,找包含他的结构体指针
 */
#ifndef container_of
#define container_of(ptr, type, member) ({                  \
    const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
    (type *)( (char *)__mptr - offsetof(type,member) );})
#endif

/**
 * @brief 链表节点结构
 */
typedef struct _list_node
{
	struct _list_node 	*next;
	struct _list_node 	*prev;
} list_node;

/**
 * @brief 链表结构体
 */
typedef struct _list
{
	list_node* head;
} list;

/**
 * @brief 链表数据定义宏
 * @details 你可以这样定义这个链表的数据类:
 * 	 LIST_DEF(test_list)
 * 	   int a;
 * 	   float b;
 * 	   ...
 * 	 LIST_DEF_END(test_list)
 */
#define LIST_DEF(type_name) typedef struct _##type_name \
	{	list_node node;

#define LIST_DEF_END(type_name) } type_name;


/**
 * @brief 链表初始化宏
 */
#define LIST_INIT(addr) (addr)->next = (addr); (addr)->prev = (addr);

/**
 * @brief 用在链表数据类型的构造函数中的初始化宏
 */
#define LIST_CREATE_INIT(this_addr) LIST_INIT(&(this_addr->node))

/**
 * @brief 宏函数, 链表的遍历
 * @details 可以用如下的方式遍历链表 
 *  list_for_each(Int_List* , ele, list) {
 *		// do some work
 *		// ele->some_member
 *	} for_each_end
 * 
 * @param type 节点类型
 * @param ele  遍历的临时变量名称
 * @param list 要遍历的列表
 */
#define list_for_each(type, ele, list) \
	{ type ele; list_node* pos; list_node* head = list->head; char b; \
	for (pos = (head), ele = (type) pos, b = 1; \
		(pos != (head) || b); \
        pos = pos->next, ele = (type) pos, b = 0)

#define for_each_end }

/**
 * @brief 链表结构的构造函数
 * @return 链表结构体指针
 */
list* Create_List() {
	MALLOC(list, l);
	l->head = NULL;
	return l;
}


/**
 * @brief 链表的节点添加通用函数, 将一个节点添加到两个节点中间
 * 
 * @param prev_node 之前一个节点
 * @param next_node 之后一个节点
 * @param new_node 新要添加的节点
 */
inline void _list_add(list_node *prev_node, list_node *next_node, list_node *new_node) {
	next_node->prev = new_node;
	new_node->next = next_node;
	new_node->prev = prev_node;
	prev_node->next = new_node;
}


/**
 * @brief 在一个list节点后面插入
 * 
 * @param node list的节点
 * @param new_node 要插入的新节点
 */
inline void list_insert(list_node* node, list_node *new_node) {
	_list_add(node, node->next, new_node);
}



/**
 * @brief 判定是否为空链表
 * 
 * @param l 链表的结构体
 * @return 是空返回1 否则返回0
 */
inline int list_empty(const list *l) {
	return l->head == NULL;
}

/**
 * @brief 在list的结尾添加新节点
 * 
 * @param node list的头节点
 * @param new_node 要插入的新节点
 */
inline void list_add(list *l, list_node *new_node) {
	if (list_empty(l)) {
		l->head = new_node; 
		return;
	}
	_list_add(l->head->prev, l->head, new_node);
}

#endif // LIST_H
