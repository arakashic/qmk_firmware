/* Copyright 2020 QMK Contributors
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include_next "halconf.h"

/* #define HAL_USE_I2C TRUE */
#undef HAL_USE_SPI
#define HAL_USE_SPI TRUE
#undef SPI_USE_WAIT
#define SPI_USE_WAIT TRUE
#undef SPI_SELECT_MODE
#define SPI_SELECT_MODE SPI_SELECT_MODE_PAD

