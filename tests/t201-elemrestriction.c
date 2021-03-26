/// @file
/// Test creation, use, and destruction of a strided element restriction
/// \test Test creation, use, and destruction of a strided element restriction
#include <ceed.h>
#include <ceed/backend.h>

int main(int argc, char **argv) {
  Ceed ceed;
  CeedVector x, y;
  CeedInt ne = 3;
  CeedScalar a[ne*2];
  const CeedScalar *yy;
  CeedInt strides[3] = {1, 2, 2};
  CeedInt layout[3];
  CeedElemRestriction r;

  CeedInit(argv[1], &ceed);

  CeedVectorCreate(ceed, ne*2, &x);
  for (CeedInt i=0; i<ne*2; i++)
    a[i] = 10 + i;
  CeedVectorSetArray(x, CEED_MEM_HOST, CEED_USE_POINTER, a);

  CeedElemRestrictionCreateStrided(ceed, ne, 2, 1, ne*2, strides, &r);
  CeedVectorCreate(ceed, ne*2, &y);
  CeedVectorSetValue(y, 0); // Allocates array
  CeedElemRestrictionApply(r, CEED_NOTRANSPOSE, x, y, CEED_REQUEST_IMMEDIATE);

  CeedVectorGetArrayRead(y, CEED_MEM_HOST, &yy);
  CeedElemRestrictionGetELayout(r, &layout);
  for (CeedInt i=0; i<2; i++)      // Node
    for (CeedInt j=0; j<1; j++)    // Component
      for (CeedInt k=0; k<ne; k++) // Element
        if (yy[i*layout[0] + j*layout[1] + k*layout[2]] !=
            a[i*strides[0] + j*strides[1] + k*strides[2]])
          // LCOV_EXCL_START
          printf("Error in restricted array y[%d][%d][%d] = %f",
                 i, j, k, (double)yy[i*strides[0] + j*strides[1] + j*strides[2]]);
  // LCOV_EXCL_STOP
  CeedVectorRestoreArrayRead(y, &yy);

  CeedVectorDestroy(&x);
  CeedVectorDestroy(&y);
  CeedElemRestrictionDestroy(&r);
  CeedDestroy(&ceed);
  return 0;
}
