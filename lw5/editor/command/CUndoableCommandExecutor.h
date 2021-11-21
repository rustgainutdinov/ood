//
// Created by rustam.gainutdinov on 21.11.2021.
//

#ifndef OOD_CUNDOABLECOMMANDEXECUTOR_H
#define OOD_CUNDOABLECOMMANDEXECUTOR_H


#include "IUndoableCommandExecutor.h"
#include "vector"

class CUndoableCommandExecutor : public IUndoableCommandExecutor
{
public:
    void Add(std::shared_ptr<ICommand> command) override;

    void Undo() override;

    void Redo() override;

private:
    std::vector<std::shared_ptr<ICommand>> m_commands{};
    size_t m_currentCommandIndex = -1;
};


#endif //OOD_CUNDOABLECOMMANDEXECUTOR_H
