/*  -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */

/*\
|*|
|*|	nautilus-bluetooth.c
|*|
|*|	https://gitlab.gnome.org/madmurphy/nautilus-bluetooth
|*|	Copyright (C) 2019 Stefano Gioffr&eacute; <madmurphy333@gmail.com>
|*|
|*|	nautilus-bluetooth is free software: you can redistribute it and/or modify it
|*|	under the terms of the GNU General Public License as published by the
|*|	Free Software Foundation, either version 3 of the License, or
|*|	(at your option) any later version.
|*|
|*|	nautilus-bluetooth is distributed in the hope that it will be useful, but
|*|	WITHOUT ANY WARRANTY; without even the implied warranty of
|*|	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
|*|	See the GNU General Public License for more details.
|*|
|*|	You should have received a copy of the GNU General Public License along
|*|	with this program. If not, see <http://www.gnu.org/licenses/>.
|*|
\*/



#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <glib.h>
#include <nautilus-extension.h>

#ifdef ENABLE_NLS
#include <glib/gi18n-lib.h>
#else
#define _(STRING) STRING
#endif



/*

	GLOBAL TYPES AND VARIABLES

*/


typedef struct {
	GObject parent_slot;
} NautilusBluetooth;

typedef struct {
	GObjectClass parent_slot;
} NautilusBluetoothClass;

static GType provider_types[1];
static GType nautilus_bluetooth_type;
static GObjectClass * parent_class;



/*

	FUNCTIONS

*/


static void nautilus_bluetooth_sendto (
	NautilusMenuItem * const menu_item,
	gpointer v_unused
) {

	GList * const file_selection = g_object_get_data((GObject *) menu_item, "nautilus_bluetooth_files");
	const gsize argv_last = g_list_length(file_selection) + 1;
	gchar ** const argv = g_malloc((argv_last + 1) * sizeof(gchar *));
	gsize idx = 1;
	GError * spawnerr = NULL;

	*argv = NAUTILUS_BLUETOOTH_SENDTO_CMD;
	argv[argv_last] = NULL;

	for (GList * iter = file_selection; iter; iter = iter->next) {

		argv[idx++] = nautilus_file_info_get_uri(NAUTILUS_FILE_INFO(iter->data));

	}

	if (!g_spawn_async(NULL, argv, NULL, G_SPAWN_DEFAULT, NULL, NULL, NULL, &spawnerr)) {

		fprintf(stderr, "%s\n", spawnerr->message);
		g_error_free(spawnerr);

	}

	for (idx = 1; idx < argv_last; g_free(argv[idx++]));

	g_free(argv);

}


GType nautilus_bluetooth_get_type (void) {

	return nautilus_bluetooth_type;

}


static void nautilus_bluetooth_class_init (
	NautilusBluetoothClass * const nautilus_bluetooth_class,
	gpointer class_data
) {

	parent_class = g_type_class_peek_parent(nautilus_bluetooth_class);

}


static GList * nautilus_bluetooth_get_file_items (
	NautilusMenuProvider * const provider,
	GtkWidget * const window,
	GList * const file_selection
) {

	for (GList * iter = file_selection; iter; iter = iter->next) {

		/*  Avoid directories  */

		if (nautilus_file_info_is_directory(NAUTILUS_FILE_INFO(iter->data))) {

			return NULL;

		}

	}

	NautilusMenuItem * const menu_item = nautilus_menu_item_new(
		"NautilusBluetooth::send_via_bluetooth",
		_("Send via Bluetooth"),
		_("Send the selected files to a Bluetooth device"),
		"bluetooth"
	);

	g_signal_connect(
		menu_item,
		"activate",
		G_CALLBACK(nautilus_bluetooth_sendto),
		NULL
	);

	g_object_set_data_full(
		(GObject *) menu_item, "nautilus_bluetooth_files",
		nautilus_file_info_list_copy(file_selection),
		(GDestroyNotify) nautilus_file_info_list_free
	);

	return g_list_append(NULL, menu_item);

}


static void nautilus_bluetooth_menu_provider_iface_init (
	NautilusMenuProviderIface * const iface,
	gpointer iface_data
) {

	iface->get_file_items = nautilus_bluetooth_get_file_items;

}


static void nautilus_bluetooth_register_type (GTypeModule * const module) {

	static const GTypeInfo info = {
		sizeof(NautilusBluetoothClass),
		(GBaseInitFunc) NULL,
		(GBaseFinalizeFunc) NULL,
		(GClassInitFunc) nautilus_bluetooth_class_init,
		(GClassFinalizeFunc) NULL,
		NULL,
		sizeof(NautilusBluetooth),
		0,
		(GInstanceInitFunc) NULL,
	};

	static const GInterfaceInfo menu_provider_iface_info = {
		(GInterfaceInitFunc) nautilus_bluetooth_menu_provider_iface_init,
		(GInterfaceFinalizeFunc) NULL,
		NULL
	};

	nautilus_bluetooth_type = g_type_module_register_type(
		module,
		G_TYPE_OBJECT,
		"NautilusBluetooth",
		&info,
		0
	);

	g_type_module_add_interface(
		module,
		nautilus_bluetooth_type,
		NAUTILUS_TYPE_MENU_PROVIDER,
		&menu_provider_iface_info
	);

}


void nautilus_module_initialize (GTypeModule * const module) {

	#ifdef ENABLE_NLS
	bindtextdomain(GETTEXT_PACKAGE, NAUTILUS_BLUETOOTH_LOCALEDIR);
	#endif

	nautilus_bluetooth_register_type(module);
	*provider_types = nautilus_bluetooth_get_type();

}


void nautilus_module_shutdown (void) {

	/*  Any module-specific shutdown  */

}


void nautilus_module_list_types (const GType ** types, int * num_types) {

	*types = provider_types;
	*num_types = G_N_ELEMENTS(provider_types);

}


/*  EOF  */

