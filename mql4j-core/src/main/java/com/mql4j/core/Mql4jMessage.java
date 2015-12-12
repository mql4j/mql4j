package com.mql4j.core;

import com.fasterxml.jackson.annotation.JsonSetter;

public class Mql4jMessage {
	private Mql4jCommand command;

	@JsonSetter("command")
	public void setCommand(String command) {
		this.command = Mql4jCommand.valueOf(command);
	}

	public Mql4jCommand getCommand() {
		return command;
	}
}
