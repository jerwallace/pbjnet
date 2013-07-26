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
				
				//packet_copy(&(in_port[i].packet), &packet);
				packet = in_port[i].port_queue.front();
				
				in_port[i].port_queue.pop();
				/* Unlock the port */
				port_unlock(&(in_port[i]));	
				
				/*lookup packet's appropriate output port using destination IP*/
				to_port = cam_lookup_address(&(packet.address));
				
				/* Lock the output port */
				port_lock(&(out_port[to_port]));
				 //packet_copy(&packet,&(out_port[to_port].packet));									
				out_port[to_port].port_queue.push(packet);
				
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
