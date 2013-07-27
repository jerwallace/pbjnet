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
				packet_t packet;
				
				/* Set the flag to false */
				in_port[i].flag=FALSE;
				
				/* Lock the input port */
				port_lock(&(in_port[i]));
				
				/* Search routing table for destination port */
				to_port = cam_lookup_address(&(in_port[i].port_queue.front().address));
				
				/* Unlock the port */
				port_unlock(&(in_port[i]));	
				
				if(out_port[to_port].port_queue.size()<=BUFFER_SIZE)
				{
					/* Lock the output port */
					port_lock(&(out_port[to_port]));
				
					/* Push the packet onto output port queue */
					out_port[to_port].port_queue.push(in_port[i].port_queue.front());
					
					/* Set the flag to indicate that the port has a packet */
					out_port[to_port].flag = TRUE;
					
					/* Unlock the output port */
					port_unlock(&(out_port[to_port]));
				}
				/* Unlock the input port */
				in_port[i].port_queue.pop();
			} 
	   }
   }
}


void switch_init()
{

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
