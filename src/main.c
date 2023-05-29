#include <gtk/gtk.h>
#include <math.h>

FILE* fancontrol_file;

static void on_slide(GtkRange* slider, GtkLabel* value_label) {
    gint value = (gint) floor(gtk_range_get_value(slider) + 0.5);
    gtk_range_set_value(slider, (gdouble) value);
    gchar value_label_text[5];
    switch (value) {
        case -1:
            sprintf(value_label_text, "auto");
            fputs("level auto", fancontrol_file);
            break;
        case 8:
            sprintf(value_label_text, "full");
            fputs("level full-speed", fancontrol_file);
            break;
        case 9:
            sprintf(value_label_text, "max");
            fputs("level disengaged", fancontrol_file);
            break;
        default:
            sprintf(value_label_text, "%d", value);
            fprintf(fancontrol_file, "level %d", value);
            break;
    }
    fflush(fancontrol_file);
    gtk_label_set_text(value_label, value_label_text);
}

static void on_close(GtkWindow* window) {
    fputs("level auto", fancontrol_file);
    fflush(fancontrol_file);
    fclose(fancontrol_file);
}

static void on_activate(GtkApplication* app) {
    GtkWidget* window = gtk_application_window_new(app);
    g_signal_connect(window, "destroy", G_CALLBACK(on_close), NULL);

    GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    GtkWidget* title_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(title_label),
            "<span font=\"18\"> Thinkpad Fan Speed </span>");
    GtkWidget* slider = gtk_scale_new_with_range(
            GTK_ORIENTATION_HORIZONTAL, -1, 9, 1);
    GtkWidget* value_label = gtk_label_new("auto");

    g_signal_connect(slider, "value-changed",
            G_CALLBACK(on_slide), value_label);

    gtk_box_append(GTK_BOX(box), title_label);
    gtk_box_append(GTK_BOX(box), slider);
    gtk_box_append(GTK_BOX(box), value_label);

    gtk_window_set_default_size(GTK_WINDOW(window), 360, 240);
    gtk_window_set_child(GTK_WINDOW(window), box);
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char* argv[]) {
    fancontrol_file = fopen("/proc/acpi/ibm/fan", "w");
    if (fancontrol_file == NULL) {
        fprintf(stderr, "Permission denied; run as root (su -c '%s')\n",
                argv[0]);
        exit(1);
    }
    GtkApplication* app = gtk_application_new("com.example.GtkApplication",
            G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
    return g_application_run(G_APPLICATION(app), argc, argv);
}
