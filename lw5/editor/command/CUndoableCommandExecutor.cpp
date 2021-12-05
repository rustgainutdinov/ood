//
// Created by rustam.gainutdinov on 21.11.2021.
//

#include "CUndoableCommandExecutor.h"
#include "ICommand.h"

using namespace std;

void CUndoableCommandExecutor::Add(unique_ptr<ICommand> command)
{
    if (m_currentCommandIndex + 1 != m_commands.size())
    {
        m_commands.erase(m_commands.begin() + m_currentCommandIndex + 1, m_commands.end());
    }
    command->Execute();
    m_commands.push_back(move(command));
    m_currentCommandIndex = m_commands.size() - 1;
}

void CUndoableCommandExecutor::Undo()
{
    if (m_currentCommandIndex == -1)
    {
        throw invalid_argument("can't undo: commands list is empty");
    }
    m_commands[m_currentCommandIndex]->CancelExecution();
    m_currentCommandIndex--;
}

void CUndoableCommandExecutor::Redo()
{
    if (m_currentCommandIndex + 1 >= m_commands.size())
    {
        throw invalid_argument("can't redo: no cancelled command for redo");
    }
    m_currentCommandIndex++;
    m_commands[m_currentCommandIndex]->Execute();
}

bool CUndoableCommandExecutor::CanUndo()
{
    return m_currentCommandIndex != -1;
}

bool CUndoableCommandExecutor::CanRedo()
{
    return m_currentCommandIndex + 1 < m_commands.size();
}
