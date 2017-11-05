###############
# Copyright 2012-2017, Angus F. Hewlett for FXpansion and ROLI
# This code should be considered a demo / proof-of-concept, not a library.
# Templated SIMD audio signal processing examples for scalar, NEON, SSE(2,4.2), AVX(1,2), AVX512.
# Demonstrates an approach to exploiting data level (SIMD) fine-grained parallelism & ILP for parallel audio engines
# e.g. synthesizer voice architectures or mixing consoles.
# "Write once, run everywhere", re-optimise the same code for different hardware feature-sets, voice counts, cache conditions,
# data layouts etc. - fast thanks to extensive compile time code generation (C++ templates).
# Recommended tools:
# * Compiler Explorer
# * IACA
# * A good profiler - VTune, Instruments, Glowcode etc.
#
# Drop me a line if interested in licensing a fuller featured version.
###############
