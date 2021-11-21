//
// Created by rustam.gainutdinov on 21.11.2021.
//

#ifndef OOD_ICOMMAND_H
#define OOD_ICOMMAND_H

class ICommand
{
public:
    virtual ~ICommand() = default;

    virtual void Execute() = 0;

    virtual void CancelExecution() = 0;
};

#endif //OOD_ICOMMAND_H
