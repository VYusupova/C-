#ifndef QT_FRONT_H
#define QT_FRONT_H
#include "../../include/library_spec.h"

extern "C" {
typedef void (*UserInputFunc)(UserAction_t, bool);
typedef GameInfo_t (*UpdateCurrentStateFunc)(void);
void startWindows(UserInputFunc userInput,
                  UpdateCurrentStateFunc updateCurrentState);
}

#endif  // QT_FRONT_H