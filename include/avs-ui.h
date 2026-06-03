#ifndef AVS_UI_INCLUDED
#define AVS_UI_INCLUDED
#ifdef __cplusplus
extern "C" {
#endif

/**************************************/
/* Header Config                      */
/**************************************/
#include <stdint.h>
#include <stdbool.h>

#ifdef AVS_ENV_AVSOS_KERNEL
	#include <kernel_common.h>
	#include <vfs.h>
	#include <fs.h>
#elif AVS_ENV_LINUX
    #include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <sys/stat.h>
    #include <dirent.h>
    #include <unistd.h>
    #include <errno.h>
#else
	#error Unsupported AVS Environment
#endif

/**************************************/
/* System API Macro Config            */
/**************************************/

#ifdef AVS_ENV_AVSOS_KERNEL
	#define avs_malloc kmalloc
	#define avs_realloc krealloc
	#define avs_calloc kcalloc
	#define avs_free kfree
	#define avs_debugf debugf
#elif AVS_ENV_LINUX
	#define avs_malloc malloc
	#define avs_realloc realloc
	#define avs_calloc calloc
	#define avs_free free
	#define avs_debugf printf
#endif

/**************************************/
/* Functions                          */
/**************************************/

#ifdef __cplusplus
}
#endif
#endif