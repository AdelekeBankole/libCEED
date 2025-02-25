#ifndef misc_h
#define misc_h

#include <ceed.h>
#include <petsc.h>
#include "../include/structs.h"

// -----------------------------------------------------------------------------
// Context setup
// -----------------------------------------------------------------------------
// Setup context data for Jacobian evaluation
PetscErrorCode SetupJacobianCtx(MPI_Comm comm, AppCtx app_ctx, DM dm, Vec V,
                                Vec V_loc, CeedData ceed_data, Ceed ceed,
                                CeedQFunctionContext ctx_phys,
                                CeedQFunctionContext ctx_phys_smoother,
                                UserMult jacobian_ctx);

// Setup context data for prolongation and restriction operators
PetscErrorCode SetupProlongRestrictCtx(MPI_Comm comm, AppCtx app_ctx, DM dm_c,
                                       DM dm_f, Vec V_f, Vec V_loc_c, Vec V_loc_f,
                                       CeedData ceed_data_c, CeedData ceed_data_f,
                                       Ceed ceed,
                                       UserMultProlongRestr prolong_restr_ctx);

// -----------------------------------------------------------------------------
// Jacobian setup
// -----------------------------------------------------------------------------
PetscErrorCode FormJacobian(SNES snes, Vec U, Mat J, Mat J_pre, void *ctx);

// -----------------------------------------------------------------------------
// Solution output
// -----------------------------------------------------------------------------
PetscErrorCode ViewSolution(MPI_Comm comm, AppCtx app_ctx, Vec U,
                            PetscInt increment, PetscScalar load_increment);

PetscErrorCode ViewDiagnosticQuantities(MPI_Comm comm, DM dm_U,
                                        UserMult user, AppCtx app_ctx, Vec U,
                                        CeedElemRestriction elem_restr_diagnostic);

// -----------------------------------------------------------------------------
// Regression testing
// -----------------------------------------------------------------------------
PetscErrorCode RegressionTests_solids(AppCtx app_ctx, PetscReal energy);

#endif // misc_h
