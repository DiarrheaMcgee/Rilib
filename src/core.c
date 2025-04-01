/*
*
*	Rilib 0.01-dev
*
*
* <Rilib technologies>
* This is free and unencumbered software released into the public domain.
* Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
* software, either in source code form or as a compiled binary, for any purpose,
* commercial or non-commercial, and by any means.
* In jurisdictions that recognize copyright laws, the author or authors of this
* software dedicate any and all copyright interest in the software to the public
* domain. We make this dedication for the benefit of the public at large and to
* the detriment of our heirs and successors. We intend this dedication to be an
* overt act of relinquishment in perpetuity of all present and future rights to
* this software under copyright law.
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
* ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
* WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


#ifndef RI_HEADER 
#define RILIB_SHARED
#include "rilib.h"
#endif

#ifndef RI_ALLOC
#include <malloc.h>
#define RI_ALLOC malloc
#define RI_FREE free
#define RI_REALLOC realloc
#endif

#define RSGL_color riColor
#define RSGL_area riArea

/* prviate API */
riWindow* ri_createWindowSrc(const char* name, riRect rect, riWindowFlags flags, riWindow* win);
void riWindow_closeSrc(riWindow* win);

/* RGFW */
void RSGL_draw(void);
void RSGL_updateSize(RSGL_area r);
void RSGL_free();
void RSGL_init(RSGL_area r, void* proc);
void RSGL_clear(RSGL_color color);

// defined in audio.c
i32 riAudio_init(void);
void riAudio_free(void);
/* */

void riWindow_draw(riWindow* win) {
    RSGL_draw();
    riWindow_swapBuffers(win);
}

void riWindow_clear(riWindow* win, riColor color) {
    riWindow_makeCurrent(win);

    RSGL_updateSize(RI_AREA(win->r.w, win->r.h));
    RSGL_clear(color);
}

riWindow* ri_createWindow(const char* name,  riRect rect,  riWindowFlags flags) {
    riWindow* out = RI_ALLOC(sizeof(riWindow));
    return ri_createWindowPtr(name, rect, flags, out); 
}

i32 windowCount = 0;

riWindow* ri_createWindowPtr(const char* name, riRect rect, riWindowFlags flags, riWindow* win) {    
    win = ri_createWindowSrc(name, rect, flags, win);
    
    if (windowCount == 0) {
        RSGL_init(RI_AREA(win->r.w, win->r.h), ri_getProcAddress);
        riAudio_init();
    }
    
    windowCount++;
    riWindow_makeCurrent(win);
    return win;
}

void riWindow_close(riWindow* win) {
    windowCount--;
    if (windowCount) {
        RSGL_free();
        riAudio_free();
    }

    riWindow_closeSrc(win);
}
