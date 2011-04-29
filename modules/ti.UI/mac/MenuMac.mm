/*
 * Copyright (c) 2011 Appcelerator, Inc. All Rights Reserved.
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

#include "../Menu.h"

#include "../MenuItem.h"

#import <AppKit/AppKit.h>

namespace Titanium {

void Menu::createPlatformMenu()
{
    m_menu = [[NSMenu alloc] initWithTitle:@""];
}

void Menu::releasePlatformMenu()
{
    [m_menu release];
}

void Menu::appendItem(const MenuItem& item)
{
    [m_menu addItem:item.m_menuItem];
}

AutoPtr<MenuItem> Menu::getItemAt(unsigned int index)
{
    NSMenuItem* item;

    @try {
        item = [m_menu itemAtIndex:index];
    }
    @catch (NSException* e) {
        throw ValueException::FromString("Index out of range");
    }

    return new MenuItem(item);
}

void Menu::insertItemAt(const MenuItem& item, unsigned int index)
{
    @try {
        [m_menu insertItem:item.m_menuItem atIndex:index];
    }
    @catch (NSException* e) {
        throw ValueException::FromString("Index out of range");
    }
}

void Menu::removeItemAt(unsigned int index)
{
    @try {
        [m_menu removeItemAtIndex:index];
    }
    @catch (NSException* e) {
        throw ValueException::FromString("Index out of range");
    }
}

int Menu::itemCount() const
{
    return [m_menu numberOfItems];
}

void Menu::clear()
{
    // XXX: in 10.6 we can use removeAllItems instead.
    NSInteger itemCount = [m_menu numberOfItems];
    while (itemCount > 0)
        [m_menu removeItemAtIndex:--itemCount];
}

} // namespace Titanium

