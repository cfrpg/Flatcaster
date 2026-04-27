#ifndef __INSTRUMENT_DATA_H__
#define __INSTRUMENT_DATA_H__

#include <stdint.h>

#define INSTRUMENT_MIN_MIDI 40
#define INSTRUMENT_MAX_MIDI 86
#define BYTES_PER_NOTE      384000

typedef struct {
    uint32_t sample_rate;
    uint32_t bytes_per_note;
    uint16_t min_midi_note;
    uint16_t max_midi_note;
    const uint16_t (*data)[192000];
} InstrumentConfig;

extern const uint16_t guitar_sus_down[47][192000];
extern const InstrumentConfig UI_guitar;

#endif
