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

#include "Menu.h"

#include "MenuItem.h"

namespace Titanium {

Menu::Menu()
    : KAccessorObject("UI.Menu")
{
    createPlatformMenu();
    initBinding();
}

Menu::Menu(PlatformMenu* menu)
    : KAccessorObject("UI.Menu")
    , m_menu(menu)
{
    initBinding();
}

Menu::~Menu()
{
    releasePlatformMenu();
}

void Menu::initBinding()
{
    SetMethod("appendItem", &Menu::_appendItem);
    SetMethod("getItemAt", &Menu::_getItemAt);
    SetMethod("insertItemAt", &Menu::_insertItemAt);
    SetMethod("removeItemAt", &Menu::_removeItemAt);
    SetMethod("getLength", &Menu::_getLength);
    SetMethod("clear", &Menu::_clear);
    SetMethod("addItem", &Menu::_addItem);
    SetMethod("addSeparatorItem", &Menu::_addSeparatorItem);
    SetMethod("addCheckItem", &Menu::_addCheckItem);
}

void Menu::_appendItem(const ValueList& args, KValueRef result)
{
    args.VerifyException("appendItem", "o");
    KObjectRef o = args.GetObject(0);

    AutoPtr<MenuItem> item = o.cast<MenuItem>();
    if (!item.isNull())
        appendItem(*item);
}

void Menu::_getItemAt(const ValueList& args, KValueRef result)
{
    args.VerifyException("getItemAt", "i");
    AutoPtr<MenuItem> item = getItemAt(args.GetInt(0));
    result->SetObject(item);
}

void Menu::_insertItemAt(const ValueList& args, KValueRef result)
{
    args.VerifyException("insertItemAt", "o,i");
    KObjectRef o = args.GetObject(0);
    AutoPtr<MenuItem> item = o.cast<MenuItem>();
    unsigned int index = args.GetInt(1);

    if (!item.isNull())
        insertItemAt(*item, index);
}

void Menu::_removeItemAt(const ValueList& args, KValueRef result)
{
    args.VerifyException("removeItemAt", "i");
    unsigned int index = args.GetInt(0);
    removeItemAt(index);
}

void Menu::_getLength(const ValueList& args, KValueRef result)
{
    result->SetInt(itemCount());
}

void Menu::_clear(const ValueList& args, KValueRef result)
{
    clear();
}

void Menu::_addItem(const ValueList& args, KValueRef result)
{
    args.VerifyException("addItem", "?s m|0 s|0");
    // TODO: implement
}

void Menu::_addSeparatorItem(const ValueList& args, KValueRef result)
{
    // TODO: implement
}

void Menu::_addCheckItem(const ValueList& args, KValueRef result)
{
    // TODO: implement
}

} // namespace Titanium

