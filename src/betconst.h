/*
 * betconst.h
 *
 *  Created on: Jun 16, 2014
 *      Author: dimitar
 */

#ifndef BETCONST_H_
#define BETCONST_H_

#define LOGO "ETD-6"
#define PRINTOUT_TITLE "Treatment Print out ETD-6"
#define DB_FILE "./etd-6.db"


//protocol
#define PROTOCOL_TIMEOUT 500 //milliseconds

#define PROTOCOL_PREAMBLE "Z"
#define PROTOCOL_PREAMBLE_RESPONSE 'z'

#define CONFIG_FILE "etd-6.ini"

#define VOLTAGE_LOW_INCREMENT 0.1
#define VOLTAGE_LOW_DECREMENT 0.1
#define VOLTAGE_DECREMENT 5
#define VOLTAGE_LIMIT  32
#define CURRENTS_LIMIT 70
#define CURRENT_LIMIT 120
#define R_LIMIT 1000
#define Q_LIMIT 1000
#define MINIMUM_CURRENT 0.1 //minimum current that could be generated
#define DURATION_LIMIT 240 * 60
#define CURRENT_INCREMENT 1
#define CURRENT_DECREMENT 1
#define DURATION_INCREMENT 60
#define DURATION_DECREMENT 60

#define FONT_NAME "arial"
#endif /* BETCONST_H_ */
