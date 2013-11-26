#ifndef __CONFIGURATION_LVM_H__
#define __CONFIGURATION_LVM_H__


#define LVM_FACES_NUM       6 // number of Face used. (back, top, bot, right, left, front)
#define LVM_DEFAULT_H       10 // default horizontale intensity
#define LVM_DEFAULT_V       10 // default verticale intensity
#define LVM_DEFAULT_COLOR   0 // default color

#define LVM_FACE_0_H        42
#define LVM_FACE_0_V        42

#define LVM_FACE_1_H        42
#define LVM_FACE_1_V        42

#define LVM_FACE_2_H        42
#define LVM_FACE_2_V        42

#define LVM_FACE_3_H        42
#define LVM_FACE_3_V        42

#define LVM_FACE_4_H        42
#define LVM_FACE_4_V        42

#define LVM_FACE_5_H        42
#define LVM_FACE_5_V        42

#define SELECT_DEFINE_FACE( face, type)  ( LVM_FACE_ ## face ## _ ## type ) // where type = L/H/C


#endif // __CONFIGURATION_H
