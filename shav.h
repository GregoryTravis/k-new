// $Id: shav.h,v 1.4 2002/08/22 20:42:38 Administrator Exp $

#ifndef _shav_h_
#define _shav_h_

#include <stdio.h>

#include "a.h"

#define STRING 1
#define HASH 2
#define VEC 3
#define OBJ 4

extern char *shavtypes[];

#define SHAV_TYPE_OK(t) ((t)>=STRING && (t)<=OBJ)

#define SHAVTYPE(s) ((s)->type)
#define SHAVTYPESTRING(s) (SHAV_TYPE_OK(SHAVTYPE(s)) ? shavtypes[SHAVTYPE(s)] : "????")

#define ISSTRING(s) ((s)->type==STRING)
#define ISHASH(s) ((s)->type==HASH)
#define ISVEC(s) ((s)->type==VEC)
#define ISOBJ(s) ((s)->type==OBJ)

#define MUSTSTRING(s) RA(ISSTRING(s),("Not a string: 0x%x\n",(s)))
#define MUSTHASH(s) RA(ISHASH(s),("Not a hash: 0x%x type %d\n",(s), (s)->type))
#define MUSTVEC(s) RA(ISVEC(s),("Not a vec: 0x%x\n",(s)))
#define MUSTOBJ(s) RA(ISOBJ(s),("Not an obj: 0x%x\n",(s)))

typedef struct hashentry {
  char *name;
  struct shav *value;
} hashentry ;

typedef struct shav {
  int type;
  struct shav *properties;
  union {
    struct {
      char *value;
    } string ;

    struct {
      int size;
      hashentry *entries;
    } hash ;

    struct {
      int size;
      struct shav **values;
    } vec ;

    struct {
      void *ptr;
    } obj;
  } contents;
} shav ;

#define type(pshav) ((pshav)->type)

#define FORHASH(shv,_name,_value,block) \
  do {\
    shav *__source = (shv);\
    char *_name;\
    shav *_value;\
    int __inx, __size;\
    A(shavok(__source));\
    MUSTHASH(__source);\
    __size = (__source)->contents.hash.size;\
    for (__inx=0; __inx<__size; ++__inx) {\
      _name = (__source)->contents.hash.entries[__inx].name;\
      _value = (__source)->contents.hash.entries[__inx].value;\
      block\
    }\
  } while (0)

#define FORVEC(shv,index,value,block) \
  do {\
    shav *__source = (shv); \
    shav *value;\
    int index, __size;\
    A(shavok(__source));\
    MUSTVEC(__source);\
    __size = (__source)->contents.vec.size;\
    for (index=0; index<__size; ++index) {\
      value = (__source)->contents.vec.values[index];\
      block\
    }\
  } while(0)

shav *make_shav_obj( void *obj );
shav *make_shav_string( char *value );
shav *make_shav_hash( void );
shav *make_shav_vec( void );
void free_shav( shav *s );

void *get_obj( shav *s );
char *get_string( shav *s );

#define VECSIZE(s) (MUSTVEC(s),((s)->contents.vec.size))
#define HASHSIZE(s) (MUSTHASH(s),((s)->contents.hash.size))

#define get_hash(s,name) \
  (A(shavok((s))),MUSTHASH((s)),get_hash_f( (s), (name) ) )
shav *get_hash_f( shav *s, char *name );
void put_hash( shav *s, char *name, shav *value );

int hash_contains( shav *s, char *name );

shav *get_vec( shav *s, int index );
void put_vec( shav *s, int index, shav *value );
void add_vec_end( shav *s, shav *value );
void insert_vec( shav *s, int position, shav *value );
void vec_delete_range( shav *s, int start, int end );

int shavok( shav *s );

void shav_dump( shav *s );
void shav_dump_stream( FILE *stream, shav *s );
void shav_dump_file( char *filename, shav *s );

shav *get_properties( shav *s );
void set_properties( shav *s, shav *properties );

void shav_install_obj_dumper( void (*dumper)( FILE *, void * ) );

shav *shav_dup_shallow( shav *s );

void concat_vec( shav *dest, shav *src );

void shav_dump_fancy( char *message, shav *shav );

shav *vec_extract( shav *s, int start, int end );

#endif /* _shav_h_ */
