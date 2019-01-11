#ifndef __c1_RC_DOB_mdl_h__
#define __c1_RC_DOB_mdl_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc1_RC_DOB_mdlInstanceStruct
#define typedef_SFc1_RC_DOB_mdlInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c1_sfEvent;
  boolean_T c1_isStable;
  boolean_T c1_doneDoubleBufferReInit;
  uint8_T c1_is_active_c1_RC_DOB_mdl;
  real_T c1_N;
  boolean_T c1_N_not_empty;
  real_T c1_x_data[220];
  int32_T c1_x_sizes;
  boolean_T c1_x_not_empty;
  real_T c1_y;
  boolean_T c1_y_not_empty;
  real_T c1_alpha;
  boolean_T c1_alpha_not_empty;
  real_T c1_iter;
  boolean_T c1_iter_not_empty;
  real_T c1_SW_TUNE;
  boolean_T c1_SW_TUNE_not_empty;
  real_T c1_flag_alpha_stage1;
  boolean_T c1_flag_alpha_stage1_not_empty;
  real_T *c1_uk;
  real_T *c1_comp_sig;
  real_T *c1_SW;
  real_T *c1_Q_shape_coef;
  real_T *c1_alpha_init;
  real_T *c1_alpha_end;
  real_T *c1_alpha_rate;
  real_T *c1_Nq;
  real_T *c1_m;
  real_T *c1_n_lp;
  real_T *c1_alpha_middle;
  real_T *c1_alpha_convg_judge;
  real_T *c1_alpha_rate2;
} SFc1_RC_DOB_mdlInstanceStruct;

#endif                                 /*typedef_SFc1_RC_DOB_mdlInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c1_RC_DOB_mdl_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c1_RC_DOB_mdl_get_check_sum(mxArray *plhs[]);
extern void c1_RC_DOB_mdl_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
