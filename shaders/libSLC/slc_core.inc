#ifndef _SLC_CORE_H_
#define _SLC_CORE_H_

#include "../libUSL/USL.inc"
#include "slc_lib_type.inc"
#include "slc_math.inc"
#include "slc_machine.inc"
#include "slc_sys.inc"


// Function entry point preset
#ifndef IMPLEMENT
#define IMPLEMENT(_exec_, _func_) \
void _func_##_main(uint idx) \
{                           \
	_exec_(_func_, idx)     \
}
#endif


#endif // __SLC_CORE_H__