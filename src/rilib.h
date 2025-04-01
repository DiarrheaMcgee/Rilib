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

#if _MSC_VER
	#pragma comment(lib, "gdi32")
	#pragma comment(lib, "shell32")
	#pragma comment(lib, "opengl32")
	#pragma comment(lib, "winmm")
	#pragma comment(lib, "user32")
#endif

#ifndef RIAPI
#if defined(_WIN32)
        #if defined(__TINYC__)
            #define __declspec(x) __attribute__((x))
        #endif
        #if defined(RILIB_SHARED)
            #define RIAPI __declspec(dllexport)
        #elif defined(RILIB_USE_SHARED)
            #define RIAPI __declspec(dllimport)
        #endif
    #else
        #if defined(RILIB_EXPORT)
            #define RIAPI __attribute__((visibility("default")))
        #endif
    #endif
#endif

#ifndef RIAPI
	#define RIAPI 
#endif

#ifndef RI_ENUM
	#define RI_ENUM(type, name) type name; enum
#endif


#if defined(__cplusplus)
	extern "C" {
#endif

	/* makes sure the header file part is only defined once by default */
#ifndef RI_HEADER

#define RI_HEADER

#include <stddef.h>
#if !defined(u8)
	#ifdef RI_USE_INT /* optional for any system that might not have stdint.h */
		typedef unsigned char 	u8;
		typedef signed char		i8;
		typedef unsigned short  u16;
		typedef signed short 	i16;
		typedef unsigned long int 	u32;
		typedef signed long int		i32;
		typedef unsigned long long	u64;
		typedef signed long long		i64;
	#else /* use stdint standard types instead of c ""standard"" types */
		#include <stdint.h>

		typedef uint8_t     u8;
		typedef int8_t      i8;
		typedef uint16_t   u16;
		typedef int16_t    i16;
		typedef uint32_t   u32;
		typedef int32_t    i32;
		typedef uint64_t   u64;
		typedef int64_t    i64;
	#endif
	#define u8 u8
#endif

#if !defined(riBool) /* rilib bool type */
	typedef u8 riBool;
	#define riBool u8
#endif

#define RI_TRUE (riBool)1
#define RI_FALSE (riBool)0
#define RI_BOOL(x) (Ri_bool)((x) ? RI_TRUE : RI_FALSE) /* force an value to be 0 or 1 */

#define ri_key u8

/* 
*******
ri_[shape]
*******
*/

/*! basic vector type, if there's not already a point/vector type of choice */
#ifndef riPoint
	typedef struct { i32 x, y; } riPoint;
#endif

/*! basic rect type, if there's not already a rect type of choice */
#ifndef riRect
	typedef struct { i32 x, y, w, h; } riRect;
#endif

/*! basic area type, if there's not already a area type of choice */
#ifndef riArea
	typedef struct { u32 w, h; } riArea;
#endif

#if defined(__cplusplus) && !defined(__APPLE__)
#define RI_POINT(x, y) {(i32)x, (i32)y}
#define RI_RECT(x, y, w, h) {(i32)x, (i32)y, (i32)w, (i32)h}
#define RI_AREA(w, h) {(u32)w, (u32)h}
#else
#define RI_POINT(x, y) (riPoint){(i32)(x), (i32)(y)}
#define RI_RECT(x, y, w, h) (riRect){(i32)(x), (i32)(y), (i32)(w), (i32)(h)}
#define RI_AREA(w, h) (riArea){(u32)(w), (u32)(h)}
#endif

typedef struct riRectF { float x, y, w, h; } riRectF;
#define RI_RECTF(x, y, w, h) (riRectF){(float)x, (float)y, (float)w, (float)h}

typedef struct riPointF { float x, y; } riPointF;
#define RI_POINTF(x, y) (riPointF){x, y}

typedef struct riPoint3D {
    i32 x, y, z;
} riPoint3D;

typedef struct riPoint3DF { float x, y, z; } riPoint3DF;

#define RI_POINT3D(x, y, z) (riPoint3D){(i32)x, (i32)y, (i32)z}
#define RI_POINT3DF(x, y, z) (riPoint3DF){(float)x, (float)y, (float)z}

typedef struct riAreaF { float w, h;} riAreaF;
#define RI_AREAF(w, h) (riAreaF){(float)w, (float)h}

typedef struct riCircle {
    i32 x, y, d;
} riCircle;
#define riCircle(x, y, d) (riCircle){(i32)x, (i32)y, (i32)d}

typedef struct riCircleF { float x, y, d; } riCircleF;
#define riCircleF(x, y, d) (riCircleF){(float)x, (float)y, (float)d}

typedef struct riTriangle {
    riPoint p1, p2, p3;
} riTriangle;
#define RI_TRIANGLE(p1, p2, p3) (ri_triangle){p1, p2, p3}

typedef struct riTriangleF { riPointF p1, p2, p3; } riTriangleF;
#define RI_TRIANGLEF(p1, p2, p3) (riTriangleF){p1, p2, p3}

#define RI_createTriangle(x1, y1, x2, y2, x3, y3) (riTriangle){{x1, y1}, {x2, y2}, {x3, y3}}
#define RI_createTriangleF(x1, y1, x2, y2, x3, y3) (riTriangleF){{x1, y1}, {x2, y2}, {x3, y3}}

typedef struct riCube {
    i32 x, y, z, w, h, l;
} riCube;
#define RI_CUBE(x, y, z, w, h, l) (ri_cube){x, y, z, w, h, l}

typedef struct riCubeF { float x, y, z, w, h, l; } riCubeF;
#define RI_CUBEF(x, y, z, w, h, l) (riCubeF){x, y, z, w, h, l}

/* drawing functions */
#ifndef riTexture
#define riTexture size_t
#endif
typedef struct riImage { riTexture tex; riArea srcSize; char file[255]; } riImage;

/* 
the color stucture is in 
ABGR by default for performance reasons 
(converting color to hex for example)
*/
typedef struct riColor {
    u8 a, b, g, r;
} riColor;

#define RI_RGBA(r, g, b, a) ((riColor){(u8)(a), (u8)(b), (u8)(g), (u8)(r)})
#define RI_RGB(r, g, b) ((riColor){255, (u8)(b), (u8)(g), (u8)(r)})

#define riColor_TO_HEX(color) ((u32)(color) & 0xFFFFFF00)
#define RI_RGB_TO_HEX(r, g, b, a) (riColor_TO_HEX(ri_RGBA(r, g, b, a)))
#define RI_RGBA_TO_HEX(r, g, b) (riColor_TO_HEX(ri_RGB(r, g, b, a)))



typedef RI_ENUM(u8, riEventType) {
	/*! event codes */
	riEventNone = 0, /*!< no event has been sent */
 	ri_keyPressed, /* a key has been pressed */
	ri_keyReleased, /*!< a key has been released */
	/*! key event note
		the code of the key pressed is stored in
		riEvent.key
		!!Keycodes defined at the bottom of the RI_HEADER part of this file!!

		while a string version is stored in
		riEvent.KeyString

		riEvent.keyMod holds the current keyMod
		this means if CapsLock, NumLock are active or not
	*/
	ri_mouseButtonPressed, /*!< a mouse button has been pressed (left,middle,right) */
	ri_mouseButtonReleased, /*!< a mouse button has been released (left,middle,right) */
	ri_mousePosChanged, /*!< the position of the mouse has been changed */
	/*! mouse event note
		the x and y of the mouse can be found in the vector, riEvent.point

		riEvent.button holds which mouse button was pressed
	*/
	ri_gamepadConnected, /*!< a gamepad was connected */
	ri_gamepadDisconnected, /*!< a gamepad was disconnected */
	ri_gamepadButtonPressed, /*!< a gamepad button was pressed */
	ri_gamepadButtonReleased, /*!< a gamepad button was released */
	ri_gamepadAxisMove, /*!< an axis of a gamepad was moved */
	/*! gamepad event note
		riEvent.gamepad holds which gamepad was altered, if any
		riEvent.button holds which gamepad button was pressed

		riEvent.axis holds the data of all the axises
		riEvent.axisesCount says how many axises there are
	*/
	riWindowMoved, /*!< the window was moved (by the user) */
	riWindowResized, /*!< the window was resized (by the user), [on WASM this means the browser was resized] */
	ri_focusIn, /*!< window is in focus now */
	ri_focusOut, /*!< window is out of focus now */
	ri_mouseEnter, /* mouse entered the window */
	ri_mouseLeave, /* mouse left the window */
	riWindowRefresh, /* The window content needs to be refreshed */

	/* attribs change event note
		The event data is sent straight to the window structure
		with win->r.x, win->r.y, win->r.w and win->r.h
	*/
	ri_quit, /*!< the user clicked the quit button */
	ri_DND, /*!< a file has been dropped into the window */
	ri_DNDInit, /*!< the start of a dnd event, when the place where the file drop is known */
	/* dnd data note
		The x and y coords of the drop are stored in the vector riEvent.point

		riEvent.droppedFilesCount holds how many files were dropped

		This is also the size of the array which stores all the dropped file string,
		riEvent.droppedFiles
	*/
	riWindowMaximized, /*!< the window was maximized */
	riWindowMinimized, /*!< the window was minimized */
	riWindowRestored, /*!< the window was restored */
	ri_scaleUpdated, /*!< content scale factor changed */
};

/*! mouse button codes (riEvent.button) */
typedef RI_ENUM(u8, ri_mouseButton) {
	ri_mouseLeft = 0, /*!< left mouse button is pressed */
	ri_mouseMiddle, /*!< mouse-wheel-button is pressed */
	ri_mouseRight, /*!< right mouse button is pressed */
	ri_mouseScrollUp, /*!< mouse wheel is scrolling up */
	ri_mouseScrollDown, /*!< mouse wheel is scrolling down */
	ri_mouseMisc1, ri_mouseMisc2, ri_mouseMisc3, ri_mouseMisc4, ri_mouseMisc5,
	ri_mouseFinal
};

#ifndef RI_MAX_PATH
#define RI_MAX_PATH 260 /* max length of a path (for dnd) */
#endif
#ifndef RI_MAX_DROPS
#define RI_MAX_DROPS 260 /* max items you can drop at once */
#endif

#define RI_BIT(x) (1L << x)

/* for riEvent.lockstate */
typedef RI_ENUM(u8, ri_keymod) {
	ri_modCapsLock = RI_BIT(0),
	ri_modNumLock  = RI_BIT(1),
	ri_modControl  = RI_BIT(2),
	ri_modAlt = RI_BIT(3),
	ri_modShift  = RI_BIT(4),
	ri_modSuper = RI_BIT(5),
	ri_modScrollLock = RI_BIT(6)
};

/*! gamepad button codes (based on xbox/playstation), you may need to change these values per controller */
typedef RI_ENUM(u8, ri_gamepadCodes) {
	ri_gamepadNone = 0, /*!< or PS X button */
	ri_gamepadA, /*!< or PS X button */
	ri_gamepadB, /*!< or PS circle button */
	ri_gamepadY, /*!< or PS triangle button */
	ri_gamepadX, /*!< or PS square button */
	ri_gamepadStart, /*!< start button */
	ri_gamepadSelect, /*!< select button */
	ri_gamepadHome, /*!< home button */
	ri_gamepadUp, /*!< dpad up */
	ri_gamepadDown, /*!< dpad down */
	ri_gamepadLeft, /*!< dpad left */
	ri_gamepadRight, /*!< dpad right */
	ri_gamepadL1, /*!< left bump */
	ri_gamepadL2, /*!< left trigger */
	ri_gamepadR1, /*!< right bumper */
	ri_gamepadR2, /*!< right trigger */
	ri_gamepadL3,  /* left thumb stick */
	ri_gamepadR3, /*!< right thumb stick */
	ri_gamepadFinal
};

#ifndef ri_NO_MONITOR
	/* monitor mode data | can be changed by the user (with functions)*/
	typedef struct riMonitorMode {
		riArea area; /*!< monitor workarea size */
		u32 refreshRate; /*!< monitor refresh rate */
		u8 red, blue, green; 
	} riMonitorMode;

	/*! structure for monitor data */
	typedef struct riMonitor {
		i32 x, y; /*!< x - y of the monitor workarea */
		char name[128]; /*!< monitor name */
		float scaleX, scaleY; /*!< monitor content scale */
		float pixelRatio; /*!< pixel ratio for monitor (1.0 for regular, 2.0 for hiDPI)  */
		float physW, physH; /*!< monitor physical size in inches */

		riMonitorMode mode;
	} riMonitor;

	/*! get an array of all the monitors (max 6) */
	RIAPI riMonitor* ri_getMonitors(size_t* len);
	/*! get the primary monitor */
	RIAPI riMonitor ri_getPrimaryMonitor(void);

	typedef RI_ENUM(u8, ri_modeRequest) {
		riMonitorScale = RI_BIT(0), /*!< scale the monitor size */
		riMonitorRefresh = RI_BIT(1), /*!< change the refresh rate */
		riMonitorRGB = RI_BIT(2), /*!< change the monitor RGB bits size */
		riMonitorAll = riMonitorScale | riMonitorRefresh | riMonitorRGB
	};

	/*! request a specific mode */
	RIAPI riBool riMonitor_requestMode(riMonitor mon, riMonitorMode mode, ri_modeRequest request);
	/*! check if 2 monitor modes are the same */
	RIAPI riBool riMonitor_modeCompare(riMonitorMode mon, riMonitorMode mon2, ri_modeRequest request);
#endif

/* rilib mouse loading */
typedef void ri_mouse;

/*!< loads mouse icon from bitmap (similar to riWindow_setIcon). Icon NOT resized by default */
RIAPI ri_mouse* ri_loadMouse(u8* icon, riArea a, i32 channels);
/*!< frees ri_mouse data */
RIAPI void ri_freeMouse(ri_mouse* mouse);

/* NOTE: some parts of the data can represent different things based on the event (read comments in riEvent struct) */
/*! Event structure for checking/getting events */
typedef struct riEvent {
	riEventType type; /*!< which event has been sent?*/
	riPoint point; /*!< mouse x, y of event (or drop point) */
	riPoint vector; /*!< raw mouse movement */
	float scaleX, scaleY; /*!< DPI scaling */

	ri_key key; /*!< the physical key of the event, refers to where key is physically !!Keycodes defined at the bottom of the RI_HEADER part of this file!! */
	u8 keyChar; /*!< mapped key char of the event */

	riBool repeat; /*!< key press event repeated (the key is being held) */
	ri_keymod keyMod;

	u8 button; /* !< which mouse (or gamepad) button was pressed */
	double scroll; /*!< the raw mouse scroll value */

	u16 gamepad; /*! which gamepad this event applies to (if applicable to any) */
	u8 axisesCount; /*!< number of axises */

	u8 whichAxis; /* which axis was effected */
	riPoint axis[4]; /*!< x, y of axises (-100 to 100) */

	/*! drag and drop data */
	/* 260 max paths with a max length of 260 */
	char** droppedFiles; /*!< dropped files */
	size_t droppedFilesCount; /*!< house many files were dropped */

	void* _win; /*!< the window this event applies too (for event queue events) */
} riEvent;

/*! Optional arguments for making a windows */
typedef RI_ENUM(u32, riWindowFlags) {
	riWindowNoInitAPI = RI_BIT(0), /* do NOT init an API (mostly for bindings. you should use `#define RI_NO_API` in C) */
	riWindowNoBorder = RI_BIT(1), /*!< the window doesn't have a border */
	riWindowNoResize = RI_BIT(2), /*!< the window cannot be resized by the user */
	riWindowAllowDND = RI_BIT(3), /*!< the window supports drag and drop */
	riWindowHideMouse = RI_BIT(4), /*! the window should hide the mouse (can be toggled later on using `riWindow_mouseShow`) */
	riWindowFullscreen = RI_BIT(5), /*!< the window is fullscreen by default */
	riWindowTransparent = RI_BIT(6), /*!< the window is transparent (only properly works on X11 and MacOS, although it's meant for for windows) */
	riWindowCenter = RI_BIT(7), /*! center the window on the screen */
	riWindowOpenglSoftware = RI_BIT(8), /*! use OpenGL software rendering */
	riWindowCocoaCHDirToRes = RI_BIT(9), /*! (cocoa only), change directory to resource folder */
	riWindowScaleToMonitor = RI_BIT(10), /*! scale the window to the screen */
	riWindowHide = RI_BIT(11), /*! the window is hidden */
	riWindowMaximize = RI_BIT(12),
	riWindowCenterCursor = RI_BIT(13),
	riWindowFloating = RI_BIT(14), /*!< create a floating window */
	riWindowFreeOnClose = RI_BIT(15), /*!< free (riWindow_close) the riWindow struct when the window is closed (by the end user) */
	riWindowFocusOnShow = RI_BIT(16), /*!< focus the window when it's shown */
	riWindowMinimize =RI_BIT(17), /*!< focus the window when it's shown */
	riWindowFocus = RI_BIT(18), /*!< if the window is in focus */
	riWindowedFullscreen = riWindowNoBorder | riWindowMaximize,
};

typedef struct riWindow {
	void* src;
	void* userPtr; /* ptr for usr data */
	riEvent event; /*!< current event */
	riRect r; /*!< the x, y, w and h of the struct */
} riWindow; /*!< window structure for managing the window */

typedef riWindow* riWindowHandle;

/*! scale monitor to window size */
RIAPI riBool riMonitor_scaleToWindow(riMonitor mon, riWindow* win);

/** * @defgroup Window_management
* @{ */

/* NOTE: (windows) if the executable has an icon resource named ri_ICON, it will be set as the initial icon for the window */

RIAPI riWindow* ri_createWindow(
	const char* name, /* name of the window */
	riRect rect, /* rect of window */
	riWindowFlags flags /* extra arguments ((u32)0 means no flags used)*/
); /*!< function to create a window and struct */

RIAPI riWindow* ri_createWindowPtr(
	const char* name, /* name of the window */
	riRect rect, /* rect of window */
	riWindowFlags flags, /* extra arguments (NULL / (u32)0 means no flags used) */
	riWindow* win /* ptr to the window struct you want to use */
); /*!< function to create a window (without allocating a window struct) */

/*! set the window flags (will undo flags if they don't match the old ones) */
RIAPI void riWindow_setFlags(riWindow* win, riWindowFlags);

/*! get the size of the screen to an area struct */
RIAPI riArea ri_getScreenSize(void);

/*!
	for riWindow_eventWait and riWindow_checkEvents
	waitMS -> Allows the function to keep checking for events even after `riWindow_checkEvent == NULL`
			  if waitMS == 0, the loop will not wait for events
			  if waitMS > 0, the loop will wait that many miliseconds after there are no more events until it returns
			  if waitMS == -1 or waitMS == the max size of an unsigned 32-bit int, the loop will not return until it gets another event
*/
typedef RI_ENUM(u32, riEventWait) {
	riEventNoWait = 0,
	riEventWaitNext = -1
};

/*! sleep until rilib gets an event or the timer ends (defined by OS) */
RIAPI void riWindow_eventWait(riWindow* win, u32 waitMS);

/*!
	check all the events until there are none left.
	This should only be used if you're using callbacks only
*/
RIAPI riEvent* riWindow_checkEvent(riWindow* win);

/*!
	tell riWindow_eventWait to stop waiting (to be ran from another thread)
*/
RIAPI void ri_stopCheckEvents(void);

/*! window managment functions */
RIAPI void riWindow_close(riWindow* win); /*!< close the window and free leftover data */

/*! move a window to a given point */
RIAPI void riWindow_move(riWindow* win,
	riPoint v /*!< new pos */
);

#ifndef ri_NO_MONITOR
	/*! move window to a specific monitor */
	RIAPI void riWindow_moveToMonitor(riWindow* win, riMonitor m /* monitor */);
#endif

/*! resize window to a current size/area */
RIAPI void riWindow_resize(riWindow* win, /*!< source window */
	riArea a /*!< new size */
);

/*! set window aspect ratio */
RIAPI void riWindow_setAspectRatio(riWindow* win, riArea a);
/*! set the minimum dimensions of a window */
RIAPI void riWindow_setMinSize(riWindow* win, riArea a);
/*! set the maximum dimensions of a window */
RIAPI void riWindow_setMaxSize(riWindow* win, riArea a);

RIAPI void riWindow_focus(riWindow* win); /*!< sets the focus to this window */
RIAPI riBool riWindow_isInFocus(riWindow* win); /*!< checks the focus to this window */
RIAPI void riWindow_raise(riWindow* win); /*!< raise the window (to the top) */
RIAPI void riWindow_maximize(riWindow* win); /*!< maximize the window */
RIAPI void riWindow_setFullscreen(riWindow* win, riBool fullscreen); /*!< turn fullscreen on / off for a window */
RIAPI void riWindow_center(riWindow* win); /*!< center the window */
RIAPI void riWindow_minimize(riWindow* win); /*!< minimize the window (in taskbar (per OS))*/
RIAPI void riWindow_restore(riWindow* win); /*!< restore the window from minimized (per OS)*/
RIAPI void riWindow_setFloating(riWindow* win, riBool floating); /*!< make the window a floating window */
RIAPI void riWindow_setOpacity(riWindow* win, u8 opacity); /*!< sets the opacity of a window */

/*! if the window should have a border or not (borderless) based on bool value of `border` */
RIAPI void riWindow_setBorder(riWindow* win, riBool border);
RIAPI riBool riWindow_borderless(riWindow* win);

/*! turn on / off dnd (riWindowAllowDND stil must be passed to the window)*/
RIAPI void riWindow_setDND(riWindow* win, riBool allow);
/*! check if DND is allowed */
RIAPI riBool riWindow_allowsDND(riWindow* win);


#ifndef ri_NO_PASSTHROUGH
	/*! turn on / off mouse passthrough */
	RIAPI void riWindow_setMousePassthrough(riWindow* win, riBool passthrough);
#endif

/*! rename window to a given string */
RIAPI void riWindow_setName(riWindow* win,
	const char* name
);

RIAPI riBool riWindow_setIcon(riWindow* win, /*!< source window */
	u8* icon /*!< icon bitmap */,
	riArea a /*!< width and height of the bitmap */,
	i32 channels /*!< how many channels the bitmap has (rgb : 3, rgba : 4) */
); /*!< image MAY be resized by default, set both the taskbar and window icon */

typedef RI_ENUM(u8, ri_icon) {
	ri_iconTaskbar = RI_BIT(0),
	ri_iconWindow = RI_BIT(1),
	ri_iconBoth = ri_iconTaskbar | ri_iconWindow
};
RIAPI riBool riWindow_setIconEx(riWindow* win, u8* icon, riArea a, i32 channels, u8 type);

/*!< sets mouse to ri_mouse icon (loaded from a bitmap struct) */
RIAPI void riWindow_setMouse(riWindow* win, ri_mouse* mouse);

/*!< sets the mouse to a standard API cursor (based on ri_MOUSE, as seen at the end of the RI_HEADER part of this file) */
RIAPI	riBool riWindow_setMouseStandard(riWindow* win, u8 mouse);

RIAPI riBool riWindow_setMouseDefault(riWindow* win); /*!< sets the mouse to the default mouse icon */
/*
	Locks cursor at the center of the window
	win->event.point becomes raw mouse movement data

	this is useful for a 3D camera
*/
RIAPI void riWindow_mouseHold(riWindow* win, riArea area);
/*! stop holding the mouse and let it move freely */
RIAPI void riWindow_mouseUnhold(riWindow* win);

/*! hide the window */
RIAPI void riWindow_hide(riWindow* win);
/*! show the window */
RIAPI void riWindow_show(riWindow* win);

/*
	makes it so `riWindow_shouldClose` returns true or overrides a window close 
	by modifying window flags
*/
RIAPI void riWindow_setShouldClose(riWindow* win, riBool shouldClose);

/*! where the mouse is on the screen */
RIAPI riPoint ri_getGlobalMousePoint(void);

/*! where the mouse is on the window */
RIAPI riPoint riWindow_getMousePoint(riWindow* win);

/*! show the mouse or hide the mouse */
RIAPI void riWindow_showMouse(riWindow* win, riBool show);
/*! if the mouse is hidden */
RIAPI riBool riWindow_mouseHidden(riWindow* win);
/*! move the mouse to a given point */
RIAPI void riWindow_moveMouse(riWindow* win, riPoint v);

/*! if the window should close (ri_close was sent or escape was pressed) */
RIAPI riBool riWindow_shouldClose(riWindow* win);
/*! if the window is fullscreen */
RIAPI riBool riWindow_isFullscreen(riWindow* win);
/*! if the window is hidden */
RIAPI riBool riWindow_isHidden(riWindow* win);
/*! if the window is minimized */
RIAPI riBool riWindow_isMinimized(riWindow* win);
/*! if the window is maximized */
RIAPI riBool riWindow_isMaximized(riWindow* win);
/*! if the window is floating */
RIAPI riBool riWindow_isFloating(riWindow* win);
/** @} */

/** * @defgroup Monitor
* @{ */

#ifndef RI_NO_MONITOR
/*
	scale the window to the monitor.
	This is run by default if the user uses the arg `ri_scaleToMonitor` during window creation
*/
RIAPI void riWindow_scaleToMonitor(riWindow* win);
/*! get the struct of the window's monitor  */
RIAPI riMonitor riWindow_getMonitor(riWindow* win);
#endif

/** @} */

/** * @defgroup Input
* @{ */

/*! if window == NULL, it checks if the key is pressed globally. Otherwise, it checks only if the key is pressed while the window in focus. */
RIAPI riBool ri_isPressed(riWindow* win, ri_key key); /*!< if key is pressed (key code)*/

RIAPI riBool ri_wasPressed(riWindow* win, ri_key key); /*!< if key was pressed (checks previous state only) (key code) */

RIAPI riBool ri_isHeld(riWindow* win, ri_key key); /*!< if key is held (key code) */
RIAPI riBool ri_isReleased(riWindow* win, ri_key key); /*!< if key is released (key code) */

/* if a key is pressed and then released, pretty much the same as ri_isReleased */
RIAPI riBool ri_isClicked(riWindow* win, ri_key key /*!< key code */);

/*! if a mouse button is pressed */
RIAPI riBool ri_isMousePressed(riWindow* win, ri_mouseButton button /*!< mouse button code */ );
/*! if a mouse button is held */
RIAPI riBool ri_isMouseHeld(riWindow* win, ri_mouseButton button /*!< mouse button code */ );
/*! if a mouse button was released */
RIAPI riBool ri_isMouseReleased(riWindow* win, ri_mouseButton button /*!< mouse button code */ );
/*! if a mouse button was pressed (checks previous state only) */
RIAPI riBool ri_wasMousePressed(riWindow* win, ri_mouseButton button /*!< mouse button code */ );
/** @} */

/** * @defgroup Clipboard
* @{ */
typedef ptrdiff_t ri_ssize_t;

RIAPI const char* ri_readClipboard(size_t* size); /*!< read clipboard data */
/*! read clipboard data or send a NULL str to just get the length of the clipboard data */
RIAPI ri_ssize_t ri_readClipboardPtr(char* str, size_t strCapacity);
RIAPI void ri_writeClipboard(const char* text, u32 textLen); /*!< write text to the clipboard */
/** @} */

/** * @defgroup gamepad
* @{ */

typedef RI_ENUM(u8, ri_gamepadType) {
	ri_gamepadMicrosoft = 0, ri_gamepadSony, ri_gamepadNintendo, ri_gamepadLogitech, ri_gamepadUnknown
};

/*! gamepad count starts at 0*/
RIAPI u32 ri_isPressedGamepad(riWindow* win, u8 controller, ri_gamepadCodes button);
RIAPI u32 ri_isReleasedGamepad(riWindow* win, u8 controller, ri_gamepadCodes button);
RIAPI u32 ri_isHeldGamepad(riWindow* win, u8 controller, ri_gamepadCodes button);
RIAPI u32 ri_wasPressedGamepad(riWindow* win, u8 controller, ri_gamepadCodes button);
RIAPI riPoint ri_getGamepadAxis(riWindow* win, u16 controller, u16 whichAxis);
RIAPI const char* ri_getGamepadName(riWindow* win, u16 controller);
RIAPI size_t ri_getGamepadCount(riWindow* win);
RIAPI ri_gamepadType ri_getGamepadType(riWindow* win, u16 controller);

/** @} */

/** * @defgroup graphics_API
* @{ */

/*!< make the window the current opengl drawing context

	NOTE:
 	if you want to switch the graphics context's thread,
	you have to run riWindow_makeCurrent(NULL); on the old thread
	then riWindow_makeCurrent(valid_window) on the new thread
*/
RIAPI void riWindow_makeCurrent(riWindow* win);

/* supports openGL, directX, OSMesa, EGL and software rendering */
RIAPI void riWindow_swapBuffers(riWindow* win); /*!< swap the rendering buffer */
RIAPI void riWindow_vsync(riWindow* win, riBool enable);

/* 
*********************
RI_GRAPHICS_CONTEXT
*********************
*/

/* 
*******
ri_draw
*******
*/


RIAPI void ri_setTexture(riTexture texture); /* apply texture to drawing */
RIAPI void ri_setProgram(u32 program); /* use shader program for drawing */
RIAPI void ri_setGradient(
                                float* gradient, /* array of gradients */
                                size_t len /* length of array */
                            ); /* apply gradient to drawing, based on color list*/
RIAPI void ri_fill(riBool fill); /* toggle filling, if fill is false it runs ri_draw<whatever>_outline instead */
RIAPI void ri_center(riPoint3DF center); /* the center of the drawing (or shape), this is used for rotation */

/* args clear after a draw function by default, this toggles that */
RIAPI void ri_setClearArgs(riBool clearArgs); /* toggles if args are cleared by default or not */
RIAPI void ri_clearArgs(void); /* clears the args */
/* calculate the align a smaller rect with larger rect */
typedef RI_ENUM(u8, ri_alignment) {
    ri_ALIGN_NONE = RI_BIT(0),
    /* horizontal */
    ri_ALIGN_LEFT = RI_BIT(1),
    ri_ALIGN_CENTER = RI_BIT(2),
    ri_ALIGN_RIGHT = RI_BIT(3),
    
    /* vertical */
    ri_ALIGN_UP = RI_BIT(4),
    ri_ALIGN_MIDDLE = RI_BIT(5),
    ri_ALIGN_DOWN = RI_BIT(6),

    ri_ALIGN_HORIZONTAL = ri_ALIGN_LEFT | ri_ALIGN_CENTER | ri_ALIGN_RIGHT,
    ri_ALIGN_VERTICAL = ri_ALIGN_UP | ri_ALIGN_MIDDLE | ri_ALIGN_DOWN,
/* ex : alignment = (ri_ALIGN_LEFT | ri_ALIGN_MIDDLE) */
};

/* align smaller rect onto larger rect based on a given alignment */
RIAPI riRect ri_alignRect(riRect larger, riRect smaller, u16 alignment);
RIAPI riRectF ri_alignRectF(riRectF larger, riRectF smaller, u16 alignment);

typedef struct RI_MATRIX {
    float m[16];
} RI_MATRIX;

RIAPI RI_MATRIX ri_initDrawMatrix(riPoint3DF center);
RIAPI void ri_clear(riColor color);
RIAPI void ri_viewport(i32 x, i32 y, i32 w, i32 h);
/* create a texture based on a given bitmap, this must be freed later using ri_deleteTexture or opengl*/
RIAPI riTexture ri_createTexture(u8* bitmap, riArea memsize,  u8 channels);
/* delete a texture */
RIAPI void ri_deleteTexture(riTexture tex);
/* starts scissoring */
RIAPI void ri_scissorStart(riRectF scissor);
/* stops scissoring */
RIAPI void ri_scissorEnd(void);

/*!< draw current batch to the window */
RIAPI void riWindow_draw(riWindow* win);

/*!< clear graphics and update window size info (should be ran before RSGL_draw<x> calls) */
RIAPI void riWindow_clear(riWindow* win, riColor color);

/* custom shader program */
typedef struct riProgramInfo {
    u32 vShader, fShader, program;
} riProgramInfo;

RIAPI riProgramInfo ri_renderCreateProgram(const char* VShaderCode, const char* FShaderCode, const char* posName, const char* texName, const char* colorName);
RIAPI void ri_renderDeleteProgram(riProgramInfo program);
RIAPI void ri_renderSetShaderValue(u32 program, char* var, float value[], u8 len);

/* these are RFont functions that also must be defined by the renderer

32 RFont_create_atlas(u32 atlasWidth, u32 atlasHeight);
void RFont_bitmap_to_atlas(ri_rsoft_texture atlas, u8* bitmap, float x, float y, float w, float h);

*/

/* ri translation */
RIAPI RI_MATRIX ri_matrixMultiply(float left[16], float right[16]);
RIAPI RI_MATRIX ri_rotatef(RI_MATRIX* matrix, float angle, float x, float y, float z); 
RIAPI RI_MATRIX ri_translatef(RI_MATRIX* matrix, float x, float y, float z);
/* 2D shape drawing */
/* in the function names, F means float */

RIAPI void ri_drawPoint(riPoint p, riColor c);
RIAPI void ri_drawPointF(riPointF p, riColor c);
RIAPI void ri_plotLines(riPointF* lines, size_t points_count, u32 thickness, riColor c);

RIAPI void ri_drawTriangle(riTriangle t, riColor c);
RIAPI void ri_drawTriangleF(riTriangleF t, riColor c);

RIAPI void ri_drawTriangleHyp(riPointF p, size_t angle, float hypotenuse, riColor color);

RIAPI void ri_drawRect(riRect r, riColor c);
RIAPI void ri_drawRectF(riRectF r, riColor c);


RIAPI void ri_drawRoundRect(riRect r, riPoint rounding, riColor c);
RIAPI void ri_drawRoundRectF(riRectF r, riPoint rounding, riColor c);

RIAPI void ri_drawPolygon(riRect r, u32 sides, riColor c);
RIAPI void ri_drawPolygonF(riRectF r, u32 sides, riColor c);

RIAPI void ri_drawArc(riRect o, riPoint arc, riColor color);
RIAPI void ri_drawArcF(riRectF o, riPointF arc, riColor color);

RIAPI void ri_drawCircle(riCircle c, riColor color);
RIAPI void ri_drawCircleF(riCircleF c, riColor color);

RIAPI void ri_drawOval(riRect o, riColor c);
RIAPI void ri_drawOvalF(riRectF o, riColor c);

RIAPI void ri_drawLine(riPoint p1, riPoint p2, u32 thickness, riColor c);
RIAPI void ri_drawLineF(riPointF p1, riPointF p2, u32 thickness, riColor c);

/* 2D outlines */

/* thickness means the thickness of the line */

RIAPI void ri_drawTriangleOutline(riTriangle t, u32 thickness, riColor c);
RIAPI void ri_drawTriangleFOutline(riTriangleF t, u32 thickness, riColor c);

RIAPI void ri_drawRectOutline(riRect r, u32 thickness, riColor c);
RIAPI void ri_drawRectFOutline(riRectF r, u32 thickness, riColor c);

RIAPI void ri_drawRoundRectOutline(riRect r, riPoint rounding, u32 thickness, riColor c);
RIAPI void ri_drawRoundRectFOutline(riRectF r, riPoint rounding, u32 thickness, riColor c);

RIAPI void ri_drawPolygonOutline(riRect r, u32 sides, u32 thickness, riColor c);
RIAPI void ri_drawPolygonFOutline(riRectF r, u32 sides, u32 thickness, riColor c);

RIAPI void ri_drawArcOutline(riRect o, riPoint arc, u32 thickness, riColor color);
RIAPI void ri_drawArcFOutline(riRectF o, riPointF arc, u32 thickness, riColor color);

RIAPI void ri_drawCircleOutline(riCircle c, u32 thickness, riColor color);
RIAPI void ri_drawCircleFOutline(riCircleF c, u32 thickness, riColor color);

RIAPI void ri_drawOvalOutline(riRect o, u32 thickness, riColor c);
RIAPI void ri_drawOvalFOutline(riRectF o, u32 thickness, riColor c);

/* format a string */
RIAPI const char* RI_strFmt(const char* string, ...);

/* loads a font into ri, returns it's index into the ri_fonts array, this is used as an id in later functions */
RIAPI i32 ri_loadFont(const char* font);
/* (pro) loads a font into ri, returns it's index into the ri_fonts array, this is used as an id in later functions 
    using a given atlasWidth + atlasHeight
*/
RIAPI i32 ri_loadFontPro(const char* font, size_t atlasWidth, size_t atlasHeight);
/* sets font as the current font in use based on index in ri_font, given when it was loaded */
RIAPI void ri_setFont(i32 font);

/* sets source RFont font as the current font, given when it was loaded */
struct RFont_font;
RIAPI void ri_setRFont(struct RFont_font* font);

RIAPI void ri_drawText_len(const char* text, size_t len, riCircle c, riColor color);
RIAPI void ri_drawText_pro(const char* text, size_t len, float spacing, riCircle c, riColor color);
RIAPI void ri_drawText(const char* text, riCircle c, riColor color);
#define RI_drawTextF(text, font, c, color) \
    ri_setFont(font);\
    ri_drawText(text, c, color);

/* align text onto larger rect based on a given alignment */
RIAPI riCircle ri_alignText(const char* str, riCircle c, riRectF larger, u8 alignment);
/* align text based on a length */
RIAPI riCircle ri_alignText_len(const char* str, size_t str_len, riCircle c, riRectF larger, u8 alignment);

/* 
    returns the width of a text when rendered with the set font with the size of `fontSize
    stops at `textEnd` or when it reaches '\0'
*/
RIAPI riArea ri_textArea(const char* text, u32 fontSize, size_t textEnd);
RIAPI riArea ri_textLineArea(const char* text, u32 fontSize, size_t textEnd, size_t line);
#define RI_textAreaF(text, fontSize, textEnd) \
    ri_setFont(font);\
    ri_textAreaF(text, fontSize, textEnd);

/* 
    this creates a texture based on a given image, draws it on a rectangle and then returns the loaded texture 
    
    if the rectangle's width and height are 0 it doesn't draw the image
    the texture is loaded into riImage, this means it doesn't need to be freed
    but you can still free it early
*/

RIAPI riImage ri_loadImage(const char* image);
RIAPI riImage ri_drawImage(riImage, riRect r);
RIAPI riImage ri_drawImageFile(const char* image, riRect r);

/* 
    these two functions can be used before ri_renderCreateTexture in order to create 
    an swizzle'd texutre or atlas
*/

/* 
*******
extra
*******
*/

/* ** collision functions ** */
RIAPI riBool riCircleCollidePoint(riCircle c, riPoint p);
RIAPI riBool riCircleCollideRect(riCircle c, riRect r);
RIAPI riBool riCircleCollide(riCircle cir1, riCircle cir2);
RIAPI riBool riRectCollidePoint(riRect r, riPoint p);
RIAPI riBool riRectCollide(riRect r, riRect r2);
RIAPI riBool riPointCollide(riPoint p, riPoint p2);

RIAPI riBool riCircleCollidePointF(riCircleF c, riPointF p);
RIAPI riBool riCircleCollideRectF(riCircleF c, riRectF r);
RIAPI riBool riCircleCollideF(riCircleF cir1, riCircleF cir2);
RIAPI riBool riRectCollidePointF(riRectF r, riPointF p);
RIAPI riBool riRectCollideF(riRectF r, riRectF r2);
RIAPI riBool riPointCollideF(riPointF p, riPointF p2);

typedef void (*ri_proc)(void); // function pointer equivalent of void*

/*! native API functions */
/*! OpenGL init hints */
typedef RI_ENUM(u8, ri_glHints)  {
	ri_glStencil = 0,  /*!< set stencil buffer bit size (8 by default) */
	ri_glSamples, /*!< set number of sampiling buffers (4 by default) */
	ri_glStereo, /*!< use GL_STEREO (GL_FALSE by default) */
	ri_glAuxBuffers, /*!< number of aux buffers (0 by default) */
	ri_glDoubleBuffer, /*!< request double buffering */
	ri_glRed, ri_glGreen, ri_glBlue, ri_glAlpha, /*!< set RGBA bit sizes */
	ri_glDepth, 
	ri_glAccumRed, ri_glAccumGreen, ri_glAccumBlue,ri_glAccumAlpha, /*!< set accumulated RGBA bit sizes */
	ri_glSRGB, /*!< request sRGA */
	ri_glRobustness, /*!< request a robust context */
	ri_glDebug, /*!< request opengl debugging */
	ri_glNoError, /*!< request no opengl errors */
	ri_glReleaseBehavior,
	ri_glProfile,
	ri_glMajor, ri_glMinor,
	ri_glFinalHint, /*!< the final hint (not for setting) */
	ri_releaseFlush = 0,  ri_glReleaseNone, /* ri_glReleaseBehavior options */
	ri_glCore = 0,  ri_glCompatibility /*!< ri_glProfile options */
};
RIAPI void ri_setGLHint(ri_glHints hint, i32 value);
RIAPI ri_proc ri_getProcAddress(const char* procname); /*!< get native opengl proc address */
/** * @defgroup Supporting

* @{ */
RIAPI double ri_getTime(void); /*!< get time in seconds since ri_setTime, which ran when the first window is open  */
RIAPI u64 ri_getTimeNS(void); /*!< get time in nanoseconds ri_setTime, which ran when the first window is open */
RIAPI void ri_sleep(u64 milisecond); /*!< sleep for a set time */
RIAPI void ri_setTime(double time); /*!< set timer in seconds */
RIAPI u64 ri_getTimerValue(void); /*!< get API timer value */
RIAPI u64 ri_getTimerFreq(void); /*!< get API time freq */

/*< updates fps / sets fps to cap (must by ran manually by the user at the end of a frame), returns current fps */
RIAPI u32 ri_checkFPS(double startTime, u32 frameCount, u32 fpsCap);

/*!
	key codes and mouse icon enums
*/
#undef ri_key
typedef RI_ENUM(u8, ri_key) {
	ri_keyNULL = 0,
	ri_escape = '\033',
	ri_backtick = '`',
	ri_0 = '0',
	ri_1 = '1',
	ri_2 = '2',
	ri_3 = '3',
	ri_4 = '4',
	ri_5 = '5',
	ri_6 = '6',
	ri_7 = '7',
	ri_8 = '8',
	ri_9 = '9',

	ri_minus = '-',
	ri_equals = '=',
	ri_backSpace = '\b',
	ri_tab = '\t',
	ri_space = ' ',

	ri_a = 'a',
	ri_b = 'b',
	ri_c = 'c',
	ri_d = 'd',
	ri_e = 'e',
	ri_f = 'f',
	ri_g = 'g',
	ri_h = 'h',
	ri_i = 'i',
	ri_j = 'j',
	ri_k = 'k',
	ri_l = 'l',
	ri_m = 'm',
	ri_n = 'n',
	ri_o = 'o',
	ri_p = 'p',
	ri_q = 'q',
	ri_r = 'r',
	ri_s = 's',
	ri_t = 't',
	ri_u = 'u',
	ri_v = 'v',
	ri_w = 'w',
	ri_x = 'x',
	ri_y = 'y',
	ri_z = 'z',

	ri_period = '.',
	ri_comma = ',',
	ri_slash = '/',
	ri_bracket = '{',
	ri_closeBracket = '}',
	ri_semicolon = ';',
	ri_apostrophe = '\'',
	ri_backSlash = '\\',
	ri_return = '\n',

	ri_delete = '\177', /* 127 */

	ri_F1,
	ri_F2,
	ri_F3,
	ri_F4,
	ri_F5,
	ri_F6,
	ri_F7,
	ri_F8,
	ri_F9,
	ri_F10,
	ri_F11,
	ri_F12,

	ri_capsLock,
	ri_shiftL,
	ri_controlL,
	ri_altL,
	ri_superL,
	ri_shiftR,
	ri_controlR,
	ri_altR,
	ri_superR,
	ri_up,
	ri_down,
	ri_left,
	ri_right,

	ri_insert,
	ri_end,
	ri_home,
	ri_pageUp,
	ri_pageDown,

	ri_numLock,
	ri_KP_Slash,
	ri_multiply,
	ri_KP_Minus,
	ri_KP_1,
	ri_KP_2,
	ri_KP_3,
	ri_KP_4,
	ri_KP_5,
	ri_KP_6,
	ri_KP_7,
	ri_KP_8,
	ri_KP_9,
	ri_KP_0,
	ri_KP_Period,
	ri_KP_Return,
	ri_scrollLock,
	ri_keyLast
};

typedef RI_ENUM(u8, ri_mouseIcons) {
	ri_mouseNormal = 0,
	ri_mouseArrow,
	ri_mouseIbeam,
	ri_mouseCrosshair,
	ri_mousePointingHand,
	ri_mouseResizeEW,
	ri_mouseResizeNS,
	ri_mouseResizeNWSE,
	ri_mouseResizeNESW,
	ri_mouseResizeAll,
	ri_mouseNotAllowed,
};

/** @} */

/** * @defgroup Audio

* @{ */

RIAPI i32 riAudio_play(const char* file); 
/** @} */

#endif /* RI_HEADER */

#if defined(__cplusplus)
}
#endif
