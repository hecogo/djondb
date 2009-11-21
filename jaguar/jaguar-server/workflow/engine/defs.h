#ifndef ENGINE_DEFS_H_INCLUDED
#define ENGINE_DEFS_H_INCLUDED

enum InstanceStatus
{
    RUNNING,
    CLOSED,
    CANCELLED
};

enum TokenStatus {
    NONE,
    STARTED,
    USER,
    POSTUSER,
    ENDED
};

#endif // ENGINE_DEFS_H_INCLUDED
