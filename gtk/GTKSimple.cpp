#include <gtk/gtk.h>

int main (int argc, char *argv[])
{
	// This application will have a window and a single label
	GtkWidget *window, *label;

	// Initialize the GTK toolkit, pass command-line arguments
	gtk_init (&argc, &argv);

	// Create the top-level window (not yet visible)
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

	// Set the title of the window to "Exploring BB");
	gtk_window_set_title (GTK_WINDOW (window), "Exploring BB");

	// Create a label
	label = gtk_label_new ("Hello Beaglebone");

	// Add the label to the window
	gtk_container_add (GTK_CONTAINER (window), label);

	// Make the label visible (must be performed for every widget)
	gtk_widget_show (label);

	// Make the window visible on the display
	gtk_widget_show (window);

	// Run the main loop until gtk_main_quit () is
	// called for example, if Ctrl+C is typed
	gtk_main ();

	return 0;
}
