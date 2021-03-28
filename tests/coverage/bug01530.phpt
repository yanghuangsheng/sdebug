--TEST--
Test for bug #1530: Code coverage incorrect for last code line in a loop (>= PHP 7.2.14, !opcache)
--SKIPIF--
<?php
require __DIR__ . '/../utils.inc';
check_reqs('PHP >= 7.2.14,!= 7.3.0; !opcache');
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
$file = 'bug01530.inc';
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
    [3] => 1
    [4] => -1
    [5] => -1
    [9] => 1
)
