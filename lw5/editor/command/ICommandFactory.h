//
// Created by rustam.gainutdinov on 21.11.2021.
//

#ifndef OOD_ICOMMANDFACTORY_H
#define OOD_ICOMMANDFACTORY_H

#import "memory"

class ICommand;

class ICommandFactory
{
public:
    virtual ~ICommandFactory() = default;

    virtual std::unique_ptr<ICommand> CreateCommand(std::string description) = 0;
};

#endif //OOD_ICOMMANDFACTORY_H
