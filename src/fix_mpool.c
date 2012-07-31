/// @file   fix_mpool.c
/// @author Dmitry S. Melnikov, dmitryme@gmail.com
/// @date   Created on: 07/31/2012 04:31:55 PM

#include "fix_mpool.h"

#include <stdlib.h>

Page* alloc_page(uint32_t size)
{
   Page* p = malloc(sizeof(Page) - 1 + size);
   p->size = size;
   p->offset = 0;
   p->next = 0;
   return p;
}

FIXMPool* fix_mpool_init(uint32_t initSize)
{
   FIXMPool* pool = malloc(sizeof(FIXMPool));
   pool->pages = alloc_page(initSize);
   pool->curr_page = pool->pages;
   pool->page_size = initSize;
   return pool;
}

void fix_mpool_free(FIXMPool* pool)
{
   Page* page = pool->pages;
   while(page)
   {
      Page* next_page = page->next;
      free(page);
      page = next_page;
   }
   free(pool);
}

void* fix_mpool_alloc(FIXMPool* pool, uint32_t size)
{
   Page* curr_page = pool->curr_page;
   if (sizeof(uint32_t) + curr_page->size - curr_page->offset >= size)
   {
      uint32_t old_offset = curr_page->offset;
      *(uint32_t*)(&curr_page->data + curr_page->offset) = size;
      curr_page->offset += (size + sizeof(uint32_t));
      return &curr_page->data + old_offset + sizeof(uint32_t);
   }
   else
   {
      Page* new_page = alloc_page(size + sizeof(uint32_t) > pool->page_size ? size : pool->page_size);
      curr_page->next = new_page;
      pool->curr_page = new_page;
      return fix_mpool_alloc(pool, size);
   }
}

void* fix_mpool_realloc(FIXMPool* pool, void* ptr, uint32_t size)
{
   if (*(uint32_t*)(ptr - sizeof(uint32_t)) >= size)
   {
      return ptr;
   }
   else
   {
      return fix_mpool_alloc(pool, size);
   }
}+