dnl  Process this file with autoconf to produce a configure script.


dnl  ***************************************************************************
dnl     A U T O C O N F   E N V I R O N M E N T
dnl  ***************************************************************************


AC_PREREQ([2.69])

AC_INIT([Nautilus Bluetooth],
	[1.0.0],
	[madmurphy333@gmail.com],
	[nautilus-bluetooth],
	[https://gitlab.gnome.org/madmurphy/nautilus-bluetooth])

AC_CONFIG_MACRO_DIR([m4])

AC_CONFIG_AUX_DIR([build-aux])

AC_CONFIG_SRCDIR([src/nautilus-bluetooth.c])

AC_CONFIG_HEADERS([config.h])

AC_CONFIG_FILES([Makefile
src/Makefile
po/Makefile.in])

AM_INIT_AUTOMAKE([1.11])

AM_SILENT_RULES([yes])

AC_PROG_CC

PKG_CHECK_MODULES([NAUTILUS_BLUETOOTH], [glib-2.0 libnautilus-extension])

AC_CHECK_PROG([HAVE_PKGCONFIG], [pkg-config], [yes], [no])

AS_IF([test "x${HAVE_PKGCONFIG}" = xno],
	[AC_MSG_ERROR([you need to have pkgconfig installed!])])


dnl  ***************************************************************************
dnl     B L U E T O O T H   S E T T I N G S
dnl  ***************************************************************************


dnl  Default program used by nautilus-bluetooth when the user does not specify a
dnl  BLUETOOTH_SENDTO argument variable
AC_DEFUN([DEFAULT_BLUETOOTH_SENDTO_PROG], [bluetooth-sendto])

dnl  Register the BLUETOOTH_SENDTO argument variable...
AC_ARG_VAR([BLUETOOTH_SENDTO],
	[Bluetooth file sharing command; it must support the syntax BLUETOOTH_SENDTO file1 file2 file3 ... etc. @<:@default=BINDIR/]DEFAULT_BLUETOOTH_SENDTO_PROG[@:>@])

dnl  First check whether a BLUETOOTH_SENDTO argument variable has been given; if
dnl  not, check whether DEFAULT_BLUETOOTH_SENDTO_PROG is present in the system;
dnl  if not, print an error message and stop configuring.
AS_IF([test "x${BLUETOOTH_SENDTO}" = x], [
	AC_PATH_PROG([AUTO_BLUETOOTH_SENDTO_CMD], DEFAULT_BLUETOOTH_SENDTO_PROG)
	AS_IF([test "x${AUTO_BLUETOOTH_SENDTO_CMD}" = x],
		[AC_MSG_ERROR(DEFAULT_BLUETOOTH_SENDTO_PROG[ utility not found. Please specify a BLUETOOTH_SENDTO argument variable before launching this configure script. For more information see ./configure --help])],
		[AC_DEFINE_UNQUOTED([NAUTILUS_BLUETOOTH_SENDTO_CMD],
			["${AUTO_BLUETOOTH_SENDTO_CMD}"],
			[Command invoked to send files via Bluetooth])])
], [
	AC_DEFINE_UNQUOTED([NAUTILUS_BLUETOOTH_SENDTO_CMD],
		["${BLUETOOTH_SENDTO}"],
		[Command invoked to send files via Bluetooth])
])


dnl  ***************************************************************************
dnl     I N T E R N A T I O N A L I Z A T I O N
dnl  ***************************************************************************


IT_PROG_INTLTOOL([0.35.0])

AM_CONDITIONAL([NLS_ENABLED], [test "x${USE_NLS}" != xno])

AM_COND_IF([NLS_ENABLED], [
	AC_SUBST([GETTEXT_PACKAGE], AC_PACKAGE_TARNAME)
	AC_DEFINE_UNQUOTED([GETTEXT_PACKAGE],
		["${GETTEXT_PACKAGE}"], [GETTEXT package name])
	AM_GLIB_GNU_GETTEXT
	AM_GLIB_DEFINE_LOCALEDIR([NAUTILUS_BLUETOOTH_LOCALEDIR])
])



dnl  ***************************************************************************
dnl     F I N A L I Z A T I O N
dnl  ***************************************************************************


AC_SUBST([NAUTILUS_EXTENSION_DIR],
	["$($PKG_CONFIG --variable=extensiondir libnautilus-extension)"])

LT_INIT([disable-static])

AC_OUTPUT


dnl  EOF

