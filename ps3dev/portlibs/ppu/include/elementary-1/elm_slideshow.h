/**
 * @defgroup Slideshow Slideshow
 * @ingroup Elementary
 *
 * @image html slideshow_inheritance_tree.png
 * @image latex slideshow_inheritance_tree.eps
 *
 * @image html img/widget/slideshow/preview-00.png
 * @image latex img/widget/slideshow/preview-00.eps
 *
 * This widget, as the name indicates, is a pre-made image
 * slideshow panel, with API functions acting on (child) image
 * items presentation. Between those actions, are:
 * - advance to next/previous image
 * - select the style of image transition animation
 * - set the exhibition time for each image
 * - start/stop the slideshow
 *
 * The transition animations are defined in the widget's theme,
 * consequently new animations can be added without having to
 * update the widget's code.
 *
 * @section Slideshow_Items Slideshow items
 *
 * For slideshow items, just like for @ref Genlist "genlist" ones,
 * the user defines a @b classes, specifying functions that will be
 * called on the item's creation and deletion times.
 *
 * The #Elm_Slideshow_Item_Class structure contains the following
 * members:
 *
 * - @c func.get - When an item is displayed, this function is
 *   called, and it's where one should create the item object, de
 *   facto. For example, the object can be a pure Evas image object
 *   or an Elementary @ref Photocam "photocam" widget.
 *   See #SlideshowItemGetFunc.
 * - @c func.del - When an item is no more displayed, this function
 *   is called, where the user must delete any data associated to
 *   the item. See #SlideshowItemDelFunc.
 *
 * @section Slideshow_Caching Slideshow caching
 *
 * The slideshow provides facilities to have items adjacent to the
 * one being displayed <b>already "realized"</b> (i.e. loaded) for
 * you, so that the system does not have to decode image data
 * anymore at the time it has to actually switch images on its
 * viewport. The user is able to set the numbers of items to be
 * cached @b before and @b after the current item, in the widget's
 * item list.
 *
 * This widget inherits from the @ref Layout one, so that all the
 * functions acting on it also work for slideshow objects.
 *
 * This widget emits the following signals, besides the ones sent from
 * @ref Layout:
 * - @c "changed" - when the slideshow switches its view to a new
 *   item. event_info parameter in callback contains the current visible item
 * - @c "transition,end" - when a slide transition ends. event_info parameter
 *   in callback contains the current visible item
 *
 * List of examples for the slideshow widget:
 * @li @ref slideshow_example
 */

/**
 * @addtogroup Slideshow
 * @{
 */

typedef struct _Elm_Slideshow_Item_Class      Elm_Slideshow_Item_Class; /**< Slideshow item class definition struct */
typedef struct _Elm_Slideshow_Item_Class_Func Elm_Slideshow_Item_Class_Func;    /**< Class functions for slideshow item classes. */
typedef Evas_Object                        *(*SlideshowItemGetFunc)(void *data, Evas_Object *obj); /**< Image fetching class function for slideshow item classes. */
typedef void                                (*SlideshowItemDelFunc)(void *data, Evas_Object *obj); /**< Deletion class function for slideshow item classes. */

/**
 * @struct _Elm_Slideshow_Item_Class
 *
 * Slideshow item class definition. See @ref Slideshow_Items for
 * field details.
 */
struct _Elm_Slideshow_Item_Class
{
   struct _Elm_Slideshow_Item_Class_Func
     {
        SlideshowItemGetFunc get;
        SlideshowItemDelFunc del;
     } func;
};   /**< member definitions of #Elm_Slideshow_Item_Class */

/**
 * Add a new slideshow widget to the given parent Elementary
 * (container) object
 *
 * @param parent The parent object
 * @return A new slideshow widget handle or @c NULL, on errors
 *
 * This function inserts a new slideshow widget on the canvas.
 *
 * @ingroup Slideshow
 */
EAPI Evas_Object          *elm_slideshow_add(Evas_Object *parent);

/**
 * Add (append) a new item in a given slideshow widget.
 *
 * @param obj The slideshow object
 * @param itc The item class for the item
 * @param data The item's data
 * @return A handle to the item added or @c NULL, on errors
 *
 * Add a new item to @p obj's internal list of items, appending it.
 * The item's class must contain the function really fetching the
 * image object to show for this item, which could be an Evas image
 * object or an Elementary photo, for example. The @p data
 * parameter is going to be passed to both class functions of the
 * item.
 *
 * @see #Elm_Slideshow_Item_Class
 * @see elm_slideshow_item_sorted_insert()
 * @see elm_object_item_data_set()
 *
 * @ingroup Slideshow
 */
EAPI Elm_Object_Item      *elm_slideshow_item_add(Evas_Object *obj, const Elm_Slideshow_Item_Class *itc, const void *data);

/**
 * Insert a new item into the given slideshow widget, using the @p func
 * function to sort items (by item handles).
 *
 * @param obj The slideshow object
 * @param itc The item class for the item
 * @param data The item's data
 * @param func The comparing function to be used to sort slideshow
 * items <b>by #Elm_Slideshow_Item_Class item handles</b>
 * @return Returns The slideshow item handle, on success, or
 * @c NULL, on errors
 *
 * Add a new item to @p obj's internal list of items, in a position
 * determined by the @p func comparing function. The item's class
 * must contain the function really fetching the image object to
 * show for this item, which could be an Evas image object or an
 * Elementary photo, for example. The @p data parameter is going to
 * be passed to both class functions of the item.
 *
 * @see #Elm_Slideshow_Item_Class
 * @see elm_slideshow_item_add()
 *
 * @ingroup Slideshow
 */
EAPI Elm_Object_Item      *elm_slideshow_item_sorted_insert(Evas_Object *obj, const Elm_Slideshow_Item_Class *itc, const void *data, Eina_Compare_Cb func);

/**
 * Display a given slideshow widget's item, programmatically.
 *
 * @param it The item to display on @p obj's viewport
 *
 * The change between the current item and @p item will use the
 * transition @p obj is set to use (@see
 * elm_slideshow_transition_set()).
 *
 * @ingroup Slideshow
 */
EAPI void                  elm_slideshow_item_show(Elm_Object_Item *it);

/**
 * Slide to the @b next item, in a given slideshow widget
 *
 * @param obj The slideshow object
 *
 * The sliding animation @p obj is set to use will be the
 * transition effect used, after this call is issued.
 *
 * @note If the end of the slideshow's internal list of items is
 * reached, it'll wrap around to the list's beginning, again.
 *
 * @ingroup Slideshow
 */
EAPI void                  elm_slideshow_next(Evas_Object *obj);

/**
 * Slide to the @b previous item, in a given slideshow widget
 *
 * @param obj The slideshow object
 *
 * The sliding animation @p obj is set to use will be the
 * transition effect used, after this call is issued.
 *
 * @note If the beginning of the slideshow's internal list of items
 * is reached, it'll wrap around to the list's end, again.
 *
 * @ingroup Slideshow
 */
EAPI void                  elm_slideshow_previous(Evas_Object *obj);

/**
 * Returns the list of sliding transition/effect names available, for a
 * given slideshow widget.
 *
 * @param obj The slideshow object
 * @return The list of transitions (list of @b stringshared strings
 * as data)
 *
 * The transitions, which come from @p obj's theme, must be an EDC
 * data item named @c "transitions" on the theme file, with (prefix)
 * names of EDC programs actually implementing them.
 *
 * The available transitions for slideshows on the default theme are:
 * - @c "fade" - the current item fades out, while the new one
 *   fades in to the slideshow's viewport.
 * - @c "black_fade" - the current item fades to black, and just
 *   then, the new item will fade in.
 * - @c "horizontal" - the current item slides horizontally, until
 *   it gets out of the slideshow's viewport, while the new item
 *   comes from the left to take its place.
 * - @c "vertical" - the current item slides vertically, until it
 *   gets out of the slideshow's viewport, while the new item comes
 *   from the bottom to take its place.
 * - @c "square" - the new item starts to appear from the middle of
 *   the current one, but with a tiny size, growing until its
 *   target (full) size and covering the old one.
 *
 * @warning The stringshared strings get no new references
 * exclusive to the user grabbing the list, here, so if you'd like
 * to use them out of this call's context, you'd better @c
 * eina_stringshare_ref() them. Also the list is an internal list and
 * so is only valid for as long as the slideshow object is valid and
 * has not internally changed its list for some reason, so make a
 * copy if you need it around.
 *
 * @see elm_slideshow_transition_set()
 *
 * @ingroup Slideshow
 */
EAPI const Eina_List      *elm_slideshow_transitions_get(const Evas_Object *obj);

/**
 * Set the current slide transition/effect in use for a given
 * slideshow widget
 *
 * @param obj The slideshow object
 * @param transition The new transition's name string
 *
 * If @p transition is implemented in @p obj's theme (i.e., is
 * contained in the list returned by
 * elm_slideshow_transitions_get()), this new sliding effect will
 * be used on the widget.
 *
 * @see elm_slideshow_transitions_get() for more details
 *
 * @ingroup Slideshow
 */
EAPI void                  elm_slideshow_transition_set(Evas_Object *obj, const char *transition);

/**
 * Get the current slide transition/effect in use for a given
 * slideshow widget
 *
 * @param obj The slideshow object
 * @return The current transition's name
 *
 * @see elm_slideshow_transition_set() for more details
 *
 * @ingroup Slideshow
 */
EAPI const char           *elm_slideshow_transition_get(const Evas_Object *obj);

/**
 * Set the interval between each image transition on a given
 * slideshow widget, <b>and start the slideshow, itself</b>
 *
 * @param obj The slideshow object
 * @param timeout The new displaying timeout for images
 *
 * After this call, the slideshow widget will start cycling its
 * view, sequentially and automatically, with the images of the
 * items it has. The time between each new image displayed is going
 * to be @p timeout, in @b seconds. If a different timeout was set
 * previously and an slideshow was in progress, it will continue
 * with the new time between transitions, after this call.
 *
 * @note A value less than or equal to 0 on @p timeout will disable
 * the widget's internal timer, thus halting any slideshow which
 * could be happening on @p obj.
 *
 * @see elm_slideshow_timeout_get()
 *
 * @ingroup Slideshow
 */
EAPI void                  elm_slideshow_timeout_set(Evas_Object *obj, double timeout);

/**
 * Get the interval set for image transitions on a given slideshow
 * widget.
 *
 * @param obj The slideshow object
 * @return Returns the timeout set on it
 *
 * @see elm_slideshow_timeout_set() for more details
 *
 * @ingroup Slideshow
 */
EAPI double                elm_slideshow_timeout_get(const Evas_Object *obj);

/**
 * Set if, after a slideshow is started, for a given slideshow
 * widget, its items should be displayed cyclically or not.
 *
 * @param obj The slideshow object
 * @param loop Use @c EINA_TRUE to make it cycle through items or
 * @c EINA_FALSE for it to stop at the end of @p obj's internal
 * list of items
 *
 * @note elm_slideshow_next() and elm_slideshow_previous() will @b
 * ignore what is set by this functions, i.e., they'll @b always
 * cycle through items. This affects only the "automatic"
 * slideshow, as set by elm_slideshow_timeout_set().
 *
 * @see elm_slideshow_loop_get()
 *
 * @ingroup Slideshow
 */
EAPI void                  elm_slideshow_loop_set(Evas_Object *obj, Eina_Bool loop);

/**
 * Get if, after a slideshow is started, for a given slideshow
 * widget, its items are to be displayed cyclically or not.
 *
 * @param obj The slideshow object
 * @return @c EINA_TRUE, if the items in @p obj will be cycled
 * through or @c EINA_FALSE, otherwise
 *
 * @see elm_slideshow_loop_set() for more details
 *
 * @ingroup Slideshow
 */
EAPI Eina_Bool             elm_slideshow_loop_get(const Evas_Object *obj);

/**
 * Remove all items from a given slideshow widget
 *
 * @param obj The slideshow object
 *
 * This removes (and deletes) all items in @p obj, leaving it
 * empty.
 *
 * @see elm_object_item_del(), to remove just one item.
 *
 * @ingroup Slideshow
 */
EAPI void                  elm_slideshow_clear(Evas_Object *obj);

/**
 * Get the internal list of items in a given slideshow widget.
 *
 * @param obj The slideshow object
 * @return The list of items (#Elm_Object_Item as data) or
 * @c NULL on errors.
 *
 * This list is @b not to be modified in any way and must not be
 * freed. Use the list members with functions like
 * elm_object_item_del(), elm_object_item_data_get().
 *
 * @warning This list is only valid until @p obj object's internal
 * items list is changed. It should be fetched again with another
 * call to this function when changes happen.
 *
 * @ingroup Slideshow
 */
EAPI const Eina_List      *elm_slideshow_items_get(const Evas_Object *obj);

/**
 * Returns the currently displayed item, in a given slideshow widget
 *
 * @param obj The slideshow object
 * @return A handle to the item being displayed in @p obj or
 * @c NULL, if none is (and on errors)
 *
 * @ingroup Slideshow
 */
EAPI Elm_Object_Item      *elm_slideshow_item_current_get(const Evas_Object *obj);

/**
 * Get the real Evas object created to implement the view of a
 * given slideshow item
 *
 * @param it The slideshow item.
 * @return the Evas object implementing this item's view.
 *
 * This returns the actual Evas object used to implement the
 * specified slideshow item's view. This may be @c NULL, as it may
 * not have been created or may have been deleted, at any time, by
 * the slideshow. <b>Do not modify this object</b> (move, resize,
 * show, hide, etc.), as the slideshow is controlling it. This
 * function is for querying, emitting custom signals or hooking
 * lower level callbacks for events on that object. Do not delete
 * this object under any circumstances.
 *
 * @see elm_object_item_data_get()
 *
 * @ingroup Slideshow
 */
EAPI Evas_Object          *elm_slideshow_item_object_get(const Elm_Object_Item *it);

/**
 * Get the the item, in a given slideshow widget, placed at
 * position @p nth, in its internal items list
 *
 * @param obj The slideshow object
 * @param nth The number of the item to grab a handle to (0 being
 * the first)
 * @return The item stored in @p obj at position @p nth or @c NULL,
 * if there's no item with that index (and on errors)
 *
 * @ingroup Slideshow
 */
EAPI Elm_Object_Item      *elm_slideshow_item_nth_get(const Evas_Object *obj, unsigned int nth);

/**
 * Set the current slide layout in use for a given slideshow widget
 *
 * @param obj The slideshow object
 * @param layout The new layout's name string
 *
 * If @p layout is implemented in @p obj's theme (i.e., is contained
 * in the list returned by elm_slideshow_layouts_get()), this new
 * images layout will be used on the widget.
 *
 * @see elm_slideshow_layouts_get() for more details
 *
 * @ingroup Slideshow
 */
EAPI void                  elm_slideshow_layout_set(Evas_Object *obj, const char *layout);

/**
 * Get the current slide layout in use for a given slideshow widget
 *
 * @param obj The slideshow object
 * @return The current layout's name
 *
 * @see elm_slideshow_layout_set() for more details
 *
 * @ingroup Slideshow
 */
EAPI const char           *elm_slideshow_layout_get(const Evas_Object *obj);

/**
 * Returns the list of @b layout names available, for a given
 * slideshow widget.
 *
 * @param obj The slideshow object
 * @return The list of layouts (list of @b stringshared strings
 * as data)
 *
 * Slideshow layouts will change how the widget is to dispose each
 * image item in its viewport, with regard to cropping, scaling,
 * etc.
 *
 * The layouts, which come from @p obj's theme, must be an EDC
 * data item name @c "layouts" on the theme file, with (prefix)
 * names of EDC programs actually implementing them.
 *
 * The available layouts for slideshows on the default theme are:
 * - @c "fullscreen" - item images with original aspect, scaled to
 *   touch top and down slideshow borders or, if the image's height
 *   is not enough, left and right slideshow borders.
 * - @c "not_fullscreen" - the same behavior as the @c "fullscreen"
 *   one, but always leaving 10% of the slideshow's dimensions of
 *   distance between the item image's borders and the slideshow
 *   borders, for each axis.
 *
 * @warning The stringshared strings get no new references
 * exclusive to the user grabbing the list, here, so if you'd like
 * to use them out of this call's context, you'd better @c
 * eina_stringshare_ref() them.
 *
 * @see elm_slideshow_layout_set()
 *
 * @ingroup Slideshow
 */
EAPI const Eina_List      *elm_slideshow_layouts_get(const Evas_Object *obj);

/**
 * Set the number of items to cache, on a given slideshow widget,
 * <b>before the current item</b>
 *
 * @param obj The slideshow object
 * @param count Number of items to cache before the current one
 *
 * The default value for this property is @c 2. See
 * @ref Slideshow_Caching "slideshow caching" for more details.
 *
 * @see elm_slideshow_cache_before_get()
 *
 * @ingroup Slideshow
 */
EAPI void                  elm_slideshow_cache_before_set(Evas_Object *obj, int count);

/**
 * Retrieve the number of items to cache, on a given slideshow widget,
 * <b>before the current item</b>
 *
 * @param obj The slideshow object
 * @return The number of items set to be cached before the current one
 *
 * @see elm_slideshow_cache_before_set() for more details
 *
 * @ingroup Slideshow
 */
EAPI int                   elm_slideshow_cache_before_get(const Evas_Object *obj);

/**
 * Set the number of items to cache, on a given slideshow widget,
 * <b>after the current item</b>
 *
 * @param obj The slideshow object
 * @param count Number of items to cache after the current one
 *
 * The default value for this property is @c 2. See
 * @ref Slideshow_Caching "slideshow caching" for more details.
 *
 * @see elm_slideshow_cache_after_get()
 *
 * @ingroup Slideshow
 */
EAPI void                  elm_slideshow_cache_after_set(Evas_Object *obj, int count);

/**
 * Retrieve the number of items to cache, on a given slideshow widget,
 * <b>after the current item</b>
 *
 * @param obj The slideshow object
 * @return The number of items set to be cached after the current one
 *
 * @see elm_slideshow_cache_after_set() for more details
 *
 * @ingroup Slideshow
 */
EAPI int                   elm_slideshow_cache_after_get(const Evas_Object *obj);

/**
 * Get the number of items stored in a given slideshow widget
 *
 * @param obj The slideshow object
 * @return The number of items on @p obj, at the moment of this call
 *
 * @ingroup Slideshow
 */
EAPI unsigned int          elm_slideshow_count_get(const Evas_Object *obj);

/**
 * @}
 */
