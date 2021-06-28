#ifndef matops_h
#define matops_h

#include <ceed.h>
#include <petsc.h>
#include <petscdmplex.h>

#include "structs.h"

PetscErrorCode MatGetDiag(Mat A, Vec D);
PetscErrorCode ApplyLocal_Ceed(Vec X, Vec Y, UserO user);
PetscErrorCode MatMult_Ceed(Mat A, Vec X, Vec Y);
PetscErrorCode FormResidual_Ceed(SNES snes, Vec X, Vec Y, void *ctx);
PetscErrorCode MatMult_Prolong(Mat A, Vec X, Vec Y);
PetscErrorCode MatMult_Restrict(Mat A, Vec X, Vec Y);
PetscErrorCode PCShellApply_BDDC(PC pc, Vec X, Vec Y);
PetscErrorCode PCShellSetup_BDDC(PC pc);
PetscErrorCode MatMult_BDDCElementSchur(UserBDDC user, Vec X, Vec Y);
PetscErrorCode FormResidual_BDDCElementSchur(SNES snes, Vec X, Vec Y,
    void *ctx);
PetscErrorCode MatMult_BDDCSchur(UserBDDC user, Vec X, Vec Y);
PetscErrorCode FormResidual_BDDCSchur(SNES snes, Vec X, Vec Y, void *ctx);
PetscErrorCode ComputeErrorMax(UserO user, CeedOperator op_error,
                               Vec X, CeedVector target, PetscReal *max_error);

#endif // matops_h
