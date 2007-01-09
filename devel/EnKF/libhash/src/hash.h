#ifndef __HASH_H__
#define __HASH_H__

typedef struct hash_struct hash_type;

#include <hash_node.h>

#define HASH_GET_SCALAR(FUNC,TYPE)    	   TYPE   FUNC(const hash_type *, const char *)
#define HASH_GET_ARRAY_PTR(FUNC,TYPE) 	   TYPE * FUNC(const hash_type *, const char *)
#define HASH_INSERT_SCALAR(FUNC,TYPE)      void FUNC(hash_type * , const char * , TYPE )
#define HASH_INSERT_ARRAY(FUNC,TYPE)       void FUNC(hash_type * , const char * , TYPE * , int)



hash_type   * hash_alloc(int);
void          hash_free(hash_type *);
void          hash_insert_ref(hash_type * , const char * , const void *);
void          hash_insert_copy(hash_type *, const char * , const void *, copyc_type *, del_type *);
void          hash_insert_string_copy(hash_type *, const char *, const char *);
bool          hash_has_key(hash_type *, const char *);
void        * hash_get(const hash_type *, const char *);
char        * hash_get_string(const hash_type * , const char *);
void          hash_del(hash_type *, const char *);
void          hash_printf_keys(const hash_type *hash);
int           hash_get_size(const hash_type *);
void          hash_set_keylist(const hash_type * , char **);
char **       hash_alloc_keylist(const hash_type *);

HASH_GET_SCALAR(hash_get_int       , int);
HASH_GET_SCALAR(hash_get_double    , double);
HASH_INSERT_SCALAR(hash_insert_int    , int);
HASH_INSERT_SCALAR(hash_insert_double , double);
HASH_INSERT_ARRAY(hash_insert_int_array    , int);
HASH_INSERT_ARRAY(hash_insert_double_array , double);
HASH_GET_ARRAY_PTR(hash_get_double_ptr , double);
HASH_GET_ARRAY_PTR(hash_get_int_ptr    , int);


#undef HASH_GET_SCALAR
#undef HASH_INSERT_SCALAR
#undef HASH_INSERT_ARRAY
#undef HASH_GET_ARRAY_PTR

#endif
