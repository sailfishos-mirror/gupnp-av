/*
 * Copyright (C) 2009 Nokia Corporation.
 *
 * Authors: Zeeshan Ali (Khattak) <zeeshan.ali@nokia.com>
 *                                <zeeshanak@gnome.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef GUPNP_DIDL_LITE_DESCRIPTOR_H
#define GUPNP_DIDL_LITE_DESCRIPTOR_H

#include <stdarg.h>
#include <glib-object.h>
#include <libxml/tree.h>

G_BEGIN_DECLS

#define GUPNP_TYPE_DIDL_LITE_DESCRIPTOR gupnp_didl_lite_descriptor_get_type ()

G_DECLARE_DERIVABLE_TYPE (GUPnPDIDLLiteDescriptor,
                          gupnp_didl_lite_descriptor,
                          GUPNP,
                          DIDL_LITE_DESCRIPTOR,
                          GObject)

struct _GUPnPDIDLLiteDescriptorClass {
        GObjectClass parent_class;

        /* future padding */
        void (* _gupnp_reserved1) (void);
        void (* _gupnp_reserved2) (void);
        void (* _gupnp_reserved3) (void);
        void (* _gupnp_reserved4) (void);
};

GUPnPDIDLLiteDescriptor *
gupnp_didl_lite_descriptor_new (void);

xmlNode *
gupnp_didl_lite_descriptor_get_xml_node (GUPnPDIDLLiteDescriptor *descriptor);

const char *
gupnp_didl_lite_descriptor_get_content  (GUPnPDIDLLiteDescriptor *descriptor);

const char *
gupnp_didl_lite_descriptor_get_id       (GUPnPDIDLLiteDescriptor *descriptor);

const char *
gupnp_didl_lite_descriptor_get_metadata_type
                                        (GUPnPDIDLLiteDescriptor *descriptor);

const char *
gupnp_didl_lite_descriptor_get_name_space
                                        (GUPnPDIDLLiteDescriptor *descriptor);

void
gupnp_didl_lite_descriptor_set_content  (GUPnPDIDLLiteDescriptor *descriptor,
                                         const char              *content);

void
gupnp_didl_lite_descriptor_set_id       (GUPnPDIDLLiteDescriptor *descriptor,
                                         const char              *id);

void
gupnp_didl_lite_descriptor_set_metadata_type
                                        (GUPnPDIDLLiteDescriptor *descriptor,
                                         const char              *type);

void
gupnp_didl_lite_descriptor_set_name_space
                                        (GUPnPDIDLLiteDescriptor *descriptor,
                                         const char              *name_space);

G_END_DECLS

#endif /* __GUPNP_DIDL_LITE_DESCRIPTOR_H__ */
