#ifndef petsc_macros
#define petsc_macros

#if PETSC_VERSION_LT(3,14,0)
#  define DMAddBoundary(a,b,c,d,e,f,g,h,i,j,k,l,m,n) DMAddBoundary(a,b,c,e,h,i,j,k,f,g,m)
#elif PETSC_VERSION_LT(3,16,0)
#  define DMAddBoundary(a,b,c,d,e,f,g,h,i,j,k,l,m,n) DMAddBoundary(a,b,c,e,h,i,j,k,l,f,g,m)
#else
#  define DMAddBoundary(a,b,c,d,e,f,g,h,i,j,k,l,m,n) DMAddBoundary(a,b,c,d,f,g,h,i,j,k,l,m,n)
#endif

#endif
