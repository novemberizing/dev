AC_INIT (package, version, [bug-report], [tarname], [url])

Process any command-line arguments and perform various initializations and verifications.

Set the name of the package and its version. These are typically used in --version support, including that of configure. The optional argument bug-report should be the email to which users should send bug reports. The package tarname differs from package: the latter designates the full package name (e.g., ‘GNU Autoconf’), while the former is meant for distribution tar ball names (e.g., ‘autoconf’). It defaults to package with ‘GNU ’ stripped, lower-cased, and all characters other than alphanumerics and underscores are changed to ‘-’. If provided, url should be the home page for the package.

The arguments of AC_INIT must be static, i.e., there should not be any shell computation, quotes, or newlines, but they can be computed by M4. This is because the package information strings are expanded at M4 time into several contexts, and must give the same text at shell time whether used in single-quoted strings, double-quoted strings, quoted here-documents, or unquoted here-documents. It is permissible to use m4_esyscmd or m4_esyscmd_s for computing a version string that changes with every commit to a version control system (in fact, Autoconf does just that, for all builds of the development tree made between releases).

The following M4 macros (e.g., AC_PACKAGE_NAME), output variables (e.g., PACKAGE_NAME), and preprocessor symbols (e.g., PACKAGE_NAME), are defined by AC_INIT:

| MACRO                                   | DESCRIPTION      |
| --------------------------------------- | ---------------- |
| AC_PACKAGE_NAME, PACKAGE_NAME           | Exactly package. |
| AC_PACKAGE_TARNAME, PACKAGE_TARNAME     | Exactly tarname, possibly generated from package. |
| AC_PACKAGE_VERSION, PACKAGE_VERSION     | Exactly version. |
| AC_PACKAGE_STRING, PACKAGE_STRING       | Exactly 'package version'. |
| AC_PACKAGE_BUGREPORT, PACKAGE_BUGREPORT | Exactly bug-report, if one was provided. |
| AC_PACKAGE_URL, PACKAGE_URL             | Exactly url, if one was provided. If url was empty, but package begins with ‘GNU ’, then this defaults to ‘http://www.gnu.org/software/tarname/’, otherwise, no URL is assumed. |

If your configure script does its own option processing, it should inspect ‘$@’ or ‘$*’ immediately after calling AC_INIT, because other Autoconf macros liberally use the set command to process strings, and this has the side effect of updating ‘$@’ and ‘$*’. However, we suggest that you use standard macros like AC_ARG_ENABLE instead of attempting to implement your own option processing. See Site Configuration.
