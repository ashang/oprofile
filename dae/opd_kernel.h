/**
 * @file opd_kernel.h
 * Dealing with the kernel and kernel module samples
 *
 * @remark Copyright 2002 OProfile authors
 * @remark Read the file COPYING
 *
 * @author John Levon <moz@compsoc.man.ac.uk>
 * @author Philippe Elie <phil_el@wanadoo.fr>
 */

#ifndef OPD_KERNEL_H
#define OPD_KERNEL_H

#include "op_types.h"

void opd_init_kernel_image(void);
void opd_read_system_map(char const * filename);
void opd_clear_module_info(void);
void opd_handle_kernel_sample(u32 eip, u16 count);

#endif /* OPD_KERNEL_H */