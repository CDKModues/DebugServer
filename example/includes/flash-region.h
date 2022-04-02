#ifndef __MEM_REGION_H__
#define __MEM_REGION_H__

#include <dataType.h>
#ifdef _WIN32
#define FLSHREGIONAPI __declspec(dllexport)
#else
#define FLSHREGIONAPI
#endif


#ifdef __cplusplus
extern "C" {
#endif

enum flash_algorithm_get_config_type
{
	FLAGALGORITHM_GET_DESTROYED_ADDR,
	FLAGALGORITHM_GET_DESTROYED_SIZE,
	FLAGALGORITHM_GET_LOAD_CONTENT,
	FLAGALGORITHM_GET_ENTRY_ADDR,
	FLAGALGORITHM_GET_BKPT_LABEL,
	FLAGALGORITHM_GET_FUNCID_ADDR,
	FLAGALGORITHM_GET_DST_ADDR,
	FLAGALGORITHM_GET_LEN_ADDR,
	FLAGALGORITHM_GET_BUFFER_ADDR,
	FLAGALGORITHM_GET_BUFFER_SIZE,
	FLAGALGORITHM_GET_SECTOR_SIZE,
};

struct flash_block
{
	U64 start;
	U64 size;
	U64 sector_size;
};

struct flash_algorithm_content
{
	U64 addr;
	U64 size;
	unsigned char *contents;

	struct flash_algorithm_content *next;
};

FLSHREGIONAPI void *FlashAlgorithmInit(const char *path, void *target, unsigned int timeout);

//FLSHREGIONAPI char* FlashAlgorithmGetGdbXml(void *handle);

//FLSHREGIONAPI void FlashAlgorithmForeachBlocks(void *handle, void (*func)(size_t n, uint64_t start, size_t size, size_t sector_size));

FLSHREGIONAPI struct flash_block * FlashAlgorithmGetBlocks(void *handle, int *count);

FLSHREGIONAPI void FlashAlgorithmReleaseBlocks(struct flash_block*blk);

FLSHREGIONAPI int FlashAlgorithmUinit(void *handle);

FLSHREGIONAPI int FlashAlgorithmFileOk(void *handle);

FLSHREGIONAPI const char * FlashAlgorithmErrorMsg(void *handle);

FLSHREGIONAPI int FlashAlgorithmSectorErase(void *handle, U64 addr, U64 size);

FLSHREGIONAPI int FlashAlgorithmProgram(void *handle, U64 addr, U64 size, unsigned char *data);

FLSHREGIONAPI void FlashAlgorithmGetDestoryedAddr(void *handle, U64 *addr, U64 *size);

FLSHREGIONAPI int FlashAlgorithmLoad(void *handle);

FLSHREGIONAPI int FlashAlgorithmRestoreState(void *handle);

FLSHREGIONAPI int FlashAlgorithmChipErase(void *handle);

FLSHREGIONAPI int FlashAlgorithmProgramBin(void *handle, const char *file, U64 addr, int verify);

FLSHREGIONAPI int FlashAlgorithmProgramHex(void *handle, const char *file, int verify);

FLSHREGIONAPI int FlashAlgorithmProgramElf(void *handle, const char *file, int verify);

FLSHREGIONAPI int FlashAlgorithmCheckFlashAddr(void *handle, U64 addr);

FLSHREGIONAPI int FlashAlgorithmGetSectorRange(void *handle, U64 addr, U64 *start, U64 *size);

FLSHREGIONAPI int FlashAlgorithmGetFLMInfo(void *handle, char *str);

FLSHREGIONAPI int FlashAlgorithmReadToHexFile(void *handle, const char *path, U64 address, U64 size);

FLSHREGIONAPI int FlashAlgorithmReadToBinFile(void *handle, const char *path, U64 address, U64 size);

#ifdef __cplusplus
}
#endif

#endif

