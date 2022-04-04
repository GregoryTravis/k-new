// $Id: ktree.h,v 1.1 2002/08/22 20:42:37 Administrator Exp $

#ifndef _ktree_h_
#define _ktree_h_

#include "shav.h"

/* returns 1 for good, 0 for bad */
typedef int (*ktree_callback)( shav *node, void *data );

void ktree_walk( ktree_callback callback, shav *node, void *data );
void ktree_walk_type( ktree_callback callback, char *type, shav *node, void *data );

#endif /* _ktree_h_ */
