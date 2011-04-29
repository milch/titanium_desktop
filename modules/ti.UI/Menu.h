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

#ifndef Menu_h
#define Menu_h

#include <kroll/kroll.h>

#ifdef OS_OSX
@class NSMenu;
typedef NSMenu PlatformMenu;
#endif

namespace Titanium {

class MenuItem;

class Menu : public KAccessorObject {
public:
    Menu();
    Menu(PlatformMenu* menu);
    ~Menu();

    void appendItem(const MenuItem& item);
    AutoPtr<MenuItem> getItemAt(unsigned int index);
    void insertItemAt(const MenuItem& item, unsigned int index);
    void removeItemAt(unsigned int index);
    int itemCount() const;
    void clear();

private:
    void initBinding();
    void _appendItem(const ValueList& args, KValueRef result);
    void _getItemAt(const ValueList& args, KValueRef result);
    void _insertItemAt(const ValueList& args, KValueRef result);
    void _removeItemAt(const ValueList& args, KValueRef result);
    void _getLength(const ValueList& args, KValueRef result);
    void _clear(const ValueList& args, KValueRef result);
    void _addItem(const ValueList& args, KValueRef result);
    void _addSeparatorItem(const ValueList& args, KValueRef result);
    void _addCheckItem(const ValueList& args, KValueRef result);

    void createPlatformMenu();
    void releasePlatformMenu();

    PlatformMenu* m_menu;

    friend class MenuItem;
};

} // namespace Titanium

#endif
