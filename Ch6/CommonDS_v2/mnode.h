#ifndef _MNODE_H_
#define _MNODE_H_

#ifndef ElementType
#define ElementType void *
#endif

struct _MultiNode;

typedef _MultiNode MultiNode, *PMultiNode;
typedef PMultiNode MultiList;
typedef PMultiNode MultiListPosition;

#endif