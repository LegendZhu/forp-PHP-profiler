/*
  +----------------------------------------------------------------------+
  | Forp	                                                         |
  +----------------------------------------------------------------------+
  | Copyright (c) 2012 Anthony Terrien                                   |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Anthony Terrien <forp@anthonyterrien.com>                    |
  +----------------------------------------------------------------------+
 */
#ifndef PHP_FORP_H
#define PHP_FORP_H

#define FORP_VERSION                        "1.1.0"

#define FORP_FLAG_TIME                      0x0001
#define FORP_FLAG_MEMORY                    0x0002
#define FORP_FLAG_CPU                       0x0004

#define FORP_FLAG_ALIAS                     0x0020
#define FORP_FLAG_CAPTION                   0x0040
#define FORP_FLAG_GROUPS                    0x0080
#define FORP_FLAG_HIGHLIGHT                 0x0100
#define FORP_FLAG_ANNOTATIONS               0x01E0

#define FORP_FLAG_ALL                       0x03FF

extern zend_module_entry forp_module_entry;
#define phpext_forp_ptr &forp_module_entry

#ifdef PHP_WIN32
#define PHP_FORP_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#define PHP_FORP_API __attribute__ ((visibility("default")))
#else
#define PHP_FORP_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#include "forp.h"

PHP_MINIT_FUNCTION(forp);
PHP_MSHUTDOWN_FUNCTION(forp);
PHP_RINIT_FUNCTION(forp);
PHP_RSHUTDOWN_FUNCTION(forp);
PHP_MINFO_FUNCTION(forp);
ZEND_MODULE_POST_ZEND_DEACTIVATE_D(forp);

PHP_FUNCTION(forp_enable);
PHP_FUNCTION(forp_start);
PHP_FUNCTION(forp_end);
PHP_FUNCTION(forp_dump);
PHP_FUNCTION(forp_print);
PHP_FUNCTION(forp_info);
PHP_FUNCTION(forp_inspect);
PHP_FUNCTION(forp_json);
PHP_FUNCTION(forp_json_google_tracer);

/* global variables */
ZEND_BEGIN_MODULE_GLOBALS(forp)
    int flags;
	int started;
	int nesting_level;
	forp_node_t *main;
	forp_node_t *current_node;
	int stack_len;
	forp_node_t **stack;
	zval *dump;
	long max_nesting_level;
	int no_internals;
    double stime;
    double utime;
    //struct hashtable_t *functions;
    int inspect_len;
    forp_var_t **inspect;
    long inspect_depth_array;
    long inspect_depth_object;
ZEND_END_MODULE_GLOBALS(forp)

ZEND_DECLARE_MODULE_GLOBALS(forp);

#ifdef ZTS
#define FORP_G(v) TSRMG(forp_globals_id, zend_forp_globals *, v)
#else
#define FORP_G(v) (forp_globals.v)
#endif

#endif	/* PHP_FORP_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
