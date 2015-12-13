package com.mql4j.activemq;

import org.apache.activemq.broker.BrokerService;
import org.apache.activemq.usage.MemoryUsage;
import org.apache.activemq.usage.SystemUsage;
import org.apache.activemq.util.ServiceStopper;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class ActivemqBroker implements Runnable {
	private final static Logger log = LoggerFactory.getLogger(ActivemqBroker.class);
	private String brokerURI;
	private BrokerService broker;
	private SystemUsage usage;

	public ActivemqBroker(final String brokerURI) {
		this.brokerURI = brokerURI;
		this.broker = null;
		this.usage = null;
	}

	@Override
	public void run() {
		try {
			broker = new BrokerService();
			broker.setUseLocalHostBrokerName(true);
			broker.setSystemUsage(getUsageManager());
			broker.setEnableStatistics(false);
			broker.setPersistent(false);
			broker.setStartAsync(false);
			broker.setSystemExitOnShutdown(false);
			broker.setUseShutdownHook(false);
			broker.addConnector(brokerURI);
			broker.start();
			log.debug(String.format("Activemq broker (%s) started", brokerURI));
		} catch (Exception e) {
			log.error("Failed to start Activemq broker: " + e.getMessage());
			e.printStackTrace();
		}
	}

	public void close() {
		try {
			log.trace("Stopping open connections ...");
			broker.stopAllConnectors(new ServiceStopper());
			log.trace("Stopping activemq broker ...");
			broker.stop();
			broker = null;
			log.debug("Activemq broker stopped");
		} catch (Exception e) {
			log.error("Failed to stop activemq broker: " + e.getMessage());
			e.printStackTrace();
		} catch (Throwable e) {
			log.error("Failed to stop activemq broker: " + e.getMessage());
			e.printStackTrace();
		}
	}

	private SystemUsage getUsageManager() {
		if(usage == null) {
			usage = new SystemUsage();
			MemoryUsage memoryUsage = new MemoryUsage();
			memoryUsage.setLimit(200 * 1024 * 1023);
			usage.setMemoryUsage(memoryUsage);
		}
		return usage;
	}
}
