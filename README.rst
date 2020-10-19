Sdebug 
------------
* Sdebug is a fork of the Offical [Xdebug](https://github.com/xdebug/xdebug) to compilant with Swoole.
* Based on xdebug2.7(https://github.com/xdebug/xdebug)

Notice
------------
* The name of the extension is `sdebug` instead of `xdebug`, if you want to use `Phpunit CodeCoverage`, you have to manually modify `xdebug` to be `sdebug`.

Install and setup
-----

You can clone the Sdebug source directory with::

   git clone https://github.com/swoole/sdebug.git

Then move into this new directory::

	cd sdebug

Although it is recommended to run the latest version from the **master**
branch, older versions are available through tags. For example to checkout the
2.5.5 release, you can switch to it with ``git checkout XDEBUG_2_5_5``.

Compile
-------

If PHP is installed in a normal, and uncomplicated way, with default locations
and configuration, all you will need to do is to run the following script::

	./rebuild.sh

This will run ``phpize``, ``./configure``, ``make clean``, ``make`` and ``make
install``.

The long winded way of installation is:

#. Run phpize: ``phpize``
   (or ``/path/to/phpize`` if phpize is not in your path).

#. ``./configure --enable-xdebug`` (or: ``../configure --enable-xdebug
   --with-php-config=/path/to/php-config`` if ``php-config`` is not in your
   path)

#. Run: ``make clean``

#. Run: ``make``

#. Run: ``make install``

#. Add the following line to ``php.ini`` (which you can find by running ``php
   --ini``, or look at ``phpinfo()`` output): ``zend_extension="xdebug.so"``.

   Please note, that sometimes the ``php.ini`` file is different for the
   command line and for your web server. Make sure you pick the right one.

#. Unless you exclusively use the command line with PHP, restart your webserver.

#. Write a PHP page that calls ``phpinfo();``. Load it in a browser and
   look for the info on the Xdebug module.  If you see it, you have been
   successful! Alternatively, you can run ``php -v`` on the command line to
   see that Xdebug is loaded::

	$ php -v
	PHP 7.2.0RC6 (cli) (built: Nov 23 2017 10:30:56) ( NTS DEBUG )
	Copyright (c) 1997-2017 The PHP Group
	Zend Engine v3.2.0-dev, Copyright (c) 1998-2017 Zend Technologies
      with Sdebug v2.x.x-dev, Copyright (c) 2002-2017, by Derick Rethans
