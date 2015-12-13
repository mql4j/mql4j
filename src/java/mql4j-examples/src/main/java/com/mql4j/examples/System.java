package com.mql4j.examples;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class System {
	private final static Logger log = LoggerFactory.getLogger(System.class);

	public static String exec(final String command) throws IOException {
		log.info("Executing command '" + command + "'");
		Process p = Runtime.getRuntime().exec(command);
		BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
		String out = "";
		String line;
		while ((line = in.readLine()) != null) {
			out += line;
		}
		in.close();
		final String end = String.format("Ended with code %d", p.exitValue());
		out += end;
		log.info(end);
		p.destroy();
		return out;
	}
}
