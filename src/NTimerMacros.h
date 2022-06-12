#define INVALID_EVENT(event) (event.time <= NULL || event.id == NULL) ? true : false
#define INVALID_ELAPSED_EVENT(elapsedEvent) (elapsedEvent.signalTime == 0 || elapsedEvent.pEventSettings == 0) ? true : false
#define ELAPSEDEVENT_FUNCTION(name, args_name) void name(ElapsedEvent args_name)