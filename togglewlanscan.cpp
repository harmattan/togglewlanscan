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
#include "togglewlanscan.h"

#include <QObject>
#include <QVariant>
#include <QProcess>
#include <gconfitem.h>
#include <MNotification>

#define GCONF_WIFI_SEARCH_INTERVAL "/system/osso/connectivity/network_type/search_interval"

#define WLAN_SCAN_OFF_DESKTOP_SOURCE "/opt/togglewlanscan/data/togglewlanscan_off_harmattan.desktop"
#define WLAN_SCAN_ON_DESKTOP_SOURCE "/opt/togglewlanscan/data/togglewlanscan_on_harmattan.desktop"
#define DESKTOP_DESTINATION "/usr/share/applications/togglewlanscan_harmattan.desktop"

ToggleWlanScan::ToggleWlanScan()
{
}

void
ToggleWlanScan::toggle() {
    if (isOn()) {
        setOff();
    } else {
        setOn();
    }
}

void
ToggleWlanScan::_setScanInterval(int scanIntervalSecs) {
    qDebug("ToggleWlanScan::_setScanInterval %d", scanIntervalSecs);
    GConfItem gconfItem(GCONF_WIFI_SEARCH_INTERVAL);
    gconfItem.set(scanIntervalSecs);
}

void
ToggleWlanScan::_showNotification(const QString &message) {
    qDebug("ToggleWlanScan::_showNotification publishing notification '%s'", qPrintable(message));
    MNotification notification(MNotification::DeviceEvent);
    notification.setImage("/usr/share/icons/hicolor/80x80/apps/togglewscan80.png");
    notification.setBody(message);
    notification.publish();

}

void
ToggleWlanScan::_replaceDesktopFile(const QString &source) {
    // QFile::copy can not be used for overwritting files, so as an ugly workaround just do a copy with cp
    // This is actually double ugly workaround. Busybox's cp does not overwrite the destination file,
    // maybe because parent directory does not have write permissions. But overwriting with cat works.
    QString cmdline = QString("/bin/sh -c \"cat %1 >%2\"").arg(qPrintable(source), DESKTOP_DESTINATION);
    int ret_value = QProcess::execute(cmdline);
    if (ret_value != 0) {
        qDebug("ToggleWlanScan: error replacing desktop file: %s: %d", qPrintable(cmdline), ret_value);
    }
}

bool
ToggleWlanScan::isOn() const {
    GConfItem gconfItem(GCONF_WIFI_SEARCH_INTERVAL);
    QVariant scanIntervalVariant = gconfItem.value();
    int scanInterval = scanIntervalVariant.toInt();
    qDebug("ToggleWlanScan::isOn(): scanInterval %d", scanInterval);
    return scanInterval <= 0 ? false : true;
}

void
ToggleWlanScan::setOn(int scanIntervalSecs) {
    _setScanInterval(scanIntervalSecs);
    _replaceDesktopFile(WLAN_SCAN_OFF_DESKTOP_SOURCE);
    _showNotification("WLAN scanning turned on");
}

void
ToggleWlanScan::setOff() {
    _setScanInterval(0);
    _replaceDesktopFile(WLAN_SCAN_ON_DESKTOP_SOURCE);
    _showNotification("WLAN scanning turned off");
}
