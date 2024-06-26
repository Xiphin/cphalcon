
#ifdef HAVE_CONFIG_H
#include "../../../ext_config.h"
#endif

#include <php.h>
#include "../../../php_ext.h"
#include "../../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"
#include "kernel/require.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"
#include "kernel/operators.h"
#include "kernel/object.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */
/**
 * Reads php files and converts them to Phalcon\Config\Config objects.
 *
 * Given the next configuration file:
 *
 *```php
 * <?php
 *
 * return [
 *     "database" => [
 *         "adapter"  => "Mysql",
 *         "host"     => "localhost",
 *         "username" => "scott",
 *         "password" => "cheetah",
 *         "dbname"   => "test_db",
 *     ],
 *     "phalcon" => [
 *         "controllersDir" => "../app/controllers/",
 *         "modelsDir"      => "../app/models/",
 *         "viewsDir"       => "../app/views/",
 *     ],
 * ];
 *```
 *
 * You can read it as follows:
 *
 *```php
 * use Phalcon\Config\Adapter\Php;
 *
 * $config = new Php("path/config.php");
 *
 * echo $config->phalcon->controllersDir;
 * echo $config->database->username;
 *```
 */
ZEPHIR_INIT_CLASS(Phalcon_Config_Adapter_Php)
{
	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Config\\Adapter, Php, phalcon, config_adapter_php, phalcon_config_config_ce, phalcon_config_adapter_php_method_entry, 0);

	return SUCCESS;
}

/**
 * Phalcon\Config\Adapter\Php constructor
 */
PHP_METHOD(Phalcon_Config_Adapter_Php, __construct)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *filePath_param = NULL, _0;
	zval filePath;

	ZVAL_UNDEF(&filePath);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(filePath)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &filePath_param);
	if (UNEXPECTED(Z_TYPE_P(filePath_param) != IS_STRING && Z_TYPE_P(filePath_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'filePath' must be of the type string"));
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(filePath_param) == IS_STRING)) {
		zephir_get_strval(&filePath, filePath_param);
	} else {
		ZEPHIR_INIT_VAR(&filePath);
	}
	ZEPHIR_OBSERVE_OR_NULLIFY_PPZV(&_0);
	if (zephir_require_zval_ret(&_0, &filePath) == FAILURE) {
		RETURN_MM_NULL();
	}
	ZEPHIR_CALL_PARENT(NULL, phalcon_config_adapter_php_ce, getThis(), "__construct", NULL, 0, &_0);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();
}

