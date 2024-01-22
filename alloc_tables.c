#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "alloc_tables.h"

int sblims[5] = { 27, 30, 8, 12, 30 };

static sb_alloc al_table_0[SBLIMIT][16] =
{
  { // 0
    {0,4,0,0},{3,5,1,0},{7,3,3,2},{15,4,3,4},
    {31,5,3,5},{63,6,3,6},{127,7,3,7},{255,8,3,8},
    {511,9,3,9},{1023,10,3,10},{2047,11,3,11},{4095,12,3,12},
    {8191,13,3,13},{16383,14,3,14},{32767,15,3,15},{65535,16,3,16}
  },
  { // 1
    {0,4,0,0},{3,5,1,0},{7,3,3,2},{15,4,3,4},
    {31,5,3,5},{63,6,3,6},{127,7,3,7},{255,8,3,8},
    {511,9,3,9},{1023,10,3,10},{2047,11,3,11},{4095,12,3,12},
    {8191,13,3,13},{16383,14,3,14},{32767,15,3,15},{65535,16,3,16}
  },
  { // 2
    {0,4,0,0},{3,5,1,0},{7,3,3,2},{15,4,3,4},
    {31,5,3,5},{63,6,3,6},{127,7,3,7},{255,8,3,8},
    {511,9,3,9},{1023,10,3,10},{2047,11,3,11},{4095,12,3,12},
    {8191,13,3,13},{16383,14,3,14},{32767,15,3,15},{65535,16,3,16}
  },
  { // 3
    {0,4,0,0},{3,5,1,0},{5,7,1,1},{7,3,3,2},
    {9,10,1,3},{15,4,3,4},{31,5,3,5},{63,6,3,6},
    {127,7,3,7},{255,8,3,8},{511,9,3,9},{1023,10,3,10},
    {2047,11,3,11},{4095,12,3,12},{8191,13,3,13},{65535,16,3,16}
  },
  { // 4
    {0,4,0,0},{3,5,1,0},{5,7,1,1},{7,3,3,2},
    {9,10,1,3},{15,4,3,4},{31,5,3,5},{63,6,3,6},
    {127,7,3,7},{255,8,3,8},{511,9,3,9},{1023,10,3,10},
    {2047,11,3,11},{4095,12,3,12},{8191,13,3,13},{65535,16,3,16}
  },
  { // 5
    {0,4,0,0},{3,5,1,0},{5,7,1,1},{7,3,3,2},
    {9,10,1,3},{15,4,3,4},{31,5,3,5},{63,6,3,6},
    {127,7,3,7},{255,8,3,8},{511,9,3,9},{1023,10,3,10},
    {2047,11,3,11},{4095,12,3,12},{8191,13,3,13},{65535,16,3,16}
  },
  { // 6
    {0,4,0,0},{3,5,1,0},{5,7,1,1},{7,3,3,2},
    {9,10,1,3},{15,4,3,4},{31,5,3,5},{63,6,3,6},
    {127,7,3,7},{255,8,3,8},{511,9,3,9},{1023,10,3,10},
    {2047,11,3,11},{4095,12,3,12},{8191,13,3,13},{65535,16,3,16}
  },
  { // 7
    {0,4,0,0},{3,5,1,0},{5,7,1,1},{7,3,3,2},
    {9,10,1,3},{15,4,3,4},{31,5,3,5},{63,6,3,6},
    {127,7,3,7},{255,8,3,8},{511,9,3,9},{1023,10,3,10},
    {2047,11,3,11},{4095,12,3,12},{8191,13,3,13},{65535,16,3,16}
  },
  { // 8
    {0,4,0,0},{3,5,1,0},{5,7,1,1},{7,3,3,2},
    {9,10,1,3},{15,4,3,4},{31,5,3,5},{63,6,3,6},
    {127,7,3,7},{255,8,3,8},{511,9,3,9},{1023,10,3,10},
    {2047,11,3,11},{4095,12,3,12},{8191,13,3,13},{65535,16,3,16}
  },
  { // 9
    {0,4,0,0},{3,5,1,0},{5,7,1,1},{7,3,3,2},
    {9,10,1,3},{15,4,3,4},{31,5,3,5},{63,6,3,6},
    {127,7,3,7},{255,8,3,8},{511,9,3,9},{1023,10,3,10},
    {2047,11,3,11},{4095,12,3,12},{8191,13,3,13},{65535,16,3,16}
  },
  { // 10
    {0,4,0,0},{3,5,1,0},{5,7,1,1},{7,3,3,2},
    {9,10,1,3},{15,4,3,4},{31,5,3,5},{63,6,3,6},
    {127,7,3,7},{255,8,3,8},{511,9,3,9},{1023,10,3,10},
    {2047,11,3,11},{4095,12,3,12},{8191,13,3,13},{65535,16,3,16}
  },
  { // 11
    {0,3,0,0},{3,5,1,0},{5,7,1,1},{7,3,3,2},
    {9,10,1,3},{15,4,3,4},{31,5,3,5},{65535,16,3,16}
  },
  { // 12
    {0,3,0,0},{3,5,1,0},{5,7,1,1},{7,3,3,2},
    {9,10,1,3},{15,4,3,4},{31,5,3,5},{65535,16,3,16}
  },
  { // 13
    {0,3,0,0},{3,5,1,0},{5,7,1,1},{7,3,3,2},
    {9,10,1,3},{15,4,3,4},{31,5,3,5},{65535,16,3,16}
  },
  { // 14
    {0,3,0,0},{3,5,1,0},{5,7,1,1},{7,3,3,2},
    {9,10,1,3},{15,4,3,4},{31,5,3,5},{65535,16,3,16}
  },
  { // 15
    {0,3,0,0},{3,5,1,0},{5,7,1,1},{7,3,3,2},
    {9,10,1,3},{15,4,3,4},{31,5,3,5},{65535,16,3,16}
  },
  { // 16
    {0,3,0,0},{3,5,1,0},{5,7,1,1},{7,3,3,2},
    {9,10,1,3},{15,4,3,4},{31,5,3,5},{65535,16,3,16}
  },
  { // 17
    {0,3,0,0},{3,5,1,0},{5,7,1,1},{7,3,3,2},
    {9,10,1,3},{15,4,3,4},{31,5,3,5},{65535,16,3,16}
  },
  { // 18
    {0,3,0,0},{3,5,1,0},{5,7,1,1},{7,3,3,2},
    {9,10,1,3},{15,4,3,4},{31,5,3,5},{65535,16,3,16}
  },
  { // 19
    {0,3,0,0},{3,5,1,0},{5,7,1,1},{7,3,3,2},
    {9,10,1,3},{15,4,3,4},{31,5,3,5},{65535,16,3,16}
  },
  { // 20
    {0,3,0,0},{3,5,1,0},{5,7,1,1},{7,3,3,2},
    {9,10,1,3},{15,4,3,4},{31,5,3,5},{65535,16,3,16}
  },
  { // 21
    {0,3,0,0},{3,5,1,0},{5,7,1,1},{7,3,3,2},
    {9,10,1,3},{15,4,3,4},{31,5,3,5},{65535,16,3,16}
  },
  { // 22
    {0,3,0,0},{3,5,1,0},{5,7,1,1},{7,3,3,2},
    {9,10,1,3},{15,4,3,4},{31,5,3,5},{65535,16,3,16 }
  },
  { // 23
    {0,2,0,0},{3,5,1,0},{5,7,1,1},{65535,16,3,16}
  },
  { // 24
    {0,2,0,0},{3,5,1,0},{5,7,1,1},{65535,16,3,16}
  },
  { // 25
    {0,2,0,0},{3,5,1,0},{5,7,1,1},{65535,16,3,16}
  },
  { // 26
    {0,2,0,0},{3,5,1,0},{5,7,1,1},{65535,16,3,16}
  }
};


static sb_alloc al_table_1[SBLIMIT][16] =
{
    {
      {0,4,0,0},{3,5,1,0},{7,3,3,2},{15,4,3,4},
      {31,5,3,5},{63,6,3,6},{127,7,3,7},{255,8,3,8},
      {511,9,3,9},{1023,10,3,10},{2047,11,3,11},{4095,12,3,12},
      {8191,13,3,13},{16383,14,3,14},{32767,15,3,15},{65535,16,3,16},
    },
    {
      {0,4,0,0},{3,5,1,0},{7,3,3,2},{15,4,3,4},
      {31,5,3,5},{63,6,3,6},{127,7,3,7},{255,8,3,8},
      {511,9,3,9},{1023,10,3,10},{2047,11,3,11},{4095,12,3,12},
      {8191,13,3,13},{16383,14,3,14},{32767,15,3,15},{65535,16,3,16},
    },
    {
      {0,4,0,0},{3,5,1,0},{7,3,3,2},{15,4,3,4},
      {31,5,3,5},{63,6,3,6},{127,7,3,7},{255,8,3,8},
      {511,9,3,9},{1023,10,3,10},{2047,11,3,11},{4095,12,3,12},
      {8191,13,3,13},{16383,14,3,14},{32767,15,3,15},{65535,16,3,16}
    },
    {
      {0,4,0,0},{3,5,1,0},{5,7,1,1},{7,3,3,2},
      {9,10,1,3},{15,4,3,4},{31,5,3,5},{63,6,3,6},
      {127,7,3,7},{255,8,3,8},{511,9,3,9},{1023,10,3,10},
      {2047,11,3,11},{4095,12,3,12},{8191,13,3,13},{65535,16,3,16}
    },
    {
      {0,4,0,0},{3,5,1,0},{5,7,1,1},{7,3,3,2},
      {9,10,1,3},{15,4,3,4},{31,5,3,5},{63,6,3,6},
      {127,7,3,7},{255,8,3,8},{511,9,3,9},{1023,10,3,10},
      {2047,11,3,11},{4095,12,3,12},{8191,13,3,13},{65535,16,3,16}
    },
    {
      {0,4,0,0},{3,5,1,0},{5,7,1,1},{7,3,3,2},
      {9,10,1,3},{15,4,3,4},{31,5,3,5},{63,6,3,6},
      {127,7,3,7},{255,8,3,8},{511,9,3,9},{1023,10,3,10},
      {2047,11,3,11},{4095,12,3,12},{8191,13,3,13},{65535,16,3,16}
    },
    {
      {0,4,0,0},{3,5,1,0},{5,7,1,1},{7,3,3,2},
      {9,10,1,3},{15,4,3,4},{31,5,3,5},{63,6,3,6},
      {127,7,3,7},{255,8,3,8},{511,9,3,9},{1023,10,3,10},
      {2047,11,3,11},{4095,12,3,12},{8191,13,3,13},{65535,16,3,16}
    },
    {
      {0,4,0,0},{3,5,1,0},{5,7,1,1},{7,3,3,2},
      {9,10,1,3},{15,4,3,4},{31,5,3,5},{63,6,3,6},
      {127,7,3,7},{255,8,3,8},{511,9,3,9},{1023,10,3,10},
      {2047,11,3,11},{4095,12,3,12},{8191,13,3,13},{65535,16,3,16}
    },
    {
      {0,4,0,0},{3,5,1,0},{5,7,1,1},{7,3,3,2},
      {9,10,1,3},{15,4,3,4},{31,5,3,5},{63,6,3,6},
      {127,7,3,7},{255,8,3,8},{511,9,3,9},{1023,10,3,10},
      {2047,11,3,11},{4095,12,3,12},{8191,13,3,13},{65535,16,3,16}
    },
    {
      {0,4,0,0},{3,5,1,0},{5,7,1,1},{7,3,3,2},
      {9,10,1,3},{15,4,3,4},{31,5,3,5},{63,6,3,6},
      {127,7,3,7},{255,8,3,8},{511,9,3,9},{1023,10,3,10},
      {2047,11,3,11},{4095,12,3,12},{8191,13,3,13},{65535,16,3,16}
    },
    {
      {0,4,0,0},{3,5,1,0},{5,7,1,1},{7,3,3,2},
      {9,10,1,3},{15,4,3,4},{31,5,3,5},{63,6,3,6},
      {127,7,3,7},{255,8,3,8},{511,9,3,9},{1023,10,3,10},
      {2047,11,3,11},{4095,12,3,12},{8191,13,3,13},{65535,16,3,16}
    },
    {
      {0,3,0,0},{3,5,1,0},{5,7,1,1},{7,3,3,2},
      {9,10,1,3},{15,4,3,4},{31,5,3,5},{65535,16,3,16}
    },
    {
      {0,3,0,0},{3,5,1,0},{5,7,1,1},{7,3,3,2},
      {9,10,1,3},{15,4,3,4},{31,5,3,5},{65535,16,3,16}
    },
    {
      {0,3,0,0},{3,5,1,0},{5,7,1,1},{7,3,3,2},
      {9,10,1,3},{15,4,3,4},{31,5,3,5},{65535,16,3,16}
    },
    {
      {0,3,0,0},{3,5,1,0},{5,7,1,1},{7,3,3,2},
      {9,10,1,3},{15,4,3,4},{31,5,3,5},{65535,16,3,16}
    },
    {
      {0,3,0,0},{3,5,1,0},{5,7,1,1},{7,3,3,2},
      {9,10,1,3},{15,4,3,4},{31,5,3,5},{65535,16,3,16}
    },
    {
      {0,3,0,0},{3,5,1,0},{5,7,1,1},{7,3,3,2},
      {9,10,1,3},{15,4,3,4},{31,5,3,5},{65535,16,3,16}
    },
    {
      {0,3,0,0},{3,5,1,0},{5,7,1,1},{7,3,3,2},
      {9,10,1,3},{15,4,3,4},{31,5,3,5},{65535,16,3,16}
    },
    {
      {0,3,0,0},{3,5,1,0},{5,7,1,1},{7,3,3,2},
      {9,10,1,3},{15,4,3,4},{31,5,3,5},{65535,16,3,16}
    },
    {
      {0,3,0,0},{3,5,1,0},{5,7,1,1},{7,3,3,2},
      {9,10,1,3},{15,4,3,4},{31,5,3,5},{65535,16,3,16}
    },
    {
      {0,3,0,0},{3,5,1,0},{5,7,1,1},{7,3,3,2},
      {9,10,1,3},{15,4,3,4},{31,5,3,5},{65535,16,3,16}
    },
    {
      {0,3,0,0},{3,5,1,0},{5,7,1,1},{7,3,3,2},
      {9,10,1,3},{15,4,3,4},{31,5,3,5},{65535,16,3,16}
    },
    {
      {0,3,0,0},{3,5,1,0},{5,7,1,1},{7,3,3,2},
      {9,10,1,3},{15,4,3,4},{31,5,3,5},{65535,16,3,16}
    },
    {
      {0,2,0,0},{3,5,1,0},{5,7,1,1},{65535,16,3,16}
    },
    {
      {0,2,0,0},{3,5,1,0},{5,7,1,1},{65535,16,3,16}
    },
    {
      {0,2,0,0},{3,5,1,0},{5,7,1,1},{65535,16,3,16}
    },
    {
      {0,2,0,0},{3,5,1,0},{5,7,1,1},{65535,16,3,16}
    },
    {
      {0,2,0,0},{3,5,1,0},{5,7,1,1},{65535,16,3,16}
    },
    {
      {0,2,0,0},{3,5,1,0},{5,7,1,1},{65535,16,3,16}
    },
    {
      {0,2,0,0},{3,5,1,0},{5,7,1,1},{65535,16,3,16}
    }
};

static sb_alloc al_table_2[SBLIMIT][16] =
{
    {
      {0,4,0,0},{3,5,1,0},{5,7,1,1},{9,10,1,3},
      {15,4,3,4},{31,5,3,5},{63,6,3,6},{127,7,3,7},
      {255,8,3,8},{511,9,3,9},{1023,10,3,10},{2047,11,3,11},
      {4095,12,3,12},{8191,13,3,13},{16383,14,3,14},{32767,15,3,15}
    },
    {
      {0,4,0,0},{3,5,1,0},{5,7,1,1},{9,10,1,3},
      {15,4,3,4},{31,5,3,5},{63,6,3,6},{127,7,3,7},
      {255,8,3,8},{511,9,3,9},{1023,10,3,10},{2047,11,3,11},
      {4095,12,3,12},{8191,13,3,13},{16383,14,3,14},{32767,15,3,15}
    },
    {
      {0,3,0,0},{3,5,1,0},{5,7,1,1},{9,10,1,3},
      {15,4,3,4},{31,5,3,5},{63,6,3,6},{127,7,3,7}
    },
    {
      {0,3,0,0},{3,5,1,0},{5,7,1,1},{9,10,1,3},
      {15,4,3,4},{31,5,3,5},{63,6,3,6},{127,7,3,7}
    },
    {
      {0,3,0,0},{3,5,1,0},{5,7,1,1},{9,10,1,3},
      {15,4,3,4},{31,5,3,5},{63,6,3,6},{127,7,3,7}
    },
    {
      {0,3,0,0},{3,5,1,0},{5,7,1,1},{9,10,1,3},
      {15,4,3,4},{31,5,3,5},{63,6,3,6},{127,7,3,7}
    },
    {
      {0,3,0,0},{3,5,1,0},{5,7,1,1},{9,10,1,3},
      {15,4,3,4},{31,5,3,5},{63,6,3,6},{127,7,3,7}
    },
    {
      {0,3,0,0},{3,5,1,0},{5,7,1,1},{9,10,1,3},
      {15,4,3,4},{31,5,3,5},{63,6,3,6},{127,7,3,7}
    }
};

static sb_alloc al_table_3[SBLIMIT][16] =
{
    {
      {0,4,0,0},{3,5,1,0},{5,7,1,1},{9,10,1,3},
      {15,4,3,4},{31,5,3,5},{63,6,3,6},{127,7,3,7},
      {255,8,3,8},{511,9,3,9},{1023,10,3,10},{2047,11,3,11},
      {4095,12,3,12},{8191,13,3,13},{16383,14,3,14},{32767,15,3,15}
    },
    {
      {0,4,0,0},{3,5,1,0},{5,7,1,1},{9,10,1,3},
      {15,4,3,4},{31,5,3,5},{63,6,3,6},{127,7,3,7},
      {255,8,3,8},{511,9,3,9},{1023,10,3,10},{2047,11,3,11},
      {4095,12,3,12},{8191,13,3,13},{16383,14,3,14},{32767,15,3,15}
    },
    {
      {0,3,0,0},{3,5,1,0},{5,7,1,1},{9,10,1,3},
      {15,4,3,4},{31,5,3,5},{63,6,3,6},{127,7,3,7}
    },
    {
      {0,3,0,0},{3,5,1,0},{5,7,1,1},{9,10,1,3},
      {15,4,3,4},{31,5,3,5},{63,6,3,6},{127,7,3,7}
    },
    {
      {0,3,0,0},{3,5,1,0},{5,7,1,1},{9,10,1,3},
      {15,4,3,4},{31,5,3,5},{63,6,3,6},{127,7,3,7}
    },
    {
      {0,3,0,0},{3,5,1,0},{5,7,1,1},{9,10,1,3},
      {15,4,3,4},{31,5,3,5},{63,6,3,6},{127,7,3,7}
    },
    {
      {0,3,0,0},{3,5,1,0},{5,7,1,1},{9,10,1,3},
      {15,4,3,4},{31,5,3,5},{63,6,3,6},{127,7,3,7}
    },
    {
      {0,3,0,0},{3,5,1,0},{5,7,1,1},{9,10,1,3},
      {15,4,3,4},{31,5,3,5},{63,6,3,6},{127,7,3,7}
    },
    {
      {0,3,0,0},{3,5,1,0},{5,7,1,1},{9,10,1,3},
      {15,4,3,4},{31,5,3,5},{63,6,3,6},{127,7,3,7}
    },
    {
      {0,3,0,0},{3,5,1,0},{5,7,1,1},{9,10,1,3},
      {15,4,3,4},{31,5,3,5},{63,6,3,6},{127,7,3,7}
    },
    {
      {0,3,0,0},{3,5,1,0},{5,7,1,1},{9,10,1,3},
      {15,4,3,4},{31,5,3,5},{63,6,3,6},{127,7,3,7}
    },
    {
      {0,3,0,0},{3,5,1,0},{5,7,1,1},{9,10,1,3},
      {15,4,3,4},{31,5,3,5},{63,6,3,6},{127,7,3,7}
    }
};

static sb_alloc al_table_4[SBLIMIT][16] =
{
    {
      {0,4,0,0},{3,5,1,0},{5,7,1,1},{7,3,3,2},
      {9,10,1,3},{15,4,3,4},{31,5,3,5},{63,6,3,6},
      {127,7,3,7},{255,8,3,8},{511,9,3,9},{1023,10,3,10},
      {2047,11,3,11},{4095,12,3,12},{8191,13,3,13},{16383,14,3,14}
    },
    {
      {0,4,0,0},{3,5,1,0},{5,7,1,1},{7,3,3,2},
      {9,10,1,3},{15,4,3,4},{31,5,3,5},{63,6,3,6},
      {127,7,3,7},{255,8,3,8},{511,9,3,9},{1023,10,3,10},
      {2047,11,3,11},{4095,12,3,12},{8191,13,3,13},{16383,14,3,14}
    },
    {
      {0,4,0,0},{3,5,1,0},{5,7,1,1},{7,3,3,2},
      {9,10,1,3},{15,4,3,4},{31,5,3,5},{63,6,3,6},
      {127,7,3,7},{255,8,3,8},{511,9,3,9},{1023,10,3,10},
      {2047,11,3,11},{4095,12,3,12},{8191,13,3,13},{16383,14,3,14}
    },
    {
      {0,4,0,0},{3,5,1,0},{5,7,1,1},{7,3,3,2},
      {9,10,1,3},{15,4,3,4},{31,5,3,5},{63,6,3,6},
      {127,7,3,7},{255,8,3,8},{511,9,3,9},{1023,10,3,10},
      {2047,11,3,11},{4095,12,3,12},{8191,13,3,13},{16383,14,3,14}
    },
    {
      {0,3,0,0},{3,5,1,0},{5,7,1,1},{9,10,1,3},
      {15,4,3,4},{31,5,3,5},{63,6,3,6},{127,7,3,7}
    },
    {
      {0,3,0,0},{3,5,1,0},{5,7,1,1},{9,10,1,3},
      {15,4,3,4},{31,5,3,5},{63,6,3,6},{127,7,3,7}
    },
    {
      {0,3,0,0},{3,5,1,0},{5,7,1,1},{9,10,1,3},
      {15,4,3,4},{31,5,3,5},{63,6,3,6},{127,7,3,7}
    },
    {
      {0,3,0,0},{3,5,1,0},{5,7,1,1},{9,10,1,3},
      {15,4,3,4},{31,5,3,5},{63,6,3,6},{127,7,3,7}
    },
    {
      {0,3,0,0},{3,5,1,0},{5,7,1,1},{9,10,1,3},
      {15,4,3,4},{31,5,3,5},{63,6,3,6},{127,7,3,7}
    },
    {
      {0,3,0,0},{3,5,1,0},{5,7,1,1},{9,10,1,3},
      {15,4,3,4},{31,5,3,5},{63,6,3,6},{127,7,3,7}
    },
    {
      {0,3,0,0},{3,5,1,0},{5,7,1,1},{9,10,1,3},
      {15,4,3,4},{31,5,3,5},{63,6,3,6},{127,7,3,7}
    },
    {
      {0,2,0,0},{3,5,1,0},{5,7,1,1},{9,10,1,3}
    },
    {
      {0,2,0,0},{3,5,1,0},{5,7,1,1},{9,10,1,3}
    },
    {
      {0,2,0,0},{3,5,1,0},{5,7,1,1},{9,10,1,3}
    },
    {
      {0,2,0,0},{3,5,1,0},{5,7,1,1},{9,10,1,3}
    },
    {
      {0,2,0,0},{3,5,1,0},{5,7,1,1},{9,10,1,3}
    },
    {
      {0,2,0,0},{3,5,1,0},{5,7,1,1},{9,10,1,3}
    },
    {
      {0,2,0,0},{3,5,1,0},{5,7,1,1},{9,10,1,3}
    },
    {
      {0,2,0,0},{3,5,1,0},{5,7,1,1},{9,10,1,3}
    },
    {
      {0,2,0,0},{3,5,1,0},{5,7,1,1},{9,10,1,3}
    },
    {
      {0,2,0,0},{3,5,1,0},{5,7,1,1},{9,10,1,3}
    },
    {
      {0,2,0,0},{3,5,1,0},{5,7,1,1},{9,10,1,3}
    },
    {
      {0,2,0,0},{3,5,1,0},{5,7,1,1},{9,10,1,3}
    },
    {
      {0,2,0,0},{3,5,1,0},{5,7,1,1},{9,10,1,3}
    },
    {
      {0,2,0,0},{3,5,1,0},{5,7,1,1},{9,10,1,3}
    },
    {
      {0,2,0,0},{3,5,1,0},{5,7,1,1},{9,10,1,3}
    },
    {
      {0,2,0,0},{3,5,1,0},{5,7,1,1},{9,10,1,3}
    },
    {
      {0,2,0,0},{3,5,1,0},{5,7,1,1},{9,10,1,3}
    },
    {
      {0,2,0,0},{3,5,1,0},{5,7,1,1},{9,10,1,3}
    },
    {
      {0,2,0,0},{3,5,1,0},{5,7,1,1},{9,10,1,3}
    }
};

//---------------------------------------------------------------------------
// choose table, return # sb's
//---------------------------------------------------------------------------
int pick_table (frame_params *fr)
{
  int table, br, sfrq;

  br = bitrate[2-1][fr->header->bitrate_index] / fr->stereo;
  sfrq = s_freq[fr->header->sampling_frequency];

  if (fr->header->version == MPEG_AUDIO_ID)
  {				// MPEG-1
    if ((sfrq == 48 && br >= 56) || (br >= 56 && br <= 80)) table = 0;
    else if (sfrq != 48 && br >= 96) table = 1;
    else if (sfrq != 32 && br <= 48) table = 2;
    else table = 3;
  }
  else table = 4; // MPEG-2 LSF

  if (fr->tab_num != table)
  {
    fr->tab_num = table;
    fr->sblimit = sblims[table];
    switch(table)
    {
      case 1:  fr->alloc = &al_table_1; break;
      case 2:  fr->alloc = &al_table_2; break;
      case 3:  fr->alloc = &al_table_3; break;
      case 4:  
	fr->alloc = &al_table_4; 
	fprintf(stderr,"Warning! Danger! I don't think you can use LSF here!\n");
	break;
      default: fr->alloc = &al_table_0; break;
    }
  }
  return(sblims[table]);
}


void mc_pick_table (frame_params * fr_ps)
{
  int tablemc, tableml, ws, sfrq;

  /* BUG corrected SWKim060695 */
  ws = fr_ps->header->sampling_frequency;
  sfrq = s_freq[ws];

  /* decision rules refer to sampling frequency */
  /* For ML/MC channels, only get to choose between table 0 and 1.
     See ISO13818 Section 2.5.2.12 */
  if (sfrq == 48)
    tablemc = 0;
  else
    tablemc = 1;


  switch(tablemc) {
  case 0:
    fr_ps->alloc_mc = &al_table_0;
    fr_ps->sblimit_mc = sblims[tablemc];
    break;
  case 1:
    fr_ps->alloc_mc = &al_table_1;
    fr_ps->sblimit_mc = sblims[tablemc];
    break;
  }


  if (fr_ps->header->multiling_ch > 0) {
    if (fr_ps->header->multiling_fs == 0) {
      /* ML channels at same freq as main channels */
      fr_ps->tab_num_ml = fr_ps->tab_num_mc;
      fr_ps->alloc_ml = fr_ps->alloc_mc;
      fr_ps->sblimit_ml = fr_ps->sblimit_mc;
    } else {
      /* ML channels at half frequency. i.e. LSF */
      tableml = 4;
      fr_ps->alloc_ml = &al_table_4;
      fr_ps->sblimit_ml = sblims[4];
      }
    }				/* ml_fs==0 */
  /* ml_ch>0 */
  if (verbosity >= 2) {
    printf ("Multchannel uses : sblim = %d,  table = %d\n", fr_ps->sblimit_mc,
	    fr_ps->tab_num_mc);
    if (fr_ps->header->multiling_ch > 0)
      printf ("Multilingual uses : sblim = %d, table = %d\n", fr_ps->sblimit_ml,
	      fr_ps->tab_num_ml);
  }
}
