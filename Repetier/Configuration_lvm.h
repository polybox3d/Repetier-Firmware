#ifndef __CONFIGURATION_LVM_H__
#define __CONFIGURATION_LVM_H__


#define LVM_FACES_NUM       5 // number of Face used. (back, top, bot, right, left, front)
#define LVM_DEFAULT_H       10 // default horizontale intensity
#define LVM_DEFAULT_V       10 // default verticale intensity
#define LVM_DEFAULT_COLOR   0 // default color

#define LVM_BOARD_ID		1
#define TARGET_BOARD_INDEX	PINS_PER_BOARD*LVM_BOARD_ID

#define LVM_FACE_0_H        13
#define LVM_FACE_0_V        12

#define LVM_FACE_1_H        8
#define LVM_FACE_1_V        11

#define LVM_FACE_2_H        5
#define LVM_FACE_2_V        6

#define LVM_FACE_3_H        7
#define LVM_FACE_3_V        45

#define LVM_FACE_4_H        46
#define LVM_FACE_4_V        44

#define LVM_FACE_5_H        -1
#define LVM_FACE_5_V        -1

#define SELECT_DEFINE_FACE( face, type)  ( LVM_FACE_ ## face ## _ ## type ) // where type = L/H/C


#endif // __CONFIGURATION_H
