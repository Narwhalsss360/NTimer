#define INVALID_EVENT(event) (event.time <= NULL || event.id == NULL) ? true : false
#define INVALID_ELAPSED_EVENT(elapsedEvent) (elapsedEvent.signalTime == 0 || elapsedEvent.pEventSettings == 0) ? true : false
#define ELAPSEDEVENT_FUNCTION(name, args_name) void name(ElapsedEvent args_name)

#define MAX_TIMER_EVENTS BYTE_MAX
#define CALL 1
#define KEEP_ITERATION_COUNT 0