package com.mql4j.activemq;

import javax.jms.Connection;
import javax.jms.ConnectionFactory;
import javax.jms.JMSException;
import javax.jms.MessageConsumer;
import javax.jms.MessageProducer;
import javax.jms.Queue;
import javax.jms.Session;
import javax.jms.Topic;

import org.apache.activemq.ActiveMQConnectionFactory;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.mql4j.core.exception.Mql4jException;

public class ActivemqClient {
	private final static Logger log = LoggerFactory.getLogger(ActivemqClient.class);
	private Connection connection;
	private Session session;
	private boolean connected;
	private TransactionType transactions;

	public ActivemqClient() {
		connected = false;
		transactions = TransactionType.NO_TRANSACTIONS;
		connection = null;
		session = null;
	}

	public void connect(final String brokerURI) throws Mql4jException, JMSException {
		if(connected) {
			throw new Mql4jException("Failed to connect to broker: Already connected");
		}
		log.trace(String.format("Connecting broker '%s'", brokerURI));
		ConnectionFactory connectionFactory = new ActiveMQConnectionFactory(brokerURI);
		connection = connectionFactory.createConnection();
		connection.start();
		switch(transactions) {
		case TRANSACTIONS: 
			session = connection.createSession(true, Session.CLIENT_ACKNOWLEDGE);
			break;
		case NO_TRANSACTIONS:
			session = connection.createSession(false, Session.AUTO_ACKNOWLEDGE);
			break;
		}
		log.debug(String.format("Connected broker '%s'", brokerURI));
		connected = true;
	}

	public void close() {
		try {
			if(session != null) {
				session.close();
			}
		} catch (JMSException e) {
			log.warn("Failed to close session: " + e.getMessage());
		}
		try {
			if(connection != null) {
				connection.close();
			}
		} catch (JMSException e) {
			log.warn("Failed to close connection: " + e.getMessage());
		}
		session = null;
		connection = null;
		connected = false;
	}

	public void enableTransactions() {
		transactions = TransactionType.TRANSACTIONS;
	}

	public MessageProducer getProducer(final String name, DestinationType type) throws Mql4jException, JMSException {
		if(!connected || connection == null|| session == null) {
			throw new Mql4jException("Not connected");
		}
		switch(type) {
		case QUEUE:
			Queue q = session.createQueue(name);
			return session.createProducer(q);
		case TOPIC:
			Topic t = session.createTopic(name);
			return session.createProducer(t);
		default:
			throw new Mql4jException("Invalid type");
		}
	}

	public MessageConsumer getConsumer(final String name, DestinationType type) throws Mql4jException, JMSException {
		if(!connected || connection == null|| session == null) {
			throw new Mql4jException("Not connected");
		}
		switch(type) {
		case QUEUE:
			Queue q = session.createQueue(name);
			return session.createConsumer(q);
		case TOPIC:
			Topic t = session.createTopic(name);
			return session.createConsumer(t);
		default:
			throw new Mql4jException("Invalid type");
		}
	}

	/*
	public void writeMessage(final String message) {
		connect();
		try {
			Message msg = session.createTextMessage(message);
			producer.send(msg);
		} catch (JMSException e) {
			e.printStackTrace();
		}
	}
	*/
}
