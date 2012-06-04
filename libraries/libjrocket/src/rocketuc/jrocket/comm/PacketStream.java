/* 
 * This file is part of the JRocket Library project
 *
 * Copyright (C) 2012 Stefan Wendler <sw@kaltpost.de>
 *
 * The JRocket Library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * JRocket Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with the JRocket firmware; if not, write to the Free
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 * 02111-1307 USA.  
 */

package rocketuc.jrocket.comm;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import rocketuc.jrocket.util.RingBuffer;

public class PacketStream {
	
	protected static final int RING_BUFFER_SIZE = 4;
	
	private ReaderThread reader;
	private WriterThread writer;
			
	private static class ReaderThread extends Thread {
	
		private class HandlerThread extends Thread {

			private Packet pkt;
			
			public HandlerThread(Packet pkt) {
				super();
				
				this.pkt = pkt;
			}

			@Override
			public void run() {
				packetEventHandler.handleEvent(pkt);
			}
		}
		
		private PacketEventHandler packetEventHandler = null;
		private boolean handleAllAsEvent = false;
		private InputStream stream;
		private RingBuffer<Packet> buf;
		
		public ReaderThread(InputStream in) {
			this.stream = in;
			this.buf 	= new RingBuffer<Packet>(RING_BUFFER_SIZE);
		}
		
		public void setEventHandler(PacketEventHandler handler, boolean handleAllAsEvent) {
			this.packetEventHandler = handler;
			this.handleAllAsEvent   = handleAllAsEvent;
		}

		public void removeEventHandler() {
			this.packetEventHandler = null;
		}
		
		public Packet get() throws InterruptedException {
			return buf.remove();
		}
		
		public void run() {
			
			Packet pkt = new Packet();
			
			while(!interrupted()) {
				try {
					if(stream.available() == 0) {
						continue;
					}
			
					byte b = (byte)stream.read();
										
					pkt.addByte(b);
					
					if(pkt.isComplete()) {
						if(packetEventHandler != null && 
						  (handleAllAsEvent || pkt.getStart() == Packet.PACKET_START_INBEV)) {
							HandlerThread t = new HandlerThread(pkt);
							t.run();
						}
						else {
							buf.add(pkt);
						}
						pkt = new Packet();
					}
				} catch (IOException e) {
					e.printStackTrace();
				} catch (PacketException e) {
					e.printStackTrace();
				} catch (InterruptedException e) {
					break;
				}
			}
		}
	}

	private static class WriterThread extends Thread {
		
		private OutputStream stream;	
		private RingBuffer<Packet>	buf;

		public WriterThread(OutputStream out) {
			this.stream = out;
			this.buf 	= new RingBuffer<Packet>(RING_BUFFER_SIZE);;
		}

		public void put(Packet pkt) throws InterruptedException {
			buf.add(pkt);
		}

		public void run() {
			while (!interrupted()) {
				try {
					
					if (buf.isEmpty()) {
						continue;
					}

					Packet pkt = buf.remove();

					for (byte b : pkt.toByteArray()) {
						stream.write(b);
					}
				} catch (PacketException e) {
					e.printStackTrace();
				} catch (IOException e) {
					e.printStackTrace();
				} catch (InterruptedException e) {
					break;
				}
			}
		}
	}

	public PacketStream() {
		super();
	}

	public PacketStream(InputStream in, OutputStream out) {
		super();

		init(in, out);
	}

	public void init(InputStream in, OutputStream out) {
		reader = new ReaderThread(in);
		writer = new WriterThread(out);
	}
	
	public void setEventHandler(PacketEventHandler handler, boolean handleAllAsEvent) {
		if(reader != null) {
			reader.setEventHandler(handler, handleAllAsEvent);
		}
	}

	public void removeEventHandler() {
		if(reader != null) {
			reader.removeEventHandler();
		}		
	}

	public void start() throws Exception {
		reader.start();
		writer.start();
	}
	
	public void stop() throws Exception {
		if(reader != null && reader.isAlive()) {
			reader.interrupt();
			reader.join();
		}		
		if(writer != null && writer.isAlive()) {
			writer.interrupt();
			writer.join();
		}				
	}	
	
	public synchronized void send(Packet pkt) throws InterruptedException {
		if(writer != null && writer.isAlive()) {
			writer.put(pkt);
		}
	}

	public synchronized Packet receive() throws InterruptedException {
		if(reader != null && reader.isAlive()) {
			return reader.get();
		}
		
		return null;
	}
	
	public synchronized Packet xfer(Packet pkt) throws InterruptedException {
		send(pkt);
		return receive();
	}
}
