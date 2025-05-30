
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
#include "kernel/fcall.h"
#include "kernel/memory.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"
#include "kernel/object.h"
#include "kernel/array.h"
#include "kernel/operators.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */
ZEPHIR_INIT_CLASS(Phalcon_Image_ImageFactory)
{
	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Image, ImageFactory, phalcon, image_imagefactory, phalcon_factory_abstractfactory_ce, phalcon_image_imagefactory_method_entry, 0);

	return SUCCESS;
}

/**
 * Constructor
 */
PHP_METHOD(Phalcon_Image_ImageFactory, __construct)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *services_param = NULL;
	zval services;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&services);
	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_ARRAY(services)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 1, &services_param);
	if (!services_param) {
		ZEPHIR_INIT_VAR(&services);
		array_init(&services);
	} else {
	ZEPHIR_OBS_COPY_OR_DUP(&services, services_param);
	}
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "init", NULL, 0, &services);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();
}

/**
 * Factory to create an instance from a Config object
 *
 * @param array|\Phalcon\Config\Config config = [
 *     'adapter' => 'gd',
 *     'file' => 'image.jpg',
 *     'height' => null,
 *     'width' => null
 * ]
 */
PHP_METHOD(Phalcon_Image_ImageFactory, load)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *config = NULL, config_sub, height, file, name, width, _0, _1, _2;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&config_sub);
	ZVAL_UNDEF(&height);
	ZVAL_UNDEF(&file);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&width);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(config)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &config);
	ZEPHIR_SEPARATE_PARAM(config);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "checkconfig", NULL, 0, config);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(config, &_0);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "adapter");
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "checkconfigelement", NULL, 0, config, &_1);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(config, &_0);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "file");
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "checkconfigelement", NULL, 0, config, &_1);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(config, &_0);
	zephir_memory_observe(&name);
	zephir_array_fetch_string(&name, config, SL("adapter"), PH_NOISY, "phalcon/Image/ImageFactory.zep", 44);
	zephir_array_unset_string(config, SL("adapter"), PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "file");
	ZEPHIR_CALL_METHOD(&file, this_ptr, "getarrval", NULL, 411, config, &_1);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "height");
	ZVAL_NULL(&_2);
	ZEPHIR_CALL_METHOD(&height, this_ptr, "getarrval", NULL, 411, config, &_1, &_2);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "width");
	ZVAL_NULL(&_2);
	ZEPHIR_CALL_METHOD(&width, this_ptr, "getarrval", NULL, 411, config, &_1, &_2);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "newinstance", NULL, 0, &name, &file, &width, &height);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Creates a new instance
 */
PHP_METHOD(Phalcon_Image_ImageFactory, newInstance)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long width, height, ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *file_param = NULL, *width_param = NULL, *height_param = NULL, definition, _1;
	zval name, file;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&file);
	ZVAL_UNDEF(&definition);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_0);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(2, 4)
		Z_PARAM_STR(name)
		Z_PARAM_STR(file)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG_OR_NULL(width, is_null_true)
		Z_PARAM_LONG_OR_NULL(height, is_null_true)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 2, &name_param, &file_param, &width_param, &height_param);
	if (UNEXPECTED(Z_TYPE_P(name_param) != IS_STRING && Z_TYPE_P(name_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'name' must be of the type string"));
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(name_param) == IS_STRING)) {
		zephir_get_strval(&name, name_param);
	} else {
		ZEPHIR_INIT_VAR(&name);
	}
	if (UNEXPECTED(Z_TYPE_P(file_param) != IS_STRING && Z_TYPE_P(file_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'file' must be of the type string"));
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(file_param) == IS_STRING)) {
		zephir_get_strval(&file, file_param);
	} else {
		ZEPHIR_INIT_VAR(&file);
	}
	if (!width_param) {
		width = 0;
	} else {
		}
	if (!height_param) {
		height = 0;
	} else {
		}
	ZEPHIR_CALL_METHOD(&definition, this_ptr, "getservice", NULL, 0, &name);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_0);
	zephir_create_array(&_0, 3, 0);
	zephir_array_fast_append(&_0, &file);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_LONG(&_1, width);
	zephir_array_fast_append(&_0, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_LONG(&_1, height);
	zephir_array_fast_append(&_0, &_1);
	ZEPHIR_LAST_CALL_STATUS = zephir_create_instance_params(return_value, &definition, &_0);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * @return string
 */
PHP_METHOD(Phalcon_Image_ImageFactory, getExceptionClass)
{

	RETURN_STRING("Phalcon\\Image\\Exception");
}

/**
 * Returns the available adapters
 *
 * @return string[]
 */
PHP_METHOD(Phalcon_Image_ImageFactory, getServices)
{

	zephir_create_array(return_value, 2, 0);
	add_assoc_stringl_ex(return_value, SL("gd"), SL("Phalcon\\Image\\Adapter\\Gd"));
	add_assoc_stringl_ex(return_value, SL("imagick"), SL("Phalcon\\Image\\Adapter\\Imagick"));
	return;
}

/**
 * @todo Remove this when we get traits
 */
PHP_METHOD(Phalcon_Image_ImageFactory, getArrVal)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *collection_param = NULL, *index, index_sub, *defaultValue = NULL, defaultValue_sub, __$null, value;
	zval collection;

	ZVAL_UNDEF(&collection);
	ZVAL_UNDEF(&index_sub);
	ZVAL_UNDEF(&defaultValue_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&value);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(2, 3)
		Z_PARAM_ARRAY(collection)
		Z_PARAM_ZVAL(index)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(defaultValue)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 1, &collection_param, &index, &defaultValue);
	ZEPHIR_OBS_COPY_OR_DUP(&collection, collection_param);
	if (!defaultValue) {
		defaultValue = &defaultValue_sub;
		defaultValue = &__$null;
	}
	zephir_memory_observe(&value);
	if (UNEXPECTED(!(zephir_array_isset_fetch(&value, &collection, index, 0)))) {
		RETVAL_ZVAL(defaultValue, 1, 0);
		RETURN_MM();
	}
	RETURN_CCTOR(&value);
}

