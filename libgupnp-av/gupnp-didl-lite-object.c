/*
 * Copyright (C) 2009 Nokia Corporation.
 * Copyright (C) 2007, 2008 OpenedHand Ltd.
 *
 * Authors: Zeeshan Ali (Khattak) <zeeshan.ali@nokia.com>
 *                                <zeeshanak@gnome.org>
 *          Jorn Baayen <jorn@openedhand.com>
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
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/**
 * SECTION:gupnp-didl-lite-object
 * @short_description: DIDL-Lite Object
 *
 * #GUPnPDIDLLiteObject respresent a DIDL-Lite object element.
 */

#include <string.h>
#include <libgupnp/gupnp.h>

#include "gupnp-didl-lite-object.h"
#include "xml-util.h"

G_DEFINE_ABSTRACT_TYPE (GUPnPDIDLLiteObject,
                        gupnp_didl_lite_object,
                        G_TYPE_OBJECT);

struct _GUPnPDIDLLiteObjectPrivate {
        xmlNode            *xml_node;
        GUPnPXMLDocWrapper *xml_doc;

        xmlNs              *upnp_ns;
        xmlNs              *dc_ns;
};

enum {
        PROP_0,
        PROP_XML_NODE,
        PROP_XML_DOC,
        PROP_ID,
        PROP_PARENT_ID,
        PROP_RESTRICTED,
        PROP_TITLE,
        PROP_UPNP_CLASS,
        PROP_CREATOR,
        PROP_ARTIST,
        PROP_AUTHOR,
        PROP_GENRE,
        PROP_WRITE_STATUS,
        PROP_ALBUM,
        PROP_ALBUM_ART,
        PROP_DESCRIPTION,
        PROP_DATE,
        PROP_TRACK_NUMBER,
};

static void
gupnp_didl_lite_object_init (GUPnPDIDLLiteObject *object)
{
        object->priv = G_TYPE_INSTANCE_GET_PRIVATE
                                        (object,
                                         GUPNP_TYPE_DIDL_LITE_OBJECT,
                                         GUPnPDIDLLiteObjectPrivate);
}

static void
gupnp_didl_lite_object_set_property (GObject      *object,
                                     guint         property_id,
                                     const GValue *value,
                                     GParamSpec   *pspec)

{
        GUPnPDIDLLiteObject *didl_object;

        didl_object = GUPNP_DIDL_LITE_OBJECT (object);

        switch (property_id) {
        case PROP_XML_NODE:
                didl_object->priv->xml_node = g_value_get_pointer (value);
                break;
        case PROP_XML_DOC:
                didl_object->priv->xml_doc = g_value_dup_object (value);
                break;
        case PROP_ID:
                gupnp_didl_lite_object_set_id (didl_object,
                                               g_value_get_string (value));
                break;
        case PROP_PARENT_ID:
                gupnp_didl_lite_object_set_parent_id
                                        (didl_object,
                                         g_value_get_string (value));
                break;
        case PROP_RESTRICTED:
                gupnp_didl_lite_object_set_restricted
                                        (didl_object,
                                         g_value_get_boolean (value));
                break;
        case PROP_TITLE:
                gupnp_didl_lite_object_set_title
                                        (didl_object,
                                         g_value_get_string (value));
                break;
        case PROP_UPNP_CLASS:
                gupnp_didl_lite_object_set_upnp_class
                                        (didl_object,
                                         g_value_get_string (value),
                                         NULL);
                break;
        case PROP_CREATOR:
                gupnp_didl_lite_object_set_creator
                                        (didl_object,
                                         g_value_get_string (value));
                break;
        case PROP_ARTIST:
                gupnp_didl_lite_object_set_artist
                                        (didl_object,
                                         g_value_get_string (value),
                                         NULL);
                break;
        case PROP_AUTHOR:
                gupnp_didl_lite_object_set_author
                                        (didl_object,
                                         g_value_get_string (value),
                                         NULL);
                break;
        case PROP_GENRE:
                gupnp_didl_lite_object_set_genre
                                        (didl_object,
                                         g_value_get_string (value),
                                         NULL,
                                         NULL);
                break;
        case PROP_WRITE_STATUS:
                gupnp_didl_lite_object_set_write_status
                                        (didl_object,
                                         g_value_get_string (value));
                break;
        case PROP_ALBUM:
                gupnp_didl_lite_object_set_album
                                        (didl_object,
                                         g_value_get_string (value));
                break;
        case PROP_ALBUM_ART:
                gupnp_didl_lite_object_set_album_art
                                        (didl_object,
                                         g_value_get_string (value));
                break;
        case PROP_DESCRIPTION:
                gupnp_didl_lite_object_set_description
                                        (didl_object,
                                         g_value_get_string (value));
                break;
        case PROP_DATE:
                gupnp_didl_lite_object_set_date
                                        (didl_object,
                                         g_value_get_string (value));
                break;
        case PROP_TRACK_NUMBER:
                gupnp_didl_lite_object_set_track_number
                                        (didl_object,
                                         g_value_get_int (value));
                break;
        default:
                G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
                break;
        }
}

static void
gupnp_didl_lite_object_get_property (GObject    *object,
                                     guint       property_id,
                                     GValue     *value,
                                     GParamSpec *pspec)
{
        GUPnPDIDLLiteObject *didl_object;

        didl_object = GUPNP_DIDL_LITE_OBJECT (object);

        switch (property_id) {
        case PROP_XML_NODE:
                g_value_set_pointer
                        (value,
                         gupnp_didl_lite_object_get_xml_node (didl_object));
                break;
        case PROP_ID:
                g_value_take_string
                        (value,
                         gupnp_didl_lite_object_get_id (didl_object));
                break;
        case PROP_PARENT_ID:
                g_value_take_string
                        (value,
                         gupnp_didl_lite_object_get_parent_id (didl_object));
                break;
        case PROP_RESTRICTED:
                g_value_set_boolean
                        (value,
                         gupnp_didl_lite_object_get_restricted (didl_object));
                break;
        case PROP_TITLE:
                g_value_take_string
                        (value,
                         gupnp_didl_lite_object_get_title (didl_object));
                break;
        case PROP_UPNP_CLASS:
                g_value_take_string
                        (value,
                         gupnp_didl_lite_object_get_upnp_class
                                                        (didl_object, NULL));
                break;
        case PROP_CREATOR:
                g_value_take_string
                        (value,
                         gupnp_didl_lite_object_get_creator (didl_object));
                break;
        case PROP_ARTIST:
                g_value_take_string
                        (value,
                         gupnp_didl_lite_object_get_artist (didl_object, NULL));
                break;
        case PROP_AUTHOR:
                g_value_take_string
                        (value,
                         gupnp_didl_lite_object_get_author (didl_object, NULL));
                break;
        case PROP_GENRE:
                g_value_take_string
                        (value,
                         gupnp_didl_lite_object_get_genre (didl_object,
                                                           NULL,
                                                           NULL));
                break;
        case PROP_WRITE_STATUS:
                g_value_take_string
                        (value,
                         gupnp_didl_lite_object_get_write_status (didl_object));
                break;
        case PROP_ALBUM:
                g_value_take_string
                        (value,
                         gupnp_didl_lite_object_get_album (didl_object));
                break;
        case PROP_ALBUM_ART:
                g_value_take_string
                        (value,
                         gupnp_didl_lite_object_get_album_art (didl_object));
                break;
        case PROP_DESCRIPTION:
                g_value_take_string
                        (value,
                         gupnp_didl_lite_object_get_description (didl_object));
                break;
        case PROP_DATE:
                g_value_take_string
                        (value,
                         gupnp_didl_lite_object_get_date (didl_object));
                break;
        case PROP_TRACK_NUMBER:
                g_value_set_int
                        (value,
                         gupnp_didl_lite_object_get_track_number (didl_object));
                break;
        default:
                G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
                break;
        }
}

static void
gupnp_didl_lite_object_constructed (GObject *object)
{
        GObjectClass               *object_class;
        GUPnPDIDLLiteObjectPrivate *priv;
        xmlNs                     **ns_list;
        short                       i;

        priv = GUPNP_DIDL_LITE_OBJECT (object)->priv;

        if (priv->xml_doc == NULL) {
                xmlDoc  *doc;

                doc = xmlNewDoc ((unsigned char *) "1.0");
                priv->xml_doc = gupnp_xml_doc_wrapper_new (doc);
        }

        if (priv->xml_node == NULL) {
                xmlNode *root_node;

                root_node = xmlNewDocNode (priv->xml_doc->doc,
                                           NULL,
                                           (unsigned char *) "DIDL-Lite",
                                           NULL);
                xmlDocSetRootElement (priv->xml_doc->doc, root_node);
                xmlNewNs (root_node,
                          (unsigned char *) "http://purl.org/dc/elements/1.1/",
                          (unsigned char *) "dc");
                xmlNewNs (root_node,
                          (unsigned char *) "urn:schemas-upnp-org:"
                                            "metadata-1-0/upnp/",
                          (unsigned char *) "upnp");
                xmlNewNs (root_node,
                          (unsigned char *) "urn:schemas-upnp-org:"
                                            "metadata-1-0/DIDL-Lite/",
                          NULL);
                /* Subclasses must override the name of the node */
                priv->xml_node = xmlNewNode (NULL, (unsigned char *) "object");
                xmlAddChild (root_node, priv->xml_node);
        }

        ns_list = xmlGetNsList (priv->xml_doc->doc,
                                xmlDocGetRootElement (priv->xml_doc->doc));
        for (i = 0; ns_list[i] != NULL; i++) {
                if (ns_list[i]->prefix == NULL)
                        continue;

                if (g_ascii_strcasecmp ((char *) ns_list[i]->prefix,
                                        (char *) "upnp") == 0)
                        priv->upnp_ns = ns_list[i];
                else if (g_ascii_strcasecmp ((char *) ns_list[i]->prefix,
                                             (char *) "dc") == 0)
                        priv->dc_ns = ns_list[i];
        }

        object_class = G_OBJECT_CLASS (gupnp_didl_lite_object_parent_class);
        if (object_class->constructed != NULL)
                object_class->constructed (object);
}

static void
gupnp_didl_lite_object_dispose (GObject *object)
{
        GObjectClass               *object_class;
        GUPnPDIDLLiteObjectPrivate *priv;

        priv = GUPNP_DIDL_LITE_OBJECT (object)->priv;

        if (priv->xml_doc) {
                g_object_unref (priv->xml_doc);
                priv->xml_doc = NULL;
        }

        object_class = G_OBJECT_CLASS (gupnp_didl_lite_object_parent_class);
        object_class->dispose (object);
}

static void
gupnp_didl_lite_object_class_init (GUPnPDIDLLiteObjectClass *klass)
{
        GObjectClass *object_class;

        object_class = G_OBJECT_CLASS (klass);

        object_class->set_property = gupnp_didl_lite_object_set_property;
        object_class->get_property = gupnp_didl_lite_object_get_property;
        object_class->constructed = gupnp_didl_lite_object_constructed;
        object_class->dispose = gupnp_didl_lite_object_dispose;

        g_type_class_add_private (klass, sizeof (GUPnPDIDLLiteObjectPrivate));

        /**
         * GUPnPDIDLLiteObject:xml-node
         *
         * The pointer to object node in XML document.
         **/
        g_object_class_install_property
                (object_class,
                 PROP_XML_NODE,
                 g_param_spec_pointer ("xml-node",
                                       "XMLNode",
                                       "The pointer to object node in XML"
                                       " document.",
                                       G_PARAM_READWRITE |
                                       G_PARAM_CONSTRUCT_ONLY |
                                       G_PARAM_STATIC_NAME |
                                       G_PARAM_STATIC_NICK |
                                       G_PARAM_STATIC_BLURB));

        /**
         * GUPnPDIDLLiteObject:xml-doc
         *
         * The reference to XML document containing this object.
         *
         * Internal property.
         *
         * Stability: Private
         **/
        g_object_class_install_property
                (object_class,
                 PROP_XML_DOC,
                 g_param_spec_object ("xml-doc",
                                      "XMLDoc",
                                      "The reference to XML document"
                                      " containing this object.",
                                      GUPNP_TYPE_XML_DOC_WRAPPER,
                                      G_PARAM_WRITABLE |
                                      G_PARAM_CONSTRUCT_ONLY |
                                      G_PARAM_PRIVATE |
                                      G_PARAM_STATIC_NAME |
                                      G_PARAM_STATIC_NICK |
                                      G_PARAM_STATIC_BLURB));

        /**
         * GUPnPDIDLLiteObject:id
         *
         * The ID of this object.
         **/
        g_object_class_install_property
                (object_class,
                 PROP_ID,
                 g_param_spec_string ("id",
                                      "ID",
                                      "The ID of this object.",
                                      NULL,
                                      G_PARAM_READWRITE |
                                      G_PARAM_STATIC_NAME |
                                      G_PARAM_STATIC_NICK |
                                      G_PARAM_STATIC_BLURB));

        /**
         * GUPnPDIDLLiteObject:parent-id
         *
         * The ID of the parent container of this object.
         **/
        g_object_class_install_property
                (object_class,
                 PROP_PARENT_ID,
                 g_param_spec_string ("parent-id",
                                      "ParentID",
                                      "The ID of the parent container of"
                                      " this object.",
                                      NULL,
                                      G_PARAM_READWRITE |
                                      G_PARAM_STATIC_NAME |
                                      G_PARAM_STATIC_NICK |
                                      G_PARAM_STATIC_BLURB));

        /**
         * GUPnPDIDLLiteObject:restricted
         *
         * Whether this object is restricted.
         **/
        g_object_class_install_property
                (object_class,
                 PROP_RESTRICTED,
                 g_param_spec_string ("restricted",
                                      "Restricted",
                                      "Whether this object is restricted.",
                                      NULL,
                                      G_PARAM_READWRITE |
                                      G_PARAM_STATIC_NAME |
                                      G_PARAM_STATIC_NICK |
                                      G_PARAM_STATIC_BLURB));

        /**
         * GUPnPDIDLLiteObject:title
         *
         * The title of this object.
         **/
        g_object_class_install_property
                (object_class,
                 PROP_TITLE,
                 g_param_spec_string ("title",
                                      "Title",
                                      "The title of this object.",
                                      NULL,
                                      G_PARAM_READWRITE |
                                      G_PARAM_STATIC_NAME |
                                      G_PARAM_STATIC_NICK |
                                      G_PARAM_STATIC_BLURB));

        /**
         * GUPnPDIDLLiteObject:upnp-class
         *
         * The UPnP class of this object.
         **/
        g_object_class_install_property
                (object_class,
                 PROP_UPNP_CLASS,
                 g_param_spec_string ("upnp-class",
                                      "UPnPClassName",
                                      "The UPnP class of this object.",
                                      NULL,
                                      G_PARAM_READWRITE |
                                      G_PARAM_STATIC_NAME |
                                      G_PARAM_STATIC_NICK |
                                      G_PARAM_STATIC_BLURB));

        /**
         * GUPnPDIDLLiteObject:creator
         *
         * The creator of this object.
         **/
        g_object_class_install_property
                (object_class,
                 PROP_CREATOR,
                 g_param_spec_string ("creator",
                                      "Creator",
                                      "The creator of this object.",
                                      NULL,
                                      G_PARAM_READWRITE |
                                      G_PARAM_STATIC_NAME |
                                      G_PARAM_STATIC_NICK |
                                      G_PARAM_STATIC_BLURB));

        /**
         * GUPnPDIDLLiteObject:artist
         *
         * The artist of this object.
         **/
        g_object_class_install_property
                (object_class,
                 PROP_ARTIST,
                 g_param_spec_string ("artist",
                                      "Artist",
                                      "The artist of this object.",
                                      NULL,
                                      G_PARAM_READWRITE |
                                      G_PARAM_STATIC_NAME |
                                      G_PARAM_STATIC_NICK |
                                      G_PARAM_STATIC_BLURB));

        /**
         * GUPnPDIDLLiteObject:author
         *
         * The author of this object.
         **/
        g_object_class_install_property
                (object_class,
                 PROP_AUTHOR,
                 g_param_spec_string ("author",
                                      "Author",
                                      "The author of this object.",
                                      NULL,
                                      G_PARAM_READWRITE |
                                      G_PARAM_STATIC_NAME |
                                      G_PARAM_STATIC_NICK |
                                      G_PARAM_STATIC_BLURB));

        /**
         * GUPnPDIDLLiteObject:genre
         *
         * The genre of this object.
         **/
        g_object_class_install_property
                (object_class,
                 PROP_GENRE,
                 g_param_spec_string ("genre",
                                      "Genre",
                                      "The genre of this object.",
                                      NULL,
                                      G_PARAM_READWRITE |
                                      G_PARAM_STATIC_NAME |
                                      G_PARAM_STATIC_NICK |
                                      G_PARAM_STATIC_BLURB));

        /**
         * GUPnPDIDLLiteObject:write-status
         *
         * The write status of this object.
         **/
        g_object_class_install_property
                (object_class,
                 PROP_WRITE_STATUS,
                 g_param_spec_string ("write-status",
                                      "WriteStatus",
                                      "The write status of this object.",
                                      NULL,
                                      G_PARAM_READWRITE |
                                      G_PARAM_STATIC_NAME |
                                      G_PARAM_STATIC_NICK |
                                      G_PARAM_STATIC_BLURB));

        /**
         * GUPnPDIDLLiteObject:album
         *
         * The album of this object.
         **/
        g_object_class_install_property
                (object_class,
                 PROP_ALBUM,
                 g_param_spec_string ("album",
                                      "Album",
                                      "The album of this object.",
                                      NULL,
                                      G_PARAM_READWRITE |
                                      G_PARAM_STATIC_NAME |
                                      G_PARAM_STATIC_NICK |
                                      G_PARAM_STATIC_BLURB));

        /**
         * GUPnPDIDLLiteObject:album-art
         *
         * The URI to album art of this object.
         **/
        g_object_class_install_property
                (object_class,
                 PROP_ALBUM_ART,
                 g_param_spec_string ("album-art",
                                      "AlbumArt",
                                      "The URI to album art of this object.",
                                      NULL,
                                      G_PARAM_READWRITE |
                                      G_PARAM_STATIC_NAME |
                                      G_PARAM_STATIC_NICK |
                                      G_PARAM_STATIC_BLURB));

        /**
         * GUPnPDIDLLiteObject:description
         *
         * The description of this object.
         **/
        g_object_class_install_property
                (object_class,
                 PROP_DESCRIPTION,
                 g_param_spec_string ("description",
                                      "Description",
                                      "The description of this object.",
                                      NULL,
                                      G_PARAM_READWRITE |
                                      G_PARAM_STATIC_NAME |
                                      G_PARAM_STATIC_NICK |
                                      G_PARAM_STATIC_BLURB));

        /**
         * GUPnPDIDLLiteObject:date
         *
         * The date of this object.
         **/
        g_object_class_install_property
                (object_class,
                 PROP_DATE,
                 g_param_spec_string ("date",
                                      "Date",
                                      "The date of this object.",
                                      NULL,
                                      G_PARAM_READWRITE |
                                      G_PARAM_STATIC_NAME |
                                      G_PARAM_STATIC_NICK |
                                      G_PARAM_STATIC_BLURB));

        /**
         * GUPnPDIDLLiteObject:tracker-number
         *
         * The original tracker number of this object.
         **/
        g_object_class_install_property
                (object_class,
                 PROP_TRACK_NUMBER,
                 g_param_spec_int ("tracker-number",
                                   "TrackNumber",
                                   "The original track number of this  object.",
                                   -1, G_MAXINT, -1,
                                   G_PARAM_READWRITE |
                                   G_PARAM_STATIC_NAME |
                                   G_PARAM_STATIC_NICK |
                                   G_PARAM_STATIC_BLURB));
}

static gboolean
is_resource_compatible (GUPnPDIDLLiteResource *resource,
                        const char            *sink_protocol_info)
{
        gboolean ret = FALSE;
        char **protocols;
        guint8 i;

        protocols = g_strsplit (sink_protocol_info, ",", 0);

        for (i = 0; protocols[i] && !ret; i++) {
                GUPnPProtocolInfo *info;
                GUPnPProtocolInfo *res_info;

                info = gupnp_protocol_info_new_from_string (protocols[i], NULL);
                if (info == NULL)
                        continue;

                res_info = gupnp_didl_lite_resource_get_protocol_info
                                                        (resource);
                ret = gupnp_protocol_info_is_compatible (info, res_info);

                g_object_unref (info);
        }

        g_strfreev (protocols);

        return ret;
}

/**
 * gupnp_didl_lite_object_get_xml_node
 * @object: The #GUPnPDIDLLiteObject
 *
 * Get the pointer to object node in XML document.
 *
 * Return value: The pointer to object node in XML document.
 **/
xmlNode *
gupnp_didl_lite_object_get_xml_node (GUPnPDIDLLiteObject *object)
{
        g_return_val_if_fail (object != NULL, NULL);
        g_return_val_if_fail (GUPNP_IS_DIDL_LITE_OBJECT (object), NULL);

        return object->priv->xml_node;
}

/**
 * gupnp_didl_lite_object_get_upnp_class
 * @object: The #GUPnPDIDLLiteObject
 * @friendly_name: Location to put the friendly name of the UPnP class into, or
 * %NULL
 *
 * Get the UPnP class of the @object. If @friendly_name is not %NULL, the
 * friendly name of the UPnP class is put there that must be freed (using
 * #gfree) after usage.
 *
 * Return value: The class of @object, or %NULL. #g_free after usage.
 **/
char *
gupnp_didl_lite_object_get_upnp_class (GUPnPDIDLLiteObject *object,
                                       char               **friendly_name)
{
        g_return_val_if_fail (object != NULL, NULL);
        g_return_val_if_fail (GUPNP_IS_DIDL_LITE_OBJECT (object), NULL);

        return xml_util_get_child_element_content (object->priv->xml_node,
                                                   "class",
                                                   "name",
                                                   friendly_name,
                                                   NULL);
}

/**
 * gupnp_didl_lite_object_get_id
 * @object: #GUPnPDIDLLiteObject
 *
 * Get the ID of the @object.
 *
 * Return value: The ID of the @object, or %NULL. #g_free after usage.
 **/
char *
gupnp_didl_lite_object_get_id (GUPnPDIDLLiteObject *object)
{
        g_return_val_if_fail (object != NULL, NULL);
        g_return_val_if_fail (GUPNP_IS_DIDL_LITE_OBJECT (object), NULL);

        return xml_util_get_attribute_content (object->priv->xml_node, "id");
}

/**
 * gupnp_didl_lite_object_get_parent_id
 * @object: #GUPnPDIDLLiteObject
 *
 * Get the ID of the parent of the @object.
 *
 * Return value: The ID of parent of the @object, or %NULL. #g_free after
 * usage.
 **/
char *
gupnp_didl_lite_object_get_parent_id (GUPnPDIDLLiteObject *object)
{
        g_return_val_if_fail (object != NULL, NULL);
        g_return_val_if_fail (GUPNP_IS_DIDL_LITE_OBJECT (object), NULL);

        return xml_util_get_attribute_content (object->priv->xml_node,
                                               "parentID");
}

/**
 * gupnp_didl_lite_object_get_properties
 * @object: #GUPnPDIDLLiteObject
 * @name: name of the properties
 *
 * Use this function to retreive property nodes by name.
 *
 * Return value: The list of property nodes by the name @property_name
 * belonging to @object, or %NULL. #g_list_free the returned list after
 * usage but do not modify the contents.
 **/
GList *
gupnp_didl_lite_object_get_properties (GUPnPDIDLLiteObject *object,
                                       const char          *name)
{
        g_return_val_if_fail (object != NULL, NULL);
        g_return_val_if_fail (name != NULL, NULL);
        g_return_val_if_fail (GUPNP_IS_DIDL_LITE_OBJECT (object), NULL);

        return xml_util_get_child_elements_by_name (object->priv->xml_node,
                                                    name);
}

/**
 * gupnp_didl_lite_object_get_restricted
 * @object: #GUPnPDIDLLiteObject
 *
 * Whether the @object is restricted or not.
 *
 * Return value: #TRUE if @object is restricted.
 **/
gboolean
gupnp_didl_lite_object_get_restricted (GUPnPDIDLLiteObject *object)
{
        g_return_val_if_fail (object != NULL, FALSE);
        g_return_val_if_fail (GUPNP_IS_DIDL_LITE_OBJECT (object), FALSE);

        return xml_util_get_boolean_attribute (object->priv->xml_node,
                                               "restricted");
}

/**
 * gupnp_didl_lite_object_get_title
 * @object: #GUPnPDIDLLiteObject
 *
 * Get the title of the @object.
 *
 * Return value: The title of the @object, or %NULL. #g_free after usage.
 **/
char *
gupnp_didl_lite_object_get_title (GUPnPDIDLLiteObject *object)
{
        g_return_val_if_fail (object != NULL, FALSE);
        g_return_val_if_fail (GUPNP_IS_DIDL_LITE_OBJECT (object), NULL);

        return xml_util_get_child_element_content (object->priv->xml_node,
                                                   "title",
                                                   NULL);
}

/**
 * gupnp_didl_lite_object_get_creator
 * @object: #GUPnPDIDLLiteObject
 *
 * Get the creator of the @object.
 *
 * Return value: The creator of the @object, or %NULL. #g_free after
 * usage.
 **/
char *
gupnp_didl_lite_object_get_creator (GUPnPDIDLLiteObject *object)
{
        g_return_val_if_fail (object != NULL, FALSE);
        g_return_val_if_fail (GUPNP_IS_DIDL_LITE_OBJECT (object), NULL);

        return xml_util_get_child_element_content (object->priv->xml_node,
                                                   "creator",
                                                   NULL);
}

/**
 * gupnp_didl_lite_object_get_artist
 * @object: #GUPnPDIDLLiteObject
 * @role: Location to put the role string (if any) into, or %NULL
 *
 * Get the artist of the @object. If role is not %NULL, it is set to the role
 * of the artist if available that must be freed (using #gfree) after usage.
 *
 * Return value: The artist of the @object, or %NULL. #g_free after usage.
 **/
char *
gupnp_didl_lite_object_get_artist (GUPnPDIDLLiteObject *object,
                                   char               **role)
{
        g_return_val_if_fail (object != NULL, FALSE);
        g_return_val_if_fail (GUPNP_IS_DIDL_LITE_OBJECT (object), NULL);

        return xml_util_get_child_element_content (object->priv->xml_node,
                                                   "artist",
                                                   "role",
                                                   role,
                                                   NULL);
}

/**
 * gupnp_didl_lite_object_get_author
 * @object: #GUPnPDIDLLiteObject
 * @role: Location to put the role string (if any) into, or %NULL
 *
 * Get the author of the @object. If role is not %NULL, it is set to the role
 * of the author if available that must be freed (using #gfree) after usage.
 *
 * Return value: The author of the @object, or %NULL. #g_free after usage.
 **/
char *
gupnp_didl_lite_object_get_author (GUPnPDIDLLiteObject *object,
                                   char               **role)
{
        g_return_val_if_fail (object != NULL, FALSE);
        g_return_val_if_fail (GUPNP_IS_DIDL_LITE_OBJECT (object), NULL);

        return xml_util_get_child_element_content (object->priv->xml_node,
                                                   "author",
                                                   "role",
                                                   role,
                                                   NULL);
}

/**
 * gupnp_didl_lite_object_get_genre
 * @object: #GUPnPDIDLLiteObject
 * @id: Location to put the ID string (if any) into, or %NULL
 * @extended: Location to put the extended genre string (if any) into, or %NULL
 *
 * Get the genre of the @object. If @id is not %NULL, it is set to the ID
 * of the genre if available that must be freed (using #gfree) after usage. The
 * same goes for @extended.
 *
 * Return value: The genre of the @object, or %NULL. #g_free after usage.
 **/
char *
gupnp_didl_lite_object_get_genre (GUPnPDIDLLiteObject *object,
                                  char               **id,
                                  char               **extended)
{
        g_return_val_if_fail (object != NULL, FALSE);
        g_return_val_if_fail (GUPNP_IS_DIDL_LITE_OBJECT (object), NULL);

        return xml_util_get_child_element_content (object->priv->xml_node,
                                                   "genre",
                                                   "id",
                                                   id,
                                                   "extended",
                                                   extended,
                                                   NULL);
}

/**
 * gupnp_didl_lite_object_get_write_status
 * @object: #GUPnPDIDLLiteObject
 *
 * Get the write status of the @object.
 *
 * Return value: The write status of the @object, or %NULL. #g_free after
 * usage.
 **/
char *
gupnp_didl_lite_object_get_write_status (GUPnPDIDLLiteObject *object)
{
        g_return_val_if_fail (object != NULL, FALSE);

        return xml_util_get_child_element_content (object->priv->xml_node,
                                                   "writeStatus",
                                                   NULL);
}

/**
 * gupnp_didl_lite_object_get_album
 * @object: #GUPnPDIDLLiteObject
 *
 * Get the album of the @object.
 *
 * Return value: The album of the @object, or %NULL. #g_free after
 * usage.
 **/
char *
gupnp_didl_lite_object_get_album (GUPnPDIDLLiteObject *object)
{
        g_return_val_if_fail (object != NULL, FALSE);

        return xml_util_get_child_element_content (object->priv->xml_node,
                                                   "album",
                                                   NULL);
}

/**
 * gupnp_didl_lite_object_get_album_art
 * @object: #GUPnPDIDLLiteObject
 *
 * Get the URI to album art of the @object.
 *
 * Return value: The URI to album art of the @object, or %NULL. #g_free after
 * usage.
 **/
char *
gupnp_didl_lite_object_get_album_art (GUPnPDIDLLiteObject *object)
{
        g_return_val_if_fail (object != NULL, FALSE);

        return xml_util_get_child_element_content (object->priv->xml_node,
                                                   "albumArtURI",
                                                   NULL);
}

/**
 * gupnp_didl_lite_object_get_description
 * @object: #GUPnPDIDLLiteObject
 *
 * Get the description of the @object.
 *
 * Return value: The description of the @object, or %NULL. #g_free after
 * usage.
 **/
char *
gupnp_didl_lite_object_get_description (GUPnPDIDLLiteObject *object)
{
        g_return_val_if_fail (object != NULL, FALSE);

        return xml_util_get_child_element_content (object->priv->xml_node,
                                                   "description",
                                                   NULL);
}

/**
 * gupnp_didl_lite_object_get_date
 * @object: #GUPnPDIDLLiteObject
 *
 * Get the date of the @object.
 *
 * Return value: The date of the @object, or %NULL. #g_free after
 * usage.
 **/
char *
gupnp_didl_lite_object_get_date (GUPnPDIDLLiteObject *object)
{
        g_return_val_if_fail (object != NULL, FALSE);

        return xml_util_get_child_element_content (object->priv->xml_node,
                                                   "date",
                                                   NULL);
}

/**
 * gupnp_didl_lite_object_get_track_number
 * @object: #GUPnPDIDLLiteObject
 *
 * Get the original track number of the @object.
 *
 * Return value: The original track number of the @object, or -1.
 **/
int
gupnp_didl_lite_object_get_track_number (GUPnPDIDLLiteObject *object)
{
        char *str;
        int ret;

        g_return_val_if_fail (object != NULL, FALSE);

        str = xml_util_get_child_element_content (object->priv->xml_node,
                                                  "originalTrackNumber",
                                                  NULL);
        if (str) {
                ret = atoi (str);
                g_free (str);
        } else
                ret = -1;

        return ret;
}

/**
 * gupnp_didl_lite_object_get_resources
 * @object: #GUPnPDIDLLiteObject
 *
 * Use this function to retreive resources from the @object.
 *
 * Return value: The list of resources belonging to @object, or %NULL.
 * #g_list_free the returned list after usage and unref each resource in it.
 **/
GList *
gupnp_didl_lite_object_get_resources (GUPnPDIDLLiteObject *object)
{
        GList *resources = NULL;
        GList *res = NULL;
        GList *ret = NULL;

        g_return_val_if_fail (object != NULL, NULL);
        g_return_val_if_fail (GUPNP_IS_DIDL_LITE_OBJECT (object), NULL);

        resources = gupnp_didl_lite_object_get_properties (object, "res");

        for (res = resources; res; res = res->next) {
                GUPnPDIDLLiteResource *resource;
                xmlNode *res_node;
                GError *error;

                res_node = (xmlNode *) res->data;

                error = NULL;
                /* Create a resource struct out of DIDLLite XML */
                resource = gupnp_didl_lite_resource_new_from_xml (res_node,
                                                                  &error);
                if (resources == NULL) {
                        g_warning ("Error parsing a 'res' node: %s",
                                   error->message);

                        g_error_free (error);

                        continue;
                }

                ret = g_list_append (ret, resource);
        }

        g_list_free (resources);

        return ret;
}

/**
 * gupnp_didl_lite_object_get_compat_resource
 * @object: #GUPnPDIDLLiteObject
 * @sink_protocol_info: The SinkProtocolInfo string from MediaRenderer
 * @lenient: Enable lenient mode
 *
 * Use this function to get a resource from the @object that is compatible with
 * any of the protocols specified in the @sink_protocol_info. The value of
 * @sink_protocol_info will typically be acquired from 'Sink' argument of
 * 'GetProtocolInfo' action or 'SinkProtocolInfo' state-variable of a
 * ConnectionManager service.
 *
 * If @lenient is #TRUE, the first resource in the list is returned instead of
 * %NULL if none of resources and protocols are found to be compatible.
 *
 * Return value: The resource belonging to @object that is comaptible with
 * any of the protocols specified in @sink_protocol_info, or %NULL. Unref after
 * usage.
 **/
GUPnPDIDLLiteResource *
gupnp_didl_lite_object_get_compat_resource
                                (GUPnPDIDLLiteObject *object,
                                 const char          *sink_protocol_info,
                                 gboolean             lenient)
{
        GUPnPDIDLLiteResource *resource = NULL;
        GList  *resources = NULL;
        GList  *res;

        g_return_val_if_fail (object != NULL, NULL);
        g_return_val_if_fail (GUPNP_IS_DIDL_LITE_OBJECT (object), NULL);
        g_return_val_if_fail (sink_protocol_info != NULL, NULL);

        resources = gupnp_didl_lite_object_get_resources (object);

        for (res = resources;
             res != NULL && resource == NULL;
             res = res->next) {
                resource = (GUPnPDIDLLiteResource *) res->data;

                if (!is_resource_compatible (resource, sink_protocol_info))
                        resource = NULL;
        }

        if (resource == NULL && lenient)
                /* Just use the first resource */
                resource = (GUPnPDIDLLiteResource *) resources->data;

        /* Unref all resources except for the one we just took */
        for (res = resources; res; res = res->next)
                if (res->data != resource)
                        g_object_unref (res->data);
        g_list_free (resources);

        return resource;
}

/**
 * gupnp_didl_lite_object_set_upnp_class
 * @object: The #GUPnPDIDLLiteObject
 * @upnp_class: The UPnP class
 * @friendly_name: The friendly name of the UPnP class
 *
 * Set the UPnP class of the @object to @upnp_class.
 **/
void
gupnp_didl_lite_object_set_upnp_class (GUPnPDIDLLiteObject *object,
                                       const char          *upnp_class,
                                       const char          *friendly_name)
{
        g_return_if_fail (object != NULL);
        g_return_if_fail (GUPNP_IS_DIDL_LITE_OBJECT (object));

        xml_util_set_child (object->priv->xml_node,
                            object->priv->upnp_ns,
                            "class",
                            upnp_class,
                            "name",
                            friendly_name,
                            NULL);

        g_object_notify (G_OBJECT (object), "upnp-class");
}

/**
 * gupnp_didl_lite_object_set_id
 * @object: #GUPnPDIDLLiteObject
 * @id: The ID
 *
 * Set the ID of the @object to @id.
 **/
void
gupnp_didl_lite_object_set_id (GUPnPDIDLLiteObject *object,
                               const char          *id)
{
        g_return_if_fail (object != NULL);
        g_return_if_fail (GUPNP_IS_DIDL_LITE_OBJECT (object));

        xmlSetProp (object->priv->xml_node,
                    (unsigned char *) "id",
                    (unsigned char *) id);

        g_object_notify (G_OBJECT (object), "id");
}

/**
 * gupnp_didl_lite_object_set_parent_id
 * @object: #GUPnPDIDLLiteObject
 * @parent_id: The parent ID
 *
 * Set the ID of the parent of the @object to @parent_id.
 **/
void
gupnp_didl_lite_object_set_parent_id (GUPnPDIDLLiteObject *object,
                                      const char          *parent_id)
{
        g_return_if_fail (object != NULL);
        g_return_if_fail (GUPNP_IS_DIDL_LITE_OBJECT (object));

        xmlSetProp (object->priv->xml_node,
                    (unsigned char *) "parentID",
                    (unsigned char *) parent_id);

        g_object_notify (G_OBJECT (object), "parent-id");
}

/**
 * gupnp_didl_lite_object_set_restricted
 * @object: #GUPnPDIDLLiteObject
 * @restricted: The restricted status
 *
 * Set the restricted status of @object to @restricted.
 **/
void
gupnp_didl_lite_object_set_restricted (GUPnPDIDLLiteObject *object,
                                       gboolean             restricted)
{
        const char *str;

        g_return_if_fail (object != NULL);
        g_return_if_fail (GUPNP_IS_DIDL_LITE_OBJECT (object));

        if (restricted)
                str = "1";
        else
                str = "0";
        xmlSetProp (object->priv->xml_node,
                    (unsigned char *) "restricted",
                    (unsigned char *) str);

        g_object_notify (G_OBJECT (object), "restricted");
}

/**
 * gupnp_didl_lite_object_set_title
 * @object: #GUPnPDIDLLiteObject
 * @title: The title
 *
 * Set the title of the @object to @title.
 **/
void
gupnp_didl_lite_object_set_title (GUPnPDIDLLiteObject *object,
                                  const char          *title)
{
        g_return_if_fail (object != NULL);
        g_return_if_fail (GUPNP_IS_DIDL_LITE_OBJECT (object));

        xml_util_set_child (object->priv->xml_node,
                            object->priv->dc_ns,
                            "title",
                            title,
                            NULL);

        g_object_notify (G_OBJECT (object), "title");
}

/**
 * gupnp_didl_lite_object_set_creator
 * @object: #GUPnPDIDLLiteObject
 * @creator: The creator
 *
 * Set the creator of the @object to @creator.
 **/
void
gupnp_didl_lite_object_set_creator (GUPnPDIDLLiteObject *object,
                                    const char          *creator)
{
        g_return_if_fail (object != NULL);
        g_return_if_fail (GUPNP_IS_DIDL_LITE_OBJECT (object));

        xml_util_set_child (object->priv->xml_node,
                            object->priv->dc_ns,
                            "creator",
                            creator,
                            NULL);

        g_object_notify (G_OBJECT (object), "creator");
}

/**
 * gupnp_didl_lite_object_set_artist
 * @object: The #GUPnPDIDLLiteObject
 * @artist: The Artist
 * @role: The role of the Artist or %NULL
 *
 * Set the Artist of the @object to @artist and her/his role to @role.
 **/
void
gupnp_didl_lite_object_set_artist (GUPnPDIDLLiteObject *object,
                                   const char          *artist,
                                   const char          *role)
{
        g_return_if_fail (object != NULL);
        g_return_if_fail (GUPNP_IS_DIDL_LITE_OBJECT (object));

        xml_util_set_child (object->priv->xml_node,
                            object->priv->upnp_ns,
                            "artist",
                            artist,
                            "role",
                            role,
                            NULL);

        g_object_notify (G_OBJECT (object), "artist");
}

/**
 * gupnp_didl_lite_object_set_author
 * @object: The #GUPnPDIDLLiteObject
 * @author: The Author
 * @role: The role of the Author or %NULL
 *
 * Set the Author of the @object to @author and her/his role to @role.
 **/
void
gupnp_didl_lite_object_set_author (GUPnPDIDLLiteObject *object,
                                   const char          *author,
                                   const char          *role)
{
        g_return_if_fail (object != NULL);
        g_return_if_fail (GUPNP_IS_DIDL_LITE_OBJECT (object));

        xml_util_set_child (object->priv->xml_node,
                            object->priv->upnp_ns,
                            "author",
                            author,
                            "role",
                            role,
                            NULL);

        g_object_notify (G_OBJECT (object), "author");
}

/**
 * gupnp_didl_lite_object_set_genre
 * @object: The #GUPnPDIDLLiteObject
 * @genre: The Genre
 * @id: The role of the Genre or %NULL
 * @extended: A string containing CSV list of sub-genre names or %NULL
 *
 * Set the Author of the @object to @author, id to @id and extended genre list
 * to @extended.
 **/
void
gupnp_didl_lite_object_set_genre (GUPnPDIDLLiteObject *object,
                                  const char          *genre,
                                  const char          *id,
                                  const char          *extended)
{
        g_return_if_fail (object != NULL);
        g_return_if_fail (GUPNP_IS_DIDL_LITE_OBJECT (object));

        xml_util_set_child (object->priv->xml_node,
                            object->priv->dc_ns,
                            "genre",
                            genre,
                            "id",
                            id,
                            "extended",
                            extended,
                            NULL);

        g_object_notify (G_OBJECT (object), "genre");
}

/**
 * gupnp_didl_lite_object_set_write_status
 * @object: #GUPnPDIDLLiteObject
 * @write_status: The write status string
 *
 * Set the write status of the @object to @write_status.
 **/
void
gupnp_didl_lite_object_set_write_status (GUPnPDIDLLiteObject *object,
                                         const char          *write_status)
{
        g_return_if_fail (object != NULL);
        g_return_if_fail (GUPNP_IS_DIDL_LITE_OBJECT (object));

        xml_util_set_child (object->priv->xml_node,
                            object->priv->dc_ns,
                            "writeStatus",
                            write_status,
                            NULL);

        g_object_notify (G_OBJECT (object), "write-status");
}

/**
 * gupnp_didl_lite_object_set_album
 * @object: #GUPnPDIDLLiteObject
 * @album: The album string
 *
 * Set the album of the @object to @album.
 **/
void
gupnp_didl_lite_object_set_album (GUPnPDIDLLiteObject *object,
                                  const char          *album)
{
        g_return_if_fail (object != NULL);
        g_return_if_fail (GUPNP_IS_DIDL_LITE_OBJECT (object));

        xml_util_set_child (object->priv->xml_node,
                            object->priv->upnp_ns,
                            "album",
                            album,
                            NULL);

        g_object_notify (G_OBJECT (object), "album");
}

/**
 * gupnp_didl_lite_object_set_album_art
 * @object: #GUPnPDIDLLiteObject
 * @album_art: The URI of album art
 *
 * Set the URI to album art of the @object to @album_art.
 **/
void
gupnp_didl_lite_object_set_album_art (GUPnPDIDLLiteObject *object,
                                      const char          *album_art)
{
        g_return_if_fail (object != NULL);
        g_return_if_fail (GUPNP_IS_DIDL_LITE_OBJECT (object));

        xml_util_set_child (object->priv->xml_node,
                            object->priv->upnp_ns,
                            "albumArtURI",
                            album_art,
                            NULL);

        g_object_notify (G_OBJECT (object), "album-art");
}

/**
 * gupnp_didl_lite_object_set_description
 * @object: #GUPnPDIDLLiteObject
 * @description: The description string
 *
 * Set the description of the @object to @description.
 **/
void
gupnp_didl_lite_object_set_description (GUPnPDIDLLiteObject *object,
                                        const char          *description)
{
        g_return_if_fail (object != NULL);
        g_return_if_fail (GUPNP_IS_DIDL_LITE_OBJECT (object));

        xml_util_set_child (object->priv->xml_node,
                            object->priv->dc_ns,
                            "description",
                            description,
                            NULL);

        g_object_notify (G_OBJECT (object), "description");
}

/**
 * gupnp_didl_lite_object_set_date
 * @object: #GUPnPDIDLLiteObject
 * @date: The date string
 *
 * Set the date of the @object to @date.
 **/
void
gupnp_didl_lite_object_set_date (GUPnPDIDLLiteObject *object,
                                 const char          *date)
{
        g_return_if_fail (object != NULL);
        g_return_if_fail (GUPNP_IS_DIDL_LITE_OBJECT (object));

        xml_util_set_child (object->priv->xml_node,
                            object->priv->dc_ns,
                            "date",
                            date,
                            NULL);

        g_object_notify (G_OBJECT (object), "date");
}

/**
 * gupnp_didl_lite_object_set_track_number
 * @object: #GUPnPDIDLLiteObject
 * @track_number: The original track number
 *
 * Set the original track number of the @object to @track_number.
 **/
void
gupnp_didl_lite_object_set_track_number (GUPnPDIDLLiteObject *object,
                                         int                  track_number)
{
        char *str;

        g_return_if_fail (object != NULL);
        g_return_if_fail (GUPNP_IS_DIDL_LITE_OBJECT (object));

        str = g_strdup_printf ("%d", track_number);
        xml_util_set_child (object->priv->xml_node,
                            object->priv->upnp_ns,
                            "originalTrackNumber",
                            str,
                            NULL);
        g_free (str);

        g_object_notify (G_OBJECT (object), "track-number");
}

/**
 * gupnp_didl_lite_object_to_string
 * @object: #GUPnPDIDLLiteObject
 *
 * Creates an XML string representation of @object.
 *
 * Return value: The XML string representation of @object, or %NULL.
 * #g_free after usage.
 **/
char *
gupnp_didl_lite_object_to_string (GUPnPDIDLLiteObject *object)
{
        xmlBuffer *buffer;
        char      *ret;

        g_return_val_if_fail (object != NULL, FALSE);
        g_return_val_if_fail (GUPNP_IS_DIDL_LITE_OBJECT (object), NULL);

        buffer = xmlBufferCreate ();
        xmlNodeDump (buffer,
                     object->priv->xml_doc->doc,
                     object->priv->xml_node,
                     0,
                     0);
        ret = g_strndup ((char *) xmlBufferContent (buffer),
                         xmlBufferLength (buffer));
        xmlBufferFree (buffer);

        return ret;
}

