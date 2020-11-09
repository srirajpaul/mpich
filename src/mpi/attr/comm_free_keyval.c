/*
 * Copyright (C) by Argonne National Laboratory
 *     See COPYRIGHT in top-level directory
 */

#include "mpiimpl.h"

/* -- Begin Profiling Symbol Block for routine MPI_Comm_free_keyval */
#if defined(HAVE_PRAGMA_WEAK)
#pragma weak MPI_Comm_free_keyval = PMPI_Comm_free_keyval
#elif defined(HAVE_PRAGMA_HP_SEC_DEF)
#pragma _HP_SECONDARY_DEF PMPI_Comm_free_keyval  MPI_Comm_free_keyval
#elif defined(HAVE_PRAGMA_CRI_DUP)
#pragma _CRI duplicate MPI_Comm_free_keyval as PMPI_Comm_free_keyval
#elif defined(HAVE_WEAK_ATTRIBUTE)
int MPI_Comm_free_keyval(int *comm_keyval) __attribute__ ((weak, alias("PMPI_Comm_free_keyval")));
#endif
/* -- End Profiling Symbol Block */

/* Define MPICH_MPI_FROM_PMPI if weak symbols are not supported to build
   the MPI routines */
#ifndef MPICH_MPI_FROM_PMPI
#undef MPI_Comm_free_keyval
#define MPI_Comm_free_keyval PMPI_Comm_free_keyval

#endif

/*@
   MPI_Comm_free_keyval - Frees an attribute key for communicators

Input Parameters:
. comm_keyval - Frees the integer key value (integer)

   Notes:
Key values are global (they can be used with any and all communicators)

.N ThreadSafe

.N Fortran

.N Errors
.N MPI_SUCCESS
.N MPI_ERR_ARG
.N MPI_ERR_PERM_KEY
@*/
int MPI_Comm_free_keyval(int *comm_keyval)
{
    int mpi_errno = MPI_SUCCESS;
    MPII_Keyval *keyval_ptr = NULL;
    MPIR_FUNC_TERSE_STATE_DECL(MPID_STATE_MPI_COMM_FREE_KEYVAL);

    MPIR_ERRTEST_INITIALIZED_ORDIE();

    MPID_THREAD_CS_ENTER(GLOBAL, MPIR_THREAD_GLOBAL_ALLFUNC_MUTEX);
    MPIR_FUNC_TERSE_ENTER(MPID_STATE_MPI_COMM_FREE_KEYVAL);

    /* Validate parameters, especially handles needing to be converted */
#ifdef HAVE_ERROR_CHECKING
    {
        MPID_BEGIN_ERROR_CHECKS;
        {
            MPIR_ERRTEST_ARGNULL(comm_keyval, "comm_keyval", mpi_errno);
            MPIR_ERRTEST_KEYVAL(*comm_keyval, MPIR_COMM, "communicator", mpi_errno);
            MPIR_ERRTEST_KEYVAL_PERM(*comm_keyval, mpi_errno);
        }
        MPID_END_ERROR_CHECKS;
    }
#endif

    /* Validate parameters and objects (post conversion) */
#ifdef HAVE_ERROR_CHECKING
    {
        MPID_BEGIN_ERROR_CHECKS;
        {
            /* Convert MPI object handles to object pointers */
            MPII_Keyval_get_ptr(*comm_keyval, keyval_ptr);

            MPII_Keyval_valid_ptr(keyval_ptr, mpi_errno);
            if (mpi_errno)
                goto fn_fail;
        }
        MPID_END_ERROR_CHECKS;
    }
#endif /* HAVE_ERROR_CHECKING */

    /* ... body of routine ...  */

    MPIR_free_keyval(keyval_ptr);
    *comm_keyval = MPI_KEYVAL_INVALID;

    /* ... end of body of routine ... */

#ifdef HAVE_ERROR_CHECKING
  fn_exit:
#endif
    MPIR_FUNC_TERSE_EXIT(MPID_STATE_MPI_COMM_FREE_KEYVAL);
    MPID_THREAD_CS_EXIT(GLOBAL, MPIR_THREAD_GLOBAL_ALLFUNC_MUTEX);
    return mpi_errno;

    /* --BEGIN ERROR HANDLING-- */
#ifdef HAVE_ERROR_CHECKING
  fn_fail:
    {
        mpi_errno =
            MPIR_Err_create_code(mpi_errno, MPIR_ERR_RECOVERABLE, __func__, __LINE__, MPI_ERR_OTHER,
                                 "**mpi_comm_free_keyval", "**mpi_comm_free_keyval %p",
                                 comm_keyval);
    }
    mpi_errno = MPIR_Err_return_comm(NULL, __func__, mpi_errno);
    goto fn_exit;
#endif
    /* --END ERROR HANDLING-- */
}
