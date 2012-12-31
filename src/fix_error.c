/* @file   fix_error.c
   @author Dmitry S. Melnikov, dmitryme@gmail.com
   @date   Created on: 07/30/2012 10:26:54 AM
*/

#include "fix_utils.h"
#include "fix_error.h"
#include "fix_error_priv.h"
#include "fix_parser_priv.h"

#include <stdarg.h>
#include <stdio.h>

static FIXError error;


/*------------------------------------------------------------------------------------------------------------------------*/
FIX_PARSER_API FIXErrCode fix_error_get_code()
{
   return error.code;
}

/*------------------------------------------------------------------------------------------------------------------------*/
FIX_PARSER_API char const* fix_error_get_text()
{
   return error.text;
}
