#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "structs.h"
#include "ui_utils.h"
#include "ui_messages.h"
#include "login.h"
#include "main_window.h"
#include "db_utils.h"

#define GLADE_UI_FILE "login.glade"

GtkBuilder *builder;
sqlite3 *db;
sqlite3_stmt *res;
int rc;
GtkListStore *employee_list_store;