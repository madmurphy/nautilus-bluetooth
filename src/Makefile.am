# Process this file with automake to produce Makefile.in

AM_CPPFLAGS = \
	"-DPACKAGE_LOCALE_DIR=\"$(localedir)\"" \
	"-DPACKAGE_SRC_DIR=\"$(srcdir)\"" \
	"-DPACKAGE_DATA_DIR=\"$(pkgdatadir)\"" \
	"-DG_LOG_DOMAIN=\"NautilusBluetooth\""

AM_CFLAGS = \
	-Wall\
	-g \
	-pedantic \
	$(WARN_CFLAGS) \
	$(NAUTILUS_CFLAGS) \
	$(GLIB_CFLAGS) \
	$(NAUTILUS_BLUETOOTH_CFLAGS)

nautilus_extensiondir = $(NAUTILUS_EXTENSION_DIR)

nautilus_extension_LTLIBRARIES = \
	libnautilus-bluetooth.la

libnautilus_bluetooth_la_SOURCES = \
	nautilus-bluetooth.c

libnautilus_bluetooth_la_LDFLAGS = \
	-module \
	-avoid-version

libnautilus_bluetooth_la_LIBADD = \
	$(NAUTILUS_BLUETOOTH_LIBS)

# EOF

