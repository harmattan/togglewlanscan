/**********************************************************************
 * Copyright 2012 Arto Jalkanen
 *
 * This file is part of ToggleWlanScan.
 *
 * ToggleWlanScan is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ToggleWlanScan is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ToggleWlanScan.  If not, see <http://www.gnu.org/licenses/>
**/
#ifndef TOGGLEWLANSCAN_H
#define TOGGLEWLANSCAN_H

#include <QString>

#define DEFAULT_WLAN_SCAN_INTERVAL 300

class ToggleWlanScan
{    
    void _setScanInterval(int scanIntervalSecs);
    void _showNotification(const QString &message);
    void _replaceDesktopFile(const QString &source);
public:
    ToggleWlanScan();

    void toggle();

    bool isOn() const;
    void setOn(int scanIntervalSecs = DEFAULT_WLAN_SCAN_INTERVAL);
    void setOff();
};

#endif // TOGGLEWLANSCAN_H
