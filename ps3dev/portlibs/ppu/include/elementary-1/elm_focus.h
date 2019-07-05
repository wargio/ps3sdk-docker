/**
 * @defgroup Focus Focus
 * @ingroup Elementary
 *
 * An Elementary application has, at all times, one (and only one)
 * @b focused object. This is what determines where the input
 * events go to within the application's window. Also, focused
 * objects can be decorated differently, in order to signal to the
 * user where the input is, at a given moment.
 *
 * Elementary applications also have the concept of <b>focus
 * chain</b>: one can cycle through all the windows' focusable
 * objects by input (tab key) or programmatically. The default
 * focus chain for an application is the one define by the order in
 * which the widgets where added in code. One will cycle through
 * top level widgets, and, for each one containing sub-objects, cycle
 * through them all, before returning to the level
 * above. Elementary also allows one to set @b custom focus chains
 * for their applications.
 *
 * Besides the focused decoration a widget may exhibit, when it
 * gets focus, Elementary has a @b global focus highlight object
 * that can be enabled for a window. If one chooses to do so, this
 * extra highlight effect will surround the current focused object,
 * too.
 *
 * @note Some Elementary widgets are @b unfocusable, after
 * creation, by their very nature: they are not meant to be
 * interacted with input events, but are there just for visual
 * purposes.
 *
 * @ref general_functions_example_page "This" example contemplates
 * some of these functions.
 */

/**
 * Get the whether an Elementary object has the focus or not.
 *
 * @param obj The Elementary object to get the information from
 * @return @c EINA_TRUE, if the object is focused, @c EINA_FALSE if
 *            not (and on errors).
 *
 * @see elm_object_focus_set()
 *
 * @ingroup Focus
 */
EAPI Eina_Bool            elm_object_focus_get(const Evas_Object *obj);

/**
 * Set/unset focus to a given Elementary object.
 *
 * @param obj The Elementary object to operate on.
 * @param focus @c EINA_TRUE Set focus to a given object,
 *              @c EINA_FALSE Unset focus to a given object.
 *
 * @note When you set focus to this object, if it can handle focus, will
 * take the focus away from the one who had it previously and will, for
 * now on, be the one receiving input events. Unsetting focus will remove
 * the focus from @p obj, passing it back to the previous element in the
 * focus chain list.
 *
 * @see elm_object_focus_get(), elm_object_focus_custom_chain_get()
 *
 * @ingroup Focus
 */
EAPI void                 elm_object_focus_set(Evas_Object *obj, Eina_Bool focus);

/**
 * Set the ability for an Elementary object to be focused
 *
 * @param obj The Elementary object to operate on
 * @param enable @c EINA_TRUE if the object can be focused, @c
 *        EINA_FALSE if not (and on errors)
 *
 * This sets whether the object @p obj is able to take focus or
 * not. Unfocusable objects do nothing when programmatically
 * focused, being the nearest focusable parent object the one
 * really getting focus. Also, when they receive mouse input, they
 * will get the event, but not take away the focus from where it
 * was previously.
 *
 * @ingroup Focus
 */
EAPI void                 elm_object_focus_allow_set(Evas_Object *obj, Eina_Bool enable);

/**
 * Get whether an Elementary object is focusable or not
 *
 * @param obj The Elementary object to operate on
 * @return @c EINA_TRUE if the object is allowed to be focused, @c
 *             EINA_FALSE if not (and on errors)
 *
 * @note Objects which are meant to be interacted with by input
 * events are created able to be focused, by default. All the
 * others are not.
 *
 * @ingroup Focus
 */
EAPI Eina_Bool            elm_object_focus_allow_get(const Evas_Object *obj);

/**
 * Set custom focus chain.
 *
 * This function overwrites any previous custom focus chain within
 * the list of objects. The previous list will be deleted and this list
 * will be managed by elementary. After it is set, don't modify it.
 *
 * @note On focus cycle, only will be evaluated children of this container.
 *
 * @param obj The container object
 * @param objs Chain of objects to pass focus
 * @ingroup Focus
 */
EAPI void                 elm_object_focus_custom_chain_set(Evas_Object *obj, Eina_List *objs);

/**
 * Unset a custom focus chain on a given Elementary widget
 *
 * @param obj The container object to remove focus chain from
 *
 * Any focus chain previously set on @p obj (for its child objects)
 * is removed entirely after this call.
 *
 * @ingroup Focus
 */
EAPI void                 elm_object_focus_custom_chain_unset(Evas_Object *obj);

/**
 * Get custom focus chain
 *
 * @param obj The container object
 * @ingroup Focus
 */
EAPI const Eina_List     *elm_object_focus_custom_chain_get(const Evas_Object *obj);

/**
 * Append object to custom focus chain.
 *
 * @note If relative_child equal to NULL or not in custom chain, the object
 * will be added in end.
 *
 * @note On focus cycle, only will be evaluated children of this container.
 *
 * @param obj The container object
 * @param child The child to be added in custom chain
 * @param relative_child The relative object to position the child
 * @ingroup Focus
 */
EAPI void                 elm_object_focus_custom_chain_append(Evas_Object *obj, Evas_Object *child, Evas_Object *relative_child);

/**
 * Prepend object to custom focus chain.
 *
 * @note If relative_child equal to NULL or not in custom chain, the object
 * will be added in begin.
 *
 * @note On focus cycle, only will be evaluated children of this container.
 *
 * @param obj The container object
 * @param child The child to be added in custom chain
 * @param relative_child The relative object to position the child
 * @ingroup Focus
 */
EAPI void                 elm_object_focus_custom_chain_prepend(Evas_Object *obj, Evas_Object *child, Evas_Object *relative_child);

/**
 * Give focus to next object in object tree.
 *
 * Give focus to next object in focus chain of one object sub-tree.
 * If the last object of chain already have focus, the focus will go to the
 * first object of chain.
 *
 * @param obj The object root of sub-tree
 * @param dir Direction to move the focus
 *
 * @ingroup Focus
 */
EAPI void                 elm_object_focus_next(Evas_Object *obj, Elm_Focus_Direction dir);

/**
 * Make the elementary object and its children to be focusable
 * (or unfocusable).
 *
 * @param obj The Elementary object to operate on
 * @param focusable @c EINA_TRUE for focusable,
 *        @c EINA_FALSE for unfocusable.
 *
 * This sets whether the object @p obj and its children objects
 * are able to take focus or not. If the tree is set as unfocusable,
 * newest focused object which is not in this tree will get focus.
 * This API can be helpful for an object to be deleted.
 * When an object will be deleted soon, it and its children may not
 * want to get focus (by focus reverting or by other focus controls).
 * Then, just use this API before deleting.
 *
 * @see elm_object_tree_focus_allow_get()
 *
 * @ingroup Focus
 *
 */
EAPI void                 elm_object_tree_focus_allow_set(Evas_Object *obj, Eina_Bool focusable);

/**
 * Get whether an Elementary object and its children are focusable or not.
 *
 * @param obj The Elementary object to get the information from
 * @return @c EINA_TRUE, if the tree is focusable,
 *         @c EINA_FALSE if not (and on errors).
 *
 * @see elm_object_tree_focus_allow_set()
 *
 * @ingroup Focus
 */
EAPI Eina_Bool            elm_object_tree_focus_allow_get(const Evas_Object *obj);
