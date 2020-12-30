AM_INIT_AUTOMAKE([OPTIONS])

Runs many macros required for proper operation of the generated Makefiles.

Today, AM_INIT_AUTOMAKE is called with a single argument: a space-separated list of Automake options that should be applied to every Makefile.am in the tree. The effect is as if each option were listed in AUTOMAKE_OPTIONS (see Options).

This macro can also be called in another, deprecated form: AM_INIT_AUTOMAKE(PACKAGE, VERSION, [NO-DEFINE]). In this form, there are two required arguments: the package and the version number. This usage is mostly obsolete because the package and version can be obtained from Autoconf’s AC_INIT macro. However, differently from what happens for AC_INIT invocations, this AM_INIT_AUTOMAKE invocation supports shell variables’ expansions in the PACKAGE and VERSION arguments (which otherwise defaults, respectively, to the PACKAGE_TARNAME and PACKAGE_VERSION defined via the AC_INIT invocation; see The AC_INIT macro in The Autoconf Manual); and this can still be useful in some selected situations. Our hope is that future Autoconf versions will improve their support for package versions defined dynamically at configure runtime; when (and if) this happens, support for the two-args AM_INIT_AUTOMAKE invocation will likely be removed from Automake.

If your configure.ac has:

```
AC_INIT([src/foo.c])
AM_INIT_AUTOMAKE([mumble], [1.5])
```

you should modernize it as follows:

```
AC_INIT([mumble], [1.5])
AC_CONFIG_SRCDIR([src/foo.c])
AM_INIT_AUTOMAKE
```

Note that if you’re upgrading your configure.ac from an earlier version of Automake, it is not always correct to simply move the package and version arguments from AM_INIT_AUTOMAKE directly to AC_INIT, as in the example above. The first argument to AC_INIT should be the name of your package (e.g., ‘GNU Automake’), not the tarball name (e.g., ‘automake’) that you used to pass to AM_INIT_AUTOMAKE. Autoconf tries to derive a tarball name from the package name, which should work for most but not all package names. (If it doesn’t work for yours, you can use the four-argument form of AC_INIT to provide the tarball name explicitly).

By default this macro AC_DEFINE’s PACKAGE and VERSION. This can be avoided by passing the no-define option (see List of Automake options):

```
AM_INIT_AUTOMAKE([no-define ...])
```