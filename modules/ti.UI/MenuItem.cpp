/*
 * Copyright (c) 2009-2010 Appcelerator, Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "MenuItem.h"

#include "Menu.h"

namespace Titanium {

MenuItem::MenuItem(MenuItemType type, const std::string& label)
    : KEventObject("UI.MenuItem")
{
    createPlatformMenuItem(type, label);
    initBinding();
}

MenuItem::MenuItem(PlatformMenuItem* item)
    : KEventObject("UI.MenuItem")
    , m_menuItem(item)
{
    initBinding();
}

MenuItem::~MenuItem()
{
    releasePlatformMenuItem();
}

std::string MenuItem::getIcon() const
{
    return m_iconURL;
}

void MenuItem::initBinding()
{
    SetMethod("isSeparator", &MenuItem::_isSeparator);
    SetMethod("isCheck", &MenuItem::_isCheck);
    SetMethod("setLabel", &MenuItem::_setLabel);
    SetMethod("getLabel", &MenuItem::_getLabel);
    SetMethod("setSubmenu", &MenuItem::_setSubmenu);
    SetMethod("getSubmenu", &MenuItem::_getSubmenu);
    SetMethod("enable", &MenuItem::_enable);
    SetMethod("disable", &MenuItem::_disable);
    SetMethod("isEnabled", &MenuItem::_isEnabled);
    SetMethod("addItem", &MenuItem::_addItem);
    SetMethod("addSeparatorItem", &MenuItem::_addSeparatorItem);
    SetMethod("addCheckItem", &MenuItem::_addCheckItem);
    SetMethod("setIcon", &MenuItem::_setIcon);
    SetMethod("getIcon", &MenuItem::_getIcon);
    SetMethod("setState", &MenuItem::_setState);
    SetMethod("getState", &MenuItem::_getState);
    SetMethod("setAutoCheck", &MenuItem::_setAutoCheck);
    SetMethod("isAutoCheck", &MenuItem::_isAutoCheck);
}

void MenuItem::_isSeparator(const ValueList& args, KValueRef result)
{
    result->SetBool(isSeparator());
}

void MenuItem::_isCheck(const ValueList& args, KValueRef result)
{
    result->SetBool(isCheck());
}

void MenuItem::_setLabel(const ValueList& args, KValueRef result)
{
    args.VerifyException("setLabel", "s|0");
    string newLabel = args.GetString(0, "");
    setLabel(newLabel);
}

void MenuItem::_getLabel(const ValueList& args, KValueRef result)
{
    string label = getLabel();
    result->SetString(label);
}

void MenuItem::_setIcon(const ValueList& args, KValueRef result)
{
    args.VerifyException("setIcon", "s|0");
    std::string newIcon = args.GetString(0, "");
    setIcon(newIcon);
}

void MenuItem::_getIcon(const ValueList& args, KValueRef result)
{
    std::string iconPath = getIcon();
    result->SetString(iconPath);
}

void MenuItem::_setState(const ValueList& args, KValueRef result)
{
    args.VerifyException("setState", "b");
    setState(args.GetBool(0));
}

void MenuItem::_getState(const ValueList& args, KValueRef result)
{
    result->SetBool(getState());
}

void MenuItem::_setSubmenu(const ValueList& args, KValueRef result)
{
    args.VerifyException("setSubmenu", "o|0");
    AutoPtr<Menu> newSubmenu = NULL;

    if (args.at(0)->IsObject())
    {
        KObjectRef o = args.at(0)->ToObject();
        o = KObject::Unwrap(o);
        newSubmenu = o.cast<Menu>();
    }

    setSubmenu(newSubmenu);
}

void MenuItem::_getSubmenu(const ValueList& args, KValueRef result)
{
    result->SetObject(getSubmenu());
}

void MenuItem::_enable(const ValueList& args, KValueRef result)
{
    setEnabled(true);
}

void MenuItem::_disable(const ValueList& args, KValueRef result)
{
    setEnabled(false);
}

void MenuItem::_setAutoCheck(const ValueList& args, KValueRef result)
{
}

void MenuItem::_isAutoCheck(const ValueList& args, KValueRef result)
{
}

void MenuItem::_isEnabled(const ValueList& args, KValueRef result)
{
    result->SetBool(isEnabled());
}

void MenuItem::_addItem(const ValueList& args, KValueRef result)
{
    args.VerifyException("addItem", "s ?m|0 s|0");
    std::string label = args.GetString(0);

    AutoPtr<MenuItem> menuItem = new MenuItem(MenuItem::NORMAL, label);
    if (args.size() > 1)
        menuItem->setActivationCallback(args.GetMethod(1));

    addItem(*menuItem);
    result->SetObject(menuItem);
}

void MenuItem::_addSeparatorItem(const ValueList& args, KValueRef result)
{
    AutoPtr<MenuItem> menuItem = new MenuItem(MenuItem::SEPARATOR);
    addItem(*menuItem);
    result->SetObject(menuItem);
}

void MenuItem::_addCheckItem(const ValueList& args, KValueRef result)
{
    args.VerifyException("addCheckItem", "s ?m");
    std::string label = args.GetString(0);

    AutoPtr<MenuItem> menuItem = new MenuItem(MenuItem::CHECK, label);
    if (args.size() > 1)
        menuItem->setActivationCallback(args.GetMethod(1));

    addItem(*menuItem);
    result->SetObject(menuItem);
}

} // namespace Titanium

