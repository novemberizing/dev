AC_PROG_CC ([compiler-search-list])

Determine a C compiler to use. If CC is not already set in the environment, check for gcc and cc, then for other C compilers. Set output variable CC to the name of the compiler found.

This macro may, however, be invoked with an optional first argument which, if specified, must be a blank-separated list of C compilers to search for. This just gives the user an opportunity to specify an alternative search list for the C compiler. For example, if you didn't like the default order, then you could invoke AC_PROG_CC like this:

AC_PROG_CC([gcc cl cc])

If the C compiler does not handle function prototypes correctly by default, try to add an option to output variable CC to make it so. This macro tries various options that select standard-conformance modes on various systems.

After calling this macro you can check whether the C compiler has been set to accept ANSI C89 (ISO C90); if not, the shell variable ac_cv_prog_cc_c89 is set to ‘no’. See also AC_C_PROTOTYPES below.

If using the GNU C compiler, set shell variable GCC to ‘yes’. If output variable CFLAGS was not already set, set it to -g -O2 for the GNU C compiler (-O2 on systems where GCC does not accept -g), or -g for other compilers.
