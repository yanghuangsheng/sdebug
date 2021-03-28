--TEST--
Test for bug #1403: Code coverage does not cover BIND_STATIC/BIND_LEXICAL (>= PHP 7.1, < PHP 7.4)
--SKIPIF--
<?php
require __DIR__ . '/../utils.inc';
check_reqs('PHP >= 7.1,< 7.4');
?>
--INI--
xdebug.default_enable=1
xdebug.auto_trace=0
xdebug.auto_profile=0
xdebug.profiler_enable=0
xdebug.overload_var_dump=0
xdebug.coverage_enable=1
--FILE--
<?php
$file = 'bug01403.inc';
$pathname = stream_resolve_include_path($file);
xdebug_start_code_coverage(XDEBUG_CC_UNUSED | XDEBUG_CC_DEAD_CODE);
require $pathname;
$coverage = xdebug_get_code_coverage();
xdebug_stop_code_coverage();
print_r($coverage[$pathname]);
?>
--EXPECTF--
Array
(
    [2] => 1
    [5] => 1
    [6] => 1
    [8] => 1
    [11] => 1
    [12] => 1
    [13] => 1
    [15] => 1
    [16] => 1
    [18] => 1
)
