#pragma once
#include <dataType.h>

struct server;

enum libflash_mem_type {
	MEM_TYPE_RAM = 0,
	MEM_TYPE_ROM,
	MEM_TYPE_FLASH,
};

struct mem_map_die {
	enum libflash_mem_type mem_type;
	U64 start;
	U64 length;
	U64 block_size;
	struct mem_map_die *next;
};

enum thserver_flash_commad_type
{
	FLASH_CMD_SECTOR_ERASE = 1,
	FLASH_CMD_CHIP_ERASE,
	FLASH_CMD_PROGRAM_DATA,
	FLASH_CMD_PROGRAM_BIN,
	FLASH_CMD_PROGRAM_HEX,
	FLASH_CMD_PROGRAM_ELF,
	FLASH_CMD_DUMP_BIN,
	FLASH_CMD_DUMP_HEX,
};

struct flash_command_contents
{
	int verify;
	const char *path;
	U64 addr;
	U64 length;
	int valid;
	unsigned char *data;
};

#define FLASH_COMMAND_COUNT_MAX 32
struct thserver_flash_command
{
	enum thserver_flash_commad_type cmd_type;
	struct flash_command_contents cmd_content[FLASH_COMMAND_COUNT_MAX];
};

/* Implemented in libflash.c */
void *libflash_flash_driver_init(const char *path, void *target, unsigned int timeout, int print_error);

int libflash_flash_driver_ok(void *handle);

struct mem_map_die * libflash_get_memory_map(void *handle, int xlen);

void libflash_memory_map_destory(struct mem_map_die * my_mem_map);

void libflash_uninit(void *handle);

int libflash_do_flashcommand_prepare(void *flashalgorithm_handle, void *target, void(*message_out) (const char *, ...));

int libflash_do_flashcommand(void *handle, struct thserver_flash_command *cmd, void(*message_out) (const char *, ...));

int libflash_do_flashcommand_finish(void *handle, void *target, void(*message_out) (const char *, ...));

int libflash_check_addr_in_flash(void *handle, U64 addr);

int libflash_get_sector_range_via_addr(void *handle, U64 addr, U64 *sector_start, U64 *sector_length);

int libflash_mem_die_changed();

int libflash_flash_get_flashalgorithm_info(void *handle, char *str);

/* Implemented in flash-breakpoints.c */
int flashbp_add_breakpoint(U64 addr);

int flashbp_addr_is_flashbp(U64 addr);

int flashbp_insert_flash_breakpoints(struct server *server, void *flm_handle, void *target, void *cfg, U64 current_pc);

int flashbp_remove_breakpoint(void *target, U64 address);

int flashbp_resources_cleanup(void *flm_handle, void *target);

struct breakpoint *	flashbp_find_flashbp_via_addr(U64 addr);

void
flashbp_adjust_flash_sim_bps_according_to_flashcmd(void *flm_handle,
	struct thserver_flash_command *flashcmd);

void flashbp_check_mem_read(U64 addr, unsigned char *data, unsigned int length);
