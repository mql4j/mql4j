package com.mql4j.core.exception;

@SuppressWarnings("serial")
public class Mql4jException extends Exception {
	public Mql4jException(Throwable cause) {
		super(cause);
	}

	public Mql4jException(String msg) {
		super(msg);
	}
}
