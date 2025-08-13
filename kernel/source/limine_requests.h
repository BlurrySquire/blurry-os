#ifndef _H_LIMINE_REQUESTS
#define _H_LIMINE_REQUESTS

#ifdef __cplusplus
extern "C" {
#endif

#include "limine.h"

extern volatile struct limine_executable_cmdline_request cmdline_request;
extern volatile struct limine_framebuffer_request framebuffer_request;
extern volatile struct limine_memmap_request memmap_request;
extern volatile struct limine_hhdm_request hhdm_request;

#ifdef __cplusplus
}
#endif

#endif