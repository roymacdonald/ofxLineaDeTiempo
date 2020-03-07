//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#include "ofx/MUI/MUI.h"
#include "ofx/MUI/Styles.h"


namespace ofx {
namespace MUI {


MUI::MUI(ofAppBaseWindow* window): DOM::Document(window)
{
}


MUI::~MUI()
{
}


std::shared_ptr<Styles> MUI::getDocumentStyles() const
{
    if (_documentStyles == nullptr)
    {
        _documentStyles = std::make_shared<Styles>();
    }

    return _documentStyles;
}


void MUI::setDocumentStyles(std::shared_ptr<Styles> documentStyles)
{
    _documentStyles = documentStyles;
}


} } // namespace ofx::MUI
