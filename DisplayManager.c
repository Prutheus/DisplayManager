#include <libappindicator/app-indicator.h>

static void activate_desktop(GtkAction *action);
static void activate_cube_only(GtkAction *action);
static void activate_cube_onlyHD(GtkAction *action);
static void activate_cube_dual(GtkAction *action);

static GtkActionEntry entries[] = { {"Desktop", "gtk-go-forward-ltr", "_Desktop", "<control>D", "", G_CALLBACK(activate_desktop)}
                                  , {"CubeOnly", "gtk-go-forward-ltr", "_CubeOnly", "<control>C", "", G_CALLBACK(activate_cube_only)}
                                  , {"CubeOnlyHD", "gtk-go-forward-ltr", "_CubeOnlyHD", "<control>H", "", G_CALLBACK(activate_cube_onlyHD)}
                                  , {"CubeDual", "gtk-go-forward-ltr", "_CubeDual", "<control>X", "", G_CALLBACK(activate_cube_dual)}
                                  , {"Quit", "application-exit", "_Quit", "<control>Q", "", G_CALLBACK(gtk_main_quit)},
                                  };

static guint n_entries = G_N_ELEMENTS(entries);

static const gchar *ui_info =
"<ui>"
"  <popup name='IndicatorPopup'>"
"    <menuitem action='Desktop' />"
"    <menuitem action='CubeOnly' />"
"    <menuitem action='CubeOnlyHD' />"
"    <menuitem action='CubeDual' />"
"    <menuitem action='Quit' />"
"  </popup>"
"</ui>";

static void activate_desktop(GtkAction *action) {
  system("xrandr --output VIRTUAL1 --off --output DP1 --off --output HDMI2 --off --output HDMI1 --off --output DP1-1 --primary --mode 3440x1440 --pos 0x0 --rotate normal --output DP1-2 --off --output DVI-I-1 --off --output DP2 --off --output eDP1 --off && nitrogen --restore");
}

static void activate_cube_only(GtkAction *action) {
  system("xrandr --output VIRTUAL1 --off --output DP1 --off --output HDMI2 --off --output HDMI1 --off --output DP1-2 --primary --mode 712x400_60.00 --pos 0x0 --rotate normal --output DP1-1 --off --output DVI-I-1 --off --output DP2 --off --output eDP1 --off && nitrogen --restore");
}

static void activate_cube_onlyHD(GtkAction *action) {
  system("xrandr --output VIRTUAL1 --off --output DP1 --off --output HDMI2 --off --output HDMI1 --off --output DP1-2 --primary --mode 1280x720 --pos 0x0 --rotate normal --output DP1-1 --off --output DVI-I-1 --off --output DP2 --off --output eDP1 --off && nitrogen --restore");
}

static void activate_cube_dual(GtkAction *action) {
  system("xrandr --output VIRTUAL1 --off --output eDP1 --off --output DP1 --off --output HDMI2 --off --output HDMI1 --off --output DP1-2 --mode 712x400_60.00 --pos 0x0 --rotate normal --output DP1-1 --primary --mode 3440x1440 --pos 0x400 --rotate normal --output DP2 --off && nitrogen --restore");
}

int main(int argc, char **argv) {
  GtkWidget*      indicator_menu;
  GtkActionGroup* action_group;
  GtkUIManager*   uim;
  AppIndicator*   indicator;
  GError*         error = NULL;

  gtk_init(&argc, &argv);

  action_group = gtk_action_group_new("DisplayManager");
  gtk_action_group_add_actions(action_group, entries, n_entries, NULL);

  uim = gtk_ui_manager_new();
  gtk_ui_manager_insert_action_group(uim, action_group, 0);

  if(!gtk_ui_manager_add_ui_from_string(uim, ui_info, -1, &error)) {
    g_message("Failed to build menus: %s\n", error->message);
    g_error_free(error);
    error = NULL;
  }

  indicator = app_indicator_new_with_path("DisplayManager", "/home/prutheus/workspace/programming/c/DisplayManager/monitor.gif", APP_INDICATOR_CATEGORY_APPLICATION_STATUS, "/home/prutheus/workspace/programming/c/DisplayManager/");

  indicator_menu = gtk_ui_manager_get_widget(uim, "/ui/IndicatorPopup");

  app_indicator_set_status(indicator, APP_INDICATOR_STATUS_ACTIVE);

  app_indicator_set_menu(indicator, GTK_MENU(indicator_menu));

  system("xrandr --newmode '712x400_60.00'   22.00  712 736 800 888  400 403 413 417 -hsync +vsync");
  system("xrandr --addmode DP1-2 712x400_60.00");

  gtk_main();

  return 0;
}
