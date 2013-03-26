/* -*- c-basic-offset: 4; -*-

 * See LICENSE for license details
 *
 * Changelog:
 * ---------
 *
 * (c) 2009 by Robert Manea
 *     - introduced struct concept
 *
 */

#ifndef __UZBL_CORE__
#define __UZBL_CORE__

#include "webkit.h"

#include "cookie-jar.h"

#include <sys/types.h>

#define UZBL_UNUSED(var) (void)var
#define uzbl_debug(...) if (uzbl.state.verbose) printf(__VA_ARGS__)


/* GUI elements */
typedef struct {
    /* Window */
    GtkWidget*     main_window;
    gchar*         geometry;
    GtkPlug*       plug;
    GtkWidget*     scrolled_win;
    GtkWidget*     vbox;

    /* Mainbar */
    GtkWidget*     status_bar;

    /* Scrolling */
    GtkAdjustment* bar_v;     /* Information about document length */
    GtkAdjustment* bar_h;     /* and scrolling position */

    /* Web page */
    WebKitWebView* web_view;
    gchar*         main_title;
    gchar*         icon;
    gchar*         icon_name;

    /* WebInspector */
    GtkWidget*          inspector_window;
    WebKitWebInspector* inspector;

    /* Custom context menu item */
    gboolean       custom_context_menu;
    GPtrArray*     menu_items;
} GUI;


/* External communication */
enum { FIFO, SOCKET};
typedef struct {
    gchar          *fifo_path;
    gchar          *socket_path;

    GPtrArray      *connect_chan;
    GPtrArray      *client_chan;
} Communication;


/* Internal state */
typedef struct {
    gchar*          uri;
    gchar*          config_file;
    char*           instance_name;
    gchar*          selected_url;
    gchar*          last_selected_url;
    gchar*          executable_path;
    gchar*          searchtx;
    gboolean        verbose;
    gboolean        embed;
    GdkEventButton* last_button;
    gchar*          last_result;
    gboolean        plug_mode;

    /* Events */
    int             socket_id;
    gboolean        events_stdout;
    gboolean        handle_multi_button;
    GPtrArray*      event_buffer;
    gchar**         connect_socket_names;
} State;


/* Networking */
typedef struct {
    SoupSession*    soup_session;
    UzblCookieJar*  soup_cookie_jar;
    GHashTable*     pending_auths;
    SoupLogger*     soup_logger;
    char*           proxy_url;
    char*           useragent;
    char*           accept_languages;
    gint            max_conns;
    gint            max_conns_host;
} Network;

/* Behaviour */
typedef struct {
    /* Status bar */
    gchar*   status_format;
    gchar*   status_format_right;
    gchar*   status_background;
    gboolean status_top;

    /* Window title */
    gchar*   title_format_short;
    gchar*   title_format_long;

    /* Communication */
    gchar*   fifo_dir;
    gchar*   socket_dir;

    /* Handlers */
    gchar*   authentication_handler;
    gchar*   scheme_handler;
    gchar*   request_handler;
    gchar*   download_handler;

    gboolean forward_keys;
    guint    http_debug;
    gchar*   shell_cmd;
    guint    view_source;
    gboolean maintain_history;

    gboolean print_version;

    /* command list: (key)name -> (value)Command  */
    GHashTable* commands;
    /* variables: (key)name -> (value)uzbl_cmdprop */
    GHashTable* proto_var;
} Behaviour;


/* Static information */
typedef struct {
    int     webkit_major;
    int     webkit_minor;
    int     webkit_micro;
    int     webkit2;
    gchar*  arch;
    gchar*  commit;

    pid_t   pid;
    gchar*  pid_str;
} Info;


/* Main uzbl data structure */
typedef struct {
    GUI           gui;
    State         state;
    Network       net;
    Behaviour     behave;
    Communication comm;
    Info          info;
} UzblCore;

extern UzblCore uzbl; /* Main Uzbl object */


/* Functions */
void        clean_up(void);

/* Configuration variables */
gboolean    valid_name(const gchar* name);

/* Running commands */
gchar*      expand(const char* s, guint recurse);

/* Initialization functions */
void        initialize(int argc, char *argv[]);
void        settings_init();

/* Window */
void        retrieve_geometry();


#endif
/* vi: set et ts=4: */
