#ifndef __LVM_H__
#define __LVM_H__

#include "Configuration_lvm.h"
#include "Face.h" 

extern Face faces[LVM_FACES_NUM];

void lvm_set_global_intensity( uint8_t h, uint8_t v ); 
void lvm_set_global_color(  Color &c );

void lvm_set_face_intensity(uint8_t id, uint8_t h, uint8_t v);

Color lvm_get_global_color();
uint8_t lvm_get_global_h_intensity();
uint8_t lvm_get_global_v_intensity();
uint8_t lvm_get_face_h_intensity(uint8_t id);
uint8_t lvm_get_face_v_intensity(uint8_t id);



#endif // __LVM_H__
