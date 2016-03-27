/* 
 * Copyright (c) 2016 Ashiqur Rahman <ashiqur.rahman05@northsouth.edu>
 *              Aniruddha Adhikary <aniruddha.adhikary@northsouth.edu>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "common_includes.h"
#include "main_window.h"

GtkWidget *main_window;
GtkDialog *about_dialog;
GtkStatusbar *statusbar;

void show_main_window() {
	main_window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
	statusbar = GTK_STATUSBAR(gtk_builder_get_object(builder, "statusbar"));
	gtk_builder_connect_signals(builder, NULL);

	gtk_statusbar_push(statusbar, gtk_statusbar_get_context_id(statusbar, "boo"), "Ready");

	gtk_widget_show(main_window);
}

void on_menu_help_about_activate(GtkObject *object, gpointer user_data) {
	about_dialog = GTK_DIALOG(gtk_builder_get_object(builder, "about_dialog"));
	gtk_builder_connect_signals(builder, NULL);

	gtk_dialog_run(about_dialog);
}

void on_about_dialog_response(GtkObject *object, gpointer user_data) {
	
}

void on_main_window_destroy(GtkObject *object, gpointer user_data) {
	gtk_main_quit();
}

void on_menu_quit_activate(GtkObject *object, gpointer user_data) {
	gtk_main_quit();
}