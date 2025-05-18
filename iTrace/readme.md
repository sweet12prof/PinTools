# Purpose 
 1. This pintool generates traces for all load instructions (standard memory operations, excludes some non standard loads check pin docs)
 2. The trace is meant to be used to drive an address predictor that requires actaual target addresses, the instruction IP, base address, and offset specified in the load instruction.
 3. The instruction disambiguates thread if the instruction is not singlethreaded.
 4. Make use of dedicated buffers for each thread hence no use of locks to synchronise threads, every thread writes their own file 
