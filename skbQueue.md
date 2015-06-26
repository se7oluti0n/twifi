alloc\_skb has a memory limitation

```
struct sk_buff_head frame_queue;

skb_queue_head_init(&frame_queue);

spin_lock(&queue_lock);
skb_queue_tail(&frame_queue, skb);
spin_unlock(&queue_lock);

spin_lock(&queue_lock);
while (skb = skb_dequeue(&frame_queue))
	dev_queue_xmit(skb);
spin_unlock(&queue_lock);
```