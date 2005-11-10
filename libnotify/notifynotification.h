/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with main.c; if not, write to:
 *            The Free Software Foundation, Inc.,
 *            59 Temple Place - Suite 330,
 *            Boston,  MA  02111-1307, USA.
 */

#ifndef NOTIFY_NOTIFICATION_H
#define NOTIFY_NOTIFICATION_H
#include "config.h"

#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>

#include "notifycommon.h"

G_BEGIN_DECLS

#define NOTIFY_TYPE_NOTIFICATION         (notify_notification_get_type ())
#define NOTIFY_NOTIFICATION(o)           (G_TYPE_CHECK_INSTANCE_CAST ((o), NOTIFY_TYPE_NOTIFICATION, NotifyNotification))
#define NOTIFY_NOTIFICATION_CLASS(k)     (G_TYPE_CHECK_CLASS_CAST((k), NOTIFY_TYPE_NOTIFICATION, NotifyNotificationClass))
#define NOTIFY_IS_NOTIFICATION(o)        (G_TYPE_CHECK_INSTANCE_TYPE ((o), NOTIFY_TYPE_NOTIFICATION))
#define NOTIFY_IS_NOTIFICATION_CLASS(k)  (G_TYPE_CHECK_CLASS_TYPE ((k), NOTIFY_TYPE_NOTIFICATION))
#define NOTIFY_NOTIFICATION_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), NOTIFY_TYPE_NOTIFICATION, NotifyNotificationClass))

typedef struct NotifyNotificationPrivate NotifyNotificationPrivate;

typedef struct {
	GObject parent;
	NotifyNotificationPrivate *priv;
} NotifyNotification;

typedef struct {
	GObjectClass parent_class;
	/* Add Signal Functions Here */
} NotifyNotificationClass;

typedef void (*NotifyActionCallback )(NotifyNotification *, gchar *);

GType notify_notification_get_type();
NotifyNotification *notify_notification_new (const gchar *summary,
                                             const gchar *message,
                                             const gchar *icon,
                                             GtkWidget *attach);

gboolean notify_notification_update (NotifyNotification *notification,
                                     const gchar *summary,
                                     const gchar *message,
                                     const gchar *icon);

void notify_notification_attach_to_widget (NotifyNotification *notification,
                                           GtkWidget *attach);

gboolean notify_notification_set_user_data (NotifyNotification *notification,
                                            void *user_data,
                                            GFreeFunc free_func);

gboolean notify_notification_show (NotifyNotification *notification, 
                                   GError **error);

void notify_notification_set_timeout (NotifyNotification *notification,
                                      gint timeout);

gboolean notify_notification_set_category (NotifyNotification *notification,
                                           const char *category);

gboolean notify_notification_set_urgency (NotifyNotification *notification,
                                          NotifyUrgency l);

gboolean notify_notification_set_icon_data_from_pixbuf (NotifyNotification *notification,
                                                        GdkPixbuf *icon);

                                          
gboolean notify_notification_set_hint_int32 (NotifyNotification *notification,
                                             const gchar *key,
                                             gint value);

gboolean notify_notification_set_hint_double (NotifyNotification *notification,
                                              const gchar *key,
                                              gdouble value);
 
gboolean notify_notification_set_hint_string (NotifyNotification *notification,
                                              const gchar *key,
                                              const gchar *value);
                                              
gboolean notify_notification_set_hint_byte (NotifyNotification *notification,
                                            const gchar *key,
                                            guchar value);

gboolean notify_notification_set_hint_byte_array (
                                         NotifyNotification *notification,
                                         const gchar *key,
                                         const guchar *value,
                                         gsize len);

gboolean notify_notification_add_action (NotifyNotification *notification,
                                         const char *action,
                                         const char *label,
                                         NotifyActionCallback callback);
                                         
gboolean notify_notification_hide  (NotifyNotification *notification, 
                                    GError **error); 
                                         
NotifyNotification *notify_notification_ref (NotifyNotification *notification);
void notify_notification_unref (NotifyNotification *notification);
#endif /* NOTIFY_NOTIFICATION_H */
