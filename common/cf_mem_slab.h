#ifndef __cf_mem_slab_h_
#define __cf_mem_slab_h_

#include <stdint.h>
#include <stddef.h>

struct mem_slab_s;
typedef struct mem_slab_s mem_slab_t;

struct mem_slab_s
{
	mem_slab_t*		next;
	uint32_t		magic;				/*����ħ����*/

	char			data[0];
};

typedef struct
{
	mem_slab_t*			head;

	void**				blocks;		/*�����ڴ������飬ÿһ��block���С��4M���зֳ�N��1K��С��wb_mem_slab_t����ζ��ÿ��������ϵͳ������4M��С������*/
	int					blocks_size;/*blocks�ĳ���*/
	int					block_num;  /*block������*/

	int					slab_size;	/*��󲻳���1M��Ĭ����1024*/

	/*״̬��Ϣ*/
	uint32_t			usable_size;
	uint32_t			alloc_count;
	uint32_t			free_count;
}mem_block_t;

#define PTR2BLOCK(ptr)	((mem_slab_t*)((char*)(ptr) - offsetof(mem_slab_t, data)))


mem_block_t*			slab_create(int slab_size);
void					slab_destroy(mem_block_t* mem);

void*					slab_alloc(mem_block_t* mem);
void					slab_free(mem_block_t* mem, void* ptr);
void					slab_print(mem_block_t* mem);

#endif


