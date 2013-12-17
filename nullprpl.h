#include "network.h"
#include "eventloop.h"
#include "udp.h"


#define AUTH_SEND_PORT   8888
#define AUTH_LISTEN_PORT 8888

#define BUFFER_SIZE      96
#define PRPL_TAG         "nullprpl"

#define nullprpl_debug_info(tag, format, ...) fprintf(stdout, "%s:", tag);\
                                              fprintf(stdout, format,## __VA_ARGS__)

#define nullprpl_debug_error(tag, format, ...) fprintf(stderr, "%s:", tag);\
                                               fprintf(stderr, format,## __VA_ARGS__)

#define nullprpl_debug_trace(tag, format, ...) fprintf(stdout, "%s:", tag);\
                                               fprintf(stdout, format,## __VA_ARGS__)
typedef struct _SocketData {
    UdpSocket *udp_send_sock;
    int udp_listenfd;
    PurpleNetworkListenData *udp_listen_data;
    guint udp_input_read;
}SocketData;

static void process (PurpleConnection *gc, json_val_t *val);
static void process_auth (PurpleConnection *gc, json_val_t *val);
static void process_noti (PurpleConnection *gc, json_val_t *val);
static void process_msg (PurpleConnection *gc, json_val_t *val);
static void input_cb (gpointer data, gint source, PurpleInputCondition cond);