/*
 +----------------------------------------------------------------------+
 | PHP Version 5                                                        |
 +----------------------------------------------------------------------+
 | Copyright (c) 1997-2011 The PHP Group                                |
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include <stdio.h>
#include "forp_string.h"

#ifdef ZTS
#include "TSRM.h"
#endif

/* {{{ forp_substr_replace
 */
char* forp_strndup(const char* s, size_t n) {
    size_t slen = (size_t)strlen(s);
    char* copy;
    if (slen < n) {
        n = slen;
    }
    copy = malloc(n+1);
    if (copy) {
        memcpy(copy, s, n);
        copy[n] = 0;
    }
    return copy;
}
/* }}} */

/* {{{ forp_addslashes
 */
char *forp_addslashes(char *subject TSRMLS_DC) {
    return subject;
    /*char *result = NULL;
    char c;
    size_t sSize = (size_t)strlen(subject);
    uint rSize = 0;
    uint i = 0;
    uint j = 0;
    for(i = 0; i < sSize; i++) {
        c  = subject[i];
        if (c == '/' || c == '\\' || c == '\"' || c == '\'') {
            rSize++;
        }
    }
    if ( rSize > 0 ) {
        //result = malloc(sSize + rSize + 1);
        if ( result != NULL ) {
            for(i = 0; i < sSize; i++) {
                c = subject[i];
                if (c == '/' || c == '\\'  || c == '\"' || c == '\'') {
                    result[j++] = '\\';
                }
                result[j++] = c;
            }
            //subject = strdup(result);
            //free(result);
        }
    }
    return subject;*/
}
/* }}} */

/* {{{ forp_substr_replace
 *
 * @param char* subject
 * @param uint start
 * @param uint len
 * @param char* replace
 * @return char*
 */
char *forp_substr_replace(char *subject, char *replace, unsigned int start, unsigned int len) {
    char *ns = NULL;
    size_t size;
    if (
            subject != NULL && replace != NULL
            && start >= 0 && len > 0
            ) {
        size = strlen(subject);
        ns = malloc(sizeof (*ns) * (size - len + strlen(replace) + 1));
        if (ns) {
            memcpy(ns, subject, start);
            memcpy(&ns[start], replace, strlen(replace));
            memcpy(&ns[start + strlen(replace)], &subject[start + len], size - len - start + 1);
        }
        subject = strdup(ns);
        free(ns);
    }
    return subject;
}
/* }}} */

/* {{{ forp_str_replace
 *
 * @param char* search
 * @param char* replace
 * @param char* subject
 * @return char*
 */
char *forp_str_replace(char *search,  char *replace, char *subject TSRMLS_DC) {
    char *ret, *sr;
    size_t i, count = 0;
    size_t newlen = strlen(replace);
    size_t oldlen = strlen(search);

    if (newlen != oldlen) {
        for (i = 0; subject[i] != '\0';) {
            if (memcmp(&subject[i], search, oldlen) == 0)
                count++, i += oldlen;
            else
                i++;
        }
    } else
        i = strlen(subject);

    ret = malloc(i + 1 + count * (newlen - oldlen));
    if (ret == NULL)
        return NULL;

    sr = ret;
    while (*subject) {
        if (memcmp(subject, search, oldlen) == 0) {
            memcpy(sr, replace, newlen);
            sr += newlen;
            subject += oldlen;
        } else
            *sr++ = *subject++;
    }
    *sr = '\0';

    return ret;
}
/* }}} */