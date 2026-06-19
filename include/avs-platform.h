#ifndef AVS_PLATFORM_INCLUDED
#define AVS_PLATFORM_INCLUDED
#ifdef __cplusplus
extern "C" {
#endif

/**************************************/
/* Header Config                      */
/**************************************/
#include <stdint.h>
#include <stdbool.h>

#define AVS_PFORM_AVSOS 0
#define AVS_PFORM_AVSOS_KERNEL 1
#define AVS_PFORM_LINUX 2

#ifdef AVS_ENV_AVSOS_KERNEL
	#include <kernel_common.h>
	#include <vfs.h>
	#include <fs.h>

	#define AVS_PLATFORM AVS_PFORM_AVSOS_KERNEL
#elif AVS_ENV_LINUX
    #include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <sys/stat.h>
    #include <dirent.h>
    #include <unistd.h>
    #include <errno.h>
	#include <ctype.h>

	#define AVS_PLATFORM AVS_PFORM_LINUX
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
    #define avs_strcpy kstrcpy
    #define avs_strlen kstrlen
	#define avs_memcpy kmemcpy
	#define avs_strcmp kstrcmp
	#define avs_isdigit kisdigit
#elif AVS_ENV_LINUX
	#define avs_malloc malloc
	#define avs_realloc realloc
	#define avs_calloc calloc
	#define avs_free free
	#define avs_debugf printf
    #define avs_strcpy strcpy
    #define avs_strlen strlen
	#define avs_memcpy memcpy
	#define avs_strcmp strcmp
	#define avs_isdigit isdigit
#endif

/**************************************/
/* Functions                          */
/**************************************/

typedef struct {
	uint8_t platform;

	uint16_t screen_width;
	uint16_t screen_height;

	uint32_t screen_pitch;
	uint32_t buffer_size;

	void *front_buffer;
	void *back_buffer;

	uint32_t *back_buffer32_t;

	void (*draw_front)(void);
} avs_platform;

/**************************************/
/* Functions                          */
/**************************************/

bool avs_platform_init( void );
bool avs_platform_init_avsos( avs_platform *avsp );
bool avs_platform_init_avsos_kernel( avs_platform *avsp );
bool avs_platform_init_linux( avs_platform *avsp );
avs_platform* get_avs_platform( void );

void avs_draw_rect( uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color );
void avs_platform_copy_b_to_f( void );

#ifdef __cplusplus
}
#endif
#endif