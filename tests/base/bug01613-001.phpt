--TEST--
Test for bug #1613: Wrong name displayed for Recoverable fatal error [text] (>= PHP 7.1, < PHP 7.4)
--SKIPIF--
<?php
require __DIR__ . '/../utils.inc';
check_reqs('PHP >= 7.1,< 7.4');
?>
--INI--
xdebug.default_enable=1
xdebug.auto_trace=0
xdebug.collect_params=1
xdebug.collect_assignments=0
xdebug.profiler_enable=0
xdebug.show_local_vars=0
xdebug.dump_globals=0
--FILE--
<?php
$v = new DateTime();
$v = (string) $v;
?>
--EXPECTF--
Recoverable fatal error: Object of class DateTime could not be converted to string in %sbug01613-001.php on line %d

Call Stack:
%w%f  %w%d   1. {main}() %sbug01613-001.php:%d
