/* The specific, correct include order is as follows:

// First, include node implementations
// Note that ElementType can only be defined once
// One can always define them before inclusion, but that defeats the purpose of header files
// Remember, Once the following files are included, the size of ElementType is unchangable
#include "node_impl.h" <-- use an implementation or implement something new
#include "tnode_impl.h" <-- same here

// Then, include the basic headers, if needed
// THEY ALL REQUIRE NODE_IMPL!
#include "list.h"
#include "stack.h"
#include "queue.h"

// Next, advanced headers, if needed
#include "tree.h" // REQUIRES TNODE_IMPL

// For Cling or unity build, include sources as well, in any order
#include "list.c"
#include "stack.c"
#include "queue.c"
#include "tree.c"

// Last, include application below
// BE SURE to include the correct node implementation!
#include "list_app_polynomial.h"
#include "list_app_polynomial.c"

*/

// Chapter DS here
#include "CommonDS_v2/adjacency_list.c"

#include "../Ch3/CommonDS_v2/list.c"
#include "../Ch3/CommonDS_v2/stack.c"
#include "../Ch3/CommonDS_v2/queue.c"