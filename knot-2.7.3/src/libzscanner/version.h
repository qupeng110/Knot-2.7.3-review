/*  Copyright (C) 2018 CZ.NIC, z.s.p.o. <knot-dns@labs.nic.cz>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#define ZSCANNER_VERSION_MAJOR 2
#define ZSCANNER_VERSION_MINOR 7
#define ZSCANNER_VERSION_PATCH 0x03

#define ZSCANNER_VERSION_HEX ((ZSCANNER_VERSION_MAJOR << 16) | \
                              (ZSCANNER_VERSION_MINOR <<  8) | \
                              (ZSCANNER_VERSION_PATCH))
