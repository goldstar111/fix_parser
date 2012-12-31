/* @file   fix_error_priv.h
   @author Dmitry S. Melnikov, dmitryme@gmail.com
   @date   Created on: 07/30/2012 10:54:30 AM
*/

#ifndef FIX_PARSER_FIX_ERROR_PRIV_H
#define FIX_PARSER_FIX_ERROR_PRIV_H

#include <fix_types.h>

#include <stdint.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define ERROR_TXT_SIZE 1024

typedef struct FIXError
{
   FIXErrCode code;
   char       text[ERROR_TXT_SIZE];
} FIXError;

void fix_error_set_va(FIXError* error, FIXErrCode code, char const* text, va_list ap);
void fix_error_set(FIXError* error, FIXErrCode code, char const* text, ...);
void fix_error_reset(FIXError* error);

FIXError* fix_error_static_get();
void fix_error_static_set_va(FIXErrCode code, char const* text, va_list ap);
void fix_error_static_set(FIXErrCode code, char const* text, ...);
void fix_error_static_reset();

#ifdef __cplusplus
}
#endif

#endif // FIX_PARSER_FIX_ERROR_PRIV_H
