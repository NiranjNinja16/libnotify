/*
 * @file tests/test-image.c Unit test: images
 *
 * @Copyright (C) 2004 Mike Hearn <mike@navi.cx>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA  02111-1307, USA.
 */

#include <libnotify/notify.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define DBUS_API_SUBJECT_TO_CHANGE 1

#include <glib.h>
#include <gtk/gtk.h>
#include <dbus/dbus.h>
#include <dbus/dbus-glib.h>
#include <dbus/dbus-glib-lowlevel.h>

GMainLoop *loop;
NotifyNotification *n;

int main(int argc, char *argv[]) {
	char file[PATH_MAX];
	int size;
        char *uri;
	GdkPixbuf *icon;
	gchar *buf;
	gsize buf_size;
	GtkWidget *helper;

	gtk_init (&argc, &argv);

	if (!notify_init("Images Test")) exit(1);

	n = notify_notification_new ("Icon Test", "Testing stock icon", "stock_help", NULL);
        notify_notification_set_timeout (n, NOTIFY_TIMEOUT_NEVER);
	if (!notify_notification_show (n, NULL)) {
		fprintf(stderr, "failed to send notification\n");
		return 1;
	}

	g_usleep (5000000); //5 seconds

	size = readlink("/proc/self/cwd", file, PATH_MAX - 1);
	file[size] = '\0';
        uri = g_strdup_printf ("file://%s/%s", file, "applet-critical.png");

	printf("sending %s\n", uri);

	notify_notification_update (n, "Alert!", "Testing URI icons", uri);

	if (!notify_notification_show (n, NULL)) {
		fprintf(stderr, "failed to send notification\n");
		return 1;
	}

	g_usleep (5000000); //5 seconds

	notify_notification_update (n, "Raw image test", "Testing sending raw pixbufs", NULL);

	/* This is just a hack to get a stock icon's pixbuf
	   in a realworld app if you were sending bitmapped data
	   you would know the file location and open it up with
	   a method that could generate a bmp for you*/
	helper = gtk_button_new();
	icon = gtk_widget_render_icon (helper,
	                              GTK_STOCK_DIALOG_QUESTION,
	                              GTK_ICON_SIZE_DIALOG,
	                              "");


	notify_notification_set_icon_data_from_pixbuf (n, 
	                                               icon);

	if (!notify_notification_show (n, NULL)) {
		fprintf(stderr, "failed to send notification\n");
		return 1;
	}


	gtk_widget_destroy (helper);
	g_object_unref ((GObject *)icon);

	g_usleep (5000000); //5 seconds
	return 0;
}
