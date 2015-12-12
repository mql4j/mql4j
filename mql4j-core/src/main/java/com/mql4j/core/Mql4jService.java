package com.mql4j.core;

import java.io.IOException;

import javax.jms.JMSException;
import javax.jms.Message;
import javax.jms.MessageConsumer;
import javax.jms.TextMessage;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.fasterxml.jackson.core.JsonParseException;
import com.fasterxml.jackson.databind.JsonMappingException;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.mql4j.activemq.ActivemqBroker;
import com.mql4j.activemq.ActivemqClient;
import com.mql4j.activemq.DestinationType;
import com.mql4j.core.tools.ThreadTools;

public class Mql4jService implements Runnable {
	private final static long TIMEOUT = 5000;
	private static final String ACTIVEMQ_BROKER_URI = "tcp://localhost:61616";
	private static final String EVENT_QUEUE = "com.mql4j.java.events";
	private final static Logger log = LoggerFactory.getLogger(Mql4jService.class);
	private ActivemqBroker activemq;
	private ActivemqClient event;
	private MessageConsumer eventConsumer;
	private ObjectMapper mapper;
	private boolean run;

	public Mql4jService() {
		run = true;
		activemq = null;
		event = null;
		eventConsumer = null;
		mapper = new ObjectMapper();
	}

	@Override
	public void run() {
		try {
			activemq = new ActivemqBroker(ACTIVEMQ_BROKER_URI);
			activemq.run();
			ActivemqClient event = new ActivemqClient();
			event.connect(ACTIVEMQ_BROKER_URI);
			eventConsumer = event.getConsumer(EVENT_QUEUE, DestinationType.QUEUE);
		} catch (Exception e) {
			log.error("Startup failed: " + e.getMessage());
			close();
			return;
		}
		log.info("Event queue ready");
		while (run) {
			try {
				Message message = eventConsumer.receive(TIMEOUT);
				if (message != null) {
					processMessage(message);
				} else {
					log.trace("No event retrieved");
					continue;
				}
			} catch (JMSException e) {
				log.warn("Failed to retrieve message from queue: " + e.getMessage());
			}
		}
		log.info("Event queue stopped");
		close();
	}

	private void processMessage(final Message message) {
		if (!(message instanceof TextMessage)) {
			log.warn("Retrieved an invalid message " + message.toString());
			return;
		}
		try {
			final String json = ((TextMessage) message).getText();
			Mql4jMessage msgObj = mapper.readValue(json, Mql4jMessage.class);
			processEvent(msgObj);
		} catch (JMSException e) {
			log.warn("Failed to retrieve event message from queue: " + e.getMessage());
		} catch (JsonMappingException e) {
			log.warn("Failed to parse JSON message: " + e.getMessage());
		} catch (JsonParseException e) {
			log.warn("Failed to parse JSON message: " + e.getMessage());
		} catch (IOException e) {
			log.warn("Failed to read message:" + e.getMessage());
		}
	}

	private void processEvent(Mql4jMessage msgObj) {
		log.debug("Event " + msgObj.getCommand().toString());
		switch(msgObj.getCommand()) {
		case PING:
			log.info("Ping");
			break;
		case STACKTRACE:
			ThreadTools.stackTrace();;
			break;
		case SHUTDOWN:
			log.info("Shutdown initialized");
			run = false;
			break;
		default:
			log.error("No event for " + msgObj.getCommand().toString());
			break;
		}
	}

	private void close() {
		if (eventConsumer != null) {
			try {
				eventConsumer.close();
			} catch (JMSException e) {
				log.warn("Failed to close event consumer: " + e.getMessage());
			}
		}
		if (event != null) {
			event.close();
		}
		if (activemq != null) {
			activemq.close();
		}
		run = false;
		activemq = null;
		event = null;
		eventConsumer = null;
	}

	public static void main(String[] args) {
		log.trace("main");
		(new Thread(new Mql4jService())).start();
		log.debug("Thread Mql4jService started");
	}
}
