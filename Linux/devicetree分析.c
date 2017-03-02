struct boot_param_header {
	__be32	magic;			/* magic word OF_DT_HEADER 魔数*/
	__be32	totalsize;		/* total size of DT block 设备树的大小*/
	__be32	off_dt_struct;		/* offset to structure */
	__be32	off_dt_strings;		/* offset to strings */
	__be32	off_mem_rsvmap;		/* offset to memory reserve map */
	__be32	version;		/* format version */
	__be32	last_comp_version;	/* last compatible version */
	/* version 2 fields below */
	__be32	boot_cpuid_phys;	/* Physical CPU id we're booting on */
	/* version 3 fields below */
	__be32	dt_strings_size;	/* size of the DT strings block */
	/* version 17 fields below */
	__be32	dt_struct_size;		/* size of the DT structure block */
};
/*
1、首先读取内存中的devicetree
2、获取devicetree的root node
3、获取root node中的compatible属性
4、匹配最佳的平台
*/

devtree = phys_to_virt(dt_phys);

	/* check device tree validity */
	if (be32_to_cpu(devtree->magic) != OF_DT_HEADER)
		return NULL;

	/* Search the mdescs for the 'best' compatible value match */
	initial_boot_params = devtree;
	dt_root = of_get_flat_dt_root();
	for_each_machine_desc(mdesc) {
		score = of_flat_dt_match(dt_root, mdesc->dt_compat);
		if (score > 0 && score < mdesc_score) {
			mdesc_best = mdesc;
			mdesc_score = score;
		}
	}

of_get_flat_dt_root(); // 获取device tree的根？find the root node in the flat blob 找到二进制树的根节点

#define for_each_machine_desc(p)			\
	for (p = __arch_info_begin; p < __arch_info_end; p++)

int __init of_flat_dt_match(unsigned long node, const char *const *compat)
{
	return of_fdt_match(initial_boot_params, node, compat);
}

int of_fdt_match(struct boot_param_header *blob, unsigned long node,
                 const char *const *compat)
{
	unsigned int tmp, score = 0;

	if (!compat)
		return 0;

	while (*compat) {
		tmp = of_fdt_is_compatible(blob, node, *compat);
		if (tmp && (score == 0 || (tmp < score)))
			score = tmp;
		compat++;
	}

	return score;
}


void *__init of_get_flat_dt_prop(unsigned long node, const char *name,
				 unsigned long *size);	// 获取device tree的falt bolb中的属性
				 
void *of_fdt_get_property(initial_boot_params, node, name, size); // 实际的实现


int __init of_scan_flat_dt(int (*it)(unsigned long node,
				     const char *uname, int depth,			
				     void *data),
			   void *data);		// 扫描 device tree falt bolb 并且调用回调函数
								// 用来在启动内核前提取内存信息，使得将来可以unflatten the tree
								
								
								
								
struct machine_desc * __init setup_machine_fdt(unsigned int dt_phys)
{
	struct boot_param_header *devtree;
	struct machine_desc *mdesc, *mdesc_best = NULL;
	unsigned int score, mdesc_score = ~1;
	unsigned long dt_root;
	const char *model;

	if (!dt_phys)
		return NULL;

	devtree = phys_to_virt(dt_phys);

	/* check device tree validity */
	if (be32_to_cpu(devtree->magic) != OF_DT_HEADER)
		return NULL;

	/* Search the mdescs for the 'best' compatible value match */
	initial_boot_params = devtree;
	dt_root = of_get_flat_dt_root();	 // 获取falt bolb的root node
	
	// 展开宏 此时的mdesc是一个未初始化过的值 for循环中应该是循环获取kernel中保存着的 支持的厂商信息
	for (mdesc = __arch_info_begin; mdesc < __arch_info_end; mdesc++){		// 循环获取DTS中的 厂商信息
		score = of_flat_dt_match(dt_root, mdesc->dt_compat);
		if (score > 0 && score < mdesc_score) {
			mdesc_best = mdesc;
			mdesc_score = score;
		}
	}
	if (!mdesc_best) {
		const char *prop;
		long size;

		early_print("\nError: unrecognized/unsupported "
			    "device tree compatible list:\n[ ");

		prop = of_get_flat_dt_prop(dt_root, "compatible", &size);
		while (size > 0) {
			early_print("'%s' ", prop);
			size -= strlen(prop) + 1;
			prop += strlen(prop) + 1;
		}
		early_print("]\n\n");

		dump_machine_table(); /* does not return */
	}

	model = of_get_flat_dt_prop(dt_root, "model", NULL);
	if (!model)
		model = of_get_flat_dt_prop(dt_root, "compatible", NULL);
	if (!model)
		model = "<unknown>";
	pr_info("Machine: %s, model: %s\n", mdesc_best->name, model);

	/* Retrieve various information from the /chosen node */
	of_scan_flat_dt(early_init_dt_scan_chosen, boot_command_line);
	/* Initialize {size,address}-cells info */
	of_scan_flat_dt(early_init_dt_scan_root, NULL);
	/* Setup memory, calling early_init_dt_add_memory_arch */
	of_scan_flat_dt(early_init_dt_scan_memory, NULL);

	/* Change machine number to match the mdesc we're using */
	__machine_arch_type = mdesc_best->nr;

	return mdesc_best;
}

保存板子的信息的struc Mach_desc.h (f:\myself\kernel_imx\kernel_imx\arch\arc\include\asm)	2662	2015/12/27

struct machine_desc {
	const char		*name;
	const char		**dt_compat;

	void			(*init_early)(void);
	void			(*init_irq)(void);
#ifdef CONFIG_SMP
	void			(*init_smp)(unsigned int);
#endif
	void			(*init_time)(void);
	void			(*init_machine)(void);
	void			(*init_late)(void);

};

我们新建一个板子就需要通过MACHINE_START()/MACHINE_END(),来添加我们的板子信息
