//---------------------------------------------------------------------------


#pragma hdrstop

#include "Unit1.h"
#include "Unit5.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

void Tinsp::push()
{
   rlist *tmp = new rlist;
   tmp->next = head;
   tmp->data = data;
   head = tmp;
}

void Tinsp::free()
{
   rlist *tmp;
   while (head != NULL) {
     tmp = head;
     head = head->next;
     delete tmp->data;
     delete tmp;
   }
}


