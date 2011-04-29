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

#ifndef MenuItem_h
#define MenuItem_h

#include <kroll/kroll.h>

#ifdef OS_OSX
@class NSMenuItem;
typedef NSMenuItem PlatformMenuItem;
#endif

namespace Titanium {

class Menu;

class MenuItem : public KEventObject {
public:
    enum MenuItemType {
        NORMAL,
        SEPARATOR,
        CHECK
    };

    MenuItem(MenuItemType type, const std::string& label="");
    MenuItem(PlatformMenuItem* item);
    ~MenuItem();

    void setLabel(const string& label);
    std::string getLabel() const;
    void setIcon(const string& iconURL);
    std::string getIcon() const;
    bool getState() const;
    void setState(bool state);
    bool isSeparator() const;
    bool isCheck() const;
    void setEnabled(bool enabled);
    bool isEnabled() const;
    void setSubmenu(AutoPtr<Menu> submenu);
    AutoPtr<Menu> getSubmenu() const;
    void addItem(const MenuItem& item);

    void setActivationCallback(KMethodRef callback);

private:
    void initBinding();
    void _isSeparator(const ValueList& args, KValueRef result);
    void _isCheck(const ValueList& args, KValueRef result);
    void _setLabel(const ValueList& args, KValueRef result);
    void _getLabel(const ValueList& args, KValueRef result);
    void _setIcon(const ValueList& args, KValueRef result);
    void _getIcon(const ValueList& args, KValueRef result);
    void _setState(const ValueList& args, KValueRef result);
    void _getState(const ValueList& args, KValueRef result);
    void _setAutoCheck(const ValueList& args, KValueRef result);
    void _isAutoCheck(const ValueList& args, KValueRef result);
    void _setSubmenu(const ValueList& args, KValueRef result);
    void _getSubmenu(const ValueList& args, KValueRef result);
    void _enable(const ValueList& args, KValueRef result);
    void _disable(const ValueList& args, KValueRef result);
    void _isEnabled(const ValueList& args, KValueRef result);
    void _addItem(const ValueList& args, KValueRef result);
    void _addSeparatorItem(const ValueList& args, KValueRef result);
    void _addCheckItem(const ValueList& args, KValueRef result);

    void createPlatformMenuItem(MenuItemType type, const std::string& label);
    void releasePlatformMenuItem();

    PlatformMenuItem* m_menuItem;
    bool m_checkItem;
    std::string m_iconURL;
    KMethodRef m_activationCallback;

    friend class Menu;
};

} // namespace Titanium

#endif
