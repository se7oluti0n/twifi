#ifndef _TDMA_H_
#define _TDMA_H_

#define SLOT_SIZE 13	         // 2^3 * 2^10, 8 * 1024us
#define SLOT_NUMBER 32 
#define SLOT_MASK 0x0000001f   // 5 bit mask, it is same as SLOT_NUMBER

extern int g_init;

#define QUEUE_FULL -2
#define DESTINATION_NOT_EXSIT -3

void link_queue_init(void);
struct sk_buff_head * link_queue_find(u32 dstIP);
struct sk_buff_head * link_queue_add(u32 dstIP);
struct sk_buff * link_queue_dequeue(u32 dstIP);
int link_queue_enqueue(u32 dstIP, struct sk_buff *skb);

extern unsigned long g_slot_set[SLOT_NUMBER];
extern unsigned long g_dstIP_IO;

void slot_set_init(unsigned long *slot_set);
void slot_set_add(unsigned long *slot_set, int key, unsigned int dstIP);
u32 slot_set_get(unsigned long *slot_set, int key);
int slot_set_check(unsigned long *slot_set, int key, unsigned long dstIP);
int mod(int v, int m);


#endif /* _TDMA_H_ */
