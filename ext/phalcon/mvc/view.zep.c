
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/object.h"
#include "kernel/memory.h"
#include "kernel/operators.h"
#include "kernel/fcall.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"
#include "kernel/array.h"
#include "kernel/file.h"
#include "kernel/concat.h"
#include "kernel/string.h"
#include "Zend/zend_closures.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */
/**
 * Phalcon\Mvc\View
 *
 * Phalcon\Mvc\View is a class for working with the "view" portion of the
 * model-view-controller pattern. That is, it exists to help keep the view
 * script separate from the model and controller scripts. It provides a system
 * of helpers, output filters, and variable escaping.
 *
 * ```php
 * use Phalcon\Mvc\View;
 *
 * $view = new View();
 *
 * // Setting views directory
 * $view->setViewsDir("app/views/");
 *
 * $view->start();
 *
 * // Shows recent posts view (app/views/posts/recent.phtml)
 * $view->render("posts", "recent");
 * $view->finish();
 *
 * // Printing views output
 * echo $view->getContent();
 * ```
 */
ZEPHIR_INIT_CLASS(Phalcon_Mvc_View)
{
	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Mvc, View, phalcon, mvc_view, phalcon_di_injectable_ce, phalcon_mvc_view_method_entry, 0);

	/**
	 * @var string
	 */
	zend_declare_property_null(phalcon_mvc_view_ce, SL("actionName"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_view_ce, SL("activeRenderPaths"), ZEND_ACC_PROTECTED);
	/**
	 * @var string
	 */
	zend_declare_property_string(phalcon_mvc_view_ce, SL("basePath"), "", ZEND_ACC_PROTECTED);
	/**
	 * @var string
	 */
	zend_declare_property_string(phalcon_mvc_view_ce, SL("content"), "", ZEND_ACC_PROTECTED);
	/**
	 * @var string
	 */
	zend_declare_property_null(phalcon_mvc_view_ce, SL("controllerName"), ZEND_ACC_PROTECTED);
	/**
	 * @var int
	 */
	zend_declare_property_long(phalcon_mvc_view_ce, SL("currentRenderLevel"), 0, ZEND_ACC_PROTECTED);
	/**
	 * @var bool
	 */
	zend_declare_property_bool(phalcon_mvc_view_ce, SL("disabled"), 0, ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_view_ce, SL("disabledLevels"), ZEND_ACC_PROTECTED);
	/**
	 * @var array|bool
	 */
	zend_declare_property_bool(phalcon_mvc_view_ce, SL("engines"), 0, ZEND_ACC_PROTECTED);
	/**
	 * @var ManagerInterface|null
	 */
	zend_declare_property_null(phalcon_mvc_view_ce, SL("eventsManager"), ZEND_ACC_PROTECTED);
	/**
	 * @var string|null
	 */
	zend_declare_property_null(phalcon_mvc_view_ce, SL("layout"), ZEND_ACC_PROTECTED);
	/**
	 * @var string
	 */
	zend_declare_property_string(phalcon_mvc_view_ce, SL("layoutsDir"), "", ZEND_ACC_PROTECTED);
	/**
	 * @var string
	 */
	zend_declare_property_string(phalcon_mvc_view_ce, SL("mainView"), "index", ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_view_ce, SL("options"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_view_ce, SL("params"), ZEND_ACC_PROTECTED);
	/**
	 * @var array|null
	 */
	zend_declare_property_null(phalcon_mvc_view_ce, SL("pickView"), ZEND_ACC_PROTECTED);
	/**
	 * @var string
	 */
	zend_declare_property_string(phalcon_mvc_view_ce, SL("partialsDir"), "", ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_view_ce, SL("registeredEngines"), ZEND_ACC_PROTECTED);
	/**
	 * @var int
	 */
	zend_declare_property_long(phalcon_mvc_view_ce, SL("renderLevel"), 5, ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_view_ce, SL("templatesAfter"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_view_ce, SL("templatesBefore"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_view_ce, SL("viewsDirs"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_view_ce, SL("viewParams"), ZEND_ACC_PROTECTED);
	phalcon_mvc_view_ce->create_object = zephir_init_properties_Phalcon_Mvc_View;
	/**
	 * Render Level: To the action view
	 */
	zephir_declare_class_constant_long(phalcon_mvc_view_ce, SL("LEVEL_ACTION_VIEW"), 1);

	/**
	 * Render Level: To the templates "before"
	 */
	zephir_declare_class_constant_long(phalcon_mvc_view_ce, SL("LEVEL_BEFORE_TEMPLATE"), 2);

	/**
	 * Render Level: To the controller layout
	 */
	zephir_declare_class_constant_long(phalcon_mvc_view_ce, SL("LEVEL_LAYOUT"), 3);

	/**
	 * Render Level: To the main layout
	 */
	zephir_declare_class_constant_long(phalcon_mvc_view_ce, SL("LEVEL_MAIN_LAYOUT"), 5);

	/**
	 * Render Level: No render any view
	 */
	zephir_declare_class_constant_long(phalcon_mvc_view_ce, SL("LEVEL_NO_RENDER"), 0);

	/**
	 * Render Level: Render to the templates "after"
	 */
	zephir_declare_class_constant_long(phalcon_mvc_view_ce, SL("LEVEL_AFTER_TEMPLATE"), 4);

	zend_class_implements(phalcon_mvc_view_ce, 1, phalcon_mvc_viewinterface_ce);
	zend_class_implements(phalcon_mvc_view_ce, 1, phalcon_events_eventsawareinterface_ce);
	return SUCCESS;
}

/**
 * Phalcon\Mvc\View constructor
 */
PHP_METHOD(Phalcon_Mvc_View, __construct)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *options_param = NULL;
	zval options;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&options);
	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_ARRAY(options)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 1, &options_param);
	if (!options_param) {
		ZEPHIR_INIT_VAR(&options);
		array_init(&options);
	} else {
		zephir_get_arrval(&options, options_param);
	}
	zephir_update_property_zval(this_ptr, ZEND_STRL("options"), &options);
	ZEPHIR_MM_RESTORE();
}

/**
 * Magic method to retrieve a variable passed to the view
 *
 *```php
 * echo $this->view->products;
 *```
 */
PHP_METHOD(Phalcon_Mvc_View, __get)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *key_param = NULL;
	zval key;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(key)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &key_param);
	if (UNEXPECTED(Z_TYPE_P(key_param) != IS_STRING && Z_TYPE_P(key_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'key' must be of the type string"));
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(key_param) == IS_STRING)) {
		zephir_get_strval(&key, key_param);
	} else {
		ZEPHIR_INIT_VAR(&key);
	}
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "getvar", NULL, 0, &key);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Magic method to retrieve if a variable is set in the view
 *
 *```php
 * echo isset($this->view->products);
 *```
 */
PHP_METHOD(Phalcon_Mvc_View, __isset)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *key_param = NULL, _0;
	zval key;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(key)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &key_param);
	if (UNEXPECTED(Z_TYPE_P(key_param) != IS_STRING && Z_TYPE_P(key_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'key' must be of the type string"));
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(key_param) == IS_STRING)) {
		zephir_get_strval(&key, key_param);
	} else {
		ZEPHIR_INIT_VAR(&key);
	}
	zephir_read_property(&_0, this_ptr, ZEND_STRL("viewParams"), PH_NOISY_CC | PH_READONLY);
	RETURN_MM_BOOL(zephir_array_isset(&_0, &key));
}

/**
 * Magic method to pass variables to the views
 *
 *```php
 * $this->view->products = $products;
 *```
 */
PHP_METHOD(Phalcon_Mvc_View, __set)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *key_param = NULL, *value, value_sub;
	zval key;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&value_sub);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(key)
		Z_PARAM_ZVAL(value)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &key_param, &value);
	if (UNEXPECTED(Z_TYPE_P(key_param) != IS_STRING && Z_TYPE_P(key_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'key' must be of the type string"));
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(key_param) == IS_STRING)) {
		zephir_get_strval(&key, key_param);
	} else {
		ZEPHIR_INIT_VAR(&key);
	}
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setvar", NULL, 0, &key, value);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();
}

/**
 * Resets any template before layouts
 */
PHP_METHOD(Phalcon_Mvc_View, cleanTemplateAfter)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_INIT_VAR(&_0);
	array_init(&_0);
	zephir_update_property_zval(this_ptr, ZEND_STRL("templatesAfter"), &_0);
	RETURN_THIS();
}

/**
 * Resets any "template before" layouts
 */
PHP_METHOD(Phalcon_Mvc_View, cleanTemplateBefore)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_INIT_VAR(&_0);
	array_init(&_0);
	zephir_update_property_zval(this_ptr, ZEND_STRL("templatesBefore"), &_0);
	RETURN_THIS();
}

/**
 * Disables a specific level of rendering
 *
 *```php
 * // Render all levels except ACTION level
 * $this->view->disableLevel(
 *     View::LEVEL_ACTION_VIEW
 * );
 *```
 */
PHP_METHOD(Phalcon_Mvc_View, disableLevel)
{
	zval *level, level_sub, __$true;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&level_sub);
	ZVAL_BOOL(&__$true, 1);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(level)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &level);
	if (Z_TYPE_P(level) == IS_ARRAY) {
		zephir_update_property_zval(this_ptr, ZEND_STRL("disabledLevels"), level);
	} else {
		zephir_update_property_array(this_ptr, SL("disabledLevels"), level, &__$true);
	}
	RETURN_THISW();
}

/**
 * Disables the auto-rendering process
 */
PHP_METHOD(Phalcon_Mvc_View, disable)
{
	zval __$true, __$false;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	if (1) {
		zephir_update_property_zval(this_ptr, ZEND_STRL("disabled"), &__$true);
	} else {
		zephir_update_property_zval(this_ptr, ZEND_STRL("disabled"), &__$false);
	}
	RETURN_THISW();
}

/**
 * Enables the auto-rendering process
 */
PHP_METHOD(Phalcon_Mvc_View, enable)
{
	zval __$true, __$false;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	if (0) {
		zephir_update_property_zval(this_ptr, ZEND_STRL("disabled"), &__$true);
	} else {
		zephir_update_property_zval(this_ptr, ZEND_STRL("disabled"), &__$false);
	}
	RETURN_THISW();
}

/**
 * Checks whether view exists
 * @deprecated
 */
PHP_METHOD(Phalcon_Mvc_View, exists)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *view_param = NULL;
	zval view;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&view);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(view)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &view_param);
	if (UNEXPECTED(Z_TYPE_P(view_param) != IS_STRING && Z_TYPE_P(view_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'view' must be of the type string"));
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(view_param) == IS_STRING)) {
		zephir_get_strval(&view, view_param);
	} else {
		ZEPHIR_INIT_VAR(&view);
	}
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "has", NULL, 0, &view);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Finishes the render process by stopping the output buffering
 */
PHP_METHOD(Phalcon_Mvc_View, finish)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_CALL_FUNCTION(NULL, "ob_end_clean", NULL, 492);
	zephir_check_call_status();
	RETURN_THIS();
}

/**
 * Gets the name of the action rendered
 */
PHP_METHOD(Phalcon_Mvc_View, getActionName)
{

	RETURN_MEMBER(getThis(), "actionName");
}

/**
 * Returns the path (or paths) of the views that are currently rendered
 */
PHP_METHOD(Phalcon_Mvc_View, getActiveRenderPath)
{
	zend_bool _1$$3;
	zval activeRenderPath, _0, _2$$4;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, viewsDirsCount = 0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&activeRenderPath);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2$$4);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_CALL_METHOD(&_0, this_ptr, "getviewsdirs", NULL, 0);
	zephir_check_call_status();
	viewsDirsCount = zephir_fast_count_int(&_0);
	zephir_memory_observe(&activeRenderPath);
	zephir_read_property(&activeRenderPath, this_ptr, ZEND_STRL("activeRenderPaths"), PH_NOISY_CC);
	if (viewsDirsCount == 1) {
		_1$$3 = Z_TYPE_P(&activeRenderPath) == IS_ARRAY;
		if (_1$$3) {
			_1$$3 = ((zephir_fast_count_int(&activeRenderPath)) ? 1 : 0);
		}
		if (_1$$3) {
			zephir_array_fetch_long(&_2$$4, &activeRenderPath, 0, PH_NOISY | PH_READONLY, "phalcon/Mvc/View.zep", 339);
			ZEPHIR_CPY_WRT(&activeRenderPath, &_2$$4);
		}
	}
	if (Z_TYPE_P(&activeRenderPath) == IS_NULL) {
		ZEPHIR_INIT_NVAR(&activeRenderPath);
		ZVAL_STRING(&activeRenderPath, "");
	}
	RETURN_CCTOR(&activeRenderPath);
}

/**
 * Gets base path
 */
PHP_METHOD(Phalcon_Mvc_View, getBasePath)
{

	RETURN_MEMBER(getThis(), "basePath");
}

/**
 * Returns output from another view stage
 */
PHP_METHOD(Phalcon_Mvc_View, getContent)
{

	RETURN_MEMBER(getThis(), "content");
}

/**
 * Gets the name of the controller rendered
 */
PHP_METHOD(Phalcon_Mvc_View, getControllerName)
{

	RETURN_MEMBER(getThis(), "controllerName");
}

/**
 * @return int
 */
PHP_METHOD(Phalcon_Mvc_View, getCurrentRenderLevel)
{

	RETURN_MEMBER(getThis(), "currentRenderLevel");
}

/**
 * @return array
 */
PHP_METHOD(Phalcon_Mvc_View, getRegisteredEngines)
{

	RETURN_MEMBER(getThis(), "registeredEngines");
}

/**
 * @return int
 */
PHP_METHOD(Phalcon_Mvc_View, getRenderLevel)
{

	RETURN_MEMBER(getThis(), "renderLevel");
}

/**
 * Returns the internal event manager
 */
PHP_METHOD(Phalcon_Mvc_View, getEventsManager)
{

	RETURN_MEMBER(getThis(), "eventsManager");
}

/**
 * Returns the name of the main view
 */
PHP_METHOD(Phalcon_Mvc_View, getLayout)
{

	RETURN_MEMBER(getThis(), "layout");
}

/**
 * Gets the current layouts sub-directory
 */
PHP_METHOD(Phalcon_Mvc_View, getLayoutsDir)
{

	RETURN_MEMBER(getThis(), "layoutsDir");
}

/**
 * Returns the name of the main view
 */
PHP_METHOD(Phalcon_Mvc_View, getMainView)
{

	RETURN_MEMBER(getThis(), "mainView");
}

/**
 * Returns parameters to views
 */
PHP_METHOD(Phalcon_Mvc_View, getParamsToView)
{

	RETURN_MEMBER(getThis(), "viewParams");
}

/**
 * Renders a partial view
 *
 * ```php
 * // Retrieve the contents of a partial
 * echo $this->getPartial("shared/footer");
 * ```
 *
 * ```php
 * // Retrieve the contents of a partial with arguments
 * echo $this->getPartial(
 *     "shared/footer",
 *     [
 *         "content" => $html,
 *     ]
 * );
 * ```
 */
PHP_METHOD(Phalcon_Mvc_View, getPartial)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *partialPath_param = NULL, *params = NULL, params_sub, __$null;
	zval partialPath;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&partialPath);
	ZVAL_UNDEF(&params_sub);
	ZVAL_NULL(&__$null);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_STR(partialPath)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(params)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &partialPath_param, &params);
	if (UNEXPECTED(Z_TYPE_P(partialPath_param) != IS_STRING && Z_TYPE_P(partialPath_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'partialPath' must be of the type string"));
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(partialPath_param) == IS_STRING)) {
		zephir_get_strval(&partialPath, partialPath_param);
	} else {
		ZEPHIR_INIT_VAR(&partialPath);
	}
	if (!params) {
		params = &params_sub;
		params = &__$null;
	}
	ZEPHIR_CALL_FUNCTION(NULL, "ob_start", NULL, 390);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "partial", NULL, 0, &partialPath, params);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_FUNCTION("ob_get_clean", NULL, 397);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Gets the current partials sub-directory
 */
PHP_METHOD(Phalcon_Mvc_View, getPartialsDir)
{

	RETURN_MEMBER(getThis(), "partialsDir");
}

/**
 * Perform the automatic rendering returning the output as a string
 *
 * ```php
 * $template = $this->view->getRender(
 *     "products",
 *     "show",
 *     [
 *         "products" => $products,
 *     ]
 * );
 * ```
 *
 * @param mixed configCallback
 */
PHP_METHOD(Phalcon_Mvc_View, getRender)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval params, _1$$3;
	zval *controllerName_param = NULL, *actionName_param = NULL, *params_param = NULL, *configCallback = NULL, configCallback_sub, __$null, view, _0$$3;
	zval controllerName, actionName;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&controllerName);
	ZVAL_UNDEF(&actionName);
	ZVAL_UNDEF(&configCallback_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&view);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&params);
	ZVAL_UNDEF(&_1$$3);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(2, 4)
		Z_PARAM_STR(controllerName)
		Z_PARAM_STR(actionName)
		Z_PARAM_OPTIONAL
		Z_PARAM_ARRAY(params)
		Z_PARAM_ZVAL_OR_NULL(configCallback)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 2, &controllerName_param, &actionName_param, &params_param, &configCallback);
	if (UNEXPECTED(Z_TYPE_P(controllerName_param) != IS_STRING && Z_TYPE_P(controllerName_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'controllerName' must be of the type string"));
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(controllerName_param) == IS_STRING)) {
		zephir_get_strval(&controllerName, controllerName_param);
	} else {
		ZEPHIR_INIT_VAR(&controllerName);
	}
	if (UNEXPECTED(Z_TYPE_P(actionName_param) != IS_STRING && Z_TYPE_P(actionName_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'actionName' must be of the type string"));
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(actionName_param) == IS_STRING)) {
		zephir_get_strval(&actionName, actionName_param);
	} else {
		ZEPHIR_INIT_VAR(&actionName);
	}
	if (!params_param) {
		ZEPHIR_INIT_VAR(&params);
		array_init(&params);
	} else {
		zephir_get_arrval(&params, params_param);
	}
	if (!configCallback) {
		configCallback = &configCallback_sub;
		configCallback = &__$null;
	}
	ZEPHIR_INIT_VAR(&view);
	if (zephir_clone(&view, this_ptr) == FAILURE) {
		RETURN_MM();
	}
	ZEPHIR_CALL_METHOD(NULL, &view, "reset", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &view, "setvars", NULL, 0, &params);
	zephir_check_call_status();
	if (Z_TYPE_P(configCallback) == IS_OBJECT) {
		ZEPHIR_INIT_VAR(&_0$$3);
		ZEPHIR_INIT_VAR(&_1$$3);
		zephir_create_array(&_1$$3, 1, 0);
		zephir_array_fast_append(&_1$$3, &view);
		ZEPHIR_CALL_USER_FUNC_ARRAY(&_0$$3, configCallback, &_1$$3);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(NULL, &view, "start", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &view, "render", NULL, 0, &controllerName, &actionName);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &view, "finish", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(&view, "getcontent", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Returns a parameter previously set in the view
 *
 * @return mixed|null
 */
PHP_METHOD(Phalcon_Mvc_View, getVar)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *key_param = NULL, value, _0;
	zval key;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(key)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &key_param);
	if (UNEXPECTED(Z_TYPE_P(key_param) != IS_STRING && Z_TYPE_P(key_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'key' must be of the type string"));
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(key_param) == IS_STRING)) {
		zephir_get_strval(&key, key_param);
	} else {
		ZEPHIR_INIT_VAR(&key);
	}
	zephir_memory_observe(&value);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("viewParams"), PH_NOISY_CC | PH_READONLY);
	if (!(zephir_array_isset_fetch(&value, &_0, &key, 0))) {
		RETURN_MM_NULL();
	}
	RETURN_CCTOR(&value);
}

/**
 * Gets views directory
 */
PHP_METHOD(Phalcon_Mvc_View, getViewsDir)
{

	RETURN_MEMBER(getThis(), "viewsDirs");
}

/**
 * Gets views directories
 */
PHP_METHOD(Phalcon_Mvc_View, getViewsDirs)
{
	zval _0, _1$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_memory_observe(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("viewsDirs"), PH_NOISY_CC);
	if (Z_TYPE_P(&_0) == IS_STRING) {
		zephir_create_array(return_value, 1, 0);
		zephir_memory_observe(&_1$$3);
		zephir_read_property(&_1$$3, this_ptr, ZEND_STRL("viewsDirs"), PH_NOISY_CC);
		zephir_array_fast_append(return_value, &_1$$3);
		RETURN_MM();
	}
	RETURN_MM_MEMBER(getThis(), "viewsDirs");
}

/**
 * Checks whether view exists
 */
PHP_METHOD(Phalcon_Mvc_View, has)
{
	zend_string *_9$$4, *_16$$9;
	zend_ulong _8$$4, _15$$9;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *view_param = NULL, basePath, viewsDir, engines, extension, _0, _2, *_3, _4, _1$$3, _5$$4, *_6$$4, _7$$4, _10$$5, _11$$7, _12$$9, *_13$$9, _14$$9, _17$$10, _18$$12;
	zval view;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&view);
	ZVAL_UNDEF(&basePath);
	ZVAL_UNDEF(&viewsDir);
	ZVAL_UNDEF(&engines);
	ZVAL_UNDEF(&extension);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&_11$$7);
	ZVAL_UNDEF(&_12$$9);
	ZVAL_UNDEF(&_14$$9);
	ZVAL_UNDEF(&_17$$10);
	ZVAL_UNDEF(&_18$$12);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(view)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &view_param);
	if (UNEXPECTED(Z_TYPE_P(view_param) != IS_STRING && Z_TYPE_P(view_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'view' must be of the type string"));
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(view_param) == IS_STRING)) {
		zephir_get_strval(&view, view_param);
	} else {
		ZEPHIR_INIT_VAR(&view);
	}
	zephir_read_property(&_0, this_ptr, ZEND_STRL("basePath"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&basePath, &_0);
	zephir_memory_observe(&engines);
	zephir_read_property(&engines, this_ptr, ZEND_STRL("registeredEngines"), PH_NOISY_CC);
	if (ZEPHIR_IS_EMPTY(&engines)) {
		ZEPHIR_INIT_VAR(&_1$$3);
		zephir_create_array(&_1$$3, 1, 0);
		add_assoc_stringl_ex(&_1$$3, SL(".phtml"), SL("Phalcon\\Mvc\\View\\Engine\\Php"));
		ZEPHIR_CPY_WRT(&engines, &_1$$3);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "registerengines", NULL, 0, &engines);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(&_2, this_ptr, "getviewsdirs", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_2, 0, "phalcon/Mvc/View.zep", 599);
	if (Z_TYPE_P(&_2) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_2), _3)
		{
			ZEPHIR_INIT_NVAR(&viewsDir);
			ZVAL_COPY(&viewsDir, _3);
			ZEPHIR_INIT_NVAR(&_5$$4);
			zephir_is_iterable(&engines, 0, "phalcon/Mvc/View.zep", 597);
			if (Z_TYPE_P(&engines) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&engines), _8$$4, _9$$4, _6$$4)
				{
					ZEPHIR_INIT_NVAR(&extension);
					if (_9$$4 != NULL) { 
						ZVAL_STR_COPY(&extension, _9$$4);
					} else {
						ZVAL_LONG(&extension, _8$$4);
					}
					ZEPHIR_INIT_NVAR(&_5$$4);
					ZVAL_COPY(&_5$$4, _6$$4);
					ZEPHIR_INIT_NVAR(&_10$$5);
					ZEPHIR_CONCAT_VVVV(&_10$$5, &basePath, &viewsDir, &view, &extension);
					if ((zephir_file_exists(&_10$$5) == SUCCESS)) {
						RETURN_MM_BOOL(1);
					}
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &engines, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_7$$4, &engines, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_7$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&extension, &engines, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&_5$$4, &engines, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_11$$7);
						ZEPHIR_CONCAT_VVVV(&_11$$7, &basePath, &viewsDir, &view, &extension);
						if ((zephir_file_exists(&_11$$7) == SUCCESS)) {
							RETURN_MM_BOOL(1);
						}
					ZEPHIR_CALL_METHOD(NULL, &engines, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&_5$$4);
			ZEPHIR_INIT_NVAR(&extension);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_2, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_4, &_2, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_4)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&viewsDir, &_2, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_12$$9);
				zephir_is_iterable(&engines, 0, "phalcon/Mvc/View.zep", 597);
				if (Z_TYPE_P(&engines) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&engines), _15$$9, _16$$9, _13$$9)
					{
						ZEPHIR_INIT_NVAR(&extension);
						if (_16$$9 != NULL) { 
							ZVAL_STR_COPY(&extension, _16$$9);
						} else {
							ZVAL_LONG(&extension, _15$$9);
						}
						ZEPHIR_INIT_NVAR(&_12$$9);
						ZVAL_COPY(&_12$$9, _13$$9);
						ZEPHIR_INIT_NVAR(&_17$$10);
						ZEPHIR_CONCAT_VVVV(&_17$$10, &basePath, &viewsDir, &view, &extension);
						if ((zephir_file_exists(&_17$$10) == SUCCESS)) {
							RETURN_MM_BOOL(1);
						}
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &engines, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_14$$9, &engines, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_14$$9)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&extension, &engines, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&_12$$9, &engines, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_18$$12);
							ZEPHIR_CONCAT_VVVV(&_18$$12, &basePath, &viewsDir, &view, &extension);
							if ((zephir_file_exists(&_18$$12) == SUCCESS)) {
								RETURN_MM_BOOL(1);
							}
						ZEPHIR_CALL_METHOD(NULL, &engines, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&_12$$9);
				ZEPHIR_INIT_NVAR(&extension);
			ZEPHIR_CALL_METHOD(NULL, &_2, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&viewsDir);
	RETURN_MM_BOOL(0);
}

/**
 * Whether automatic rendering is enabled
 */
PHP_METHOD(Phalcon_Mvc_View, isDisabled)
{

	RETURN_MEMBER(getThis(), "disabled");
}

/**
 * Renders a partial view
 *
 * ```php
 * // Show a partial inside another view
 * $this->partial("shared/footer");
 * ```
 *
 * ```php
 * // Show a partial inside another view with parameters
 * $this->partial(
 *     "shared/footer",
 *     [
 *         "content" => $html,
 *     ]
 * );
 * ```
 */
PHP_METHOD(Phalcon_Mvc_View, partial)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *partialPath_param = NULL, *params = NULL, params_sub, __$null, viewParams, _3, _4, _5, _6, _7, _0$$3, _1$$3, _2$$3;
	zval partialPath;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&partialPath);
	ZVAL_UNDEF(&params_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&viewParams);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_STR(partialPath)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(params)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &partialPath_param, &params);
	if (UNEXPECTED(Z_TYPE_P(partialPath_param) != IS_STRING && Z_TYPE_P(partialPath_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'partialPath' must be of the type string"));
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(partialPath_param) == IS_STRING)) {
		zephir_get_strval(&partialPath, partialPath_param);
	} else {
		ZEPHIR_INIT_VAR(&partialPath);
	}
	if (!params) {
		params = &params_sub;
		params = &__$null;
	}
	if (Z_TYPE_P(params) == IS_ARRAY) {
		zephir_read_property(&_0$$3, this_ptr, ZEND_STRL("viewParams"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CPY_WRT(&viewParams, &_0$$3);
		ZEPHIR_INIT_VAR(&_1$$3);
		zephir_fast_array_merge(&_1$$3, &viewParams, params);
		zephir_update_property_zval(this_ptr, ZEND_STRL("viewParams"), &_1$$3);
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CREATE_SYMBOL_TABLE();
		
	}
	ZEPHIR_CALL_METHOD(&_3, this_ptr, "loadtemplateengines", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_4, this_ptr, ZEND_STRL("partialsDir"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_5);
	ZEPHIR_CONCAT_VV(&_5, &_4, &partialPath);
	ZVAL_BOOL(&_6, 0);
	ZVAL_BOOL(&_7, 0);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "enginerender", NULL, 0, &_3, &_5, &_6, &_7);
	zephir_check_call_status();
	if (Z_TYPE_P(params) == IS_ARRAY) {
		zephir_update_property_zval(this_ptr, ZEND_STRL("viewParams"), &viewParams);
	}
	ZEPHIR_MM_RESTORE();
}

/**
 * Choose a different view to render instead of last-controller/last-action
 *
 * ```php
 * use Phalcon\Mvc\Controller;
 *
 * class ProductsController extends Controller
 * {
 *     public function saveAction()
 *     {
 *         // Do some save stuff...
 *
 *         // Then show the list view
 *         $this->view->pick("products/list");
 *     }
 * }
 * ```
 */
PHP_METHOD(Phalcon_Mvc_View, pick)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *renderView, renderView_sub, pickView, layout, parts, _0$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&renderView_sub);
	ZVAL_UNDEF(&pickView);
	ZVAL_UNDEF(&layout);
	ZVAL_UNDEF(&parts);
	ZVAL_UNDEF(&_0$$4);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(renderView)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &renderView);
	if (Z_TYPE_P(renderView) == IS_ARRAY) {
		ZEPHIR_CPY_WRT(&pickView, renderView);
	} else {
		ZEPHIR_INIT_VAR(&layout);
		ZVAL_NULL(&layout);
		if (zephir_memnstr_str(renderView, SL("/"), "phalcon/Mvc/View.zep", 701)) {
			ZEPHIR_INIT_VAR(&parts);
			zephir_fast_explode_str(&parts, SL("/"), renderView, LONG_MAX);
			ZEPHIR_OBS_NVAR(&layout);
			zephir_array_fetch_long(&layout, &parts, 0, PH_NOISY, "phalcon/Mvc/View.zep", 703);
		}
		ZEPHIR_INIT_VAR(&_0$$4);
		zephir_create_array(&_0$$4, 1, 0);
		zephir_array_fast_append(&_0$$4, renderView);
		ZEPHIR_CPY_WRT(&pickView, &_0$$4);
		if (Z_TYPE_P(&layout) != IS_NULL) {
			zephir_array_append(&pickView, &layout, PH_SEPARATE, "phalcon/Mvc/View.zep", 709);
		}
	}
	zephir_update_property_zval(this_ptr, ZEND_STRL("pickView"), &pickView);
	RETURN_THIS();
}

/**
 * Register templating engines
 *
 * ```php
 * $this->view->registerEngines(
 *     [
 *         ".phtml" => \Phalcon\Mvc\View\Engine\Php::class,
 *         ".volt"  => \Phalcon\Mvc\View\Engine\Volt::class,
 *         ".mhtml" => \MyCustomEngine::class,
 *     ]
 * );
 * ```
 */
PHP_METHOD(Phalcon_Mvc_View, registerEngines)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *engines_param = NULL;
	zval engines;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&engines);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ARRAY(engines)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &engines_param);
	ZEPHIR_OBS_COPY_OR_DUP(&engines, engines_param);
	zephir_update_property_zval(this_ptr, ZEND_STRL("registeredEngines"), &engines);
	RETURN_THIS();
}

/**
 * Executes render process from dispatching data
 *
 *```php
 * // Shows recent posts view (app/views/posts/recent.phtml)
 * $view->start()->render("posts", "recent")->finish();
 *```
 */
PHP_METHOD(Phalcon_Mvc_View, render)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval params;
	zval *controllerName_param = NULL, *actionName_param = NULL, *params_param = NULL, result;
	zval controllerName, actionName;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&controllerName);
	ZVAL_UNDEF(&actionName);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&params);
	ZEND_PARSE_PARAMETERS_START(2, 3)
		Z_PARAM_STR(controllerName)
		Z_PARAM_STR(actionName)
		Z_PARAM_OPTIONAL
		Z_PARAM_ARRAY(params)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 1, &controllerName_param, &actionName_param, &params_param);
	if (UNEXPECTED(Z_TYPE_P(controllerName_param) != IS_STRING && Z_TYPE_P(controllerName_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'controllerName' must be of the type string"));
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(controllerName_param) == IS_STRING)) {
		zephir_get_strval(&controllerName, controllerName_param);
	} else {
		ZEPHIR_INIT_VAR(&controllerName);
	}
	if (UNEXPECTED(Z_TYPE_P(actionName_param) != IS_STRING && Z_TYPE_P(actionName_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'actionName' must be of the type string"));
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(actionName_param) == IS_STRING)) {
		zephir_get_strval(&actionName, actionName_param);
	} else {
		ZEPHIR_INIT_VAR(&actionName);
	}
	if (!params_param) {
		ZEPHIR_INIT_VAR(&params);
		array_init(&params);
	} else {
		zephir_get_arrval(&params, params_param);
	}
	ZEPHIR_CALL_METHOD(&result, this_ptr, "processrender", NULL, 0, &controllerName, &actionName, &params);
	zephir_check_call_status();
	if (!(zephir_is_true(&result))) {
		RETURN_MM_BOOL(0);
	}
	RETURN_THIS();
}

/**
 * Resets the view component to its factory default values
 */
PHP_METHOD(Phalcon_Mvc_View, reset)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval __$true, __$false, _0, _1, _2;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	if (0) {
		zephir_update_property_zval(this_ptr, ZEND_STRL("disabled"), &__$true);
	} else {
		zephir_update_property_zval(this_ptr, ZEND_STRL("disabled"), &__$false);
	}
	if (0) {
		zephir_update_property_zval(this_ptr, ZEND_STRL("engines"), &__$true);
	} else {
		zephir_update_property_zval(this_ptr, ZEND_STRL("engines"), &__$false);
	}
	ZVAL_UNDEF(&_0);
	ZVAL_LONG(&_0, 5);
	zephir_update_property_zval(this_ptr, ZEND_STRL("renderLevel"), &_0);
	ZEPHIR_INIT_VAR(&_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "");
	zephir_update_property_zval(this_ptr, ZEND_STRL("content"), &_1);
	ZEPHIR_INIT_NVAR(&_1);
	array_init(&_1);
	zephir_update_property_zval(this_ptr, ZEND_STRL("templatesBefore"), &_1);
	ZEPHIR_INIT_VAR(&_2);
	array_init(&_2);
	zephir_update_property_zval(this_ptr, ZEND_STRL("templatesAfter"), &_2);
	RETURN_THIS();
}

/**
 * Sets base path. Depending of your platform, always add a trailing slash
 * or backslash
 *
 * ```php
 * $view->setBasePath(__DIR__ . "/");
 * ```
 */
PHP_METHOD(Phalcon_Mvc_View, setBasePath)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *basePath_param = NULL;
	zval basePath;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&basePath);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(basePath)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &basePath_param);
	zephir_get_strval(&basePath, basePath_param);
	zephir_update_property_zval(this_ptr, ZEND_STRL("basePath"), &basePath);
	RETURN_THIS();
}

/**
 * Externally sets the view content
 *
 *```php
 * $this->view->setContent("<h1>hello</h1>");
 *```
 */
PHP_METHOD(Phalcon_Mvc_View, setContent)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *content_param = NULL;
	zval content;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&content);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(content)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &content_param);
	zephir_get_strval(&content, content_param);
	zephir_update_property_zval(this_ptr, ZEND_STRL("content"), &content);
	RETURN_THIS();
}

/**
 * Sets the events manager
 */
PHP_METHOD(Phalcon_Mvc_View, setEventsManager)
{
	zval *eventsManager, eventsManager_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&eventsManager_sub);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(eventsManager, phalcon_events_managerinterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &eventsManager);
	zephir_update_property_zval(this_ptr, ZEND_STRL("eventsManager"), eventsManager);
}

/**
 * Change the layout to be used instead of using the name of the latest
 * controller name
 *
 * ```php
 * $this->view->setLayout("main");
 * ```
 */
PHP_METHOD(Phalcon_Mvc_View, setLayout)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *layout_param = NULL;
	zval layout;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&layout);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(layout)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &layout_param);
	zephir_get_strval(&layout, layout_param);
	zephir_update_property_zval(this_ptr, ZEND_STRL("layout"), &layout);
	RETURN_THIS();
}

/**
 * Sets the layouts sub-directory. Must be a directory under the views
 * directory. Depending of your platform, always add a trailing slash or
 * backslash
 *
 *```php
 * $view->setLayoutsDir("../common/layouts/");
 *```
 */
PHP_METHOD(Phalcon_Mvc_View, setLayoutsDir)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *layoutsDir_param = NULL;
	zval layoutsDir;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&layoutsDir);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(layoutsDir)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &layoutsDir_param);
	zephir_get_strval(&layoutsDir, layoutsDir_param);
	zephir_update_property_zval(this_ptr, ZEND_STRL("layoutsDir"), &layoutsDir);
	RETURN_THIS();
}

/**
 * Sets default view name. Must be a file without extension in the views
 * directory
 *
 * ```php
 * // Renders as main view views-dir/base.phtml
 * $this->view->setMainView("base");
 * ```
 */
PHP_METHOD(Phalcon_Mvc_View, setMainView)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *viewPath_param = NULL;
	zval viewPath;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&viewPath);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(viewPath)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &viewPath_param);
	zephir_get_strval(&viewPath, viewPath_param);
	zephir_update_property_zval(this_ptr, ZEND_STRL("mainView"), &viewPath);
	RETURN_THIS();
}

/**
 * Sets a partials sub-directory. Must be a directory under the views
 * directory. Depending of your platform, always add a trailing slash or
 * backslash
 *
 *```php
 * $view->setPartialsDir("../common/partials/");
 *```
 */
PHP_METHOD(Phalcon_Mvc_View, setPartialsDir)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *partialsDir_param = NULL;
	zval partialsDir;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&partialsDir);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(partialsDir)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &partialsDir_param);
	zephir_get_strval(&partialsDir, partialsDir_param);
	zephir_update_property_zval(this_ptr, ZEND_STRL("partialsDir"), &partialsDir);
	RETURN_THIS();
}

/**
 * Adds parameters to views (alias of setVar)
 *
 *```php
 * $this->view->setParamToView("products", $products);
 *```
 */
PHP_METHOD(Phalcon_Mvc_View, setParamToView)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *key_param = NULL, *value, value_sub;
	zval key;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&value_sub);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(key)
		Z_PARAM_ZVAL(value)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &key_param, &value);
	if (UNEXPECTED(Z_TYPE_P(key_param) != IS_STRING && Z_TYPE_P(key_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'key' must be of the type string"));
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(key_param) == IS_STRING)) {
		zephir_get_strval(&key, key_param);
	} else {
		ZEPHIR_INIT_VAR(&key);
	}
	zephir_update_property_array(this_ptr, SL("viewParams"), &key, value);
	RETURN_THIS();
}

/**
 * Sets the render level for the view
 *
 * ```php
 * // Render the view related to the controller only
 * $this->view->setRenderLevel(
 *     View::LEVEL_LAYOUT
 * );
 * ```
 */
PHP_METHOD(Phalcon_Mvc_View, setRenderLevel)
{
	zval *level_param = NULL, _0;
	zend_long level;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(level)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &level_param);
	ZVAL_UNDEF(&_0);
	ZVAL_LONG(&_0, level);
	zephir_update_property_zval(this_ptr, ZEND_STRL("renderLevel"), &_0);
	RETURN_THISW();
}

/**
 * Sets a "template after" controller layout
 */
PHP_METHOD(Phalcon_Mvc_View, setTemplateAfter)
{
	zval _0$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *templateAfter, templateAfter_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&templateAfter_sub);
	ZVAL_UNDEF(&_0$$3);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(templateAfter)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &templateAfter);
	if (Z_TYPE_P(templateAfter) != IS_ARRAY) {
		ZEPHIR_INIT_VAR(&_0$$3);
		zephir_create_array(&_0$$3, 1, 0);
		zephir_array_fast_append(&_0$$3, templateAfter);
		zephir_update_property_zval(this_ptr, ZEND_STRL("templatesAfter"), &_0$$3);
	} else {
		zephir_update_property_zval(this_ptr, ZEND_STRL("templatesAfter"), templateAfter);
	}
	RETURN_THIS();
}

/**
 * Sets a template before the controller layout
 */
PHP_METHOD(Phalcon_Mvc_View, setTemplateBefore)
{
	zval _0$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *templateBefore, templateBefore_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&templateBefore_sub);
	ZVAL_UNDEF(&_0$$3);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(templateBefore)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &templateBefore);
	if (Z_TYPE_P(templateBefore) != IS_ARRAY) {
		ZEPHIR_INIT_VAR(&_0$$3);
		zephir_create_array(&_0$$3, 1, 0);
		zephir_array_fast_append(&_0$$3, templateBefore);
		zephir_update_property_zval(this_ptr, ZEND_STRL("templatesBefore"), &_0$$3);
	} else {
		zephir_update_property_zval(this_ptr, ZEND_STRL("templatesBefore"), templateBefore);
	}
	RETURN_THIS();
}

/**
 * Set a single view parameter
 *
 *```php
 * $this->view->setVar("products", $products);
 *```
 */
PHP_METHOD(Phalcon_Mvc_View, setVar)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *key_param = NULL, *value, value_sub;
	zval key;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&value_sub);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(key)
		Z_PARAM_ZVAL(value)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &key_param, &value);
	if (UNEXPECTED(Z_TYPE_P(key_param) != IS_STRING && Z_TYPE_P(key_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'key' must be of the type string"));
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(key_param) == IS_STRING)) {
		zephir_get_strval(&key, key_param);
	} else {
		ZEPHIR_INIT_VAR(&key);
	}
	zephir_update_property_array(this_ptr, SL("viewParams"), &key, value);
	RETURN_THIS();
}

/**
 * Set all the render params
 *
 *```php
 * $this->view->setVars(
 *     [
 *         "products" => $products,
 *     ]
 * );
 *```
 */
PHP_METHOD(Phalcon_Mvc_View, setVars)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_bool merge;
	zval *params_param = NULL, *merge_param = NULL, _0$$3, _1$$3;
	zval params;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&params);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_ARRAY(params)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(merge)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &params_param, &merge_param);
	ZEPHIR_OBS_COPY_OR_DUP(&params, params_param);
	if (!merge_param) {
		merge = 1;
	} else {
		}
	if (merge) {
		ZEPHIR_INIT_VAR(&_0$$3);
		zephir_read_property(&_1$$3, this_ptr, ZEND_STRL("viewParams"), PH_NOISY_CC | PH_READONLY);
		zephir_fast_array_merge(&_0$$3, &_1$$3, &params);
		zephir_update_property_zval(this_ptr, ZEND_STRL("viewParams"), &_0$$3);
	} else {
		zephir_update_property_zval(this_ptr, ZEND_STRL("viewParams"), &params);
	}
	RETURN_THIS();
}

/**
 * Sets the views directory. Depending of your platform,
 * always add a trailing slash or backslash
 */
PHP_METHOD(Phalcon_Mvc_View, setViewsDir)
{
	zend_string *_5$$5;
	zend_ulong _4$$5;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *viewsDir, viewsDir_sub, position, directory, newViewsDir, _1$$4, *_2$$5, _3$$5, _6$$6, _7$$8;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&viewsDir_sub);
	ZVAL_UNDEF(&position);
	ZVAL_UNDEF(&directory);
	ZVAL_UNDEF(&newViewsDir);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_3$$5);
	ZVAL_UNDEF(&_6$$6);
	ZVAL_UNDEF(&_7$$8);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(viewsDir)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &viewsDir);
	_0 = Z_TYPE_P(viewsDir) != IS_STRING;
	if (_0) {
		_0 = Z_TYPE_P(viewsDir) != IS_ARRAY;
	}
	if (_0) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_view_exception_ce, "Views directory must be a string or an array", "phalcon/Mvc/View.zep", 982);
		return;
	}
	if (Z_TYPE_P(viewsDir) == IS_STRING) {
		ZEPHIR_CALL_METHOD(&_1$$4, this_ptr, "getdirseparator", NULL, 493, viewsDir);
		zephir_check_call_status();
		zephir_update_property_zval(this_ptr, ZEND_STRL("viewsDirs"), &_1$$4);
	} else {
		ZEPHIR_INIT_VAR(&newViewsDir);
		array_init(&newViewsDir);
		zephir_is_iterable(viewsDir, 0, "phalcon/Mvc/View.zep", 1000);
		if (Z_TYPE_P(viewsDir) == IS_ARRAY) {
			ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(viewsDir), _4$$5, _5$$5, _2$$5)
			{
				ZEPHIR_INIT_NVAR(&position);
				if (_5$$5 != NULL) { 
					ZVAL_STR_COPY(&position, _5$$5);
				} else {
					ZVAL_LONG(&position, _4$$5);
				}
				ZEPHIR_INIT_NVAR(&directory);
				ZVAL_COPY(&directory, _2$$5);
				if (Z_TYPE_P(&directory) != IS_STRING) {
					ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_view_exception_ce, "Views directory item must be a string", "phalcon/Mvc/View.zep", 994);
					return;
				}
				ZEPHIR_CALL_METHOD(&_6$$6, this_ptr, "getdirseparator", NULL, 493, &directory);
				zephir_check_call_status();
				zephir_array_update_zval(&newViewsDir, &position, &_6$$6, PH_COPY | PH_SEPARATE);
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, viewsDir, "rewind", NULL, 0);
			zephir_check_call_status();
			while (1) {
				ZEPHIR_CALL_METHOD(&_3$$5, viewsDir, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_3$$5)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&position, viewsDir, "key", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&directory, viewsDir, "current", NULL, 0);
				zephir_check_call_status();
					if (Z_TYPE_P(&directory) != IS_STRING) {
						ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_view_exception_ce, "Views directory item must be a string", "phalcon/Mvc/View.zep", 994);
						return;
					}
					ZEPHIR_CALL_METHOD(&_7$$8, this_ptr, "getdirseparator", NULL, 493, &directory);
					zephir_check_call_status();
					zephir_array_update_zval(&newViewsDir, &position, &_7$$8, PH_COPY | PH_SEPARATE);
				ZEPHIR_CALL_METHOD(NULL, viewsDir, "next", NULL, 0);
				zephir_check_call_status();
			}
		}
		ZEPHIR_INIT_NVAR(&directory);
		ZEPHIR_INIT_NVAR(&position);
		zephir_update_property_zval(this_ptr, ZEND_STRL("viewsDirs"), &newViewsDir);
	}
	RETURN_THIS();
}

/**
 * Starts rendering process enabling the output buffering
 */
PHP_METHOD(Phalcon_Mvc_View, start)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval __$null;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_NULL(&__$null);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_CALL_FUNCTION(NULL, "ob_start", NULL, 390);
	zephir_check_call_status();
	zephir_update_property_zval(this_ptr, ZEND_STRL("content"), &__$null);
	RETURN_THIS();
}

/**
 * Renders the view and returns it as a string
 */
PHP_METHOD(Phalcon_Mvc_View, toString)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval params;
	zval *controllerName_param = NULL, *actionName_param = NULL, *params_param = NULL, result, _0;
	zval controllerName, actionName;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&controllerName);
	ZVAL_UNDEF(&actionName);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&params);
	ZEND_PARSE_PARAMETERS_START(2, 3)
		Z_PARAM_STR(controllerName)
		Z_PARAM_STR(actionName)
		Z_PARAM_OPTIONAL
		Z_PARAM_ARRAY(params)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 1, &controllerName_param, &actionName_param, &params_param);
	if (UNEXPECTED(Z_TYPE_P(controllerName_param) != IS_STRING && Z_TYPE_P(controllerName_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'controllerName' must be of the type string"));
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(controllerName_param) == IS_STRING)) {
		zephir_get_strval(&controllerName, controllerName_param);
	} else {
		ZEPHIR_INIT_VAR(&controllerName);
	}
	if (UNEXPECTED(Z_TYPE_P(actionName_param) != IS_STRING && Z_TYPE_P(actionName_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'actionName' must be of the type string"));
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(actionName_param) == IS_STRING)) {
		zephir_get_strval(&actionName, actionName_param);
	} else {
		ZEPHIR_INIT_VAR(&actionName);
	}
	if (!params_param) {
		ZEPHIR_INIT_VAR(&params);
		array_init(&params);
	} else {
		zephir_get_arrval(&params, params_param);
	}
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "start", NULL, 0);
	zephir_check_call_status();
	ZVAL_BOOL(&_0, 0);
	ZEPHIR_CALL_METHOD(&result, this_ptr, "processrender", NULL, 0, &controllerName, &actionName, &params, &_0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "finish", NULL, 0);
	zephir_check_call_status();
	if (!(zephir_is_true(&result))) {
		RETURN_MM_STRING("");
	}
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "getcontent", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Checks whether view exists on registered extensions and render it
 */
PHP_METHOD(Phalcon_Mvc_View, engineRender)
{
	zend_string *_9$$3, *_28$$16;
	zend_ulong _8$$3, _27$$16;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_5 = NULL, *_13 = NULL, *_16 = NULL, *_20 = NULL, *_23 = NULL, *_32 = NULL, *_35 = NULL, *_39 = NULL, *_42 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool silence, mustClean;
	zval viewPath, _45$$30;
	zval *engines_param = NULL, *viewPath_param = NULL, *silence_param = NULL, *mustClean_param = NULL, basePath, engine, eventsManager, extension, viewsDir, viewsDirPath, viewEnginePath, viewEnginePaths, viewParams, _0, _1, *_2, _3, _4$$3, *_6$$3, _7$$3, _11$$8, _12$$8, _14$$7, _15$$10, _18$$13, _19$$13, _21$$12, _22$$15, _24$$16, *_25$$16, _26$$16, _30$$21, _31$$21, _33$$20, _34$$23, _37$$26, _38$$26, _40$$25, _41$$28, _43$$29, _44$$30;
	zval engines, _10$$8, _17$$13, _29$$21, _36$$26;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&engines);
	ZVAL_UNDEF(&_10$$8);
	ZVAL_UNDEF(&_17$$13);
	ZVAL_UNDEF(&_29$$21);
	ZVAL_UNDEF(&_36$$26);
	ZVAL_UNDEF(&basePath);
	ZVAL_UNDEF(&engine);
	ZVAL_UNDEF(&eventsManager);
	ZVAL_UNDEF(&extension);
	ZVAL_UNDEF(&viewsDir);
	ZVAL_UNDEF(&viewsDirPath);
	ZVAL_UNDEF(&viewEnginePath);
	ZVAL_UNDEF(&viewEnginePaths);
	ZVAL_UNDEF(&viewParams);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_11$$8);
	ZVAL_UNDEF(&_12$$8);
	ZVAL_UNDEF(&_14$$7);
	ZVAL_UNDEF(&_15$$10);
	ZVAL_UNDEF(&_18$$13);
	ZVAL_UNDEF(&_19$$13);
	ZVAL_UNDEF(&_21$$12);
	ZVAL_UNDEF(&_22$$15);
	ZVAL_UNDEF(&_24$$16);
	ZVAL_UNDEF(&_26$$16);
	ZVAL_UNDEF(&_30$$21);
	ZVAL_UNDEF(&_31$$21);
	ZVAL_UNDEF(&_33$$20);
	ZVAL_UNDEF(&_34$$23);
	ZVAL_UNDEF(&_37$$26);
	ZVAL_UNDEF(&_38$$26);
	ZVAL_UNDEF(&_40$$25);
	ZVAL_UNDEF(&_41$$28);
	ZVAL_UNDEF(&_43$$29);
	ZVAL_UNDEF(&_44$$30);
	ZVAL_UNDEF(&viewPath);
	ZVAL_UNDEF(&_45$$30);
	ZEND_PARSE_PARAMETERS_START(3, 4)
		Z_PARAM_ARRAY(engines)
		Z_PARAM_STR(viewPath)
		Z_PARAM_BOOL(silence)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(mustClean)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 1, &engines_param, &viewPath_param, &silence_param, &mustClean_param);
	zephir_get_arrval(&engines, engines_param);
	zephir_get_strval(&viewPath, viewPath_param);
	if (!mustClean_param) {
		mustClean = 1;
	} else {
		}
	zephir_read_property(&_0, this_ptr, ZEND_STRL("basePath"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&basePath, &_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("viewParams"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&viewParams, &_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("eventsManager"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&eventsManager, &_0);
	ZEPHIR_INIT_VAR(&viewEnginePaths);
	array_init(&viewEnginePaths);
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "getviewsdirs", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_1, 0, "phalcon/Mvc/View.zep", 1106);
	if (Z_TYPE_P(&_1) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_1), _2)
		{
			ZEPHIR_INIT_NVAR(&viewsDir);
			ZVAL_COPY(&viewsDir, _2);
			ZEPHIR_CALL_METHOD(&_4$$3, this_ptr, "isabsolutepath", &_5, 494, &viewPath);
			zephir_check_call_status();
			if (!(zephir_is_true(&_4$$3))) {
				ZEPHIR_INIT_NVAR(&viewsDirPath);
				ZEPHIR_CONCAT_VVV(&viewsDirPath, &basePath, &viewsDir, &viewPath);
			} else {
				ZEPHIR_CPY_WRT(&viewsDirPath, &viewPath);
			}
			zephir_is_iterable(&engines, 0, "phalcon/Mvc/View.zep", 1101);
			if (Z_TYPE_P(&engines) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&engines), _8$$3, _9$$3, _6$$3)
				{
					ZEPHIR_INIT_NVAR(&extension);
					if (_9$$3 != NULL) { 
						ZVAL_STR_COPY(&extension, _9$$3);
					} else {
						ZVAL_LONG(&extension, _8$$3);
					}
					ZEPHIR_INIT_NVAR(&engine);
					ZVAL_COPY(&engine, _6$$3);
					ZEPHIR_INIT_NVAR(&viewEnginePath);
					ZEPHIR_CONCAT_VV(&viewEnginePath, &viewsDirPath, &extension);
					if ((zephir_file_exists(&viewEnginePath) == SUCCESS)) {
						if (Z_TYPE_P(&eventsManager) == IS_OBJECT) {
							ZEPHIR_INIT_NVAR(&_10$$8);
							zephir_create_array(&_10$$8, 1, 0);
							zephir_array_fast_append(&_10$$8, &viewEnginePath);
							zephir_update_property_zval(this_ptr, ZEND_STRL("activeRenderPaths"), &_10$$8);
							ZEPHIR_INIT_NVAR(&_12$$8);
							ZVAL_STRING(&_12$$8, "view:beforeRenderView");
							ZEPHIR_CALL_METHOD(&_11$$8, &eventsManager, "fire", &_13, 0, &_12$$8, this_ptr, &viewEnginePath);
							zephir_check_call_status();
							if (ZEPHIR_IS_FALSE_IDENTICAL(&_11$$8)) {
								continue;
							}
						}
						if (mustClean) {
							ZVAL_BOOL(&_14$$7, 1);
						} else {
							ZVAL_BOOL(&_14$$7, 0);
						}
						ZEPHIR_CALL_METHOD(NULL, &engine, "render", NULL, 0, &viewEnginePath, &viewParams, &_14$$7);
						zephir_check_call_status();
						if (Z_TYPE_P(&eventsManager) == IS_OBJECT) {
							ZEPHIR_INIT_NVAR(&_15$$10);
							ZVAL_STRING(&_15$$10, "view:afterRenderView");
							ZEPHIR_CALL_METHOD(NULL, &eventsManager, "fire", &_16, 0, &_15$$10, this_ptr);
							zephir_check_call_status();
						}
						RETURN_MM_NULL();
					}
					zephir_array_append(&viewEnginePaths, &viewEnginePath, PH_SEPARATE, "phalcon/Mvc/View.zep", 1099);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &engines, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_7$$3, &engines, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_7$$3)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&extension, &engines, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&engine, &engines, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&viewEnginePath);
						ZEPHIR_CONCAT_VV(&viewEnginePath, &viewsDirPath, &extension);
						if ((zephir_file_exists(&viewEnginePath) == SUCCESS)) {
							if (Z_TYPE_P(&eventsManager) == IS_OBJECT) {
								ZEPHIR_INIT_NVAR(&_17$$13);
								zephir_create_array(&_17$$13, 1, 0);
								zephir_array_fast_append(&_17$$13, &viewEnginePath);
								zephir_update_property_zval(this_ptr, ZEND_STRL("activeRenderPaths"), &_17$$13);
								ZEPHIR_INIT_NVAR(&_19$$13);
								ZVAL_STRING(&_19$$13, "view:beforeRenderView");
								ZEPHIR_CALL_METHOD(&_18$$13, &eventsManager, "fire", &_20, 0, &_19$$13, this_ptr, &viewEnginePath);
								zephir_check_call_status();
								if (ZEPHIR_IS_FALSE_IDENTICAL(&_18$$13)) {
									continue;
								}
							}
							if (mustClean) {
								ZVAL_BOOL(&_21$$12, 1);
							} else {
								ZVAL_BOOL(&_21$$12, 0);
							}
							ZEPHIR_CALL_METHOD(NULL, &engine, "render", NULL, 0, &viewEnginePath, &viewParams, &_21$$12);
							zephir_check_call_status();
							if (Z_TYPE_P(&eventsManager) == IS_OBJECT) {
								ZEPHIR_INIT_NVAR(&_22$$15);
								ZVAL_STRING(&_22$$15, "view:afterRenderView");
								ZEPHIR_CALL_METHOD(NULL, &eventsManager, "fire", &_23, 0, &_22$$15, this_ptr);
								zephir_check_call_status();
							}
							RETURN_MM_NULL();
						}
						zephir_array_append(&viewEnginePaths, &viewEnginePath, PH_SEPARATE, "phalcon/Mvc/View.zep", 1099);
					ZEPHIR_CALL_METHOD(NULL, &engines, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&engine);
			ZEPHIR_INIT_NVAR(&extension);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_1, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_3, &_1, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_3)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&viewsDir, &_1, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_24$$16, this_ptr, "isabsolutepath", &_5, 494, &viewPath);
				zephir_check_call_status();
				if (!(zephir_is_true(&_24$$16))) {
					ZEPHIR_INIT_NVAR(&viewsDirPath);
					ZEPHIR_CONCAT_VVV(&viewsDirPath, &basePath, &viewsDir, &viewPath);
				} else {
					ZEPHIR_CPY_WRT(&viewsDirPath, &viewPath);
				}
				zephir_is_iterable(&engines, 0, "phalcon/Mvc/View.zep", 1101);
				if (Z_TYPE_P(&engines) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&engines), _27$$16, _28$$16, _25$$16)
					{
						ZEPHIR_INIT_NVAR(&extension);
						if (_28$$16 != NULL) { 
							ZVAL_STR_COPY(&extension, _28$$16);
						} else {
							ZVAL_LONG(&extension, _27$$16);
						}
						ZEPHIR_INIT_NVAR(&engine);
						ZVAL_COPY(&engine, _25$$16);
						ZEPHIR_INIT_NVAR(&viewEnginePath);
						ZEPHIR_CONCAT_VV(&viewEnginePath, &viewsDirPath, &extension);
						if ((zephir_file_exists(&viewEnginePath) == SUCCESS)) {
							if (Z_TYPE_P(&eventsManager) == IS_OBJECT) {
								ZEPHIR_INIT_NVAR(&_29$$21);
								zephir_create_array(&_29$$21, 1, 0);
								zephir_array_fast_append(&_29$$21, &viewEnginePath);
								zephir_update_property_zval(this_ptr, ZEND_STRL("activeRenderPaths"), &_29$$21);
								ZEPHIR_INIT_NVAR(&_31$$21);
								ZVAL_STRING(&_31$$21, "view:beforeRenderView");
								ZEPHIR_CALL_METHOD(&_30$$21, &eventsManager, "fire", &_32, 0, &_31$$21, this_ptr, &viewEnginePath);
								zephir_check_call_status();
								if (ZEPHIR_IS_FALSE_IDENTICAL(&_30$$21)) {
									continue;
								}
							}
							if (mustClean) {
								ZVAL_BOOL(&_33$$20, 1);
							} else {
								ZVAL_BOOL(&_33$$20, 0);
							}
							ZEPHIR_CALL_METHOD(NULL, &engine, "render", NULL, 0, &viewEnginePath, &viewParams, &_33$$20);
							zephir_check_call_status();
							if (Z_TYPE_P(&eventsManager) == IS_OBJECT) {
								ZEPHIR_INIT_NVAR(&_34$$23);
								ZVAL_STRING(&_34$$23, "view:afterRenderView");
								ZEPHIR_CALL_METHOD(NULL, &eventsManager, "fire", &_35, 0, &_34$$23, this_ptr);
								zephir_check_call_status();
							}
							RETURN_MM_NULL();
						}
						zephir_array_append(&viewEnginePaths, &viewEnginePath, PH_SEPARATE, "phalcon/Mvc/View.zep", 1099);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &engines, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_26$$16, &engines, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_26$$16)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&extension, &engines, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&engine, &engines, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&viewEnginePath);
							ZEPHIR_CONCAT_VV(&viewEnginePath, &viewsDirPath, &extension);
							if ((zephir_file_exists(&viewEnginePath) == SUCCESS)) {
								if (Z_TYPE_P(&eventsManager) == IS_OBJECT) {
									ZEPHIR_INIT_NVAR(&_36$$26);
									zephir_create_array(&_36$$26, 1, 0);
									zephir_array_fast_append(&_36$$26, &viewEnginePath);
									zephir_update_property_zval(this_ptr, ZEND_STRL("activeRenderPaths"), &_36$$26);
									ZEPHIR_INIT_NVAR(&_38$$26);
									ZVAL_STRING(&_38$$26, "view:beforeRenderView");
									ZEPHIR_CALL_METHOD(&_37$$26, &eventsManager, "fire", &_39, 0, &_38$$26, this_ptr, &viewEnginePath);
									zephir_check_call_status();
									if (ZEPHIR_IS_FALSE_IDENTICAL(&_37$$26)) {
										continue;
									}
								}
								if (mustClean) {
									ZVAL_BOOL(&_40$$25, 1);
								} else {
									ZVAL_BOOL(&_40$$25, 0);
								}
								ZEPHIR_CALL_METHOD(NULL, &engine, "render", NULL, 0, &viewEnginePath, &viewParams, &_40$$25);
								zephir_check_call_status();
								if (Z_TYPE_P(&eventsManager) == IS_OBJECT) {
									ZEPHIR_INIT_NVAR(&_41$$28);
									ZVAL_STRING(&_41$$28, "view:afterRenderView");
									ZEPHIR_CALL_METHOD(NULL, &eventsManager, "fire", &_42, 0, &_41$$28, this_ptr);
									zephir_check_call_status();
								}
								RETURN_MM_NULL();
							}
							zephir_array_append(&viewEnginePaths, &viewEnginePath, PH_SEPARATE, "phalcon/Mvc/View.zep", 1099);
						ZEPHIR_CALL_METHOD(NULL, &engines, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&engine);
				ZEPHIR_INIT_NVAR(&extension);
			ZEPHIR_CALL_METHOD(NULL, &_1, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&viewsDir);
	if (Z_TYPE_P(&eventsManager) == IS_OBJECT) {
		zephir_update_property_zval(this_ptr, ZEND_STRL("activeRenderPaths"), &viewEnginePaths);
		ZEPHIR_INIT_VAR(&_43$$29);
		ZVAL_STRING(&_43$$29, "view:notFoundView");
		ZEPHIR_CALL_METHOD(NULL, &eventsManager, "fire", NULL, 0, &_43$$29, this_ptr, &viewEnginePath);
		zephir_check_call_status();
	}
	if (!(silence)) {
		ZEPHIR_INIT_VAR(&_44$$30);
		object_init_ex(&_44$$30, phalcon_mvc_view_exception_ce);
		ZEPHIR_INIT_VAR(&_45$$30);
		ZEPHIR_CONCAT_SVS(&_45$$30, "View '", &viewPath, "' was not found in any of the views directory");
		ZEPHIR_CALL_METHOD(NULL, &_44$$30, "__construct", NULL, 33, &_45$$30);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_44$$30, "phalcon/Mvc/View.zep", 1115);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_MM_RESTORE();
}

/**
 * Checks if a path is absolute or not
 */
PHP_METHOD(Phalcon_Mvc_View, isAbsolutePath)
{
	unsigned char _6, _2$$3, _4$$3;
	zend_bool _5, _1$$3, _3$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *path_param = NULL, _0;
	zval path;

	ZVAL_UNDEF(&path);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(path)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &path_param);
	zephir_get_strval(&path, path_param);
	ZEPHIR_INIT_VAR(&_0);
	ZEPHIR_GET_CONSTANT(&_0, "PHP_OS");
	if (ZEPHIR_IS_STRING_IDENTICAL(&_0, "WINNT")) {
		_1$$3 = zephir_fast_strlen_ev(&path) >= 3;
		if (_1$$3) {
			_2$$3 = ZEPHIR_STRING_OFFSET(&path, 1);
			_1$$3 = _2$$3 == ':';
		}
		_3$$3 = _1$$3;
		if (_3$$3) {
			_4$$3 = ZEPHIR_STRING_OFFSET(&path, 2);
			_3$$3 = _4$$3 == '\\';
		}
		RETURN_MM_BOOL(_3$$3);
	}
	_5 = zephir_fast_strlen_ev(&path) >= 1;
	if (_5) {
		_6 = ZEPHIR_STRING_OFFSET(&path, 0);
		_5 = _6 == '/';
	}
	RETURN_MM_BOOL(_5);
}

/**
 * Loads registered template engines, if none is registered it will use
 * Phalcon\Mvc\View\Engine\Php
 */
PHP_METHOD(Phalcon_Mvc_View, loadTemplateEngines)
{
	zval _15$$11, _21$$17;
	zend_class_entry *_8$$9, *_17$$15;
	zend_string *_6$$5;
	zend_ulong _5$$5;
	zval engines, di, registeredEngines, engineService, extension, _0, _1$$3, _2$$4, *_3$$5, _4$$5, _7$$9, _11$$12, _12$$12, _14$$11, _16$$15, _18$$18, _19$$18, _20$$17;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_9 = NULL, *_10 = NULL, *_13 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&engines);
	ZVAL_UNDEF(&di);
	ZVAL_UNDEF(&registeredEngines);
	ZVAL_UNDEF(&engineService);
	ZVAL_UNDEF(&extension);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_7$$9);
	ZVAL_UNDEF(&_11$$12);
	ZVAL_UNDEF(&_12$$12);
	ZVAL_UNDEF(&_14$$11);
	ZVAL_UNDEF(&_16$$15);
	ZVAL_UNDEF(&_18$$18);
	ZVAL_UNDEF(&_19$$18);
	ZVAL_UNDEF(&_20$$17);
	ZVAL_UNDEF(&_15$$11);
	ZVAL_UNDEF(&_21$$17);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property(&_0, this_ptr, ZEND_STRL("engines"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&engines, &_0);
	if (ZEPHIR_IS_FALSE_IDENTICAL(&engines)) {
		zephir_read_property(&_1$$3, this_ptr, ZEND_STRL("container"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CPY_WRT(&di, &_1$$3);
		ZEPHIR_INIT_NVAR(&engines);
		array_init(&engines);
		zephir_read_property(&_1$$3, this_ptr, ZEND_STRL("registeredEngines"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CPY_WRT(&registeredEngines, &_1$$3);
		if (ZEPHIR_IS_EMPTY(&registeredEngines)) {
			ZEPHIR_INIT_VAR(&_2$$4);
			object_init_ex(&_2$$4, phalcon_mvc_view_engine_php_ce);
			ZEPHIR_CALL_METHOD(NULL, &_2$$4, "__construct", NULL, 495, this_ptr, &di);
			zephir_check_call_status();
			zephir_array_update_string(&engines, SL(".phtml"), &_2$$4, PH_COPY | PH_SEPARATE);
		} else {
			if (Z_TYPE_P(&di) != IS_OBJECT) {
				ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_view_exception_ce, "A dependency injection container is required to access application services", "phalcon/Mvc/View.zep", 1159);
				return;
			}
			zephir_is_iterable(&registeredEngines, 0, "phalcon/Mvc/View.zep", 1196);
			if (Z_TYPE_P(&registeredEngines) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&registeredEngines), _5$$5, _6$$5, _3$$5)
				{
					ZEPHIR_INIT_NVAR(&extension);
					if (_6$$5 != NULL) { 
						ZVAL_STR_COPY(&extension, _6$$5);
					} else {
						ZVAL_LONG(&extension, _5$$5);
					}
					ZEPHIR_INIT_NVAR(&engineService);
					ZVAL_COPY(&engineService, _3$$5);
					if (Z_TYPE_P(&engineService) == IS_OBJECT) {
						if (zephir_is_instance_of(&engineService, SL("Closure"))) {
							_8$$9 = zephir_fetch_class_str_ex(SL("Closure"), ZEND_FETCH_CLASS_AUTO);
							ZEPHIR_CALL_CE_STATIC(&_7$$9, _8$$9, "bind", &_9, 0, &engineService, &di);
							zephir_check_call_status();
							ZEPHIR_CPY_WRT(&engineService, &_7$$9);
							ZEPHIR_CALL_FUNCTION(&_7$$9, "call_user_func", &_10, 188, &engineService, this_ptr);
							zephir_check_call_status();
							zephir_array_update_zval(&engines, &extension, &_7$$9, PH_COPY | PH_SEPARATE);
						} else {
							zephir_array_update_zval(&engines, &extension, &engineService, PH_COPY | PH_SEPARATE);
						}
					} else {
						if (Z_TYPE_P(&engineService) != IS_STRING) {
							ZEPHIR_INIT_NVAR(&_11$$12);
							object_init_ex(&_11$$12, phalcon_mvc_view_exception_ce);
							ZEPHIR_INIT_NVAR(&_12$$12);
							ZEPHIR_CONCAT_SV(&_12$$12, "Invalid template engine registration for extension: ", &extension);
							ZEPHIR_CALL_METHOD(NULL, &_11$$12, "__construct", &_13, 33, &_12$$12);
							zephir_check_call_status();
							zephir_throw_exception_debug(&_11$$12, "phalcon/Mvc/View.zep", 1187);
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_INIT_NVAR(&_15$$11);
						zephir_create_array(&_15$$11, 1, 0);
						zephir_array_fast_append(&_15$$11, this_ptr);
						ZEPHIR_CALL_METHOD(&_14$$11, &di, "get", NULL, 0, &engineService, &_15$$11);
						zephir_check_call_status();
						zephir_array_update_zval(&engines, &extension, &_14$$11, PH_COPY | PH_SEPARATE);
					}
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &registeredEngines, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_4$$5, &registeredEngines, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_4$$5)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&extension, &registeredEngines, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&engineService, &registeredEngines, "current", NULL, 0);
					zephir_check_call_status();
						if (Z_TYPE_P(&engineService) == IS_OBJECT) {
							if (zephir_is_instance_of(&engineService, SL("Closure"))) {
								_17$$15 = zephir_fetch_class_str_ex(SL("Closure"), ZEND_FETCH_CLASS_AUTO);
								ZEPHIR_CALL_CE_STATIC(&_16$$15, _17$$15, "bind", &_9, 0, &engineService, &di);
								zephir_check_call_status();
								ZEPHIR_CPY_WRT(&engineService, &_16$$15);
								ZEPHIR_CALL_FUNCTION(&_16$$15, "call_user_func", &_10, 188, &engineService, this_ptr);
								zephir_check_call_status();
								zephir_array_update_zval(&engines, &extension, &_16$$15, PH_COPY | PH_SEPARATE);
							} else {
								zephir_array_update_zval(&engines, &extension, &engineService, PH_COPY | PH_SEPARATE);
							}
						} else {
							if (Z_TYPE_P(&engineService) != IS_STRING) {
								ZEPHIR_INIT_NVAR(&_18$$18);
								object_init_ex(&_18$$18, phalcon_mvc_view_exception_ce);
								ZEPHIR_INIT_NVAR(&_19$$18);
								ZEPHIR_CONCAT_SV(&_19$$18, "Invalid template engine registration for extension: ", &extension);
								ZEPHIR_CALL_METHOD(NULL, &_18$$18, "__construct", &_13, 33, &_19$$18);
								zephir_check_call_status();
								zephir_throw_exception_debug(&_18$$18, "phalcon/Mvc/View.zep", 1187);
								ZEPHIR_MM_RESTORE();
								return;
							}
							ZEPHIR_INIT_NVAR(&_21$$17);
							zephir_create_array(&_21$$17, 1, 0);
							zephir_array_fast_append(&_21$$17, this_ptr);
							ZEPHIR_CALL_METHOD(&_20$$17, &di, "get", NULL, 0, &engineService, &_21$$17);
							zephir_check_call_status();
							zephir_array_update_zval(&engines, &extension, &_20$$17, PH_COPY | PH_SEPARATE);
						}
					ZEPHIR_CALL_METHOD(NULL, &registeredEngines, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&engineService);
			ZEPHIR_INIT_NVAR(&extension);
		}
		zephir_update_property_zval(this_ptr, ZEND_STRL("engines"), &engines);
	}
	RETURN_CCTOR(&engines);
}

/**
 * Processes the view and templates; Fires events if needed
 */
PHP_METHOD(Phalcon_Mvc_View, processRender)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, renderLevel = 0;
	zend_bool fireEvents, silence = 0, _5, _30;
	zval params;
	zval *controllerName_param = NULL, *actionName_param = NULL, *params_param = NULL, *fireEvents_param = NULL, layoutsDir, layout, pickView, layoutName, engines, renderView, pickViewAction, eventsManager, disabledLevels, templatesBefore, templatesAfter, templateBefore, templateAfter, _0, _2, _4, _8, _9, _1$$3, _6$$11, _7$$11, _10$$15, _11$$17, *_12$$17, _13$$17, _14$$18, _15$$18, _16$$19, _17$$19, _18$$21, _19$$21, _20$$23, *_21$$23, _22$$23, _23$$24, _24$$24, _25$$25, _26$$25, _27$$27, _28$$27, _29$$13, _31$$28;
	zval controllerName, actionName, _3$$7;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&controllerName);
	ZVAL_UNDEF(&actionName);
	ZVAL_UNDEF(&_3$$7);
	ZVAL_UNDEF(&layoutsDir);
	ZVAL_UNDEF(&layout);
	ZVAL_UNDEF(&pickView);
	ZVAL_UNDEF(&layoutName);
	ZVAL_UNDEF(&engines);
	ZVAL_UNDEF(&renderView);
	ZVAL_UNDEF(&pickViewAction);
	ZVAL_UNDEF(&eventsManager);
	ZVAL_UNDEF(&disabledLevels);
	ZVAL_UNDEF(&templatesBefore);
	ZVAL_UNDEF(&templatesAfter);
	ZVAL_UNDEF(&templateBefore);
	ZVAL_UNDEF(&templateAfter);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_6$$11);
	ZVAL_UNDEF(&_7$$11);
	ZVAL_UNDEF(&_10$$15);
	ZVAL_UNDEF(&_11$$17);
	ZVAL_UNDEF(&_13$$17);
	ZVAL_UNDEF(&_14$$18);
	ZVAL_UNDEF(&_15$$18);
	ZVAL_UNDEF(&_16$$19);
	ZVAL_UNDEF(&_17$$19);
	ZVAL_UNDEF(&_18$$21);
	ZVAL_UNDEF(&_19$$21);
	ZVAL_UNDEF(&_20$$23);
	ZVAL_UNDEF(&_22$$23);
	ZVAL_UNDEF(&_23$$24);
	ZVAL_UNDEF(&_24$$24);
	ZVAL_UNDEF(&_25$$25);
	ZVAL_UNDEF(&_26$$25);
	ZVAL_UNDEF(&_27$$27);
	ZVAL_UNDEF(&_28$$27);
	ZVAL_UNDEF(&_29$$13);
	ZVAL_UNDEF(&_31$$28);
	ZVAL_UNDEF(&params);
	ZEND_PARSE_PARAMETERS_START(2, 4)
		Z_PARAM_STR(controllerName)
		Z_PARAM_STR(actionName)
		Z_PARAM_OPTIONAL
		Z_PARAM_ARRAY(params)
		Z_PARAM_BOOL(fireEvents)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 2, &controllerName_param, &actionName_param, &params_param, &fireEvents_param);
	if (UNEXPECTED(Z_TYPE_P(controllerName_param) != IS_STRING && Z_TYPE_P(controllerName_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'controllerName' must be of the type string"));
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(controllerName_param) == IS_STRING)) {
		zephir_get_strval(&controllerName, controllerName_param);
	} else {
		ZEPHIR_INIT_VAR(&controllerName);
	}
	if (UNEXPECTED(Z_TYPE_P(actionName_param) != IS_STRING && Z_TYPE_P(actionName_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'actionName' must be of the type string"));
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(actionName_param) == IS_STRING)) {
		zephir_get_strval(&actionName, actionName_param);
	} else {
		ZEPHIR_INIT_VAR(&actionName);
	}
	if (!params_param) {
		ZEPHIR_INIT_VAR(&params);
		array_init(&params);
	} else {
		zephir_get_arrval(&params, params_param);
	}
	if (!fireEvents_param) {
		fireEvents = 1;
	} else {
		}
	ZVAL_UNDEF(&_0);
	ZVAL_LONG(&_0, 0);
	zephir_update_property_zval(this_ptr, ZEND_STRL("currentRenderLevel"), &_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("disabled"), PH_NOISY_CC | PH_READONLY);
	if (!ZEPHIR_IS_FALSE_IDENTICAL(&_0)) {
		ZEPHIR_CALL_FUNCTION(&_1$$3, "ob_get_contents", NULL, 496);
		zephir_check_call_status();
		zephir_update_property_zval(this_ptr, ZEND_STRL("content"), &_1$$3);
		RETURN_MM_BOOL(0);
	}
	zephir_update_property_zval(this_ptr, ZEND_STRL("controllerName"), &controllerName);
	zephir_update_property_zval(this_ptr, ZEND_STRL("actionName"), &actionName);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setvars", NULL, 0, &params);
	zephir_check_call_status();
	zephir_read_property(&_2, this_ptr, ZEND_STRL("layoutsDir"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&layoutsDir, &_2);
	if (!(zephir_is_true(&layoutsDir))) {
		ZEPHIR_INIT_NVAR(&layoutsDir);
		ZVAL_STRING(&layoutsDir, "layouts/");
	}
	zephir_read_property(&_2, this_ptr, ZEND_STRL("layout"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&layout, &_2);
	if (zephir_is_true(&layout)) {
		ZEPHIR_CPY_WRT(&layoutName, &layout);
	} else {
		ZEPHIR_CPY_WRT(&layoutName, &controllerName);
	}
	ZEPHIR_CALL_METHOD(&engines, this_ptr, "loadtemplateengines", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_2, this_ptr, ZEND_STRL("pickView"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&pickView, &_2);
	if (Z_TYPE_P(&pickView) == IS_NULL) {
		ZEPHIR_INIT_VAR(&_3$$7);
		ZEPHIR_CONCAT_VSV(&_3$$7, &controllerName, "/", &actionName);
		ZEPHIR_CPY_WRT(&renderView, &_3$$7);
	} else {
		ZEPHIR_OBS_NVAR(&renderView);
		zephir_array_fetch_long(&renderView, &pickView, 0, PH_NOISY, "phalcon/Mvc/View.zep", 1274);
		if (Z_TYPE_P(&layoutName) == IS_NULL) {
			zephir_memory_observe(&pickViewAction);
			if (zephir_array_isset_long_fetch(&pickViewAction, &pickView, 1, 0)) {
				ZEPHIR_CPY_WRT(&layoutName, &pickViewAction);
			}
		}
	}
	zephir_read_property(&_2, this_ptr, ZEND_STRL("eventsManager"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&eventsManager, &_2);
	ZEPHIR_INIT_VAR(&_4);
	ZEPHIR_CREATE_SYMBOL_TABLE();
	
	_5 = fireEvents;
	if (_5) {
		_5 = Z_TYPE_P(&eventsManager) == IS_OBJECT;
	}
	if (_5) {
		ZEPHIR_INIT_VAR(&_7$$11);
		ZVAL_STRING(&_7$$11, "view:beforeRender");
		ZEPHIR_CALL_METHOD(&_6$$11, &eventsManager, "fire", NULL, 0, &_7$$11, this_ptr);
		zephir_check_call_status();
		if (ZEPHIR_IS_FALSE_IDENTICAL(&_6$$11)) {
			RETURN_MM_BOOL(0);
		}
	}
	ZEPHIR_CALL_FUNCTION(&_8, "ob_get_contents", NULL, 496);
	zephir_check_call_status();
	zephir_update_property_zval(this_ptr, ZEND_STRL("content"), &_8);
	silence = 1;
	zephir_read_property(&_2, this_ptr, ZEND_STRL("disabledLevels"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&disabledLevels, &_2);
	zephir_memory_observe(&_9);
	zephir_read_property(&_9, this_ptr, ZEND_STRL("renderLevel"), PH_NOISY_CC);
	renderLevel = zephir_get_intval(&_9);
	if (renderLevel) {
		if (renderLevel >= 1) {
			if (!(zephir_array_isset_long(&disabledLevels, 1))) {
				ZVAL_UNDEF(&_10$$15);
				ZVAL_LONG(&_10$$15, 1);
				zephir_update_property_zval(this_ptr, ZEND_STRL("currentRenderLevel"), &_10$$15);
				if (silence) {
					ZVAL_BOOL(&_10$$15, 1);
				} else {
					ZVAL_BOOL(&_10$$15, 0);
				}
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "enginerender", NULL, 0, &engines, &renderView, &_10$$15);
				zephir_check_call_status();
			}
		}
		if (renderLevel >= 2) {
			if (!(zephir_array_isset_long(&disabledLevels, 2))) {
				ZVAL_UNDEF(&_11$$17);
				ZVAL_LONG(&_11$$17, 2);
				zephir_update_property_zval(this_ptr, ZEND_STRL("currentRenderLevel"), &_11$$17);
				zephir_read_property(&_11$$17, this_ptr, ZEND_STRL("templatesBefore"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_CPY_WRT(&templatesBefore, &_11$$17);
				silence = 0;
				zephir_is_iterable(&templatesBefore, 0, "phalcon/Mvc/View.zep", 1350);
				if (Z_TYPE_P(&templatesBefore) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&templatesBefore), _12$$17)
					{
						ZEPHIR_INIT_NVAR(&templateBefore);
						ZVAL_COPY(&templateBefore, _12$$17);
						ZEPHIR_INIT_NVAR(&_14$$18);
						ZEPHIR_CONCAT_VV(&_14$$18, &layoutsDir, &templateBefore);
						if (silence) {
							ZVAL_BOOL(&_15$$18, 1);
						} else {
							ZVAL_BOOL(&_15$$18, 0);
						}
						ZEPHIR_CALL_METHOD(NULL, this_ptr, "enginerender", NULL, 0, &engines, &_14$$18, &_15$$18);
						zephir_check_call_status();
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &templatesBefore, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_13$$17, &templatesBefore, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_13$$17)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&templateBefore, &templatesBefore, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_16$$19);
							ZEPHIR_CONCAT_VV(&_16$$19, &layoutsDir, &templateBefore);
							if (silence) {
								ZVAL_BOOL(&_17$$19, 1);
							} else {
								ZVAL_BOOL(&_17$$19, 0);
							}
							ZEPHIR_CALL_METHOD(NULL, this_ptr, "enginerender", NULL, 0, &engines, &_16$$19, &_17$$19);
							zephir_check_call_status();
						ZEPHIR_CALL_METHOD(NULL, &templatesBefore, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&templateBefore);
				silence = 1;
			}
		}
		if (renderLevel >= 3) {
			if (!(zephir_array_isset_long(&disabledLevels, 3))) {
				ZVAL_UNDEF(&_18$$21);
				ZVAL_LONG(&_18$$21, 3);
				zephir_update_property_zval(this_ptr, ZEND_STRL("currentRenderLevel"), &_18$$21);
				ZEPHIR_INIT_VAR(&_19$$21);
				ZEPHIR_CONCAT_VV(&_19$$21, &layoutsDir, &layoutName);
				if (silence) {
					ZVAL_BOOL(&_18$$21, 1);
				} else {
					ZVAL_BOOL(&_18$$21, 0);
				}
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "enginerender", NULL, 0, &engines, &_19$$21, &_18$$21);
				zephir_check_call_status();
			}
		}
		if (renderLevel >= 4) {
			if (!(zephir_array_isset_long(&disabledLevels, 4))) {
				ZVAL_UNDEF(&_20$$23);
				ZVAL_LONG(&_20$$23, 4);
				zephir_update_property_zval(this_ptr, ZEND_STRL("currentRenderLevel"), &_20$$23);
				zephir_read_property(&_20$$23, this_ptr, ZEND_STRL("templatesAfter"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_CPY_WRT(&templatesAfter, &_20$$23);
				silence = 0;
				zephir_is_iterable(&templatesAfter, 0, "phalcon/Mvc/View.zep", 1386);
				if (Z_TYPE_P(&templatesAfter) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&templatesAfter), _21$$23)
					{
						ZEPHIR_INIT_NVAR(&templateAfter);
						ZVAL_COPY(&templateAfter, _21$$23);
						ZEPHIR_INIT_NVAR(&_23$$24);
						ZEPHIR_CONCAT_VV(&_23$$24, &layoutsDir, &templateAfter);
						if (silence) {
							ZVAL_BOOL(&_24$$24, 1);
						} else {
							ZVAL_BOOL(&_24$$24, 0);
						}
						ZEPHIR_CALL_METHOD(NULL, this_ptr, "enginerender", NULL, 0, &engines, &_23$$24, &_24$$24);
						zephir_check_call_status();
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &templatesAfter, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_22$$23, &templatesAfter, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_22$$23)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&templateAfter, &templatesAfter, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_25$$25);
							ZEPHIR_CONCAT_VV(&_25$$25, &layoutsDir, &templateAfter);
							if (silence) {
								ZVAL_BOOL(&_26$$25, 1);
							} else {
								ZVAL_BOOL(&_26$$25, 0);
							}
							ZEPHIR_CALL_METHOD(NULL, this_ptr, "enginerender", NULL, 0, &engines, &_25$$25, &_26$$25);
							zephir_check_call_status();
						ZEPHIR_CALL_METHOD(NULL, &templatesAfter, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&templateAfter);
				silence = 1;
			}
		}
		if (renderLevel >= 5) {
			if (!(zephir_array_isset_long(&disabledLevels, 5))) {
				ZVAL_UNDEF(&_27$$27);
				ZVAL_LONG(&_27$$27, 5);
				zephir_update_property_zval(this_ptr, ZEND_STRL("currentRenderLevel"), &_27$$27);
				zephir_read_property(&_27$$27, this_ptr, ZEND_STRL("mainView"), PH_NOISY_CC | PH_READONLY);
				if (silence) {
					ZVAL_BOOL(&_28$$27, 1);
				} else {
					ZVAL_BOOL(&_28$$27, 0);
				}
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "enginerender", NULL, 0, &engines, &_27$$27, &_28$$27);
				zephir_check_call_status();
			}
		}
		ZVAL_UNDEF(&_29$$13);
		ZVAL_LONG(&_29$$13, 0);
		zephir_update_property_zval(this_ptr, ZEND_STRL("currentRenderLevel"), &_29$$13);
	}
	_30 = fireEvents;
	if (_30) {
		_30 = Z_TYPE_P(&eventsManager) == IS_OBJECT;
	}
	if (_30) {
		ZEPHIR_INIT_VAR(&_31$$28);
		ZVAL_STRING(&_31$$28, "view:afterRender");
		ZEPHIR_CALL_METHOD(NULL, &eventsManager, "fire", NULL, 0, &_31$$28, this_ptr);
		zephir_check_call_status();
	}
	RETURN_MM_BOOL(1);
}

/**
 * @todo Remove this when we get traits
 */
PHP_METHOD(Phalcon_Mvc_View, getDirSeparator)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *directory_param = NULL, _0, _1;
	zval directory;

	ZVAL_UNDEF(&directory);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(directory)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &directory_param);
	if (UNEXPECTED(Z_TYPE_P(directory_param) != IS_STRING && Z_TYPE_P(directory_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'directory' must be of the type string"));
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(directory_param) == IS_STRING)) {
		zephir_get_strval(&directory, directory_param);
	} else {
		ZEPHIR_INIT_VAR(&directory);
	}
	ZEPHIR_INIT_VAR(&_0);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "/");
	zephir_fast_trim(&_0, &directory, &_1, ZEPHIR_TRIM_RIGHT);
	ZEPHIR_CONCAT_VS(return_value, &_0, "/");
	RETURN_MM();
}

zend_object *zephir_init_properties_Phalcon_Mvc_View(zend_class_entry *class_type)
{
		zval _0, _2, _4, _6, _8, _10, _12, _14, _1$$3, _3$$4, _5$$5, _7$$6, _9$$7, _11$$8, _13$$9, _15$$10;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_14);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_7$$6);
	ZVAL_UNDEF(&_9$$7);
	ZVAL_UNDEF(&_11$$8);
	ZVAL_UNDEF(&_13$$9);
	ZVAL_UNDEF(&_15$$10);
	

		ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
		zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	
	{
		zval local_this_ptr, *this_ptr = &local_this_ptr;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		zephir_read_property_ex(&_0, this_ptr, ZEND_STRL("viewParams"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_1$$3);
			array_init(&_1$$3);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("viewParams"), &_1$$3);
		}
		zephir_read_property_ex(&_2, this_ptr, ZEND_STRL("viewsDirs"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_2) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_3$$4);
			array_init(&_3$$4);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("viewsDirs"), &_3$$4);
		}
		zephir_read_property_ex(&_4, this_ptr, ZEND_STRL("templatesBefore"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_4) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_5$$5);
			array_init(&_5$$5);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("templatesBefore"), &_5$$5);
		}
		zephir_read_property_ex(&_6, this_ptr, ZEND_STRL("templatesAfter"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_6) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_7$$6);
			array_init(&_7$$6);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("templatesAfter"), &_7$$6);
		}
		zephir_read_property_ex(&_8, this_ptr, ZEND_STRL("registeredEngines"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_8) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_9$$7);
			array_init(&_9$$7);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("registeredEngines"), &_9$$7);
		}
		zephir_read_property_ex(&_10, this_ptr, ZEND_STRL("params"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_10) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_11$$8);
			array_init(&_11$$8);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("params"), &_11$$8);
		}
		zephir_read_property_ex(&_12, this_ptr, ZEND_STRL("options"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_12) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_13$$9);
			array_init(&_13$$9);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("options"), &_13$$9);
		}
		zephir_read_property_ex(&_14, this_ptr, ZEND_STRL("disabledLevels"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_14) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_15$$10);
			array_init(&_15$$10);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("disabledLevels"), &_15$$10);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}
}

