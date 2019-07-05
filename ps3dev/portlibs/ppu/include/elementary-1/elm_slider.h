/**
 * @defgroup Slider Slider
 * @ingroup Elementary
 *
 * @image html slider_inheritance_tree.png
 * @image latex slider_inheritance_tree.eps
 *
 * @image html img/widget/slider/preview-00.png
 * @image latex img/widget/slider/preview-00.eps width=\textwidth
 *
 * The slider adds a draggable “slider” widget for selecting the value of
 * something within a range.
 *
 * A slider can be horizontal or vertical. It can contain an Icon and has a
 * primary label as well as a units label (that is formatted with floating
 * point values and thus accepts a printf-style format string, like
 * “%1.2f units”. There is also an indicator string that may be somewhere
 * else (like on the slider itself) that also accepts a format string like
 * units. Label, Icon Unit and Indicator strings/objects are optional.
 *
 * A slider may be inverted which means values invert, with high vales being
 * on the left or top and low values on the right or bottom (as opposed to
 * normally being low on the left or top and high on the bottom and right).
 *
 * The slider should have its minimum and maximum values set by the
 * application with  elm_slider_min_max_set() and value should also be set by
 * the application before use with  elm_slider_value_set(). The span of the
 * slider is its length (horizontally or vertically). This will be scaled by
 * the object or applications scaling factor. At any point code can query the
 * slider for its value with elm_slider_value_get().
 *
 * This widget inherits from the @ref Layout one, so that all the
 * functions acting on it also work for slider objects.
 *
 * This widget emits the following signals, besides the ones sent from
 * @ref Layout:
 * - @c "changed" - Whenever the slider value is changed by the user.
 * - @c "slider,drag,start" - dragging the slider indicator around has started.
 * - @c "slider,drag,stop" - dragging the slider indicator around has stopped.
 * - @c "delay,changed" - A short time after the value is changed by the user.
 * This will be called only when the user stops dragging for
 * a very short period or when they release their
 * finger/mouse, so it avoids possibly expensive reactions to
 * the value change.
 *
 * Available styles for it:
 * - @c "default"
 *
 * Default content parts of the slider widget that you can use for are:
 * @li "icon" - An icon of the slider
 * @li "end" - A end part content of the slider
 *
 * Default text parts of the slider widget that you can use for are:
 * @li "default" - Label of the slider
 *
 * Supported elm_object common APIs.
 * @li @ref elm_object_disabled_set
 * @li @ref elm_object_disabled_get
 * @li @ref elm_object_part_text_set
 * @li @ref elm_object_part_text_get
 * @li @ref elm_object_part_content_set
 * @li @ref elm_object_part_content_get
 * @li @ref elm_object_part_content_unset
 *
 * Here is an example on its usage:
 * @li @ref slider_example
 */

/**
 * @addtogroup Slider
 * @{
 */

/**
 * Add a new slider widget to the given parent Elementary
 * (container) object.
 *
 * @param parent The parent object.
 * @return a new slider widget handle or @c NULL, on errors.
 *
 * This function inserts a new slider widget on the canvas.
 *
 * @ingroup Slider
 */
EAPI Evas_Object                 *elm_slider_add(Evas_Object *parent);

/**
 * Set the (exact) length of the bar region of a given slider widget.
 *
 * @param obj The slider object.
 * @param size The length of the slider's bar region.
 *
 * This sets the minimum width (when in horizontal mode) or height
 * (when in vertical mode) of the actual bar area of the slider
 * @p obj. This in turn affects the object's minimum size. Use
 * this when you're not setting other size hints expanding on the
 * given direction (like weight and alignment hints) and you would
 * like it to have a specific size.
 *
 * @note Icon, end, label, indicator and unit text around @p obj
 * will require their
 * own space, which will make @p obj to require more the @p size,
 * actually.
 *
 * @see elm_slider_span_size_get()
 *
 * @ingroup Slider
 */
EAPI void                         elm_slider_span_size_set(Evas_Object *obj, Evas_Coord size);

/**
 * Get the length set for the bar region of a given slider widget
 *
 * @param obj The slider object.
 * @return The length of the slider's bar region.
 *
 * If that size was not set previously, with
 * elm_slider_span_size_set(), this call will return @c 0.
 *
 * @ingroup Slider
 */
EAPI Evas_Coord                   elm_slider_span_size_get(const Evas_Object *obj);

/**
 * Set the format string for the unit label.
 *
 * @param obj The slider object.
 * @param format The format string for the unit display.
 *
 * Unit label is displayed all the time, if set, after slider's bar.
 * In horizontal mode, at right and in vertical mode, at bottom.
 *
 * If @c NULL, unit label won't be visible. If not it sets the format
 * string for the label text. To the label text is provided a floating point
 * value, so the label text can display up to 1 floating point value.
 * Note that this is optional.
 *
 * Use a format string such as "%1.2f meters" for example, and it will
 * display values like: "3.14 meters" for a value equal to 3.14159.
 *
 * Default is unit label disabled.
 *
 * @see elm_slider_indicator_format_get()
 *
 * @ingroup Slider
 */
EAPI void                         elm_slider_unit_format_set(Evas_Object *obj, const char *format);

/**
 * Get the unit label format of the slider.
 *
 * @param obj The slider object.
 * @return The unit label format string in UTF-8.
 *
 * Unit label is displayed all the time, if set, after slider's bar.
 * In horizontal mode, at right and in vertical mode, at bottom.
 *
 * @see elm_slider_unit_format_set() for more
 * information on how this works.
 *
 * @ingroup Slider
 */
EAPI const char                  *elm_slider_unit_format_get(const Evas_Object *obj);

/**
 * Set the format string for the indicator label.
 *
 * @param obj The slider object.
 * @param indicator The format string for the indicator display.
 *
 * The slider may display its value somewhere else then unit label,
 * for example, above the slider knob that is dragged around. This function
 * sets the format string used for this.
 *
 * If @c NULL, indicator label won't be visible. If not it sets the format
 * string for the label text. To the label text is provided a floating point
 * value, so the label text can display up to 1 floating point value.
 * Note that this is optional.
 *
 * Use a format string such as "%1.2f meters" for example, and it will
 * display values like: "3.14 meters" for a value equal to 3.14159.
 *
 * Default is indicator label disabled.
 *
 * @see elm_slider_indicator_format_get()
 *
 * @ingroup Slider
 */
EAPI void                         elm_slider_indicator_format_set(Evas_Object *obj, const char *indicator);

/**
 * Get the indicator label format of the slider.
 *
 * @param obj The slider object.
 * @return The indicator label format string in UTF-8.
 *
 * The slider may display its value somewhere else then unit label,
 * for example, above the slider knob that is dragged around. This function
 * gets the format string used for this.
 *
 * @see elm_slider_indicator_format_set() for more
 * information on how this works.
 *
 * @ingroup Slider
 */
EAPI const char                  *elm_slider_indicator_format_get(const Evas_Object *obj);

/**
 * Set the format function pointer for the indicator label
 *
 * @param obj The slider object.
 * @param func The indicator format function.
 * @param free_func The freeing function for the format string.
 *
 * Set the callback function to format the indicator string.
 *
 * @see elm_slider_indicator_format_set() for more info on how this works.
 *
 * @ingroup Slider
 */
EAPI void                         elm_slider_indicator_format_function_set(Evas_Object *obj, char *(*func)(double val), void (*free_func)(char *str));

/**
 * Set the format function pointer for the units label
 *
 * @param obj The slider object.
 * @param func The units format function.
 * @param free_func The freeing function for the format string.
 *
 * Set the callback function to format the units string.
 *
 * @see elm_slider_unit_format_set() for more info on how this works.
 *
 * @ingroup Slider
 */
EAPI void                         elm_slider_units_format_function_set(Evas_Object *obj, char *(*func)(double val), void (*free_func)(char *str));

/**
 * Set the orientation of a given slider widget.
 *
 * @param obj The slider object.
 * @param horizontal Use @c EINA_TRUE to make @p obj to be
 * @b horizontal, @c EINA_FALSE to make it @b vertical.
 *
 * Use this function to change how your slider is to be
 * disposed: vertically or horizontally.
 *
 * By default it's displayed horizontally.
 *
 * @see elm_slider_horizontal_get()
 *
 * @ingroup Slider
 */
EAPI void                         elm_slider_horizontal_set(Evas_Object *obj, Eina_Bool horizontal);

/**
 * Retrieve the orientation of a given slider widget
 *
 * @param obj The slider object.
 * @return @c EINA_TRUE, if @p obj is set to be @b horizontal,
 * @c EINA_FALSE if it's @b vertical (and on errors).
 *
 * @see elm_slider_horizontal_set() for more details.
 *
 * @ingroup Slider
 */
EAPI Eina_Bool                    elm_slider_horizontal_get(const Evas_Object *obj);

/**
 * Set the minimum and maximum values for the slider.
 *
 * @param obj The slider object.
 * @param min The minimum value.
 * @param max The maximum value.
 *
 * Define the allowed range of values to be selected by the user.
 *
 * If actual value is less than @p min, it will be updated to @p min. If it
 * is bigger then @p max, will be updated to @p max. Actual value can be
 * get with elm_slider_value_get().
 *
 * By default, min is equal to 0.0, and max is equal to 1.0.
 *
 * @warning Maximum must be greater than minimum, otherwise behavior
 * is undefined.
 *
 * @see elm_slider_min_max_get()
 *
 * @ingroup Slider
 */
EAPI void                         elm_slider_min_max_set(Evas_Object *obj, double min, double max);

/**
 * Get the minimum and maximum values of the slider.
 *
 * @param obj The slider object.
 * @param min Pointer to store the minimum value.
 * @param max Pointer to store the maximum value.
 *
 * @note If only one value is needed, the other pointer can be passed
 * as @c NULL.
 *
 * @see elm_slider_min_max_set() for details.
 *
 * @ingroup Slider
 */
EAPI void                         elm_slider_min_max_get(const Evas_Object *obj, double *min, double *max);

/**
 * Set the value the slider displays.
 *
 * @param obj The slider object.
 * @param val The value to be displayed.
 *
 * Value will be presented on the unit label following format specified with
 * elm_slider_unit_format_set() and on indicator with
 * elm_slider_indicator_format_set().
 *
 * @warning The value must to be between min and max values. This values
 * are set by elm_slider_min_max_set().
 *
 * @see elm_slider_value_get()
 * @see elm_slider_unit_format_set()
 * @see elm_slider_indicator_format_set()
 * @see elm_slider_min_max_set()
 *
 * @ingroup Slider
 */
EAPI void                         elm_slider_value_set(Evas_Object *obj, double val);

/**
 * Get the value displayed by the spinner.
 *
 * @param obj The spinner object.
 * @return The value displayed.
 *
 * @see elm_spinner_value_set() for details.
 *
 * @ingroup Slider
 */
EAPI double                       elm_slider_value_get(const Evas_Object *obj);

/**
 * Invert a given slider widget's displaying values order
 *
 * @param obj The slider object.
 * @param inverted Use @c EINA_TRUE to make @p obj inverted,
 * @c EINA_FALSE to bring it back to default, non-inverted values.
 *
 * A slider may be @b inverted, in which state it gets its
 * values inverted, with high vales being on the left or top and
 * low values on the right or bottom, as opposed to normally have
 * the low values on the former and high values on the latter,
 * respectively, for horizontal and vertical modes.
 *
 * @see elm_slider_inverted_get()
 *
 * @ingroup Slider
 */
EAPI void                         elm_slider_inverted_set(Evas_Object *obj, Eina_Bool inverted);

/**
 * Get whether a given slider widget's displaying values are
 * inverted or not.
 *
 * @param obj The slider object.
 * @return @c EINA_TRUE, if @p obj has inverted values,
 * @c EINA_FALSE otherwise (and on errors).
 *
 * @see elm_slider_inverted_set() for more details.
 *
 * @ingroup Slider
 */
EAPI Eina_Bool                    elm_slider_inverted_get(const Evas_Object *obj);

/**
 * Set whether to enlarge slider indicator (augmented knob) or not.
 *
 * @param obj The slider object.
 * @param show @c EINA_TRUE will make it enlarge, @c EINA_FALSE will
 * let the knob always at default size.
 *
 * By default, indicator will be bigger while dragged by the user.
 *
 * @warning It won't display values set with
 * elm_slider_indicator_format_set() if you disable indicator.
 *
 * @ingroup Slider
 */
EAPI void                         elm_slider_indicator_show_set(Evas_Object *obj, Eina_Bool show);

/**
 * Get whether a given slider widget's enlarging indicator or not.
 *
 * @param obj The slider object.
 * @return @c EINA_TRUE, if @p obj is enlarging indicator, or
 * @c EINA_FALSE otherwise (and on errors).
 *
 * @see elm_slider_indicator_show_set() for details.
 *
 * @ingroup Slider
 */
EAPI Eina_Bool                    elm_slider_indicator_show_get(const Evas_Object *obj);

/**
 * @}
 */
