/*******************************************************
 *
 *  Switch Routines
 *
 *  Created by _________, University of British Columbia
 *
 *  This is where you will put your routines to implement
 *  the switch routines.  You should use the headers as
 *  supplied.  All your code for Assignment 2 will go in this
 *  file (and possibly in switch.h)
 *
 ******************************************************/

#include "defs.h"

IPHashTable lookupTable(40000);

void *switch_thread_routine(void *arg)
{
   /* Add your code here */
}


void switch_init()
{
   for (unsigned int i = 0; i < 4; i++) {
  	if (in_port[i].flag==TRUE) {
		recieve_message_if_there_is_one(lookupTable.get(in_port[i].packet.payload));
	} 
   }
}

void switch_add_entry(ip_address_t *address,
                      int port)
{
   lookupTable.set(address,port);
}

void switch_free()
{
   /* add your code (if any) here */
}
