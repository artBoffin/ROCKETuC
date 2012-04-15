/* 
 * This file is part of the ROCKETuC firmware project
 *
 * Copyright (C) 2011 Stefan Wendler <sw@kaltpost.de>
 *
 * The ROCKETuC firmware is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * ROCKETuC firmware is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with the ROCKETuC firmware; if not, write to the Free
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 * 02111-1307 USA.  
 */

#include "serial_rb.h"

unsigned short serial_rb_free(serial_rb *rb)
{
    return (rb->elements - rb->entries);
}

int serial_rb_full(serial_rb *rb)
{
    return (rb->elements == rb->entries);
}

int serial_rb_empty(serial_rb *rb)
{
    return (rb->entries == 0);
}

void serial_rb_init(serial_rb *rb, SERIAL_RB_Q *buffer, unsigned short elements)
{
    rb->buffer      = buffer;
    rb->read        = &(rb->buffer[0]);
    rb->write       = &(rb->buffer[0]);
    rb->elements    = elements;
    rb->entries     = 0;
}

void serial_rb_write(serial_rb *rb, SERIAL_RB_Q element)
{
  rb->entries++;

  if (rb->write > &(rb->buffer[rb->elements - 1])) {
      rb->write = &(rb->buffer[0]);
  }

  *(rb->write++) = element;
}

SERIAL_RB_Q serial_rb_read(serial_rb *rb)
{
  rb->entries--;

  if (rb->read > &(rb->buffer[rb->elements - 1])) {
      rb->read = &(rb->buffer[0]);
  }

  return *(rb->read++);
}
