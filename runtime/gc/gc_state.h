/* Copyright (C) 2012 Matthew Fluet.
 * Copyright (C) 1999-2008 Henry Cejtin, Matthew Fluet, Suresh
 *    Jagannathan, and Stephen Weeks.
 * Copyright (C) 1997-2000 NEC Research Institute.
 *
 * MLton is released under a BSD-style license.
 * See the file MLton-LICENSE for details.
 */

#if (defined (MLTON_GC_INTERNAL_TYPES))

struct GC_state {
  /* These fields are at the front because they are the most commonly
   * referenced, and having them at smaller offsets may decrease code
   * size and improve cache performance.
   */
  pointer frontier; /* heap.start <= frontier < limit */
  pointer limit; /* limit = heap.start + heap.size */
  pointer stackTop; /* Top of stack in current thread. */
  pointer stackLimit; /* stackBottom + stackSize - maxFrameSize */
  size_t exnStack;
  /* Alphabetized fields follow. */
  size_t alignment; /* */
  bool amInGC;
  bool amOriginal;
  char **atMLtons; /* Initial @MLton args, processed before command line. */
  int atMLtonsLength;
  uint32_t atomicState;
  objptr callFromCHandlerThread; /* Handler for exported C calls (in heap). */
  struct GC_callStackState callStackState;
  bool canMinor; /* TRUE iff there is space for a minor gc. */
  struct GC_controls controls;
  struct GC_cumulativeStatistics cumulativeStatistics;
  objptr currentThread; /* Currently executing thread (in heap). */
  struct GC_forwardState forwardState;
  GC_frameLayout frameLayouts; /* Array of frame layouts. */
  uint32_t frameLayoutsLength; /* Cardinality of frameLayouts array. */
  struct GC_generationalMaps generationalMaps;
  objptr *globals;
  uint32_t globalsLength;
  bool hashConsDuringGC;
  struct GC_heap *heap;
  struct GC_intInfInit *intInfInits;
  uint32_t intInfInitsLength;
  struct GC_lastMajorStatistics *lastMajorStatistics;
  pointer limitPlusSlop; /* limit + GC_HEAP_LIMIT_SLOP */
  int (*loadGlobals)(FILE *f); /* loads the globals from the file. */
  uint32_t magic; /* The magic number for this executable. */
  uint32_t maxFrameSize;
  bool mutatorMarksCards;
  GC_objectHashTable objectHashTable;
  GC_objectType objectTypes; /* Array of object types. */
  uint32_t objectTypesLength; /* Cardinality of objectTypes array. */
  struct GC_profiling profiling;
  GC_frameIndex (*returnAddressToFrameIndex) (GC_returnAddress ra);
  objptr savedThread; /* Result of GC_copyCurrentThread.
                       * Thread interrupted by arrival of signal.
                       */
  int (*saveGlobals)(FILE *f); /* saves the globals to the file. */
  bool saveWorldStatus; /* */
  struct GC_heap *secondaryHeap; /* Used for major copying collection. */
  objptr signalHandlerThread; /* Handler for signals (in heap). */
  struct GC_signalsInfo signalsInfo;
  struct GC_sourceMaps sourceMaps;
  pointer stackBottom; /* Bottom of stack in current thread. */
  struct GC_sysvals sysvals;
  struct GC_translateState translateState;
  struct GC_vectorInit *vectorInits;
  uint32_t vectorInitsLength;
  GC_weak weaks; /* Linked list of (live) weak pointers */
};

#endif /* (defined (MLTON_GC_INTERNAL_TYPES)) */

#if (defined (MLTON_GC_INTERNAL_FUNCS))

static void displayGCState (GC_state s, FILE *stream);

static inline size_t sizeofGCStateCurrentStackUsed (GC_state s);
static inline void setGCStateCurrentThreadAndStack (GC_state s);
static void setGCStateCurrentHeap (GC_state s,
                                   size_t oldGenBytesRequested,
                                   size_t nurseryBytesRequested);

#endif /* (defined (MLTON_GC_INTERNAL_FUNCS)) */

#if (defined (MLTON_GC_INTERNAL_BASIS))

PRIVATE bool GC_getAmOriginal (void);
PRIVATE void GC_setAmOriginal (bool b);
PRIVATE void GC_setControlsMessages (bool b);
PRIVATE void GC_setControlsSummary (bool b);
PRIVATE void GC_setControlsRusageMeasureGC (bool b);
PRIVATE uintmax_t GC_getCumulativeStatisticsBytesAllocated (void);
PRIVATE uintmax_t GC_getCumulativeStatisticsNumCopyingGCs (void);
PRIVATE uintmax_t GC_getCumulativeStatisticsNumMarkCompactGCs (void);
PRIVATE uintmax_t GC_getCumulativeStatisticsNumMinorGCs (void);
PRIVATE size_t GC_getCumulativeStatisticsMaxBytesLive (void);
PRIVATE void GC_setHashConsDuringGC (bool b);
PRIVATE size_t GC_getLastMajorStatisticsBytesLive (void);

PRIVATE pointer GC_getCallFromCHandlerThread (void);
PRIVATE void GC_setCallFromCHandlerThread (pointer p);
PRIVATE pointer GC_getCurrentThread (void);
PRIVATE pointer GC_getSavedThread (void);
PRIVATE void GC_setSavedThread (pointer p);
PRIVATE void GC_setSignalHandlerThread (pointer p);

#endif /* (defined (MLTON_GC_INTERNAL_BASIS)) */

PRIVATE struct rusage* GC_getRusageGCAddr (void);

PRIVATE sigset_t* GC_getSignalsHandledAddr (void);
PRIVATE sigset_t* GC_getSignalsPendingAddr (void);
PRIVATE void GC_setGCSignalHandled (bool b);
PRIVATE bool GC_getGCSignalPending (void);
PRIVATE void GC_setGCSignalPending (bool b);
