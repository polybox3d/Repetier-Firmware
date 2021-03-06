/*
    This file is part of Polybox.

    Repetier-Firmware is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Repetier-Firmware is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Repetier-Firmware.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef __COLOR_H__
#define __COLOR_H__

/**
 * Struct. for LED color (rgba).
 * 
 * **/
typedef struct Color {
    uint8_t r; // Red       0-255
    uint8_t g; // Green     0-255
    uint8_t b; // Blu       0-255
    uint8_t i; // intensity 0-255
} Color;


#endif // __COLOR_H__
