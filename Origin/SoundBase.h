#ifndef INCLUDED_SOUND_BASE_H
#define INCLUDED_SOUND_BASE_H

#define CHANNEL				2			// ステレオ
#define BITS_PER_SAMPLE		16			// 量子化ビット数
#define SAMPLES_PER_SEC		44100		// 標本化周波数

#define BLOCK_ALIGN			4			// CHANNEL * BITS_PER_SAMPLE / 8
#define BYTES_PER_SEC		176400		// SAMPLES_PER_SEC * BLOCK_ALIGN
#define BUFFER_SIZE			11760		// BYTES_PER_SEC / BUFFER_PER_SEC( 15 )
//#define BUFFER_SIZE			17640		// BYTES_PER_SEC / BUFFER_PER_SEC( 10 )

#define WAVE_DATA_LENGTH	2940		// BUFFER_SIZE / 4  ( double -> char )
//#define WAVE_DATA_LENGTH	4410		// BUFFER_SIZE / 4  ( double -> char )

#define EFFECT_MAX_NUM		6	// 追加できるエフェクトの最大数
#define LOG_MAX_DATA_NUM	30	// バッファのログを取るデータの最大数
#define LOG_MAX_INDEX_NUM	3	// バッファのログを取るインデックスの最大数

typedef enum {
	WAVE_CURVE,
	WAVE_SAWTOOTH,
	WAVE_SQUARE,
	WAVE_TRIANGLE,
	WAVE_NONE
} WaveID;

typedef enum {
	EFFECT_NOISE_GATE,
	EFFECT_DISTORTION1,
	EFFECT_DISTORTION2,
	EFFECT_DISTORTION3,
	EFFECT_COMPRESSOR,
	EFFECT_TREMOLO,
	
	EFFECT_DELAY,
	EFFECT_CHORUS,
	EFFECT_VIBRATO,

	EFFECT_LOW_PASS_FILTER,
	EFFECT_HIGH_PASS_FILTER,
	EFFECT_BAND_PASS_FILTER,
	EFFECT_BAND_ELIMINATE_FILTER,

	EFFECT_EQUALIZER,

	EFFECT_NONE
} EffectID;

typedef enum {
	EQ_LOW_SHELVING,
	EQ_PEAKING,
	EQ_HIGH_SHELVING,
	EQ_NONE
} EQID;

#endif // INCLUDED_SOUND_BASE_H
