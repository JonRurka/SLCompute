
#include "../libUSL/USL.inc"
#include "complex.inc"

#ifndef IN_BUFFER
#define IN_BUFFER buffer_in
#endif

#ifndef IN_BUFFER_BIND
#define IN_BUFFER_BIND 0
#endif

#ifndef OUT_BUFFER
#define OUT_BUFFER buffer_out
#endif

#ifndef OUT_BUFFER_BIND
#define OUT_BUFFER_BIND 1
#endif

read_buffer_float(IN_BUFFER_BIND, IN_BUFFER)
readwrite_buffer_float(OUT_BUFFER_BIND, OUT_BUFFER)

slc_type read(uint index)
{
	return get_buffer_scalar(IN_BUFFER, index);
}

void write(uint index, slc_type val)
{
	set_buffer_scalar(OUT_BUFFER, index, val);
}
