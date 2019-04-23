#include "php_xdebug.h"

ZEND_DECLARE_MODULE_GLOBALS(xdebug);
void function_stack_entry_dtor(void *dummy, void *elem);

zend_fcall_info_cache fci_cache;

void sw_xdebug_init()
{
	zend_hash_init(&sw_xdebug_globals, 32, NULL, ZVAL_PTR_DTOR, 0);

	zend_string *classname = zend_string_init("Swoole\\Coroutine", sizeof("Swoole\\Coroutine") - 1, 0);
	zend_class_entry *class_handle = zend_lookup_class(classname);
	zend_string_release(classname);
	zval *getcid_func = zend_hash_str_find(&(class_handle->function_table), "getcid", sizeof("getcid") - 1);

	fci_cache.initialized = 1;
	fci_cache.function_handler = getcid_func->value.func;
	fci_cache.calling_scope = class_handle;
}

long get_cid()
{
	zend_fcall_info fci;
	zval            retval;

	fci.size = sizeof(fci);
	fci.object = NULL;
	fci.retval = &retval;
	fci.param_count = 0;
	fci.params = NULL;
	fci.no_separation = 0;

	XG(in_getcid) = 1;
	zend_call_function(&fci, &fci_cache);

	return zval_get_long(&retval) == -1 ? 0 : zval_get_long(&retval);
}

int add_current_context()
{
	long cid = get_cid();
	zval pData;
	sw_zend_xdebug_globals *new_context;

	if (zend_hash_index_exists(&sw_xdebug_globals, cid)) {
		return 0;
	}

	new_context = emalloc(sizeof(sw_zend_xdebug_globals));
	new_context->cid   = cid;
	new_context->level = 0;
	new_context->stack = xdebug_llist_alloc(function_stack_entry_dtor);
	ZVAL_PTR(&pData, new_context);
	zend_hash_index_add(&sw_xdebug_globals, cid, &pData);

	return 1;
}

sw_zend_xdebug_globals *get_current_context()
{
	zval *val = zend_hash_index_find(&sw_xdebug_globals, get_cid());
	return (sw_zend_xdebug_globals *)Z_PTR_P(val);
}

void remove_context(long cid)
{
    sw_zend_xdebug_globals *context;
    zval *pData = zend_hash_index_find(&sw_xdebug_globals, cid);

    context = (sw_zend_xdebug_globals *)Z_PTR_P(pData);
    xdebug_llist_destroy(context->stack, NULL);
    context->level = 0;
    context->stack = NULL;
    efree(context);
    zend_hash_index_del(&sw_xdebug_globals, cid);
}
