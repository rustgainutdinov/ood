//
// Created by rustam.gainutdinov on 21.11.2021.
//

#ifndef OOD_IUNDOABLECOMMANDEXECUTOR_H
#define OOD_IUNDOABLECOMMANDEXECUTOR_H


#include "memory"
#include "ICommandExecutor.h"

class IUndoableCommandExecutor : public ICommandExecutor
{
public:
    virtual void Undo() = 0;

    virtual void Redo() = 0;

    virtual ~IUndoableCommandExecutor() = default;
};

#endif //OOD_IUNDOABLECOMMANDEXECUTOR_H
