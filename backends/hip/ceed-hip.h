// Copyright (c) 2017-2018, Lawrence Livermore National Security, LLC.
// Produced at the Lawrence Livermore National Laboratory. LLNL-CODE-734707.
// All Rights reserved. See files LICENSE and NOTICE for details.
//
// This file is part of CEED, a collection of benchmarks, miniapps, software
// libraries and APIs for efficient high-order finite element and spectral
// element discretizations for exascale applications. For more information and
// source code availability see http://github.com/ceed.
//
// The CEED research is supported by the Exascale Computing Project 17-SC-20-SC,
// a collaborative effort of two U.S. Department of Energy organizations (Office
// of Science and the National Nuclear Security Administration) responsible for
// the planning and preparation of a capable exascale ecosystem, including
// software, applications, hardware, advanced system engineering and early
// testbed platforms, in support of the nation's exascale computing imperative.
#ifndef _ceed_hip_h
#define _ceed_hip_h

#include <ceed-backend.h>
#include <ceed.h>
#include <hip/hip_runtime_api.h>
#include <hip/hiprtc.h>

#define HIP_MAX_PATH 256

#define CeedChk_Hiprtc(ceed, x) \
do { \
  if (x != HIPRTC_SUCCESS) \
    return CeedError((ceed), 1, hiprtcGetErrorString(x)); \
} while (0)

#define CeedChk_ModHip(ceed, x) \
do { \
  if (x != HIP_SUCCESS) { \
    return CeedError((ceed), 1, hipGetErrorString(x)); \
  } \
} while (0)

#define CeedChk_Hip(ceed, x) \
do { \
  if (x != HIP_SUCCESS) { \
    return CeedError((ceed), 1, "hip error"); \
  } \
} while (0)

#define QUOTE(...) #__VA_ARGS__

typedef enum {CEED_HIP_HOST_SYNC,
              CEED_HIP_DEVICE_SYNC,
              CEED_HIP_BOTH_SYNC,
              CEED_HIP_NONE_SYNC
             } CeedHipSyncState;

typedef struct {
  CeedScalar *h_array;
  CeedScalar *h_array_allocated;
  CeedScalar *d_array;
  CeedScalar *d_array_allocated;
  CeedHipSyncState memState;
} CeedVector_Hip;

typedef struct {
  hipModule_t module;
  hipFunction_t noTrStrided;
  hipFunction_t noTrNoTr;
  hipFunction_t noTrTr;
  hipFunction_t trStrided;
  hipFunction_t trNoTr;
  hipFunction_t trTr;
  CeedInt *h_ind;
  CeedInt *h_ind_allocated;
  CeedInt *d_ind;
  CeedInt *d_ind_allocated;
} CeedElemRestriction_Hip;

// We use a struct to avoid having to memCpy the array of pointers
// __global__ copies by value the struct.
typedef struct {
  const CeedScalar *inputs[16];
  CeedScalar *outputs[16];
} Fields_Hip;

typedef struct {
  hipModule_t module;
  char *qFunctionName;
  char *qFunctionSource;
  hipFunction_t qFunction;
  Fields_Hip fields;
  void *d_c;
} CeedQFunction_Hip;

typedef struct {
  hipModule_t module;
  hipFunction_t interp;
  hipFunction_t grad;
  hipFunction_t weight;
  CeedScalar *d_interp1d;
  CeedScalar *d_grad1d;
  CeedScalar *d_qweight1d;
} CeedBasis_Hip;

typedef struct {
  hipModule_t module;
  hipFunction_t interp;
  hipFunction_t grad;
  hipFunction_t weight;
  CeedScalar *d_interp;
  CeedScalar *d_grad;
  CeedScalar *d_qweight;
} CeedBasisNonTensor_Hip;

typedef struct {
  CeedVector
  *evecs;   /// E-vectors needed to apply operator (input followed by outputs)
  CeedScalar **edata;
  CeedVector *qvecsin;   /// Input Q-vectors needed to apply operator
  CeedVector *qvecsout;   /// Output Q-vectors needed to apply operator
  CeedInt    numein;
  CeedInt    numeout;
} CeedOperator_Hip;

typedef struct {
  int optblocksize;
  int deviceId;
} Ceed_Hip;

static inline CeedInt CeedDivUpInt(CeedInt numer, CeedInt denom) {
  return (numer + denom - 1) / denom;
}
//***
CEED_INTERN int CeedDeviceSetValue(CeedScalar *d_array, CeedInt length, CeedScalar val);
//***

CEED_INTERN int CeedCompileHip(Ceed ceed, const char *source, hipModule_t *module,
                                const CeedInt numopts, ...);

CEED_INTERN int CeedGetKernelHip(Ceed ceed, hipModule_t module, const char *name,
                                  hipFunction_t *kernel);

CEED_INTERN int CeedRunKernelHip(Ceed ceed, hipFunction_t kernel,
                                  const int gridSize,
                                  const int blockSize, void **args);

CEED_INTERN int CeedRunKernelDimHip(Ceed ceed, hipFunction_t kernel,
                                     const int gridSize,
                                     const int blockSizeX, const int blockSizeY,
                                     const int blockSizeZ, void **args);

CEED_INTERN int CeedRunKernelDimSharedHip(Ceed ceed, hipFunction_t kernel,
    const int gridSize, const int blockSizeX, const int blockSizeY,
    const int blockSizeZ, const int sharedMemSize, void **args);

CEED_INTERN int run_kernel_dim_shared(Ceed ceed, hipFunction_t kernel,
                                      const int gridSize,
                                      const int blockSizeX,
                                      const int blockSizeY,
                                      const int blockSizeZ,
                                      const int sharedMemSize, void **args);

CEED_INTERN int run_kernel_dim_shared(Ceed ceed, hipFunction_t kernel,
                                      const int gridSize,
                                      const int blockSizeX, const int blockSizeY,
                                      const int blockSizeZ,
                                      const int sharedMemSize,
                                      void **args);
CEED_INTERN int CeedHipInit(Ceed ceed, const char *resource, int nrc);

CEED_INTERN int CeedVectorCreate_Hip(CeedInt n, CeedVector vec);

CEED_INTERN int CeedElemRestrictionCreate_Hip(CeedMemType mtype,
    CeedCopyMode cmode, const CeedInt *indices, CeedElemRestriction r);

CEED_INTERN int CeedElemRestrictionCreateBlocked_Hip(const CeedMemType mtype,
    const CeedCopyMode cmode, const CeedInt *indices,
    const CeedElemRestriction res);

CEED_INTERN int CeedBasisApplyElems_Hip(CeedBasis basis, const CeedInt nelem,
    CeedTransposeMode tmode, CeedEvalMode emode, const CeedVector u, CeedVector v);

CEED_INTERN int CeedQFunctionApplyElems_Hip(CeedQFunction qf, const CeedInt Q,
    const CeedVector *const u, const CeedVector *v);

CEED_INTERN int CeedBasisCreateTensorH1_Hip(CeedInt dim, CeedInt P1d,
    CeedInt Q1d,
    const CeedScalar *interp1d,
    const CeedScalar *grad1d,
    const CeedScalar *qref1d,
    const CeedScalar *qweight1d,
    CeedBasis basis);

CEED_INTERN int CeedBasisCreateH1_Hip(CeedElemTopology, CeedInt, CeedInt,
                                       CeedInt, const CeedScalar *,
                                       const CeedScalar *, const CeedScalar *,
                                       const CeedScalar *, CeedBasis);

CEED_INTERN int CeedQFunctionCreate_Hip(CeedQFunction qf);

CEED_INTERN int CeedOperatorCreate_Hip(CeedOperator op);

CEED_INTERN int CeedCompositeOperatorCreate_Hip(CeedOperator op);
#endif
