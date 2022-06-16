#define NTIMER_MAJOR_VERSION 2
#define NTIMER_MINOR_VERSION 0
#define NTIMER_PATCH_VERSION 0

#define INVALID_EVENT(event) (event.time <= NULL || event.id == NULL) ? true : false
#define INVALID_ELAPSED_EVENT(elapsedEvent) (elapsedEvent.signalTime == 0 || elapsedEvent.pEventSettings == 0) ? true : false
#define NEW_ELAPSEDEVENT(name) void name(ElapsedEvent)
#define ELAPSEDEVENT_FUNCTION(name, args_name) void name(ElapsedEvent args_name)

#define MAX_TIMER_EVENTS BYTE_MAX
#define CALL 1

#define KEEP_ITERATION_COUNT 0
#define RESET_ITERATION_COUNT 1

#define FORCE_CALL 1

#ifdef NPush_h
#warning Move NPush.h include BELOW NTimer.h for optimization.
#pragma message "Move NPush.h include BELOW NTimer.h for optimization."
#endif

#ifndef LIB_LOOP_INCLUDE
#define LIB_LOOP_INCLUDE
#endif

#ifndef MAX_INSTANCES
#define MAX_INSTANCES 1
#endif

#ifndef UC_UPTIME_NAME
#define UC_UPTIME_NAME runtime
#endif

#ifdef MAX_NTIMEREVENTS
#if MAX_NTIMEREVENTS > 254
#define MAX_NTIMEREVENTS 254
#endif
#else
#define MAX_NTIMEREVENTS 254
#endif

#define UNBLOCK_TIMED() runtimeUpdate();