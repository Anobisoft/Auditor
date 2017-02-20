//---------------------------------------------------------------------------

#ifndef Unit5H
#define Unit5H
//---------------------------------------------------------------------------

struct inspdata {
    int dbi, ind;
    AnsiString fio, pwd;
};

struct rlist {
  inspdata *data;
  rlist *next;
};

class Tinsp
{
  public:
  rlist *head;
  inspdata *data;
  void push();
  void free();
};



#endif
 