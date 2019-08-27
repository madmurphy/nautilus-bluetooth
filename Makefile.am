## Process this file with automake to produce Makefile.in

SUBDIRS = src po

dist_doc_DATA = \
	AUTHORS \
	COPYING \
	ChangeLog \
	NEWS \
	README

INTLTOOL_FILES = intltool-extract.in \
	intltool-merge.in \
	intltool-update.in

EXTRA_DIST = \
	ChangeLog.md \
	INSTALL \
	NEWS \
	README.md \
	autogen.sh \
	package.json \
	m4/ChangeLog \
	$(INTLTOOL_FILES)

DISTCLEANFILES = \
	intltool-extract \
	intltool-merge \
	intltool-update \
	po/.intltool-merge-cache

# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(docdir)

ACLOCAL_AMFLAGS = -I m4

## EOF
