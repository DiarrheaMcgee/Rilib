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



#ifndef RI_ALLOC
#include <malloc.h>
#define RI_ALLOC malloc
#define RI_FREE free
#define RI_REALLOC realloc
#endif

#ifndef RI_HEADER // for  clangd
#define RILIB_SHARED
#include "rilib.h"
#endif

#define RGFW_IMPLEMENTATION
#define RGFW_ALLOC RI_ALLOC
#define RGFW_FREE RI_FREE
#define RGFW_bool riBool
#define RGFW_point riPoint
#define RGFW_area riArea
#define RGFW_rect riRect
#include "deps/RGFW.h"

void riWindow_swapBuffers(riWindow* win) {
    RGFW_window_swapBuffers((RGFW_window*)win->src);
}


void riWindow_vsync(riWindow* win, riBool enable) {
    RGFW_window_swapInterval((RGFW_window*)win->src, enable);
}

riMonitor* ri_getMonitors(size_t* len) {
    return (riMonitor*)RGFW_getMonitors(len);
}

riMonitor ri_getPrimaryMonitor(void) {
    RGFW_monitor mon = RGFW_getPrimaryMonitor();
    riMonitor ri_mon = *(riMonitor*)&mon;
    return ri_mon;
}

riBool riMonitor_requestMode(riMonitor mon, riMonitorMode mode, ri_modeRequest request) {
    RGFW_monitor rgfw_mon = *(RGFW_monitor*)&mon;
    RGFW_monitorMode rgfw_mode = *(RGFW_monitorMode*)&mode;
    RGFW_modeRequest rgfw_request = *(RGFW_modeRequest*)&request;


    return RGFW_monitor_requestMode(rgfw_mon, rgfw_mode, rgfw_request);
}

riBool riMonitor_ModeCompare(riMonitorMode mon, riMonitorMode mon2, ri_modeRequest request) {
    RGFW_monitorMode rgfw_mon = *(RGFW_monitorMode*)&mon;
    RGFW_monitorMode rgfw_mon2 = *(RGFW_monitorMode*)&mon2;

    return RGFW_monitorModeCompare(rgfw_mon, rgfw_mon2, request);
}

ri_mouse* ri_loadMouse(u8* icon, riArea a, i32 channels) {
    return RGFW_loadMouse(icon, a, channels);
}

void ri_freeMouse(ri_mouse* mouse) {
    RGFW_freeMouse(mouse);
}

riBool riMonitor_scaleToWindow(riMonitor mon, riWindow* win) {
    RGFW_monitor rgfw_mon = *(RGFW_monitor*)&mon;
    return RGFW_monitor_scaleToWindow(rgfw_mon, (RGFW_window*)win->src);
}

riWindow* ri_createWindowSrc(const char* name, riRect rect, riWindowFlags flags, riWindow* win) {    
    win->src = RGFW_createWindow(name, rect, flags);
    win->r = ((RGFW_window*)(RGFW_window*)win->src)->r;
    return win;
}

void riWindow_closeSrc(riWindow* win) {
    RGFW_window_close((RGFW_window*)win->src);
}

void riWindow_setShouldClose(riWindow* win, riBool shouldClose) {
    RGFW_window_setShouldClose((RGFW_window*)win->src, shouldClose);
}

RGFW_bool riWindow_shouldClose(riWindow* win) {
    return RGFW_window_shouldClose((RGFW_window*)win->src);
}

riArea ri_getScreenSize(void) {
    return RGFW_getScreenSize();
}


riEvent* riWindow_checkEvent(riWindow* win) {
    RGFW_event* ev = RGFW_window_checkEvent((RGFW_window*)win->src);
    if (ev == NULL) return NULL;
    
    win->event = *(riEvent*)&((RGFW_window*)((RGFW_window*)win->src))->event;
    win->r = ((RGFW_window*)((RGFW_window*)win->src))->r;

    return &win->event;
}

void riWindow_eventWait(riWindow* win, u32 waitMS) {
    RGFW_window_eventWait((RGFW_window*)win->src, waitMS);
}

riPoint ri_getGlobalMousePoint(void) {
    return RGFW_getGlobalMousePoint();
}

riPoint riWindow_getMousePoint(riWindow* win) {
    return RGFW_window_getMousePoint((RGFW_window*)win->src);
}

void riWindow_showMouse(riWindow* win, riBool show) {
    RGFW_window_showMouse((RGFW_window*)win->src, show);
}

riBool riWindow_mouseHidden(riWindow* win) {
    return RGFW_window_mouseHidden((RGFW_window*)win->src);
}

riBool riWindow_isFullscreen(riWindow* win) {
    return RGFW_window_isFullscreen((RGFW_window*)win->src);
}

riBool riWindow_isHidden(riWindow* win) {
    return RGFW_window_isHidden((RGFW_window*)win->src);
}

riBool riWindow_isMinimized(riWindow* win) {
    return RGFW_window_isMinimized((RGFW_window*)win->src);
}

riBool riWindow_isMaximized(riWindow* win) {
    return RGFW_window_isMaximized((RGFW_window*)win->src);
}

riBool riWindow_isFloating(riWindow* win) {
    return RGFW_window_isFloating((RGFW_window*)win->src);
}

riMonitor riWindow_getMonitor(riWindow* win) {
    RGFW_monitor mon = RGFW_window_getMonitor((RGFW_window*)win->src);
    riMonitor riMon = *(riMonitor*)&mon;
    return riMon;
}


riBool ri_isPressed(riWindow* win, ri_key key) {
    return RGFW_isPressed((RGFW_window*)win->src, key);
}

riBool ri_wasPressed(riWindow* win, ri_key key) {
    return RGFW_wasPressed((RGFW_window*)win->src, key);
}

riBool ri_isHeld(riWindow* win, ri_key key) {
    return RGFW_isHeld((RGFW_window*)win->src, key);
}

riBool ri_isReleased(riWindow* win, ri_key key) {
    return RGFW_isReleased((RGFW_window*)win->src, key);
}

riBool ri_isClicked(riWindow* win, ri_key key) {
    return RGFW_isClicked((RGFW_window*)win->src, key);
}

riBool ri_isMousePressed(riWindow* win, ri_mouseButton button) {
    return RGFW_isMousePressed((RGFW_window*)win->src, button);
}

riBool ri_isMouseHeld(riWindow* win, ri_mouseButton button) {
    return RGFW_isMouseHeld((RGFW_window*)win->src, button);
}

riBool ri_isMouseReleased(riWindow* win, ri_mouseButton button) {
    return RGFW_isMouseReleased((RGFW_window*)win->src, button);
}

riBool ri_wasMousePressed(riWindow* win, ri_mouseButton button) {
    return RGFW_wasMousePressed((RGFW_window*)win->src, button);
}



const char* ri_readClipboard(size_t* size) {
    return RGFW_readClipboard(size);
}

ri_ssize_t ri_readClipboardPtr(char* str, size_t strCapacity) {
    return RGFW_readClipboardPtr(str, strCapacity);
}

void ri_writeClipboard(const char* text, u32 textLen) {
    RGFW_writeClipboard(text, textLen);
}

size_t ri_getGamepadCount(riWindow* win) {
    return RGFW_getGamepadCount((RGFW_window*)win->src);
}

ri_gamepadType ri_getGamepadType(riWindow* win, u16 controller) {
    return RGFW_getGamepadType((RGFW_window*)win->src, controller);
}

double ri_getTime(void) {
    return RGFW_getTime();
}

u64 ri_getTimeNS(void) {
    return RGFW_getTimeNS();
}

void ri_sleep(u64 milisecond) {
    RGFW_sleep(milisecond);
}

void ri_setTime(double time) {
    RGFW_setTime(time);
}

u64 ri_getTimerValue(void) {
    return RGFW_getTimerValue();
}

u64 ri_getTimerFreq(void) {
    return RGFW_getTimerFreq();
}


u32 ri_checkFPS(double startTime, u32 frameCount, u32 fpsCap) {
    return RGFW_checkFPS(startTime, frameCount, fpsCap);
}

ri_proc ri_getProcAddress(const char* procname) {
    return RGFW_getProcAddress(procname);
}

void ri_setGLHint(ri_glHints hint, i32 value) {
    RGFW_setGLHint(hint, value);
}

void riWindow_makeCurrent(riWindow* win) {
    RGFW_window_makeCurrent((RGFW_window*)win->src);
}

const char* ri_getGamepadName(riWindow* win, u16 controller) {
    return RGFW_getGamepadName((RGFW_window*)win->src, controller);
}

riPoint ri_getGamepadAxis(riWindow* win, u16 controller, u16 whichAxis) {
    return RGFW_getGamepadAxis((RGFW_window*)win->src, controller, whichAxis);
}

u32 ri_wasPressedGamepad(riWindow* win, u8 controller, ri_gamepadCodes button) {
    return RGFW_wasPressedGamepad((RGFW_window*)win->src, controller, button);
}

u32 ri_isHeldGamepad(riWindow* win, u8 controller, ri_gamepadCodes button) {
    return RGFW_isHeldGamepad((RGFW_window*)win->src, controller, button);
}

u32 ri_isReleasedGamepad(riWindow* win, u8 controller, ri_gamepadCodes button) {
    return RGFW_isReleasedGamepad((RGFW_window*)win->src, controller, button);
}

u32 ri_isPressedGamepad(riWindow* win, u8 controller, ri_gamepadCodes button) {
    return RGFW_isPressedGamepad((RGFW_window*)win->src, controller, button);
}

void riWindow_scaleToMonitor(riWindow* win) {
    RGFW_window_scaleToMonitor((RGFW_window*)win->src);
}

void riWindow_moveMouse(riWindow* win, riPoint v) {
    RGFW_window_moveMouse((RGFW_window*)win->src, v);
}

void riWindow_show(riWindow* win) {
    RGFW_window_show((RGFW_window*)win->src);
}

void riWindow_hide(riWindow* win) {
    RGFW_window_hide((RGFW_window*)win->src);
}

void riWindow_mouseUnhold(riWindow* win) {
    RGFW_window_mouseUnhold((RGFW_window*)win->src);
}

void riWindow_mouseHold(riWindow* win, riArea area) {
    RGFW_window_mouseHold((RGFW_window*)win->src, area);
}

riBool riWindow_setMouseDefault(riWindow* win) {
    return RGFW_window_setMouseDefault((RGFW_window*)win->src);
}

riBool riWindow_setMouseStandard(riWindow* win, u8 mouse) {
    return RGFW_window_setMouseStandard((RGFW_window*)win->src, mouse);
}

void riWindow_setMouse(riWindow* win, ri_mouse* mouse) {
    RGFW_window_setMouse((RGFW_window*)win->src, mouse);
}

riBool riWindow_setIconEx(riWindow* win, u8* icon, riArea a, i32 channels, u8 type) {
    return RGFW_window_setIconEx((RGFW_window*)win->src, icon, a, channels, type);
}

riBool riWindow_setIcon(riWindow* win, u8* icon, riArea a, i32 channels) {
    return RGFW_window_setIcon((RGFW_window*)win->src, icon, a, channels);
}

void riWindow_setName(riWindow* win, const char* name) {
    RGFW_window_setName((RGFW_window*)win->src, name);
}

void riWindow_setMousePassthrough(riWindow* win, riBool passthrough) {
    RGFW_window_setMousePassthrough((RGFW_window*)win->src, passthrough);
}

riBool riWindow_allowsDND(riWindow* win) {
    return RGFW_window_allowsDND((RGFW_window*)win->src);
}

void riWindow_setDND(riWindow* win, riBool allow) {
    RGFW_window_setDND((RGFW_window*)win->src, allow);
}

riBool riWindow_borderless(riWindow* win) {
    return RGFW_window_borderless((RGFW_window*)win->src);
}

void riWindow_setBorder(riWindow* win, riBool border) {
    RGFW_window_setBorder((RGFW_window*)win->src, border);
}

void riWindow_setOpacity(riWindow* win, u8 opacity) {
    RGFW_window_setOpacity((RGFW_window*)win->src, opacity);
}

void riWindow_setFloating(riWindow* win, riBool floating) {
    RGFW_window_setFloating((RGFW_window*)win->src, floating);
}

void riWindow_restore(riWindow* win) {
    RGFW_window_restore((RGFW_window*)win->src);
}

void riWindow_minimize(riWindow* win) {
    RGFW_window_minimize((RGFW_window*)win->src);
}

void riWindow_center(riWindow* win) {
    RGFW_window_center((RGFW_window*)win->src);
}

void riWindow_setFullscreen(riWindow* win, riBool fullscreen) {
    RGFW_window_setFullscreen((RGFW_window*)win->src, fullscreen);
}

void riWindow_maximize(riWindow* win) {
    RGFW_window_maximize((RGFW_window*)win->src);
}

void riWindow_raise(riWindow* win) {
    RGFW_window_raise((RGFW_window*)win->src);
}

riBool riWindow_isInFocus(riWindow* win) {
    return RGFW_window_isInFocus((RGFW_window*)win->src);
}

void riWindow_focus(riWindow* win) {
    RGFW_window_focus((RGFW_window*)win->src);
}

void riWindow_setMaxSize(riWindow* win, riArea a) {
    RGFW_window_setMaxSize((RGFW_window*)win->src, a);
}

void riWindow_setMinSize(riWindow* win, riArea a) {
    RGFW_window_setMinSize((RGFW_window*)win->src, a);
}

void riWindow_setAspectRatio(riWindow* win, riArea a) {
    RGFW_window_setAspectRatio((RGFW_window*)win->src, a);
}

void riWindow_resize(riWindow* win, riArea size) {
    RGFW_window_resize((RGFW_window*)win->src, size);
}

void riWindow_moveToMonitor(riWindow* win, riMonitor m) {
    RGFW_window_moveToMonitor((RGFW_window*)win->src, *(RGFW_monitor*)(&m));
}

void riWindow_move(riWindow* win, riPoint v) {
    RGFW_window_move((RGFW_window*)win->src, v);
}

void ri_stopCheckEvents(void) {
    RGFW_stopCheckEvents();
}

void riWindow_setFlags(riWindow* win, riWindowFlags flags) {
    RGFW_window_setFlags((RGFW_window*)win->src, flags);
}
