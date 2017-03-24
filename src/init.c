#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* FIXME:
   Check these declarations against the C/Fortran source code.
*/

/* .Call calls */
extern SEXP ndjson_internal_flatten(SEXP);
extern SEXP ndjson_internal_stream_in(SEXP);
extern SEXP ndjson_internal_validate(SEXP, SEXP);

static const R_CallMethodDef CallEntries[] = {
    {"ndjson_internal_flatten",   (DL_FUNC) &ndjson_internal_flatten,   1},
    {"ndjson_internal_stream_in", (DL_FUNC) &ndjson_internal_stream_in, 1},
    {"ndjson_internal_validate",  (DL_FUNC) &ndjson_internal_validate,  2},
    {NULL, NULL, 0}
};

void R_init_ndjson(DllInfo *dll)
{
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
