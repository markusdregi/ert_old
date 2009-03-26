#ifndef __SCHED_KW_WCONHIST_H__
#define __SCHED_KW_WCONHIST_H__
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdbool.h>
#include <sched_macros.h>

typedef struct sched_kw_wconhist_struct sched_kw_wconhist_type;



sched_kw_wconhist_type * sched_kw_wconhist_fscanf_alloc( FILE *, bool *, const char *);
void                     sched_kw_wconhist_free(sched_kw_wconhist_type * );
void                     sched_kw_wconhist_fprintf(const sched_kw_wconhist_type * , FILE *);
void                     sched_kw_wconhist_fwrite(const sched_kw_wconhist_type *, FILE *);
sched_kw_wconhist_type * sched_kw_wconhist_fread_alloc( FILE *);

hash_type * sched_kw_wconhist_alloc_well_obs_hash(const sched_kw_wconhist_type *);

sched_kw_wconhist_type * sched_kw_wconhist_safe_cast( void * arg );

double 	 		 sched_kw_wconhist_get_orat( const sched_kw_wconhist_type * kw , const char * well_name);
void   	 		 sched_kw_wconhist_scale_orat( const sched_kw_wconhist_type * kw , const char * well_name, double factor);
void   	 		 sched_kw_wconhist_set_surface_flow( const sched_kw_wconhist_type * kw , const char * well_name , double orat);
bool   	 		 sched_kw_wconhist_has_well( const sched_kw_wconhist_type * kw , const char * well_name);


/*******************************************************************/



KW_FSCANF_ALLOC_HEADER(wconhist)
KW_FWRITE_HEADER(wconhist)
KW_FREAD_ALLOC_HEADER(wconhist)
KW_FREE_HEADER(wconhist)
KW_FPRINTF_HEADER(wconhist)

#ifdef __cplusplus
}
#endif
#endif
