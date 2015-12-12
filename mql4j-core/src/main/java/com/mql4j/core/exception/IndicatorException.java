package com.mql4j.core.exception;

@SuppressWarnings("serial")
public class IndicatorException extends Exception {
	public IndicatorException(Throwable cause) {
		super(cause);
	}

	public IndicatorException(String msg) {
		super(msg);
	}
}
