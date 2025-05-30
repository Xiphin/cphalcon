
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
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/object.h"
#include "kernel/operators.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"
#include "kernel/concat.h"
#include "kernel/string.h"
#include "ext/date/php_date.h"
#include "kernel/array.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */
/**
 * Part of the HTTP cycle is return responses to the clients.
 * Phalcon\HTTP\Response is the Phalcon component responsible to achieve this task.
 * HTTP responses are usually composed by headers and body.
 *
 *```php
 * $response = new \Phalcon\Http\Response();
 *
 * $response->setStatusCode(200, "OK");
 * $response->setContent("<html><body>Hello</body></html>");
 *
 * $response->send();
 *```
 */
ZEPHIR_INIT_CLASS(Phalcon_Http_Response)
{
	ZEPHIR_REGISTER_CLASS(Phalcon\\Http, Response, phalcon, http_response, phalcon_http_response_method_entry, 0);

	/**
	 * @var DiInterface|null
	 */
	zend_declare_property_null(phalcon_http_response_ce, SL("container"), ZEND_ACC_PROTECTED);
	/**
	 * @var string|null
	 */
	zend_declare_property_null(phalcon_http_response_ce, SL("content"), ZEND_ACC_PROTECTED);
	/**
	 * @var CookiesInterface|null
	 */
	zend_declare_property_null(phalcon_http_response_ce, SL("cookies"), ZEND_ACC_PROTECTED);
	/**
	 * @var ManagerInterface|null
	 */
	zend_declare_property_null(phalcon_http_response_ce, SL("eventsManager"), ZEND_ACC_PROTECTED);
	/**
	 * @var string|null
	 */
	zend_declare_property_null(phalcon_http_response_ce, SL("file"), ZEND_ACC_PROTECTED);
	/**
	 * @var Headers
	 */
	zend_declare_property_null(phalcon_http_response_ce, SL("headers"), ZEND_ACC_PROTECTED);
	/**
	 * @var bool
	 */
	zend_declare_property_bool(phalcon_http_response_ce, SL("sent"), 0, ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_http_response_ce, SL("statusCodes"), ZEND_ACC_PROTECTED);
	/**
	 * @var Encode
	 */
	zend_declare_property_null(phalcon_http_response_ce, SL("encode"), ZEND_ACC_PRIVATE);
	phalcon_http_response_ce->create_object = zephir_init_properties_Phalcon_Http_Response;

	zend_class_implements(phalcon_http_response_ce, 1, phalcon_http_responseinterface_ce);
	zend_class_implements(phalcon_http_response_ce, 1, phalcon_di_injectionawareinterface_ce);
	zend_class_implements(phalcon_http_response_ce, 1, phalcon_events_eventsawareinterface_ce);
	zend_class_implements(phalcon_http_response_ce, 1, phalcon_http_message_responsestatuscodeinterface_ce);
	return SUCCESS;
}

/**
 * Phalcon\Http\Response constructor
 */
PHP_METHOD(Phalcon_Http_Response, __construct)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *content_param = NULL, *code = NULL, code_sub, *status = NULL, status_sub, __$null, _0, _1;
	zval content;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&content);
	ZVAL_UNDEF(&code_sub);
	ZVAL_UNDEF(&status_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 3)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR_OR_NULL(content)
		Z_PARAM_ZVAL_OR_NULL(code)
		Z_PARAM_ZVAL_OR_NULL(status)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 3, &content_param, &code, &status);
	if (!content_param) {
		ZEPHIR_INIT_VAR(&content);
	} else {
	if (UNEXPECTED(Z_TYPE_P(content_param) != IS_STRING && Z_TYPE_P(content_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'content' must be of the type string"));
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(content_param) == IS_STRING)) {
		zephir_get_strval(&content, content_param);
	} else {
		ZEPHIR_INIT_VAR(&content);
	}
	}
	if (!code) {
		code = &code_sub;
		code = &__$null;
	}
	if (!status) {
		status = &status_sub;
		status = &__$null;
	}
	ZEPHIR_INIT_VAR(&_0);
	object_init_ex(&_0, phalcon_http_response_headers_ce);
	if (zephir_has_constructor(&_0)) {
		ZEPHIR_CALL_METHOD(NULL, &_0, "__construct", NULL, 0);
		zephir_check_call_status();
	}

	zephir_update_property_zval(this_ptr, ZEND_STRL("headers"), &_0);
	ZEPHIR_INIT_VAR(&_1);
	object_init_ex(&_1, phalcon_support_helper_json_encode_ce);
	if (zephir_has_constructor(&_1)) {
		ZEPHIR_CALL_METHOD(NULL, &_1, "__construct", NULL, 0);
		zephir_check_call_status();
	}

	zephir_update_property_zval(this_ptr, ZEND_STRL("encode"), &_1);
	if (!ZEPHIR_IS_NULL(&content)) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "setcontent", NULL, 0, &content);
		zephir_check_call_status();
	}
	if (Z_TYPE_P(code) != IS_NULL) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "setstatuscode", NULL, 0, code, status);
		zephir_check_call_status();
	}
	ZEPHIR_MM_RESTORE();
}

/**
 * Appends a string to the HTTP response body
 */
PHP_METHOD(Phalcon_Http_Response, appendContent)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *content, content_sub, _0, _1;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&content_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(content)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &content);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "getcontent", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_1);
	ZEPHIR_CONCAT_VV(&_1, &_0, content);
	zephir_update_property_zval(this_ptr, ZEND_STRL("content"), &_1);
	RETURN_THIS();
}

/**
 * Gets the HTTP response body
 */
PHP_METHOD(Phalcon_Http_Response, getContent)
{
	zval _1;
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_memory_observe(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("content"), PH_NOISY_CC);
	zephir_cast_to_string(&_1, &_0);
	RETURN_CTOR(&_1);
}

/**
 * Returns cookies set by the user
 */
PHP_METHOD(Phalcon_Http_Response, getCookies)
{

	RETURN_MEMBER(getThis(), "cookies");
}

/**
 * Returns the internal dependency injector
 */
PHP_METHOD(Phalcon_Http_Response, getDI)
{
	zval container, _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&container);
	ZVAL_UNDEF(&_0);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property(&_0, this_ptr, ZEND_STRL("container"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&container, &_0);
	if (Z_TYPE_P(&container) == IS_NULL) {
		ZEPHIR_CALL_CE_STATIC(&container, phalcon_di_di_ce, "getdefault", NULL, 0);
		zephir_check_call_status();
		if (Z_TYPE_P(&container) == IS_NULL) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_http_response_exception_ce, "A dependency injection container is required to access the 'url' service", "phalcon/Http/Response.zep", 153);
			return;
		}
		zephir_update_property_zval(this_ptr, ZEND_STRL("container"), &container);
	}
	RETURN_CCTOR(&container);
}

/**
 * Returns the internal event manager
 */
PHP_METHOD(Phalcon_Http_Response, getEventsManager)
{

	RETURN_MEMBER(getThis(), "eventsManager");
}

/**
 * Returns headers set by the user
 */
PHP_METHOD(Phalcon_Http_Response, getHeaders)
{

	RETURN_MEMBER(getThis(), "headers");
}

/**
 * Returns the reason phrase
 *
 *```php
 * echo $response->getReasonPhrase();
 *```
 */
PHP_METHOD(Phalcon_Http_Response, getReasonPhrase)
{
	zval statusReasonPhrase, _0, _1, _2, _3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&statusReasonPhrase);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property(&_0, this_ptr, ZEND_STRL("headers"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "Status");
	ZEPHIR_CALL_METHOD(&_1, &_0, "get", NULL, 0, &_2);
	zephir_check_call_status();
	ZVAL_LONG(&_3, 4);
	ZEPHIR_INIT_VAR(&statusReasonPhrase);
	zephir_substr(&statusReasonPhrase, &_1, 4 , 0, ZEPHIR_SUBSTR_NO_LENGTH);
	ZEPHIR_INIT_NVAR(&_2);
	if (zephir_is_true(&statusReasonPhrase)) {
		ZEPHIR_CPY_WRT(&_2, &statusReasonPhrase);
	} else {
		ZEPHIR_INIT_NVAR(&_2);
		ZVAL_NULL(&_2);
	}
	RETURN_CCTOR(&_2);
}

/**
 * Returns the status code
 *
 *```php
 * echo $response->getStatusCode();
 *```
 */
PHP_METHOD(Phalcon_Http_Response, getStatusCode)
{
	zval statusCode, _0, _1, _2, _3, _4;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&statusCode);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property(&_0, this_ptr, ZEND_STRL("headers"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "Status");
	ZEPHIR_CALL_METHOD(&_1, &_0, "get", NULL, 0, &_2);
	zephir_check_call_status();
	ZVAL_LONG(&_3, 0);
	ZVAL_LONG(&_4, 3);
	ZEPHIR_INIT_VAR(&statusCode);
	zephir_substr(&statusCode, &_1, 0 , 3 , 0);
	ZEPHIR_INIT_NVAR(&_2);
	if (zephir_is_true(&statusCode)) {
		ZEPHIR_INIT_NVAR(&_2);
		ZVAL_LONG(&_2, zephir_get_intval(&statusCode));
	} else {
		ZEPHIR_INIT_NVAR(&_2);
		ZVAL_NULL(&_2);
	}
	RETURN_CCTOR(&_2);
}

/**
 * Checks if a header exists
 *
 *```php
 * $response->hasHeader("Content-Type");
 *```
 */
PHP_METHOD(Phalcon_Http_Response, hasHeader)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, headers;
	zval name;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&headers);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(name)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &name_param);
	zephir_get_strval(&name, name_param);
	ZEPHIR_CALL_METHOD(&headers, this_ptr, "getheaders", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(&headers, "has", NULL, 0, &name);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Check if the response is already sent
 */
PHP_METHOD(Phalcon_Http_Response, isSent)
{

	RETURN_MEMBER(getThis(), "sent");
}

/**
 * Redirect by HTTP to another action or URL
 *
 *```php
 * // Using a string redirect (internal/external)
 * $response->redirect("posts/index");
 * $response->redirect("http://en.wikipedia.org", true);
 * $response->redirect("http://www.example.com/new-location", true, 301);
 *
 * // Making a redirection based on a named route
 * $response->redirect(
 *     [
 *         "for"        => "index-lang",
 *         "lang"       => "jp",
 *         "controller" => "index",
 *     ]
 * );
 *```
 */
PHP_METHOD(Phalcon_Http_Response, redirect)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long statusCode, ZEPHIR_LAST_CALL_STATUS;
	zend_bool externalRedirect, _11, _0$$5;
	zval *location = NULL, location_sub, *externalRedirect_param = NULL, *statusCode_param = NULL, __$null, header, url, container, matched, view, _8, _9, _12, _1$$5, _2$$5, _3$$6, _4$$6, _5$$6, _6$$10, _7$$10, _10$$11;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&location_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&header);
	ZVAL_UNDEF(&url);
	ZVAL_UNDEF(&container);
	ZVAL_UNDEF(&matched);
	ZVAL_UNDEF(&view);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_1$$5);
	ZVAL_UNDEF(&_2$$5);
	ZVAL_UNDEF(&_3$$6);
	ZVAL_UNDEF(&_4$$6);
	ZVAL_UNDEF(&_5$$6);
	ZVAL_UNDEF(&_6$$10);
	ZVAL_UNDEF(&_7$$10);
	ZVAL_UNDEF(&_10$$11);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 3)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(location)
		Z_PARAM_BOOL(externalRedirect)
		Z_PARAM_LONG(statusCode)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 3, &location, &externalRedirect_param, &statusCode_param);
	if (!location) {
		location = &location_sub;
		ZEPHIR_CPY_WRT(location, &__$null);
	} else {
		ZEPHIR_SEPARATE_PARAM(location);
	}
	if (!externalRedirect_param) {
		externalRedirect = 0;
	} else {
		}
	if (!statusCode_param) {
		statusCode = 302;
	} else {
		}
	if (!(zephir_is_true(location))) {
		ZEPHIR_INIT_NVAR(location);
		ZVAL_STRING(location, "");
	}
	if (externalRedirect) {
		ZEPHIR_CPY_WRT(&header, location);
	} else {
		_0$$5 = Z_TYPE_P(location) == IS_STRING;
		if (_0$$5) {
			ZEPHIR_INIT_VAR(&_1$$5);
			ZVAL_STRING(&_1$$5, "://");
			ZEPHIR_CALL_FUNCTION(&_2$$5, "strstr", NULL, 358, location, &_1$$5);
			zephir_check_call_status();
			_0$$5 = zephir_is_true(&_2$$5);
		}
		if (_0$$5) {
			ZEPHIR_INIT_VAR(&_3$$6);
			ZEPHIR_INIT_VAR(&_4$$6);
			ZVAL_STRING(&_4$$6, "/^[^:\\/?#]++:/");
			ZEPHIR_INIT_VAR(&_5$$6);
			ZVAL_STRING(&_5$$6, "/^[^:\\/?#]++:/");
			ZEPHIR_INIT_VAR(&matched);
			zephir_preg_match(&matched, &_5$$6, location, &_3$$6, 0, 0 , 0 );
			if (zephir_is_true(&matched)) {
				ZEPHIR_CPY_WRT(&header, location);
			} else {
				ZEPHIR_INIT_NVAR(&header);
				ZVAL_NULL(&header);
			}
		} else {
			ZEPHIR_INIT_NVAR(&header);
			ZVAL_NULL(&header);
		}
	}
	ZEPHIR_CALL_METHOD(&container, this_ptr, "getdi", NULL, 0);
	zephir_check_call_status();
	if (!(zephir_is_true(&header))) {
		ZEPHIR_INIT_VAR(&_7$$10);
		ZVAL_STRING(&_7$$10, "url");
		ZEPHIR_CALL_METHOD(&_6$$10, &container, "getshared", NULL, 0, &_7$$10);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(&url, &_6$$10);
		ZEPHIR_CALL_METHOD(&header, &url, "get", NULL, 0, location);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_VAR(&_9);
	ZVAL_STRING(&_9, "view");
	ZEPHIR_CALL_METHOD(&_8, &container, "has", NULL, 0, &_9);
	zephir_check_call_status();
	if (zephir_is_true(&_8)) {
		ZEPHIR_INIT_VAR(&_10$$11);
		ZVAL_STRING(&_10$$11, "view");
		ZEPHIR_CALL_METHOD(&view, &container, "getshared", NULL, 0, &_10$$11);
		zephir_check_call_status();
		if (zephir_instance_of_ev(&view, phalcon_mvc_viewinterface_ce)) {
			ZEPHIR_CALL_METHOD(NULL, &view, "disable", NULL, 0);
			zephir_check_call_status();
		}
	}
	_11 = statusCode < 300;
	if (!(_11)) {
		_11 = statusCode > 308;
	}
	if (_11) {
		statusCode = 302;
	}
	ZVAL_LONG(&_12, statusCode);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setstatuscode", NULL, 0, &_12);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_9);
	ZVAL_STRING(&_9, "Location");
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setheader", NULL, 0, &_9, &header);
	zephir_check_call_status();
	RETURN_THIS();
}

/**
 * Remove a header in the response
 *
 *```php
 * $response->removeHeader("Expires");
 *```
 */
PHP_METHOD(Phalcon_Http_Response, removeHeader)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, _0;
	zval name;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(name)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &name_param);
	zephir_get_strval(&name, name_param);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("headers"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(NULL, &_0, "remove", NULL, 0, &name);
	zephir_check_call_status();
	RETURN_THIS();
}

/**
 * Resets all the established headers
 */
PHP_METHOD(Phalcon_Http_Response, resetHeaders)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property(&_0, this_ptr, ZEND_STRL("headers"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(NULL, &_0, "reset", NULL, 0);
	zephir_check_call_status();
	RETURN_THIS();
}

/**
 * Prints out HTTP response to the client
 */
PHP_METHOD(Phalcon_Http_Response, send)
{
	zend_bool _3$$5;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval __$true, __$false, content, file, _0, _1, _2$$5;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_UNDEF(&content);
	ZVAL_UNDEF(&file);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2$$5);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property(&_0, this_ptr, ZEND_STRL("sent"), PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(zephir_is_true(&_0))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_http_response_exception_ce, "Response was already sent", "phalcon/Http/Response.zep", 343);
		return;
	}
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "sendheaders", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "sendcookies", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, ZEND_STRL("content"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&content, &_1);
	if (Z_TYPE_P(&content) != IS_NULL) {
		zend_print_zval(&content, 0);
	} else {
		zephir_read_property(&_2$$5, this_ptr, ZEND_STRL("file"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CPY_WRT(&file, &_2$$5);
		_3$$5 = Z_TYPE_P(&file) == IS_STRING;
		if (_3$$5) {
			_3$$5 = ((zephir_fast_strlen_ev(&file)) ? 1 : 0);
		}
		if (_3$$5) {
			ZEPHIR_CALL_FUNCTION(NULL, "readfile", NULL, 359, &file);
			zephir_check_call_status();
		}
	}
	if (1) {
		zephir_update_property_zval(this_ptr, ZEND_STRL("sent"), &__$true);
	} else {
		zephir_update_property_zval(this_ptr, ZEND_STRL("sent"), &__$false);
	}
	RETURN_THIS();
}

/**
 * Sends cookies to the client
 */
PHP_METHOD(Phalcon_Http_Response, sendCookies)
{
	zval cookies, _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&cookies);
	ZVAL_UNDEF(&_0);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property(&_0, this_ptr, ZEND_STRL("cookies"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&cookies, &_0);
	if (Z_TYPE_P(&cookies) == IS_OBJECT) {
		ZEPHIR_CALL_METHOD(NULL, &cookies, "send", NULL, 0);
		zephir_check_call_status();
	}
	RETURN_THIS();
}

/**
 * Sends headers to the client
 */
PHP_METHOD(Phalcon_Http_Response, sendHeaders)
{
	zend_bool _3;
	zval eventsManager, headers, result, _0, _1$$3, _2$$3, _4$$5;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&eventsManager);
	ZVAL_UNDEF(&headers);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_4$$5);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property(&_0, this_ptr, ZEND_STRL("headers"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&headers, &_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("eventsManager"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&eventsManager, &_0);
	if (Z_TYPE_P(&eventsManager) == IS_OBJECT) {
		ZEPHIR_INIT_VAR(&_2$$3);
		ZVAL_STRING(&_2$$3, "response:beforeSendHeaders");
		ZEPHIR_CALL_METHOD(&_1$$3, &eventsManager, "fire", NULL, 0, &_2$$3, this_ptr);
		zephir_check_call_status();
		if (ZEPHIR_IS_FALSE_IDENTICAL(&_1$$3)) {
			RETURN_MM_BOOL(0);
		}
	}
	ZEPHIR_CALL_METHOD(&result, &headers, "send", NULL, 0);
	zephir_check_call_status();
	_3 = ZEPHIR_IS_TRUE_IDENTICAL(&result);
	if (_3) {
		_3 = Z_TYPE_P(&eventsManager) == IS_OBJECT;
	}
	if (_3) {
		ZEPHIR_INIT_VAR(&_4$$5);
		ZVAL_STRING(&_4$$5, "response:afterSendHeaders");
		ZEPHIR_CALL_METHOD(NULL, &eventsManager, "fire", NULL, 0, &_4$$5, this_ptr);
		zephir_check_call_status();
	}
	RETURN_THIS();
}

/**
 * Sets Cache headers to use HTTP cache
 *
 *```php
 * $this->response->setCache(60);
 *```
 */
PHP_METHOD(Phalcon_Http_Response, setCache)
{
	zval _1, _3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *minutes_param = NULL, date, _0, _2, _4;
	zend_long minutes, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&date);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(minutes)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &minutes_param);
	if (UNEXPECTED(Z_TYPE_P(minutes_param) != IS_LONG)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'minutes' must be of the type int"));
		RETURN_MM_NULL();
	}
	minutes = Z_LVAL_P(minutes_param);
	ZEPHIR_INIT_VAR(&date);
	object_init_ex(&date, php_date_get_date_ce());
	ZEPHIR_CALL_METHOD(NULL, &date, "__construct", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, minutes);
	ZEPHIR_INIT_VAR(&_1);
	ZEPHIR_CONCAT_SVS(&_1, "+", &_0, " minutes");
	ZEPHIR_CALL_METHOD(NULL, &date, "modify", NULL, 0, &_1);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setexpires", NULL, 0, &date);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_LONG(&_2, ((minutes * 60)));
	ZEPHIR_INIT_VAR(&_3);
	ZEPHIR_CONCAT_SV(&_3, "max-age=", &_2);
	ZEPHIR_INIT_VAR(&_4);
	ZVAL_STRING(&_4, "Cache-Control");
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setheader", NULL, 0, &_4, &_3);
	zephir_check_call_status();
	RETURN_THIS();
}

/**
 * Sets HTTP response body
 *
 *```php
 * $response->setContent("<h1>Hello!</h1>");
 *```
 */
PHP_METHOD(Phalcon_Http_Response, setContent)
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
 * Sets the response content-length
 *
 *```php
 * $response->setContentLength(2048);
 *```
 */
PHP_METHOD(Phalcon_Http_Response, setContentLength)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *contentLength_param = NULL, _0, _1;
	zend_long contentLength, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(contentLength)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &contentLength_param);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "Content-Length");
	ZVAL_LONG(&_1, contentLength);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setheader", NULL, 0, &_0, &_1);
	zephir_check_call_status();
	RETURN_THIS();
}

/**
 * Sets the response content-type mime, optionally the charset
 *
 *```php
 * $response->setContentType("application/pdf");
 * $response->setContentType("text/plain", "UTF-8");
 *```
 */
PHP_METHOD(Phalcon_Http_Response, setContentType)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *contentType_param = NULL, *charset = NULL, charset_sub, __$null, _0$$3, _1;
	zval contentType;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&contentType);
	ZVAL_UNDEF(&charset_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_STR(contentType)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(charset)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &contentType_param, &charset);
	zephir_get_strval(&contentType, contentType_param);
	if (!charset) {
		charset = &charset_sub;
		charset = &__$null;
	}
	if (Z_TYPE_P(charset) != IS_NULL) {
		ZEPHIR_INIT_VAR(&_0$$3);
		ZEPHIR_CONCAT_SV(&_0$$3, "; charset=", charset);
		zephir_concat_self(&contentType, &_0$$3);
	}
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "Content-Type");
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setheader", NULL, 0, &_1, &contentType);
	zephir_check_call_status();
	RETURN_THIS();
}

/**
 * Sets a cookies bag for the response externally
 */
PHP_METHOD(Phalcon_Http_Response, setCookies)
{
	zval *cookies, cookies_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&cookies_sub);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(cookies, phalcon_http_response_cookiesinterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &cookies);
	zephir_update_property_zval(this_ptr, ZEND_STRL("cookies"), cookies);
	RETURN_THISW();
}

/**
 * Sets the dependency injector
 */
PHP_METHOD(Phalcon_Http_Response, setDI)
{
	zval *container, container_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&container_sub);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(container, phalcon_di_diinterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &container);
	zephir_update_property_zval(this_ptr, ZEND_STRL("container"), container);
}

/**
 * Set a custom ETag
 *
 *```php
 * $response->setEtag(
 *     md5(
 *         time()
 *     )
 * );
 *```
 */
PHP_METHOD(Phalcon_Http_Response, setEtag)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *etag_param = NULL, _0;
	zval etag;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&etag);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(etag)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &etag_param);
	zephir_get_strval(&etag, etag_param);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "Etag");
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setheader", NULL, 0, &_0, &etag);
	zephir_check_call_status();
	RETURN_THIS();
}

/**
 * Sets an Expires header in the response that allows to use the HTTP cache
 *
 *```php
 * $this->response->setExpires(
 *     new DateTime()
 * );
 *```
 */
PHP_METHOD(Phalcon_Http_Response, setExpires)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *datetime, datetime_sub, date, _0, _1, _2, _3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&datetime_sub);
	ZVAL_UNDEF(&date);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(datetime, php_date_get_date_ce())
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &datetime);
	ZEPHIR_INIT_VAR(&date);
	if (zephir_clone(&date, datetime) == FAILURE) {
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(&_0);
	object_init_ex(&_0, php_date_get_timezone_ce());
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "UTC");
	ZEPHIR_CALL_METHOD(NULL, &_0, "__construct", NULL, 0, &_1);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &date, "settimezone", NULL, 0, &_0);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "D, d M Y H:i:s");
	ZEPHIR_CALL_METHOD(&_2, &date, "format", NULL, 0, &_1);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_3);
	ZEPHIR_CONCAT_VS(&_3, &_2, " GMT");
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "Expires");
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setheader", NULL, 0, &_1, &_3);
	zephir_check_call_status();
	RETURN_THIS();
}

/**
 * Sets the events manager
 */
PHP_METHOD(Phalcon_Http_Response, setEventsManager)
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
 * Sets an attached file to be sent at the end of the request
 */
PHP_METHOD(Phalcon_Http_Response, setFileToSend)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *filePath_param = NULL, *attachmentName = NULL, attachmentName_sub, *attachment = NULL, attachment_sub, __$true, __$null, basePath, basePathEncoding, _0$$6, _1$$5, _2$$7, _3$$7, _4$$7, _5$$8, _6$$8, _7$$8;
	zval filePath;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&filePath);
	ZVAL_UNDEF(&attachmentName_sub);
	ZVAL_UNDEF(&attachment_sub);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&basePath);
	ZVAL_UNDEF(&basePathEncoding);
	ZVAL_UNDEF(&_0$$6);
	ZVAL_UNDEF(&_1$$5);
	ZVAL_UNDEF(&_2$$7);
	ZVAL_UNDEF(&_3$$7);
	ZVAL_UNDEF(&_4$$7);
	ZVAL_UNDEF(&_5$$8);
	ZVAL_UNDEF(&_6$$8);
	ZVAL_UNDEF(&_7$$8);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 3)
		Z_PARAM_STR(filePath)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(attachmentName)
		Z_PARAM_ZVAL(attachment)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 2, &filePath_param, &attachmentName, &attachment);
	zephir_get_strval(&filePath, filePath_param);
	if (!attachmentName) {
		attachmentName = &attachmentName_sub;
		attachmentName = &__$null;
	}
	if (!attachment) {
		attachment = &attachment_sub;
		attachment = &__$true;
	}
	ZEPHIR_INIT_VAR(&basePathEncoding);
	ZVAL_STRING(&basePathEncoding, "ASCII");
	if (Z_TYPE_P(attachmentName) != IS_STRING) {
		ZEPHIR_CALL_METHOD(&basePath, this_ptr, "getbasename", NULL, 360, &filePath);
		zephir_check_call_status();
	} else {
		ZEPHIR_CPY_WRT(&basePath, attachmentName);
	}
	if (zephir_is_true(attachment)) {
		if ((zephir_function_exists_ex(ZEND_STRL("mb_detect_encoding")) == SUCCESS)) {
			ZEPHIR_CALL_FUNCTION(&_0$$6, "mb_detect_order", NULL, 361);
			zephir_check_call_status();
			ZEPHIR_CALL_FUNCTION(&basePathEncoding, "mb_detect_encoding", NULL, 324, &basePath, &_0$$6, &__$true);
			zephir_check_call_status();
		}
		ZEPHIR_INIT_VAR(&_1$$5);
		ZVAL_STRING(&_1$$5, "Content-Description: File Transfer");
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "setrawheader", NULL, 0, &_1$$5);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(&_1$$5);
		ZVAL_STRING(&_1$$5, "Content-Type: application/octet-stream");
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "setrawheader", NULL, 0, &_1$$5);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(&_1$$5);
		ZVAL_STRING(&_1$$5, "Content-Transfer-Encoding: binary");
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "setrawheader", NULL, 0, &_1$$5);
		zephir_check_call_status();
		if (!ZEPHIR_IS_STRING(&basePathEncoding, "ASCII")) {
			ZEPHIR_CALL_FUNCTION(&_2$$7, "rawurlencode", NULL, 328, &basePath);
			zephir_check_call_status();
			ZEPHIR_CPY_WRT(&basePath, &_2$$7);
			ZEPHIR_INIT_VAR(&_3$$7);
			zephir_fast_strtolower(&_3$$7, &basePathEncoding);
			ZEPHIR_INIT_VAR(&_4$$7);
			ZEPHIR_CONCAT_SVSVSV(&_4$$7, "Content-Disposition: attachment; filename=", &basePath, "; filename*=", &_3$$7, "''", &basePath);
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "setrawheader", NULL, 0, &_4$$7);
			zephir_check_call_status();
		} else {
			ZEPHIR_INIT_VAR(&_5$$8);
			ZVAL_STRING(&_5$$8, "\15\17\\\"");
			ZEPHIR_CALL_FUNCTION(&_6$$8, "addcslashes", NULL, 215, &basePath, &_5$$8);
			zephir_check_call_status();
			ZEPHIR_CPY_WRT(&basePath, &_6$$8);
			ZEPHIR_INIT_VAR(&_7$$8);
			ZEPHIR_CONCAT_SVS(&_7$$8, "Content-Disposition: attachment; filename=\"", &basePath, "\"");
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "setrawheader", NULL, 0, &_7$$8);
			zephir_check_call_status();
		}
	}
	zephir_update_property_zval(this_ptr, ZEND_STRL("file"), &filePath);
	RETURN_THIS();
}

/**
 * Overwrites a header in the response
 *
 *```php
 * $response->setHeader("Content-Type", "text/plain");
 *```
 */
PHP_METHOD(Phalcon_Http_Response, setHeader)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *value, value_sub, _0;
	zval name;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&value_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(name)
		Z_PARAM_ZVAL(value)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &name_param, &value);
	zephir_get_strval(&name, name_param);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("headers"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(NULL, &_0, "set", NULL, 0, &name, value);
	zephir_check_call_status();
	RETURN_THIS();
}

/**
 * Sets a headers bag for the response externally
 */
PHP_METHOD(Phalcon_Http_Response, setHeaders)
{
	zend_string *_3;
	zend_ulong _2;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *headers, headers_sub, data, name, value, *_0, _1, _4$$3, _5$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&headers_sub);
	ZVAL_UNDEF(&data);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$4);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(headers, phalcon_http_response_headersinterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &headers);
	ZEPHIR_CALL_METHOD(&data, headers, "toarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&data, 0, "phalcon/Http/Response.zep", 628);
	if (Z_TYPE_P(&data) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&data), _2, _3, _0)
		{
			ZEPHIR_INIT_NVAR(&name);
			if (_3 != NULL) { 
				ZVAL_STR_COPY(&name, _3);
			} else {
				ZVAL_LONG(&name, _2);
			}
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _0);
			zephir_read_property(&_4$$3, this_ptr, ZEND_STRL("headers"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_CALL_METHOD(NULL, &_4$$3, "set", NULL, 0, &name, &value);
			zephir_check_call_status();
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &data, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_1, &data, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_1)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&name, &data, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&value, &data, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property(&_5$$4, this_ptr, ZEND_STRL("headers"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_CALL_METHOD(NULL, &_5$$4, "set", NULL, 0, &name, &value);
				zephir_check_call_status();
			ZEPHIR_CALL_METHOD(NULL, &data, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_INIT_NVAR(&name);
	RETURN_THIS();
}

/**
 * Sets HTTP response body. The parameter is automatically converted to JSON
 * and also sets default header: Content-Type: "application/json; charset=UTF-8"
 *
 *```php
 * $response->setJsonContent(
 *     [
 *         "status" => "OK",
 *     ]
 * );
 *```
 */
PHP_METHOD(Phalcon_Http_Response, setJsonContent)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long jsonOptions, depth, ZEPHIR_LAST_CALL_STATUS;
	zval *content, content_sub, *jsonOptions_param = NULL, *depth_param = NULL, _0, _1, _2, _3, _4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&content_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZEND_PARSE_PARAMETERS_START(1, 3)
		Z_PARAM_ZVAL(content)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(jsonOptions)
		Z_PARAM_LONG(depth)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 2, &content, &jsonOptions_param, &depth_param);
	if (!jsonOptions_param) {
		jsonOptions = 0;
	} else {
		}
	if (!depth_param) {
		depth = 512;
	} else {
		}
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "application/json");
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setcontenttype", NULL, 0, &_0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, ZEND_STRL("encode"), PH_NOISY_CC | PH_READONLY);
	ZVAL_LONG(&_3, jsonOptions);
	ZVAL_LONG(&_4, depth);
	ZEPHIR_CALL_METHOD(&_2, &_1, "__invoke", NULL, 0, content, &_3, &_4);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setcontent", NULL, 0, &_2);
	zephir_check_call_status();
	RETURN_THIS();
}

/**
 * Sets Last-Modified header
 *
 *```php
 * $this->response->setLastModified(
 *     new DateTime()
 * );
 *```
 */
PHP_METHOD(Phalcon_Http_Response, setLastModified)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *datetime, datetime_sub, date, _0, _1, _2, _3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&datetime_sub);
	ZVAL_UNDEF(&date);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(datetime, php_date_get_date_ce())
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &datetime);
	ZEPHIR_INIT_VAR(&date);
	if (zephir_clone(&date, datetime) == FAILURE) {
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(&_0);
	object_init_ex(&_0, php_date_get_timezone_ce());
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "UTC");
	ZEPHIR_CALL_METHOD(NULL, &_0, "__construct", NULL, 0, &_1);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &date, "settimezone", NULL, 0, &_0);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "D, d M Y H:i:s");
	ZEPHIR_CALL_METHOD(&_2, &date, "format", NULL, 0, &_1);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_3);
	ZEPHIR_CONCAT_VS(&_3, &_2, " GMT");
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "Last-Modified");
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setheader", NULL, 0, &_1, &_3);
	zephir_check_call_status();
	RETURN_THIS();
}

/**
 * Sends a Not-Modified response
 */
PHP_METHOD(Phalcon_Http_Response, setNotModified)
{
	zval _0, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZVAL_LONG(&_0, 304);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "Not modified");
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setstatuscode", NULL, 0, &_0, &_1);
	zephir_check_call_status();
	RETURN_THIS();
}

/**
 * Sets the HTTP response code
 *
 *```php
 * $response->setStatusCode(404, "Not Found");
 *```
 */
PHP_METHOD(Phalcon_Http_Response, setStatusCode)
{
	zend_bool _6$$3, _11$$5;
	zend_string *_5;
	zend_ulong _4;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_9 = NULL;
	zval message, _17, _20;
	zval *code_param = NULL, *message_param = NULL, currentHeadersRaw, key, statusCodes, defaultMessage, _0, _1, *_2, _3, _15, _16, _18, _19, _21, _7$$3, _8$$3, _10$$4, _12$$5, _13$$5, _14$$6;
	zend_long code, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&currentHeadersRaw);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&statusCodes);
	ZVAL_UNDEF(&defaultMessage);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_15);
	ZVAL_UNDEF(&_16);
	ZVAL_UNDEF(&_18);
	ZVAL_UNDEF(&_19);
	ZVAL_UNDEF(&_21);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_8$$3);
	ZVAL_UNDEF(&_10$$4);
	ZVAL_UNDEF(&_12$$5);
	ZVAL_UNDEF(&_13$$5);
	ZVAL_UNDEF(&_14$$6);
	ZVAL_UNDEF(&message);
	ZVAL_UNDEF(&_17);
	ZVAL_UNDEF(&_20);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_LONG(code)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR_OR_NULL(message)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &code_param, &message_param);
	if (!message_param) {
		ZEPHIR_INIT_VAR(&message);
	} else {
		zephir_get_strval(&message, message_param);
	}
	zephir_read_property(&_0, this_ptr, ZEND_STRL("headers"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&currentHeadersRaw, &_0, "toarray", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_1);
	zephir_is_iterable(&currentHeadersRaw, 0, "phalcon/Http/Response.zep", 717);
	if (Z_TYPE_P(&currentHeadersRaw) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&currentHeadersRaw), _4, _5, _2)
		{
			ZEPHIR_INIT_NVAR(&key);
			if (_5 != NULL) { 
				ZVAL_STR_COPY(&key, _5);
			} else {
				ZVAL_LONG(&key, _4);
			}
			ZEPHIR_INIT_NVAR(&_1);
			ZVAL_COPY(&_1, _2);
			_6$$3 = Z_TYPE_P(&key) == IS_STRING;
			if (_6$$3) {
				ZEPHIR_INIT_NVAR(&_7$$3);
				ZVAL_STRING(&_7$$3, "HTTP/");
				ZEPHIR_CALL_FUNCTION(&_8$$3, "strstr", &_9, 358, &key, &_7$$3);
				zephir_check_call_status();
				_6$$3 = zephir_is_true(&_8$$3);
			}
			if (_6$$3) {
				zephir_read_property(&_10$$4, this_ptr, ZEND_STRL("headers"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_CALL_METHOD(NULL, &_10$$4, "remove", NULL, 0, &key);
				zephir_check_call_status();
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &currentHeadersRaw, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_3, &currentHeadersRaw, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_3)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&key, &currentHeadersRaw, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&_1, &currentHeadersRaw, "current", NULL, 0);
			zephir_check_call_status();
				_11$$5 = Z_TYPE_P(&key) == IS_STRING;
				if (_11$$5) {
					ZEPHIR_INIT_NVAR(&_12$$5);
					ZVAL_STRING(&_12$$5, "HTTP/");
					ZEPHIR_CALL_FUNCTION(&_13$$5, "strstr", &_9, 358, &key, &_12$$5);
					zephir_check_call_status();
					_11$$5 = zephir_is_true(&_13$$5);
				}
				if (_11$$5) {
					zephir_read_property(&_14$$6, this_ptr, ZEND_STRL("headers"), PH_NOISY_CC | PH_READONLY);
					ZEPHIR_CALL_METHOD(NULL, &_14$$6, "remove", NULL, 0, &key);
					zephir_check_call_status();
				}
			ZEPHIR_CALL_METHOD(NULL, &currentHeadersRaw, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&_1);
	ZEPHIR_INIT_NVAR(&key);
	if (ZEPHIR_IS_NULL(&message)) {
		ZEPHIR_INIT_VAR(&statusCodes);
		zephir_create_array(&statusCodes, 89, 0);
		add_index_stringl(&statusCodes, 100, SL("Continue"));
		add_index_stringl(&statusCodes, 101, SL("Switching Protocols"));
		add_index_stringl(&statusCodes, 102, SL("Processing"));
		add_index_stringl(&statusCodes, 103, SL("Early Hints"));
		add_index_stringl(&statusCodes, 200, SL("OK"));
		add_index_stringl(&statusCodes, 201, SL("Created"));
		add_index_stringl(&statusCodes, 202, SL("Accepted"));
		add_index_stringl(&statusCodes, 203, SL("Non-Authoritative Information"));
		add_index_stringl(&statusCodes, 204, SL("No Content"));
		add_index_stringl(&statusCodes, 205, SL("Reset Content"));
		add_index_stringl(&statusCodes, 206, SL("Partial Content"));
		add_index_stringl(&statusCodes, 207, SL("Multi-status"));
		add_index_stringl(&statusCodes, 208, SL("Already Reported"));
		add_index_stringl(&statusCodes, 226, SL("IM Used"));
		add_index_stringl(&statusCodes, 300, SL("Multiple Choices"));
		add_index_stringl(&statusCodes, 301, SL("Moved Permanently"));
		add_index_stringl(&statusCodes, 302, SL("Found"));
		add_index_stringl(&statusCodes, 303, SL("See Other"));
		add_index_stringl(&statusCodes, 304, SL("Not Modified"));
		add_index_stringl(&statusCodes, 305, SL("Use Proxy"));
		add_index_stringl(&statusCodes, 306, SL("Switch Proxy"));
		add_index_stringl(&statusCodes, 307, SL("Temporary Redirect"));
		add_index_stringl(&statusCodes, 308, SL("Permanent Redirect"));
		add_index_stringl(&statusCodes, 400, SL("Bad Request"));
		add_index_stringl(&statusCodes, 401, SL("Unauthorized"));
		add_index_stringl(&statusCodes, 402, SL("Payment Required"));
		add_index_stringl(&statusCodes, 403, SL("Forbidden"));
		add_index_stringl(&statusCodes, 404, SL("Not Found"));
		add_index_stringl(&statusCodes, 405, SL("Method Not Allowed"));
		add_index_stringl(&statusCodes, 406, SL("Not Acceptable"));
		add_index_stringl(&statusCodes, 407, SL("Proxy Authentication Required"));
		add_index_stringl(&statusCodes, 408, SL("Request Time-out"));
		add_index_stringl(&statusCodes, 409, SL("Conflict"));
		add_index_stringl(&statusCodes, 410, SL("Gone"));
		add_index_stringl(&statusCodes, 411, SL("Length Required"));
		add_index_stringl(&statusCodes, 412, SL("Precondition Failed"));
		add_index_stringl(&statusCodes, 413, SL("Request Entity Too Large"));
		add_index_stringl(&statusCodes, 414, SL("Request-URI Too Large"));
		add_index_stringl(&statusCodes, 415, SL("Unsupported Media Type"));
		add_index_stringl(&statusCodes, 416, SL("Requested range not satisfiable"));
		add_index_stringl(&statusCodes, 417, SL("Expectation Failed"));
		add_index_stringl(&statusCodes, 418, SL("I'm a teapot"));
		add_index_stringl(&statusCodes, 421, SL("Misdirected Request"));
		add_index_stringl(&statusCodes, 422, SL("Unprocessable Entity"));
		add_index_stringl(&statusCodes, 423, SL("Locked"));
		add_index_stringl(&statusCodes, 424, SL("Failed Dependency"));
		add_index_stringl(&statusCodes, 425, SL("Unordered Collection"));
		add_index_stringl(&statusCodes, 426, SL("Upgrade Required"));
		add_index_stringl(&statusCodes, 428, SL("Precondition Required"));
		add_index_stringl(&statusCodes, 429, SL("Too Many Requests"));
		add_index_stringl(&statusCodes, 431, SL("Request Header Fields Too Large"));
		add_index_stringl(&statusCodes, 451, SL("Unavailable For Legal Reasons"));
		add_index_stringl(&statusCodes, 500, SL("Internal Server Error"));
		add_index_stringl(&statusCodes, 501, SL("Not Implemented"));
		add_index_stringl(&statusCodes, 502, SL("Bad Gateway"));
		add_index_stringl(&statusCodes, 503, SL("Service Unavailable"));
		add_index_stringl(&statusCodes, 504, SL("Gateway Time-out"));
		add_index_stringl(&statusCodes, 505, SL("HTTP Version not supported"));
		add_index_stringl(&statusCodes, 506, SL("Variant Also Negotiates"));
		add_index_stringl(&statusCodes, 507, SL("Insufficient Storage"));
		add_index_stringl(&statusCodes, 508, SL("Loop Detected"));
		add_index_stringl(&statusCodes, 510, SL("Not Extended"));
		add_index_stringl(&statusCodes, 511, SL("Network Authentication Required"));
		add_index_stringl(&statusCodes, 218, SL("This is fine"));
		add_index_stringl(&statusCodes, 419, SL("Page Expired"));
		add_index_stringl(&statusCodes, 420, SL("Method Failure"));
		add_index_stringl(&statusCodes, 440, SL("Login Time-out"));
		add_index_stringl(&statusCodes, 444, SL("No Response"));
		add_index_stringl(&statusCodes, 449, SL("Retry With"));
		add_index_stringl(&statusCodes, 450, SL("Blocked by Windows Parental Controls (Microsoft)"));
		add_index_stringl(&statusCodes, 494, SL("Request header too large"));
		add_index_stringl(&statusCodes, 495, SL("SSL Certificate Error"));
		add_index_stringl(&statusCodes, 496, SL("SSL Certificate Required"));
		add_index_stringl(&statusCodes, 497, SL("HTTP Request Sent to HTTPS Port"));
		add_index_stringl(&statusCodes, 498, SL("Invalid Token (Esri)"));
		add_index_stringl(&statusCodes, 499, SL("Client Closed Request"));
		add_index_stringl(&statusCodes, 509, SL("Bandwidth Limit Exceeded"));
		add_index_stringl(&statusCodes, 520, SL("Unknown Error"));
		add_index_stringl(&statusCodes, 521, SL("Web Server Is Down"));
		add_index_stringl(&statusCodes, 522, SL("Connection Timed Out"));
		add_index_stringl(&statusCodes, 523, SL("Origin Is Unreachable"));
		add_index_stringl(&statusCodes, 524, SL("A Timeout Occurred"));
		add_index_stringl(&statusCodes, 525, SL("SSL Handshake Failed"));
		add_index_stringl(&statusCodes, 526, SL("Invalid SSL Certificate"));
		add_index_stringl(&statusCodes, 527, SL("Railgun Error"));
		add_index_stringl(&statusCodes, 530, SL("Origin DNS Error"));
		add_index_stringl(&statusCodes, 598, SL("Network read timeout error"));
		add_index_stringl(&statusCodes, 599, SL("Network Connect Timeout Error"));
		if (UNEXPECTED(!(zephir_array_isset_long(&statusCodes, code)))) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_http_response_exception_ce, "Non-standard statuscode given without a message", "phalcon/Http/Response.zep", 824);
			return;
		}
		zephir_memory_observe(&defaultMessage);
		zephir_array_fetch_long(&defaultMessage, &statusCodes, code, PH_NOISY, "phalcon/Http/Response.zep", 827);
		zephir_get_strval(&message, &defaultMessage);
	}
	zephir_read_property(&_15, this_ptr, ZEND_STRL("headers"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_16);
	ZVAL_LONG(&_16, code);
	ZEPHIR_INIT_VAR(&_17);
	ZEPHIR_CONCAT_SVSV(&_17, "HTTP/1.1 ", &_16, " ", &message);
	ZEPHIR_CALL_METHOD(NULL, &_15, "setraw", NULL, 0, &_17);
	zephir_check_call_status();
	zephir_read_property(&_18, this_ptr, ZEND_STRL("headers"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_19);
	ZVAL_LONG(&_19, code);
	ZEPHIR_INIT_VAR(&_20);
	ZEPHIR_CONCAT_VSV(&_20, &_19, " ", &message);
	ZEPHIR_INIT_VAR(&_21);
	ZVAL_STRING(&_21, "Status");
	ZEPHIR_CALL_METHOD(NULL, &_18, "set", NULL, 0, &_21, &_20);
	zephir_check_call_status();
	RETURN_THIS();
}

/**
 * Send a raw header to the response
 *
 *```php
 * $response->setRawHeader("HTTP/1.1 404 Not Found");
 *```
 */
PHP_METHOD(Phalcon_Http_Response, setRawHeader)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *header_param = NULL, _0;
	zval header;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&header);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(header)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &header_param);
	zephir_get_strval(&header, header_param);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("headers"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(NULL, &_0, "setraw", NULL, 0, &header);
	zephir_check_call_status();
	RETURN_THIS();
}

/**
 * @todo Remove this when we get traits
 */
PHP_METHOD(Phalcon_Http_Response, getBasename)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *uri_param = NULL, *suffix = NULL, suffix_sub, __$null, filename, matches, _0, _1, _2, _3, _4, _5, _6$$3, _7$$3, _8$$3, _9$$3;
	zval uri;

	ZVAL_UNDEF(&uri);
	ZVAL_UNDEF(&suffix_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&filename);
	ZVAL_UNDEF(&matches);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_8$$3);
	ZVAL_UNDEF(&_9$$3);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_STR(uri)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(suffix)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &uri_param, &suffix);
	if (UNEXPECTED(Z_TYPE_P(uri_param) != IS_STRING && Z_TYPE_P(uri_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'uri' must be of the type string"));
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(uri_param) == IS_STRING)) {
		zephir_get_strval(&uri, uri_param);
	} else {
		ZEPHIR_INIT_VAR(&uri);
	}
	if (!suffix) {
		suffix = &suffix_sub;
		suffix = &__$null;
	}
	ZEPHIR_INIT_VAR(&_0);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "/");
	zephir_fast_trim(&_0, &uri, &_1, ZEPHIR_TRIM_RIGHT);
	zephir_get_strval(&uri, &_0);
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "/");
	ZEPHIR_INIT_VAR(&_3);
	ZVAL_STRING(&_3, "@");
	ZEPHIR_CALL_FUNCTION(&_4, "preg_quote", NULL, 354, &_2, &_3);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_5);
	ZEPHIR_CONCAT_SVS(&_5, "@[^", &_4, "]+$@");
	ZEPHIR_INIT_NVAR(&_2);
	zephir_preg_match(&_2, &_5, &uri, &matches, 0, 0 , 0 );
	if (zephir_is_true(&_2)) {
		zephir_memory_observe(&filename);
		zephir_array_fetch_long(&filename, &matches, 0, PH_NOISY, "phalcon/Http/Response.zep", 867);
	} else {
		ZEPHIR_INIT_NVAR(&filename);
		ZVAL_STRING(&filename, "");
	}
	if (zephir_is_true(suffix)) {
		ZEPHIR_INIT_VAR(&_6$$3);
		ZVAL_STRING(&_6$$3, "@");
		ZEPHIR_CALL_FUNCTION(&_7$$3, "preg_quote", NULL, 354, suffix, &_6$$3);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_8$$3);
		ZEPHIR_CONCAT_SVS(&_8$$3, "@", &_7$$3, "$@");
		ZEPHIR_INIT_NVAR(&_6$$3);
		ZVAL_STRING(&_6$$3, "");
		ZEPHIR_CALL_FUNCTION(&_9$$3, "preg_replace", NULL, 41, &_8$$3, &_6$$3, &filename);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(&filename, &_9$$3);
	}
	RETURN_CCTOR(&filename);
}

zend_object *zephir_init_properties_Phalcon_Http_Response(zend_class_entry *class_type)
{
		zval _0, _1$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);
	

		ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
		zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	
	{
		zval local_this_ptr, *this_ptr = &local_this_ptr;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		zephir_read_property_ex(&_0, this_ptr, ZEND_STRL("statusCodes"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_1$$3);
			array_init(&_1$$3);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("statusCodes"), &_1$$3);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}
}

