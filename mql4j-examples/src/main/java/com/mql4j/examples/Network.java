package com.mql4j.examples;

import java.io.IOException;
import java.net.InetAddress;
import java.net.UnknownHostException;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class Network {
	private final static int TIMEOUT_MILLIS = 3000;
	private final static Logger log = LoggerFactory.getLogger(Network.class);

	public static String ping(final String host) throws IOException {
		final InetAddress address = InetAddress.getByName(host);
		final String name = address.getHostName();
		final String addr = address.getHostAddress();
		String out = String.format("PING %s (%s)\n", name, addr);
		for(int i = 0; i < 4; i++) {
			log.info(String.format("Ping %s (%s) #%d", name, addr, i));
			String result = "";
			if(address.isReachable(TIMEOUT_MILLIS)) {
				result = String.format("Response retrieved from %s: icmp_seq %d", i, address.getHostAddress());
			} else {
				result = String.format("Request timeout for icmp_seq %d", i);
			}
			out += result + "\n";
			log.info(result);
		}
		return out;
	}

	public static String host(final String host) throws UnknownHostException {
		final InetAddress address = InetAddress.getByName(host);
		String out = "";
		if(host.matches("^(?:[0-9]{1,3}\\.){3}[0-9]{1,3}$")) {
			out = String.format("IP %s => Hostname %s", address.getHostAddress(), address.getHostName());
		} else {
			out = String.format("Hostname %s => IP %s", address.getHostName(), address.getHostAddress());
		}
		log.info(out);
		return out;
	}
}
