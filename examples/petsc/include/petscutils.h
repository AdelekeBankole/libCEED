#ifndef petscutils_h
#define petscutils_h

#include <ceed.h>
#include <petsc.h>
#include <petscdmplex.h>
#include <petscfe.h>

CeedMemType MemTypeP2C(PetscMemType mtype);
PetscErrorCode PetscFECreateByDegree(DM dm, PetscInt dim, PetscInt Nc,
                                     PetscBool isSimplex, PetscBool isContinuous,
                                     const char prefix[],
                                     PetscInt order, PetscFE *fem);
PetscErrorCode ProjectToUnitSphere(DM dm);
PetscErrorCode Kershaw(DM dm_orig, PetscScalar eps);
typedef PetscErrorCode (*BCFunction)(PetscInt dim, PetscReal time,
                                     const PetscReal x[], PetscInt num_comp_u,
                                     PetscScalar *u, void *ctx);
PetscErrorCode SetupDMByDegree(DM dm, PetscInt degree, PetscInt num_comp_u,
                               PetscInt topo_dim, PetscBool is_continuous,
                               PetscBool enforce_bc,  BCFunction bc_func);
PetscErrorCode SetupVertexDMFromDM(DM dm, DM dm_vertex, PetscInt num_comp_u,
                                   PetscBool is_continuous, PetscBool enforce_bc,
                                   BCFunction bc_func);
PetscErrorCode CreateRestrictionFromPlex(Ceed ceed, DM dm, CeedInt P,
    CeedInt topo_dim, CeedInt height, DMLabel domain_label, CeedInt value,
    CeedElemRestriction *elem_restr);

#endif // petscutils_h
