#ifndef __U_DISTINGUISH_H__
#define __U_DISTINGUISH_H__

typedef enum {
    STRAIGHT = 0,
    TURN_LEFT,
    TURN_RIGHT,
    CROSSROAD,
    ROUNDABOUT_IN,
    ROUNDABOUT_OUT,
    UNKNOWN
} TrackType;

extern char trace_flag;
void distinguish_path(void);

#endif