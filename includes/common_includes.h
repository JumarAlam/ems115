#ifndef SQLITE3_H
#define SQLITE3_H
#include <sqlite3.h>
#endif

#ifndef GTK_GTK_H
#define GTK_GTK_H
#include <gtk/gtk.h>
#endif

#ifndef STRING_H
#define STRING_H
#include <string.h>
#endif

#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif

#include "struct.h"
#include "ui_utils.h"
#include "login.h"
#include "main_window.h"

#define GLADE_UI_FILE "login.glade"

GtkBuilder *builder;