/**
 * @defgroup Win Win
 * @ingroup Elementary
 *
 * @image html win_inheritance_tree.png
 * @image latex win_inheritance_tree.eps
 *
 * @image html img/widget/win/preview-00.png
 * @image latex img/widget/win/preview-00.eps
 *
 * The window class of Elementary. Contains functions to manipulate
 * windows. The Evas engine used to render the window contents is specified
 * in the system or user elementary config files (whichever is found last),
 * and can be overridden with the ELM_ENGINE environment variable for
 * testing.  Engines that may be supported (depending on Evas and Ecore-Evas
 * compilation setup and modules actually installed at runtime) are (listed
 * in order of best supported and most likely to be complete and work to
 * lowest quality).
 *
 * @li "x11", "x", "software-x11", "software_x11" (Software rendering in X11)
 * @li "gl", "opengl", "opengl-x11", "opengl_x11" (OpenGL or OpenGL-ES2
 * rendering in X11)
 * @li "shot:..." (Virtual screenshot renderer - renders to output file and
 * exits)
 * @li "fb", "software-fb", "software_fb" (Linux framebuffer direct software
 * rendering)
 * @li "sdl", "software-sdl", "software_sdl" (SDL software rendering to SDL
 * buffer)
 * @li "gl-sdl", "gl_sdl", "opengl-sdl", "opengl_sdl" (OpenGL or OpenGL-ES2
 * rendering using SDL as the buffer)
 * @li "gdi", "software-gdi", "software_gdi" (Windows WIN32 rendering via
 * GDI with software)
 * @li "dfb", "directfb" (Rendering to a DirectFB window)
 * @li "x11-8", "x8", "software-8-x11", "software_8_x11" (Rendering in
 * grayscale using dedicated 8bit software engine in X11)
 * @li "x11-16", "x16", "software-16-x11", "software_16_x11" (Rendering in
 * X11 using 16bit software engine)
 * @li "wince-gdi", "software-16-wince-gdi", "software_16_wince_gdi"
 * (Windows CE rendering via GDI with 16bit software renderer)
 * @li "sdl-16", "software-16-sdl", "software_16_sdl" (Rendering to SDL
 * buffer with 16bit software renderer)
 * @li "ews" (rendering to EWS - Ecore + Evas Single Process Windowing System)
 * @li "gl-cocoa", "gl_cocoa", "opengl-cocoa", "opengl_cocoa" (OpenGL rendering in Cocoa)
 * @li "psl1ght" (PS3 rendering using PSL1GHT)
 *
 * All engines use a simple string to select the engine to render, EXCEPT
 * the "shot" engine. This actually encodes the output of the virtual
 * screenshot and how long to delay in the engine string. The engine string
 * is encoded in the following way:
 *
 *   "shot:[delay=XX][:][repeat=DDD][:][file=XX]"
 *
 * Where options are separated by a ":" char if more than one option is
 * given, with delay, if provided being the first option and file the last
 * (order is important). The delay specifies how long to wait after the
 * window is shown before doing the virtual "in memory" rendering and then
 * save the output to the file specified by the file option (and then exit).
 * If no delay is given, the default is 0.5 seconds. If no file is given the
 * default output file is "out.png". Repeat option is for continuous
 * capturing screenshots. Repeat range is from 1 to 999 and filename is
 * fixed to "out001.png" Some examples of using the shot engine:
 *
 *   ELM_ENGINE="shot:delay=1.0:repeat=5:file=elm_test.png" elementary_test
 *   ELM_ENGINE="shot:delay=1.0:file=elm_test.png" elementary_test
 *   ELM_ENGINE="shot:file=elm_test2.png" elementary_test
 *   ELM_ENGINE="shot:delay=2.0" elementary_test
 *   ELM_ENGINE="shot:" elementary_test
 *
 * Signals that you can add callbacks for are:
 *
 * @li "delete,request": the user requested to close the window. See
 * elm_win_autodel_set().
 * @li "focus,in": window got focus
 * @li "focus,out": window lost focus
 * @li "moved": window that holds the canvas was moved
 * @li "withdrawn": window is still managed normally but removed from view
 * @li "iconified": window is minimized (perhaps into an icon or taskbar)
 * @li "normal": window is in a normal state (not withdrawn or iconified)
 * @li "stick": window has become sticky (shows on all desktops)
 * @li "unstick": window has stopped being sticky
 * @li "fullscreen": window has become fullscreen
 * @li "unfullscreen": window has stopped being fullscreen
 * @li "maximized": window has been maximized
 * @li "unmaximized": window has stopped being maximized
 * @li "ioerr": there has been a low-level I/O error with the display system
 *
 * Examples:
 * @li @ref win_example_01
 *
 * @{
 */
/**
 * Defines the types of window that can be created
 *
 * These are hints set on the window so that a running Window Manager knows
 * how the window should be handled and/or what kind of decorations it
 * should have.
 *
 * Currently, only the X11 backed engines use them.
 */
typedef enum
{
   ELM_WIN_BASIC, /**< A normal window. Indicates a normal, top-level
                     window. Almost every window will be created with this
                     type. */
   ELM_WIN_DIALOG_BASIC, /**< Used for simple dialog windows/ */
   ELM_WIN_DESKTOP, /**< For special desktop windows, like a background
                       window holding desktop icons. */
   ELM_WIN_DOCK, /**< The window is used as a dock or panel. Usually would
                    be kept on top of any other window by the Window
                    Manager. */
   ELM_WIN_TOOLBAR, /**< The window is used to hold a floating toolbar, or
                       similar. */
   ELM_WIN_MENU, /**< Similar to #ELM_WIN_TOOLBAR. */
   ELM_WIN_UTILITY, /**< A persistent utility window, like a toolbox or
                       palette. */
   ELM_WIN_SPLASH, /**< Splash window for a starting up application. */
   ELM_WIN_DROPDOWN_MENU, /**< The window is a dropdown menu, as when an
                             entry in a menubar is clicked. Typically used
                             with elm_win_override_set(). This hint exists
                             for completion only, as the EFL way of
                             implementing a menu would not normally use a
                             separate window for its contents. */
   ELM_WIN_POPUP_MENU, /**< Like #ELM_WIN_DROPDOWN_MENU, but for the menu
                          triggered by right-clicking an object. */
   ELM_WIN_TOOLTIP, /**< The window is a tooltip. A short piece of
                       explanatory text that typically appear after the
                       mouse cursor hovers over an object for a while.
                       Typically used with elm_win_override_set() and also
                       not very commonly used in the EFL. */
   ELM_WIN_NOTIFICATION, /**< A notification window, like a warning about
                            battery life or a new E-Mail received. */
   ELM_WIN_COMBO, /**< A window holding the contents of a combo box. Not
                     usually used in the EFL. */
   ELM_WIN_DND, /**< Used to indicate the window is a representation of an
                   object being dragged across different windows, or even
                   applications. Typically used with
                   elm_win_override_set(). */
   ELM_WIN_INLINED_IMAGE, /**< The window is rendered onto an image
                             buffer. No actual window is created for this
                             type, instead the window and all of its
                             contents will be rendered to an image buffer.
                             This allows to have children window inside a
                             parent one just like any other object would
                             be, and do other things like applying @c
                             Evas_Map effects to it. This is the only type
                             of window that requires the @c parent
                             parameter of elm_win_add() to be a valid @c
                             Evas_Object. */
   ELM_WIN_SOCKET_IMAGE,/**< The window is rendered onto an image buffer
			     and can be shown other process's plug image object.
			     No actual window is created for this type,
			     instead the window and all of its contents will be
			     rendered to an image buffer and can be shown
			     other process's plug image object*/
} Elm_Win_Type;

/**
 * The different layouts that can be requested for the virtual keyboard.
 *
 * When the application window is being managed by Illume, it may request
 * any of the following layouts for the virtual keyboard.
 */
typedef enum
{
   ELM_WIN_KEYBOARD_UNKNOWN, /**< Unknown keyboard state */
   ELM_WIN_KEYBOARD_OFF, /**< Request to deactivate the keyboard */
   ELM_WIN_KEYBOARD_ON, /**< Enable keyboard with default layout */
   ELM_WIN_KEYBOARD_ALPHA, /**< Alpha (a-z) keyboard layout */
   ELM_WIN_KEYBOARD_NUMERIC, /**< Numeric keyboard layout */
   ELM_WIN_KEYBOARD_PIN, /**< PIN keyboard layout */
   ELM_WIN_KEYBOARD_PHONE_NUMBER, /**< Phone keyboard layout */
   ELM_WIN_KEYBOARD_HEX, /**< Hexadecimal numeric keyboard layout */
   ELM_WIN_KEYBOARD_TERMINAL, /**< Full (QWERTY) keyboard layout */
   ELM_WIN_KEYBOARD_PASSWORD, /**< Password keyboard layout */
   ELM_WIN_KEYBOARD_IP, /**< IP keyboard layout */
   ELM_WIN_KEYBOARD_HOST, /**< Host keyboard layout */
   ELM_WIN_KEYBOARD_FILE, /**< File keyboard layout */
   ELM_WIN_KEYBOARD_URL, /**< URL keyboard layout */
   ELM_WIN_KEYBOARD_KEYPAD, /**< Keypad layout */
   ELM_WIN_KEYBOARD_J2ME /**< J2ME keyboard layout */
} Elm_Win_Keyboard_Mode;

/**
 * In some environments, like phones, you may have an indicator that
 * shows battery status, reception, time etc. This is the indicator.
 *
 * Sometimes you don't want it because you provide the same functionality
 * inside your app, so this will request that the indicator is hidden in
 * this circumstance if you use ELM_ILLUME_INDICATOR_HIDE. The default
 * is to have the indicator shown.
 */
typedef enum
{
   ELM_WIN_INDICATOR_UNKNOWN, /**< Unknown indicator state */
   ELM_WIN_INDICATOR_HIDE, /**< Hides the indicator */
   ELM_WIN_INDICATOR_SHOW /**< Shows the indicator */
} Elm_Win_Indicator_Mode;

/**
 * Defines the opacity modes of indicator that can be shown
 */

typedef enum
{
   ELM_WIN_INDICATOR_OPACITY_UNKNOWN, /**< Unknown indicator opacity mode */
   ELM_WIN_INDICATOR_OPAQUE, /**< Opacifies the indicator */
   ELM_WIN_INDICATOR_TRANSLUCENT, /**< Be translucent the indicator */
   ELM_WIN_INDICATOR_TRANSPARENT /**< Transparentizes the indicator */
} Elm_Win_Indicator_Opacity_Mode;

/**
 * Available commands that can be sent to the Illume manager.
 *
 * When running under an Illume session, a window may send commands to the
 * Illume manager to perform different actions.
 */
typedef enum
{
   ELM_ILLUME_COMMAND_FOCUS_BACK, /**< Reverts focus to the previous window */
   ELM_ILLUME_COMMAND_FOCUS_FORWARD, /**< Sends focus to the next window in the list */
   ELM_ILLUME_COMMAND_FOCUS_HOME, /**< Hides all windows to show the Home screen */
   ELM_ILLUME_COMMAND_CLOSE, /**< Closes the currently active window */
} Elm_Illume_Command;

/**
 * Adds a window object. If this is the first window created, pass NULL as
 * @p parent.
 *
 * @param parent Parent object to add the window to, or NULL
 * @param name The name of the window
 * @param type The window type, one of #Elm_Win_Type.
 *
 * The @p parent parameter can be @c NULL for every window @p type
 * except #ELM_WIN_INLINED_IMAGE, which needs a parent to retrieve the
 * canvas on which the image object will be created.
 *
 * @return The created object, or @c NULL on failure
 *
 * @ingroup Win
 */
EAPI Evas_Object          *elm_win_add(Evas_Object *parent, const char *name, Elm_Win_Type type);

/**
 * Adds a window object with standard setup
 *
 * @param name The name of the window
 * @param title The title for the window
 *
 * This creates a window like elm_win_add() but also puts in a standard
 * background with elm_bg_add(), as well as setting the window title to
 * @p title. The window type created is of type ELM_WIN_BASIC, with @c NULL
 * as the parent widget.
 *
 * @return The created object, or @c NULL on failure
 *
 * @see elm_win_add()
 *
 * @ingroup Win
 */
EAPI Evas_Object          *elm_win_util_standard_add(const char *name, const char *title);

/**
 * Add @p subobj as a resize object of window @p obj.
 *
 *
 * Setting an object as a resize object of the window means that the
 * @p subobj child's size and position will be controlled by the window
 * directly. That is, the object will be resized to match the window size
 * and should never be moved or resized manually by the developer.
 *
 * In addition, resize objects of the window control what the minimum size
 * of it will be, as well as whether it can or not be resized by the user.
 *
 * For the end user to be able to resize a window by dragging the handles
 * or borders provided by the Window Manager, or using any other similar
 * mechanism, all of the resize objects in the window should have their
 * evas_object_size_hint_weight_set() set to EVAS_HINT_EXPAND.
 *
 * Also notice that the window can get resized to the current size of the
 * object if the EVAS_HINT_EXPAND is set @b after the call to
 * elm_win_resize_object_add(). So if the object should get resized to the
 * size of the window, set this hint @b before adding it as a resize object
 * (this happens because the size of the window and the object are evaluated
 * as soon as the object is added to the window).
 *
 * @param obj The window object
 * @param subobj The resize object to add
 *
 * @ingroup Win
 */
EAPI void                  elm_win_resize_object_add(Evas_Object *obj, Evas_Object *subobj);

/**
 * Delete @p subobj as a resize object of window @p obj.
 *
 * This function removes the object @p subobj from the resize objects of
 * the window @p obj. It will not delete the object itself, which will be
 * left unmanaged and should be deleted by the developer, manually handled
 * or set as child of some other container.
 *
 * @param obj The window object
 * @param subobj The resize object to add
 *
 * @ingroup Win
 */
EAPI void                  elm_win_resize_object_del(Evas_Object *obj, Evas_Object *subobj);

/**
 * Set the title of the window
 *
 * @param obj The window object
 * @param title The title to set
 *
 * @ingroup Win
 */
EAPI void                  elm_win_title_set(Evas_Object *obj, const char *title);

/**
 * Get the title of the window
 *
 * The returned string is an internal one and should not be freed or
 * modified. It will also be rendered invalid if a new title is set or if
 * the window is destroyed.
 *
 * @param obj The window object
 * @return The title
 *
 * @ingroup Win
 */
EAPI const char           *elm_win_title_get(const Evas_Object *obj);

/**
 * Set the icon name of the window
 *
 * @param obj The window object
 * @param icon_name The icon name to set
 *
 * @ingroup Win
 */
EAPI void                  elm_win_icon_name_set(Evas_Object *obj, const char *icon_name);

/**
 * Get the icon name of the window
 *
 * The returned string is an internal one and should not be freed or
 * modified. It will also be rendered invalid if a new icon name is set or if
 * the window is destroyed.
 *
 * @param obj The window object
 * @return The icon name
 *
 * @ingroup Win
 */
EAPI const char           *elm_win_icon_name_get(const Evas_Object *obj);

/**
 * Set the role of the window
 *
 * @param obj The window object
 * @param role The role to set
 *
 * @ingroup Win
 */
EAPI void                  elm_win_role_set(Evas_Object *obj, const char *role);

/**
 * Get the role of the window
 *
 * The returned string is an internal one and should not be freed or
 * modified. It will also be rendered invalid if a new role is set or if
 * the window is destroyed.
 *
 * @param obj The window object
 * @return The role
 *
 * @ingroup Win
 */
EAPI const char           *elm_win_role_get(const Evas_Object *obj);

/**
 * Set a window object's icon
 *
 * This sets an image to be used as the icon for the given window, in
 * the window manager decoration part. The exact pixel dimensions of
 * the object (not object size) will be used, and the image pixels
 * will be used as-is when this function is called. If the image
 * object has been updated, then call this function again to source
 * the image pixels and put them on the window's icon. Note that
 * <b>only Evas image objects are allowed</b>, for
 *
 * @param obj The window object to get an icon
 * @param icon The Evas image object to use for an icon
 *
 * Example of usage:
 * @code
 *  icon = evas_object_image_add(evas_object_evas_get(elm_window));
 *  evas_object_image_file_set(icon, "/path/to/the/icon", NULL);
 *  elm_win_icon_object_set(elm_window, icon);
 *  evas_object_show(icon);
 * @endcode
 *
 * @ingroup Win
 */
EAPI void                  elm_win_icon_object_set(Evas_Object *obj, Evas_Object *icon);

/**
 * Get the icon object used for the window
 *
 * The object returns is the one marked by elm_win_icon_object_set() as the
 * object to use for the window icon.
 *
 * @param obj The window object
 * @return The icon object set
 *
 * @ingroup Win
 */
EAPI const Evas_Object    *elm_win_icon_object_get(const Evas_Object *obj);

/**
 * Set the window's autodel state.
 *
 * When closing the window in any way outside of the program control, like
 * pressing the X button in the titlebar or using a command from the
 * Window Manager, a "delete,request" signal is emitted to indicate that
 * this event occurred and the developer can take any action, which may
 * include, or not, destroying the window object.
 *
 * When the @p autodel parameter is set, the window will be automatically
 * destroyed when this event occurs, after the signal is emitted.
 * If @p autodel is @c EINA_FALSE, then the window will not be destroyed
 * and is up to the program to do so when it's required.
 *
 * @param obj The window object
 * @param autodel If true, the window will automatically delete itself when
 * closed
 *
 * @ingroup Win
 */
EAPI void                  elm_win_autodel_set(Evas_Object *obj, Eina_Bool autodel);

/**
 * Get the window's autodel state.
 *
 * @param obj The window object
 * @return If the window will automatically delete itself when closed
 *
 * @see elm_win_autodel_set()
 *
 * @ingroup Win
 */
EAPI Eina_Bool             elm_win_autodel_get(const Evas_Object *obj);

/**
 * Activate a window object.
 *
 * This function sends a request to the Window Manager to activate the
 * window pointed by @p obj. If honored by the WM, the window will receive
 * the keyboard focus.
 *
 * @note This is just a request that a Window Manager may ignore, so calling
 * this function does not ensure in any way that the window will be the
 * active one after it.
 *
 * @param obj The window object
 *
 * @ingroup Win
 */
EAPI void                  elm_win_activate(Evas_Object *obj);

/**
 * Lower a window object.
 *
 * Places the window pointed by @p obj at the bottom of the stack, so that
 * no other window is covered by it.
 *
 * If elm_win_override_set() is not set, the Window Manager may ignore this
 * request.
 *
 * @param obj The window object
 *
 * @ingroup Win
 */
EAPI void                  elm_win_lower(Evas_Object *obj);

/**
 * Raise a window object.
 *
 * Places the window pointed by @p obj at the top of the stack, so that it's
 * not covered by any other window.
 *
 * If elm_win_override_set() is not set, the Window Manager may ignore this
 * request.
 *
 * @param obj The window object
 *
 * @ingroup Win
 */
EAPI void                  elm_win_raise(Evas_Object *obj);

/**
 * Center a window on its screen
 *
 * This function centers window @p obj horizontally and/or vertically based on the values
 * of @p h and @p v.
 * @param obj The window object
 * @param h If true, center horizontally. If false, do not change horizontal location.
 * @param v If true, center vertically. If false, do not change vertical location.
 *
 * @ingroup Win
 */
EAPI void                  elm_win_center(Evas_Object *obj, Eina_Bool h, Eina_Bool v);

/**
 * Set the borderless state of a window.
 *
 * This function requests the Window Manager to not draw any decoration
 * around the window.
 *
 * @param obj The window object
 * @param borderless If true, the window is borderless
 *
 * @ingroup Win
 */
EAPI void                  elm_win_borderless_set(Evas_Object *obj, Eina_Bool borderless);

/**
 * Get the borderless state of a window.
 *
 * @param obj The window object
 * @return If true, the window is borderless
 *
 * @ingroup Win
 */
EAPI Eina_Bool             elm_win_borderless_get(const Evas_Object *obj);

/**
 * Set the shaped state of a window.
 *
 * Shaped windows, when supported, will render the parts of the window that
 * has no content, transparent.
 *
 * If @p shaped is EINA_FALSE, then it is strongly advised to have some
 * background object or cover the entire window in any other way, or the
 * parts of the canvas that have no data will show framebuffer artifacts.
 *
 * @param obj The window object
 * @param shaped If true, the window is shaped
 *
 * @see elm_win_alpha_set()
 *
 * @ingroup Win
 */
EAPI void                  elm_win_shaped_set(Evas_Object *obj, Eina_Bool shaped);

/**
 * Get the shaped state of a window.
 *
 * @param obj The window object
 * @return If true, the window is shaped
 *
 * @see elm_win_shaped_set()
 *
 * @ingroup Win
 */
EAPI Eina_Bool             elm_win_shaped_get(const Evas_Object *obj);

/**
 * Set the alpha channel state of a window.
 *
 * If @p alpha is EINA_TRUE, the alpha channel of the canvas will be enabled
 * possibly making parts of the window completely or partially transparent.
 * This is also subject to the underlying system supporting it, like for
 * example, running under a compositing manager. If no compositing is
 * available, enabling this option will instead fallback to using shaped
 * windows, with elm_win_shaped_set().
 *
 * @param obj The window object
 * @param alpha If true, the window has an alpha channel
 *
 * @see elm_win_alpha_set()
 *
 * @ingroup Win
 */
EAPI void                  elm_win_alpha_set(Evas_Object *obj, Eina_Bool alpha);

/**
 * Get the alpha channel state of a window.
 *
 * @param obj The window object
 * @return If true, the window has an alpha channel
 *
 * @ingroup Win
 */
EAPI Eina_Bool             elm_win_alpha_get(const Evas_Object *obj);

/**
 * Set the override state of a window.
 *
 * A window with @p override set to EINA_TRUE will not be managed by the
 * Window Manager. This means that no decorations of any kind will be shown
 * for it, moving and resizing must be handled by the application, as well
 * as the window visibility.
 *
 * This should not be used for normal windows, and even for not so normal
 * ones, it should only be used when there's a good reason and with a lot
 * of care. Mishandling override windows may result situations that
 * disrupt the normal workflow of the end user.
 *
 * @param obj The window object
 * @param override If true, the window is overridden
 *
 * @ingroup Win
 */
EAPI void                  elm_win_override_set(Evas_Object *obj, Eina_Bool override);

/**
 * Get the override state of a window.
 *
 * @param obj The window object
 * @return If true, the window is overridden
 *
 * @see elm_win_override_set()
 *
 * @ingroup Win
 */
EAPI Eina_Bool             elm_win_override_get(const Evas_Object *obj);

/**
 * Set the fullscreen state of a window.
 *
 * @param obj The window object
 * @param fullscreen If true, the window is fullscreen
 *
 * @ingroup Win
 */
EAPI void                  elm_win_fullscreen_set(Evas_Object *obj, Eina_Bool fullscreen);

/**
 * Get the fullscreen state of a window.
 *
 * @param obj The window object
 * @return If true, the window is fullscreen
 *
 * @ingroup Win
 */
EAPI Eina_Bool             elm_win_fullscreen_get(const Evas_Object *obj);

/**
 * Set the maximized state of a window.
 *
 * @param obj The window object
 * @param maximized If true, the window is maximized
 *
 * @ingroup Win
 */
EAPI void                  elm_win_maximized_set(Evas_Object *obj, Eina_Bool maximized);

/**
 * Get the maximized state of a window.
 *
 * @param obj The window object
 * @return If true, the window is maximized
 *
 * @ingroup Win
 */
EAPI Eina_Bool             elm_win_maximized_get(const Evas_Object *obj);

/**
 * Set the iconified state of a window.
 *
 * @param obj The window object
 * @param iconified If true, the window is iconified
 *
 * @ingroup Win
 */
EAPI void                  elm_win_iconified_set(Evas_Object *obj, Eina_Bool iconified);

/**
 * Get the iconified state of a window.
 *
 * @param obj The window object
 * @return If true, the window is iconified
 *
 * @ingroup Win
 */
EAPI Eina_Bool             elm_win_iconified_get(const Evas_Object *obj);

/**
 * Set the withdrawn state of a window.
 *
 * @param obj The window object
 * @param withdrawn If true, the window is withdrawn
 *
 * @ingroup Win
 */
EAPI void                  elm_win_withdrawn_set(Evas_Object *obj, Eina_Bool withdrawn);

/**
 * Get the withdrawn state of a window.
 *
 * @param obj The window object
 * @return If true, the window is withdrawn
 *
 * @ingroup Win
 */
EAPI Eina_Bool             elm_win_withdrawn_get(const Evas_Object *obj);

/**
 * Set the urgent state of a window.
 *
 * @param obj The window object
 * @param urgent If true, the window is urgent
 *
 * @ingroup Win
 */
EAPI void                  elm_win_urgent_set(Evas_Object *obj, Eina_Bool urgent);

/**
 * Get the urgent state of a window.
 *
 * @param obj The window object
 * @return If true, the window is urgent
 *
 * @ingroup Win
 */
EAPI Eina_Bool             elm_win_urgent_get(const Evas_Object *obj);

/**
 * Set the demand_attention state of a window.
 *
 * @param obj The window object
 * @param demand_attention If true, the window is demand_attention
 *
 * @ingroup Win
 */
EAPI void                  elm_win_demand_attention_set(Evas_Object *obj, Eina_Bool demand_attention);

/**
 * Get the demand_attention state of a window.
 *
 * @param obj The window object
 * @return If true, the window is demand_attention
 *
 * @ingroup Win
 */
EAPI Eina_Bool             elm_win_demand_attention_get(const Evas_Object *obj);

/**
 * Set the modal state of a window.
 *
 * @param obj The window object
 * @param modal If true, the window is modal
 *
 * @ingroup Win
 */
EAPI void                  elm_win_modal_set(Evas_Object *obj, Eina_Bool modal);

/**
 * Get the modal state of a window.
 *
 * @param obj The window object
 * @return If true, the window is modal
 *
 * @ingroup Win
 */
EAPI Eina_Bool             elm_win_modal_get(const Evas_Object *obj);

/**
 * Set the aspect ratio of a window.
 *
 * @param obj The window object
 * @param aspect If 0, the window has no aspect limits, otherwise it is
 * width divided by height
 *
 * @ingroup Win
 */
EAPI void                  elm_win_aspect_set(Evas_Object *obj, double aspect);

/**
 * Get the aspect ratio of a window.
 *
 * @param obj The window object
 * @return The aspect ratio set (0 by default)
 *
 * @ingroup Win
 */
EAPI double                elm_win_aspect_get(const Evas_Object *obj);

/**
 * Set the base window size used with stepping calculation
 *
 * Base size + stepping is what is calculated for window sizing restrictions.
 * 
 * @param obj The window object
 * @param w The base width
 * @param h The base height
 *
 * @ingroup Win
 * @see elm_win_size_step_set
 * @see elm_win_size_base_get
 * @since 1.7
 */
EAPI void                  elm_win_size_base_set(Evas_Object *obj, int w, int h);

/**
 * Get the base size of a window.
 *
 * @param obj The window object
 * @param w Pointer in which to store returned base width
 * @param h Pointer in which to store returned base height
 *
 * @ingroup Win
 * @see elm_win_size_base_set
 * @see elm_win_size_step_set
 * @since 1.7
 */
EAPI void                  elm_win_size_base_get(Evas_Object *obj, int *w, int *h);

/**
 * Set the window stepping used with sizing calculation
 *
 * Base size + stepping is what is calculated for window sizing restrictions.
 * 
 * @param obj The window object
 * @param w The stepping width (0 disables)
 * @param h The stepping height (0 disables)
 *
 * @ingroup Win
 * @see elm_win_size_step_get
 * @see elm_win_size_base_set
 * @since 1.7
 */
EAPI void                  elm_win_size_step_set(Evas_Object *obj, int w, int h);

/**
 * Get the stepping of a window.
 *
 * @param obj The window object
 * @param w Pointer in which to store returned stepping width
 * @param h Pointer in which to store returned stepping height
 *
 * @ingroup Win
 * @see elm_win_size_base_set
 * @see elm_win_size_step_set
 * @since 1.7
 */
EAPI void                  elm_win_size_step_get(Evas_Object *obj, int *w, int *h);

/**
 * Set the layer of the window.
 *
 * What this means exactly will depend on the underlying engine used.
 *
 * In the case of X11 backed engines, the value in @p layer has the
 * following meanings:
 * @li < 3: The window will be placed below all others.
 * @li > 5: The window will be placed above all others.
 * @li other: The window will be placed in the default layer.
 *
 * @param obj The window object
 * @param layer The layer of the window
 *
 * @ingroup Win
 */
EAPI void                  elm_win_layer_set(Evas_Object *obj, int layer);

/**
 * Get the layer of the window.
 *
 * @param obj The window object
 * @return The layer of the window
 *
 * @see elm_win_layer_set()
 *
 * @ingroup Win
 */
EAPI int                   elm_win_layer_get(const Evas_Object *obj);

/**
 * This pushes (incriments) the norender counter on the window
 * 
 * @param obj The window object
 * 
 * There are some occasions where you wish to suspend rendering on a window.
 * You may be "sleeping" and have nothing to update and do not want animations
 * or other theme side-effects causing rendering to the window while "asleep".
 * You can push (and pop) the norender mode to have this work.
 * 
 * If combined with evas_render_dump(), evas_image_cache_flush() and
 * evas_font_cache_flush() (and maybe edje_file_cache_flush() and 
 * edje_collection_cache_flush()), you can minimize memory footprint
 * significantly while "asleep", and the pausing of rendering ensures
 * evas does not re-load data into memory until needed. When rendering is
 * resumed, data will be re-loaded as needed, which may result in some
 * lag, but does save memory.
 * 
 * @see elm_win_norender_pop()
 * @see elm_win_norender_get()
 * @see elm_win_render()
 * @ingroup Win
 * @since 1.7
 */
EAPI void                  elm_win_norender_push(Evas_Object *obj);

/**
 * This pops (decrements) the norender counter on the window
 * 
 * @param obj The window object
 * 
 * Once norender has gone back to 0, then automatic rendering will continue
 * in the given window. If it is already at 0, this will have no effect.
 * 
 * @see elm_win_norender_push()
 * @see elm_win_norender_get()
 * @see elm_win_render()
 * @ingroup Win
 * @since 1.7
 */
EAPI void                  elm_win_norender_pop(Evas_Object *obj);

/**
 * The retruns how many times norender has been pushed on the window
 * @param obj The window object
 * @return The number of times norender has been pushed
 * 
 * @see elm_win_norender_push()
 * @see elm_win_norender_pop()
 * @see elm_win_render()
 * @ingroup Win
 * @since 1.7
 */
EAPI int                   elm_win_norender_get(Evas_Object *obj);

/**
 * This manually asks evas to render the window now
 * 
 * @param obj The window object
 * 
 * You should NEVER call this unless you really know what you are doing and
 * why. Never call this unless you are asking for performance degredation
 * and possibly weird behavior. Windows get automatically rendered when the
 * application goes idle so there is never a need to call this UNLESS you
 * have enabled "norender" mode.
 * 
 * @see elm_win_norender_push()
 * @see elm_win_norender_pop()
 * @see elm_win_norender_get()
 * @ingroup Win
 * @since 1.7
 */
EAPI void                  elm_win_render(Evas_Object *obj);

/**
 * Set the rotation of the window.
 *
 * Most engines only work with multiples of 90.
 *
 * This function is used to set the orientation of the window @p obj to
 * match that of the screen. The window itself will be resized to adjust
 * to the new geometry of its contents. If you want to keep the window size,
 * see elm_win_rotation_with_resize_set().
 *
 * @param obj The window object
 * @param rotation The rotation of the window, in degrees (0-360),
 * counter-clockwise.
 *
 * @ingroup Win
 */
EAPI void                  elm_win_rotation_set(Evas_Object *obj, int rotation);

/**
 * Rotates the window and resizes it.
 *
 * Like elm_win_rotation_set(), but it also resizes the window's contents so
 * that they fit inside the current window geometry.
 *
 * @param obj The window object
 * @param rotation The rotation of the window in degrees (0-360),
 * counter-clockwise.
 *
 * @ingroup Win
 */
EAPI void                  elm_win_rotation_with_resize_set(Evas_Object *obj, int rotation);

/**
 * Get the rotation of the window.
 *
 * @param obj The window object
 * @return The rotation of the window in degrees (0-360)
 *
 * @see elm_win_rotation_set()
 * @see elm_win_rotation_with_resize_set()
 *
 * @ingroup Win
 */
EAPI int                   elm_win_rotation_get(const Evas_Object *obj);

/**
 * Set the sticky state of the window.
 *
 * Hints the Window Manager that the window in @p obj should be left fixed
 * at its position even when the virtual desktop it's on moves or changes.
 *
 * @param obj The window object
 * @param sticky If true, the window's sticky state is enabled
 *
 * @ingroup Win
 */
EAPI void                  elm_win_sticky_set(Evas_Object *obj, Eina_Bool sticky);

/**
 * Get the sticky state of the window.
 *
 * @param obj The window object
 * @return If true, the window's sticky state is enabled
 *
 * @see elm_win_sticky_set()
 *
 * @ingroup Win
 */
EAPI Eina_Bool             elm_win_sticky_get(const Evas_Object *obj);

/**
 * Set if this window is an illume conformant window
 *
 * @param obj The window object
 * @param conformant The conformant flag (1 = conformant, 0 = non-conformant)
 *
 * @ingroup Win
 */
EAPI void                  elm_win_conformant_set(Evas_Object *obj, Eina_Bool conformant);

/**
 * Get if this window is an illume conformant window
 *
 * @param obj The window object
 * @return A boolean if this window is illume conformant or not
 *
 * @ingroup Win
 */
EAPI Eina_Bool             elm_win_conformant_get(const Evas_Object *obj);

/**
 * Set a window to be an illume quickpanel window
 *
 * By default window objects are not quickpanel windows.
 *
 * @param obj The window object
 * @param quickpanel The quickpanel flag (1 = quickpanel, 0 = normal window)
 *
 * @ingroup Win
 */
EAPI void                  elm_win_quickpanel_set(Evas_Object *obj, Eina_Bool quickpanel);

/**
 * Get if this window is a quickpanel or not
 *
 * @param obj The window object
 * @return A boolean if this window is a quickpanel or not
 *
 * @ingroup Win
 */
EAPI Eina_Bool             elm_win_quickpanel_get(const Evas_Object *obj);

/**
 * Set the major priority of a quickpanel window
 *
 * @param obj The window object
 * @param priority The major priority for this quickpanel
 *
 * @ingroup Win
 */
EAPI void                  elm_win_quickpanel_priority_major_set(Evas_Object *obj, int priority);

/**
 * Get the major priority of a quickpanel window
 *
 * @param obj The window object
 * @return The major priority of this quickpanel
 *
 * @ingroup Win
 */
EAPI int                   elm_win_quickpanel_priority_major_get(const Evas_Object *obj);

/**
 * Set the minor priority of a quickpanel window
 *
 * @param obj The window object
 * @param priority The minor priority for this quickpanel
 *
 * @ingroup Win
 */
EAPI void                  elm_win_quickpanel_priority_minor_set(Evas_Object *obj, int priority);

/**
 * Get the minor priority of a quickpanel window
 *
 * @param obj The window object
 * @return The minor priority of this quickpanel
 *
 * @ingroup Win
 */
EAPI int                   elm_win_quickpanel_priority_minor_get(const Evas_Object *obj);

/**
 * Set which zone this quickpanel should appear in
 *
 * @param obj The window object
 * @param zone The requested zone for this quickpanel
 *
 * @ingroup Win
 */
EAPI void                  elm_win_quickpanel_zone_set(Evas_Object *obj, int zone);

/**
 * Get which zone this quickpanel should appear in
 *
 * @param obj The window object
 * @return The requested zone for this quickpanel
 *
 * @ingroup Win
 */
EAPI int                   elm_win_quickpanel_zone_get(const Evas_Object *obj);

/**
 * Set the window to be skipped by keyboard focus
 *
 * This sets the window to be skipped by normal keyboard input. This means
 * a window manager will be asked to not focus this window as well as omit
 * it from things like the taskbar, pager, "alt-tab" list etc. etc.
 *
 * Call this and enable it on a window BEFORE you show it for the first time,
 * otherwise it may have no effect.
 *
 * Use this for windows that have only output information or might only be
 * interacted with by the mouse or fingers, and never for typing input.
 * Be careful that this may have side-effects like making the window
 * non-accessible in some cases unless the window is specially handled. Use
 * this with care.
 *
 * @param obj The window object
 * @param skip The skip flag state (EINA_TRUE if it is to be skipped)
 *
 * @ingroup Win
 */
EAPI void                  elm_win_prop_focus_skip_set(Evas_Object *obj, Eina_Bool skip);

/**
 * Send a command to the windowing environment
 *
 * This is intended to work in touchscreen or small screen device
 * environments where there is a more simplistic window management policy in
 * place. This uses the window object indicated to select which part of the
 * environment to control (the part that this window lives in), and provides
 * a command and an optional parameter structure (use NULL for this if not
 * needed).
 *
 * @param obj The window object that lives in the environment to control
 * @param command The command to send
 * @param params Optional parameters for the command
 *
 * @ingroup Win
 */
EAPI void                  elm_win_illume_command_send(Evas_Object *obj, Elm_Illume_Command command, void *params);

/**
 * Get the inlined image object handle
 *
 * When you create a window with elm_win_add() of type ELM_WIN_INLINED_IMAGE,
 * then the window is in fact an evas image object inlined in the parent
 * canvas. You can get this object (be careful to not manipulate it as it
 * is under control of elementary), and use it to do things like get pixel
 * data, save the image to a file, etc.
 *
 * @param obj The window object to get the inlined image from
 * @return The inlined image object, or NULL if none exists
 *
 * @ingroup Win
 */
EAPI Evas_Object          *elm_win_inlined_image_object_get(Evas_Object *obj);

/**
 * Determine whether a window has focus
 * @param obj The window to query
 * @return EINA_TRUE if the window exists and has focus, else EINA_FALSE
 *
 * @ingroup Win
 */
EAPI Eina_Bool             elm_win_focus_get(const Evas_Object *obj);

/**
 * Constrain the maximum width and height of a window to the width and height of its screen
 *
 * When @p constrain is true, @p obj will never resize larger than the screen.
 * @param obj The window object
 * @param constrain EINA_TRUE to restrict the window's maximum size, EINA_FALSE to disable restriction
 *
 * @ingroup Win
 */
EAPI void                  elm_win_screen_constrain_set(Evas_Object *obj, Eina_Bool constrain);

/**
 * Retrieve the constraints on the maximum width and height of a window relative to the width and height of its screen
 *
 * When this function returns true, @p obj will never resize larger than the screen.
 * @param obj The window object
 * @return EINA_TRUE to restrict the window's maximum size, EINA_FALSE to disable restriction
 *
 * @ingroup Win
 */
EAPI Eina_Bool             elm_win_screen_constrain_get(Evas_Object *obj);

/**
 * Get screen geometry details for the screen that a window is on
 * @param obj The window to query
 * @param x where to return the horizontal offset value. May be NULL.
 * @param y where to return the vertical offset value. May be NULL.
 * @param w where to return the width value. May be NULL.
 * @param h where to return the height value. May be NULL.
 *
 * @ingroup Win
 */
EAPI void                  elm_win_screen_size_get(const Evas_Object *obj, int *x, int *y, int *w, int *h);

/**
 * Get screen dpi for the screen that a window is on
 * @param obj The window to query
 * @param xdpi Pointer to value to store return horizontal dpi. May be NULL.
 * @param ydpi Pointer to value to store return vertical dpi. May be NULL.
 *
 * @ingroup Win
 * @since 1.7
 */
EAPI void                  elm_win_screen_dpi_get(const Evas_Object *obj, int *xdpi, int *ydpi);

/**
 * Set the enabled status for the focus highlight in a window
 *
 * This function will enable or disable the focus highlight only for the
 * given window, regardless of the global setting for it
 *
 * @param obj The window where to enable the highlight
 * @param enabled The enabled value for the highlight
 *
 * @ingroup Win
 */
EAPI void                  elm_win_focus_highlight_enabled_set(Evas_Object *obj, Eina_Bool enabled);

/**
 * Get the enabled value of the focus highlight for this window
 *
 * @param obj The window in which to check if the focus highlight is enabled
 *
 * @return EINA_TRUE if enabled, EINA_FALSE otherwise
 *
 * @ingroup Win
 */
EAPI Eina_Bool             elm_win_focus_highlight_enabled_get(const Evas_Object *obj);

/**
 * Set the style for the focus highlight on this window
 *
 * Sets the style to use for theming the highlight of focused objects on
 * the given window. If @p style is NULL, the default will be used.
 *
 * @param obj The window where to set the style
 * @param style The style to set
 *
 * @ingroup Win
 */
EAPI void                  elm_win_focus_highlight_style_set(Evas_Object *obj, const char *style);

/**
 * Get the style set for the focus highlight object
 *
 * Gets the style set for this windows highlight object, or NULL if none
 * is set.
 *
 * @param obj The window to retrieve the highlights style from
 *
 * @return The style set or NULL if none was. Default is used in that case.
 *
 * @ingroup Win
 */
EAPI const char           *elm_win_focus_highlight_style_get(const Evas_Object *obj);

/**
 * Sets the keyboard mode of the window.
 *
 * @param obj The window object
 * @param mode The mode to set, one of #Elm_Win_Keyboard_Mode
 *
 * @ingroup Win
 */
EAPI void                  elm_win_keyboard_mode_set(Evas_Object *obj, Elm_Win_Keyboard_Mode mode);

/**
 * Gets the keyboard mode of the window.
 *
 * @param obj The window object
 * @return The mode, one of #Elm_Win_Keyboard_Mode
 *
 * @ingroup Win
 */
EAPI Elm_Win_Keyboard_Mode elm_win_keyboard_mode_get(const Evas_Object *obj);

/**
 * Sets whether the window is a keyboard.
 *
 * @param obj The window object
 * @param is_keyboard If true, the window is a virtual keyboard
 *
 * @ingroup Win
 */
EAPI void                  elm_win_keyboard_win_set(Evas_Object *obj, Eina_Bool is_keyboard);

/**
 * Gets whether the window is a keyboard.
 *
 * @param obj The window object
 * @return If the window is a virtual keyboard
 *
 * @ingroup Win
 */
EAPI Eina_Bool             elm_win_keyboard_win_get(const Evas_Object *obj);

/**
 * Sets the indicator mode of the window.
 *
 * @param obj The window object
 * @param mode The mode to set, one of #Elm_Win_Indicator_Mode
 *
 * @ingroup Win
 */
EAPI void                  elm_win_indicator_mode_set(Evas_Object *obj, Elm_Win_Indicator_Mode mode);

/**
 * Gets the indicator mode of the window.
 *
 * @param obj The window object
 * @return The mode, one of #Elm_Win_Indicator_Mode
 *
 * @ingroup Win
 */
EAPI Elm_Win_Indicator_Mode elm_win_indicator_mode_get(const Evas_Object *obj);

/**
 * Sets the indicator opacity mode of the window.
 *
 * @param obj The window object
 * @param mode The mode to set, one of #Elm_Win_Indicator_Opacity_Mode
 *
 * @ingroup Win
 */
EAPI void                  elm_win_indicator_opacity_set(Evas_Object *obj, Elm_Win_Indicator_Opacity_Mode mode);

/**
 * Gets the indicator opacity mode of the window.
 *
 * @param obj The window object
 * @return The mode, one of #Elm_Win_Indicator_Opacity_Mode
 *
 * @ingroup Win
 */
EAPI Elm_Win_Indicator_Opacity_Mode elm_win_indicator_opacity_get(const Evas_Object *obj);

/**
 * Get the screen position of a window.
 *
 * @param obj The window object
 * @param x The int to store the x coordinate to
 * @param y The int to store the y coordinate to
 *
 * @ingroup Win
 */
EAPI void                  elm_win_screen_position_get(const Evas_Object *obj, int *x, int *y);

/**
 * Create a socket to provide the service for Plug widget
 *
 * @param obj The window object
 * @param svcname The name of the service to be advertised. ensure that it is unique (when combined with @p svcnum) otherwise creation may fail.
 * @param svcnum A number (any value, 0 being the common default) to differentiate multiple instances of services with the same name.
 * @param svcsys A boolean that if true, specifies to create a system-wide service all users can connect to, otherwise the service is private to the user id that created the service.
 * @return If socket creation is successful
 *
 * @ingroup Win
 */
EAPI Eina_Bool             elm_win_socket_listen(Evas_Object *obj, const char *svcname, int svcnum, Eina_Bool svcsys);

/* X specific calls - won't work on non-x engines (return 0) */
/**
 * Get the Ecore_X_Window of an Evas_Object
 *
 * @param obj The object
 *
 * @return The Ecore_X_Window of @p obj
 *
 * @ingroup Win
 */
EAPI Ecore_X_Window elm_win_xwindow_get(const Evas_Object *obj);

/* Wayland specific call - returns NULL on non-Wayland engines */
/**
 * Get the Ecore_Wl_Window of and Evas_Object
 *
 * @param obj the object
 *
 * @return The Ecore_Wl_Window of @p obj
 *
 * @ingroup Win
 */
EAPI Ecore_Wl_Window *elm_win_wl_window_get(const Evas_Object *obj);

/**
 * @typedef Elm_Win_Trap
 *
 * Trap can be set with elm_win_trap_set() and will intercept the
 * calls to internal ecore_evas with the same name and parameters. If
 * there is a trap and it returns @c EINA_TRUE then the call will be
 * allowed, otherwise it will be ignored.
 *
 * @since 1.7
 */
typedef struct _Elm_Win_Trap Elm_Win_Trap;
struct _Elm_Win_Trap
{
#define ELM_WIN_TRAP_VERSION (1UL)
   unsigned long version;
   void *(*add)(Evas_Object *o); /**< object was just added. The returned pointer will be handled to every other trap call. */
   void (*del)(void *data, Evas_Object *o); /**< object will be deleted. */
   Eina_Bool (*hide)(void *data, Evas_Object *o);
   Eina_Bool (*show)(void *data, Evas_Object *o);
   Eina_Bool (*move)(void *data, Evas_Object *o, int x, int y);
   Eina_Bool (*resize)(void *data, Evas_Object *o, int w, int h);
   Eina_Bool (*center)(void *data, Evas_Object *o); /* not in ecore_evas, but nice to trap */
   Eina_Bool (*lower)(void *data, Evas_Object *o);
   Eina_Bool (*raise)(void *data, Evas_Object *o);
   Eina_Bool (*activate)(void *data, Evas_Object *o);
   Eina_Bool (*alpha_set)(void *data, Evas_Object *o, Eina_Bool alpha);
   Eina_Bool (*aspect_set)(void *data, Evas_Object *o, double aspect);
   Eina_Bool (*avoid_damage_set)(void *data, Evas_Object *o, Ecore_Evas_Avoid_Damage_Type on);
   Eina_Bool (*borderless_set)(void *data, Evas_Object *o, Eina_Bool on);
   Eina_Bool (*demand_attention_set)(void *data, Evas_Object *o, Eina_Bool on);
   Eina_Bool (*focus_skip_set)(void *data, Evas_Object *o, Eina_Bool skip);
   Eina_Bool (*fullscreen_set)(void *data, Evas_Object *o, Eina_Bool on);
   Eina_Bool (*iconified_set)(void *data, Evas_Object *o, Eina_Bool on);
   Eina_Bool (*layer_set)(void *data, Evas_Object *o, int layer);
   Eina_Bool (*manual_render_set)(void *data, Evas_Object *o, Eina_Bool manual_render);
   Eina_Bool (*maximized_set)(void *data, Evas_Object *o, Eina_Bool on);
   Eina_Bool (*modal_set)(void *data, Evas_Object *o, Eina_Bool on);
   Eina_Bool (*name_class_set)(void *data, Evas_Object *o, const char *n, const char *c);
   Eina_Bool (*object_cursor_set)(void *data, Evas_Object *o, Evas_Object *obj, int layer, int hot_x, int hot_y);
   Eina_Bool (*override_set)(void *data, Evas_Object *o, Eina_Bool on);
   Eina_Bool (*rotation_set)(void *data, Evas_Object *o, int rot);
   Eina_Bool (*rotation_with_resize_set)(void *data, Evas_Object *o, int rot);
   Eina_Bool (*shaped_set)(void *data, Evas_Object *o, Eina_Bool shaped);
   Eina_Bool (*size_base_set)(void *data, Evas_Object *o, int w, int h);
   Eina_Bool (*size_step_set)(void *data, Evas_Object *o, int w, int h);
   Eina_Bool (*size_min_set)(void *data, Evas_Object *o, int w, int h);
   Eina_Bool (*size_max_set)(void *data, Evas_Object *o, int w, int h);
   Eina_Bool (*sticky_set)(void *data, Evas_Object *o, Eina_Bool sticky);
   Eina_Bool (*title_set)(void *data, Evas_Object *o, const char *t);
   Eina_Bool (*urgent_set)(void *data, Evas_Object *o, Eina_Bool urgent);
   Eina_Bool (*withdrawn_set)(void *data, Evas_Object *o, Eina_Bool withdrawn);
};

/**
 * Sets the trap to be used for internal @c Ecore_Evas management.
 *
 * @param trap the trap to be used or @c NULL to remove traps. Pointer
 *        is not modified or copied, keep it alive.
 * @return @c EINA_TRUE on success, @c EINA_FALSE if there was a
 *         problem, such as invalid version number.
 *
 * @warning this is an advanced feature that you should avoid using.
 *
 * @since 1.7
 */
EAPI Eina_Bool elm_win_trap_set(const Elm_Win_Trap *trap);

/**
 * @}
 */
