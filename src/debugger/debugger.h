/*
   +----------------------------------------------------------------------+
   | Xdebug                                                               |
   +----------------------------------------------------------------------+
   | Copyright (c) 2002-2019 Derick Rethans                               |
   +----------------------------------------------------------------------+
   | This source file is subject to version 1.01 of the Xdebug license,   |
   | that is bundled with this package in the file LICENSE, and is        |
   | available at through the world-wide-web at                           |
   | https://xdebug.org/license.php                                       |
   | If you did not receive a copy of the Xdebug license and are unable   |
   | to obtain it through the world-wide-web, please send a note to       |
   | derick@xdebug.org so we can mail you a copy immediately.             |
   +----------------------------------------------------------------------+
   | Authors: Derick Rethans <derick@xdebug.org>                          |
   +----------------------------------------------------------------------+
 */

#ifndef __XDEBUG_DEBUGGER_H__
#define __XDEBUG_DEBUGGER_H__

#include "com.h"
#include "lib/private.h"

typedef struct _xdebug_debugger_globals_t {
	int           status;
	int           reason;
	const char   *lastcmd;
	char         *lasttransid;

	zend_bool     remote_connection_enabled;
	zend_ulong    remote_connection_pid;
	zend_bool     breakpoints_allowed;
	xdebug_con    context;
	unsigned int  breakpoint_count;
	unsigned int  no_exec;
	char         *ide_key; /* As Xdebug uses it, from environment, USER, USERNAME or empty */
	FILE         *remote_log_file;  /* File handler for protocol log */

	/* breakpoint resolving */
	size_t        function_count;
	size_t        class_count;
	xdebug_hash  *breakable_lines_map;

	/* output redirection */
	int           stdout_mode;
} xdebug_debugger_globals_t;

typedef struct _xdebug_debugger_settings_t {
	zend_bool     remote_enable;  /* 0 */
	zend_long     remote_port;    /* 9000 */
	char         *remote_host;    /* localhost */
	long          remote_mode;    /* XDEBUG_NONE, XDEBUG_JIT, XDEBUG_REQ */
	zend_bool     remote_autostart; /* Disables the requirement for XDEBUG_SESSION_START */
	zend_bool     remote_connect_back;   /* connect back to the HTTP requestor */
	char         *remote_log;       /* Filename to log protocol communication to */
	zend_long     remote_log_level; /* Log level XDEBUG_LOG_{ERR,WARN,INFO,DEBUG} */
	zend_long     remote_cookie_expire_time; /* Expire time for the remote-session cookie */
	char         *remote_addr_header; /* User configured header to check for forwarded IP address */
	zend_long     remote_connect_timeout; /* Timeout in MS for remote connections */

	char         *ide_key_setting; /* Set through php.ini and friends */
} xdebug_debugger_settings_t;

PHP_INI_MH(OnUpdateDebugMode);

void xdebug_init_debugger_globals(xdebug_debugger_globals_t *xg);

void xdebug_debugger_reset_ide_key(char *envval);
int xdebug_debugger_bailout_if_no_exec_requested(void);
void xdebug_debugger_set_program_name(zend_string *filename);
void xdebug_debugger_register_eval(function_stack_entry *fse);

xdebug_set *xdebug_debugger_get_breakable_lines_from_oparray(zend_op_array *opa);

void xdebug_debugger_statement_call(char *file, int file_len, int lineno);
void xdebug_debugger_throw_exception_hook(zend_class_entry * exception_ce, zval *file, zval *line, zval *code, char *code_str, zval *message);
void xdebug_debugger_error_cb(const char *error_filename, int error_lineno, int type, char *error_type_str, char *buffer);
void xdebug_debugger_handle_breakpoints(function_stack_entry *fse, int breakpoint_type);

void xdebug_debugger_zend_startup(void);
void xdebug_debugger_zend_shutdown(void);
void xdebug_debugger_minit(void);
void xdebug_debugger_minfo(void);
void xdebug_debugger_rinit(void);
void xdebug_debugger_post_deactivate(void);

void xdebug_debugger_compile_file(zend_op_array *op_array);

PHP_FUNCTION(xdebug_break);


#endif
