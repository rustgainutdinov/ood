//
// Created by rustam.gainutdinov on 27.11.2021.
//

#ifndef OOD_ICOMMANDEXECUTOR_H
#define OOD_ICOMMANDEXECUTOR_H


#include "memory"

class ICommand;

class ICommandExecutor
{
public:
    virtual void Add(std::unique_ptr<ICommand> command) = 0;

    virtual ~ICommandExecutor() = default;
};

#endif //OOD_ICOMMANDEXECUTOR_H
