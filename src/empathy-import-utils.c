/*
 * Copyright (C) 2009 Collabora Ltd.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * Authors: Jonny Lamb <jonny.lamb@collabora.co.uk>
 *          Cosimo Cecchi <cosimo.cecchi@collabora.co.uk>
 */

#include <telepathy-glib/util.h>

#include <libempathy/empathy-utils.h>

#include "empathy-import-utils.h"
#include "empathy-import-pidgin.h"

EmpathyImportAccountData *
empathy_import_account_data_new (const gchar *source)
{
  EmpathyImportAccountData *data;

  g_return_val_if_fail (!EMP_STR_EMPTY (source), NULL);

  data = g_slice_new0 (EmpathyImportAccountData);
  data->settings = g_hash_table_new_full (g_str_hash, g_str_equal, NULL,
    (GDestroyNotify) tp_g_value_slice_free);
  data->source = g_strdup (source);
  data->protocol = NULL;
  data->connection_manager = NULL;

  return data;
}

void
empathy_import_account_data_free (EmpathyImportAccountData *data)
{
  if (data == NULL)
    return;
  if (data->protocol != NULL)
    g_free (data->protocol);
  if (data->connection_manager != NULL)
    g_free (data->connection_manager);
  if (data->settings != NULL)
    g_hash_table_destroy (data->settings);
  if (data->source != NULL)
    g_free (data->source);

  g_slice_free (EmpathyImportAccountData, data);
}

gboolean
empathy_import_accounts_to_import (void)
{
  return empathy_import_pidgin_accounts_to_import ();
}

GList *
empathy_import_accounts_load (EmpathyImportApplication id)
{
  if (id == EMPATHY_IMPORT_APPLICATION_PIDGIN)
    return empathy_import_pidgin_load ();

  return empathy_import_pidgin_load ();
}