/* 
 * This file is part of the ROCKETuC firmware project
 *
 * Copyright (C) 2012 Stefan Wendler <sw@kaltpost.de>
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

/**
 * File: RingBuffer.java
 * Author: Keith Schwarz (htiek@cs.stanford.edu)
 *
 * An implementation of a synchronized queue backed by a ring buffer.  This
 * functionality and implementation is similar to the ArrayBlockingQueue class,
 * but I thought that I'd implement my own version to get a better feel for how
 * it works.
 *
 * A ring buffer is a space-efficient, locality-friendly implementation of a 
 * FIFO queue.  It is implemented as a fixed-sized array that is treated as
 * though it wraps around like a ring; it has no well-defined start or end
 * point.  This array stores two pointers, a read pointer and a write pointer,
 * delineating where the next insert should take place and from where the next
 * element should be dequeued.  For example:
 *
 *                       [2] [3] [ ] [ ] [ ] [ ] [0] [1]
 *                                ^               ^
 *                                |               |
 *                              write            read
 *
 * When using a ring buffer, one must be careful not to let the read and write
 * pointers cross one another.  If this happens, future write operations will
 * start overwriting old elements that have not yet been consumed.  For this
 * reason, most ring buffers adopt one of two strategies.  First, the ring
 * buffer can increase its size whenever it runs out of room.  This approach
 * allows the buffer to grow arbitrarily large if need be.  The second option,
 * and the one used in this implementation, is simply to block on a read or
 * write when data is not available.  This allows the ring buffer to implement
 * the producer/consumer pattern fairly easily; any number of threads can begin
 * creating data while some number of threads consume it, and at no time are
 * too many elements kept in memory waiting to be read.
 */

package rocketuc.jrocket.util;

public final class RingBuffer<T> {
	/** 
	 * The actual ring buffer. 
	 */
	private final T[] elements;

	/** 
	 * The write pointer
	 */
	private int offset = 0;

	/**
	 * The read pointer.
	 */
	private int unconsumedElements = 0;

	/**
	 * Constructs a new RingBuffer with the specified capacity, which must be
	 * positive.
	 * 
	 * @param size
	 *            The capacity of the new ring buffer.
	 * @throws IllegalArgumentException
	 *             If the capacity is negative.
	 */
	@SuppressWarnings("unchecked")
	public RingBuffer(int size) {
		if (size <= 0)
			throw new IllegalArgumentException(
					"RingBuffer capacity must be positive.");

		elements = (T[]) new Object[size];
	}

	/**
	 * Appends an element to the ring buffer, blocking until space becomes
	 * available.
	 * 
	 * @param elem
	 *            The element to add to the ring buffer.
	 * @throws InterruptedException
	 *             If the thread is interrupted before the insertion completes.
	 */
	public synchronized void add(T elem) throws InterruptedException {

		while (unconsumedElements == elements.length) {
			wait();
		}

		elements[offset] = elem;
		offset = (offset + 1) % elements.length;

		unconsumedElements++;
		notifyAll();
	}

	/**
	 * Returns the maximum capacity of the ring buffer.
	 * 
	 * @return The maximum capacity of the ring buffer.
	 */
	public int capacity() {
		return elements.length;
	}

	/**
	 * Observes, but does not dequeue, the next available element, blocking
	 * until data becomes available.
	 * 
	 * @return The next available element.
	 * @throws InterruptedException
	 *             If the caller is interrupted before data becomes available.
	 */
	public synchronized T peek() throws InterruptedException {
		while (unconsumedElements == 0) {
			wait();
		}

		return elements[(offset + (capacity() - unconsumedElements))
				% capacity()];
	}

	/**
	 * Removes and returns the next available element, blocking until data
	 * becomes available.
	 * 
	 * @return The next available element
	 * @throws InterruptedException
	 *             If the caller is interrupted before data becomes available.
	 */
	public synchronized T remove() throws InterruptedException {
		T result = peek();

		unconsumedElements--;
		notifyAll();

		return result;
	}

	/**
	 * Returns the number of elements that are currently being stored in the
	 * ring buffer.
	 * 
	 * @return The number of elements currently stored in the ring buffer.
	 */
	public synchronized int size() {

		return unconsumedElements;
	}

	/**
	 * Returns whether the ring buffer is empty.
	 * 
	 * @return Whether the ring buffer is empty.
	 */
	public synchronized boolean isEmpty() {

		return size() == 0;
	}
}
