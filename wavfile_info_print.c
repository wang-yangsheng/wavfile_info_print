/* wavfile_info_print.c
 *
 * author: Yangsheng Wang
 * wang_yangsheng@163.com
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

struct wav_file_head_info {
	uint32_t chunk_id; /* "RIFF" */
	uint32_t chunk_size; /* 36 + subchunk2_size */
	uint32_t format; /* "WAVE" */

	/* sub-chunk "fmt" */
	uint32_t subchunk1_id; /* "fmt " */
	uint32_t subchunk1_size; /* 16:PCM */
	uint16_t audio_format; /* PCM:1 */
	uint16_t num_channels; /* mono:1, stereo:2 */
	uint32_t sample_rate; /* 8000 16000 ... 44100 48000 */
	uint32_t byte_rate; /* equal sample_rate * num_channels * bits_persample/8 */
	uint16_t block_align; /* equal num_channels * bits_persample/8 */
	uint16_t bits_persample; /* 8bits, 16bits, etc. */

	/* sub-chunk "data" */
	uint32_t subchunk2_id; /* "data" */
	uint32_t subchunk2_size; /* data size */
};

int main(int argc, char *argv[])
{
	FILE *fp = NULL;
	struct wav_file_head_info file_info;

	if (argc < 2)
		printf("%s [file.wav]\n", argv[0]);

	fp = fopen(argv[1], "rb");
	if (fp == NULL) {
		printf("fopen audio file failed\n");
		exit(1);
	}

	fread(&file_info, 1, sizeof(struct wav_file_head_info), fp);

	printf("chunk_id \t%x\n", file_info.chunk_id);
	printf("chunk_size \t%d\n", file_info.chunk_size);
	printf("format \t\t%x\n", file_info.format);
	printf("subchunk1_id \t%x\n", file_info.subchunk1_id);
	printf("subchunk1_size \t%d\n", file_info.subchunk1_size);
	printf("audio_format \t%d\n", file_info.audio_format);
	printf("num_channels \t%d\n", file_info.num_channels);
	printf("sample_rate \t%d\n", file_info.sample_rate);
	printf("byte_rate \t%d\n", file_info.byte_rate);
	printf("block_align \t%d\n", file_info.block_align);
	printf("bits_persample \t%d\n", file_info.bits_persample);
	printf("subchunk2_id \t%x\n", file_info.subchunk2_id);
	printf("Subchunk2_size \t%d\n", file_info.subchunk2_size);

	fclose(fp);

	return 0;
}
