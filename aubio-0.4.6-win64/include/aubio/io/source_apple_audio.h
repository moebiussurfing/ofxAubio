/*
  Copyright (C) 2012-2013 Paul Brossier <piem@aubio.org>

  This file is part of aubio.

  aubio is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  aubio is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with aubio.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef AUBIO_SOURCE_APPLE_AUDIO_H
#define AUBIO_SOURCE_APPLE_AUDIO_H

/** \file

  Read from file using CoreAudio Extended Audio File Services
  [ExtAudioFileRef](https://developer.apple.com/library/ios/#documentation/MusicAudio/Reference/ExtendedAudioFileServicesReference/Reference/reference.html)

  Avoid including this file directly! Prefer using ::aubio_source_t instead to
  make your code portable.

  To write to file, use ::aubio_sink_t.

  \example io/test-source_apple_audio.c

*/

#ifdef __cplusplus
extern "C" {
#endif

/** apple audio media source object */
typedef struct _aubio_source_apple_audio_t aubio_source_apple_audio_t;

/**

  create new ::aubio_source_apple_audio_t

  \param uri the file path or uri to read from
  \param samplerate sampling rate to view the fie at
  \param hop_size the size of the blocks to read from

  Creates a new source object. If `0` is passed as `samplerate`, the sample
  rate of the original file is used.

  The samplerate of newly created source can be obtained using
  ::aubio_source_apple_audio_get_samplerate.

*/
aubio_source_apple_audio_t * new_aubio_source_apple_audio(const char_t * uri, uint_t samplerate, uint_t hop_size);

/**

  read monophonic vector of length hop_size from source object

  \param s source object, created with ::new_aubio_source_apple_audio
  \param read_to ::fvec_t of data to read to
  \param read upon returns, equals to number of frames actually read

  Upon returns, `read` contains the number of frames actually read from the
  source. `hop_size` if enough frames could be read, less otherwise.

*/
void aubio_source_apple_audio_do(aubio_source_apple_audio_t * s, fvec_t * read_to, uint_t * read);

/**

  read polyphonic vector of length hop_size from source object

  \param s source object, created with ::new_aubio_source_apple_audio
  \param read_to ::fmat_t of data to read to
  \param read upon returns, equals to number of frames actually read

  Upon returns, `read` contains the number of frames actually read from the
  source. `hop_size` if enough frames could be read, less otherwise.

*/
void aubio_source_apple_audio_do_multi(aubio_source_apple_audio_t * s, fmat_t * read_to, uint_t * read);

/**

  get samplerate of source object

  \param s source object, created with ::new_aubio_source_apple_audio
  \return samplerate, in Hz

*/
uint_t aubio_source_apple_audio_get_samplerate(const aubio_source_apple_audio_t * s);

/**

  get channels of source object

  \param s source object, created with ::new_aubio_source_apple_audio
  \return number of channels

*/
uint_t aubio_source_apple_audio_get_channels(const aubio_source_apple_audio_t * s);

/**

  get the duration of source object, in frames

  \param s source object, created with ::new_aubio_source_apple_audio
  \return number of frames in file

*/
uint_t aubio_source_apple_audio_get_duration(const aubio_source_apple_audio_t * s);

/**

  seek source object

  \param s source object, created with ::new_aubio_source
  \param pos position to seek to, in frames

  \return 0 if sucessful, non-zero on failure

*/
uint_t aubio_source_apple_audio_seek (aubio_source_apple_audio_t * s, uint_t pos);

/**

  close source

  \param s source object, created with ::new_aubio_source_apple_audio

  \return 0 if sucessful, non-zero on failure

*/
uint_t aubio_source_apple_audio_close(aubio_source_apple_audio_t * s);

/**

  close source and cleanup memory

  \param s source object, created with ::new_aubio_source_apple_audio

*/
void del_aubio_source_apple_audio(aubio_source_apple_audio_t * s);

#ifdef __cplusplus
}
#endif

#endif /* AUBIO_SOURCE_APPLE_AUDIO_H */
