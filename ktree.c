// $Id: ktree.c,v 1.1 2002/08/22 20:42:37 Administrator Exp $

#include "kmisc.h"
#include "ktree.h"

void ktree_walk( ktree_callback callback, shav *node, void *data )
{
  int ret;
  char *type;

  A(callback);
  A(node);

  type = get_string( get_hash( node, "type" ) );
  A(type);

  ret = (*callback)( node, data );

  if (ret) {
    if (EQ( type, "block" )) {
      shav *statements = get_hash( node, "statements" );
      FORVEC(statements,i,statement,{
        ktree_walk( callback, statement, data );
      });
    } else if (EQ( type, "expression" )) {
      shav *expression = get_hash( node, "expression" );
      ktree_walk( callback, expression, data );
    } else if (EQ( type, "assignment" )) {
      shav *rvalue = get_hash( node, "rvalue" );
      ktree_walk( callback, rvalue, data );
    } else if (EQ( type, "lambda" )) {
      shav *body = get_hash( node, "body" );
      FORVEC(body,i,statement,{
        ktree_walk( callback, statement, data );
      });
    } else if (EQ( type, "funcall" )) {
      shav *function = get_hash( node, "function" );
      shav *args = get_hash( node, "args" );

      ktree_walk( callback, function, data );

      FORVEC(args,i,arg,{
        ktree_walk( callback, arg, data );
      });
    } else if (EQ( type, "return" )) {
      shav *args = get_hash( node, "args" );

      if (args) {
        FORVEC(args,i,arg,{
          ktree_walk( callback, arg, data );
        });
      }
    } else if (EQ( type, "variable" )) {
      /* nothing */
    } else if (EQ( type, "show" )) {
      /* nothing */
    } else if (EQ( type, "integer" )) {
      /* nothing */
    } else {
      err(( "Unknown node type %s\n", type ));
    }
  } else {
    /* Don't continue down tree */
  }
}

typedef struct ktree_walk_type_data {
  ktree_callback real_callback;
  char *type;
  void *real_data;
} ktree_walk_type_data ;

static int ktree_walk_type_callback( shav *node, void *data )
{
  char *type;

  ktree_walk_type_data *pd = (ktree_walk_type_data*)data;

  type = get_string( get_hash( node, "type" ) );
  if (EQ( type, pd->type )) {
    return (*pd->real_callback)( node, pd->real_data );
  } else {
    return 1;
  }
}

void ktree_walk_type( ktree_callback callback, char *type, shav *node, void *data )
{
  ktree_walk_type_data pd;

  pd.real_callback = callback;
  pd.type = type;
  pd.real_data = data;

  ktree_walk( &ktree_walk_type_callback, node, &pd );
}
