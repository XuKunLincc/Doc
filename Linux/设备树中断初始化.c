// 中断初始化过程
// 一个链表结构体 用来保存中断控制器和产生中断的设备
struct intc_desc {
	struct list_head	list;
	struct device_node	*dev;				
	struct device_node	*interrupt_parent;	// 保存着 interrupt-controller 的节点
};

static inline void list_add_tail(struct list_head *new, struct list_head *head)
{
	__list_add(new, head->prev, head);
}


/* 
* 该函数其实就是将一个数据插入到两个数据中间
* 因为，内核链表是一个循环链表，最后的数据结构的next指向头指针 头指针的prev指向了最后的
* 数据结构 看起来就是连续的数据结构 如果我们想按顺序插入一个指针 直接在这两个指针中插入一个即可
*/
static inline void __list_add(struct list_head *new,
			      struct list_head *prev,
			      struct list_head *next)
{
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}

/**
 * list_for_each_entry_safe - iterate over list of given type safe against removal of list entry
 * @pos:	the type * to use as a loop cursor.
 * @n:		another type * to use as temporary storage
 * @head:	the head for your list.
 * @member:	the name of the list_struct within the struct.
 */
#define list_for_each_entry_safe(pos, n, head, member)			\
	for (pos = list_entry((head)->next, typeof(*pos), member),	\
		n = list_entry(pos->member.next, typeof(*pos), member);	\
	    &pos->member != (head); 					\
	    pos = n, n = list_entry(n->member.next, typeof(*n), member))

/**
 * list_entry - get the struct for this entry
 * @ptr:	the &struct list_head pointer.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_struct within the struct.
 */
#define list_entry(ptr, type, member) \
	container_of(ptr, type, member)

/*通过指向list的指针 获取到到 intc_desc对象 包含它的一个对象*/
#define container_of(ptr, type, member) ({			\
	const typeof(((intc_desc *)0)->list) * __mptr = (ptr);	\
	(type *)((char *)__mptr - offsetof(type, member)); })

while (!list_empty(&intc_desc_list)) {
		/*
		 * Process all controllers with the current 'parent'.
		 * First pass will be looking for NULL as the parent.
		 * The assumption is that NULL parent means a root controller.
		 */
		list_for_each_entry_safe(desc, temp_desc, &intc_desc_list, list) {
			const struct of_device_id *match;
			int ret;
			of_irq_init_cb_t irq_init_cb;

			if (desc->interrupt_parent != parent)
				continue;

			list_del(&desc->list);
			match = of_match_node(matches, desc->dev);
			if (WARN(!match->data,
			    "of_irq_init: no init function for %s\n",
			    match->compatible)) {
				kfree(desc);
				continue;
			}

			pr_debug("of_irq_init: init %s @ %p, parent %p\n",
				 match->compatible,
				 desc->dev, desc->interrupt_parent);
			irq_init_cb = (of_irq_init_cb_t)match->data;
			ret = irq_init_cb(desc->dev, desc->interrupt_parent);
			if (ret) {
				kfree(desc);
				continue;
			}

			/*
			 * This one is now set up; add it to the parent list so
			 * its children can get processed in a subsequent pass.
			 */
			list_add_tail(&desc->list, &intc_parent_list);
		}

		/* Get the next pending parent that might have children */
		desc = list_first_entry(&intc_parent_list, typeof(*desc), list);
		if (list_empty(&intc_parent_list) || !desc) {
			pr_err("of_irq_init: children remain, but no parents\n");
			break;
		}
		list_del(&desc->list);
		parent = desc->dev;
		kfree(desc);
	}

__irqchip_begin：	// 保存着和中断寄存器相关的信息
irq_alloc_descs(); // 这个宏是用来申请中断描述符的

一、声明新的中断控制器
	IRQCHIP_DECLARE 该宏是用来声明中断控制器信息的
#define IRQCHIP_DECLARE(name,compstr,fn)				\
	static const struct of_device_id irqchip_of_match_##name	\
	__used __section(__irqchip_of_table)				\
	= { .compatible = compstr, .data = fn }

二、设备的I/O端口映射
	在ARM体系上，其实就是获取控制寄存器的地址
	void __iomem *of_iomap(struct device_node *np, int index);
		-->of_address_to_resource(np, index, &res);		// 把地址转换为 resource
			-->of_get_address(dev, index, &size, &flags);
		-->ioremap(res.start, resource_size(&res));

三、中断初始化流程：
-->start_kernel();
	-->init_IRQ();	// arch/arm/kernel/irq.c
		-->irqchip_init();	// kernel_imx/drivers/irqchip/irqchip.c
			-->of_irq_init(__irqchip_begin);
				-->for 循环开始 
				↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
	for(遍历device tree中的中断控制器)
		gic_of_init(struct device_node *node, struct device_node *parent);
			-->get the Distributor address range and CPU interface address range
			-->gic_init_bases(gic_cnt, -1, dist_base, cpu_base, percpu_offset, node);
				--> hwirq_base = 32;
				/*获取gic的interrupt sources number*/
				-->gic_irqs = readl_relaxed(gic_data_dist_base(gic) + GIC_DIST_CTR) & 0x1f;
				-->irq_alloc_descs(irq_start, 16, gic_irqs, numa_node_id());	// 在内存中分配中断描述符 并将其初始化为0
				-->gic_dist_init(gic); // 初始化 GIC硬件 比如先暂时设定所有中断以低电平触发
				-->gic_cpu_init(gic);	// 初始化CPU 接口
				-->gic_pm_init(gic);	// 初始化GIC的电源

四、设备树上的能产生中断的设备怎么注册中断？
	设备树上的中断值是相对于32的。例如在串口的设备树中，interrupts = <0x0 0x1a 0x4>; 0x1a就被等于，GIC中串口一的中断号减去32

什么是 IRQ_domain
IRQ_domain是用来映射irqnum和hwirq之间的关系的

五、如何注册irq_chip
	

	struct irq_desc irq_desc[NR_IRQS] __cacheline_aligned_in_smp = {
	[0 ... NR_IRQS-1] = {
		.handle_irq	= handle_bad_irq,
		.depth		= 1,
		.lock		= __RAW_SPIN_LOCK_UNLOCKED(irq_desc->lock),
	}
};

六、中断流程猜测
	一、假设是uart中断：
		CPU收到中断，切换至中断模式
			a-->到硬件指定的内存地址执行代码
				-->找到 root controller GIC
					-->查找irq_domain
						-->找到对应irq_num 并且找到 中断处理函数

	二假设是GPIO中断：
		CPU收到中断，切换至中断模式
			a-->到硬件指定的内存地址执行代码
				-->找到 root controller GIC
					-->查找irq_domain
						-->找到对应irq_num 并且找到 GPIO中断控制器
							-->查找irq_domain
								-->找到对应irq_num 并且找到 中断处理函数