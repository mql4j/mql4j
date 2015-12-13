package com.mql4j.core.tools;

import java.util.Map.Entry;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class ThreadTools {
	private static final Logger log = LoggerFactory.getLogger(ThreadTools.class);

	public static void stackTrace() {
		String msg = "Threads:\n";
		for (Entry<Thread, StackTraceElement[]> entry : Thread.getAllStackTraces().entrySet()) {
			msg += String.format("  Thread       '%-50s' (%s)\n", entry.getKey().getName(),
					entry.getKey().getClass().toString());
			msg += String.format("    Daemon   = %s\n", entry.getKey().isDaemon() ? "true" : "false");
			msg += String.format("    Alive    = %s\n", entry.getKey().isAlive() ? "true" : "false");
			msg += String.format("    Interptd = %s\n", entry.getKey().isInterrupted() ? "true" : "false");
			msg += "    Stack\n";
			for (int i = 0; i < entry.getValue().length; i++) {
				msg += String.format("      - %-50s %s\n", entry.getValue()[i].getClassName(),
						entry.getValue()[i].getMethodName());
			}
			msg += "\n";
		}
		log.info(msg);
	}
}
