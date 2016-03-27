#include <sqlite3.h>
#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>

#include "struct.h"
#include "ui_utils.h"
#include "ui_messages.h"
#include "login.h"
#include "main_window.h"

#define GLADE_UI_FILE "login.glade"

GtkBuilder *builder;