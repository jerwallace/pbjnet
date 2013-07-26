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

queue<packet_t> * portQueue;

void *switch_thread_routine(void *arg)
{

	while(!die)
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			if (in_port[i].flag==TRUE)
			{
				/* Port where packet should go to */
				int to_port;

				/* Lock the input port */
				port_lock(&(in_port[i]));

				/* Set the flag to false */
				in_port[i].flag==FALSE;

				/*lookup packet's appropriate output port using destination IP*/
				to_port = cam_lookup_address(&(in_port[i].packet).address);

				/* Lock the output port */
				port_lock(&(out_port[to_port]));

                packet_copy(&(in_port[i].packet),&(out_port[to_port].packet));

				/* Unlock the port */
				port_unlock(&(in_port[i]));

				/* Set the flag to indicate that the port has a packet */
				out_port[to_port].flag = TRUE;

				/* Unlock the port */
				port_unlock(&(out_port[to_port]));
			}
	   }
   }
}


void switch_init()
{
    portQueue = new queue<packet_t>[4];

}

void switch_add_entry(ip_address_t *address,
                      int port)
{
   cam_add_entry(address,port);
}

void switch_free()
{
   /* add your code (if any) here */
}
