/*
 * switch.h
 *
 *  Created on: Jul 22, 2013
 *      Author: Bahman
 */

#ifndef SWITCH_H_
#define SWITCH_H_

void switch_init();
void switch_add_entry(ip_address_t *address, int port);
void switch_thread_routine(void *args);
void switch_free();

#endif /* SWITCH_H_ */
