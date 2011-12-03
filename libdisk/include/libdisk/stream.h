/*
 * libdisk/stream.h
 * 
 * Interface for stream parsers.
 * 
 * Written in 2011 by Keir Fraser
 */

#ifndef __LIBDISK_STREAM_H__
#define __LIBDISK_STREAM_H__

#include <stdint.h>

struct stream {
    const struct stream_type *type;

    /* Accumulated read latency in nanosecs. Can be reset by the caller. */
    uint64_t latency;

    /* N = last bitcell returned was Nth full bitcell after index pulse. */
    uint32_t index_offset;

    /* Distance in bitcells between the most recent two index pulses. */
    uint32_t track_bitlen;

    /* Number of index pulses seen so far. */
    uint32_t nr_index;

    /* Most recent 32 bits read from the stream */
    uint32_t word;
};

#pragma GCC visibility push(default)
struct stream *stream_open(const char *name);
struct stream *stream_soft_open(
    uint8_t *data, uint16_t *speed, uint32_t bitlen);
void stream_close(struct stream *s);
void stream_reset(struct stream *s, unsigned int tracknr);
void stream_next_index(struct stream *s);
int stream_next_bit(struct stream *s);
int stream_next_bits(struct stream *s, unsigned int bits);
int stream_next_bytes(struct stream *s, void *p, unsigned int bytes);
#pragma GCC visibility pop

#endif /* __LIBDISK_STREAM_H__ */

/*
 * Local variables:
 * mode: C
 * c-file-style: "Linux"
 * c-basic-offset: 4
 * tab-width: 4
 * indent-tabs-mode: nil
 * End:
 */
