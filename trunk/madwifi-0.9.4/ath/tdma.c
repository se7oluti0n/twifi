#include <linux/version.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/skbuff.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/random.h>
#include <linux/delay.h>
#include <linux/cache.h>
#include <linux/sysctl.h>
#include <linux/proc_fs.h>
#include <linux/if_arp.h>
#include <linux/rtnetlink.h>
#include <asm/uaccess.h>

#include "tdma.h"

unsigned long g_slot_set[SLOT_NUMBER];

int g_tx_num_per_slot = 0;
int g_tx_num_current_slot = 0;
int g_is_first = 1;
int g_offset_time = 0;
int g_init = 0;
unsigned long g_dstIP_IO = 0;
unsigned long g_dstIP = 0;
struct ether_header *g_eh;

void link_queue_init(void);
struct sk_buff_head * link_queue_add(u32 dstIP);

// Hash Table operate
void slot_set_init(unsigned long *slot_set)
{
  g_init = 1;
  printk("Init slot set\n");
  memset(slot_set, 0, SLOT_NUMBER * sizeof(unsigned long));
  link_queue_init();
}

// key = [0, SLOT_NUMBER - 1]
void slot_set_add(unsigned long *slot_set, int key, unsigned int dstIP)
{
  if(key >= SLOT_NUMBER || key < 0) 
  {	  
    printk("wrong slot number %d\n", key);
    return;
  }
  printk("set slot %x; dstIP: %x\n", key, dstIP);
  slot_set[key] = dstIP;
  link_queue_add(dstIP);
}

u32 slot_set_get(unsigned long *slot_set, int key)
{
  return slot_set[key];
}

int slot_set_check(unsigned long *slot_set, int key, unsigned long dstIP)
{
  return (slot_set[key] == dstIP);
}

// mod
int mod(int v, int m)
{
  return v & m;
}


/* 
 * queue per link
 */
struct sk_buff_head frame_queues[SLOT_NUMBER];
u32 ip_queues[SLOT_NUMBER];
int queue_number = 0;
#define QUEUE_SIZE 10

void link_queue_init(void)
{
	int i = 0;
	printk("%s : %d\n", __func__, SLOT_NUMBER);
	for (i = 0; i < SLOT_NUMBER; ++i)
	{
		skb_queue_head_init(&frame_queues[i]);
	}
  	memset(ip_queues, 0, SLOT_NUMBER * sizeof(unsigned long));
	queue_number = 0;
}

struct sk_buff_head * link_queue_find(u32 dstIP)
{
	int i = 0;
	for (i = 0; i < queue_number; ++i) {
		printk(KERN_INFO "%x : %x\n", ip_queues[i], dstIP);
		if(ip_queues[i] == dstIP) {
			return&frame_queues[i];
		}
	}
	return NULL;
}
struct sk_buff_head * link_queue_add(u32 dstIP)
{
	struct sk_buff_head * pHead = NULL;

	if(queue_number >= SLOT_NUMBER)
		return NULL;
	
	pHead = link_queue_find(dstIP);
	if(pHead == NULL) {
		pHead = &frame_queues[queue_number];
		ip_queues[queue_number++] = dstIP;
	}
	printk(KERN_INFO "queue number %d\n", queue_number);	
	return pHead;
}

struct sk_buff * link_queue_dequeue(u32 dstIP)
{
	struct sk_buff_head * pHead = NULL;
	struct sk_buff * skb = NULL;

	pHead = link_queue_find(dstIP);
	if(pHead == NULL) 
		return skb;

//	spin_lock(&pHead->lock);
	skb = skb_dequeue(pHead);
//	spin_unlock(&pHead->lock);

	return skb;
}
int link_queue_enqueue(u32 dstIP, struct sk_buff *skb)
{
	struct sk_buff_head * pHead = NULL;

	pHead = link_queue_find(dstIP);
	if(pHead == NULL) 
		return DESTINATION_NOT_EXSIT;
	if(pHead->qlen >= QUEUE_SIZE) 
		return QUEUE_FULL;

//	spin_lock(&pHead->lock);
	skb_queue_tail(pHead, skb);
//	spin_unlock(&pHead->lock);

	return 0;
}

