//
// Created by rustam.gainutdinov on 21.11.2021.
//

#ifndef OOD_CCOMMANDFACTORY_H
#define OOD_CCOMMANDFACTORY_H


#include "ICommandFactory.h"

class IDocument;

class CCommandFactory : public ICommandFactory
{
public:
    explicit CCommandFactory(std::shared_ptr<IDocument> document);

    std::unique_ptr<ICommand> CreateCommand(std::string description) override;

private:
    std::shared_ptr<IDocument> m_document;
};


#endif //OOD_CCOMMANDFACTORY_H
