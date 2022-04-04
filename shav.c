// $Id: shav.c,v 1.4 2002/08/22 20:42:38 Administrator Exp $

#include <string.h>
#include <stdio.h>
#include "a.h"
#include "mem.h"
#include "shav.h"
#include "spew.h"

char *shavtypes[] = { "???", "string", "hash", "vec", "obj" };

static void (*obj_dumper)( FILE *, void * );

shav *make_shav_obj( void *obj )
{
  shav *s;

  s = (shav*)malik( sizeof(shav) );
  s->type = OBJ;
  s->properties = 0;
  s->contents.obj.ptr = obj;

  return s;
}

shav *make_shav_string( char *string )
{
  shav *s;

  s = (shav*)malik( sizeof(shav) );
  s->type = STRING;
  s->properties = 0;
  s->contents.string.value = strdoop( string );

  return s;
}

shav *make_shav_vec( void )
{
  shav *s;

  s = (shav*)malik( sizeof(shav) );
  s->type = VEC;
  s->properties = 0;
  s->contents.vec.size = 0;
  s->contents.vec.values = 0;

  return s;
}

shav *make_shav_hash( void )
{
  shav *s;

  s = (shav*)malik( sizeof(shav) );
  s->type = HASH;
  s->properties = 0;
  s->contents.hash.size = 0;
  s->contents.hash.entries = 0;

  return s;
}

void free_shav( shav *s )
{
  A(shavok(s));

  if (s->type==STRING) {
    fri( s->contents.string.value );
  }

  fri( s ); 
}

int shavok( shav *s )
{
  if (s==0) {
    warn(( "Null shav\n" ));
    return 0;
  }

  if (!SHAV_TYPE_OK( s->type )) {
    warn(( "Bad type: 0x%x: %d\n", s, s->type ));
    return 0;
  }

  if (s->type == STRING && s->contents.string.value==0) {
    warn(( "Empty string: 0x%x\n", s ));
    return 0;
  }

  return 1;
}

void *get_obj( shav *s )
{
  A(shavok(s));
  MUSTOBJ(s);

  return s->contents.obj.ptr;
}

char *get_string( shav *s )
{
  A(shavok(s));
  MUSTSTRING(s);

  return s->contents.string.value;
}

static int get_hash_entry_index( shav *s, char *name )
{
  int i, size;

  A(shavok(s));
  MUSTHASH(s);

  size = s->contents.hash.size;

  if (size==0)
    return -1;

  for (i=0; i<size; ++i) {
    if (!strcmp( name, s->contents.hash.entries[i].name ))
      return i;
  }

  return -1;
}

int hash_contains( shav *s, char *name )
{
  A(shavok(s));
  MUSTHASH(s);

  return get_hash_entry_index( s, name )!=-1;
}

shav *get_hash_f( shav *s, char *name )
{
  int index;

  A(shavok(s));
  MUSTHASH(s);

  index = get_hash_entry_index( s, name );

  if (index==-1)
    return NULL;

  return s->contents.hash.entries[index].value;
}

shav *get_vec( shav *s, int index )
{
  int i, size;

  A(shavok(s));
  MUSTVEC(s);

  size = s->contents.vec.size;

  if (index >= size)
    return 0;

  return s->contents.vec.values[index];
}

void put_hash( shav *s, char *name, shav *value )
{
  int index;

  A(shavok(s));
  MUSTHASH(s);

  index = get_hash_entry_index( s, name );

  if (index != -1) {
    s->contents.hash.entries[index].value = value;
  } else {
    if (s->contents.hash.entries==0) {
      s->contents.hash.size = 1;
      s->contents.hash.entries = malik( sizeof(hashentry) );
      index = 0;
    } else {
      s->contents.hash.size++;
      s->contents.hash.entries = realik( s->contents.hash.entries, sizeof(hashentry)*s->contents.hash.size );
      index = s->contents.hash.size-1;
    }

    s->contents.hash.entries[index].name = strdoop( name );
    s->contents.hash.entries[index].value = value;
  }
}

void put_vec( shav *s, int index, shav *value )
{
  A(shavok(s));
  MUSTVEC(s);

  if (index >= s->contents.vec.size) {
    if (s->contents.vec.size==0) {
      s->contents.vec.size = index+1;
      s->contents.vec.values = malik( sizeof(shav*)*s->contents.vec.size );
    } else {
      s->contents.vec.size = index+1;
      s->contents.vec.values = realik( s->contents.vec.values, sizeof(shav*)*s->contents.vec.size );
    }
  }

  s->contents.vec.values[index] = value;
}

void add_vec_end( shav *s, shav *value )
{
  int i;

  A(shavok(s));
  MUSTVEC(s);

  for (i=s->contents.vec.size-1; i>=0; --i) {
    if (s->contents.vec.values[i]!=0) {
      break;
    }
  }

  if (i==-1)
    i = s->contents.vec.size;
  else
    i++;

  put_vec( s, i, value );
}

void insert_vec( shav *s, int position, shav *value )
{
  int i;

  // Move everything after the insertion point to the right
  for (i=VECSIZE(s)-1; i>=position; --i) {
    put_vec( s, i+1, get_vec( s, i ) );
  }

  // Store the new value
  put_vec( s, position, value );
}

/* start, end inclusive */
void vec_delete_range( shav *s, int start, int end )
{
  int i, ii;

  A(shavok(s));
  MUSTVEC(s);

  for (i=0, ii=0; i<VECSIZE(s); ++i) {
    if (ii<start || i>end) {
      put_vec( s, ii++, get_vec( s, i ) );
    }
  }

  s->contents.vec.size = ii;

  s->contents.vec.values = realik( s->contents.vec.values, sizeof(shav*)*ii );
}

static void print_spaces( FILE *stream, int n )
{
  while( n-- )
    fputc( ' ', stream );
}

#define DUMP_INDENT (2)

static void dump_stream_1( FILE *stream, shav *s, int level )
{
  if (s==0) {
    print_spaces( stream, level );
    fprintf( stream, "[NULL]\n" );
    return;
  }

  A(shavok(s));

  switch( SHAVTYPE(s) ) {
    case STRING:
      print_spaces( stream, level );
      fprintf( stream, "\"%s\"\n", get_string( s ) );
      break;

    case OBJ:
      print_spaces( stream, level );
      if (obj_dumper) {
        (*obj_dumper)( stream, get_obj( s ) );
        fprintf( stream, "\n" );
      } else {
        fprintf( stream, "[0x%x]\n", get_obj( s ) );
      }
      break;

    case HASH:
      print_spaces( stream, level );
      fprintf( stream, "{\n" );

      FORHASH(s,name,value,{
        print_spaces( stream, level+DUMP_INDENT );
        fprintf( stream, "\"%s\" =>\n", name );
        dump_stream_1( stream, value, level+DUMP_INDENT*2 );
      });

      print_spaces( stream, level );
      fprintf( stream, "}\n" );
      break;

    case VEC:
      print_spaces( stream, level );
      fprintf( stream, "[\n" );

      FORVEC(s,index,value,{
        print_spaces( stream, level+DUMP_INDENT );
        fprintf( stream, "%d =>\n", index );
        dump_stream_1( stream, value, level+DUMP_INDENT*2 );
      });

      print_spaces( stream, level );
      fprintf( stream, "]\n" );
      break;

    default:
      A(0);
      break;
  }
}

void shav_dump_stream( FILE *stream, shav *s )
{
  dump_stream_1( stream, s, 0 );
}

void shav_dump( shav *s )
{
  shav_dump_stream( stdout, s );
}

void shav_dump_file( char *filename, shav *s )
{
  FILE *stream = fopen( filename, "w" );
  A(stream);
  shav_dump_stream( stream, s );
  fclose( stream );
}

shav *get_properties( shav *s )
{
  shav *p;

  A(shavok(s));

  p = s->properties;
  A(p==0 || shavok(p));

  return p;
}

void set_properties( shav *s, shav *properties )
{
  A(shavok(s));
  A(properties==0 || shavok(properties));
  s->properties = properties;
}

void shav_install_obj_dumper( void (*dumper)( FILE *, void * ) )
{
  obj_dumper = dumper;
}

shav *shav_dup_shallow( shav *s )
{
  A(s);
  A(shavok(s));

  switch( s->type ) {
    case STRING:
      return make_shav_string( get_string( s ) );
      break;
    case OBJ:
      return make_shav_obj( get_obj( s ) );
    case HASH:
      {
        shav *ns = make_shav_hash();
        FORHASH(s,name,value,{
          put_hash( ns, name, value );
        });
        return ns;
      }
      break;
    case VEC:
      {
        shav *ns = make_shav_vec();
        FORVEC(s,i,value,{
          put_vec( ns, i, value );
        });
        return ns;
      }
      break;
    default:
      err(( "Bad shav type %d\n", s->type ));
      break;
  }
  return NULL;
}

void concat_vec( shav *dest, shav *src )
{
  A(dest);
  A(src);
  MUSTVEC(dest);
  MUSTVEC(src);

  FORVEC(src,i,val,{
    add_vec_end( dest, val );
  });
}

void shav_dump_fancy( char *message, shav *shav )
{
  printf( "-- %s ---------------------------------\n", message );
  shav_dump( shav );
  printf( "-- %s ---------------------------------\n", message );
}

/* start and end inclusive */
shav *vec_extract( shav *s, int start, int end )
{
  int i;
  shav *nu = make_shav_vec();

  if (start>end || end >= VECSIZE(s))
    err(( "Can't extract %d-%d from vec length %d\n", start, end, VECSIZE(s) ));

  for (i=start; i<=end; ++i) {
    add_vec_end( nu, get_vec( s, i ) );
  }

  return nu;
}
