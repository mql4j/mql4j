package com.mql4j.examples;

import java.io.UnsupportedEncodingException;
import java.security.NoSuchAlgorithmException;
import java.util.UUID;

import org.apache.commons.codec.digest.DigestUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class Codec {
	private final static String ENCODING = "UTF-8";
	private final static Logger log = LoggerFactory.getLogger(Codec.class);

	public static String md5(final String str) throws UnsupportedEncodingException, NoSuchAlgorithmException {
		log.info(String.format("Calculate md5 hash for %d bytes", str.length()));
		return DigestUtils.md5Hex(str);
	}

	public static String sha2(final String str) throws UnsupportedEncodingException, NoSuchAlgorithmException {
		log.info(String.format("Calculate sha2 hash for %d bytes", str.length()));
		return DigestUtils.sha256Hex(str);
	}

	public static String uuid(final String str) throws UnsupportedEncodingException {
		log.info(String.format("Calculate UUID for %d bytes", str.length()));
		UUID u = UUID.nameUUIDFromBytes(str.getBytes(ENCODING));
		return u.toString();
	}
}
