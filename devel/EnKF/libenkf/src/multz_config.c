#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <enkf_util.h>
#include <util.h>
#include <ens_config.h>
#include <config.h>
#include <multz_config.h>
#include <logmode.h>
#include <util.h>
#include <trans_func.h>



/*
  WARNING: Returns the multz_config object in a completely unitialized state.
*/
static multz_config_type * __multz_config_alloc_empty(int size , const char * eclfile , const char * ensfile) {

  multz_config_type *multz_config = malloc(sizeof *multz_config);
  multz_config->mult_config = mult_config_alloc_empty(size);
  multz_config->ecl_kw_name = NULL;
  multz_config->var_type    = parameter;
  
  multz_config->eclfile = NULL;
  multz_config->ensfile = NULL;
  multz_config_set_eclfile(multz_config , eclfile);
  multz_config_set_ensfile(multz_config , ensfile);
  multz_config->i1   	= enkf_util_malloc(size * sizeof *multz_config->i1      , __func__);
  multz_config->i2   	= enkf_util_malloc(size * sizeof *multz_config->i2      , __func__);
  multz_config->j1   	= enkf_util_malloc(size * sizeof *multz_config->j1      , __func__);
  multz_config->j2   	= enkf_util_malloc(size * sizeof *multz_config->j2      , __func__);
  multz_config->k    	= enkf_util_malloc(size * sizeof *multz_config->k       , __func__);
  multz_config->area 	= enkf_util_malloc(size * sizeof *multz_config->area    , __func__);
 
  

  return multz_config;
}





/* void multz_config_fwrite(const multz_config_type * config , FILE * stream) { */
/*   /\* Bootstrap is based on the three first fields. *\/ */
/*   UTIL_FWRITE_SCALAR(config->data_size   , stream); */
/*   util_fwrite_string(config->ensfile     , stream); */
/*   util_fwrite_string(config->eclfile     , stream); */
  
/*   UTIL_FWRITE_SCALAR(config->serial_size , stream); */
/*   util_fwrite_string(config->ecl_kw_name , stream); */
/*   UTIL_FWRITE_SCALAR(config->var_type    , stream); */
/*   UTIL_FWRITE_VECTOR(config->i1          , config->data_size , stream); */
/*   UTIL_FWRITE_VECTOR(config->i2          , config->data_size , stream); */
/*   UTIL_FWRITE_VECTOR(config->j1          , config->data_size , stream); */
/*   UTIL_FWRITE_VECTOR(config->j2          , config->data_size , stream); */
/*   UTIL_FWRITE_VECTOR(config->k           , config->data_size , stream); */
/*   UTIL_FWRITE_VECTOR(config->area        , config->data_size , stream); */
/*   UTIL_FWRITE_VECTOR(config->mean        , config->data_size , stream); */
/*   UTIL_FWRITE_VECTOR(config->std         , config->data_size , stream); */
/*   UTIL_FWRITE_VECTOR(config->active      , config->data_size , stream); */
/*   { */
/*     int i; */
/*     for (i=0; i < config->data_size; i++) { */
/*       logmode_fwrite(config->logmode[i] , stream); */
/*       util_fwrite_string(config->output_transform_name[i] , stream); */
/*     } */
/*   } */
/* } */



/* multz_config_type * multz_config_fread_alloc(FILE * stream) { */
/*   int size; */
/*   multz_config_type * config; */
/*   UTIL_FREAD_SCALAR(size , stream); */
/*   { */
/*     char * ensfile , *eclfile; */
/*     ensfile = util_fread_alloc_string(stream); */
/*     eclfile = util_fread_alloc_string(stream); */
/*     config = __multz_config_alloc_empty(size , eclfile , ensfile); */
/*   } */
  
/*   UTIL_FREAD_SCALAR(config->serial_size , stream); */
/*   config->ecl_kw_name = util_fread_alloc_string(stream); */
/*   UTIL_FREAD_SCALAR(config->var_type    , stream); */
/*   UTIL_FREAD_VECTOR(config->i1          , config->data_size , stream); */
/*   UTIL_FREAD_VECTOR(config->i2          , config->data_size , stream); */
/*   UTIL_FREAD_VECTOR(config->j1          , config->data_size , stream); */
/*   UTIL_FREAD_VECTOR(config->j2          , config->data_size , stream); */
/*   UTIL_FREAD_VECTOR(config->k           , config->data_size , stream); */
/*   UTIL_FREAD_VECTOR(config->area        , config->data_size , stream); */
/*   UTIL_FREAD_VECTOR(config->mean        , config->data_size , stream); */
/*   UTIL_FREAD_VECTOR(config->std         , config->data_size , stream); */
/*   UTIL_FREAD_VECTOR(config->active      , config->data_size , stream); */
/*   { */
/*     int i; */
/*     for (i=0; i < config->data_size; i++) { */
/*       config->logmode[i] = logmode_fread_alloc(stream); */
/*       config->output_transform_name[i] = util_fread_alloc_string(stream); */
/*     } */
/*   } */
/*   multz_config_set_output_transform(config); */
/*   return config; */
/* } */




multz_config_type * multz_config_fscanf_alloc(const char * filename , int nx , int ny , int nz , const char * eclfile , const char * ensfile) {
  multz_config_type * config;
  FILE * stream = util_fopen(filename , "r");
  int size , line_nr;

  size = util_count_file_lines(stream);
  fseek(stream , 0L , SEEK_SET);
  config  = __multz_config_alloc_empty(size , eclfile , ensfile);
  line_nr = 0;
  do {
    int i1 = 1;
    int i2 = nx;
    int j1 = 1;
    int j2 = ny;
    int k;
    
    if (fscanf(stream , "%d" , &k) != 1) {
      fprintf(stderr,"%s: something wrong when reading: %s - aborting \n",__func__ , filename);
      abort();
    }
    mult_config_fscanf_line(config->mult_config , line_nr , stream);
    util_fscanf_int(stream, &i1);  
    util_fscanf_int(stream, &i2);
    util_fscanf_int(stream, &j1);
    util_fscanf_int(stream, &j2);
    
    config->k[line_nr]     = k;
    config->i1[line_nr]    = util_int_max(i1 , 1);
    config->i2[line_nr]    = util_int_min(i2 , nx);
    config->j1[line_nr]    = util_int_max(j1 , 1);
    config->j2[line_nr]    = util_int_min(j2 , ny);
    config->area[line_nr]  = (config->i2[line_nr]- config->i1[line_nr] + 1) * (config->j2[line_nr]- config->j1[line_nr] + 1);
    line_nr++;
  } while ( line_nr < size );

  mult_config_finalize_init(config->mult_config);
  fclose(stream);
  return config;
}




void multz_config_ecl_write(const multz_config_type * config , const double *data , FILE *stream) {
  int ik;
  for (ik = 0; ik < multz_config_get_data_size(config); ik++) {

    fprintf(stream,"BOX\n   %5d %5d %5d %5d %5d %5d / \nMULTZ\n%d*%g /\nENDBOX\n\n\n" , 
	    config->i1[ik]   , config->i2[ik] , 
	    config->j1[ik]   , config->j2[ik] , 
	    config->k[ik]    , config->k[ik]  , 
	    config->area[ik] , data[ik]);
  }
  
}



void multz_config_free(multz_config_type * config) {
  free(config->j1);
  free(config->j2);
  free(config->i1);
  free(config->i2);
  free(config->k);
  free(config->area);
  mult_config_free(config->mult_config);
  free(config);
}





int multz_config_get_data_size(const multz_config_type * multz_config) {
  return mult_config_get_data_size(multz_config->mult_config);
}

void multz_config_set_serial_offset(multz_config_type * multz_config, int serial_offset ) {
  mult_config_set_serial_offset(multz_config->mult_config , serial_offset);
}


/*****************************************************************/

CONFIG_GET_ENSFILE(multz);
CONFIG_GET_ECLFILE(multz);
CONFIG_SET_ECLFILE(multz);
CONFIG_SET_ENSFILE(multz);
CONFIG_SET_ECLFILE_VOID(multz);
CONFIG_SET_ENSFILE_VOID(multz);
VOID_FUNC(multz_config_free , multz_config_type);
VOID_SET_SERIAL_OFFSET(multz);

							 

