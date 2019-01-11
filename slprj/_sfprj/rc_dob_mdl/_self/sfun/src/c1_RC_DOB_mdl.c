/* Include files */

#include <stddef.h>
#include "blas.h"
#include "RC_DOB_mdl_sfun.h"
#include "c1_RC_DOB_mdl.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "RC_DOB_mdl_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c1_debug_family_names[24] = { "xk", "delta_alpha", "nargin",
  "nargout", "uk", "SW", "alpha_init", "alpha_end", "alpha_rate", "Nq", "m",
  "n_lp", "alpha_middle", "alpha_convg_judge", "alpha_rate2", "comp_sig",
  "Q_shape_coef", "N", "x", "y", "alpha", "iter", "SW_TUNE", "flag_alpha_stage1"
};

/* Function Declarations */
static void initialize_c1_RC_DOB_mdl(SFc1_RC_DOB_mdlInstanceStruct
  *chartInstance);
static void initialize_params_c1_RC_DOB_mdl(SFc1_RC_DOB_mdlInstanceStruct
  *chartInstance);
static void enable_c1_RC_DOB_mdl(SFc1_RC_DOB_mdlInstanceStruct *chartInstance);
static void disable_c1_RC_DOB_mdl(SFc1_RC_DOB_mdlInstanceStruct *chartInstance);
static void c1_update_debugger_state_c1_RC_DOB_mdl(SFc1_RC_DOB_mdlInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c1_RC_DOB_mdl(SFc1_RC_DOB_mdlInstanceStruct *
  chartInstance);
static void set_sim_state_c1_RC_DOB_mdl(SFc1_RC_DOB_mdlInstanceStruct
  *chartInstance, const mxArray *c1_st);
static void finalize_c1_RC_DOB_mdl(SFc1_RC_DOB_mdlInstanceStruct *chartInstance);
static void sf_gateway_c1_RC_DOB_mdl(SFc1_RC_DOB_mdlInstanceStruct
  *chartInstance);
static void mdl_start_c1_RC_DOB_mdl(SFc1_RC_DOB_mdlInstanceStruct *chartInstance);
static void c1_chartstep_c1_RC_DOB_mdl(SFc1_RC_DOB_mdlInstanceStruct
  *chartInstance);
static void initSimStructsc1_RC_DOB_mdl(SFc1_RC_DOB_mdlInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber, uint32_T c1_instanceNumber);
static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData);
static real_T c1_emlrt_marshallIn(SFc1_RC_DOB_mdlInstanceStruct *chartInstance,
  const mxArray *c1_b_flag_alpha_stage1, const char_T *c1_identifier);
static real_T c1_b_emlrt_marshallIn(SFc1_RC_DOB_mdlInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static real_T c1_c_emlrt_marshallIn(SFc1_RC_DOB_mdlInstanceStruct *chartInstance,
  const mxArray *c1_b_SW_TUNE, const char_T *c1_identifier);
static real_T c1_d_emlrt_marshallIn(SFc1_RC_DOB_mdlInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static real_T c1_e_emlrt_marshallIn(SFc1_RC_DOB_mdlInstanceStruct *chartInstance,
  const mxArray *c1_b_iter, const char_T *c1_identifier);
static real_T c1_f_emlrt_marshallIn(SFc1_RC_DOB_mdlInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static real_T c1_g_emlrt_marshallIn(SFc1_RC_DOB_mdlInstanceStruct *chartInstance,
  const mxArray *c1_b_alpha, const char_T *c1_identifier);
static real_T c1_h_emlrt_marshallIn(SFc1_RC_DOB_mdlInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_e_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static real_T c1_i_emlrt_marshallIn(SFc1_RC_DOB_mdlInstanceStruct *chartInstance,
  const mxArray *c1_b_y, const char_T *c1_identifier);
static real_T c1_j_emlrt_marshallIn(SFc1_RC_DOB_mdlInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_f_sf_marshallOut(void *chartInstanceVoid, real_T
  c1_inData_data[], int32_T *c1_inData_sizes);
static void c1_k_emlrt_marshallIn(SFc1_RC_DOB_mdlInstanceStruct *chartInstance,
  const mxArray *c1_x, const char_T *c1_identifier, real_T c1_y_data[], int32_T *
  c1_y_sizes);
static void c1_l_emlrt_marshallIn(SFc1_RC_DOB_mdlInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y_data[],
  int32_T *c1_y_sizes);
static void c1_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, real_T c1_outData_data[], int32_T
  *c1_outData_sizes);
static const mxArray *c1_g_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static real_T c1_m_emlrt_marshallIn(SFc1_RC_DOB_mdlInstanceStruct *chartInstance,
  const mxArray *c1_b_N, const char_T *c1_identifier);
static real_T c1_n_emlrt_marshallIn(SFc1_RC_DOB_mdlInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_h_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static real_T c1_o_emlrt_marshallIn(SFc1_RC_DOB_mdlInstanceStruct *chartInstance,
  const mxArray *c1_b_Q_shape_coef, const char_T *c1_identifier);
static real_T c1_p_emlrt_marshallIn(SFc1_RC_DOB_mdlInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static void c1_info_helper(const mxArray **c1_info);
static const mxArray *c1_emlrt_marshallOut(const char * c1_u);
static const mxArray *c1_b_emlrt_marshallOut(const uint32_T c1_u);
static void c1_eml_scalar_eg(SFc1_RC_DOB_mdlInstanceStruct *chartInstance);
static const mxArray *c1_i_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static int32_T c1_q_emlrt_marshallIn(SFc1_RC_DOB_mdlInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static uint8_T c1_r_emlrt_marshallIn(SFc1_RC_DOB_mdlInstanceStruct
  *chartInstance, const mxArray *c1_b_is_active_c1_RC_DOB_mdl, const char_T
  *c1_identifier);
static uint8_T c1_s_emlrt_marshallIn(SFc1_RC_DOB_mdlInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void init_dsm_address_info(SFc1_RC_DOB_mdlInstanceStruct *chartInstance);
static void init_simulink_io_address(SFc1_RC_DOB_mdlInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c1_RC_DOB_mdl(SFc1_RC_DOB_mdlInstanceStruct
  *chartInstance)
{
  chartInstance->c1_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c1_N_not_empty = false;
  chartInstance->c1_x_not_empty = false;
  chartInstance->c1_y_not_empty = false;
  chartInstance->c1_alpha_not_empty = false;
  chartInstance->c1_iter_not_empty = false;
  chartInstance->c1_SW_TUNE_not_empty = false;
  chartInstance->c1_flag_alpha_stage1_not_empty = false;
  chartInstance->c1_is_active_c1_RC_DOB_mdl = 0U;
}

static void initialize_params_c1_RC_DOB_mdl(SFc1_RC_DOB_mdlInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void enable_c1_RC_DOB_mdl(SFc1_RC_DOB_mdlInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c1_RC_DOB_mdl(SFc1_RC_DOB_mdlInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c1_update_debugger_state_c1_RC_DOB_mdl(SFc1_RC_DOB_mdlInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c1_RC_DOB_mdl(SFc1_RC_DOB_mdlInstanceStruct *
  chartInstance)
{
  const mxArray *c1_st;
  const mxArray *c1_b_y = NULL;
  real_T c1_hoistedGlobal;
  real_T c1_u;
  const mxArray *c1_c_y = NULL;
  real_T c1_b_hoistedGlobal;
  real_T c1_b_u;
  const mxArray *c1_d_y = NULL;
  real_T c1_c_hoistedGlobal;
  real_T c1_c_u;
  const mxArray *c1_e_y = NULL;
  real_T c1_d_hoistedGlobal;
  real_T c1_d_u;
  const mxArray *c1_f_y = NULL;
  real_T c1_e_hoistedGlobal;
  real_T c1_e_u;
  const mxArray *c1_g_y = NULL;
  real_T c1_f_hoistedGlobal;
  real_T c1_f_u;
  const mxArray *c1_h_y = NULL;
  real_T c1_g_hoistedGlobal;
  real_T c1_g_u;
  const mxArray *c1_i_y = NULL;
  int32_T c1_u_sizes;
  int32_T c1_i0;
  real_T c1_u_data[220];
  const mxArray *c1_j_y = NULL;
  real_T c1_h_hoistedGlobal;
  real_T c1_h_u;
  const mxArray *c1_k_y = NULL;
  uint8_T c1_i_hoistedGlobal;
  uint8_T c1_i_u;
  const mxArray *c1_l_y = NULL;
  c1_st = NULL;
  c1_st = NULL;
  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_createcellmatrix(10, 1), false);
  c1_hoistedGlobal = *chartInstance->c1_Q_shape_coef;
  c1_u = c1_hoistedGlobal;
  c1_c_y = NULL;
  sf_mex_assign(&c1_c_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c1_b_y, 0, c1_c_y);
  c1_b_hoistedGlobal = *chartInstance->c1_comp_sig;
  c1_b_u = c1_b_hoistedGlobal;
  c1_d_y = NULL;
  sf_mex_assign(&c1_d_y, sf_mex_create("y", &c1_b_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c1_b_y, 1, c1_d_y);
  c1_c_hoistedGlobal = chartInstance->c1_N;
  c1_c_u = c1_c_hoistedGlobal;
  c1_e_y = NULL;
  if (!chartInstance->c1_N_not_empty) {
    sf_mex_assign(&c1_e_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c1_e_y, sf_mex_create("y", &c1_c_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_setcell(c1_b_y, 2, c1_e_y);
  c1_d_hoistedGlobal = chartInstance->c1_SW_TUNE;
  c1_d_u = c1_d_hoistedGlobal;
  c1_f_y = NULL;
  if (!chartInstance->c1_SW_TUNE_not_empty) {
    sf_mex_assign(&c1_f_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c1_f_y, sf_mex_create("y", &c1_d_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_setcell(c1_b_y, 3, c1_f_y);
  c1_e_hoistedGlobal = chartInstance->c1_alpha;
  c1_e_u = c1_e_hoistedGlobal;
  c1_g_y = NULL;
  if (!chartInstance->c1_alpha_not_empty) {
    sf_mex_assign(&c1_g_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c1_g_y, sf_mex_create("y", &c1_e_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_setcell(c1_b_y, 4, c1_g_y);
  c1_f_hoistedGlobal = chartInstance->c1_flag_alpha_stage1;
  c1_f_u = c1_f_hoistedGlobal;
  c1_h_y = NULL;
  if (!chartInstance->c1_flag_alpha_stage1_not_empty) {
    sf_mex_assign(&c1_h_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c1_h_y, sf_mex_create("y", &c1_f_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_setcell(c1_b_y, 5, c1_h_y);
  c1_g_hoistedGlobal = chartInstance->c1_iter;
  c1_g_u = c1_g_hoistedGlobal;
  c1_i_y = NULL;
  if (!chartInstance->c1_iter_not_empty) {
    sf_mex_assign(&c1_i_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c1_i_y, sf_mex_create("y", &c1_g_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_setcell(c1_b_y, 6, c1_i_y);
  c1_u_sizes = 220;
  for (c1_i0 = 0; c1_i0 < 220; c1_i0++) {
    c1_u_data[c1_i0] = chartInstance->c1_x_data[c1_i0];
  }

  c1_j_y = NULL;
  if (!chartInstance->c1_x_not_empty) {
    sf_mex_assign(&c1_j_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c1_j_y, sf_mex_create("y", c1_u_data, 0, 0U, 1U, 0U, 1,
      c1_u_sizes), false);
  }

  sf_mex_setcell(c1_b_y, 7, c1_j_y);
  c1_h_hoistedGlobal = chartInstance->c1_y;
  c1_h_u = c1_h_hoistedGlobal;
  c1_k_y = NULL;
  if (!chartInstance->c1_y_not_empty) {
    sf_mex_assign(&c1_k_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c1_k_y, sf_mex_create("y", &c1_h_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_setcell(c1_b_y, 8, c1_k_y);
  c1_i_hoistedGlobal = chartInstance->c1_is_active_c1_RC_DOB_mdl;
  c1_i_u = c1_i_hoistedGlobal;
  c1_l_y = NULL;
  sf_mex_assign(&c1_l_y, sf_mex_create("y", &c1_i_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c1_b_y, 9, c1_l_y);
  sf_mex_assign(&c1_st, c1_b_y, false);
  return c1_st;
}

static void set_sim_state_c1_RC_DOB_mdl(SFc1_RC_DOB_mdlInstanceStruct
  *chartInstance, const mxArray *c1_st)
{
  const mxArray *c1_u;
  int32_T c1_tmp_sizes;
  real_T c1_tmp_data[220];
  int32_T c1_i1;
  chartInstance->c1_doneDoubleBufferReInit = true;
  c1_u = sf_mex_dup(c1_st);
  *chartInstance->c1_Q_shape_coef = c1_o_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 0)), "Q_shape_coef");
  *chartInstance->c1_comp_sig = c1_o_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 1)), "comp_sig");
  chartInstance->c1_N = c1_m_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 2)), "N");
  chartInstance->c1_SW_TUNE = c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 3)), "SW_TUNE");
  chartInstance->c1_alpha = c1_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 4)), "alpha");
  chartInstance->c1_flag_alpha_stage1 = c1_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 5)), "flag_alpha_stage1");
  chartInstance->c1_iter = c1_e_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 6)), "iter");
  c1_k_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 7)), "x",
                        c1_tmp_data, &c1_tmp_sizes);
  chartInstance->c1_x_sizes = 220;
  for (c1_i1 = 0; c1_i1 < 220; c1_i1++) {
    chartInstance->c1_x_data[c1_i1] = c1_tmp_data[c1_i1];
  }

  chartInstance->c1_y = c1_i_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 8)), "y");
  chartInstance->c1_is_active_c1_RC_DOB_mdl = c1_r_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 9)),
     "is_active_c1_RC_DOB_mdl");
  sf_mex_destroy(&c1_u);
  c1_update_debugger_state_c1_RC_DOB_mdl(chartInstance);
  sf_mex_destroy(&c1_st);
}

static void finalize_c1_RC_DOB_mdl(SFc1_RC_DOB_mdlInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c1_RC_DOB_mdl(SFc1_RC_DOB_mdlInstanceStruct
  *chartInstance)
{
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_uk, 0U);
  chartInstance->c1_sfEvent = CALL_EVENT;
  c1_chartstep_c1_RC_DOB_mdl(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_RC_DOB_mdlMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_comp_sig, 1U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_SW, 2U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Q_shape_coef, 3U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_alpha_init, 4U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_alpha_end, 5U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_alpha_rate, 6U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Nq, 7U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_m, 8U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_n_lp, 9U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_alpha_middle, 10U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_alpha_convg_judge, 11U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_alpha_rate2, 12U);
}

static void mdl_start_c1_RC_DOB_mdl(SFc1_RC_DOB_mdlInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c1_chartstep_c1_RC_DOB_mdl(SFc1_RC_DOB_mdlInstanceStruct
  *chartInstance)
{
  real_T c1_hoistedGlobal;
  real_T c1_b_hoistedGlobal;
  real_T c1_c_hoistedGlobal;
  real_T c1_d_hoistedGlobal;
  real_T c1_e_hoistedGlobal;
  real_T c1_f_hoistedGlobal;
  real_T c1_g_hoistedGlobal;
  real_T c1_h_hoistedGlobal;
  real_T c1_i_hoistedGlobal;
  real_T c1_j_hoistedGlobal;
  real_T c1_k_hoistedGlobal;
  real_T c1_b_uk;
  real_T c1_b_SW;
  real_T c1_b_alpha_init;
  real_T c1_b_alpha_end;
  real_T c1_b_alpha_rate;
  real_T c1_b_Nq;
  real_T c1_b_m;
  real_T c1_b_n_lp;
  real_T c1_b_alpha_middle;
  real_T c1_b_alpha_convg_judge;
  real_T c1_b_alpha_rate2;
  uint32_T c1_debug_family_var_map[24];
  real_T c1_xk;
  real_T c1_delta_alpha;
  real_T c1_nargin = 11.0;
  real_T c1_nargout = 2.0;
  real_T c1_b_comp_sig;
  real_T c1_b_Q_shape_coef;
  int32_T c1_i2;
  real_T c1_l_hoistedGlobal;
  real_T c1_a;
  real_T c1_b_a;
  real_T c1_c_a;
  real_T c1_ak;
  real_T c1_d_a;
  real_T c1_ar;
  real_T c1_c;
  real_T c1_A;
  real_T c1_B;
  real_T c1_x;
  real_T c1_b_y;
  real_T c1_b_x;
  real_T c1_c_y;
  real_T c1_c_x;
  real_T c1_d_y;
  real_T c1_d0;
  int32_T c1_tmp_sizes;
  int32_T c1_i3;
  int32_T c1_tmp_data[219];
  int32_T c1_b_tmp_sizes[2];
  int32_T c1_i4;
  real_T c1_b_tmp_data[219];
  int32_T c1_i5;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  c1_hoistedGlobal = *chartInstance->c1_uk;
  c1_b_hoistedGlobal = *chartInstance->c1_SW;
  c1_c_hoistedGlobal = *chartInstance->c1_alpha_init;
  c1_d_hoistedGlobal = *chartInstance->c1_alpha_end;
  c1_e_hoistedGlobal = *chartInstance->c1_alpha_rate;
  c1_f_hoistedGlobal = *chartInstance->c1_Nq;
  c1_g_hoistedGlobal = *chartInstance->c1_m;
  c1_h_hoistedGlobal = *chartInstance->c1_n_lp;
  c1_i_hoistedGlobal = *chartInstance->c1_alpha_middle;
  c1_j_hoistedGlobal = *chartInstance->c1_alpha_convg_judge;
  c1_k_hoistedGlobal = *chartInstance->c1_alpha_rate2;
  c1_b_uk = c1_hoistedGlobal;
  c1_b_SW = c1_b_hoistedGlobal;
  c1_b_alpha_init = c1_c_hoistedGlobal;
  c1_b_alpha_end = c1_d_hoistedGlobal;
  c1_b_alpha_rate = c1_e_hoistedGlobal;
  c1_b_Nq = c1_f_hoistedGlobal;
  c1_b_m = c1_g_hoistedGlobal;
  c1_b_n_lp = c1_h_hoistedGlobal;
  c1_b_alpha_middle = c1_i_hoistedGlobal;
  c1_b_alpha_convg_judge = c1_j_hoistedGlobal;
  c1_b_alpha_rate2 = c1_k_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 24U, 24U, c1_debug_family_names,
    c1_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_xk, 0U, c1_h_sf_marshallOut,
    c1_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_delta_alpha, 1U, c1_h_sf_marshallOut,
    c1_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargin, 2U, c1_h_sf_marshallOut,
    c1_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargout, 3U, c1_h_sf_marshallOut,
    c1_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_b_uk, 4U, c1_h_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_b_SW, 5U, c1_h_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_b_alpha_init, 6U, c1_h_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_b_alpha_end, 7U, c1_h_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_b_alpha_rate, 8U, c1_h_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_b_Nq, 9U, c1_h_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_b_m, 10U, c1_h_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_b_n_lp, 11U, c1_h_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_b_alpha_middle, 12U, c1_h_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_b_alpha_convg_judge, 13U, c1_h_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_b_alpha_rate2, 14U, c1_h_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_b_comp_sig, 15U, c1_h_sf_marshallOut,
    c1_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_b_Q_shape_coef, 16U,
    c1_h_sf_marshallOut, c1_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c1_N, 17U,
    c1_g_sf_marshallOut, c1_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_DYN_IMPORTABLE(chartInstance->c1_x_data, (const
    int32_T *)&chartInstance->c1_x_sizes, NULL, 1, 18, (void *)
    c1_f_sf_marshallOut, (void *)c1_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c1_y, 19U,
    c1_e_sf_marshallOut, c1_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c1_alpha, 20U,
    c1_d_sf_marshallOut, c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c1_iter, 21U,
    c1_c_sf_marshallOut, c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c1_SW_TUNE, 22U,
    c1_b_sf_marshallOut, c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c1_flag_alpha_stage1, 23U,
    c1_sf_marshallOut, c1_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 10);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 24);
  if (CV_EML_IF(0, 1, 0, !chartInstance->c1_N_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 25);
    CV_EML_IF(0, 1, 1, true);
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 26);
    chartInstance->c1_N = 220.0;
    chartInstance->c1_N_not_empty = true;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 31);
    chartInstance->c1_SW_TUNE = 0.0;
    chartInstance->c1_SW_TUNE_not_empty = true;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 37);
    chartInstance->c1_x_sizes = 220;
    for (c1_i2 = 0; c1_i2 < 220; c1_i2++) {
      chartInstance->c1_x_data[c1_i2] = 0.0;
    }

    chartInstance->c1_x_not_empty = true;
    chartInstance->c1_x_not_empty = true;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 38);
    chartInstance->c1_y = 0.0;
    chartInstance->c1_y_not_empty = true;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 40);
    chartInstance->c1_alpha = c1_b_alpha_init;
    chartInstance->c1_alpha_not_empty = true;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 41);
    c1_b_comp_sig = 0.0;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 42);
    chartInstance->c1_iter = 0.0;
    chartInstance->c1_iter_not_empty = true;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 43);
    chartInstance->c1_flag_alpha_stage1 = 1.0;
    chartInstance->c1_flag_alpha_stage1_not_empty = true;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 45);
  if (CV_EML_IF(0, 1, 2, CV_RELATIONAL_EVAL(4U, 0U, 0, c1_b_SW, 0.0, -1, 0U,
        c1_b_SW == 0.0))) {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 48);
    CV_EML_IF(0, 1, 3, true);
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 54);
    c1_b_comp_sig = 0.0;
  } else {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 57);
    CV_EML_IF(0, 1, 4, true);
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 58);
    c1_l_hoistedGlobal = chartInstance->c1_alpha;
    c1_a = c1_l_hoistedGlobal;
    c1_b_a = c1_a;
    c1_c_a = c1_b_a;
    c1_eml_scalar_eg(chartInstance);
    c1_ak = c1_c_a;
    c1_d_a = c1_ak;
    c1_eml_scalar_eg(chartInstance);
    c1_ar = c1_d_a;
    c1_c = muDoubleScalarPower(c1_ar, 220.0);
    c1_xk = c1_b_uk + c1_c * (chartInstance->c1_x_data[219] - c1_b_uk);
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 62);
    chartInstance->c1_y = chartInstance->c1_x_data[_SFD_EML_ARRAY_BOUNDS_CHECK(
      "x", (int32_T)_SFD_INTEGER_CHECK("N-m-n_lp", (220.0 - c1_b_m) - c1_b_n_lp),
      1, 220, 1, 0) - 1];
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 64);
    if (CV_EML_IF(0, 1, 5, CV_RELATIONAL_EVAL(4U, 0U, 1, c1_b_alpha_middle,
          c1_b_alpha_end, -1, 0U, c1_b_alpha_middle == c1_b_alpha_end))) {
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 65);
      chartInstance->c1_alpha = c1_b_alpha_end - (c1_b_alpha_end -
        chartInstance->c1_alpha) * c1_b_alpha_rate;
    } else {
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 67);
      if (CV_EML_IF(0, 1, 6, chartInstance->c1_flag_alpha_stage1 != 0.0)) {
        _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 68);
        c1_delta_alpha = (c1_b_alpha_middle - (c1_b_alpha_middle -
          chartInstance->c1_alpha) * c1_b_alpha_rate) - chartInstance->c1_alpha;
        _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 70);
        c1_A = c1_delta_alpha;
        c1_B = c1_b_alpha_init - c1_b_alpha_middle;
        c1_x = c1_A;
        c1_b_y = c1_B;
        c1_b_x = c1_x;
        c1_c_y = c1_b_y;
        c1_c_x = c1_b_x;
        c1_d_y = c1_c_y;
        c1_d0 = c1_c_x / c1_d_y;
        if (CV_EML_IF(0, 1, 7, CV_RELATIONAL_EVAL(4U, 0U, 2, c1_d0,
              -c1_b_alpha_convg_judge, -1, 4U, c1_d0 > -c1_b_alpha_convg_judge)))
        {
          _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 71);
          chartInstance->c1_flag_alpha_stage1 = 0.0;
        }

        _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 73);
        chartInstance->c1_alpha += c1_delta_alpha;
      } else {
        _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 75);
        chartInstance->c1_alpha = c1_b_alpha_end - (c1_b_alpha_end -
          chartInstance->c1_alpha) * c1_b_alpha_rate2;
      }
    }

    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 78);
    chartInstance->c1_iter++;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 81);
    c1_tmp_sizes = 219;
    for (c1_i3 = 0; c1_i3 < 219; c1_i3++) {
      c1_tmp_data[c1_i3] = 2 + c1_i3;
    }

    c1_b_tmp_sizes[0] = 1;
    c1_b_tmp_sizes[1] = 219;
    for (c1_i4 = 0; c1_i4 < 219; c1_i4++) {
      c1_b_tmp_data[c1_b_tmp_sizes[0] * c1_i4] = chartInstance->c1_x_data[c1_i4];
    }

    for (c1_i5 = 0; c1_i5 < 219; c1_i5++) {
      chartInstance->c1_x_data[c1_tmp_data[c1_i5] - 1] =
        c1_b_tmp_data[c1_b_tmp_sizes[0] * c1_i5];
    }

    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 82);
    chartInstance->c1_x_data[0] = c1_xk;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 84);
    CV_EML_IF(0, 1, 8, chartInstance->c1_SW_TUNE != 0.0);
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 91);
    c1_b_comp_sig = chartInstance->c1_y;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 93);
  c1_b_Q_shape_coef = chartInstance->c1_alpha;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, -93);
  _SFD_SYMBOL_SCOPE_POP();
  *chartInstance->c1_comp_sig = c1_b_comp_sig;
  *chartInstance->c1_Q_shape_coef = c1_b_Q_shape_coef;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
}

static void initSimStructsc1_RC_DOB_mdl(SFc1_RC_DOB_mdlInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber, uint32_T c1_instanceNumber)
{
  (void)c1_machineNumber;
  (void)c1_chartNumber;
  (void)c1_instanceNumber;
}

static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_u;
  const mxArray *c1_b_y = NULL;
  SFc1_RC_DOB_mdlInstanceStruct *chartInstance;
  chartInstance = (SFc1_RC_DOB_mdlInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_b_y = NULL;
  if (!chartInstance->c1_flag_alpha_stage1_not_empty) {
    sf_mex_assign(&c1_b_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_assign(&c1_mxArrayOutData, c1_b_y, false);
  return c1_mxArrayOutData;
}

static real_T c1_emlrt_marshallIn(SFc1_RC_DOB_mdlInstanceStruct *chartInstance,
  const mxArray *c1_b_flag_alpha_stage1, const char_T *c1_identifier)
{
  real_T c1_b_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_b_y = c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c1_b_flag_alpha_stage1), &c1_thisId);
  sf_mex_destroy(&c1_b_flag_alpha_stage1);
  return c1_b_y;
}

static real_T c1_b_emlrt_marshallIn(SFc1_RC_DOB_mdlInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_b_y;
  real_T c1_d1;
  if (mxIsEmpty(c1_u)) {
    chartInstance->c1_flag_alpha_stage1_not_empty = false;
  } else {
    chartInstance->c1_flag_alpha_stage1_not_empty = true;
    sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d1, 1, 0, 0U, 0, 0U, 0);
    c1_b_y = c1_d1;
  }

  sf_mex_destroy(&c1_u);
  return c1_b_y;
}

static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_flag_alpha_stage1;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_b_y;
  SFc1_RC_DOB_mdlInstanceStruct *chartInstance;
  chartInstance = (SFc1_RC_DOB_mdlInstanceStruct *)chartInstanceVoid;
  c1_b_flag_alpha_stage1 = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_b_y = c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c1_b_flag_alpha_stage1), &c1_thisId);
  sf_mex_destroy(&c1_b_flag_alpha_stage1);
  *(real_T *)c1_outData = c1_b_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_u;
  const mxArray *c1_b_y = NULL;
  SFc1_RC_DOB_mdlInstanceStruct *chartInstance;
  chartInstance = (SFc1_RC_DOB_mdlInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_b_y = NULL;
  if (!chartInstance->c1_SW_TUNE_not_empty) {
    sf_mex_assign(&c1_b_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_assign(&c1_mxArrayOutData, c1_b_y, false);
  return c1_mxArrayOutData;
}

static real_T c1_c_emlrt_marshallIn(SFc1_RC_DOB_mdlInstanceStruct *chartInstance,
  const mxArray *c1_b_SW_TUNE, const char_T *c1_identifier)
{
  real_T c1_b_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_b_y = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_SW_TUNE),
    &c1_thisId);
  sf_mex_destroy(&c1_b_SW_TUNE);
  return c1_b_y;
}

static real_T c1_d_emlrt_marshallIn(SFc1_RC_DOB_mdlInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_b_y;
  real_T c1_d2;
  if (mxIsEmpty(c1_u)) {
    chartInstance->c1_SW_TUNE_not_empty = false;
  } else {
    chartInstance->c1_SW_TUNE_not_empty = true;
    sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d2, 1, 0, 0U, 0, 0U, 0);
    c1_b_y = c1_d2;
  }

  sf_mex_destroy(&c1_u);
  return c1_b_y;
}

static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_SW_TUNE;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_b_y;
  SFc1_RC_DOB_mdlInstanceStruct *chartInstance;
  chartInstance = (SFc1_RC_DOB_mdlInstanceStruct *)chartInstanceVoid;
  c1_b_SW_TUNE = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_b_y = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_SW_TUNE),
    &c1_thisId);
  sf_mex_destroy(&c1_b_SW_TUNE);
  *(real_T *)c1_outData = c1_b_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_u;
  const mxArray *c1_b_y = NULL;
  SFc1_RC_DOB_mdlInstanceStruct *chartInstance;
  chartInstance = (SFc1_RC_DOB_mdlInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_b_y = NULL;
  if (!chartInstance->c1_iter_not_empty) {
    sf_mex_assign(&c1_b_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_assign(&c1_mxArrayOutData, c1_b_y, false);
  return c1_mxArrayOutData;
}

static real_T c1_e_emlrt_marshallIn(SFc1_RC_DOB_mdlInstanceStruct *chartInstance,
  const mxArray *c1_b_iter, const char_T *c1_identifier)
{
  real_T c1_b_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_b_y = c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_iter),
    &c1_thisId);
  sf_mex_destroy(&c1_b_iter);
  return c1_b_y;
}

static real_T c1_f_emlrt_marshallIn(SFc1_RC_DOB_mdlInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_b_y;
  real_T c1_d3;
  if (mxIsEmpty(c1_u)) {
    chartInstance->c1_iter_not_empty = false;
  } else {
    chartInstance->c1_iter_not_empty = true;
    sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d3, 1, 0, 0U, 0, 0U, 0);
    c1_b_y = c1_d3;
  }

  sf_mex_destroy(&c1_u);
  return c1_b_y;
}

static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_iter;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_b_y;
  SFc1_RC_DOB_mdlInstanceStruct *chartInstance;
  chartInstance = (SFc1_RC_DOB_mdlInstanceStruct *)chartInstanceVoid;
  c1_b_iter = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_b_y = c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_iter),
    &c1_thisId);
  sf_mex_destroy(&c1_b_iter);
  *(real_T *)c1_outData = c1_b_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_u;
  const mxArray *c1_b_y = NULL;
  SFc1_RC_DOB_mdlInstanceStruct *chartInstance;
  chartInstance = (SFc1_RC_DOB_mdlInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_b_y = NULL;
  if (!chartInstance->c1_alpha_not_empty) {
    sf_mex_assign(&c1_b_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_assign(&c1_mxArrayOutData, c1_b_y, false);
  return c1_mxArrayOutData;
}

static real_T c1_g_emlrt_marshallIn(SFc1_RC_DOB_mdlInstanceStruct *chartInstance,
  const mxArray *c1_b_alpha, const char_T *c1_identifier)
{
  real_T c1_b_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_b_y = c1_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_alpha),
    &c1_thisId);
  sf_mex_destroy(&c1_b_alpha);
  return c1_b_y;
}

static real_T c1_h_emlrt_marshallIn(SFc1_RC_DOB_mdlInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_b_y;
  real_T c1_d4;
  if (mxIsEmpty(c1_u)) {
    chartInstance->c1_alpha_not_empty = false;
  } else {
    chartInstance->c1_alpha_not_empty = true;
    sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d4, 1, 0, 0U, 0, 0U, 0);
    c1_b_y = c1_d4;
  }

  sf_mex_destroy(&c1_u);
  return c1_b_y;
}

static void c1_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_alpha;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_b_y;
  SFc1_RC_DOB_mdlInstanceStruct *chartInstance;
  chartInstance = (SFc1_RC_DOB_mdlInstanceStruct *)chartInstanceVoid;
  c1_b_alpha = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_b_y = c1_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_alpha),
    &c1_thisId);
  sf_mex_destroy(&c1_b_alpha);
  *(real_T *)c1_outData = c1_b_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_e_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_u;
  const mxArray *c1_b_y = NULL;
  SFc1_RC_DOB_mdlInstanceStruct *chartInstance;
  chartInstance = (SFc1_RC_DOB_mdlInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_b_y = NULL;
  if (!chartInstance->c1_y_not_empty) {
    sf_mex_assign(&c1_b_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_assign(&c1_mxArrayOutData, c1_b_y, false);
  return c1_mxArrayOutData;
}

static real_T c1_i_emlrt_marshallIn(SFc1_RC_DOB_mdlInstanceStruct *chartInstance,
  const mxArray *c1_b_y, const char_T *c1_identifier)
{
  real_T c1_c_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_c_y = c1_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_y), &c1_thisId);
  sf_mex_destroy(&c1_b_y);
  return c1_c_y;
}

static real_T c1_j_emlrt_marshallIn(SFc1_RC_DOB_mdlInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_b_y;
  real_T c1_d5;
  if (mxIsEmpty(c1_u)) {
    chartInstance->c1_y_not_empty = false;
  } else {
    chartInstance->c1_y_not_empty = true;
    sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d5, 1, 0, 0U, 0, 0U, 0);
    c1_b_y = c1_d5;
  }

  sf_mex_destroy(&c1_u);
  return c1_b_y;
}

static void c1_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_y;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_c_y;
  SFc1_RC_DOB_mdlInstanceStruct *chartInstance;
  chartInstance = (SFc1_RC_DOB_mdlInstanceStruct *)chartInstanceVoid;
  c1_b_y = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_c_y = c1_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_y), &c1_thisId);
  sf_mex_destroy(&c1_b_y);
  *(real_T *)c1_outData = c1_c_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_f_sf_marshallOut(void *chartInstanceVoid, real_T
  c1_inData_data[], int32_T *c1_inData_sizes)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_b_inData_sizes;
  int32_T c1_i6;
  real_T c1_b_inData_data[220];
  int32_T c1_u_sizes;
  int32_T c1_i7;
  real_T c1_u_data[220];
  const mxArray *c1_b_y = NULL;
  SFc1_RC_DOB_mdlInstanceStruct *chartInstance;
  (void)c1_inData_sizes;
  chartInstance = (SFc1_RC_DOB_mdlInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_b_inData_sizes = 220;
  for (c1_i6 = 0; c1_i6 < 220; c1_i6++) {
    c1_b_inData_data[c1_i6] = c1_inData_data[c1_i6];
  }

  c1_u_sizes = 220;
  for (c1_i7 = 0; c1_i7 < 220; c1_i7++) {
    c1_u_data[c1_i7] = c1_b_inData_data[c1_i7];
  }

  c1_b_y = NULL;
  if (!chartInstance->c1_x_not_empty) {
    sf_mex_assign(&c1_b_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c1_b_y, sf_mex_create("y", c1_u_data, 0, 0U, 1U, 0U, 1,
      c1_u_sizes), false);
  }

  sf_mex_assign(&c1_mxArrayOutData, c1_b_y, false);
  return c1_mxArrayOutData;
}

static void c1_k_emlrt_marshallIn(SFc1_RC_DOB_mdlInstanceStruct *chartInstance,
  const mxArray *c1_x, const char_T *c1_identifier, real_T c1_y_data[], int32_T *
  c1_y_sizes)
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_l_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_x), &c1_thisId, c1_y_data,
                        c1_y_sizes);
  sf_mex_destroy(&c1_x);
}

static void c1_l_emlrt_marshallIn(SFc1_RC_DOB_mdlInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y_data[],
  int32_T *c1_y_sizes)
{
  static uint32_T c1_uv0[1] = { 220U };

  uint32_T c1_uv1[1];
  static boolean_T c1_bv0[1] = { false };

  boolean_T c1_bv1[1];
  int32_T c1_tmp_sizes;
  real_T c1_tmp_data[220];
  int32_T c1_i8;
  c1_uv1[0] = c1_uv0[0];
  if (mxIsEmpty(c1_u)) {
    chartInstance->c1_x_not_empty = false;
    *c1_y_sizes = 220;
  } else {
    chartInstance->c1_x_not_empty = true;
    c1_bv1[0] = c1_bv0[0];
    sf_mex_import_vs(c1_parentId, sf_mex_dup(c1_u), c1_tmp_data, 1, 0, 0U, 1, 0U,
                     1, c1_bv1, c1_uv1, &c1_tmp_sizes);
    *c1_y_sizes = 220;
    for (c1_i8 = 0; c1_i8 < 220; c1_i8++) {
      c1_y_data[c1_i8] = c1_tmp_data[c1_i8];
    }
  }

  sf_mex_destroy(&c1_u);
}

static void c1_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, real_T c1_outData_data[], int32_T
  *c1_outData_sizes)
{
  const mxArray *c1_x;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  int32_T c1_y_sizes;
  real_T c1_y_data[220];
  int32_T c1_i9;
  SFc1_RC_DOB_mdlInstanceStruct *chartInstance;
  chartInstance = (SFc1_RC_DOB_mdlInstanceStruct *)chartInstanceVoid;
  c1_x = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_l_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_x), &c1_thisId, c1_y_data,
                        &c1_y_sizes);
  sf_mex_destroy(&c1_x);
  *c1_outData_sizes = 220;
  for (c1_i9 = 0; c1_i9 < 220; c1_i9++) {
    c1_outData_data[c1_i9] = c1_y_data[c1_i9];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_g_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_u;
  const mxArray *c1_b_y = NULL;
  SFc1_RC_DOB_mdlInstanceStruct *chartInstance;
  chartInstance = (SFc1_RC_DOB_mdlInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_b_y = NULL;
  if (!chartInstance->c1_N_not_empty) {
    sf_mex_assign(&c1_b_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_assign(&c1_mxArrayOutData, c1_b_y, false);
  return c1_mxArrayOutData;
}

static real_T c1_m_emlrt_marshallIn(SFc1_RC_DOB_mdlInstanceStruct *chartInstance,
  const mxArray *c1_b_N, const char_T *c1_identifier)
{
  real_T c1_b_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_b_y = c1_n_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_N), &c1_thisId);
  sf_mex_destroy(&c1_b_N);
  return c1_b_y;
}

static real_T c1_n_emlrt_marshallIn(SFc1_RC_DOB_mdlInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_b_y;
  real_T c1_d6;
  if (mxIsEmpty(c1_u)) {
    chartInstance->c1_N_not_empty = false;
  } else {
    chartInstance->c1_N_not_empty = true;
    sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d6, 1, 0, 0U, 0, 0U, 0);
    c1_b_y = c1_d6;
  }

  sf_mex_destroy(&c1_u);
  return c1_b_y;
}

static void c1_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_N;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_b_y;
  SFc1_RC_DOB_mdlInstanceStruct *chartInstance;
  chartInstance = (SFc1_RC_DOB_mdlInstanceStruct *)chartInstanceVoid;
  c1_b_N = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_b_y = c1_n_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_N), &c1_thisId);
  sf_mex_destroy(&c1_b_N);
  *(real_T *)c1_outData = c1_b_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_h_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_u;
  const mxArray *c1_b_y = NULL;
  SFc1_RC_DOB_mdlInstanceStruct *chartInstance;
  chartInstance = (SFc1_RC_DOB_mdlInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_b_y, false);
  return c1_mxArrayOutData;
}

static real_T c1_o_emlrt_marshallIn(SFc1_RC_DOB_mdlInstanceStruct *chartInstance,
  const mxArray *c1_b_Q_shape_coef, const char_T *c1_identifier)
{
  real_T c1_b_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_b_y = c1_p_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_Q_shape_coef),
    &c1_thisId);
  sf_mex_destroy(&c1_b_Q_shape_coef);
  return c1_b_y;
}

static real_T c1_p_emlrt_marshallIn(SFc1_RC_DOB_mdlInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_b_y;
  real_T c1_d7;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d7, 1, 0, 0U, 0, 0U, 0);
  c1_b_y = c1_d7;
  sf_mex_destroy(&c1_u);
  return c1_b_y;
}

static void c1_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_Q_shape_coef;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_b_y;
  SFc1_RC_DOB_mdlInstanceStruct *chartInstance;
  chartInstance = (SFc1_RC_DOB_mdlInstanceStruct *)chartInstanceVoid;
  c1_b_Q_shape_coef = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_b_y = c1_p_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_Q_shape_coef),
    &c1_thisId);
  sf_mex_destroy(&c1_b_Q_shape_coef);
  *(real_T *)c1_outData = c1_b_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

const mxArray *sf_c1_RC_DOB_mdl_get_eml_resolved_functions_info(void)
{
  const mxArray *c1_nameCaptureInfo = NULL;
  c1_nameCaptureInfo = NULL;
  sf_mex_assign(&c1_nameCaptureInfo, sf_mex_createstruct("structure", 2, 21, 1),
                false);
  c1_info_helper(&c1_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c1_nameCaptureInfo);
  return c1_nameCaptureInfo;
}

static void c1_info_helper(const mxArray **c1_info)
{
  const mxArray *c1_rhs0 = NULL;
  const mxArray *c1_lhs0 = NULL;
  const mxArray *c1_rhs1 = NULL;
  const mxArray *c1_lhs1 = NULL;
  const mxArray *c1_rhs2 = NULL;
  const mxArray *c1_lhs2 = NULL;
  const mxArray *c1_rhs3 = NULL;
  const mxArray *c1_lhs3 = NULL;
  const mxArray *c1_rhs4 = NULL;
  const mxArray *c1_lhs4 = NULL;
  const mxArray *c1_rhs5 = NULL;
  const mxArray *c1_lhs5 = NULL;
  const mxArray *c1_rhs6 = NULL;
  const mxArray *c1_lhs6 = NULL;
  const mxArray *c1_rhs7 = NULL;
  const mxArray *c1_lhs7 = NULL;
  const mxArray *c1_rhs8 = NULL;
  const mxArray *c1_lhs8 = NULL;
  const mxArray *c1_rhs9 = NULL;
  const mxArray *c1_lhs9 = NULL;
  const mxArray *c1_rhs10 = NULL;
  const mxArray *c1_lhs10 = NULL;
  const mxArray *c1_rhs11 = NULL;
  const mxArray *c1_lhs11 = NULL;
  const mxArray *c1_rhs12 = NULL;
  const mxArray *c1_lhs12 = NULL;
  const mxArray *c1_rhs13 = NULL;
  const mxArray *c1_lhs13 = NULL;
  const mxArray *c1_rhs14 = NULL;
  const mxArray *c1_lhs14 = NULL;
  const mxArray *c1_rhs15 = NULL;
  const mxArray *c1_lhs15 = NULL;
  const mxArray *c1_rhs16 = NULL;
  const mxArray *c1_lhs16 = NULL;
  const mxArray *c1_rhs17 = NULL;
  const mxArray *c1_lhs17 = NULL;
  const mxArray *c1_rhs18 = NULL;
  const mxArray *c1_lhs18 = NULL;
  const mxArray *c1_rhs19 = NULL;
  const mxArray *c1_lhs19 = NULL;
  const mxArray *c1_rhs20 = NULL;
  const mxArray *c1_lhs20 = NULL;
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("mpower"), "name", "name", 0);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "resolved",
                  "resolved", 0);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363731878U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c1_rhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs0), "rhs", "rhs", 0);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs0), "lhs", "lhs", 0);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "context",
                  "context", 1);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 1);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 1);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1395949856U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c1_rhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs1), "rhs", "rhs", 1);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs1), "lhs", "lhs", 1);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "context",
                  "context", 2);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("ismatrix"), "name", "name", 2);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/ismatrix.m"), "resolved",
                  "resolved", 2);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1331326458U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c1_rhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs2), "rhs", "rhs", 2);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs2), "lhs", "lhs", 2);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "context",
                  "context", 3);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("power"), "name", "name", 3);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 3);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m"), "resolved",
                  "resolved", 3);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1395346506U), "fileTimeLo",
                  "fileTimeLo", 3);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 3);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 3);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 3);
  sf_mex_assign(&c1_rhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs3), "rhs", "rhs", 3);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs3), "lhs", "lhs", 3);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m"), "context",
                  "context", 4);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 4);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 4);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 4);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1395949856U), "fileTimeLo",
                  "fileTimeLo", 4);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 4);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 4);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 4);
  sf_mex_assign(&c1_rhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs4), "rhs", "rhs", 4);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs4), "lhs", "lhs", 4);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower"), "context",
                  "context", 5);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 5);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 5);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 5);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1376002288U), "fileTimeLo",
                  "fileTimeLo", 5);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 5);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 5);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 5);
  sf_mex_assign(&c1_rhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs5), "rhs", "rhs", 5);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs5), "lhs", "lhs", 5);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "context",
                  "context", 6);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 6);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 6);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 6);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1410829370U), "fileTimeLo",
                  "fileTimeLo", 6);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 6);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 6);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 6);
  sf_mex_assign(&c1_rhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs6), "rhs", "rhs", 6);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs6), "lhs", "lhs", 6);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower"), "context",
                  "context", 7);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalexp_alloc"), "name",
                  "name", 7);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 7);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "resolved", "resolved", 7);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1376002288U), "fileTimeLo",
                  "fileTimeLo", 7);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 7);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 7);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 7);
  sf_mex_assign(&c1_rhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs7), "rhs", "rhs", 7);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs7), "lhs", "lhs", 7);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "context", "context", 8);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.scalexpAlloc"),
                  "name", "name", 8);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 8);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalexpAlloc.p"),
                  "resolved", "resolved", 8);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1410829370U), "fileTimeLo",
                  "fileTimeLo", 8);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 8);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 8);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 8);
  sf_mex_assign(&c1_rhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs8), "rhs", "rhs", 8);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs8), "lhs", "lhs", 8);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower"), "context",
                  "context", 9);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("floor"), "name", "name", 9);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 9);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "resolved",
                  "resolved", 9);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363731854U), "fileTimeLo",
                  "fileTimeLo", 9);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 9);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 9);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 9);
  sf_mex_assign(&c1_rhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs9), "rhs", "rhs", 9);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs9), "lhs", "lhs", 9);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 10);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 10);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 10);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 10);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1395949856U), "fileTimeLo",
                  "fileTimeLo", 10);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 10);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 10);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 10);
  sf_mex_assign(&c1_rhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs10), "rhs", "rhs",
                  10);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs10), "lhs", "lhs",
                  10);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 11);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalar_floor"), "name",
                  "name", 11);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 11);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m"),
                  "resolved", "resolved", 11);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286840326U), "fileTimeLo",
                  "fileTimeLo", 11);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 11);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 11);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 11);
  sf_mex_assign(&c1_rhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs11), "rhs", "rhs",
                  11);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs11), "lhs", "lhs",
                  11);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower"), "context",
                  "context", 12);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_error"), "name", "name",
                  12);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 12);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m"), "resolved",
                  "resolved", 12);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1343851958U), "fileTimeLo",
                  "fileTimeLo", 12);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 12);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 12);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 12);
  sf_mex_assign(&c1_rhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs12), "rhs", "rhs",
                  12);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs12), "lhs", "lhs",
                  12);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!scalar_float_power"),
                  "context", "context", 13);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 13);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 13);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 13);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1376002288U), "fileTimeLo",
                  "fileTimeLo", 13);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 13);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 13);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 13);
  sf_mex_assign(&c1_rhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs13), "rhs", "rhs",
                  13);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs13), "lhs", "lhs",
                  13);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "context", "context", 14);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("mrdivide"), "name", "name", 14);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 14);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "resolved",
                  "resolved", 14);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1410829248U), "fileTimeLo",
                  "fileTimeLo", 14);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 14);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1370031486U), "mFileTimeLo",
                  "mFileTimeLo", 14);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 14);
  sf_mex_assign(&c1_rhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs14), "rhs", "rhs",
                  14);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs14), "lhs", "lhs",
                  14);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "context",
                  "context", 15);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.assert"),
                  "name", "name", 15);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 15);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/assert.m"),
                  "resolved", "resolved", 15);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1389739374U), "fileTimeLo",
                  "fileTimeLo", 15);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 15);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 15);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 15);
  sf_mex_assign(&c1_rhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs15), "rhs", "rhs",
                  15);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs15), "lhs", "lhs",
                  15);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "context",
                  "context", 16);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("rdivide"), "name", "name", 16);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 16);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "resolved",
                  "resolved", 16);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363731880U), "fileTimeLo",
                  "fileTimeLo", 16);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 16);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 16);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 16);
  sf_mex_assign(&c1_rhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs16), "rhs", "rhs",
                  16);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs16), "lhs", "lhs",
                  16);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 17);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 17);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 17);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 17);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1395949856U), "fileTimeLo",
                  "fileTimeLo", 17);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 17);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 17);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 17);
  sf_mex_assign(&c1_rhs17, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs17, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs17), "rhs", "rhs",
                  17);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs17), "lhs", "lhs",
                  17);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 18);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalexp_compatible"),
                  "name", "name", 18);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 18);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m"),
                  "resolved", "resolved", 18);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286840396U), "fileTimeLo",
                  "fileTimeLo", 18);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 18);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 18);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 18);
  sf_mex_assign(&c1_rhs18, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs18, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs18), "rhs", "rhs",
                  18);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs18), "lhs", "lhs",
                  18);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 19);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_div"), "name", "name", 19);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 19);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "resolved",
                  "resolved", 19);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1386445552U), "fileTimeLo",
                  "fileTimeLo", 19);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 19);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 19);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 19);
  sf_mex_assign(&c1_rhs19, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs19, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs19), "rhs", "rhs",
                  19);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs19), "lhs", "lhs",
                  19);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "context",
                  "context", 20);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.div"), "name",
                  "name", 20);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 20);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/div.p"), "resolved",
                  "resolved", 20);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1410829370U), "fileTimeLo",
                  "fileTimeLo", 20);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 20);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 20);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 20);
  sf_mex_assign(&c1_rhs20, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs20, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs20), "rhs", "rhs",
                  20);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs20), "lhs", "lhs",
                  20);
  sf_mex_destroy(&c1_rhs0);
  sf_mex_destroy(&c1_lhs0);
  sf_mex_destroy(&c1_rhs1);
  sf_mex_destroy(&c1_lhs1);
  sf_mex_destroy(&c1_rhs2);
  sf_mex_destroy(&c1_lhs2);
  sf_mex_destroy(&c1_rhs3);
  sf_mex_destroy(&c1_lhs3);
  sf_mex_destroy(&c1_rhs4);
  sf_mex_destroy(&c1_lhs4);
  sf_mex_destroy(&c1_rhs5);
  sf_mex_destroy(&c1_lhs5);
  sf_mex_destroy(&c1_rhs6);
  sf_mex_destroy(&c1_lhs6);
  sf_mex_destroy(&c1_rhs7);
  sf_mex_destroy(&c1_lhs7);
  sf_mex_destroy(&c1_rhs8);
  sf_mex_destroy(&c1_lhs8);
  sf_mex_destroy(&c1_rhs9);
  sf_mex_destroy(&c1_lhs9);
  sf_mex_destroy(&c1_rhs10);
  sf_mex_destroy(&c1_lhs10);
  sf_mex_destroy(&c1_rhs11);
  sf_mex_destroy(&c1_lhs11);
  sf_mex_destroy(&c1_rhs12);
  sf_mex_destroy(&c1_lhs12);
  sf_mex_destroy(&c1_rhs13);
  sf_mex_destroy(&c1_lhs13);
  sf_mex_destroy(&c1_rhs14);
  sf_mex_destroy(&c1_lhs14);
  sf_mex_destroy(&c1_rhs15);
  sf_mex_destroy(&c1_lhs15);
  sf_mex_destroy(&c1_rhs16);
  sf_mex_destroy(&c1_lhs16);
  sf_mex_destroy(&c1_rhs17);
  sf_mex_destroy(&c1_lhs17);
  sf_mex_destroy(&c1_rhs18);
  sf_mex_destroy(&c1_lhs18);
  sf_mex_destroy(&c1_rhs19);
  sf_mex_destroy(&c1_lhs19);
  sf_mex_destroy(&c1_rhs20);
  sf_mex_destroy(&c1_lhs20);
}

static const mxArray *c1_emlrt_marshallOut(const char * c1_u)
{
  const mxArray *c1_b_y = NULL;
  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", c1_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c1_u)), false);
  return c1_b_y;
}

static const mxArray *c1_b_emlrt_marshallOut(const uint32_T c1_u)
{
  const mxArray *c1_b_y = NULL;
  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_u, 7, 0U, 0U, 0U, 0), false);
  return c1_b_y;
}

static void c1_eml_scalar_eg(SFc1_RC_DOB_mdlInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *c1_i_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_u;
  const mxArray *c1_b_y = NULL;
  SFc1_RC_DOB_mdlInstanceStruct *chartInstance;
  chartInstance = (SFc1_RC_DOB_mdlInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(int32_T *)c1_inData;
  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_b_y, false);
  return c1_mxArrayOutData;
}

static int32_T c1_q_emlrt_marshallIn(SFc1_RC_DOB_mdlInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  int32_T c1_b_y;
  int32_T c1_i10;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_i10, 1, 6, 0U, 0, 0U, 0);
  c1_b_y = c1_i10;
  sf_mex_destroy(&c1_u);
  return c1_b_y;
}

static void c1_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_sfEvent;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  int32_T c1_b_y;
  SFc1_RC_DOB_mdlInstanceStruct *chartInstance;
  chartInstance = (SFc1_RC_DOB_mdlInstanceStruct *)chartInstanceVoid;
  c1_b_sfEvent = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_b_y = c1_q_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_sfEvent),
    &c1_thisId);
  sf_mex_destroy(&c1_b_sfEvent);
  *(int32_T *)c1_outData = c1_b_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static uint8_T c1_r_emlrt_marshallIn(SFc1_RC_DOB_mdlInstanceStruct
  *chartInstance, const mxArray *c1_b_is_active_c1_RC_DOB_mdl, const char_T
  *c1_identifier)
{
  uint8_T c1_b_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_b_y = c1_s_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c1_b_is_active_c1_RC_DOB_mdl), &c1_thisId);
  sf_mex_destroy(&c1_b_is_active_c1_RC_DOB_mdl);
  return c1_b_y;
}

static uint8_T c1_s_emlrt_marshallIn(SFc1_RC_DOB_mdlInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint8_T c1_b_y;
  uint8_T c1_u0;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_u0, 1, 3, 0U, 0, 0U, 0);
  c1_b_y = c1_u0;
  sf_mex_destroy(&c1_u);
  return c1_b_y;
}

static void init_dsm_address_info(SFc1_RC_DOB_mdlInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc1_RC_DOB_mdlInstanceStruct
  *chartInstance)
{
  chartInstance->c1_uk = (real_T *)ssGetInputPortSignal_wrapper(chartInstance->S,
    0);
  chartInstance->c1_comp_sig = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c1_SW = (real_T *)ssGetInputPortSignal_wrapper(chartInstance->S,
    1);
  chartInstance->c1_Q_shape_coef = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c1_alpha_init = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c1_alpha_end = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c1_alpha_rate = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 4);
  chartInstance->c1_Nq = (real_T *)ssGetInputPortSignal_wrapper(chartInstance->S,
    5);
  chartInstance->c1_m = (real_T *)ssGetInputPortSignal_wrapper(chartInstance->S,
    6);
  chartInstance->c1_n_lp = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 7);
  chartInstance->c1_alpha_middle = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 8);
  chartInstance->c1_alpha_convg_judge = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 9);
  chartInstance->c1_alpha_rate2 = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 10);
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c1_RC_DOB_mdl_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1933748176U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(4005672018U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3713697444U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3143134449U);
}

mxArray* sf_c1_RC_DOB_mdl_get_post_codegen_info(void);
mxArray *sf_c1_RC_DOB_mdl_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("0x0Hy46HjD3Dk2nVvS6QhG");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,11,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,6,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,6,"type",mxType);
    }

    mxSetField(mxData,6,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,7,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,7,"type",mxType);
    }

    mxSetField(mxData,7,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,8,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,8,"type",mxType);
    }

    mxSetField(mxData,8,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,9,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,9,"type",mxType);
    }

    mxSetField(mxData,9,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,10,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,10,"type",mxType);
    }

    mxSetField(mxData,10,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c1_RC_DOB_mdl_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c1_RC_DOB_mdl_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c1_RC_DOB_mdl_jit_fallback_info(void)
{
  const char *infoFields[] = { "fallbackType", "fallbackReason",
    "incompatibleSymbol", };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 3, infoFields);
  mxArray *fallbackReason = mxCreateString("feature_off");
  mxArray *incompatibleSymbol = mxCreateString("");
  mxArray *fallbackType = mxCreateString("early");
  mxSetField(mxInfo, 0, infoFields[0], fallbackType);
  mxSetField(mxInfo, 0, infoFields[1], fallbackReason);
  mxSetField(mxInfo, 0, infoFields[2], incompatibleSymbol);
  return mxInfo;
}

mxArray *sf_c1_RC_DOB_mdl_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c1_RC_DOB_mdl_get_post_codegen_info(void)
{
  const char* fieldNames[] = { "exportedFunctionsUsedByThisChart",
    "exportedFunctionsChecksum" };

  mwSize dims[2] = { 1, 1 };

  mxArray* mxPostCodegenInfo = mxCreateStructArray(2, dims, sizeof(fieldNames)/
    sizeof(fieldNames[0]), fieldNames);

  {
    mxArray* mxExportedFunctionsChecksum = mxCreateString("");
    mwSize exp_dims[2] = { 0, 1 };

    mxArray* mxExportedFunctionsUsedByThisChart = mxCreateCellArray(2, exp_dims);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsUsedByThisChart",
               mxExportedFunctionsUsedByThisChart);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsChecksum",
               mxExportedFunctionsChecksum);
  }

  return mxPostCodegenInfo;
}

static const mxArray *sf_get_sim_state_info_c1_RC_DOB_mdl(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x10'type','srcId','name','auxInfo'{{M[1],M[29],T\"Q_shape_coef\",},{M[1],M[5],T\"comp_sig\",},{M[4],M[0],T\"N\",S'l','i','p'{{M1x2[229 230],M[0],}}},{M[4],M[0],T\"SW_TUNE\",S'l','i','p'{{M1x2[287 294],M[0],}}},{M[4],M[0],T\"alpha\",S'l','i','p'{{M1x2[267 272],M[0],}}},{M[4],M[0],T\"flag_alpha_stage1\",S'l','i','p'{{M1x2[299 316],M[0],}}},{M[4],M[0],T\"iter\",S'l','i','p'{{M1x2[275 279],M[0],}}},{M[4],M[0],T\"x\",S'l','i','p'{{M1x2[239 240],M[0],}}},{M[4],M[0],T\"y\",S'l','i','p'{{M1x2[247 248],M[0],}}},{M[8],M[0],T\"is_active_c1_RC_DOB_mdl\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 10, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c1_RC_DOB_mdl_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc1_RC_DOB_mdlInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc1_RC_DOB_mdlInstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _RC_DOB_mdlMachineNumber_,
           1,
           1,
           1,
           0,
           13,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           (void *)S);

        /* Each instance must initialize its own list of scripts */
        init_script_number_translation(_RC_DOB_mdlMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_RC_DOB_mdlMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _RC_DOB_mdlMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"uk");
          _SFD_SET_DATA_PROPS(1,2,0,1,"comp_sig");
          _SFD_SET_DATA_PROPS(2,1,1,0,"SW");
          _SFD_SET_DATA_PROPS(3,2,0,1,"Q_shape_coef");
          _SFD_SET_DATA_PROPS(4,1,1,0,"alpha_init");
          _SFD_SET_DATA_PROPS(5,1,1,0,"alpha_end");
          _SFD_SET_DATA_PROPS(6,1,1,0,"alpha_rate");
          _SFD_SET_DATA_PROPS(7,1,1,0,"Nq");
          _SFD_SET_DATA_PROPS(8,1,1,0,"m");
          _SFD_SET_DATA_PROPS(9,1,1,0,"n_lp");
          _SFD_SET_DATA_PROPS(10,1,1,0,"alpha_middle");
          _SFD_SET_DATA_PROPS(11,1,1,0,"alpha_convg_judge");
          _SFD_SET_DATA_PROPS(12,1,1,0,"alpha_rate2");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,10,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,2303);
        _SFD_CV_INIT_EML_IF(0,1,0,587,600,-1,989);
        _SFD_CV_INIT_EML_IF(0,1,1,605,609,631,659);
        _SFD_CV_INIT_EML_IF(0,1,2,990,1000,1227,2270);
        _SFD_CV_INIT_EML_IF(0,1,3,1086,1090,1138,1200);
        _SFD_CV_INIT_EML_IF(0,1,4,1254,1258,1298,1352);
        _SFD_CV_INIT_EML_IF(0,1,5,1383,1411,1477,2006);
        _SFD_CV_INIT_EML_IF(0,1,6,1490,1510,1873,1998);
        _SFD_CV_INIT_EML_IF(0,1,7,1700,1762,-1,1823);
        _SFD_CV_INIT_EML_IF(0,1,8,2162,2172,2227,2248);
        _SFD_CV_INIT_EML_IF(0,1,9,2181,2190,-1,2222);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,0,993,1000,-1,0);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,1,1386,1411,-1,0);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,2,1703,1762,-1,4);
        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_h_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_h_sf_marshallOut,(MexInFcnForType)c1_h_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_h_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_h_sf_marshallOut,(MexInFcnForType)c1_h_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_h_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_h_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_h_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_h_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_h_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_h_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(10,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_h_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(11,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_h_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(12,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_h_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_VALUE_PTR(0U, chartInstance->c1_uk);
        _SFD_SET_DATA_VALUE_PTR(1U, chartInstance->c1_comp_sig);
        _SFD_SET_DATA_VALUE_PTR(2U, chartInstance->c1_SW);
        _SFD_SET_DATA_VALUE_PTR(3U, chartInstance->c1_Q_shape_coef);
        _SFD_SET_DATA_VALUE_PTR(4U, chartInstance->c1_alpha_init);
        _SFD_SET_DATA_VALUE_PTR(5U, chartInstance->c1_alpha_end);
        _SFD_SET_DATA_VALUE_PTR(6U, chartInstance->c1_alpha_rate);
        _SFD_SET_DATA_VALUE_PTR(7U, chartInstance->c1_Nq);
        _SFD_SET_DATA_VALUE_PTR(8U, chartInstance->c1_m);
        _SFD_SET_DATA_VALUE_PTR(9U, chartInstance->c1_n_lp);
        _SFD_SET_DATA_VALUE_PTR(10U, chartInstance->c1_alpha_middle);
        _SFD_SET_DATA_VALUE_PTR(11U, chartInstance->c1_alpha_convg_judge);
        _SFD_SET_DATA_VALUE_PTR(12U, chartInstance->c1_alpha_rate2);
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _RC_DOB_mdlMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "6kqLorQTtrXVfAHHdlp5H";
}

static void sf_opaque_initialize_c1_RC_DOB_mdl(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc1_RC_DOB_mdlInstanceStruct*) chartInstanceVar
    )->S,0);
  initialize_params_c1_RC_DOB_mdl((SFc1_RC_DOB_mdlInstanceStruct*)
    chartInstanceVar);
  initialize_c1_RC_DOB_mdl((SFc1_RC_DOB_mdlInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c1_RC_DOB_mdl(void *chartInstanceVar)
{
  enable_c1_RC_DOB_mdl((SFc1_RC_DOB_mdlInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c1_RC_DOB_mdl(void *chartInstanceVar)
{
  disable_c1_RC_DOB_mdl((SFc1_RC_DOB_mdlInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c1_RC_DOB_mdl(void *chartInstanceVar)
{
  sf_gateway_c1_RC_DOB_mdl((SFc1_RC_DOB_mdlInstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c1_RC_DOB_mdl(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  return get_sim_state_c1_RC_DOB_mdl((SFc1_RC_DOB_mdlInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c1_RC_DOB_mdl(SimStruct* S, const mxArray
  *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  set_sim_state_c1_RC_DOB_mdl((SFc1_RC_DOB_mdlInstanceStruct*)
    chartInfo->chartInstance, st);
}

static void sf_opaque_terminate_c1_RC_DOB_mdl(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc1_RC_DOB_mdlInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_RC_DOB_mdl_optimization_info();
    }

    finalize_c1_RC_DOB_mdl((SFc1_RC_DOB_mdlInstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (crtInfo != NULL) {
      utFree(crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc1_RC_DOB_mdl((SFc1_RC_DOB_mdlInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c1_RC_DOB_mdl(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    initialize_params_c1_RC_DOB_mdl((SFc1_RC_DOB_mdlInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c1_RC_DOB_mdl(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_RC_DOB_mdl_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,1);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,1,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,1,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,1);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 6, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 7, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 8, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 9, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 10, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,1,11);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,1,2);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=2; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 11; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,1);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(561575621U));
  ssSetChecksum1(S,(4291555181U));
  ssSetChecksum2(S,(2671298379U));
  ssSetChecksum3(S,(908250758U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c1_RC_DOB_mdl(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c1_RC_DOB_mdl(SimStruct *S)
{
  SFc1_RC_DOB_mdlInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc1_RC_DOB_mdlInstanceStruct *)utMalloc(sizeof
    (SFc1_RC_DOB_mdlInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc1_RC_DOB_mdlInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c1_RC_DOB_mdl;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c1_RC_DOB_mdl;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c1_RC_DOB_mdl;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c1_RC_DOB_mdl;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c1_RC_DOB_mdl;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c1_RC_DOB_mdl;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c1_RC_DOB_mdl;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c1_RC_DOB_mdl;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c1_RC_DOB_mdl;
  chartInstance->chartInfo.mdlStart = mdlStart_c1_RC_DOB_mdl;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c1_RC_DOB_mdl;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  crtInfo->checksum = SF_RUNTIME_INFO_CHECKSUM;
  crtInfo->instanceInfo = (&(chartInstance->chartInfo));
  crtInfo->isJITEnabled = false;
  crtInfo->compiledInfo = NULL;
  ssSetUserData(S,(void *)(crtInfo));  /* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  init_simulink_io_address(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c1_RC_DOB_mdl_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c1_RC_DOB_mdl(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c1_RC_DOB_mdl(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c1_RC_DOB_mdl(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c1_RC_DOB_mdl_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
