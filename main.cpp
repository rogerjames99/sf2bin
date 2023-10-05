#include <fstream>
#include <iostream>
#include <cstdint>
#include <math.h>
#include "sample_data.h"
#include "audio_defs.h"
#include "irish2_samples.cpp"

using namespace std;

/*
    The teensy 4.1 Audio library does not pad the sample_data struct and has 4 byte pointers.
*/

struct my_instrument_data : public instrument_data
{
    void serialize();
};

void my_instrument_data::serialize()
{
    std::ofstream ostrm("irish2.bin", ios::binary);
    cout << "Writing sample_count " << (unsigned int)sample_count << endl;
    ostrm.write((char*)&sample_count, sizeof(uint8_t));

    // Dump the sample_note_ranges
    for (int i = 0; i < sample_count; i++)
    {
        cout << "sample_note_ranges[" << i << "] = " << (unsigned int)sample_note_ranges[i] << endl;
        ostrm.write((char*)&sample_note_ranges[i], sizeof(uint8_t));
    }

    // Dump the sample metadata
    for (int i = 0; i < sample_count; i++)
    {
        // N.B. The sample field in the metadata is a pointer to an int16_t.
        // However the raw sample data is written as an array of int32_t.

        const int16_t* temp = samples[i].sample;
        cout << "sample[" << i << "]" << endl;
        samples[i].sample = reinterpret_cast<const int16_t*>(0xdeadbeef);
        ostrm.write((char*)&samples[i], sizeof(sample_data));
        samples[i].sample = temp;
    }
    // Dump the raw sample data
    // As mentioned above the raw data is written as a int32_t array.
    cout << "Starting position " << ostrm.tellp() << endl;
    for (int i = 0; i < sample_count; i++)
    {
        cout << "samples[" << i << "] number_of_raw_samples " <<  samples[i].number_of_raw_samples
            << " number of bytes " << samples[i].number_of_raw_samples * sizeof(uint32_t) << endl;
        ostrm.write((char*)samples[i].sample, samples[i].number_of_raw_samples * sizeof(uint32_t));
        cout << "Current position " << ostrm.tellp() << endl;
    }
}

int main(int, char**)
{
    uint8_t sample_count;
    uint8_t* sample_note_ranges;
    sample_data* samples;

    cout << "sizeof(instrument_data)) " << sizeof(instrument_data) << endl;
    cout << "sizeof(instrument_data::sample_count) " << sizeof(instrument_data::sample_count)
        <<  " offset " << reinterpret_cast<unsigned long>(&irish2.sample_count) - reinterpret_cast<unsigned long>(&irish2)
        << endl;
    cout << "sizeof(instrument_data::sample_count) " << sizeof(instrument_data::sample_note_ranges)
        <<  " offset " << reinterpret_cast<unsigned long>(&irish2.sample_note_ranges) - reinterpret_cast<unsigned long>(&irish2)
        << endl;
    cout << "sizeof(instrument_data::sample_count) " << sizeof(instrument_data::samples)
        <<  " offset " << reinterpret_cast<unsigned long>(&irish2.samples) - reinterpret_cast<unsigned long>(&irish2)
        << endl;



    cout << "sizeof(sample_data) " << sizeof(sample_data) << endl;
    cout << "sizeof(sample_data::sample) " << sizeof(sample_data::sample)
        <<  " offset " << reinterpret_cast<unsigned long>(&irish2_samples[0].sample) - reinterpret_cast<unsigned long>(&irish2_samples[0])
        << endl;

    cout << "raw samples size " << sizeof irish2_samples[0].sample << endl;

    cout << "sizeof(sample_data::number_of_raw_samples) " << sizeof(sample_data::number_of_raw_samples)
        <<  " offset " << reinterpret_cast<unsigned long>(&irish2_samples[0].number_of_raw_samples) - reinterpret_cast<unsigned long>(&irish2_samples[0])
        << endl;
    cout << "sizeof(sample_data::LOOP) " << sizeof(sample_data::LOOP)
        <<  " offset " << reinterpret_cast<unsigned long>(&irish2_samples[0].LOOP) - reinterpret_cast<unsigned long>(&irish2_samples[0])
        << endl;
    cout << "sizeof(sample_data::INDEX_BITS) " << sizeof(sample_data::INDEX_BITS)
        <<  " offset " << reinterpret_cast<unsigned long>(&irish2_samples[0].INDEX_BITS) - reinterpret_cast<unsigned long>(&irish2_samples[0])
        << endl;
    cout << "sizeof(sample_data::PER_HERTZ_PHASE_INCREMENT) " << sizeof(sample_data::PER_HERTZ_PHASE_INCREMENT)
        <<  " offset " << reinterpret_cast<unsigned long>(&irish2_samples[0].PER_HERTZ_PHASE_INCREMENT) - reinterpret_cast<unsigned long>(&irish2_samples[0])
        << endl;
    cout << "sizeof(sample_data::MAX_PHASE) " << sizeof(sample_data::MAX_PHASE)
        <<  " offset " << reinterpret_cast<unsigned long>(&irish2_samples[0].MAX_PHASE) - reinterpret_cast<unsigned long>(&irish2_samples[0])
        << endl;
    cout << "sizeof(sample_data::LOOP_PHASE_END) " << sizeof(sample_data::LOOP_PHASE_END)
        <<  " offset " << reinterpret_cast<unsigned long>(&irish2_samples[0].LOOP_PHASE_END) - reinterpret_cast<unsigned long>(&irish2_samples[0])
        << endl;
    cout << "sizeof(sample_data::LOOP_PHASE_LENGTH) " << sizeof(sample_data::LOOP_PHASE_LENGTH)
        <<  " offset " << reinterpret_cast<unsigned long>(&irish2_samples[0].LOOP_PHASE_LENGTH) - reinterpret_cast<unsigned long>(&irish2_samples[0])
        << endl;
    cout << "sizeof(sample_data::INITIAL_ATTENUATION_SCALAR) " << sizeof(sample_data::INITIAL_ATTENUATION_SCALAR)
        <<  " offset " << reinterpret_cast<unsigned long>(&irish2_samples[0].INITIAL_ATTENUATION_SCALAR) - reinterpret_cast<unsigned long>(&irish2_samples[0])
        << endl;
    cout << "sizeof(sample_data::DELAY_COUNT) " << sizeof(sample_data::DELAY_COUNT)
        <<  " offset " << reinterpret_cast<unsigned long>(&irish2_samples[0].DELAY_COUNT) - reinterpret_cast<unsigned long>(&irish2_samples[0])
        << endl;
    cout << "sizeof(sample_data::ATTACK_COUNT) " << sizeof(sample_data::ATTACK_COUNT)
        <<  " offset " << reinterpret_cast<unsigned long>(&irish2_samples[0].ATTACK_COUNT) - reinterpret_cast<unsigned long>(&irish2_samples[0])
        << endl;
    cout << "sizeof(sample_data::HOLD_COUNT) " << sizeof(sample_data::HOLD_COUNT)
        <<  " offset " << reinterpret_cast<unsigned long>(&irish2_samples[0].HOLD_COUNT) - reinterpret_cast<unsigned long>(&irish2_samples[0])
        << endl;
    cout << "sizeof(sample_data::DECAY_COUNT) " << sizeof(sample_data::DECAY_COUNT)
        <<  " offset " << reinterpret_cast<unsigned long>(&irish2_samples[0].DECAY_COUNT) - reinterpret_cast<unsigned long>(&irish2_samples[0])
        << endl;
    cout << "sizeof(sample_data::RELEASE_COUNT) " << sizeof(sample_data::RELEASE_COUNT)
        <<  " offset " << reinterpret_cast<unsigned long>(&irish2_samples[0].RELEASE_COUNT) - reinterpret_cast<unsigned long>(&irish2_samples[0])
        << endl;
    cout << "sizeof(sample_data::SUSTAIN_MULT) " << sizeof(sample_data::SUSTAIN_MULT)
        <<  " offset " << reinterpret_cast<unsigned long>(&irish2_samples[0].SUSTAIN_MULT) - reinterpret_cast<unsigned long>(&irish2_samples[0])
        << endl;
    cout << "sizeof(sample_data::VIBRATO_DELAY)) " << sizeof(sample_data::VIBRATO_DELAY)
        <<  " offset " << reinterpret_cast<unsigned long>(&irish2_samples[0].VIBRATO_DELAY) - reinterpret_cast<unsigned long>(&irish2_samples[0])
        << endl;
    cout << "sizeof(sample_data::VIBRATO_INCREMENT) " << sizeof(sample_data::VIBRATO_INCREMENT)
        <<  " offset " << reinterpret_cast<unsigned long>(&irish2_samples[0].VIBRATO_INCREMENT) - reinterpret_cast<unsigned long>(&irish2_samples[0])
        << endl;
    cout << "sizeof(sample_data::VIBRATO_PITCH_COEFFICIENT_INITIAL) " << sizeof(sample_data::VIBRATO_PITCH_COEFFICIENT_INITIAL)
        <<  " offset " << reinterpret_cast<unsigned long>(&irish2_samples[0].VIBRATO_PITCH_COEFFICIENT_INITIAL) - reinterpret_cast<unsigned long>(&irish2_samples[0])
        << endl;
    cout << "sizeof(sample_data::VIBRATO_PITCH_COEFFICIENT_SECOND) " << sizeof(sample_data::VIBRATO_PITCH_COEFFICIENT_SECOND)
        <<  " offset " << reinterpret_cast<unsigned long>(&irish2_samples[0].VIBRATO_PITCH_COEFFICIENT_SECOND) - reinterpret_cast<unsigned long>(&irish2_samples[0])
        << endl;
    cout << "sizeof(sample_data::MODULATION_DELAY) " << sizeof(sample_data::MODULATION_DELAY)
        <<  " offset " << reinterpret_cast<unsigned long>(&irish2_samples[0].MODULATION_DELAY) - reinterpret_cast<unsigned long>(&irish2_samples[0])
        << endl;
    cout << "sizeof(sample_data::MODULATION_INCREMENT) " << sizeof(sample_data::MODULATION_INCREMENT)
        <<  " offset " << reinterpret_cast<unsigned long>(&irish2_samples[0].MODULATION_INCREMENT) - reinterpret_cast<unsigned long>(&irish2_samples[0])
        << endl;
    cout << "sizeof(sample_data::MODULATION_PITCH_COEFFICIENT_INITIAL) " << sizeof(sample_data::MODULATION_PITCH_COEFFICIENT_INITIAL)
        <<  " offset " << reinterpret_cast<unsigned long>(&irish2_samples[0].MODULATION_PITCH_COEFFICIENT_INITIAL) - reinterpret_cast<unsigned long>(&irish2_samples[0])
        << endl;
    cout << "sizeof(sample_data::MODULATION_PITCH_COEFFICIENT_SECOND) " << sizeof(sample_data::MODULATION_PITCH_COEFFICIENT_SECOND)
        <<  " offset " << reinterpret_cast<unsigned long>(&irish2_samples[0].MODULATION_PITCH_COEFFICIENT_SECOND) - reinterpret_cast<unsigned long>(&irish2_samples[0])
        << endl;
    cout << "sizeof(sample_data::MODULATION_AMPLITUDE_INITIAL_GAIN) " << sizeof(sample_data::MODULATION_AMPLITUDE_INITIAL_GAIN)
        <<  " offset " << reinterpret_cast<unsigned long>(&irish2_samples[0].MODULATION_AMPLITUDE_INITIAL_GAIN) - reinterpret_cast<unsigned long>(&irish2_samples[0])
        << endl;
    cout << "sizeof(sample_data::MODULATION_AMPLITUDE_SECOND_GAIN) " << sizeof(sample_data::MODULATION_AMPLITUDE_SECOND_GAIN)
        <<  " offset " << reinterpret_cast<unsigned long>(&irish2_samples[0].MODULATION_AMPLITUDE_SECOND_GAIN) - reinterpret_cast<unsigned long>(&irish2_samples[0])
        << endl;

    my_instrument_data instrument = {irish2.sample_count, irish2.sample_note_ranges, irish2.samples};
    instrument.serialize();
	return 0;
}
