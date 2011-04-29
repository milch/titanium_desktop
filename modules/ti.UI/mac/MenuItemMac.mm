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

#include "../MenuItem.h"

#import <AppKit/AppKit.h>

#import "KMethodActionTarget.h"
#include "UIMac.h"
#include "../Menu.h"

namespace Titanium {

void MenuItem::setLabel(const std::string& label)
{
    NSString* title = [NSString stringWithUTF8String:label.c_str()];
    [m_menuItem setTitle:title];

    NSMenu* submenu = [m_menuItem submenu];
    if (submenu)
        [submenu setTitle:title];
}

std::string MenuItem::getLabel() const
{
    NSString* title = [m_menuItem title];
    return [title UTF8String];
}

void MenuItem::setIcon(const std::string& iconURL)
{
    NSImage* iconImage = UIMac::MakeImage(iconURL);
    [m_menuItem setImage:iconImage];
    [iconImage release];
    m_iconURL = iconURL;
}

bool MenuItem::getState() const
{
    return [m_menuItem state];
}

void MenuItem::setState(bool state)
{
    NSInteger itemState = state ? NSOnState : NSOffState;
    [m_menuItem setState:itemState];
}

bool MenuItem::isSeparator() const
{
    return [m_menuItem isSeparatorItem];
}

bool MenuItem::isCheck() const
{
    return m_checkItem;
}

void MenuItem::setEnabled(bool enabled)
{
    [m_menuItem setEnabled:enabled];
}

bool MenuItem::isEnabled() const
{
    return [m_menuItem isEnabled];
}

void MenuItem::setSubmenu(AutoPtr<Menu> submenu)
{
    NSMenu* menu = submenu->m_menu;
    [m_menuItem setSubmenu:menu];
}

AutoPtr<Menu> MenuItem::getSubmenu() const
{
    NSMenu* menu = [m_menuItem submenu];
    return new Menu(menu);
}

void MenuItem::addItem(const MenuItem& item)
{
    NSMenu* submenu = [m_menuItem submenu];
    if (submenu == nil)
        throw ValueException::FromString("Menu item has no submenu");

    [submenu addItem:item.m_menuItem];
}

void MenuItem::setActivationCallback(KMethodRef callback)
{
    KMethodActionTarget* target;
    target = [[KMethodActionTarget alloc] initWithCallback:callback];
    [m_menuItem setTarget:target];
    [m_menuItem setAction:@selector(activate:)];
}

void MenuItem::createPlatformMenuItem(MenuItemType type, const std::string& label)
{
    NSString* title;

    switch (type) {
    case CHECK:
        m_checkItem = true;
    case NORMAL:
        title = [NSString stringWithUTF8String:label.c_str()];
        m_menuItem = [[NSMenuItem alloc] initWithTitle:title
                                         action:@selector(activate:)
                                         keyEquivalent:@""];
        break;
    case SEPARATOR:
        m_menuItem = [NSMenuItem separatorItem];
        break;
    }
}

void MenuItem::releasePlatformMenuItem()
{
    [m_menuItem release];
}

} // namespace Titanium

